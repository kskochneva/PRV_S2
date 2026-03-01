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


void printStudentList(const std::vector<std::pair<int, double>>& students, const std::string& title) {
    std::cout << "\n" << title << "\n";
    std::cout << "----------------------------------------\n";
    if (students.empty()) {
        std::cout << "No students in the list.\n";
        return;
    }
    for (const auto& s : students) {
        std::cout << "Student " << std::setw(2) << s.first + 1 << ": average = "
            << std::fixed << std::setprecision(2) << s.second << "\n";
    }
}

std::vector<std::pair<int, double>> createStudentPairs(const std::vector<double>& averages) {
    std::vector<std::pair<int, double>> pairs;

    for (size_t i = 0; i < averages.size(); ++i) {
        pairs.push_back({ static_cast<int>(i), averages[i] });
    }

    return pairs;
}


void filterStudentsBelowThreshold(std::vector<std::pair<int, double>>& students, double threshold) {
    std::cout << "\n--- Filtering: Removing students with average < " << threshold << " ---\n";

    
    auto shouldRemove = [=](const std::pair<int, double>& s) {
        return s.second < threshold;
        };

    
    students.erase(
        std::remove_if(students.begin(), students.end(), shouldRemove),
        students.end()
    );
}


int countExcellentStudents(const std::vector<std::pair<int, double>>& students) {
    
    auto isExcellent = [&](const std::pair<int, double>& s) {
        return s.second >= 4.5;
        };

    return std::count_if(students.begin(), students.end(), isExcellent);
}


int countAtRiskStudents(const std::vector<std::pair<int, double>>& students) {
    
    auto isAtRisk = [=](const std::pair<int, double>& s) {
        return s.second < 3.0;
        };

    return std::count_if(students.begin(), students.end(), isAtRisk);
}


template<typename Predicate>
void filterStudentsCustom(std::vector<std::pair<int, double>>& students,
    Predicate pred,
    const std::string& message) {
    std::cout << "\n--- " << message << " ---\n";

    int beforeCount = students.size();

    students.erase(
        std::remove_if(students.begin(), students.end(), pred),
        students.end()
    );

    int removedCount = beforeCount - students.size();
    std::cout << "Removed " << removedCount << " students.\n";
}


void demonstrateCaptures() {
    std::cout << "\n========== LAMBDA CAPTURE DEMONSTRATION ==========\n";

    double threshold = 3.5;
    int excellentCount = 0;
    std::string status = "processing";

    std::cout << "Initial values: threshold = " << threshold
        << ", excellentCount = " << excellentCount
        << ", status = " << status << "\n\n";

    auto lambdaByValue = [=]() {
        std::cout << "[=] Capture by value (snapshot):\n";
        std::cout << "    threshold = " << threshold
            << ", excellentCount = " << excellentCount
            << ", status = " << status << "\n";
       
        };

  
    auto lambdaByReference = [&]() {
        std::cout << "[&] Capture by reference:\n";
        threshold = 4.0;
        excellentCount = 5;
        status = "completed";
        std::cout << "    After modification: threshold = " << threshold
            << ", excellentCount = " << excellentCount
            << ", status = " << status << "\n";
        };

    
    auto lambdaMixed = [threshold, &excellentCount, &status]() {
        std::cout << "\n[threshold by value, excellentCount&status by reference]:\n";
        std::cout << "    Before: threshold = " << threshold
            << ", excellentCount = " << excellentCount
            << ", status = " << status << "\n";
       
        excellentCount = 10;
        status = "filtered";
        std::cout << "    After: threshold = " << threshold
            << ", excellentCount = " << excellentCount
            << ", status = " << status << "\n";
        };

    lambdaByValue();
    lambdaByReference();
    lambdaMixed();

    std::cout << "\nFinal values: threshold = " << threshold
        << ", excellentCount = " << excellentCount
        << ", status = " << status << "\n";
}


int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 4: STUDENT FILTERING\n";
    std::cout << "========================================\n";

    
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

   
    printStudentList(studentPairs, "ORIGINAL STUDENT LIST");

   
    double threshold;
    std::cout << "\nEnter threshold for filtering: ";
    std::cin >> threshold;

    
    std::vector<std::pair<int, double>> filteredStudents = studentPairs;
    filterStudentsBelowThreshold(filteredStudents, threshold);
    printStudentList(filteredStudents, "AFTER FILTERING (students with average >= " +
        std::to_string(threshold) + ")");

   
    std::cout << "\n--- STUDENT STATISTICS ---\n";

    int excellent = countExcellentStudents(studentPairs);
    int atRisk = countAtRiskStudents(studentPairs);

    std::cout << "Excellent students (average >= 4.5): " << excellent << "\n";
    std::cout << "At-risk students (average < 3.0): " << atRisk << "\n";

    
    std::cout << "\n========== ERASE-REMOVE DEMONSTRATION ==========\n";

    
    std::vector<std::pair<int, double>> demoStudents = studentPairs;
    printStudentList(demoStudents, "DEMO: Original list");

   
    double customThreshold = 4.0;
    auto filterPredicate = [customThreshold](const std::pair<int, double>& s) {
        return s.second < customThreshold;
        };

    filterStudentsCustom(demoStudents, filterPredicate,
        "Filtering students with average < " + std::to_string(customThreshold));
    printStudentList(demoStudents, "After custom filter");

    
    demonstrateCaptures();

    return 0;
}