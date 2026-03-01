#include "Group.hpp"
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

void Group::sortStudentsByAverage() {
    std::sort(students.begin(), students.end(),
        [](const Student* a, const Student* b) {
            return a->getAverage() > b->getAverage();
        });
}

std::vector<Student*> Group::filterByThreshold(double threshold) const {
    std::vector<Student*> result;
    for (auto* student : students) {
        if (student->getAverage() >= threshold) {
            result.push_back(student);
        }
    }
    return result;
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
    std::cout << "\n=== Group: " << groupName << " ===\n";
    std::cout << "Students: " << students.size() << "\n";
    if (!students.empty()) {
        for (size_t i = 0; i < students.size(); ++i) {
            std::cout << i + 1 << ". ";
            students[i]->print();
            std::cout << "\n";
        }
        std::cout << "Group average: " << std::fixed << std::setprecision(2)
            << calculateGroupAverage() << "\n";
    }
}