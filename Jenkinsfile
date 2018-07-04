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
        sh '''pwd
ls
git checkout master
git pull origin master'''
      }
    }
    stage('Build') {
      steps {
        echo 'now buildin\''
        sh '''if ! cmake . ; then
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
        sh '''cd test
ctest'''
      }
    }
  }
}