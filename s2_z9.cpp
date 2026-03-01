#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <memory>

class Person {
protected:
    std::string name;

public:
    Person() : name("Unknown") {}

    explicit Person(const std::string& name) : name(name) {}

    virtual ~Person() {}

    std::string getName() const { return name; }
    void setName(const std::string& newName) { name = newName; }

    virtual void print() const {
        std::cout << "Person: " << name;
    }

    virtual double getAverage() const { return 0.0; }
    virtual std::string getType() const { return "Person"; }
};


class RecordBook {
private:
    std::string recordNumber;
    std::vector<double> grades;
    double average;

    void calculateAverage() {
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

public:
    RecordBook() : recordNumber("000000"), average(0.0) {}

    explicit RecordBook(const std::string& number)
        : recordNumber(number), average(0.0) {
    }

    RecordBook(const std::string& number, const std::vector<double>& initialGrades)
        : recordNumber(number), grades(initialGrades) {
        calculateAverage();
    }

    std::string getRecordNumber() const { return recordNumber; }
    double getAverage() const { return average; }
    const std::vector<double>& getGrades() const { return grades; }

    void setRecordNumber(const std::string& number) { recordNumber = number; }

    bool addGrade(double grade) {
        if (grade < 0 || grade > 5) return false;
        grades.push_back(grade);
        calculateAverage();
        return true;
    }

    bool addGrades(const std::vector<double>& newGrades) {
        for (double grade : newGrades) {
            if (grade >= 0 && grade <= 5) {
                grades.push_back(grade);
            }
        }
        calculateAverage();
        return true;
    }

    void print() const {
        std::cout << "Record Book #" << recordNumber << ", Avg: "
            << std::fixed << std::setprecision(2) << average;
    }
};


class Student : public Person {
private:
    RecordBook recordBook;

public:
    Student() : Person(), recordBook() {}

    explicit Student(const std::string& name) : Person(name), recordBook() {}

    Student(const std::string& name, const std::string& recordNumber)
        : Person(name), recordBook(recordNumber) {
    }

    Student(const std::string& name, const std::string& recordNumber,
        const std::vector<double>& grades)
        : Person(name), recordBook(recordNumber, grades) {
    }

    double getAverage() const override { return recordBook.getAverage(); }

    std::string getRecordNumber() const { return recordBook.getRecordNumber(); }
    const std::vector<double>& getGrades() const { return recordBook.getGrades(); }

    bool addGrade(double grade) { return recordBook.addGrade(grade); }
    bool addGrades(const std::vector<double>& grades) { return recordBook.addGrades(grades); }

    void print() const override {
        std::cout << "Student: " << name << " (Record: " << recordBook.getRecordNumber()
            << ", Avg: " << std::fixed << std::setprecision(2) << getAverage() << ")";
    }

    std::string getType() const override { return "Student"; }
};



class Teacher : public Person {
private:
    std::string subject;
    int experience;

public:
    Teacher() : Person(), subject("Unknown"), experience(0) {}

    Teacher(const std::string& name, const std::string& subject)
        : Person(name), subject(subject), experience(0) {
    }

    Teacher(const std::string& name, const std::string& subject, int experience)
        : Person(name), subject(subject), experience(experience) {
    }

    void print() const override {
        std::cout << "Teacher: " << name << ", " << subject
            << " (" << experience << " years)";
    }

    std::string getType() const override { return "Teacher"; }
};


class Group {
private:
    std::string groupName;
    std::vector<Student*> students;  

public:
   
    Group() : groupName("Unnamed Group") {}

    explicit Group(const std::string& name) : groupName(name) {}

   
    ~Group() {
        std::cout << "Group " << groupName << " destroyed, students still exist\n";
    }

   
    void addStudent(Student* student) {
        if (student) {
            students.push_back(student);
            std::cout << "Added " << student->getName() << " to group " << groupName << "\n";
        }
    }

    void addStudent(Student& student) {
        students.push_back(&student);
        std::cout << "Added " << student.getName() << " to group " << groupName << "\n";
    }

    
    bool removeStudent(const std::string& studentName) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if ((*it)->getName() == studentName) {
                std::cout << "Removed " << studentName << " from group " << groupName << "\n";
                students.erase(it);
                return true;
            }
        }
        std::cout << "Student " << studentName << " not found in group " << groupName << "\n";
        return false;
    }

    // Remove student by pointer
    bool removeStudent(Student* student) {
        for (auto it = students.begin(); it != students.end(); ++it) {
            if (*it == student) {
                std::cout << "Removed " << student->getName() << " from group " << groupName << "\n";
                students.erase(it);
                return true;
            }
        }
        return false;
    }

    // Clear all students from group (but don't delete them)
    void clear() {
        std::cout << "Cleared all students from group " << groupName << "\n";
        students.clear();
    }

    // Calculate group average
    double calculateGroupAverage() const {
        if (students.empty()) {
            return 0.0;
        }

        double sum = 0.0;
        int count = 0;

        for (const auto* student : students) {
            sum += student->getAverage();
            count++;
        }

        return sum / count;
    }

    // Find student with highest average
    Student* findBestStudent() const {
        if (students.empty()) return nullptr;

        Student* best = students[0];
        for (auto* student : students) {
            if (student->getAverage() > best->getAverage()) {
                best = student;
            }
        }
        return best;
    }

    // Get student count
    size_t getStudentCount() const { return students.size(); }

    // Check if student is in group
    bool contains(const std::string& studentName) const {
        for (const auto* student : students) {
            if (student->getName() == studentName) {
                return true;
            }
        }
        return false;
    }

    // Get group name
    std::string getName() const { return groupName; }
    void setName(const std::string& newName) { groupName = newName; }

    // Print group info
    void print() const {
        std::cout << "\n========== GROUP: " << groupName << " ==========\n";
        std::cout << "Students: " << students.size() << "\n";

        if (students.empty()) {
            std::cout << "  No students in group\n";
        }
        else {
            for (size_t i = 0; i < students.size(); ++i) {
                std::cout << "  " << i + 1 << ". ";
                students[i]->print();
                std::cout << "\n";
            }
            std::cout << "Group average: " << std::fixed << std::setprecision(2)
                << calculateGroupAverage() << "\n";
        }
    }
};

