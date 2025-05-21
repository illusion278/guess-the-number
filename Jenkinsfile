pipeline {
    agent any

    environment {
        BUILD_DIR = "${WORKSPACE}/build"
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Configure') {
            steps {
                bat '''
                    cd "${WORKSPACE}"
                    if not exist build mkdir build
                    cd build
                    cmake -G "Visual Studio 16 2019" -A x64 ..
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                    cd "${WORKSPACE}/build"
                    cmake --build . --config Release
                '''
            }
        }

        stage('Test') {
            steps {
                bat '''
                    cd "${WORKSPACE}/build/Release"
                    echo 50 | guess-the-number.exe
                '''
            }
        }
    }
}