#include <iostream>
#include <vector>
#include <limits>
#include <iomanip>

// ==================== ЗАДАЧА 1 ====================


double inputGrade(int N) {
    double grade;
    while (true) {
        std::cout << "Student " << N << ": ";
        std::cin >> grade;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error.\n";
            continue;
        }

        if (grade >= 0 && grade <= 5) {
            return grade;
        }
        std::cout << "Error.\n";
    }
}


double calculateAverage(const double* arr, int size) {
    if (size <= 0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum / size;
}


double findMax(const double* arr, int size) {
    if (size <= 0) return 0.0;

    double max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}


double findMin(const double* arr, int size) {
    if (size <= 0) return 0.0;

    double min = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

// Подсчёт студентов выше заданного порога
int countAboveBar(const double* arr, int size, double bar) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > bar) {
            count++;
        }
    }
    return count;
}

// ==================== ЗАДАЧА 2 ====================



int inputPositiveInt(const std::string& prompt) {
    int value;
    while (true) {
        std::cout << prompt;
        std::cin >> value;

        if (std::cin.fail() || value <= 0) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error.\n";
        }
        else {
            return value;
        }
    }
}


double inputGradeForStudent(int student, int subject) {
    double grade;
    while (true) {
        std::cout << "Student " << student + 1 << ", subject " << subject + 1 << ": ";
        std::cin >> grade;

        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Error.\n";
            continue;
        }

        if (grade >= 0 && grade <= 5) {
            return grade;
        }
        std::cout << "Error.\n";
    }
}

// Вычисление среднего балла каждого студента
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

std::vector<double> calculateSubjectAverages(const std::vector<std::vector<double>>& grades) {
    const size_t students = grades.size();
    const size_t subjects = grades[0].size();
    std::vector<double> averages(subjects, 0.0);

    for (size_t j = 0; j < subjects; ++j) {
        double sum = 0.0;
        for (size_t i = 0; i < students; ++i) {
            sum += grades[i][j];
        }
        averages[j] = sum / students;
    }
    return averages;
}


int findBestStudent(const std::vector<double>& studentAverages) {
    if (studentAverages.empty()) return -1;

    int bestIndex = 0;
    double bestAverage = studentAverages[0];

    for (size_t i = 1; i < studentAverages.size(); ++i) {
        if (studentAverages[i] > bestAverage) {
            bestAverage = studentAverages[i];
            bestIndex = i;
        }
    }
    return bestIndex;
}

void printGrades(const std::vector<std::vector<double>>& grades) {
    const size_t students = grades.size();
    const size_t subjects = grades[0].size();

    std::cout << "\nGRADE MATRIX:\n";
    std::cout << "     ";
    for (size_t j = 0; j < subjects; ++j) {
        std::cout << "Subject" << std::setw(2) << j + 1 << " ";
    }
    std::cout << "\n";

    for (size_t i = 0; i < students; ++i) {
        std::cout << "Student" << std::setw(2) << i + 1 << ": ";
        for (size_t j = 0; j < subjects; ++j) {
            std::cout << std::setw(5) << std::fixed << std::setprecision(1) << grades[i][j] << " ";
        }
        std::cout << "\n";
    }
}

// Вывод средних баллов
void printAverages(const std::vector<double>& averages, const std::string& label) {
    std::cout << label << ":\n";
    for (size_t i = 0; i < averages.size(); ++i) {
        std::cout << "  ";
        if (label.find("Student") != std::string::npos) {
            std::cout << "Student " << i + 1;
        }
        else {
            std::cout << "Subject " << i + 1;
        }
        std::cout << ": " << std::fixed << std::setprecision(2) << averages[i] << "\n";
    }
}

int main() {
    

    
    int N;
    std::cout << "Enter number of students: ";
    std::cin >> N;

    // Проверка на корректность ввода
    if (N <= 0 || std::cin.fail()) {
        std::cout << "Error\n";
        return 1;
    }

    // Выделение динамической памяти
    double* grades1 = new double[N];

    // Ввод оценок
    std::cout << "Enter grades ( 0 - 5):\n";
    for (int i = 0; i < N; ++i) {
        grades1[i] = inputGrade(i + 1);
    }

 
    std::cout << "Av: " << calculateAverage(grades1, N) << "\n";
    std::cout << "Max: " << findMax(grades1, N) << "\n";
    std::cout << "Min: " << findMin(grades1, N) << "\n";

    double bar;
    std::cout << "Bar: ";
    std::cin >> bar;
    std::cout << "Students above " << bar << ": " << countAboveBar(grades1, N, bar) << "\n";

    // Освобождение памяти Задачи 1
    delete[] grades1;

    

    
    const int students = inputPositiveInt("Enter students: ");
    const int subjects = inputPositiveInt("Enter subjects: ");

    
    std::vector<std::vector<double>> grades2(students, std::vector<double>(subjects));


    std::cout << "\nEnter grades:\n";
    for (int i = 0; i < students; ++i) {
        for (int j = 0; j < subjects; ++j) {
            grades2[i][j] = inputGradeForStudent(i, j);
        }
    }

    printGrades(grades2);

    
    const std::vector<double> studentAvgs = calculateStudentAverages(grades2);
    printAverages(studentAvgs, "\nAverage grades");

    
    const std::vector<double> subjectAvgs = calculateSubjectAverages(grades2);
    printAverages(subjectAvgs, "\nBy subjects");

    const int bestStudent = findBestStudent(studentAvgs);
    if (bestStudent != -1) {
        std::cout << "\nBest student: " << bestStudent + 1 <<  "\n";
    }

    return 0;
}