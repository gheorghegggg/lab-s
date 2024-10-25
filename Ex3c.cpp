#include <span>
#include <cassert>

void product(std::span<int> inputOutput, std::span<int> coefficients)
{
    // Убедимся, что длины массивов совпадают
    assert(inputOutput.size() == coefficients.size());

    // Цикл for
    for (size_t i = 0; i < inputOutput.size(); ++i)
    {
        // Перемножаем элементы массивов
        inputOutput[i] *= coefficients[i];
    }
}