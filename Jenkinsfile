pipeline {
    agent any

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Generate Solution') {
            steps {
                bat 'mkdir build || true'
                dir('build') {
                    bat '"C:\\Program Files\\CMake\\bin\\cmake.exe" .. -G "Visual Studio 17 2022" -A x64'
                }
            }
        }

        stage('Build') {
            steps {
                dir('build') {
                    bat '"C:\\Program Files\\CMake\\bin\\cmake.exe" --build . --config Release'
                }
            }
        }

        stage('Test') {
            steps {
                // Здесь могут быть ваши тесты, например:
                bat '"C:\\Program Files\\CMake\\bin\\ctest.exe" --output-on-failure -C Release'
            }
        }
    }

    post {
        always {
            cleanWs()
        }
    }
}