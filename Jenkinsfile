pipeline { 
    agent any 
    options {
        skipStagesAfterUnstable()
    }
    stages {
        stage('Build') { 
            steps { 
                sh 'make:' 
            }
        }
        stage('Test'){
            steps {
                sleep(2)
                // sh 'make check'
                // junit 'reports/**/*.xml' 
            }
        }
        stage('Deploy') {
            steps {
                sleep(2)
                //sh 'make publish'
            }
        }
    }
}