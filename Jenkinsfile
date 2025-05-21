pipeline {
    agent any

    environment {
        BUILD_DIR = "${WORKSPACE}\\build"
        // Для Windows используем явное указание пути к CMake
        CMAKE_PATH = "C:\\Program Files\\CMake\\bin\\cmake.exe"
    }

    stages {
        stage('Prepare') {
            steps {
                cleanWs()
                bat """
                    mkdir "${BUILD_DIR}"
                    where cmake || echo "CMake not found in PATH"
                """
            }
        }

        stage('Configure') {
            steps {
                bat """
                    cd "${BUILD_DIR}"
                    "${CMAKE_PATH}" -G "Visual Studio 17 2022" -A x64 ..
                    if errorlevel 1 exit 1
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    cd "${BUILD_DIR}"
                    "${CMAKE_PATH}" --build . --config Release --target guess-the-number
                    if errorlevel 1 exit 1
                """
            }
        }

        stage('Locate Executable') {
            steps {
                script {
                    // Ищем исполняемый файл по маске
                    env.EXE_PATH = bat(
                        script: '@echo off && dir /s /b "*guess-the-number.exe" | find /v "\\vcxproj\\"',
                        returnStdout: true
                    ).trim()

                    if (!env.EXE_PATH) {
                        bat 'dir /s /b *.exe || echo No EXE files found'
                        error "Executable not found!"
                    }
                    echo "Found executable at: ${env.EXE_PATH}"
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    // Подготавливаем тестовые данные
                    def testInput = """
                        50
                        75
                        42
                    """

                    // Запускаем тестирование с таймаутом
                    def output = bat(
                        script: """
                            @echo off
                            echo ${testInput} > input.txt
                            "${env.EXE_PATH}" < input.txt
                        """,
                        returnStdout: true
                    )

                    // Анализ результатов
                    if (output.contains("Congratulations! You guessed it!")) {
                        echo "Test passed successfully!"
                    } else {
                        echo "Test output:\n${output}"
                        error "Test failed - correct guess not detected!"
                    }
                }
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: "**/*.exe, **/*.log", allowEmptyArchive: true
            junit "**/test-results.xml" allowEmptyResults: true
        }
        failure {
            bat 'tasklist /FI "IMAGENAME eq guess-the-number.exe" /NH'
            bat 'taskkill /F /IM guess-the-number.exe /T || echo "Process not found"'
        }
    }
}