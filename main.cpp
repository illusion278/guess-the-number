// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess = 0;

    std::cout << "Угадай число от 1 до 100!\n";

    while (guess != secret) {
        std::cout << "Твоя догадка: ";
        std::cin >> guess;

        if (guess > secret) std::cout << "Слишком много!\n";
        else if (guess < secret) std::cout << "Слишком мало!\n";
    }

    std::cout << "Поздравляю! Ты угадал число " << secret << "!\n";
    return 0;
}