#!/usr/bin/python3
# proj.py
#   Script to simplify the build, run, test, docker etc. process
#   Usage:
#       python3 proj.py --help
#   
#   Note: primarily for CI, docker but can't actually run GUI (SDL) from docker
#

#region imports and constants
import argparse
# import logging
import os
import sys
import time
import traceback

try:
    import pexpect
except ImportError:
    print('need pexpect!: please do `python3 -m pip install --user pexpect`')
    sys.exit(1)


# globals, constants, options, etc...
DEFAULT_PEXPECT_LOG_FILE = 'pexpect-output.log'
#LOG_FILE = sys.stdout
IMAGE_NAME = 'pokeyellow'
REPO_NAME = 'PokeYellow_Cpp'
TEST_PROJ_NAME = 'tester'
DEFAULT_HOST_PATH = os.path.realpath(os.getcwd()) # resolved path to repo dir
GUEST_PATH = '/{}'.format(REPO_NAME)
#endregion


#region custom exception(s)
class UserInputException(Exception):
    pass
class DevEnvException(Exception): 
    pass
class NotImplementedException(Exception):
    pass
class CommandException(Exception):
    pass
#endregion


#region helper classes
class SpawnManager(pexpect.spawn):
    """Helper class to manage logfiles and exceptions under pexpect children"""
    def __init__(self, *args, logpath=None, **kwargs):
        self._logfile = logpath
        super(SpawnManager, self).__init__(*args, encoding='utf-8', **kwargs)

    def __enter__(self):
        # open the file ourselves if necessary
        if self._logfile and self._logfile not in [sys.stdout, sys.stderr]:
            self.logfile = open(self._logfile, 'a')
        else:
            self.logfile = self._logfile
        return self

    def __exit__(self, type, value, tb):
        # if still alive, attempt to close via exit...
        if self.isalive():
            self.sendline('exit')
            time.sleep(1) # arbitrary sleep before checking again

        # don't really care why, just close the file...
        if self.logfile and self.logfile not in [sys.stdout, sys.stderr]:
            self.logfile.close()

        assert not self.isalive()

    def nu_expect(self, *args, no_throw=False, **kwargs):
        """Custom expect method to use custom exceptions on timeout/EOF

        just run the command similar to if you were doing a normal child.expect
        *args and **kwargs will absorb and redirect to the expect call
        """
        err = ''
        i = super(SpawnManager, self).expect(
            list(args) + [pexpect.TIMEOUT, pexpect.EOF], **kwargs)
        if i == len(args):
            err = 'Command timed out looking for {}'.format(str(list(args)))
        elif i == len(args) + 1:
            err = 'Command output match not found: {}'.format(str(list(args)))

        if err:
            if no_throw:
                print(err) # do we rly want this? expect user to handle?
                return False
            else:
                raise CommandException(err)
        
        return True
#endregion


#region helper functions
def get_container_hashes(image_name=IMAGE_NAME, get_all=False):
    hashes = []
    cmd = 'docker container ls'
    if get_all:
        cmd = '{} -a --filter ancestor={} -q'.format(cmd, IMAGE_NAME)
    else:
        cmd = '{} --filter ancestor={} -q'.format(cmd, IMAGE_NAME)

    with SpawnManager(cmd) as container_list:
        lines = container_list.readlines()
        hashes = [str(l).strip() for l in lines if l and str(l).strip()]
    return hashes

# NOTE: thise get_cmds are pretty useless since pexpect seems broken with win32
def get_term_cmd():
    if sys.platform == 'win32':
        return 'cmd'
    if sys.platform == 'linux':
        return 'bash'


def get_del_cmd(directory=False):
    if sys.platform == 'win32':
        if directory:
            return 'rmdir /S /Q'
        else:
            return 'del'
    if sys.platform == 'linux':
        if directory:
            return 'rm -rf'
        else:
            return 'rm'

def get_config_cmd():
    if sys.platform == 'win32':
        return 'cmake .. -G "MinGW Makefiles"'
    if sys.platform == 'linux':
        return 'cmake ..'


def get_build_cmd():
    if sys.platform == 'win32':
        return 'mingw32-make'
    if sys.platform == 'linux':
        return 'make'
#endregion


#region the meat and potatoes
def check_env(native=False, host_path=DEFAULT_HOST_PATH):
    """Task to verify the dev environment before attempting build/config"""
    print('doing check task...')
    supported_os = ['linux'] # ['win32', 'linux'] # win32 pexpect wont work...
    if sys.platform not in supported_os:
        raise DevEnvException('Unsupported os {} found!'.format(sys.platform))
    if REPO_NAME != host_path.split(os.sep)[-1]:
        raise DevEnvException('Not being run from repo {}!'.format(REPO_NAME))
    
    # TODO check for g++ mingw vs (native), docker (!native), etc. here

    print('Done checking dev (host) environment, good to go')
    print('')


