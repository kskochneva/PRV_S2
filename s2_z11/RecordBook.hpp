#ifndef RECORDBOOK_HPP
#define RECORDBOOK_HPP

#include <string>
#include <vector>

class RecordBook {
private:
    std::string recordNumber;
    std::vector<double> grades;
    double average;

    void calculateAverage();

public:
    RecordBook();
    explicit RecordBook(const std::string& number);
    RecordBook(const std::string& number, const std::vector<double>& initialGrades);
    RecordBook(const RecordBook& other);
    ~RecordBook();

    std::string getRecordNumber() const;
    double getAverage() const;
    const std::vector<double>& getGrades() const;
    int getGradeCount() const;

    void setRecordNumber(const std::string& number);

    bool addGrade(double grade);
    bool addGrades(const std::vector<double>& newGrades);
    bool removeLastGrade();
    void clearGrades();

    double getHighestGrade() const;
    double getLowestGrade() const;
    bool hasGrades() const;

    void print() const;

    inline bool isValidRecord() const { return !recordNumber.empty(); }
};

#endif