pipeline {
    agent any

    stages {
        stage('Clean Workspace') {
            steps {
                bat '''
                    cd /d "%WORKSPACE%"
                    rmdir /s /q build || echo "No build directory to remove"
                '''
            }
        }

        stage('Configure CMake') {
            steps {
                bat '''
                    cd /d "%WORKSPACE%"
                    mkdir build
                    cd build
                    cmake -G "Visual Studio 17 2022" -A x64 ..
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                    cd /d "%WORKSPACE%\\build"
                    cmake --build . --config Release
                '''
            }
        }

        stage('Test') {
            steps {
                bat '''
                    cd /d "%WORKSPACE%\\build\\Release"
                    echo 50 | guess-the-number.exe
                '''
            }
        }
    }
}