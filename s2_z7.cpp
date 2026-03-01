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
    // Constructors
    Person() : name("Unknown") {
        std::cout << "Person default constructor called\n";
    }

    explicit Person(const std::string& name) : name(name) {
        std::cout << "Person parameterized constructor called for " << name << "\n";
    }

    // Virtual destructor (important for polymorphic deletion)
    virtual ~Person() {
        std::cout << "Person destructor called for " << name << "\n";
    }

    // Getters
    std::string getName() const { return name; }

    // Setters
    void setName(const std::string& newName) { name = newName; }

    // Virtual print method
    virtual void print() const {
        std::cout << "Person: name = " << name;
    }

    // Virtual method to get type
    virtual std::string getType() const { return "Person"; }
};

// ==================== STUDENT CLASS DERIVED FROM PERSON ====================

class Student : public Person {
private:
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
    Student() : Person(), average(0.0) {
        std::cout << "Student default constructor called\n";
    }

    // Constructor with name
    explicit Student(const std::string& name) : Person(name), average(0.0) {
        std::cout << "Student constructor with name called for " << name << "\n";
    }

    // Constructor with name and initial grade
    Student(const std::string& name, double initialGrade) : Person(name), average(0.0) {
        std::cout << "Student constructor with grade called for " << name << "\n";
        addGrade(initialGrade);
    }

    // Destructor
    ~Student() override {
        std::cout << "Student destructor called for " << name << "\n";
    }

    // Add a single grade
    void addGrade(double grade) {
        if (grade < 0 || grade > 5) {
            std::cout << "Error! Grade must be between 0 and 5.\n";
            return;
        }
        grades.push_back(grade);
        calculateAverage();
    }

    // Add multiple grades
    void addGrades(const std::vector<double>& newGrades) {
        for (double grade : newGrades) {
            if (grade >= 0 && grade <= 5) {
                grades.push_back(grade);
            }
        }
        calculateAverage();
    }

    // Getters
    double getAverage() const { return average; }
    const std::vector<double>& getGrades() const { return grades; }

    // Override print method
    void print() const override {
        std::cout << "Student: name = " << name
            << ", average = " << std::fixed << std::setprecision(2) << average
            << ", grades = ";
        if (grades.empty()) {
            std::cout << "none";
        }
        else {
            for (double g : grades) {
                std::cout << g << " ";
            }
        }
    }

    // Override getType
    std::string getType() const override { return "Student"; }

    // Student specific methods
    double getHighestGrade() const {
        if (grades.empty()) return 0.0;
        return *std::max_element(grades.begin(), grades.end());
    }

    double getLowestGrade() const {
        if (grades.empty()) return 0.0;
        return *std::min_element(grades.begin(), grades.end());
    }

    bool hasGrades() const { return !grades.empty(); }
};

// ==================== TEACHER CLASS DERIVED FROM PERSON ====================

class Teacher : public Person {
private:
    std::string subject;
    int experienceYears;

public:
    // Default constructor
    Teacher() : Person(), subject("Unknown"), experienceYears(0) {
        std::cout << "Teacher default constructor called\n";
    }

    // Constructor with name and subject
    Teacher(const std::string& name, const std::string& subject)
        : Person(name), subject(subject), experienceYears(0) {
        std::cout << "Teacher constructor called for " << name << "\n";
    }

    // Constructor with all fields
    Teacher(const std::string& name, const std::string& subject, int experience)
        : Person(name), subject(subject), experienceYears(experience) {
        std::cout << "Teacher full constructor called for " << name << "\n";
    }

    // Destructor
    ~Teacher() override {
        std::cout << "Teacher destructor called for " << name << "\n";
    }

    // Getters and setters
    std::string getSubject() const { return subject; }
    int getExperience() const { return experienceYears; }

    void setSubject(const std::string& newSubject) { subject = newSubject; }
    void setExperience(int years) { experienceYears = years; }

    // Override print method
    void print() const override {
        std::cout << "Teacher: name = " << name
            << ", subject = " << subject
            << ", experience = " << experienceYears << " years";
    }

    // Override getType
    std::string getType() const override { return "Teacher"; }

    // Teacher specific method
    void teach() const {
        std::cout << name << " is teaching " << subject << "\n";
    }
};

// ==================== FUNCTIONS FOR POLYMORPHIC CONTAINER ====================

