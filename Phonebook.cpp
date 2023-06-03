#include <istream>
#include <ostream>


#include "Phonebook.h"

void Phonebook::insertNode(PhoneNode *previous, PhoneNode *next, const Person &person) {
    auto *newNode = new PhoneNode(previous, next, person);
    if (previous == nullptr) {
        first = newNode;
    } else {
        previous->next = newNode;
    }
    if (next == nullptr) {
        last = newNode;
    } else {
        next->previous = newNode;
    }
    size++;
}

void Phonebook::deleteNode(PhoneNode *node) {
    if (node->previous == nullptr) {
        first = node->next;
    } else {
        node->previous->next = node->next;
    }
    if (node->next == nullptr) {
        last = node->previous;
    } else {
        node->next->previous = node->previous;
    }
    delete node;
    size--;
}

PhoneNode *mergesort(PhoneNode *first) {
    if (first->next == nullptr) {
        return first;
    }

    auto *node = first;
    auto *mid = first;
    while (node->next != nullptr && node->next->next != nullptr) {
        node = node->next->next;
        mid = mid->next;
    }

    auto h2 = mergesort(mid->next);
    mid->next = nullptr;
    auto h1 = mergesort(first);

    PhoneNode *tail;

    if (h1->person < h2->person) {
        tail = h1;
        h1 = h1->next;
    } else {
        tail = h2;
        h2 = h2->next;
    }

    tail->previous = nullptr;

    auto head = tail;

    while (h1 != nullptr && h2 != nullptr) {
        if (h1->person < h2->person) {
            head->next = h1;
            h1->previous = head;
            head = h1;
            h1 = h1->next;
        } else {
            head->next = h2;
            h2->previous = head;
            head = h2;
            h2 = h2->next;
        }
    }

    while (h1 != nullptr) {
        head->next = h1;
        h1->previous = head;
        head = h1;
        h1 = h1->next;
    }

    while (h2 != nullptr) {
        head->next = h2;
        h2->previous = head;
        head = h2;
        h2 = h2->next;
    }

    return tail;
}

void Phonebook::add(const Person &person) {
    insertNode(last, nullptr, person);
}

std::vector<Person> Phonebook::remove(const std::string &name,
                                      const std::string &dayOfBirth,
                                      const std::string &monthOfBirth,
                                      const std::string &yearOfBirth,
                                      const std::string &phoneNumber) {
    PhoneNode *node = first;
    std::vector<Person> deleted;
    while (node != nullptr) {
        auto next = node->next;
        if (node->person.check(name, dayOfBirth, monthOfBirth, yearOfBirth, phoneNumber)) {
            deleted.push_back(node->person);
            deleteNode(node);
        }
        node = next;
    }
    return deleted;
}

void Phonebook::clear() {
    PhoneNode *node = first;
    while (node != nullptr) {
        auto next = node->next;
        deleteNode(node);
        node = next;
    }
}

void Phonebook::sort() {
    first = mergesort(first);
    last = first;
    while (last->next != nullptr) {
        last = last->next;
    }
}

void Phonebook::addToSorted(const Person &person) {
    PhoneNode *previous = nullptr;
    auto current = first;
    while (current != nullptr && person >= current->person) {
        previous = current;
        current = current->next;
    }
    insertNode(previous, current, person);
}

void operator>>(std::istream &file, Phonebook &phoneBook) {
    phoneBook.clear();
    while (file.peek() > 0) {
        Person person;
        file >> person;
        phoneBook.add(person);
    }
}

void operator<<(std::ostream &file, Phonebook &phoneBook) {
    PhoneNode *node = phoneBook.first;
    while (node != nullptr) {
        file << node->person << '\n';
        node = node->next;
    }
}

std::vector<Person *> Phonebook::find(const std::string &nameStr,
                                      const std::string &dayOfBirth,
                                      const std::string &monthOfBirth,
                                      const std::string &yearOfBirth,
                                      const std::string &phoneNumberStr) {
    std::vector<Person *> vector;
    PhoneNode *node = first;
    while (node != nullptr) {
        if (node->person.check(nameStr, dayOfBirth, monthOfBirth, yearOfBirth, phoneNumberStr)) {
            vector.push_back(&node->person);
        }
        node = node->next;
    }
    return vector;
}

std::pair<std::vector<Person *>, unsigned int> Phonebook::getNextBirthday() {
    PhoneNode *node = first;

    std::vector<Person *> best;
    unsigned int bestDays = 1000;

    Date now = Date::current();

    while (node != nullptr) {
        unsigned daysUntilBDay = node->person.daysBeforeBirthday(now);
        if (daysUntilBDay < bestDays) {
            bestDays = daysUntilBDay;
            best.clear();
        }
        if (daysUntilBDay <= bestDays) {
            best.push_back(&node->person);
        }
        node = node->next;
    }

    return {best, bestDays};
}
