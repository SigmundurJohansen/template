pipeline { 
    agent any 
    options {
        skipStagesAfterUnstable()
    }
    stages {
        stage('Build') { 
            steps { 
                sh 'cmake .'
                sh 'cmake --build .' 
            }
        }
        stage('Test'){
            steps {
                sleep(2)
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
        stage('clean') {
            steps {
                sleep(2)
                sh 'git clean -d -f -x'
            }
        }
    }
}