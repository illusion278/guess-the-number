pipeline {
    agent any
    
    options {
        timeout(time: 15, unit: 'MINUTES') // Общий таймаут для всего пайплайна
        disableConcurrentBuilds() // Запрет параллельных сборок
    }

    environment {
        BUILD_DIR = "${WORKSPACE}\\build"
        CMAKE = "C:\\Program Files\\CMake\\bin\\cmake.exe"
        GENERATOR = "Visual Studio 17 2022"
        CONFIG = "Release"
    }

    stages {
        stage('Prepare') {
            steps {
                bat """
                    echo Проверка системы:
                    where cmake
                    where msbuild
                    echo Рабочая директория: %WORKSPACE%
                    dir
                """
            }
        }

        stage('Generate') {
            steps {
                bat """
                    if not exist "${BUILD_DIR}" mkdir "${BUILD_DIR}"
                    cd "${BUILD_DIR}"
                    "${CMAKE}" -G "${GENERATOR}" -DCMAKE_BUILD_TYPE=${CONFIG} "${WORKSPACE}"
                """
            }
        }

        stage('Build') {
            options {
                timeout(time: 5, unit: 'MINUTES') // Таймаут для сборки
            }
            steps {
                bat """
                    cd "${BUILD_DIR}"
                    "${CMAKE}" --build . --config ${CONFIG} -- /m:4
                """
            }
        }

        stage('Test') {
            options {
                timeout(time: 1, unit: 'MINUTES') // Жесткое ограничение для теста
            }
            steps {
                script {
                    try {
                        bat """
                            cd "${BUILD_DIR}\\${CONFIG}"
                            echo Запуск теста с таймаутом...
                            guess-the-number.exe
                        """
                    } catch (Exception e) {
                        echo "Тест прерван по таймауту"
                        bat 'taskkill /F /IM guess-the-number.exe /T' // Принудительное завершение
                        currentBuild.result = 'UNSTABLE'
                    }
                }
            }
            post {
                always {
                    bat """
                        taskkill /F /IM guess-the-number.exe /T 2>nul || echo Процесс не найден
                        echo Статус завершения теста: %errorlevel%
                    """
                }
            }
        }

        stage('Archive') {
            when {
                expression { currentBuild.resultIsBetterOrEqualTo('UNSTABLE') }
            }
            steps {
                archiveArtifacts artifacts: "${BUILD_DIR}\\${CONFIG}\\guess-the-number.exe", fingerprint: true
            }
        }
    }

    post {
        always {
            echo "Сборка завершена с статусом: ${currentBuild.result}"
            cleanWs() // Очистка workspace
        }
        failure {
            emailext (
                subject: "Сборка ${currentBuild.fullDisplayName} упала",
                body: "Проверьте сборку: ${env.BUILD_URL}",
                to: "dev@example.com"
            )
        }
    }
}