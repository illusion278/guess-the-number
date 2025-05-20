// main.cpp
#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    setlocale(LC_ALL, "RUS");
    srand(time(0));
    int secret = rand() % 100 + 1;
    int guess = 0;

    std::cout << "������ ����� �� 1 �� 100!\n";

    while (guess != secret) {
        std::cout << "���� �������: ";
        std::cin >> guess;

        if (guess > secret) std::cout << "������� �����!\n";
        else if (guess < secret) std::cout << "������� ����!\n";
    }

    std::cout << "����������! �� ������ ����� " << secret << "!\n";
    return 0;
}