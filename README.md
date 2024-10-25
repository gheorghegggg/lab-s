Какие тут типы, и какие тут объекты? перечислите все.

```cpp
struct Leg
{
    int length;
};

struct Arm
{
    int power;
};

struct Person
{
    std::array<Leg, 2> legs;
    Arm arms[2];
};

int main()
{
    Person person;
}
```
Типы:
int
Leg
Arm
std::array<Leg, 2>
Arm[2]
Person
Объекты:
Person person
legs
person.legs[0]
person.legs[1]
arms
person.arms[0]
person.arms[1]
Иерархия объектов:
Person person состоит из:
Leg legs[2] (массив из двух объектов Leg):
каждый объект Leg содержит поле int length.
Arm arms[2] (массив из двух объектов Arm):
каждый объект Arm содержит поле int power.
Итак, все типы:

Примитивный тип: int
Пользовательские типы: Leg, Arm, Person
Шаблонный тип: std::array<Leg, 2>
Все объекты:

person
person.legs[0], person.legs[1]
person.arms[0], person.arms[1]