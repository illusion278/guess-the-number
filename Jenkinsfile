pipeline {
    agent any

    environment {
        WORKSPACE = pwd()  // Получаем текущий рабочий каталог
        CMAKE = 'C:\\Program Files\\CMake\\bin\\cmake.exe'
        GENERATOR = 'Visual Studio 17 2022'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Build') {
            steps {
                bat """
                    cd "${WORKSPACE}"
                    if not exist build mkdir build
                    cd build
                    "${CMAKE}" -G "${GENERATOR}" "${WORKSPACE}"
                    "${CMAKE}" --build . --config Release
                """
            }
        } 
         
        stage('Verify Files') {
            steps {
                bat """
                    dir "${WORKSPACE}"
                    type "${WORKSPACE}\\CMakeLists.txt"
                """
            }
        }

        stage('Test') {
            steps {
                bat """
                    cd "${WORKSPACE}\\build\\Release"
                    guess-the-number.exe
                """
            }
        }
    }
}