// ==================== MAIN FUNCTION ====================

int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 9: GROUP AGGREGATION\n";
    std::cout << "========================================\n\n";

    // Create students independently (they exist outside any group)
    std::cout << "--- CREATING STUDENTS ---\n";
    Student s1("Alice", "2024001", { 4.5, 3.8, 5.0, 4.2 });
    Student s2("Bob", "2024002", { 3.5, 4.0, 3.8, 4.5 });
    Student s3("Charlie", "2024003", { 2.5, 3.0, 2.8, 3.2 });
    Student s4("Diana", "2024004", { 4.8, 4.5, 4.9, 4.7 });
    Student s5("Eve", "2024005", { 3.0, 3.5, 4.0, 3.2 });

    // Create teachers (also independent)
    Teacher t1("Dr. Smith", "Mathematics", 10);
    Teacher t2("Prof. Johnson", "Physics", 15);

    std::cout << "\n--- DEMONSTRATING AGGREGATION ---\n";

    // Create groups
    Group mathGroup("Mathematics Group");
    Group physicsGroup("Physics Group");

    // Add students to groups (aggregation - same students can be in multiple groups)
    std::cout << "\nAdding students to Math Group:\n";
    mathGroup.addStudent(s1);
    mathGroup.addStudent(s2);
    mathGroup.addStudent(s3);

    std::cout << "\nAdding students to Physics Group:\n";
    physicsGroup.addStudent(s2);
    physicsGroup.addStudent(s4);
    physicsGroup.addStudent(s5);

    // Print groups
    mathGroup.print();
    physicsGroup.print();

    // Calculate group averages
    std::cout << "\n--- GROUP STATISTICS ---\n";
    std::cout << "Math Group average: " << std::fixed << std::setprecision(2)
        << mathGroup.calculateGroupAverage() << "\n";
    std::cout << "Physics Group average: " << physicsGroup.calculateGroupAverage() << "\n";

    // Find best students
    Student* bestMath = mathGroup.findBestStudent();
    Student* bestPhysics = physicsGroup.findBestStudent();

    if (bestMath) {
        std::cout << "Best in Math Group: " << bestMath->getName()
            << " (avg: " << bestMath->getAverage() << ")\n";
    }

    if (bestPhysics) {
        std::cout << "Best in Physics Group: " << bestPhysics->getName()
            << " (avg: " << bestPhysics->getAverage() << ")\n";
    }

    // Demonstrate that same student can be in multiple groups
    std::cout << "\n--- STUDENT IN MULTIPLE GROUPS ---\n";
    std::cout << "Bob is in Math Group? " << (mathGroup.contains("Bob") ? "Yes" : "No") << "\n";
    std::cout << "Bob is in Physics Group? " << (physicsGroup.contains("Bob") ? "Yes" : "No") << "\n";

    // Remove a student from a group
    std::cout << "\n--- REMOVING STUDENT ---\n";
    mathGroup.removeStudent("Charlie");
    mathGroup.print();

    // Demonstrate that student still exists after removal
    std::cout << "\n--- STUDENT STILL EXISTS AFTER REMOVAL ---\n";
    std::cout << "Charlie still exists: ";
    s3.print();
    std::cout << "\n";

    // Demonstrate that groups don't own students
    std::cout << "\n--- GROUP DESTRUCTION ---\n";
    {
        Group tempGroup("Temporary Group");
        tempGroup.addStudent(s1);
        tempGroup.addStudent(s2);
        std::cout << "Temp group created with 2 students\n";
    } // tempGroup destroyed here, but students still exist

    std::cout << "\nStudents still exist after temp group destroyed:\n";
    s1.print();
    std::cout << "\n";
    s2.print();
    std::cout << "\n";

    // Demonstrate that Teacher cannot be added to group (type safety)
    // mathGroup.addStudent(t1); // Error! Teacher is not a Student

    // Create vector of groups
    std::cout << "\n--- VECTOR OF GROUPS ---\n";
    std::vector<Group> groups;
    groups.push_back(mathGroup);
    groups.push_back(physicsGroup);

    for (const auto& group : groups) {
        group.print();
    }

    // Demonstrate clear method
    std::cout << "\n--- CLEARING GROUP ---\n";
    mathGroup.clear();
    mathGroup.print();

    return 0;
}