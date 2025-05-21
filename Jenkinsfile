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
                script {
                    def testInputs = [10, 25, 50, 75, 100]
                    def output = bat(
                        script: """
                            cd /d "%WORKSPACE%\\build\\Release"
                            ${testInputs.collect { "echo ${it}" }.join(' & ')} | guess-the-number.exe
                        """,
                        returnStdout: true
                    )
                    
                    if (!output.contains("Правильно")) {
                        error "Тест не пройден: число не было угадано"
                    }
                }
            }
            timeout(time: 30, unit: 'SECONDS') {
                // Ограничение времени выполнения
            }
        }
    }
}