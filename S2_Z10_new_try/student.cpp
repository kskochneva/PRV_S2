#include "student.h"
#include <iostream>
#include <iomanip>

// Constructors
Student::Student() : Person(), recordBook() {}

Student::Student(const std::string& name) : Person(name), recordBook() {}

Student::Student(const std::string& name, const std::string& recordNumber)
    : Person(name), recordBook(recordNumber) {
}

Student::Student(const std::string& name, const std::string& recordNumber,
    const std::vector<double>& grades)
    : Person(name), recordBook(recordNumber, grades) {
}

// Copy constructor
Student::Student(const Student& other) : Person(other), recordBook(other.recordBook) {}

// Destructor
Student::~Student() {}

// Record book access
std::string Student::getRecordNumber() const { return recordBook.getRecordNumber(); }
double Student::getAverage() const { return recordBook.getAverage(); }  // УДАЛЕНО override
const std::vector<double>& Student::getGrades() const { return recordBook.getGrades(); }

void Student::setRecordNumber(const std::string& number) {
    recordBook.setRecordNumber(number);
}

bool Student::addGrade(double grade) { return recordBook.addGrade(grade); }
bool Student::addGrades(const std::vector<double>& grades) {
    return recordBook.addGrades(grades);
}
bool Student::removeLastGrade() { return recordBook.removeLastGrade(); }
void Student::clearGrades() { recordBook.clearGrades(); }

double Student::getHighestGrade() const { return recordBook.getHighestGrade(); }
double Student::getLowestGrade() const { return recordBook.getLowestGrade(); }
bool Student::hasGrades() const { return recordBook.hasGrades(); }

// Override methods
void Student::print() const {  // УДАЛЕНО override
    std::cout << "Student: " << name << " (Record: " << recordBook.getRecordNumber()
        << ", Avg: " << std::fixed << std::setprecision(2) << getAverage() << ")";
}

std::string Student::getType() const { return "Student"; }  // УДАЛЕНО override