#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    std::srand(std::time(0));
    int secretNumber = std::rand() % 100 + 1;
    int guess = 0;

    std::cout << "������ ����� �� 1 �� 100!\n";

    while (guess != secretNumber) {
        std::cout << "���� �������: ";
        std::cin >> guess;  // �����: ���������, ��� ���� ��������

        if (guess < secretNumber) {
            std::cout << "������� ����!\n";
        }
        else if (guess > secretNumber) {
            std::cout << "������� �����!\n";
        }
        else {
            std::cout << "���������! ��� " << secretNumber << "!\n";
        }
    }

    return 0;
}