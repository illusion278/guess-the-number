/**
 * @file main.cpp
 * @brief Главный исполняемый файл игры "Угадай число"
 *
 * Содержит логику игры с генерацией случайного числа и обработкой пользовательского ввода.
 * @author Дмитрий Корейбо
 * @date 2025
 * @version 1.0
 */

#include <iostream>
#include <cstdlib>
#include <ctime>

 /**
  * @brief Точка входа в программу
  *
  * @details Реализует основную игровую логику:
  * 1. Генерация случайного числа в диапазоне 1-100
  * 2. Цикл обработки пользовательских попыток
  * 3. Вывод подсказок ("Слишком много"/"Слишком мало")
  *
  * @code{.cpp}
  * Пример работы:
  * Угадай число от 1 до 100!
  * Твоя догадка: 50
  * Слишком много!
  * Твоя догадка: 25
  * Слишком мало!
  * Твоя догадка: 37
  * Правильно! Это 37!
  * @endcode
  *
  * @return int 0 при успешном завершении программы
  */
int main() {
    std::srand(std::time(0));
    int secretNumber = std::rand() % 100 + 1;
    int guess = 0;

    std::cout << "Угадай число от 1 до 100!\n";

    while (guess != secretNumber) {
        std::cout << "Твоя догадка: ";
        std::cin >> guess;

        if (guess < secretNumber) {
            std::cout << "Слишком мало!\n";
        }
        else if (guess > secretNumber) {
            std::cout << "Слишком много!\n";
        }
        else {
            std::cout << "Правильно! Это " << secretNumber << "!\n";
        }
    }

    return 0;
}