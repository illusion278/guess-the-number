pipeline {
    agent any
    
    environment {
        // Проверяемые пути
        CMAKE_PATH = 'C:\\Program Files\\CMake\\bin\\cmake.exe'
        VS_GENERATOR = 'Visual Studio 17 2022'
        BUILD_DIR = "${WORKSPACE}\\build"
    }

    stages {
        stage('Verify Setup') {
            steps {
                script {
                    // Проверка наличия CMakeLists.txt
                    if (!fileExists('CMakeLists.txt')) {
                        error("CMakeLists.txt not found in workspace!")
                    }
                    
                    // Проверка инструментов
                    bat """
                        where cmake || echo CMake not found!
                        where msbuild || echo MSBuild not found!
                    """
                }
            }
        }

        stage('Generate Project') {
            steps {
                bat """
                    @echo off
                    if not exist "${BUILD_DIR}" mkdir "${BUILD_DIR}"
                    cd "${BUILD_DIR}"
                    "${CMAKE_PATH}" -G "${VS_GENERATOR}" "${WORKSPACE}"
                    if %errorlevel% neq 0 exit /b %errorlevel%
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    @echo off
                    cd "${BUILD_DIR}"
                    "${CMAKE_PATH}" --build . --config Release
                    if %errorlevel% neq 0 exit /b %errorlevel%
                """
            }
        }

        stage('Test') {
            options {
                timeout(time: 1, unit: 'MINUTES') 
            }
            steps {
                bat """
                    @echo off
                    cd "${BUILD_DIR}\\Release"
                    guess-the-number.exe
                """
            }
            post {
                always {
                    bat 'taskkill /F /IM guess-the-number.exe /T 2>nul || echo Process not found'
                }
            }
        }
    }

    post {
        failure {
            echo "Build failed! Check:"
            echo "1. CMakeLists.txt exists in root"
            echo "2. Visual Studio 2022 installed"
            echo "3. CMake 3.15+ available in PATH"
        }
    }
}