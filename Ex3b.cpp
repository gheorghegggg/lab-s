#include <span>
#include <cassert>

void product(std::span<int> inputOutput, std::span<int> coefficients)
{
    // Убедимся, что длины массивов совпадают
    assert(inputOutput.size() == coefficients.size());

    // Индекс для итерации
    size_t i = 0;

    // Цикл с условием
    while (i < inputOutput.size())
    {
        // Перемножаем элементы массивов
        inputOutput[i] *= coefficients[i];

        // Увеличиваем индекс
        ++i;
    }
}
