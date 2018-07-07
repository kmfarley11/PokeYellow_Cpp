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

# also setup env vars (X11 forwarding)
echo $(pwd) > ~/wd.txt
yes | ssh-keygen -N "" -f ~/.ssh/id_rsa.local
chmod 400 ~/.ssh/id_rsa.local
cat ~/.ssh/id_rsa.local.pub >> ~/.ssh/authorized_keys
ssh -oUserKnownHostsFile=/dev/null -oStrictHostKeyChecking=no -i ~/.ssh/id_rsa.local -X localhost
cd $(cat wd.txt)
export DISPLAY=:0
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
        sh '''# run ctest
# cd test
# ctest
# run gtest
cd bin
./tester'''
      }
    }
  }
}