#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <memory>

// ==================== BASE CLASS PERSON ====================

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
        std::cout << "Person: name = " << name;
    }

    virtual std::string getType() const { return "Person"; }
};

// ==================== RECORD BOOK CLASS ====================

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
    // Constructors
    RecordBook() : recordNumber("000000"), average(0.0) {
        std::cout << "RecordBook default constructor called\n";
    }

    explicit RecordBook(const std::string& number)
        : recordNumber(number), average(0.0) {
        std::cout << "RecordBook constructor with number called: " << number << "\n";
    }

    RecordBook(const std::string& number, const std::vector<double>& initialGrades)
        : recordNumber(number), grades(initialGrades) {
        calculateAverage();
        std::cout << "RecordBook constructor with number and grades called\n";
    }

    // Copy constructor
    RecordBook(const RecordBook& other)
        : recordNumber(other.recordNumber), grades(other.grades), average(other.average) {
        std::cout << "RecordBook copy constructor called\n";
    }

    // Destructor
    ~RecordBook() {
        std::cout << "RecordBook destructor called for " << recordNumber << "\n";
    }

    // Getters
    std::string getRecordNumber() const { return recordNumber; }
    double getAverage() const { return average; }
    const std::vector<double>& getGrades() const { return grades; }
    int getGradeCount() const { return grades.size(); }

    // Setters
    void setRecordNumber(const std::string& number) { recordNumber = number; }

    // Grade management
    bool addGrade(double grade) {
        if (grade < 0 || grade > 5) {
            std::cout << "Error! Grade must be between 0 and 5.\n";
            return false;
        }
        grades.push_back(grade);
        calculateAverage();
        return true;
    }

    bool addGrades(const std::vector<double>& newGrades) {
        bool allValid = true;
        for (double grade : newGrades) {
            if (grade >= 0 && grade <= 5) {
                grades.push_back(grade);
            }
            else {
                std::cout << "Skipping invalid grade: " << grade << "\n";
                allValid = false;
            }
        }
        calculateAverage();
        return allValid;
    }

    bool removeLastGrade() {
        if (grades.empty()) {
            return false;
        }
        grades.pop_back();
        calculateAverage();
        return true;
    }

    void clearGrades() {
        grades.clear();
        average = 0.0;
    }

    // Statistics
    double getHighestGrade() const {
        if (grades.empty()) return 0.0;
        return *std::max_element(grades.begin(), grades.end());
    }

    double getLowestGrade() const {
        if (grades.empty()) return 0.0;
        return *std::min_element(grades.begin(), grades.end());
    }

    bool hasGrades() const { return !grades.empty(); }

    // Print record book info
    void print() const {
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
        std::cout << " (" << grades.size() << " grades)";
    }
};

// ==================== STUDENT CLASS WITH COMPOSITION ====================

class Student : public Person {
private:
    RecordBook recordBook;  // Composition: Student owns RecordBook

public:
    // Default constructor
    Student() : Person(), recordBook() {
        std::cout << "Student default constructor called\n";
    }

    // Constructor with name only
    explicit Student(const std::string& name)
        : Person(name), recordBook() {
        std::cout << "Student constructor with name called for " << name << "\n";
    }

    // Constructor with name and record number
    Student(const std::string& name, const std::string& recordNumber)
        : Person(name), recordBook(recordNumber) {
        std::cout << "Student constructor with name and record number called for " << name << "\n";
    }

    // Constructor with name, record number, and initial grades
    Student(const std::string& name, const std::string& recordNumber,
        const std::vector<double>& initialGrades)
        : Person(name), recordBook(recordNumber, initialGrades) {
        std::cout << "Student full constructor called for " << name << "\n";
    }

    // Copy constructor
    Student(const Student& other)
        : Person(other), recordBook(other.recordBook) {
        std::cout << "Student copy constructor called for " << name << "\n";
    }

    // Destructor
    ~Student() override {
        std::cout << "Student destructor called for " << name << "\n";
    }

    // Record book access methods
    std::string getRecordNumber() const { return recordBook.getRecordNumber(); }
    double getAverage() const override { return recordBook.getAverage(); }

    void setRecordNumber(const std::string& number) {
        recordBook.setRecordNumber(number);
    }

    bool addGrade(double grade) { return recordBook.addGrade(grade); }
    bool addGrades(const std::vector<double>& grades) { return recordBook.addGrades(grades); }
    bool removeLastGrade() { return recordBook.removeLastGrade(); }
    void clearGrades() { recordBook.clearGrades(); }

    double getHighestGrade() const { return recordBook.getHighestGrade(); }
    double getLowestGrade() const { return recordBook.getLowestGrade(); }
    bool hasGrades() const { return recordBook.hasGrades(); }
    const std::vector<double>& getGrades() const { return recordBook.getGrades(); }

    // Override print method
    void print() const override {
        std::cout << "Student: " << name << "\n";
        std::cout << "  ";
        recordBook.print();
    }

