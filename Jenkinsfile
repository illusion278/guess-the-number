pipeline {
    agent any

    environment {
        CMAKE_PATH = '"C:\\Program Files\\CMake\\bin\\cmake.exe"'
        VS_PATH = '"C:\\Program Files\\Microsoft Visual Studio\\2022\\Professional\\Common7\\Tools\\VsDevCmd.bat"'
    }

    stages {
        stage('Verify Tools') {
            steps {
                script {
                    // Проверка наличия CMake
                    bat """
                        @echo off
                        echo Проверка CMake: ${CMAKE_PATH}
                        if exist ${CMAKE_PATH} (
                            echo [OK] CMake найден
                        ) else (
                            echo [ОШИБКА] CMake не найден по пути: ${CMAKE_PATH}
                            exit 1
                        )
                    """

                    // Проверка наличия Visual Studio
                    bat """
                        @echo off
                        echo Проверка Visual Studio: ${VS_PATH}
                        if exist ${VS_PATH} (
                            echo [OK] Visual Studio найден
                        ) else (
                            echo [ОШИБКА] Visual Studio не найдена по пути: ${VS_PATH}
                            exit 1
                        )
                    """

                    // Проверка наличия файлов проекта
                    bat """
                        @echo off
                        if exist CMakeLists.txt (
                            echo [OK] Найден CMakeLists.txt
                        ) else (
                            echo [ОШИБКА] CMakeLists.txt не найден!
                            exit 1
                        )

                        if exist main.cpp (
                            echo [OK] Найден main.cpp
                        ) else (
                            echo [ОШИБКА] main.cpp не найден!
                            exit 1
                        )
                    """
                }
            }
        }

        stage('Generate Project') {
            steps {
                bat """
                    @echo off
                    call ${VS_PATH} > nul
                    mkdir build
                    cd build
                    ${CMAKE_PATH} -G "Visual Studio 17 2022" ..
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    @echo off
                    call ${VS_PATH} > nul
                    cd build
                    ${CMAKE_PATH} --build . --config Release
                """
            }
        }

        stage('Test') {
            steps {
                bat """
                    @echo off
                    cd build\\Release
                    guess-the-number.exe
                """
            }
        }

        stage('Archive') {
            steps {
                archiveArtifacts artifacts: 'build/Release/guess-the-number.exe', fingerprint: true
            }
        }
    }

    post {
        failure {
            echo "ДЛЯ ИСПРАВЛЕНИЯ:"
            echo "1. Убедитесь, что установлены:"
            echo "   - Visual Studio 2022 Professional с C++"
            echo "   - CMake 3.15+"
            echo "2. Проверьте пути в environment{} в Jenkinsfile"
            echo "3. Запустите Jenkins от имени администратора"
            echo "4. Проверьте наличие CMakeLists.txt и main.cpp"
            echo "5. Убедитесь, что имя исполняемого файла совпадает с указанным в CMakeLists.txt"
        }
        
        success {
            echo "Сборка успешно завершена!"
            echo "Исполняемый файл: build/Release/guess-the-number.exe"
        }
    }
}