def do_clean(child, native=False, wipe=False, host_path=DEFAULT_HOST_PATH):
    """Task to clean the build environment"""
    print('doing clean task...')
    if not native:
        print('Using docker...')
        child.sendline('docker images')
        if(not child.nu_expect(IMAGE_NAME, no_throw=True)):
            print('Docker image {} not found, moving on...'.format(
                IMAGE_NAME))
            print('')
            return

        # clean the build artifacts
        hashes = get_container_hashes(image_name=IMAGE_NAME)
        if hashes:
            child.sendline('docker container attach {}'.format(hashes[0]))
            child.sendline('cd {}/build'.format(GUEST_PATH))
            child.sendline('make clean')
            child.sendline('rm -rf ./*')

        print('remove any containers using the image if they exist')
        # need new child process to conveniently get & use output...
        hashes = get_container_hashes(image_name=IMAGE_NAME, get_all=True)
        for s in hashes:
            child.sendline('docker container kill {}'.format(s))
            child.sendline('docker container rm {}'.format(s))
            child.expect(s)

        if wipe:
            # continue with image removal
            child.sendline('docker rmi {}'.format(IMAGE_NAME))
            child.nu_expect('Untagged')
            child.nu_expect('Deleted')
            print('Successfully removed docker image "{}"'.format(IMAGE_NAME))

    else:
        # on native system, prety simple, make clean, rmdir, mkdir...
        child.sendline('cd {}{}build'.format(host_path, os.sep))
        child.sendline('{} clean'.format(get_build_cmd()))
        child.sendline('cd {}'.format(host_path))
        child.sendline('{} build'.format(get_del_cmd(directory=True)))
        child.sendline('{} deps'.format(get_del_cmd(directory=True)))
        #child.sendline('cleanup_all.sh')
        # TODO actually make sure dir doesn't exist...
        child.sendline('mkdir build')
        child.sendline('mkdir deps')
        print('Successfully removed build artifacts')
    print('')


def do_init(child, native=False, host_path=DEFAULT_HOST_PATH):
    """Task to intitialize the build environment (setup docker)"""
    print('doing init task...')
    if native:
        print('native option selected, nothing to do...')
        return
    
    child.sendline('docker images')
    if child.nu_expect(IMAGE_NAME, no_throw=True, timeout=5):
        print('Docker image {} found, moving on...'.format(IMAGE_NAME))
    else:
        print('Docker image not found, creating now')
        child.sendline('docker build -t {}:latest .'.format(IMAGE_NAME))
    
        # note: timeouts were empirically determined...
        child.nu_expect('apt-get.*update')
        print('Updating package base... (may take awhile)')
        child.nu_expect('apt-get install -y', timeout=300)

        print('Installing build dependencies... (may take awhile)')
        child.nu_expect('Successfully built', timeout=300)
        child.nu_expect('Successfully tagged {}:latest'.format(IMAGE_NAME))
        print('Successfully created docker image "{}"'.format(IMAGE_NAME))

    print('Creating detached container now...')
    child.sendline('docker run -d -t -i -v {}:{} {}:latest bash'.format(
        host_path, GUEST_PATH, IMAGE_NAME))
    child.nu_expect('[0-9a-f]{64}')

    # not rly necessary just to see what got started...
    hashes = get_container_hashes(image_name=IMAGE_NAME)
    print('containers for image {}: {}'.format(IMAGE_NAME, hashes))
    print('Successfully initialized...')
    
    print('')


def do_config(child, native=False, host_path=DEFAULT_HOST_PATH):
    """Task to configure the build environment (cmake)"""
    print('doing config task...')

    def _config_cmds(proj_path):
        child.sendline('mkdir -p {}/build'.format(proj_path))
        child.sendline('cd {}/build'.format(proj_path))
        child.sendline(get_config_cmd())
        child.nu_expect('Build files have been written to')

    if not native:
        hashes = get_container_hashes(image_name=IMAGE_NAME)
        if not hashes:
            raise DevEnvException(
                'No containers running! Run the init portion...')
                
        child.sendline('docker container attach {}'.format(hashes[0]))
        _config_cmds(GUEST_PATH)
    else:
        _config_cmds(host_path)

    print('Successfully configured project')
    print('')


