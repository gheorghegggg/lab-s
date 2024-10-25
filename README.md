## Рефакторинг

Зарефакторьте этот код, используя guard clause / early return.

```cpp
#include <iostream>

int main()
{
    int number = 10;

    if (number == 5)
    {
        std::cout << "The number is 5" << std::endl;
    }
    else
    {
        std::cout << "The number is not 5" << std::endl;

        if (number % 2 == 1)
        {
            std::cout << "The number is not divisible by 2" << std::endl;
        }
        else
        {
            std::cout << "The number is divisible by 2" << std::endl;

            if (number == 6)
            {
                std::cout << "The number is 6" << std::endl;
            }
        }
    }
}
```
```cpp
#include <iostream>

int main()
{
    int number = 10;

    if (number == 5)
    {
        std::cout << "The number is 5" << std::endl;
        return 0; // Early return, если число 5
    }

    std::cout << "The number is not 5" << std::endl;

    if (number % 2 == 1)
    {
        std::cout << "The number is not divisible by 2" << std::endl;
        return 0; // Early return
    }

    std::cout << "The number is divisible by 2" << std::endl;

    if (number == 6)
    {
        std::cout << "The number is 6" << std::endl;
        return 0;
    }

    return 0;
}
```

## Сложное логическое выражение

Дан базовый код:

```cpp
#include <iostream>

void main()
{
    int apples;
    int pears;
    int oranges;

    std::cout << "Apples:";
    std::cin >> apples;

    std::cout << "Pears:";
    std::cin >> pears;

    std::cout << "Oranges:";
    std::cin >> oranges;

    // ...
}
```

1. Если количество яблок больше 5, количество груш меньше 8
   и количество апельсинов в 2 раза больше чем количество яблок,
   напечатайте на экран "Hello".

2. Сделайте временную переменную с результатом выражения.
   Проверяйте ее в if.

3. Сделайте по временной переменной для каждого из подусловий.
   Вычисляйте общее условие, используя эти подусловия.

4. Объявите временные переменные подусловий в блоке,
   чтобы эти переменные не были видны за пределами блока.

5. Зарефакторьте 3 переменные с количеством фруктов в одну структуру (`FruitCounts`)
   с 3 полями, по одному для каждого типа фруктов.
   Переделайте код, чтобы везде использовалась эта структура.

```cpp
#include <iostream>

struct FruitCounts
{
    int apples;
    int pears;
    int oranges;
};

int main()
{
    FruitCounts fruitCounts;

    std::cout << "Apples: ";
    std::cin >> fruitCounts.apples;

    std::cout << "Pears: ";
    std::cin >> fruitCounts.pears;

    std::cout << "Oranges: ";
    std::cin >> fruitCounts.oranges;

    {
        bool moreThanFiveApples = fruitCounts.apples > 5;
        bool lessThanEightPears = fruitCounts.pears < 8;
        bool orangesTwiceApples = fruitCounts.oranges == 2 * fruitCounts.apples;

        bool overallCondition = moreThanFiveApples && lessThanEightPears && orangesTwiceApples;

        if (overallCondition)
        {
            std::cout << "Hello" << std::endl;
        }
    }

    return 0;
}
```