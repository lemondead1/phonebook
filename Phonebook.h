#include <vector>

#include "Person.h"

struct PhoneNode {
    PhoneNode *previous;
    PhoneNode *next;
    Person person;

    PhoneNode(PhoneNode *previous, PhoneNode *next, const Person &person) {
        this->previous = previous;
        this->next = next;
        this->person = person;
    }
};

class Phonebook {
private:
    PhoneNode *first = nullptr;
    PhoneNode *last = nullptr;
    unsigned long size = 0;

    void insertNode(PhoneNode *previous, PhoneNode *next, const Person &person);

    void deleteNode(PhoneNode *node);

public:
    void add(const Person &person);

    void clear();

    void sort();

    void addToSorted(const Person &person);

    std::vector<Person> remove(const std::string &name,
                               const std::string &dayOfBirth,
                               const std::string &monthOfBirth,
                               const std::string &yearOfBirth,
                               const std::string &phoneNumber);

    std::vector<Person *> find(const std::string &nameStr,
                               const std::string &dayOfBirth,
                               const std::string &monthOfBirth,
                               const std::string &yearOfBirth,
                               const std::string &phoneNumberStr);

    friend void operator>>(std::istream &file, Phonebook &phoneBook);

    friend void operator<<(std::ostream &file, Phonebook &phoneBook);

    std::pair<std::vector<Person *>, unsigned int> getNextBirthday();
};
