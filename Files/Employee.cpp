

#include <string>
#include <filesystem>
#include <fstream>
#include <iostream>

using namespace std;

class Employee {

private:
    int personNumber;
    string name;
    int hours;
    float hourlyWage;
    float grossWage;
public:
    Employee(int personNumber, const string &name, int hours, float hourlyWage) : personNumber(personNumber),
                                                                                  name(name), hours(hours),
                                                                                  hourlyWage(hourlyWage) {}

    int getPersonNumber() const {
        return personNumber;
    }

    void setPersonNumber(int personNumber) {
        Employee::personNumber = personNumber;
    }

    const string &getName() const {
        return name;
    }

    void setName(const string &name) {
        Employee::name = name;
    }

    int getHours() const {
        return hours;
    }

    void setHours(int hours) {
        Employee::hours = hours;
    }

    float getHourlyWage() const {
        return hourlyWage;
    }

    void setHourlyWage(float hourlyWage) {
        Employee::hourlyWage = hourlyWage;
    }

    Employee() {

    }

    void calculateGrossWage() {
        grossWage = hourlyWage * (float) hours;
    }

    void show() {
        cout << personNumber << "   " << name << "   " << hours << "   " << hourlyWage << "   " << grossWage << endl;
    }
};

int employee() {

    filesystem::path cwd =
            filesystem::current_path().parent_path() / "Files";

    ifstream inputFile(cwd / "employee.txt");

    int personNumber;
    string name;
    int hours;
    float hourlyWage;
    if (inputFile.good()) {
        getline(inputFile, name);

        Employee employees[4];

        int i = 0;

        while (inputFile >> personNumber >> name >> hours >> hourlyWage) {
            employees[i] = Employee(personNumber, name, hours, hourlyWage);
            employees[i].calculateGrossWage();
            employees[i++].show();
        }
    }
    return 0;
}