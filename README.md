## 1. Процедуральный динамический массив

Распишите код для структуры данных динамического массива:

```cpp
struct DynamicArray
{
    // ...
}
```

1. Создайте factory-функцию, которая возвращает массив изначальной максимальной длины,
   заданной параметром `capacity`.
   Создайте еще одну, которая выставляет какой-нибудь дефолтный `capacity` (например 4).

```cpp
void test1()
{
    DynamicArray arr = createDynamicArrayWithCapacity(10);
    assert(arr.capacity == 10);
}
```

2. Он должен давать доступ к размерности буфера (`capacity`),
   хранить текущее количество элементов (`length` / `count`).

```cpp
void test2()
{
    DynamicArray arr = createDynamicArray();
    assert(arr.length == 0);
    addElementToArray(&arr, 5);
    assert(arr.length == 1);
}
```

3. При добавлении элементов в массив, удваивайте длину, если массив полный.
   Имеется в виду, аллоцируйте буфер двойной длины, и перекопируйте все элементы.
   Добавляйте элемент в текущий конец массива.

```cpp
void test3()
{
    DynamicArray arr = createDynamicArrayWithCapacity(1);
    addElementToArray(&arr, 5);
    assert(arr.capacity == 1);
    addElementToArray(&arr, 10);
    assert(arr.capacity == 2);
    addElementToArray(&arr, 20);
    assert(arr.capacity == 4);
}
```

4. Создайте функцию для доступа к элементам массива по индексу.
   Выполняйте проверку длины в этой функции, используя `assert`.

```cpp
void test4()
{
    DynamicArray arr = createDynamicArray();
    addElementToArray(&arr, 5);
    int el = getElementAtIndex(&arr, 0);
    assert(el == 5);
}
```

5. Создайте функцию, которая возвращает текущий кусок массива как `std::span`.
   Пусть добавление элементов в массив инвалидирует этот взятый кусок, 
   то есть можете просто стирать эту память без лишних проверок, если надо.
   Инвалидация означает, что уже имеющиеся указатели на элементы из массива становятся недействительными
   (память на которую они указывают могла быть удалена).


```cpp
void test5()
{
    DynamicArray arr{};
    addElementToArray(&arr, 5);
    addElementToArray(&arr, 6);
    addElementToArray(&arr, 7);

    std::span<int> span = getCurrentSpan(&arr);

    assert(span.size() == 3);
    assert(span[0] == 5);
    assert(span[1] == 6);
    assert(span[2] == 7);
}
```

6. Создайте функцию, которая очищает динамическую память, выделенную функциями массива.
   Вызывайте эту функцию когда память массива больше не нужна (`free` / `destroy`).

7. Создайте функцию `main` в которой выполняются проверки всех этих фич 
   (в отдельных фнукциях, или в отдельных скоупах).
   Сделайте функции статическими, чтобы их невозможно было привязать в другом коде.
   По необходимости допишите своих тестов (как минимум 1).

8. Отделите код связанный со структурой в отдельный файл - сделайте динамический массив модулем.
   - *Объявления* функций для взаимодейтсвия со структурой и саму структуру положите в файл `dynamicArray.h`.
   - В `main.cpp` включайте файл `dynamicArray.h`.
   - В файл `dynamicArray.cpp` положите *определения* функций.
     > Можете положить очень короткие функции в `dynamicArray.h` как `inline`.
   - Если есть вспомогательные функции, который используете в коде массива, но не в `main`,
     сделайте их `static` и не добавляйте их в `dynamicArray.h`.
   - Пропишите команду которой компилируйте в `.bat` (или `.sh`) скрипт в папке с лабой.


dynamicArray.h

```cpp
#pragma once

#include <span>

struct DynamicArray {
    int* data;
    int length;
    int capacity;
};

DynamicArray createDynamicArray();
DynamicArray createDynamicArrayWithCapacity(int capacity);
void addElementToArray(DynamicArray* arr, int element);
int getElementAtIndex(const DynamicArray* arr, int index);
std::span<int> getCurrentSpan(const DynamicArray* arr);
void destroyArray(DynamicArray* arr);
```

dynamicArray.cpp

```cpp
#include "dynamicArray.h"
#include <cassert>
#include <algorithm>

static void resizeArray(DynamicArray* arr, int newCapacity) {
    int* newData = new int[newCapacity];
    std::copy(arr->data, arr->data + arr->length, newData);
    delete[] arr->data;
    arr->data = newData;
    arr->capacity = newCapacity;
}

DynamicArray createDynamicArray() {
    return createDynamicArrayWithCapacity(4);
}

DynamicArray createDynamicArrayWithCapacity(int capacity) {
    DynamicArray arr;
    arr.data = new int[capacity];
    arr.length = 0;
    arr.capacity = capacity;
    return arr;
}

void addElementToArray(DynamicArray* arr, int element) {
    if (arr->length == arr->capacity) {
        resizeArray(arr, arr->capacity * 2);
    }
    arr->data[arr->length++] = element;
}

int getElementAtIndex(const DynamicArray* arr, int index) {
    assert(index >= 0 && index < arr->length);
    return arr->data[index];
}

std::span<int> getCurrentSpan(const DynamicArray* arr) {
    return std::span<int>(arr->data, arr->length);
}

void destroyArray(DynamicArray* arr) {
    delete[] arr->data;
    arr->data = nullptr;
    arr->length = 0;
    arr->capacity = 0;
}
```

main.cpp

```cpp
#include <cassert>
#include "dynamicArray.h"

void test1() {
    DynamicArray arr = createDynamicArrayWithCapacity(10);
    assert(arr.capacity == 10);
    destroyArray(&arr);
}

void test2() {
    DynamicArray arr = createDynamicArray();
    assert(arr.length == 0);
    addElementToArray(&arr, 5);
    assert(arr.length == 1);
    destroyArray(&arr);
}

void test3() {
    DynamicArray arr = createDynamicArrayWithCapacity(1);
    addElementToArray(&arr, 5);
    assert(arr.capacity == 1);
    addElementToArray(&arr, 10);
    assert(arr.capacity == 2);
    addElementToArray(&arr, 20);
    assert(arr.capacity == 4);
    destroyArray(&arr);
}

void test4() {
    DynamicArray arr = createDynamicArray();
    addElementToArray(&arr, 5);
    int el = getElementAtIndex(&arr, 0);
    assert(el == 5);
    destroyArray(&arr);
}

void test5() {
    DynamicArray arr = createDynamicArray();
    addElementToArray(&arr, 5);
    addElementToArray(&arr, 6);
    addElementToArray(&arr, 7);

    std::span<int> span = getCurrentSpan(&arr);

    assert(span.size() == 3);
    assert(span[0] == 5);
    assert(span[1] == 6);
    assert(span[2] == 7);
    destroyArray(&arr);
}

int main() {
    test1();
    test2();
    test3();
    test4();
    test5();

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```
```sh
g++ -std=c++20 -Wall -Wextra -o dynamicArray main.cpp dynamicArray.cpp
pause
```