    // Override getType
    std::string getType() const override { return "Student"; }
};

// ==================== TEACHER CLASS ====================

class Teacher : public Person {
private:
    std::string subject;
    int experienceYears;

public:
    Teacher() : Person(), subject("Unknown"), experienceYears(0) {}

    Teacher(const std::string& name, const std::string& subject)
        : Person(name), subject(subject), experienceYears(0) {
    }

    Teacher(const std::string& name, const std::string& subject, int experience)
        : Person(name), subject(subject), experienceYears(experience) {
    }

    std::string getSubject() const { return subject; }
    int getExperience() const { return experienceYears; }

    void setSubject(const std::string& newSubject) { subject = newSubject; }
    void setExperience(int years) { experienceYears = years; }

    void print() const override {
        std::cout << "Teacher: " << name << ", " << subject
            << ", " << experienceYears << " years";
    }

    std::string getType() const override { return "Teacher"; }

    void teach() const {
        std::cout << name << " is teaching " << subject << "\n";
    }
};

// ==================== FUNCTIONS ====================

void printAllPersons(const std::vector<Person*>& persons) {
    std::cout << "\n========== ALL PERSONS ==========\n";
    for (size_t i = 0; i < persons.size(); ++i) {
        std::cout << i + 1 << ". ";
        persons[i]->print();
        std::cout << "\n";
    }
}

void deleteAllPersons(std::vector<Person*>& persons) {
    for (auto* p : persons) {
        delete p;
    }
    persons.clear();
}

// ==================== MAIN FUNCTION ====================

int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 8: COMPOSITION - RECORD BOOK\n";
    std::cout << "========================================\n\n";

    // Demonstrate RecordBook independently
    std::cout << "--- RECORD BOOK DEMONSTRATION ---\n";
    RecordBook book1("12345");
    book1.addGrade(4.5);
    book1.addGrade(3.8);
    book1.addGrade(5.0);
    book1.print();
    std::cout << "\n\n";

    // Demonstrate composition - RecordBook is part of Student
    std::cout << "--- COMPOSITION DEMONSTRATION ---\n";

    // Student with default RecordBook
    Student s1("Alice");
    s1.addGrade(4.2);
    s1.addGrade(3.9);
    s1.print();
    std::cout << "\n\n";

    // Student with specific record number
    Student s2("Bob", "67890");
    s2.addGrades({ 4.8, 3.5, 4.0, 5.0 });
    s2.print();
    std::cout << "\n\n";

    // Student with full initialization
    Student s3("Charlie", "54321", { 4.5, 3.8, 4.2 });
    s3.print();
    std::cout << "\n\n";

    // Demonstrate that RecordBook lifecycle is tied to Student
    std::cout << "--- LIFECYCLE DEMONSTRATION ---\n";
    {
        Student temp("Temporary", "99999");
        temp.addGrade(4.0);
        std::cout << "  Inside block: ";
        temp.print();
        std::cout << "\n";
    } // temp destroyed here, RecordBook destroyed automatically
    std::cout << "  Outside block - temp is destroyed\n\n";

    // Demonstrate vector of Persons with composition
    std::cout << "--- POLYMORPHIC CONTAINER ---\n";
    std::vector<Person*> people;

    people.push_back(new Student("David", "11111", { 4.7, 4.2, 4.9 }));
    people.push_back(new Student("Eve", "22222"));
    people.push_back(new Teacher("Dr. Smith", "Mathematics", 10));

    // Add grades to Eve
    Student* eve = dynamic_cast<Student*>(people[1]);
    if (eve) {
        eve->addGrades({ 3.8, 4.1, 3.5 });
    }

    printAllPersons(people);

    // Demonstrate record book operations through Student
    std::cout << "\n--- RECORD BOOK OPERATIONS THROUGH STUDENT ---\n";
    Student* david = dynamic_cast<Student*>(people[0]);
    if (david) {
        std::cout << "David's record number: " << david->getRecordNumber() << "\n";
        std::cout << "David's grades: ";
        for (double g : david->getGrades()) {
            std::cout << g << " ";
        }
        std::cout << "\n";
        std::cout << "David's average: " << david->getAverage() << "\n";
        std::cout << "David's highest grade: " << david->getHighestGrade() << "\n";
        std::cout << "David's lowest grade: " << david->getLowestGrade() << "\n";

        david->addGrade(5.0);
        std::cout << "After adding 5.0, new average: " << david->getAverage() << "\n";

        david->removeLastGrade();
        std::cout << "After removing last grade, average: " << david->getAverage() << "\n";
    }

    // Clean up
    std::cout << "\n--- CLEANUP ---\n";
    deleteAllPersons(people);

    // Demonstrate that RecordBook cannot exist without Student in this design
    std::cout << "\n--- COMPOSITION VERIFICATION ---\n";
    std::cout << "RecordBook is created and destroyed with Student\n";
    std::cout << "Student owns RecordBook - this is composition\n";

    return 0;
}