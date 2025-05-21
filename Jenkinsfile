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
                    // Ограничение: 5 чисел для ввода + 5 секунд на выполнение
                    def status = bat(
                        script: '''
                            cd /d "%WORKSPACE%\\build\\Release"
                            (
                                echo 10
                                echo 30
                                echo 50
                                echo 70
                                echo 90
                                timeout /t 5 /nobreak > nul
                            ) | guess-the-number.exe
                        ''',
                        returnStatus: true
                    )
                    
                    // Проверяем код завершения
                    if (status != 0) {
                        error "Тест провален: программа завершилась с кодом ${status}"
                    }
                }
            }
            timeout(time: 10, unit: 'SECONDS') {  // Двойное ограничение
                echo "Тестирование завершено"
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: 'build/Release/guess-the-number.exe'
        }
    }
}