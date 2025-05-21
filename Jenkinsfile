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
                    echo РџСЂРѕРІРµСЂРєР° С„Р°Р№Р»РѕРІ:
                    dir
                    echo РЎРѕРґРµСЂР¶РёРјРѕРµ CMakeLists.txt:
                    type CMakeLists.txt || echo Р¤Р°Р№Р» CMakeLists.txt РЅРµ РЅР°Р№РґРµРЅ!
                """
            }
        }

        stage('Build') {
            steps {
                bat """
                    echo РўРµРєСѓС‰РёР№ РїСѓС‚СЊ: %CD%
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