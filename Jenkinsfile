pipeline {
    agent any

    environment {
        // Устанавливаем UTF-8 для корректного отображения символов
        JAVA_TOOL_OPTIONS = '-Dfile.encoding=UTF-8'
        LANG = 'en_US.UTF-8'
        BUILD_DIR = "${WORKSPACE}/build"
    }

    stages {
        stage('Checkout') {
            steps {
                checkout([
                    $class: 'GitSCM',
                    branches: [[name: '*/main']],
                    extensions: [],
                    userRemoteConfigs: [[
                        url: 'https://github.com/illusion278/guess-the-number.git'
                    ]]
                ])
            }
        }

        stage('Configure CMake') {
            steps {
                bat '''
                    mkdir build || cd build
                    cmake -G "Visual Studio 16 2019" -A x64 -S . -B build
                '''
            }
        }

        stage('Build') {
            steps {
                bat '''
                    cd build
                    cmake --build . --config Release --target ALL_BUILD
                '''
            }
        }

        stage('Test') {
            steps {
                script {
                    // Автоматический тест с заранее заданными числами
                    def testCases = [
                        [input: "50\n", expected: "Правильно|Слишком много"],
                        [input: "10\n20\n30\n", expected: "Слишком мало"]
                    ]
                    
                    testCases.each { testCase ->
                        def output = bat(
                            script: """
                                cd build\\Release
                                echo ${testCase.input} | guess-the-number.exe
                            """,
                            returnStdout: true
                        ).trim()
                        
                        if (!(output =~ /${testCase.expected}/)) {
                            error "Тест провален для ввода ${testCase.input}"
                        }
                    }
                }
            }
            post {
                always {
                    archiveArtifacts artifacts: 'build/Release/guess-the-number.exe', fingerprint: true
                }
            }
        }
    }

    post {
        failure {
            emailext body: 'Сборка провалена. Проверьте консольный вывод.',
                    subject: 'FAILED: Job ${env.JOB_NAME}',
                    to: 'admin@example.com'
        }
        success {
            echo 'Сборка успешно завершена!'
        }
    }
}