pipeline {
    agent any
    
    environment {
        CMAKE_PATH = 'C:\\Program Files\\CMake\\bin\\cmake.exe'
        GENERATOR = 'Visual Studio 17 2022'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                bat """
                    mkdir build || cd build
                    "${CMAKE_PATH}" -G "${GENERATOR}" ..
                    "${CMAKE_PATH}" --build . --config Release
                """
            }
        }

        stage('Test') {
            steps {
                timeout(time: 1, unit: 'MINUTES') {
                    bat 'build\\Release\\guess-the-number.exe'
                }
            }
        }
    }

    post {
        always {
            bat 'taskkill /F /IM guess-the-number.exe /T 2>nul || echo Процесс не найден'
        }
    }
}