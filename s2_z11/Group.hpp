#ifndef GROUP_HPP
#define GROUP_HPP

#include <string>
#include <vector>
#include <algorithm>
#include "Student.hpp"

class Group {
private:
    std::string groupName;
    std::vector<Student*> students;

public:
    Group();
    explicit Group(const std::string& name);
    ~Group();

    void addStudent(Student* student);
    void addStudent(Student& student);
    bool removeStudent(const std::string& studentName);
    void clear();

    double calculateGroupAverage() const;
    Student* findBestStudent() const;

    void sortStudentsByAverage();
    std::vector<Student*> filterByThreshold(double threshold) const;

    size_t getStudentCount() const;
    bool contains(const std::string& studentName) const;
    std::string getName() const;
    void setName(const std::string& newName);

    void print() const;

    inline bool isEmpty() const { return students.empty(); }
};

#endif