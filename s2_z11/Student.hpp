#ifndef STUDENT_HPP
#define STUDENT_HPP

#include "Person.hpp"
#include "RecordBook.hpp"
#include <vector>

class Student : public Person {
private:
    RecordBook recordBook;

public:
    Student();
    explicit Student(const std::string& name);
    Student(const std::string& name, const std::string& recordNumber);
    Student(const std::string& name, const std::string& recordNumber,
        const std::vector<double>& grades);
    Student(const Student& other);
    ~Student() override;

    std::string getRecordNumber() const;
    double getAverage() const override;
    const std::vector<double>& getGrades() const;

    void setRecordNumber(const std::string& number);

    bool addGrade(double grade);
    bool addGrades(const std::vector<double>& grades);
    bool removeLastGrade();
    void clearGrades();

    double getHighestGrade() const;
    double getLowestGrade() const;
    bool hasGrades() const;

    void print() const override;
    std::string getType() const override;

    inline bool hasRecordBook() const { return !recordBook.getRecordNumber().empty(); }
};

#endif