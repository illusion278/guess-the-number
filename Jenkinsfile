pipeline {
    agent any

    environment {
        BUILD_DIR = "${WORKSPACE}\\build"
    }

    stages {
        stage('Build') {
            steps {
                bat """
                    mkdir "${BUILD_DIR}" || echo Folder exists
                    cd "${BUILD_DIR}"
                    cmake -G "Visual Studio 17 2022" -A x64 ..
                    cmake --build . --config Release --target guess-the-number
                """
            }
        }

        stage('Locate EXE') {
            steps {
                script {
                    env.EXE_PATH = bat(
                        script: '@echo off && for /r "%BUILD_DIR%" %%i in (guess-the-number.exe) do echo %%i',
                        returnStdout: true
                    ).trim()
                    
                    if (!env.EXE_PATH) {
                        bat 'dir /s /b *.exe || echo No EXE files found'
                        error "guess-the-number.exe not found after build!"
                    }
                    echo "Executable path: ${env.EXE_PATH}"
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    try {
                        def output = bat(
                            script: """
                                @echo off
                                echo 50 > input.txt
                                echo 75 >> input.txt
                                echo 42 >> input.txt
                                "${env.EXE_PATH}" < input.txt
                                if %errorlevel% neq 0 exit %errorlevel%
                            """,
                            returnStdout: true
                        )
                        
                        if (!output.contains("Congratulations")) {
                            error "Test failed! Output:\n${output}"
                        }
                        echo "Test passed!"
                    } catch (e) {
                        bat 'taskkill /IM guess-the-number.exe /F /T || echo Process not found'
                        error "Test error: ${e}"
                    }
                }
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: "**/*.exe, **/*.log"
            bat 'taskkill /IM guess-the-number.exe /F /T || echo Cleanup complete'
        }
    }
}