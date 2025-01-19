#include <iostream>
#include <string>
#include <Windows.h>


// Пространства имен (namespace) — механизм в C++, позволяющий разграничить области видимости имен.
// Объявляется пространства имен вот так:  namespace NAME {  . . .  }
// Внутри одного namespace все имена доступны напрямую.
// Используйте пространства имён для исключения конфликта имён.
// Не используйте using namespace в заголовочных файлах.



// Перечисления (enum) представляют еще один способ определения своих типов. Их отличительной особенностью является то, что они содержат набор числовых констант. 
// Объявляется перечесление вот так: enum class Day {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday}
// Вы можете явным образом задать значения для элементов перечисления.
// Если не установить значение, первый элемент будет равен 0, а все последующие будут увеличены на 1.
// Перечисления можно использовать, как любые другие типы данных.
// Элементы перечисления могут быть сравнимы между собой.


// Использование enum в коде 
// Я использовал enum потому-что:
// Если в будущем потребуется добавить новые роли, это можно сделать, просто добавив новые значения в enum class Role
//  Использование перечислений делает код более понятным.Вместо того чтобы использовать произвольные целые числа или строки для обозначения ролей.
enum class Role {
    Resident,
    Manager
};

class Person {
protected:
    std::string name;
    int age;
    Role role;

public:
    Person(const std::string& name, int age, Role role)
        : name(name), age(age), role(role) {}

    void displayInfo() const {
        std::cout << "Имя: " << name << "\n";
        std::cout << "Возраст: " << age << "\n";
        std::cout << "Роль: " << (role == Role::Resident ? "Резидент" : "Менеджер") << "\n";
    }

    std::string getName() const {
        return name;
    }

    Role getRole() const {
        return role;
    }
};

class Resident : public Person {
private:
    std::string apartmentNumber;

public:
    Resident(const std::string& name, int age, const std::string& apartmentNumber)
        : Person(name, age, Role::Resident), apartmentNumber(apartmentNumber) {}

    void displayInfo() const {
        Person::displayInfo();
        std::cout << "Номер квартиры: " << apartmentNumber << "\n";
    }

    void registerComplaint(const std::string& complaint) const {
        std::cout << getName() << " зарегистрировал жалобу: " << complaint << "\n";
    }
};

class Manager : public Person {
public:
    Manager(const std::string& name, int age)
        : Person(name, age, Role::Manager) {}

    void displayInfo() const {
        Person::displayInfo();
    }

    void handleComplaint(const Resident& resident, const std::string& complaint) const {
        std::cout << getName() << " обрабатывает жалобу от " << resident.getName() << ": " << complaint << "\n";
    }
};

// Использование структурного паттерна Facade ( GoF )

class ComplaintSystemFacade {
private:
    Manager& manager;
    Resident& resident;

public:
    ComplaintSystemFacade(Manager& mgr, Resident& res)
        : manager(mgr), resident(res) {}

    void registerAndHandleComplaint(const std::string& complaint) {
        resident.registerComplaint(complaint);
        manager.handleComplaint(resident, complaint);
    }
};

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    Resident resident("Алексей", 30, "12A");
    Manager manager("Игорь", 45);


    ComplaintSystemFacade facade(manager, resident);

    resident.displayInfo();
    manager.displayInfo();

    facade.registerAndHandleComplaint("Отсутствие горячей воды");

    return 0;
}