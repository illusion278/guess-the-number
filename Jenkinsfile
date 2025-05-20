pipeline {
    agent any

    environment {
        CMAKE = 'C:\\Program Files\\CMake\\bin\\cmake.exe'
        GENERATOR = 'Visual Studio 17 2022'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm  // Однократный checkout
            }
        }

        stage('Build') {
            steps {
                bat """
                    mkdir build || cd build
                    "${CMAKE}" -G "${GENERATOR}" ..
                    "${CMAKE}" --build . --config Release
                """
            }
        }

        stage('Test') {
            steps {
                bat 'build\\Release\\guess-the-number.exe'
            }
        }
    }

    post {
        always {
            echo 'Pipeline completed'
        }
        failure {
            echo 'Pipeline failed!'
        }
    }
}