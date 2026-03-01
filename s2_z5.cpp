#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <limits>

#pragma pack(push, 1)
struct FileHeader {
    char signature[4];
    uint32_t version;
    uint32_t studentCount;
};
#pragma pack(pop)

class Student {
private:
    int id;
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
    Student() : id(0), average(0.0) {}

    Student(int studentId, const std::vector<double>& studentGrades)
        : id(studentId), grades(studentGrades) {
        calculateAverage();
    }

    int getId() const { return id; }
    double getAverage() const { return average; }
    const std::vector<double>& getGrades() const { return grades; }
    size_t getGradeCount() const { return grades.size(); }

    void setId(int newId) { id = newId; }
    void setGrades(const std::vector<double>& newGrades) {
        grades = newGrades;
        calculateAverage();
    }

    void addGrade(double grade) {
        grades.push_back(grade);
        calculateAverage();
    }

    void display() const {
        std::cout << "Student " << id << ": average = " << average
            << ", grades: ";
        for (double g : grades) {
            std::cout << g << " ";
        }
        std::cout << "\n";
    }
};

class StudentDatabase {
private:
    std::vector<Student> students;
    int subjectCount;

    int inputPositiveInt(const std::string& prompt) const {
        int value;
        while (true) {
            std::cout << prompt;
            std::cin >> value;

            if (std::cin.fail() || value <= 0) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error! Please enter a positive number.\n";
            }
            else {
                return value;
            }
        }
    }

    double inputGrade(int student, int subject) const {
        double grade;
        while (true) {
            std::cout << "Student " << student << ", subject " << subject << ": ";
            std::cin >> grade;

            if (std::cin.fail()) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Error! Please enter a number between 0 and 5.\n";
                continue;
            }

            if (grade >= 0 && grade <= 5) {
                return grade;
            }
            std::cout << "Error! Grade must be between 0 and 5.\n";
        }
    }

public:
    StudentDatabase() : subjectCount(0) {}

    void inputData() {
        int studentCount = inputPositiveInt("Enter number of students: ");
        subjectCount = inputPositiveInt("Enter number of subjects: ");

        students.clear();

        std::cout << "\nEnter student grades for each subject (0 to 5):\n";
        for (int i = 0; i < studentCount; ++i) {
            std::vector<double> studentGrades;
            for (int j = 0; j < subjectCount; ++j) {
                double grade = inputGrade(i + 1, j + 1);
                studentGrades.push_back(grade);
            }
            students.emplace_back(i + 1, studentGrades);
        }
    }

    void displayAll() const {
        std::cout << "\n========== STUDENT DATABASE ==========\n";
        std::cout << "Subjects per student: " << subjectCount << "\n";
        std::cout << "Total students: " << students.size() << "\n\n";

        for (const auto& student : students) {
            student.display();
        }
    }

    bool saveToFile(const std::string& filename) const {
        std::ofstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file for writing: " << filename << "\n";
            return false;
        }

        FileHeader header;
        std::strncpy(header.signature, "GRD1", 4);
        header.version = 1;
        header.studentCount = static_cast<uint32_t>(students.size());

        std::cout << "\n--- Writing to file ---\n";
        std::cout << "Header size: " << sizeof(FileHeader) << " bytes\n";
        std::cout << "Signature: " << header.signature << "\n";
        std::cout << "Version: " << header.version << "\n";
        std::cout << "Student count: " << header.studentCount << "\n";

        file.write(reinterpret_cast<const char*>(&header), sizeof(header));
        file.write(reinterpret_cast<const char*>(&subjectCount), sizeof(subjectCount));

        for (const auto& student : students) {
            const auto& grades = student.getGrades();
            for (double grade : grades) {
                file.write(reinterpret_cast<const char*>(&grade), sizeof(grade));
            }
        }

        file.close();
        std::cout << "Data successfully saved to " << filename << "\n";
        return true;
    }

    bool loadFromFile(const std::string& filename) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            std::cerr << "Error: Cannot open file for reading: " << filename << "\n";
            return false;
        }

        FileHeader header;
        file.read(reinterpret_cast<char*>(&header), sizeof(header));

        std::cout << "\n--- Reading from file ---\n";
        std::cout << "Header size: " << sizeof(FileHeader) << " bytes\n";
        std::cout << "Signature: " << header.signature << "\n";
        std::cout << "Version: " << header.version << "\n";
        std::cout << "Student count: " << header.studentCount << "\n";

        if (std::strncmp(header.signature, "GRD1", 4) != 0) {
            std::cerr << "Error: Invalid file signature!\n";
            return false;
        }

        if (header.version != 1) {
            std::cerr << "Error: Unsupported file version!\n";
            return false;
        }

        file.read(reinterpret_cast<char*>(&subjectCount), sizeof(subjectCount));
        std::cout << "Subject count: " << subjectCount << "\n";

        students.clear();

        for (uint32_t i = 0; i < header.studentCount; ++i) {
            std::vector<double> studentGrades;
            for (int j = 0; j < subjectCount; ++j) {
                double grade;
                file.read(reinterpret_cast<char*>(&grade), sizeof(grade));
                studentGrades.push_back(grade);
            }
            students.emplace_back(i + 1, studentGrades);
        }

        file.close();
        std::cout << "Data successfully loaded from " << filename << "\n";
        return true;
    }

    void displayStatistics() const {
        if (students.empty()) {
            std::cout << "No students in database.\n";
            return;
        }

        std::cout << "\n========== STATISTICS ==========\n";

        int excellent = 0;
        int atRisk = 0;
        double sumAverages = 0.0;

        for (const auto& student : students) {
            double avg = student.getAverage();
            sumAverages += avg;

            if (avg >= 4.5) excellent++;
            if (avg < 3.0) atRisk++;
        }

        double overallAverage = sumAverages / students.size();

        std::cout << "Total students: " << students.size() << "\n";
        std::cout << "Subjects per student: " << subjectCount << "\n";
        std::cout << "Overall class average: " << overallAverage << "\n";
        std::cout << "Excellent students (>= 4.5): " << excellent << "\n";
        std::cout << "At-risk students (< 3.0): " << atRisk << "\n";
    }
};

int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 5: BINARY FILE STORAGE WITH CLASS\n";
    std::cout << "========================================\n";

    std::cout << "\n--- Structure Size Demonstration ---\n";
    std::cout << "Size of FileHeader with #pragma pack(1): "
        << sizeof(FileHeader) << " bytes\n";
    std::cout << "Components:\n";
    std::cout << "  - signature[4]: 4 bytes\n";
    std::cout << "  - version: " << sizeof(uint32_t) << " bytes\n";
    std::cout << "  - studentCount: " << sizeof(uint32_t) << " bytes\n\n";

    StudentDatabase db;

    int choice;
    do {
        std::cout << "\n========== MENU ==========\n";
        std::cout << "1. Input new data\n";
        std::cout << "2. Display all students\n";
        std::cout << "3. Save to binary file\n";
        std::cout << "4. Load from binary file\n";
        std::cout << "5. Display statistics\n";
        std::cout << "0. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            db.inputData();
            break;
        case 2:
            db.displayAll();
            break;
        case 3:
            db.saveToFile("students.bin");
            break;
        case 4:
            db.loadFromFile("students.bin");
            break;
        case 5:
            db.displayStatistics();
            break;
        case 0:
            std::cout << "Goodbye!\n";
            break;
        default:
            std::cout << "Invalid choice!\n";
        }
    } while (choice != 0);

    return 0;
}