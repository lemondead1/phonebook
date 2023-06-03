#include <regex>
#include <iostream>
#include <codecvt>

#include "Person.h"

std::string normalizeName(const std::string &name) {
    static const std::regex regex("(^ +| +$| (?= ))");
    return std::regex_replace(name, regex, "");
}

std::string normalizePhoneNumber(const std::string &phoneNumber) {
    static const std::regex pattern(R"([\(\)\-\s])");
    return std::regex_replace(phoneNumber, pattern, "");
}

Person::Person() {
    this->name = "John Doe";
    this->phoneNumber = "+78005553535";
}

Person::Person(const std::string &name, const Date &date, const std::string& phoneNumber) {
    this->name = normalizeName(name);
    this->dateOfBirth = date;
    this->phoneNumber = normalizePhoneNumber(phoneNumber);
}

void Person::read() {
    static const std::wregex namePattern(L"^ *([A-Za-zА-Яа-яЁё'-]+ *){1,3}$");

    std::cout << "Enter name > ";
    while (true) {
        std::getline(std::cin, name);
        std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
        std::wstring temp = converter.from_bytes(name);
        if (std::regex_match(temp, namePattern)) {
            break;
        } else {
            std::cout << "Incorrect name." << std::endl;
            std::cout << "Enter name again > ";
        }
    }
    name = normalizeName(name);

    std::string yearOfBirth;
    std::string monthOfBirth = "1";
    std::string dayOfBirth = "1";

    std::cout << "Enter year of birth > ";
    while (true) {
        std::getline(std::cin, yearOfBirth);
        if (Date::isValid(dayOfBirth, monthOfBirth, yearOfBirth)) {
            break;
        } else {
            std::cout << "Incorrect year of birth." << std::endl;
            std::cout << "Enter year of birth again > ";
        }
    }
    std::cout << "Enter month of birth > ";
    while (true) {
        std::getline(std::cin, monthOfBirth);
        if (Date::isValid(dayOfBirth, monthOfBirth, yearOfBirth)) {
            break;
        } else {
            std::cout << "Incorrect month of birth." << std::endl;
            std::cout << "Enter month of birth again > ";
        }
    }
    std::cout << "Enter day of birth > ";
    while (true) {
        std::getline(std::cin, dayOfBirth);
        if (Date::isValid(dayOfBirth, monthOfBirth, yearOfBirth)) {
            break;
        } else {
            std::cout << "Incorrect day of birth." << std::endl;
            std::cout << "Enter day of birth again > ";
        }
    }
    dateOfBirth = Date::parse(dayOfBirth, monthOfBirth, yearOfBirth);

    static const std::regex phonePattern(R"(^ *\+?( *[0-9] *){1,3}(( *[0-9] *){4,13}|((\(( *[0-9] *){3}\)|( *[0-9] *){3})(( *[0-9] *){1,10}|( *[0-9] *){3}-( *[0-9] *){2}-( *[0-9] *){2}))|((\(( *[0-9] *){4}\)|( *[0-9] *){4})(( *[0-9] *){1,9}|( *[0-9] *){2}-( *[0-9] *){2}-( *[0-9] *){2}))) *$)");

    std::cout << "Enter phone number > ";
    while (true) {
        std::getline(std::cin, phoneNumber);
        if (std::regex_match(phoneNumber, phonePattern)) {
            break;
        } else {
            std::cout << "Incorrect phone number." << std::endl;
            std::cout << "Enter phone number again > ";
        }
    }
    phoneNumber = normalizePhoneNumber(phoneNumber);
}

std::istream &operator>>(std::istream &stream, Person &person) {
    std::string line;
    std::getline(stream, line);

    std::stringstream lineStream(line);

    std::string n;
    std::getline(lineStream, n, ',');

    Date date;
    lineStream >> date;

    std::string number;
    std::getline(lineStream, number, ',');

    person = Person(n, date, number);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Person &person) {
    stream << person.name << ',';
    stream << person.dateOfBirth << ',';
    stream << person.phoneNumber;
    return stream;
}

void Person::write() const {
    std::cout << "name: " << name << ", ";
    std::cout << "date of birth: " << dateOfBirth.toString() << ", ";
    std::cout << "phone number: " << phoneNumber;
}

unsigned int Person::daysBeforeBirthday(Date now) const {
    return now.getDistanceInYear(dateOfBirth);
}

unsigned int Person::daysBeforeBirthday() const {
    return daysBeforeBirthday(Date::current());
}

int Person::compare(const Person &other) const {
    int i = name.compare(other.name);
    if (i > 0) {
        return 1;
    } else if (i < 0) {
        return -1;
    }
    return dateOfBirth.compare(other.dateOfBirth);
}

bool Person::operator<=(const Person &other) const {
    return compare(other) <= 0;
}

bool Person::operator>=(const Person &other) const {
    return compare(other) >= 0;
}

bool Person::operator<(const Person &other) const {
    return compare(other) < 0;
}

bool Person::operator>(const Person &other) const {
    return compare(other) > 0;
}

bool Person::check(const std::string &nameStr,
                   const std::string &dayOfBirth, const std::string &monthOfBirth, const std::string &yearOfBirth,
                   const std::string &phoneNumberStr) const {
    return (nameStr == "*" || this->name == normalizeName(nameStr)) &&
           this->dateOfBirth.check(dayOfBirth, monthOfBirth, yearOfBirth) &&
           (phoneNumberStr == "*" || this->phoneNumber == normalizePhoneNumber(phoneNumberStr));
}
