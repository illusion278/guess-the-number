pipeline {
    agent any

    environment {
        CMAKE = 'C:\\Program Files\\CMake\\bin\\cmake.exe'
        GENERATOR = 'Visual Studio 17 2022'
    }

    stages {
        stage('Verify Files') {
            steps {
                bat """
                    echo Проверка файлов:
                    dir
                    echo Содержимое CMakeLists.txt:
                    type CMakeLists.txt || echo Файл CMakeLists.txt не найден!
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    echo Текущий путь: %CD%
                    if not exist build mkdir build
                    cd build
                    "${CMAKE}" -G "${GENERATOR}" ..
                    if %errorlevel% neq 0 exit /b %errorlevel%
                    "${CMAKE}" --build . --config Release
                """
            }
        }

        stage('Test') {
            steps {
                bat """
                    cd build\\Release
                    guess-the-number.exe
                """
            }
        }
    }
}