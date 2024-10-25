#include <span>
#include <cassert>

void product(std::span<int> inputOutput, std::span<int> coefficients)
{

    assert(inputOutput.size() == coefficients.size());


    size_t i = 0;


    while (true)
    {

        if (i >= inputOutput.size())
        {
            break;
        }

        inputOutput[i] *= coefficients[i];

        ++i;
    }
}