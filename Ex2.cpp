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