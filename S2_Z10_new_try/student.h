#ifndef STUDENT_H
#define STUDENT_H

#include "person.h"
#include "recordbook.h"
#include <vector>

// Forward declaration
class Group;

class Student : public Person {
private:
    RecordBook recordBook;

public:
    // Constructors
    Student();
    explicit Student(const std::string& name);
    Student(const std::string& name, const std::string& recordNumber);
    Student(const std::string& name, const std::string& recordNumber,
        const std::vector<double>& grades);

    // Copy constructor
    Student(const Student& other);

    // Destructor
    ~Student() override;

    // Record book access
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

    // Override methods
    void print() const override;
    std::string getType() const override;

    // Inline method in header
    inline bool hasRecordBook() const { return !recordBook.getRecordNumber().empty(); }
};

#endif // STUDENT_H