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
                    // Proverka nalichiya CMake
                    bat """
                        @echo off
                        echo Proverka CMake: ${CMAKE_PATH}
                        if exist ${CMAKE_PATH} (
                            echo [OK] CMake naiden
                        ) else (
                            echo [NO] CMake Ne naiden: ${CMAKE_PATH}
                            exit 1
                        )
                    """

                    // Proverka nalichiya Visual Studio
                    bat """
                        @echo off
                        echo Proverka Visual Studio: ${VS_PATH}
                        if exist ${VS_PATH} (
                            echo [OK] Visual Studio naiden 
                        ) else (
                            echo [NO] Visual Studio Ne naiden: ${VS_PATH}
                            exit 1
                        )
                    """

                    // Proverka nalichiya failov proekta
                    bat """
                        @echo off
                        if exist CMakeLists.txt (
                            echo [OK] naiden CMakeLists.txt
                        ) else (
                            echo [NO] CMakeLists.txt ne naiden!
                            exit 1
                        )

                        if exist main.cpp (
                            echo [OK] naiden main.cpp
                        ) else (
                            echo [NO] main.cpp ne naiden!
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
            echo "Dlya ispravleniya:"
            echo "1. Ubeditsy, chto ustanovleno:"
            echo "   - Visual Studio 2022 Professional с C++"
            echo "   - CMake 3.15+"
            echo "2. Proverit puti v environment{} v Jenkinsfile"
            echo "3. Zapusk Jenkins ot imeni admina"
            echo "4. Proverit nalichie CMakeLists.txt and main.cpp"
            echo "5. Ubeditsya, chto imya ispolnyaemogo faila sovpadaet s ukazannym v CMakeLists.txt"
        }
        
        success {
            echo "Sborka Uspeshno zaverchena!"
            echo "Ispolnyemue fail: build/Release/guess-the-number.exe"
        }
    }
}
