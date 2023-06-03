#include <regex>

#include "Date.h"

bool isYearLeap(long year) {
    bool leapYear = year % 4 == 0;
    if (year % 100 == 0) {
        leapYear = false;
    }
    if (year % 400 == 0) {
        leapYear = true;
    }
    return leapYear;
}

unsigned int getDaysInMonth(unsigned int month, long year) {
    switch (month) {
        case 1:
        case 3:
        case 5:
        case 7:
        case 8:
        case 10:
        case 12:
            return 31;
        case 2:
            return isYearLeap(year) ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
            return 30;
        default:
            return 0;
    }
}

bool isNumber(const std::string& string, unsigned int maxLength) {
    static const std::regex numberPattern("^ *[0-9]+ *$");
    return string.length() <= maxLength && std::regex_match(string, numberPattern);
}

Date::Date() {
    day = 1;
    month = 1;
    year = 2020;
}

Date::Date(unsigned int day, unsigned int month, long year) {
    this->day = day;
    this->month = month;
    this->year = year;
}

int Date::compare(Date other) const {
    if (year > other.year) {
        return 1;
    } else if (year < other.year) {
        return -1;
    }
    if (month > other.month) {
        return 1;
    } else if (month < other.month) {
        return -1;
    }
    if (day > other.day) {
        return 1;
    } else if (day < other.day) {
        return -1;
    }
    return 0;
}

Date Date::parse(const std::string &day, const std::string &month, const std::string &year) {
    return {(unsigned int) std::stoi(day), (unsigned int) std::stoi(month), (unsigned int) std::stol(year)};
}

std::istream &operator>>(std::istream &stream, Date &date) {
    std::string dob, mob, yob;
    std::getline(stream, dob, ',');
    std::getline(stream, mob, ',');
    std::getline(stream, yob, ',');
    date = Date::parse(dob, mob, yob);
    return stream;
}

std::ostream &operator<<(std::ostream &stream, const Date &date) {
    stream << date.day << ',' << date.month << ',' << date.year;
    return stream;
}

std::string Date::toString() const {
    return std::to_string(day) + "-" + std::to_string(month) + "-" + std::to_string(year);
}

unsigned int Date::getDistanceInYear(Date to) const {
    if (to.month == 2 && to.day == 29 && !isYearLeap(year)) {
        if (month == 3 && day == 1) {
            return 0;
        }
        to.day = 28;
    }
    to.year = year;
    int dayDiff = (int) to.getYearDay() - (int) getYearDay();
    if (dayDiff < 0) {
        dayDiff += isYearLeap(year) ? 366 : 365;
    }
    return dayDiff;
}

unsigned int Date::getYearDay() const {
    unsigned int result = day;
    for (int i = 1; i < month; i++) {
        result += getDaysInMonth(i, year);
    }
    return result;
}

bool Date::check(const std::string &d, const std::string &m, const std::string &y) const {
    return (d == "*" || isNumber(d, 2) && std::stoul(d) == this->day) &&
           (m == "*" || isNumber(m, 2) && std::stoul(m) == this->month) &&
           (y == "*" || isNumber(y, 19) && std::stoll(y) == this->year);
}

Date Date::current() {
    std::time_t now_time_t = std::time(nullptr);
    std::tm now = *std::localtime(&now_time_t);
    return {(unsigned int) now.tm_mday, (unsigned int) now.tm_mon + 1, now.tm_year + 1900};
}

bool Date::isValid(unsigned long day, unsigned long month, long long year) {
    return day > 0 && day <= getDaysInMonth(month, year);
}

bool Date::isValid(const std::string &day, const std::string &month, const std::string &year) {
    if (!(isNumber(day, 2) && isNumber(month, 2) && isNumber(year, 19))) {
        return false;
    }
    return isValid(std::stoul(day), std::stoul(month), std::stoll(year));
}
