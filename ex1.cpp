#include <iostream>

int main() {
    int i = 69;
    int number = 72;
    i = i + number;  // i теперь равно 69 + 72 = 141
    int arr[3] = {0, 0, 0};
    int* iPointer = &i;
    number = *iPointer;  // number теперь равно 141 (значение i)
    *iPointer = 15;  // i теперь равно 15
    iPointer = &arr[0];
    iPointer += 2;  // iPointer теперь указывает на третий элемент массива
    arr[0] = 5;     // первый элемент массива теперь равен 5
    *iPointer = 6;  // третий элемент массива теперь равен 6

    // Вывод значений для проверки
    std::cout << "i: " << i << std::endl;
    std::cout << "number: " << number << std::endl;
    std::cout << "Array elements: " << arr[0] << ", " << arr[1] << ", " << arr[2] << std::endl;

    return 0;
}