def do_build(child, native=False, host_path=DEFAULT_HOST_PATH):
    """Task to build the project"""
    print('doing build task...')
    def _build_cmds(proj_path, proj_name, test_proj_name):
        child.sendline('cd {}/build'.format(proj_path))
        child.sendline('make')
        child.nu_expect('Building CXX object')
        child.nu_expect('Built target {}', proj_name)
        child.nu_expect('Built target {}', test_proj_name)

    if not native:
        hashes = get_container_hashes(image_name=IMAGE_NAME)
        if not hashes:
            raise DevEnvException(
                'No containers running! Run the init portion...')
        
        # TODO: probably need to upfront attach to container else how detach?
        #   maybe find way to send key combo rather than line?
        child.sendline('docker container attach {}'.format(hashes[0]))
        _build_cmds(GUEST_PATH, REPO_NAME, TEST_PROJ_NAME)
    else:
        _build_cmds(host_path, REPO_NAME, TEST_PROJ_NAME)

    print('Successfully built project')
    print('')


def do_run(child, native=False, host_path=DEFAULT_HOST_PATH):
    """Task to run the project"""
    print('doing run task...')
    if not native:
        raise NotImplementedException('Run task not operational for docker')

    child.sendline('cd {}/bin')
    child.sendline('.{}{}'.format(os.sep, REPO_NAME))
    print('starting executable, manually interact/verify now...')
    time.sleep(5)
    print('auto-quitting now')
    child.send('\x1b\r') # ESC control sequence

    print('')


def do_test(child, native=False, host_path=DEFAULT_HOST_PATH):
    """Task to run the test project"""
    print('doing test task...')
    if not native:
        #SDL_VIDEODRIVER="dummy"
        #SDL_AUDIODRIVER="dummy"
        raise NotImplementedException('Test task not operational for docker')
    
    child.sendline('cd {}/bin')
    child.sendline('.{}{}'.format(os.sep, TEST_PROJ_NAME))
    child.nu_expect('PASSED.')
    child.sendline('q')
    print('')
#endregion the meat and potatoes


#region main script functionality
def main():
    """Main function for build script.
        python3 proj.py --help
    """
    arg_parser = argparse.ArgumentParser(description='''
        Project CLI helper. Primarily designed for CI, 
            recommend using/looking into `cmake -G` to setup your own dev env.
        ''')
    _a = arg_parser.add_argument
    # options with consequences don't have single character options
    _a('--native', action='store_true', 
        help='Do operations on the project via native OS (non-docker)')
    _a('--wipe', action='store_true', 
        help='Destroy the previous init/config (including docker images)')
    _a('--clean', action='store_true',
        help='Clean the environment (including docker containers)')
    
    # common workflow options have single character options
    _a('--init', '-i', action='store_true',
        help='Initialize the project environment (i.e. docker image)')
    _a('--config', '-c', action='store_true',
        help='Configure the project')
    _a('--build', '-b', action='store_true',
        help='Build the application')
    _a('--run', '-r', action='store_true',
        help='Run the project')
    _a('--test', '-t', action='store_true',
        help='Run the tests')
    
    # less-used options don't have single character options
    # _a('--mount-local-repo', action='store_true',
    #     help='Use this option to share the host repo source w/ the guest.')
    _a('--pexpect-log-file', type=str, default=DEFAULT_PEXPECT_LOG_FILE,
        help='File to log sub-commands and their output. '
             '"stdout" and "stderr" supported as well')
    _a('--host-path', type=str, default=DEFAULT_HOST_PATH,
        help='Path to repository on host machine')
    #_a('--log_level', '-l', default='INFO', choices=logger.level_names, 
    #    help='log level to print')

    args = arg_parser.parse_args()
    print(args)

    # overwrite the file to start fresh
    pexpect_log_file = args.pexpect_log_file
    if 'stdout' in pexpect_log_file.lower():
        print('using stdout for pexpect output')
        pexpect_log_file = sys.stdout
    elif 'stderr' in pexpect_log_file.lower():
        print('using stderr for pexpect output')
        pexpect_log_file = sys.stderr
    else:
        with open(pexpect_log_file, 'w') as f:
            f.write('Beginning of pexpect content...\n\r')

    try:
        with SpawnManager(get_term_cmd(), logpath=pexpect_log_file) as child:
            # verify input and ability
            check_env(native=args.native, host_path=args.host_path)
            if not any([args.clean, args.init]):
                raise UserInputException('No operations provided...')

            # do operation(s) specified
            if args.clean:
                do_clean(child, native=args.native, wipe=args.wipe, 
                         host_path=args.host_path)
            if args.init:
                do_init(child, native=args.native, host_path=args.host_path)
            if args.config:
                do_config(child, native=args.native, host_path=args.host_path)
            if args.build:
                do_build(child, native=args.native, host_path=args.host_path)
            if args.run:
                do_run(child, native=args.native, host_path=args.host_path)
            if args.test:
                do_test(child, native=args.native, host_path=args.host_path)
            
            child.sendline('exit')
            print('Done.')

    except:
        print('Exception encountered...')
        traceback.print_exc()
        print('See log file {} for more details...'.format(pexpect_log_file))
        arg_parser.print_help()
        sys.exit(1)

if __name__ == '__main__':
    main()
#endregion
