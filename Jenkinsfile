pipeline {
    agent any

    environment {
        BUILD_DIR = "${WORKSPACE}\\build"
        CMAKE = "C:\\Program Files\\CMake\\bin\\cmake.exe"
        MSBUILD = "C:\\Program Files\\Microsoft Visual Studio\\2022\\BuildTools\\MSBuild\\Current\\Bin\\MSBuild.exe"
    }

    stages {
        stage('Clean Workspace') {
            steps {
                script {
                    // Более надежный способ очистки
                    try {
                        bat """
                            @echo off
                            cd /d "%WORKSPACE%"
                            if exist build (
                                taskkill /F /IM guess-the-number.exe /T >nul 2>&1 || echo No process to kill
                                timeout /t 1 /nobreak >nul
                                rmdir /s /q build
                            ) else (
                                echo "No build directory found"
                            )
                        """
                    } catch (e) {
                        echo "Cleanup warning: ${e}"
                    }
                }
            }
        }

        stage('Configure') {
            steps {
                bat """
                    @echo off
                    mkdir "${BUILD_DIR}" 2>nul || echo Build directory exists
                    cd /d "${BUILD_DIR}"
                    "${CMAKE}" -G "Visual Studio 17 2022" -A x64 ..
                    if %errorlevel% neq 0 exit /b %errorlevel%
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    @echo off
                    cd /d "${BUILD_DIR}"
                    "${MSBUILD}" guess-the-number.sln /p:Configuration=Release /p:Platform=x64 /v:m
                    if %errorlevel% neq 0 exit /b %errorlevel%
                """
            }
        }

        stage('Locate EXE') {
            steps {
                script {
                    // Надежный поиск исполняемого файла
                    env.EXE_PATH = bat(
                        script: '''
                            @echo off
                            for /r "%BUILD_DIR%" %%i in (guess-the-number.exe) do (
                                if exist "%%i" (
                                    echo %%i
                                    exit /b 0
                                )
                            )
                            exit /b 1
                        ''',
                        returnStdout: true
                    ).trim()

                    if (!env.EXE_PATH?.trim()) {
                        bat '''
                            @echo off
                            echo "Executable search failed. Directory contents:"
                            dir /s /b "%BUILD_DIR%\\*.exe" || echo No EXE files found
                        '''
                        error "Executable guess-the-number.exe not found!"
                    }
                    echo "Found executable at: ${env.EXE_PATH}"
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    // Подготовка тестовых данных
                    writeFile file: "${WORKSPACE}\\input.txt", text: """50
75
42
"""

                    // Запуск теста с таймаутом
                    def output = bat(
                        script: """
                            @echo off
                            cd /d "%WORKSPACE%"
                            "${env.EXE_PATH}" < input.txt
                            if %errorlevel% neq 0 exit /b %errorlevel%
                        """,
                        returnStdout: true
                    )

                    // Проверка результата
                    if (!output?.contains("Congratulations")) {
                        bat 'type input.txt || echo Failed to read input'
                        error "Test failed! Program output:\n${output}"
                    }
                    echo "Test passed successfully!"
                }
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: "**/*.exe, **/*.log, **/input.txt", allowEmptyArchive: true
            junit "**/test-results.xml" allowEmptyResults: true
        }
        cleanup {
            bat '''
                @echo off
                taskkill /F /IM guess-the-number.exe /T >nul 2>&1 || echo Process not found
                del /q input.txt 2>nul || echo No input file
            '''
        }
    }
}