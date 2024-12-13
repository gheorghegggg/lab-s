## Чему равно значение `Test::b` и почему?

1.  ```cpp
    enum Test
    {
        a = 1,
        b = 2,
    };
    ```
    Test::b равно 2, так как явно задано.

2.  ```cpp
    enum Test
    {
        a = 1,
        b,
    };
    ```
    Test::b равно 2, так как неявно присваивается следующее значение после a.

3.  ```cpp
    enum Test
    {
        a,
        b,
    };
    ```
    Test::b равно 1, так как значения по умолчанию начинаются с 0, и b получает следующее значение.

4.  ```cpp
    enum Test
    {
        a = -1,
        b,
    };
    ```
    Test::b равно 0, так как неявно присваивается следующее значение после a.

5.  ```cpp
    enum Test
    {
        a = (5 + 10 * 5) / 5,
        b,
    };
    ```
    Test::b равно 11, так как a вычисляется как 11, а b получает следующее значение.

6.  ```cpp
    enum Test
    {
        other = 5,
        a = other + 6,
        b,
    };
    ```
    Test::b равно 12, так как a равно other + 6 (то есть 11), а b получает следующее значение.

7.  Запишите ответ как целое число и как символ.

    ```cpp
    enum Test
    {
        a = '5',
        b = '7',
    };
    ```
    Test::b равно 55 (символ '7' имеет ASCII-код 55). В виде символа: '7'.

8.  Запишите ответ как целое число и как символ.

    ```cpp
    enum Test
    {
        a = '5',
        b,
    };
    ```
    Test::b равно 54 (так как '5' имеет ASCII-код 53, следующее значение будет 54). В виде символа: '6'.

9.  Запишите ответ как целое число и как символ.

    ```cpp
    enum Test
    {
        a = 'b',
        b,
    };
    ```
    Test::b равно 99 (так как 'b' имеет ASCII-код 98, следующее значение будет 99).

10.  Запишите ответ как целое число.

  ```cpp
    enum Test
    {
        a = 'a' + '1',
        b,
    };
  
  ```
    
  Test::b равно 147 (так как 'a' имеет ASCII-код 97, '1' имеет ASCII-код 49, и сложение дает 146, следующее значение будет 147).


## Почему?

Почему `enum class` лучше чем `enum`?
Перечислите.

Область видимости: Элементы enum class не выносятся в глобальную область видимости, предотвращая конфликты имен.

Явное приведение типов: Значения enum class неявно не приводятся к целочисленным типам, что делает код более безопасным.

Типобезопасность: enum class является строго типизированным, предотвращая неявные преобразования.

Инкапсуляция: Элементы enum class лучше инкапсулируются внутри класса или пространства имен, улучшая читаемость и поддержку кода.

## Обезвреживание бомбы.

На каждой бомбе 3 провода, все разных цветов: красный, желтый, зеленый.
Нужно написать программу, которая определяет, какой провод нужно перерезать, чтобы отключить таймер бомбы.

По характеристикам бомбы можно определить верный провод.
Характеристики следующие:
- Один из портретов: Ленин, Jeorge Washington, Гитлер;
- Один из цветов лампочки: синий, белый, красный;
- Один из 2 состояний тумблера (включен или выключен);
- Значение на циферблате, от 1 до 100.

Определить нужный провод можно по следующим правилам:
1. Если портрет Ленина, бомба не взорвется, ничего резать не надо;
2. С цветом лампочки связано значение. Синий - 11, белый - 15, красный - 35.
   Если значение на циферблате меньше этого значения, нужно резать красный провод.
3. Если портрет Гитлера, цвета лампочки смещаются на 1 в предыдущем пункте. 
   То есть, синий будет иметь значение белого (15), белый - красного (35), а красный - синего (11).
4. Если числовое значение цвета лампочки равно значению на циферблате, нужно резать зеленый провод.
5. Иначе, нужно резать желтый провод.
5. Если тумблер включен, то, какой провод нужно порезать, смещается обратно на 1.
   Вместо зеленого - желтый, вместо желтого - красный, вместо красного - зеленый.
