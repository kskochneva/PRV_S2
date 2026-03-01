#ifndef RECORD_BOOK_H
#define RECORD_BOOK_H

#include <string>
#include <vector>

class RecordBook {
private:
    std::string recordNumber;
    std::vector<double> grades;
    double average;

    void calculateAverage();

public:
    // Constructors
    RecordBook();
    explicit RecordBook(const std::string& number);
    RecordBook(const std::string& number, const std::vector<double>& initialGrades);

    // Copy constructor
    RecordBook(const RecordBook& other);

    // Destructor
    ~RecordBook();

    // Getters
    std::string getRecordNumber() const;
    double getAverage() const;
    const std::vector<double>& getGrades() const;

    // Setters
    void setRecordNumber(const std::string& number);

    // Grade management
    bool addGrade(double grade);
    bool addGrades(const std::vector<double>& newGrades);
    bool removeLastGrade();
    void clearGrades();

    // Statistics
    double getHighestGrade() const;
    double getLowestGrade() const;
    bool hasGrades() const;
    int getGradeCount() const;

    // Print
    void print() const;

    // Inline method in header
    inline bool isValidRecord() const { return !recordNumber.empty(); }
};

#endif // RECORD_BOOK_H