#include <string>

#include "Date.h"

class Person {
private:
    std::string name;
    Date dateOfBirth;
    std::string phoneNumber;

public:
    Person();

    Person(const std::string &name, const Date &date, const std::string& phoneNumber);

    void read();

    friend std::istream &operator>>(std::istream &stream, Person &person);

    friend std::ostream &operator<<(std::ostream &stream, const Person &person);

    void write() const;

    unsigned int daysBeforeBirthday(Date now) const;

    unsigned int daysBeforeBirthday() const;

    int compare(const Person &other) const;

    bool operator<=(const Person &other) const;

    bool operator>=(const Person &other) const;

    bool operator<(const Person &other) const;

    bool operator>(const Person &other) const;

    bool check(const std::string &nameStr,
               const std::string &dayOfBirth, const std::string &monthOfBirth, const std::string &yearOfBirth,
               const std::string &phoneNumberStr) const;
};
