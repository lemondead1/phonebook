#include <string>

class Date {
private:
    unsigned int day;
    unsigned int month;
    long year;

public:
    Date();

    Date(unsigned int day, unsigned int month, long year);

    int compare(Date other) const;

    static Date parse(const std::string &day, const std::string &month, const std::string &year);

    friend std::istream &operator>>(std::istream &stream, Date &date);

    friend std::ostream &operator<<(std::ostream &stream, const Date &date);

    std::string toString() const;

    unsigned int getDistanceInYear(Date to) const;

    unsigned int getYearDay() const;

    bool check(const std::string &d, const std::string &m, const std::string &y) const;

    static Date current();

    static bool isValid(unsigned long day, unsigned long month, long long year);

    static bool isValid(const std::string &day, const std::string &month, const std::string &year);
};
