#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    int secretNumber = std::rand() % 100 + 1;
    int guess = 0;

    std::cout << "Угадай число от 1 до 100!\n";

    while (guess != secretNumber) {
        std::cout << "Твоя догадка: ";
        std::cin >> guess;  // Важно: проверьте, что ввод работает

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