pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                bat 'mkdir build'
                dir('build') {
                    bat 'cmake ..'
                    bat 'cmake --build .'
                }
            }
        }
        stage('Test') {
            steps {
                bat '.\\build\\Debug\\guess-the-number.exe' // Или Release
            }
        }
    }
}