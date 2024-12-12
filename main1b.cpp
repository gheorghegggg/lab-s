#include <iostream>

// Объявление и определение функции
int hello(int value) {
    return value * 2; // Простая логика: удваиваем входное значение
}

int main() {
    int result = hello(5); // Вызов функции
    std::cout << "Result: " << result << std::endl;
    return 0;
}
