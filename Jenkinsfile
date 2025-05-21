pipeline {
    agent any

    stages {
        stage('Clean Workspace') {
            steps {
                bat '''
                    cd /d "%WORKSPACE%"
                    rmdir /s /q build 2> nul || echo "No build directory to remove"
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
                    if errorlevel 1 exit 1
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                    cd /d "%WORKSPACE%\\build"
                    cmake --build . --config Release
                    if errorlevel 1 exit 1
                '''
            }
        }

        stage('Test') {
            steps {
                script {
                    // Проверяем, что файл существует
                    def exePath = "%WORKSPACE%\\build\\Release\\guess-the-number.exe"
                    def exists = bat(
                        script: '@echo off && if exist "' + exePath + '" (echo 1) else (echo 0)',
                        returnStdout: true
                    ).trim() == '1'

                    if (!exists) {
                        error "Executable file not found: ${exePath}"
                    }

                    // Автоматизированный тест (проверяем обработку ввода)
                    def output = bat(
                        script: '''
                            @echo off
                            echo 50 > input.txt
                            echo 75 >> input.txt
                            echo 42 >> input.txt
                            guess-the-number.exe < input.txt
                        ''',
                        returnStdout: true
                    )

                    // Проверяем наличие сообщения о победе
                    if (!output.contains("Congratulations! You guessed it!")) {
                        error "Game logic test failed!"
                    }
                }
            }
        }
    }

    post {
        always {
            bat 'type "%WORKSPACE%\\build\\Release\\game_log.txt" || echo No log file found'
        }
    }
}