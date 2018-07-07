pipeline {
  agent {
    node {
      label 'node-bro'
    }

  }
  stages {
    stage('Obtain') {
      steps {
        echo 'get it boi'
        sh '''# Check current dir/path, checkout & pull branch
pwd 
ls 
git checkout master 
git pull origin master
'''
      }
    }
    stage('Build') {
      steps {
        echo 'now buildin\''
        sh '''# run cmake then make
if ! cmake . ; then
    echo "error in cmake!"
    exit 1
fi
if ! make ; then
    echo "error in make!"
    exit 1
fi
'''
      }
    }
    stage('Test') {
      steps {
        echo 'now testin\''
        sh '''# ssh localhost with x11 forwarding for tests (sdl) to work
echo "$(pwd)" > ~/wd.txt
yes | ssh-keygen -N "" -f ~/.ssh/id_rsa.localhost
chmod 400 ~/.ssh/id_rsa.localhost
cat ~/.ssh/id_rsa.localhost.pub >> ~/.ssh/authorized_keys
ssh -oUserKnownHostsFile=/dev/null -oStrictHostKeyChecking=no -i ~/.ssh/id_rsa.localhost -X localhost
cd $(cat ~/wd.txt)
export DISPLAY=:0

# run ctest
# cd test
# ctest

# run gtest
cd bin
./tester'''
      }
    }
  }
}