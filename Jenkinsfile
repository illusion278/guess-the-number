pipeline {
    agent any
    
    environment {
        WORKSPACE = pwd()  // Явное определение рабочей директории
        CMAKE = 'C:\\Program Files\\CMake\\bin\\cmake.exe'
        GENERATOR = 'Visual Studio 17 2022'
        BUILD_DIR = "${WORKSPACE}\\build"
    }

    stages {
        stage('Verify Files') {
            steps {
                bat """
                    echo Проверка файлов в рабочей директории:
                    dir
                    echo Содержимое CMakeLists.txt:
                    type CMakeLists.txt || echo Файл CMakeLists.txt не найден!
                """
            }
        }

        stage('Generate Project') {
            steps {
                bat """
                    echo Рабочая директория: %WORKSPACE%
                    if not exist "${BUILD_DIR}" mkdir "${BUILD_DIR}"
                    cd "${BUILD_DIR}"
                    "${CMAKE}" -G "${GENERATOR}" "${WORKSPACE}"
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    cd "${BUILD_DIR}"
                    "${CMAKE}" --build . --config Release
                """
            }
        }

        stage('Test') {
            options {
                timeout(time: 1, unit: 'MINUTES')
            }
            steps {
                bat """
                    cd "${BUILD_DIR}\\Release"
                    guess-the-number.exe
                """
            }
            post {
                always {
                    bat 'taskkill /F /IM guess-the-number.exe /T 2>nul || echo Процесс не найден'
                }
            }
        }
    }

    post {
        failure {
            echo "Сборка завершилась с ошибкой. Проверьте:"
            echo "1. Наличие CMakeLists.txt в корне репозитория"
            echo "2. Пути к CMake и Visual Studio в настройках"
            echo "3. Права доступа Jenkins к файлам"
        }
    }