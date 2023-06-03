#include <iostream>
#include <regex>
#include <fstream>

#include "Phonebook.h"

void readConditions(std::string &name, std::string &dob, std::string &mob, std::string &yob, std::string &phone) {
    std::cout << "Enter name > ";
    std::getline(std::cin, name);

    std::cout << "Enter year of birth > ";
    while (true) {
        std::getline(std::cin, yob);
        if (yob == "*" || Date::isValid("1", "1", yob)) {
            break;
        } else {
            std::cout << "Incorrect year of birth." << std::endl;
            std::cout << "Enter year of birth again > ";
        }
    }
    std::cout << "Enter month of birth > ";
    while (true) {
        std::getline(std::cin, mob);
        if (mob == "*" || Date::isValid("1", mob, yob == "*" ? "2020" : yob)) {
            break;
        } else {
            std::cout << "Incorrect month of birth." << std::endl;
            std::cout << "Enter month of birth again > ";
        }
    }
    std::cout << "Enter day of birth > ";
    while (true) {
        std::getline(std::cin, dob);
        if (yob == "*" || Date::isValid(dob, mob == "*" ? "1" : mob, yob == "*" ? "2020" : yob)) {
            break;
        } else {
            std::cout << "Incorrect day of birth." << std::endl;
            std::cout << "Enter day of birth again > ";
        }
    }

    std::cout << "Enter phone number > ";
    std::getline(std::cin, phone);
}

void printEntries(const std::vector<Person *> &people) {
    for (Person *person: people) {
        std::cout << "    ";
        person->write();
        std::cout << std::endl;
    }
}

int main() {
    Phonebook phoneBook;
    bool sorted = false;

    while (true) {
        std::cout << "> ";
        std::string nextCommand;
        std::getline(std::cin, nextCommand);

        std::stringstream stream(nextCommand);

        std::string commandName;
        std::getline(stream, commandName, ' ');

        if (commandName == "help") {
            std::cout << "Available commands: " << std::endl;
            std::cout << "    help            print this list" << std::endl;
            std::cout << "    clear           clear phonebook" << std::endl;
            std::cout << "    load <filename> load phonebook from file" << std::endl;
            std::cout << "    save <filename> save phonebook to file" << std::endl;
            std::cout << "    add             add entry to phonebook" << std::endl;
            std::cout << "    sort            sort phonebook" << std::endl;
            std::cout << "    find            find entries by condition" << std::endl;
            std::cout << "    delete          delete entries that match condition" << std::endl;
            std::cout << "    birthday        find entries by condition" << std::endl;
            std::cout << "    exit            exit the program" << std::endl;
        } else if (commandName == "clear") {
            phoneBook.clear();
            sorted = false;
            std::cout << "Phonebook cleared." << std::endl;
        } else if (commandName == "load") {
            std::string filename;
            std::getline(stream, filename);
            std::ifstream file(filename);
            if (file.is_open()) {
                file >> phoneBook;
                file.close();
                sorted = false;
                std::cout << "Loaded phonebook from " << filename << "." << std::endl;
            } else {
                std::cout << "File " << filename << " cannot be read." << std::endl;
            }
        } else if (commandName == "save") {
            std::string filename;
            std::getline(stream, filename);
            std::ofstream file(filename);
            if (file.is_open()) {
                file << phoneBook;
                file.close();
                std::cout << "Saved phonebook to " << filename << "." << std::endl;
            } else {
                std::cout << "File " << filename << " cannot be written to.";
            }
        } else if (commandName == "add") {
            Person person;
            person.read();
            if (sorted) {
                phoneBook.addToSorted(person);
            } else {
                phoneBook.add(person);
            }
            std::cout << "Added: " << std::endl << "    ";
            person.write();
            std::cout << std::endl;
        } else if (commandName == "sort") {
            phoneBook.sort();
            sorted = true;
            std::cout << "Phonebook sorted." << std::endl;
        } else if (commandName == "birthday") {
            std::pair<std::vector<Person *>, unsigned int> people = phoneBook.getNextBirthday();
            if (people.first.empty()) {
                std::cout << "Phonebook is empty." << std::endl;
            } else {
                std::cout << "Days until next birthday: " << people.second << std::endl;
                std::cout << "Entries: " << std::endl;
                printEntries(people.first);
            }
        } else if (commandName == "find") {
            std::string name, dob, mob, yob, phone;
            readConditions(name, dob, mob, yob, phone);
            std::vector<Person *> people = phoneBook.find(name, dob, mob, yob, phone);
            if (people.empty()) {
                std::cout << "No entries in the phonebook satisfy these conditions." << std::endl;
            } else {
                std::cout << "Entries found: " << std::endl;
                printEntries(people);
            }
        } else if (commandName == "delete") {
            std::string name, dob, mob, yob, phone;
            readConditions(name, dob, mob, yob, phone);
            std::vector<Person> people = phoneBook.remove(name, dob, mob, yob, phone);
            if (people.empty()) {
                std::cout << "No entries in phonebook satisfy these conditions.";
            } else {
                std::cout << "Entries deleted: " << std::endl;
                for (const Person &person: people) {
                    std::cout << "    ";
                    person.write();
                    std::cout << std::endl;
                }
            }
        } else if (commandName == "exit") {
            break;
        } else {
            std::cout << "Unrecognized command " << commandName << "."
                      << " Enter 'help' to get a list of available commands." << std::endl;
        }
    }

    return 0;
}
