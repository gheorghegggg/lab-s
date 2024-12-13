## Пример

```cpp
// Файл HeapInt.h
#pragma once // 1
#include <cassert>

class HeapInt
{
private:
    int* heapValue; // 2

public:
    // 3
    inline HeapInt(int val) 
        // 4
        : heapValue(new int{ val })
    {
    }

    inline ~HeapInt()
    {
        // Заметка: delete проверяет на nullptr сам.
        delete heapValue; // 5
    }

    inline int& asRef()
    {
        assert(heapValue != nullptr); // 6
        return *heapValue;
    }

    HeapInt(const HeapInt& hello); // 7
    HeapInt(HeapInt&& hello);
    void operator=(const HeapInt& hello);
    void operator=(HeapInt&& hello);
};

// Файл main.cpp
#include "HeapInt.h"

void constructors()
{
    HeapInt a{5}; // 8
    HeapInt b{a}; // 9
    HeapInt c{std::move(a)}; // 10
    HeapInt d = b; // 11
    HeapInt e = std::move(b); // 12
    d = std::move(c); // 13
    d = e; // 14
}

// Файл HeapInt.cpp
#include "HeapInt.h"

// ... 15
```

Дан класс `HeapInt` выше, представляющий собой обертку для динамически выделенного инта.
В отличии от обычного `int*`, этот тип не позволяет `nullptr` как валидное значение.

Класс следует RAII, выделяя память в конструкторе, и удаляя ее в деструкторе.

1. Почему поле `heapValue` (2) приватное?

Приватные поля класса не могут быть изменены напрямую из-за пределов класса, что помогает инкапсулировать данные и защищать их от некорректного использования.
   

2. Что означает этот синтаксис (4)? Как его расписать в теле конструктора?

Это список инициализации члена. Он используется для инициализации полей класса перед выполнением тела конструктора. Пример инициализации в теле конструктора:

```cpp
HeapInt(int val)
{
    heapValue = new int{ val };
}
```
   

3. Как скомпилировать это с помощью GCC?
```cpp
g++ -o program main.cpp HeapInt.cpp
```
   

4. Зачем (1)? Какую ситуацию это предотвратит?

   #pragma once предотвращает множественное включение файла заголовка в компиляционную единицу, что устраняет ошибки повторного определения.
   

5. Почему (3) определена как `inline`?

   Определение inline позволяет размещать реализацию функции в заголовочном файле, уменьшая накладные расходы на вызов функции.

6. Как можно обойти ограничение, что конструктор или функция должны быть `inline`?

   Определите их в файле реализации (cpp-файл), а не в заголовке.


7. Зачем на (6) нужна проверка, если `int*` не может быть `nullptr`?

   Такая проверка повышает надежность кода, подтверждая, что память была успешно выделена.


8. Объясните, какой из конструкторов или перегруженных операторов вызовется для (8-14).
   Какие из них эквивалентны?
   
(8) HeapInt a{5}; - вызывает конструктор HeapInt(int val)

(9) HeapInt b{a}; - вызывает конструктор копирования HeapInt(const HeapInt& hello)

(10) HeapInt c{std::move(a)}; - вызывает конструктор перемещения HeapInt(HeapInt&& hello)

(11) HeapInt d = b; - вызывает конструктор копирования HeapInt(const HeapInt& hello)

(12) HeapInt e = std::move(b); - вызывает конструктор перемещения HeapInt(HeapInt&& hello)

(13) d = std::move(c); - вызывает оператор присваивания перемещения operator=(HeapInt&& hello)

(14) d = e; - вызывает оператор копирующего присваивания operator=(const HeapInt& hello)

9. Как запретить синтаксис на (11-12)?

   Сделайте конструкторы копирования и перемещения приватными или удалите их, используя = delete;.

10. Определите на (15) конструкторы и операторы на (7).

```cpp
HeapInt::HeapInt(const HeapInt& hello)
    : heapValue(new int{ *hello.heapValue })
{
}

HeapInt::HeapInt(HeapInt&& hello)
    : heapValue(hello.heapValue)
{
    hello.heapValue = nullptr;
}

void HeapInt::operator=(const HeapInt& hello)
{
    if (this != &hello)
    {
        delete heapValue;
        heapValue = new int{ *hello.heapValue };
    }
}

void HeapInt::operator=(HeapInt&& hello)
{
    if (this != &hello)
    {
        delete heapValue;
        heapValue = hello.heapValue;
        hello.heapValue = nullptr;
    }
}
```
    

11. В какой еще ситуации вызовется rvalue reference перегрузка конструктора или оператора присваивания?

Со временными объектами. То есть для значений типа ожидаемого объекта, которые не были сохранены в переменную, а переданы сразу функции.
    

12. Сколько раз вызовется деструктор для типа `HeapInt` после (14)?

  Деструктор вызовется 5 раз: для объектов a, b, c, d и e.

    

13. Объясните, какая по вашему мнению была мотивация того, что у этого типа не был определен дефолтный конструктор?

  Дефолтный конструктор не был определен, чтобы гарантировать, что heapValue всегда будет указывать на выделенную память и никогда не будет равен nullptr.

    

14. Объясните, почему считывать значение объекта после применения `std::move` это неправильная операция?

    После std::move объект находится в невалидном состоянии и любые операции с ним могут привести к неопределенному поведению.
    
15. Создайте функцию `void swap(HeapInt& a, HeapInt& b)`, которая меняет значения, 
    без выделения новой динамической памяти.

    ```cpp
    void swap(HeapInt& a, HeapInt& b)
    {
    std::swap(a.heapValue, b.heapValue);
    }
    ```


    
