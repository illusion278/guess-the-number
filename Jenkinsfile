pipeline {
    agent any

    environment {
        CMAKE = 'C:\\Program Files\\CMake\\bin\\cmake.exe'
        GENERATOR = 'Visual Studio 17 2022'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout([
                    $class: 'GitSCM',
                    branches: [[name: '*/main']],
                    extensions: [[
                        $class: 'RelativeTargetDirectory',
                        relativeTargetDir: 'src'
                    ]],
                    userRemoteConfigs: [[url: 'https://github.com/illusion278/guess-the-number.git']]
                ])
            }
        }

        stage('Build') {
            steps {
                bat """
                    cd src
                    if not exist build mkdir build
                    cd build
                    "${CMAKE}" -G "${GENERATOR}" ..
                    "${CMAKE}" --build . --config Release
                """
            }
        }

        stage('Test') {
            steps {
                bat """
                    cd src\\build\\Release
                    guess-the-number.exe
                """
            }
        }
    }
}