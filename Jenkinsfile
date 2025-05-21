pipeline {
    agent any

    stages {
        stage('Clean') {
            steps {
                bat 'rmdir /s /q build || echo "No build dir"'
            }
        }

        stage('Configure') {
            steps {
                bat '''
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
                    cd build
                    cmake --build . --config Release
                    if errorlevel 1 exit 1
                '''
            }
        }

        stage('Find Executable') {
            steps {
                script {
                    // Ищем исполняемый файл в возможных путях
                    def exePaths = [
                        "%WORKSPACE%\\build\\Release\\guess-the-number.exe",
                        "%WORKSPACE%\\build\\guess-the-number.exe",
                        "%WORKSPACE%\\build\\bin\\guess-the-number.exe"
                    ]

                    env.EXE_PATH = ""
                    for (path in exePaths) {
                        def exists = bat(
                            script: "@echo off && if exist \"${path}\" (echo 1) else (echo 0)", 
                            returnStdout: true
                        ).trim() == '1'
                        
                        if (exists) {
                            env.EXE_PATH = path
                            break
                        }
                    }

                    if (env.EXE_PATH == "") {
                        error "Executable not found in any standard location!"
                        bat 'dir /s /b *.exe || echo No EXE files found'
                    } else {
                        echo "Found executable at: ${env.EXE_PATH}"
                    }
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    // Готовим тестовые данные
                    writeFile file: 'input.txt', text: '''50
75
42
'''

                    // Запускаем тест
                    bat """
                        @echo off
                        "${env.EXE_PATH}" < input.txt
                        if errorlevel 1 exit 1
                    """
                }
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: '**/*.exe', allowEmptyArchive: true
            bat 'dir /s /b *.exe || echo No EXE files to archive'
        }
    }
}