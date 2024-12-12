#include <iostream>

// Объявление функции (только прототип)
int hello(int);

int main() {
    int result = hello(5); // Попытка вызвать функцию
    std::cout << "Result: " << result << std::endl;
    return 0;
}
