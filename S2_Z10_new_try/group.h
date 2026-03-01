#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>

// Forward declaration
class Student;

class Group {
private:
    std::string groupName;
    std::vector<Student*> students;  // Aggregation

public:
    // Constructors
    Group();
    explicit Group(const std::string& name);

    // Destructor (doesn't delete students)
    ~Group();

    // Group management
    void addStudent(Student* student);
    void addStudent(Student& student);
    bool removeStudent(const std::string& studentName);
    bool removeStudent(Student* student);
    void clear();

    // Calculations
    double calculateGroupAverage() const;
    Student* findBestStudent() const;

    // Queries
    size_t getStudentCount() const;
    bool contains(const std::string& studentName) const;
    std::string getName() const;
    void setName(const std::string& newName);

    // Print
    void print() const;

    // Inline method in header
    inline bool isEmpty() const { return students.empty(); }
};

#endif // GROUP_H