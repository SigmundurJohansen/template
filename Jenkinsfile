pipeline 
{
    agent any

    options 
    {
        buildDiscarder(logRotator(numToKeepStr: '10'))
    }

    stages
    {
        stage('Build') {
            steps {
                cmakeBuild buildType: 'Release', cleanBuild: true, installation: 'InSearchPath', steps: [[withCmake: true]]
            }
        }
    }
}