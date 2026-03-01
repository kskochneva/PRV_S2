#include "group.h"
#include "student.h"
#include <iostream>
#include <iomanip>

Group::Group() : groupName("Unnamed Group") {}

Group::Group(const std::string& name) : groupName(name) {}

Group::~Group() {
    std::cout << "Group " << groupName << " destroyed\n";
}

void Group::addStudent(Student* student) {
    if (student) {
        students.push_back(student);
    }
}

void Group::addStudent(Student& student) {
    students.push_back(&student);
}

bool Group::removeStudent(const std::string& studentName) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->getName() == studentName) {
            students.erase(it);
            return true;
        }
    }
    return false;
}

bool Group::removeStudent(Student* student) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if (*it == student) {
            students.erase(it);
            return true;
        }
    }
    return false;
}

void Group::clear() {
    students.clear();
}

double Group::calculateGroupAverage() const {
    if (students.empty()) return 0.0;

    double sum = 0.0;
    for (const auto* student : students) {
        sum += student->getAverage();
    }
    return sum / students.size();
}

Student* Group::findBestStudent() const {
    if (students.empty()) return nullptr;

    Student* best = students[0];
    for (auto* student : students) {
        if (student->getAverage() > best->getAverage()) {
            best = student;
        }
    }
    return best;
}

size_t Group::getStudentCount() const { return students.size(); }

bool Group::contains(const std::string& studentName) const {
    for (const auto* student : students) {
        if (student->getName() == studentName) {
            return true;
        }
    }
    return false;
}

std::string Group::getName() const { return groupName; }
void Group::setName(const std::string& newName) { groupName = newName; }

void Group::print() const {
    std::cout << "\nGroup: " << groupName << " (" << students.size() << " students)\n";
    if (!students.empty()) {
        std::cout << "Group average: " << std::fixed << std::setprecision(2)
            << calculateGroupAverage() << "\n";
    }
}