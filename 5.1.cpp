#include <string_view>
#include <cassert>

// Функция для подсчёта символов '1'
size_t countOnes(std::string_view str) {
    size_t count = 0;
    for (char ch : str) {
        if (ch == '1') {
            ++count;
        }
    }
    return count;
}

// Тесты
void runTests() {
    // Тест: несколько единиц
    assert(countOnes("001100") == 2);

    // Тест: ни одной единицы
    assert(countOnes("0000") == 0);

    // Тест: все единицы
    assert(countOnes("1111") == 4);

    // Тест: пустая строка
    assert(countOnes("") == 0);

    // Тест: единицы в начале, середине и конце
    assert(countOnes("1010101") == 4);

    // Тест: строка без единиц, но с другими символами
    assert(countOnes("abcde") == 0);
}

int main() {
    runTests();
    return 0;
}
