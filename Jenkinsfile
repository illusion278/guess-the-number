pipeline {
    agent any
    
    environment {
        // Убедитесь, что Node.js в PATH
        PATH = "C:\\Program Files\\nodejs;${env.PATH}"
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }
        
        stage('Setup Node.js') {
            steps {
                // Проверка доступности Node.js и npm
                bat 'node --version'
                bat 'npm --version'
            }
        }
        
        stage('Install dependencies') {
            steps {
                bat 'npm install'
            }
        }
        
        stage('Build') {
            steps {
                bat 'npm run build'
            }
        }
        
        stage('Test') {
            steps {
                bat 'npm test'
            }
        }
        
        stage('Kill previous process') {
            steps {
                script {
                    try {
                        // Попытка завершить предыдущий процесс
                        bat 'taskkill /F /IM guess-the-number.exe /T || exit 0'
                    } catch (e) {
                        echo "No process to kill or error killing: ${e}"
                    }
                }
            }
        }
        
        stage('Run application') {
            steps {
                bat 'start "" npm start'
            }
        }
    }
    
    post {
        always {
            echo 'Pipeline completed'
        }
        failure {
            echo 'Pipeline failed!'
            // Дополнительные действия при ошибке
        }
    }
}