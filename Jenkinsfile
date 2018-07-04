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
git pull origin master'''
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
cd test
ctest'''
      }
    }
  }
}