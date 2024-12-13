## Практика

Реализуйте тип для `Vector2` с 2-мя `float` полями в отдельном модуле (`Vector2.h`, по надобности `Vector2.cpp`).
`Vector2` должен быть обычной структурой с публичными полями.

Перегрузите операторы (`v`, `w` это векторы, а `a` - `float`):
- `v * a`
- `a * v` (то же, что `v * a`)
- `v *= a`
- `v / a`
- `v /= a`
- `v + w`
- `v - w`
- `v += w` (c поддержкой синтаксиса `(v += w) += w`)
- `v -= w`
- Чтобы `std::cout << v` печатал компоненты `v` через запятую, в скобках
- `v[i]` для получения ссылки на компонент (i равен 0 или 1).

1. Перегрузите их как свободные `inline`, внутри `Vector2.h`;
2. В `Vector2.h` оставьте только объявления перегруженных операторов, определения задайте в `cpp` файле;
3. Используйте вместо свободных функций методы, объявленные внутри класса, определенные в `cpp` файле (там, где это возможно).
   Постарайтесь изменить прототипы и тела функций текстуальной заменой в вашем текстовом редакторе (search-and-replace).

В `main.cpp` протестируйте функционал через `assert`-ы.

Vector2.h

```cpp
#pragma once
#include <iostream>

struct Vector2 {
    float x;
    float y;

    // Методы для перегрузки операторов
    Vector2& operator*=(float scalar);
    Vector2& operator/=(float scalar);
    Vector2& operator+=(const Vector2& other);
    Vector2& operator-=(const Vector2& other);
    float& operator[](int index);
};

// Свободные функции для перегрузки операторов
Vector2 operator*(const Vector2& v, float scalar);
Vector2 operator*(float scalar, const Vector2& v);
Vector2 operator/(const Vector2& v, float scalar);
Vector2 operator+(const Vector2& v, const Vector2& w);
Vector2 operator-(const Vector2& v, const Vector2& w);
std::ostream& operator<<(std::ostream& os, const Vector2& v);
```

Vector2.cpp

```cpp
#include "Vector2.h"

Vector2& Vector2::operator*=(float scalar) {
    x *= scalar;
    y *= scalar;
    return *this;
}

Vector2& Vector2::operator/=(float scalar) {
    x /= scalar;
    y /= scalar;
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& other) {
    x += other.x;
    y += other.y;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& other) {
    x -= other.x;
    y -= other.y;
    return *this;
}

float& Vector2::operator[](int index) {
    if (index == 0) return x;
    if (index == 1) return y;
    throw std::out_of_range("Index out of range");
}

Vector2 operator*(const Vector2& v, float scalar) {
    return Vector2{v.x * scalar, v.y * scalar};
}

Vector2 operator*(float scalar, const Vector2& v) {
    return v * scalar;
}

Vector2 operator/(const Vector2& v, float scalar) {
    return Vector2{v.x / scalar, v.y / scalar};
}

Vector2 operator+(const Vector2& v, const Vector2& w) {
    return Vector2{v.x + w.x, v.y + w.y};
}

Vector2 operator-(const Vector2& v, const Vector2& w) {
    return Vector2{v.x - w.x, v.y - w.y};
}

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os;
}
```

main.cpp

```cpp
#include <cassert>
#include "Vector2.h"

int main() {
    Vector2 v1{1.0f, 2.0f};
    Vector2 v2{3.0f, 4.0f};
    float scalar = 2.0f;

    assert((v1 * scalar) == Vector2{2.0f, 4.0f});
    assert((scalar * v1) == Vector2{2.0f, 4.0f});
    v1 *= scalar;
    assert(v1 == Vector2{2.0f, 4.0f});
    assert((v1 / scalar) == Vector2{1.0f, 2.0f});
    v1 /= scalar;
    assert(v1 == Vector2{1.0f, 2.0f});
    assert((v1 + v2) == Vector2{4.0f, 6.0f});
    assert((v1 - v2) == Vector2{-2.0f, -2.0f});
    v1 += v2;
    assert(v1 == Vector2{4.0f, 6.0f});
    v1 -= v2;
    assert(v1 == Vector2{1.0f, 2.0f});

    std::cout << v1 << std::endl;
    assert(v1[0] == 1.0f);
    assert(v1[1] == 2.0f);

    std::cout << "All tests passed!" << std::endl;
    return 0;
}
```

## Ключевые идеи

-   Почему оператор `v * w` это плохая идея?

    Оператор умножения для двух векторов (v * w) в контексте двумерных векторов Vector2 может быть плохой идеей, потому что нет единого математического определения, как именно они должны умножаться.

-   Как вызвать тот или иной оператор как функцию?

Перегруженные операторы можно вызывать непосредственно как функции. Например, для оператора +:
```cpp
Vector2 v1{1.0f, 2.0f};
Vector2 v2{3.0f, 4.0f};
Vector2 result = operator+(v1, v2);
```

Аналогично для других операторов:
```cpp
Vector2 result = operator*(v1, 2.0f);
v1.operator+=(v2);
```

-   Что такое "fluent interface"? Как добавить его поддержку к операторам `<<`, `+=`, `-=` и т.п.?

  Fluent interface - это стиль написания API, который позволяет вызывать методы последовательно, в цепочке, как бы "в потоке". Это делается путем возврата ссылки на текущий объект (*this) из методов, чтобы можно было продолжить вызовы.

Пример fluent interface для операторов += и -=:
```cpp
struct Vector2 {
    float x;
    float y;

    Vector2& operator*=(float scalar) {
        x *= scalar;
        y *= scalar;
        return *this; // возвращаем ссылку на текущий объект
    }

    Vector2& operator/=(float scalar) {
        x /= scalar;
        y /= scalar;
        return *this; // возвращаем ссылку на текущий объект
    }

    Vector2& operator+=(const Vector2& other) {
        x += other.x;
        y += other.y;
        return *this; // возвращаем ссылку на текущий объект
    }

    Vector2& operator-=(const Vector2& other) {
        x -= other.x;
        y -= other.y;
        return *this; // возвращаем ссылку на текущий объект
    }
};

std::ostream& operator<<(std::ostream& os, const Vector2& v) {
    os << "(" << v.x << ", " << v.y << ")";
    return os; // возвращаем ссылку на поток для продолжения цепочки
}
```

Использование fluent interface позволяет писать более читаемый и консьержный код:
```cpp
Vector2 v1{1.0f, 2.0f};
Vector2 v2{3.0f, 4.0f};

v1 += v2 -= Vector2{1.0f, 1.0f} *= 2.0f;

std::cout << v1 << std::endl;
```
