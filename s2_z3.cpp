#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <limits>
#include <string>



int inputPositiveInt(const std::string& prompt) {
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


double inputGrade(int student, int subject) {
    double grade;
    while (true) {
        std::cout << "Student " << student + 1 << ", subject " << subject + 1 << ": ";
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

// Calculate average for each student
std::vector<double> calculateStudentAverages(const std::vector<std::vector<double>>& grades) {
    const size_t students = grades.size();
    const size_t subjects = grades[0].size();
    std::vector<double> averages(students, 0.0);

    for (size_t i = 0; i < students; ++i) {
        double sum = 0.0;
        for (size_t j = 0; j < subjects; ++j) {
            sum += grades[i][j];
        }
        averages[i] = sum / subjects;
    }
    return averages;
}


std::vector<std::pair<int, double>> createStudentPairs(const std::vector<double>& averages) {
    std::vector<std::pair<int, double>> pairs;

    for (size_t i = 0; i < averages.size(); ++i) {
        pairs.push_back({ static_cast<int>(i), averages[i] });
    }

    return pairs;
}

void sortStudents(
    std::vector<std::pair<int, double>>& students,
    bool ascendingIndex = true,
    double threshold = 0.0,
    bool useThreshold = false,
    int multiplier = 1
) {
    
    auto sortByDefault = [=](const auto& a, const auto& b) {
        if (a.second != b.second) {
            return a.second > b.second;  
        }
        
        return a.first < b.first;
        };

    
    auto sortWithThreshold = [&](const auto& a, const auto& b) {
        
        if (useThreshold && a.second < threshold && b.second < threshold) {
            return a.first < b.first;
        }
        if (a.second != b.second) {
            return a.second * multiplier > b.second * multiplier;
        }
        if (ascendingIndex) {
            return a.first < b.first;
        }
        else {
            return a.first > b.first;
        }
        };

    
    auto sortMixed = [ascendingIndex, &threshold, &useThreshold](const auto& a, const auto& b) {
        if (useThreshold && a.second > threshold && b.second > threshold) {
            return a.second > b.second;
        }
        if (a.second != b.second) {
            return a.second > b.second;
        }
        if (ascendingIndex) {
            return a.first < b.first;
        }
        return a.first > b.first;
        };

   
    std::sort(students.begin(), students.end(), sortByDefault);

   
}


void printSortedStudents(const std::vector<std::pair<int, double>>& students) {
    std::cout << "\n========== SORTED LIST ==========\n";
    std::cout << "Rank | Student | Average Grade\n";
    std::cout << "-----|---------|--------------\n";

    for (size_t i = 0; i < students.size(); ++i) {
        std::cout << std::setw(3) << i + 1 << "   | "
            << "Student " << std::setw(2) << students[i].first + 1 << " | "
            << std::fixed << std::setprecision(2) << students[i].second << "\n";
    }
}



void demonstrateCaptures() {
    std::cout << "\n========== LAMBDA  ==========\n";

    int x = 10, y = 20;
    double pi = 3.14159;
    std::string message = "Capture example";

    std::cout << "Initial values: x = " << x << ", y = " << y
        << ", pi = " << pi << ", message = " << message << "\n\n";

   
    auto lambdaByValue = [=]() {
        std::cout << "[=] Capture by value:\n";
        std::cout << "    x = " << x << ", y = " << y
            << ", pi = " << pi << ", message = " << message << "\n";
        // x = 100; // ERROR! Cannot modify captured by value
        };
    lambdaByValue();

   
    auto lambdaByReference = [&]() {
        std::cout << "[&] Capture by reference:\n";
        x = 100;  // Can modify!
        y = 200;
        message = "Changed in lambda";
        std::cout << "    After change: x = " << x << ", y = " << y
            << ", message = " << message << "\n";
        };
    lambdaByReference();

    
    auto lambdaMixed = [x, &y, &message](double factor) {
        std::cout << "\n[ x by value, &y, &message by reference ]:\n";
       
        std::cout << "    Before: x = " << x << ", y = " << y
            << ", message = " << message << "\n";
        
        y = static_cast<int>(y * factor);
        message = "Now with suffix";
        std::cout << "    After: x = " << x << ", y = " << y
            << ", message = " << message << "\n";
        };
    lambdaMixed(1.5);

    std::cout << "\nFinal values: x = " << x << ", y = " << y
        << ", message = " << message << "\n";
}



int main() {
    

    const int students = inputPositiveInt("Enter number of students: ");
    const int subjects = inputPositiveInt("Enter number of subjects: ");

   
    std::vector<std::vector<double>> grades(students, std::vector<double>(subjects));

    
    std::cout << "\nEnter student grades for each subject (0 to 5):\n";
    for (int i = 0; i < students; ++i) {
        for (int j = 0; j < subjects; ++j) {
            grades[i][j] = inputGrade(i, j);
        }
    }

    const std::vector<double> averages = calculateStudentAverages(grades);

    
    std::vector<std::pair<int, double>> studentPairs = createStudentPairs(averages);

    std::cout << "\n--- Original data (in student order) ---\n";
    for (const auto& p : studentPairs) {
        std::cout << "Student " << p.first + 1 << ": average = "
            << std::fixed << std::setprecision(2) << p.second << "\n";
    }

    sortStudents(studentPairs);

    
    printSortedStudents(studentPairs);

    
    demonstrateCaptures();

    return 0;
}