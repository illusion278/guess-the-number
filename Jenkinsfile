pipeline {
    agent any

    environment {
        // Явно указываем пути к инструментам
        CMAKE = "C:\\Program Files\\CMake\\bin\\cmake.exe"
        MSBUILD = "C:\\Program Files\\Microsoft Visual Studio\\2022\\BuildTools\\MSBuild\\Current\\Bin\\MSBuild.exe"
    }

    stages {
        stage('Prepare') {
            steps {
                cleanWs()
                bat """
                    where cmake || echo CMake not found in PATH
                    where msbuild || echo MSBuild not found in PATH
                """
            }
        }

        stage('Configure') {
            steps {
                bat """
                    mkdir build || echo Build dir exists
                    cd build
                    "${CMAKE}" -G "Visual Studio 17 2022" -A x64 ..
                    if errorlevel 1 exit 1
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    cd build
                    "${MSBUILD}" guess-the-number.sln /p:Configuration=Release /p:Platform=x64
                    if errorlevel 1 exit 1
                """
            }
        }

        stage('Locate EXE') {
            steps {
                script {
                    // Ищем исполняемый файл в стандартных путях
                    env.EXE_PATH = bat(
                        script: '@echo off && for /r "%WORKSPACE%\\build" %%i in (guess-the-number.exe) do echo %%i',
                        returnStdout: true
                    ).trim()

                    if (!env.EXE_PATH) {
                        bat 'dir /s /b *.exe || echo No EXE files found'
                        error "Executable not found after build!"
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

                    // Запускаем программу
                    def output = bat(
                        script: """
                            @echo off
                            echo ${testInput} > input.txt
                            "${env.EXE_PATH}" < input.txt
                            if %errorlevel% neq 0 exit %errorlevel%
                        """,
                        returnStdout: true
                    )

                    // Проверяем результат
                    if (!output.contains("Congratulations")) {
                        error "Test failed! Output:\n${output}"
                    }
                    echo "Test passed successfully!"
                }
            }
        }
    }

    post {
        always {
            archiveArtifacts artifacts: "**/*.exe, **/*.log"
            bat 'taskkill /IM guess-the-number.exe /F /T || echo Process not found'
        }
    }
}