6. Если значение циферблата делится на 4, 
   нужный провод смещается вперед на это значение.

Сделайте основную логику в виде функции,
принимающей параметрами характеристики бомбы,
и возвращающую нужное действие (какой провод перерезать, и если вовсе нужно перерезать).
В `main` напишите тесты через `assert`.
Можете сделать со вводом данных с клавиатуры, но не обязательно.

Рекомендации:
- Определите `enum class`-ы там, где есть фиксированный список возможных объектов. 
  Например, цвета лампочки, личность на портрете, цвет провода, положение переключателя.
- Если состояния всего 2, можно `enum` не делать, а моделировать ситуацию через `bool`.
- Если с каждым из членов `enum`-а связано какое-то значение, 
  используйте look-up table или `switch` для их связывания.
  Возможно также присвоить самому члену это значение, но делайте это только если
  код не зависит от того, что они на 1 следуют друг за другом по значению.
- Конвертируйте объект типа определенного `enum class` в `int` и обратно через `static_cast`.
- Сдвиг вперед или назад осуществите через модулярную арифметику.
- Используйте early return, когда решение находится ранее.


```cpp
#include <iostream>
#include <cassert>

enum class Portrait { Lenin, Washington, Hitler };
enum class BulbColor { Blue, White, Red };
enum class WireColor { Red, Yellow, Green };

int getBulbValue(BulbColor color, Portrait portrait) {
    switch (color) {
        case BulbColor::Blue: 
            return (portrait == Portrait::Hitler) ? 15 : 11;
        case BulbColor::White: 
            return (portrait == Portrait::Hitler) ? 35 : 15;
        case BulbColor::Red: 
            return (portrait == Portrait::Hitler) ? 11 : 35;
    }
    return -1; // Just a fallback, should not reach here
}

WireColor shiftWire(WireColor wire, int steps) {
    return static_cast<WireColor>((static_cast<int>(wire) + steps + 3) % 3);
}

WireColor determineWireToCut(Portrait portrait, BulbColor bulbColor, bool switchState, int dialValue) {
    if (portrait == Portrait::Lenin) {
        return WireColor::Red; // Ничего резать не надо, но возвращаем красный для простоты
    }

    int bulbValue = getBulbValue(bulbColor, portrait);

    WireColor wireToCut;
    if (dialValue < bulbValue) {
        wireToCut = WireColor::Red;
    } else if (dialValue == bulbValue) {
        wireToCut = WireColor::Green;
    } else {
        wireToCut = WireColor::Yellow;
    }

    if (switchState) {
        wireToCut = shiftWire(wireToCut, -1);
    }

    if (dialValue % 4 == 0) {
        wireToCut = shiftWire(wireToCut, 1);
    }

    return wireToCut;
}

int main() {
    assert(determineWireToCut(Portrait::Lenin, BulbColor::Blue, false, 10) == WireColor::Red);
    assert(determineWireToCut(Portrait::Washington, BulbColor::Blue, false, 10) == WireColor::Red);
    assert(determineWireToCut(Portrait::Washington, BulbColor::Blue, false, 11) == WireColor::Green);
    assert(determineWireToCut(Portrait::Washington, BulbColor::Blue, false, 12) == WireColor::Yellow);
    assert(determineWireToCut(Portrait::Hitler, BulbColor::Blue, false, 10) == WireColor::Red);
    assert(determineWireToCut(Portrait::Hitler, BulbColor::Blue, false, 15) == WireColor::Green);
    assert(determineWireToCut(Portrait::Hitler, BulbColor::Blue, true, 15) == WireColor::Yellow);
    assert(determineWireToCut(Portrait::Washington, BulbColor::Red, false, 35) == WireColor::Green);
    assert(determineWireToCut(Portrait::Washington, BulbColor::Red, true, 35) == WireColor::Yellow);
    assert(determineWireToCut(Portrait::Washington, BulbColor::Red, false, 36) == WireColor::Yellow);
    assert(determineWireToCut(Portrait::Washington, BulbColor::Red, true, 36) == WireColor::Red);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```
