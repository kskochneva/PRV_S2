#include "recordbook.h"
#include <iostream>
#include <algorithm>
#include <iomanip>

void RecordBook::calculateAverage() {
    if (grades.empty()) {
        average = 0.0;
        return;
    }
    double sum = 0.0;
    for (double grade : grades) {
        sum += grade;
    }
    average = sum / grades.size();
}

RecordBook::RecordBook() : recordNumber("000000"), average(0.0) {}

RecordBook::RecordBook(const std::string& number)
    : recordNumber(number), average(0.0) {
}

RecordBook::RecordBook(const std::string& number, const std::vector<double>& initialGrades)
    : recordNumber(number), grades(initialGrades) {
    calculateAverage();
}

RecordBook::RecordBook(const RecordBook& other)
    : recordNumber(other.recordNumber), grades(other.grades), average(other.average) {
}

RecordBook::~RecordBook() {}

std::string RecordBook::getRecordNumber() const { return recordNumber; }
double RecordBook::getAverage() const { return average; }
const std::vector<double>& RecordBook::getGrades() const { return grades; }

void RecordBook::setRecordNumber(const std::string& number) { recordNumber = number; }

bool RecordBook::addGrade(double grade) {
    if (grade < 0 || grade > 5) return false;
    grades.push_back(grade);
    calculateAverage();
    return true;
}

bool RecordBook::addGrades(const std::vector<double>& newGrades) {
    for (double grade : newGrades) {
        if (grade >= 0 && grade <= 5) {
            grades.push_back(grade);
        }
    }
    calculateAverage();
    return true;
}

bool RecordBook::removeLastGrade() {
    if (grades.empty()) return false;
    grades.pop_back();
    calculateAverage();
    return true;
}

void RecordBook::clearGrades() {
    grades.clear();
    average = 0.0;
}

double RecordBook::getHighestGrade() const {
    if (grades.empty()) return 0.0;
    auto it = std::max_element(grades.begin(), grades.end());
    return *it;
}

double RecordBook::getLowestGrade() const {
    if (grades.empty()) return 0.0;
    auto it = std::min_element(grades.begin(), grades.end());
    return *it;
}

bool RecordBook::hasGrades() const { return !grades.empty(); }

int RecordBook::getGradeCount() const {
    return static_cast<int>(grades.size());
}

void RecordBook::print() const {
    std::cout << "Record Book #" << recordNumber << "\n";
    std::cout << "  Grades: ";
    if (grades.empty()) {
        std::cout << "none";
    }
    else {
        for (double g : grades) {
            std::cout << g << " ";
        }
    }
    std::cout << "\n  Average: " << std::fixed << std::setprecision(2) << average;
}