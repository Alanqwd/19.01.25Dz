#include <iostream>
#include <string>
#include <Windows.h>


// ������������ ���� (namespace) � �������� � C++, ����������� ������������ ������� ��������� ����.
// ����������� ������������ ���� ��� ���:  namespace NAME {  . . .  }
// ������ ������ namespace ��� ����� �������� ��������.
// ����������� ������������ ��� ��� ���������� ��������� ���.
// �� ����������� using namespace � ������������ ������.



// ������������ (enum) ������������ ��� ���� ������ ����������� ����� �����. �� ������������� ������������ �������� ��, ��� ��� �������� ����� �������� ��������. 
// ����������� ������������ ��� ���: enum class Day {Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday}
// �� ������ ����� ������� ������ �������� ��� ��������� ������������.
// ���� �� ���������� ��������, ������ ������� ����� ����� 0, � ��� ����������� ����� ��������� �� 1.
// ������������ ����� ������������, ��� ����� ������ ���� ������.
// �������� ������������ ����� ���� �������� ����� �����.


// ������������� enum � ���� 
// � ����������� enum ������-���:
// ���� � ������� ����������� �������� ����� ����, ��� ����� �������, ������ ������� ����� �������� � enum class Role
//  ������������� ������������ ������ ��� ����� ��������.������ ���� ����� ������������ ������������ ����� ����� ��� ������ ��� ����������� �����.
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
        std::cout << "���: " << name << "\n";
        std::cout << "�������: " << age << "\n";
        std::cout << "����: " << (role == Role::Resident ? "��������" : "��������") << "\n";
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
        std::cout << "����� ��������: " << apartmentNumber << "\n";
    }

    void registerComplaint(const std::string& complaint) const {
        std::cout << getName() << " ��������������� ������: " << complaint << "\n";
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
        std::cout << getName() << " ������������ ������ �� " << resident.getName() << ": " << complaint << "\n";
    }
};

// ������������� ������������ �������� Facade ( GoF )

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

    Resident resident("�������", 30, "12A");
    Manager manager("�����", 45);


    ComplaintSystemFacade facade(manager, resident);

    resident.displayInfo();
    manager.displayInfo();

    facade.registerAndHandleComplaint("���������� ������� ����");

    return 0;
}