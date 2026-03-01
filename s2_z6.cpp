#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>

class Student {
private:
    std::string name;
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
    // Default constructor
    Student() : name("Unknown"), average(0.0) {
        std::cout << "Default constructor called\n";
    }

    // Parameterized constructor with explicit
    explicit Student(const std::string& studentName)
        : name(studentName), average(0.0) {
        std::cout << "Parameterized constructor called for " << name << "\n";
    }

    // Parameterized constructor with name and initial grade
    Student(const std::string& studentName, double initialGrade)
        : name(studentName), average(0.0) {
        std::cout << "Constructor with grade called for " << name << "\n";
        addGrade(initialGrade);
    }

    // Copy constructor
    Student(const Student& other)
        : name(other.name), grades(other.grades), average(other.average) {
        std::cout << "Copy constructor called for " << name << "\n";
    }

    // Destructor
    ~Student() {
        std::cout << "Destructor called for " << name << "\n";
    }

    // Getters
    std::string getName() const { return name; }
    double getAverage() const { return average; }
    const std::vector<double>& getGrades() const { return grades; }

    // Setters
    void setName(const std::string& newName) { name = newName; }

    // Add a single grade
    void addGrade(double grade) {
        if (grade < 0 || grade > 5) {
            std::cout << "Error! Grade must be between 0 and 5.\n";
            return;
        }
        grades.push_back(grade);
        calculateAverage();
        std::cout << "Grade " << grade << " added to " << name << "\n";
    }

    // Add multiple grades
    void addGrades(const std::vector<double>& newGrades) {
        for (double grade : newGrades) {
            if (grade >= 0 && grade <= 5) {
                grades.push_back(grade);
            }
            else {
                std::cout << "Skipping invalid grade: " << grade << "\n";
            }
        }
        calculateAverage();
    }

    // Display student information
    void displayInfo() const {
        std::cout << "\n=== Student Information ===\n";
        std::cout << "Name: " << name << "\n";
        std::cout << "Grades: ";
        if (grades.empty()) {
            std::cout << "No grades yet";
        }
        else {
            for (double g : grades) {
                std::cout << g << " ";
            }
        }
        std::cout << "\n";
        std::cout << "Average: " << std::fixed << std::setprecision(2) << average << "\n";
        std::cout << "Grade count: " << grades.size() << "\n";
    }

    // Check if student has any grades
    bool hasGrades() const { return !grades.empty(); }

    // Get highest grade
    double getHighestGrade() const {
        if (grades.empty()) return 0.0;
        return *std::max_element(grades.begin(), grades.end());
    }

    // Get lowest grade
    double getLowestGrade() const {
        if (grades.empty()) return 0.0;
        return *std::min_element(grades.begin(), grades.end());
    }

    // Clear all grades
    void clearGrades() {
        grades.clear();
        average = 0.0;
        std::cout << "All grades cleared for " << name << "\n";
    }
};

// Function to demonstrate explicit constructor
void printStudentInfo(const Student& s) {
    s.displayInfo();
}

// Function to input grade with validation
double inputGrade(const std::string& prompt) {
    double grade;
    while (true) {
        std::cout << prompt;
        std::cin >> grade;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error! Please enter a number.\n";
            continue;
        }

        if (grade >= 0 && grade <= 5) {
            return grade;
        }
        std::cout << "Error! Grade must be between 0 and 5.\n";
    }
}

int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 6: STUDENT CLASS IMPLEMENTATION\n";
    std::cout << "========================================\n\n";

    // Demonstrate constructors
    std::cout << "--- CONSTRUCTOR DEMONSTRATION ---\n";

    // Default constructor
    Student s1;
    s1.displayInfo();

    // Parameterized constructor with explicit
    Student s2("Alice");
    s2.displayInfo();

    // Constructor with initial grade
    Student s3("Bob", 4.5);
    s3.displayInfo();

    // Copy constructor
    Student s4 = s3;
    s4.setName("Bob Copy");
    s4.displayInfo();

    // Demonstrate explicit keyword
    std::cout << "\n--- EXPLICIT CONSTRUCTOR DEMONSTRATION ---\n";

    // This would NOT work because constructor is explicit:
    // printStudentInfo("Charlie"); // ERROR! Cannot convert const char* to Student

    // This works:
    printStudentInfo(Student("Charlie"));

    // This also works:
    Student s5("Charlie");
    printStudentInfo(s5);

    // Demonstrate methods
    std::cout << "\n--- METHOD DEMONSTRATION ---\n";

    Student s6("David");

    // Add grades
    s6.addGrade(4.8);
    s6.addGrade(3.5);
    s6.addGrade(5.0);
    s6.addGrade(2.5);

    s6.displayInfo();

    // Show additional methods
    std::cout << "\nHighest grade: " << s6.getHighestGrade() << "\n";
    std::cout << "Lowest grade: " << s6.getLowestGrade() << "\n";

    // Add invalid grade
    s6.addGrade(6.0); // Should show error

    // Clear grades
    s6.clearGrades();
    s6.displayInfo();

    // Interactive demonstration
    std::cout << "\n--- INTERACTIVE DEMONSTRATION ---\n";

    std::string name;
    std::cout << "Enter student name: ";
    std::cin.ignore();
    std::getline(std::cin, name);

    Student s7(name);

    int numGrades;
    std::cout << "How many grades to add? ";
    std::cin >> numGrades;

    for (int i = 0; i < numGrades; ++i) {
        double grade = inputGrade("Enter grade " + std::to_string(i + 1) + ": ");
        s7.addGrade(grade);
    }

    s7.displayInfo();

    // Demonstrate vector of students
    std::cout << "\n--- VECTOR OF STUDENTS DEMONSTRATION ---\n";

    std::vector<Student> students;

    students.push_back(Student("Eve"));
    students.push_back(Student("Frank", 4.2));
    students.emplace_back("Grace");

    // Add grades to students
    students[0].addGrade(3.8);
    students[0].addGrade(4.1);
    students[2].addGrade(4.7);
    students[2].addGrade(5.0);

    // Display all students
    for (const auto& student : students) {
        student.displayInfo();
    }

    // Find student with highest average
    if (!students.empty()) {
        auto bestStudent = std::max_element(students.begin(), students.end(),
            [](const Student& a, const Student& b) {
                return a.getAverage() < b.getAverage();
            });

        std::cout << "\nStudent with highest average: "
            << bestStudent->getName() << " ("
            << bestStudent->getAverage() << ")\n";
    }

    return 0;
}