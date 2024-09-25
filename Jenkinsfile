pipeline { 
    agent any 
    options {
        skipStagesAfterUnstable()
    }
    stages {
        stage('Build') { 
            steps { 
                sh 'sudo cmake .'
                sh 'sudo cmake --build .' 
            }
        }
        stage('Test'){
            steps {
                sh './build/Template'
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
        stage('Clean') {
            steps {
                sh 'git clean -d -f -x'
            }
        }
    }
}