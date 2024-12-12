#include <string_view>
#include <cassert>

// Функция для нахождения второго "слова" между пробелами
std::string_view secondWord(std::string_view str) {
    // Найти первый пробел
    size_t firstSpace = str.find(' ');
    if (firstSpace == std::string_view::npos) {
        return ""; // Если пробелов нет, вернуть пустую строку
    }

    // Найти начало второго слова (первый непустой символ после первого пробела)
    size_t start = str.find_first_not_of(' ', firstSpace + 1);
    if (start == std::string_view::npos) {
        return ""; // Если не нашли, вернуть пустую строку
    }

    // Найти следующий пробел после начала второго слова
    size_t end = str.find(' ', start);
    if (end == std::string_view::npos) {
        return str.substr(start); // Если пробелов больше нет, вернуть остаток строки
    }

    return str.substr(start, end - start); // Вернуть второй кусок
}

// Тесты
void runTests() {
    // Тесты с двумя словами
    assert(secondWord("Hello world") == "world");
    assert(secondWord("Hello my dear") == "my");

    // Тест: пустая строка
    assert(secondWord("") == "");

    // Тест: строка из одного пробела
    assert(secondWord(" ") == "");

    // Тест: одно слово с пробелами вокруг
    assert(secondWord(" a ") == "a");

    // Тест: одно слово без второго слова
    assert(secondWord("a  ") == "");

    // Тест: пробелы между словами
    assert(secondWord("a  b") == "");

    // Тест: строка с лишними пробелами между словами
    assert(secondWord("hello     world    dear") == "");

    // Тест: строка без второго слова
    assert(secondWord("a") == "");

    // Тест: начало с пробелов, потом слово
    assert(secondWord("   first second") == "second");
}

int main() {
    runTests();
    return 0;
}