// Print all persons in container
void printAllPersons(const std::vector<Person*>& persons) {
    std::cout << "\n========== ALL PERSONS ==========\n";
    for (size_t i = 0; i < persons.size(); ++i) {
        std::cout << i + 1 << ". ";
        persons[i]->print();
        std::cout << "\n";
    }
}

// Find person by name
Person* findPersonByName(const std::vector<Person*>& persons, const std::string& name) {
    for (auto* p : persons) {
        if (p->getName() == name) {
            return p;
        }
    }
    return nullptr;
}

// Count by type
int countByType(const std::vector<Person*>& persons, const std::string& type) {
    int count = 0;
    for (auto* p : persons) {
        if (p->getType() == type) {
            count++;
        }
    }
    return count;
}

// Clean up memory
void deleteAllPersons(std::vector<Person*>& persons) {
    for (auto* p : persons) {
        delete p;
    }
    persons.clear();
}

// ==================== MAIN FUNCTION ====================

int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 7: INHERITANCE WITH PERSON CLASS\n";
    std::cout << "========================================\n\n";

    // Create container of Person pointers
    std::vector<Person*> people;

    // Add Students
    std::cout << "--- Creating Students ---\n";
    Student* s1 = new Student("Alice");
    s1->addGrades({ 4.5, 3.8, 5.0, 4.2 });
    people.push_back(s1);

    Student* s2 = new Student("Bob", 4.8);
    s2->addGrade(3.5);
    s2->addGrade(4.0);
    people.push_back(s2);

    Student* s3 = new Student("Charlie");
    s3->addGrade(2.5);
    s3->addGrade(3.0);
    people.push_back(s3);

    // Add Teachers
    std::cout << "\n--- Creating Teachers ---\n";
    Teacher* t1 = new Teacher("Dr. Smith", "Mathematics", 10);
    people.push_back(t1);

    Teacher* t2 = new Teacher("Prof. Johnson", "Physics");
    t2->setExperience(15);
    people.push_back(t2);

    Teacher* t3 = new Teacher("Ms. Davis", "English", 5);
    people.push_back(t3);

    // Print all persons (polymorphic call)
    printAllPersons(people);

    // Demonstrate polymorphic behavior
    std::cout << "\n========== POLYMORPHIC DEMONSTRATION ==========\n";

    for (auto* person : people) {
        std::cout << "\nCalling print() on " << person->getType() << ": ";
        person->print();
        std::cout << "\n";

        // Type-specific operations
        if (person->getType() == "Teacher") {
            Teacher* t = dynamic_cast<Teacher*>(person);
            if (t) {
                t->teach();
            }
        }
        else if (person->getType() == "Student") {
            Student* s = dynamic_cast<Student*>(person);
            if (s && s->hasGrades()) {
                std::cout << "  Highest grade: " << s->getHighestGrade() << "\n";
                std::cout << "  Lowest grade: " << s->getLowestGrade() << "\n";
            }
        }
    }

    // Statistics
    std::cout << "\n========== STATISTICS ==========\n";
    std::cout << "Total persons: " << people.size() << "\n";
    std::cout << "Students: " << countByType(people, "Student") << "\n";
    std::cout << "Teachers: " << countByType(people, "Teacher") << "\n";

    // Find person by name
    std::cout << "\n========== SEARCH DEMONSTRATION ==========\n";
    std::string searchName = "Alice";
    Person* found = findPersonByName(people, searchName);
    if (found) {
        std::cout << "Found: ";
        found->print();
        std::cout << "\n";
    }
    else {
        std::cout << searchName << " not found.\n";
    }

    // Demonstrate virtual destructor (automatic when deleting)
    std::cout << "\n========== CLEANUP ==========\n";
    deleteAllPersons(people);

    // Create a new container using smart pointers (modern C++ approach)
    std::cout << "\n========== SMART POINTERS DEMONSTRATION ==========\n";
    std::vector<std::unique_ptr<Person>> smartPeople;

    smartPeople.push_back(std::make_unique<Student>("David", 4.2));
    smartPeople.push_back(std::make_unique<Teacher>("Dr. Wilson", "Chemistry", 8));

    for (const auto& person : smartPeople) {
        person->print();
        std::cout << "\n";
    }
    // No need to delete - smart pointers handle it automatically

    return 0;
}