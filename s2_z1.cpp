#include <iostream>//для ввода вывода 

//среднее арифметическое
double srednee(double* arr, int size) {
    if (size <= 0) return 0.0;

    double sum = 0.0;
    for (int i = 0; i < size; ++i) {
        sum += arr[i];
    }
    return sum / size;
}


double findMax(double* arr, int size) {
    if (size <= 0) return 0.0;

    double max = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] > max) {
            max = arr[i];
        }
    }
    return max;
}

// Функция для поиска минимального значения
double findMin(double* arr, int size) {
    if (size <= 0) return 0.0;

    double min = arr[0];
    for (int i = 1; i < size; ++i) {
        if (arr[i] < min) {
            min = arr[i];
        }
    }
    return min;
}

//  с баллом выше порога
int amount_above_bar(double* arr, int size, double bar_grade) {
    int count = 0;
    for (int i = 0; i < size; ++i) {
        if (arr[i] > bar_grade) {
            count++;
        }
    }
    return count;
}

int main() {
    int N;

    std::cout << "Enter number of students: ";
    std::cin >> N;

    
    if (N <= 0) {
        std::cout << "error!\n";
        return 1;
    }

    // ьерем динамической памяти
    //указатель хранит адрес в памяти где лежит значение
    double* grades = new double[N];

    
    std::cout << "Enter grades ( 0 - 5):\n";
    for (int i = 0; i < N; ++i) {
        do {
            std::cout << "Student " << i + 1 << ": ";
            std::cin >> grades[i];

            
            if (grades[i] < 0 || grades[i] > 5) {
                std::cout << "error\n";
            }
        } while (grades[i] < 0 || grades[i] > 5);
    }

  
    std::cout << "Average: " << srednee(grades, N) << "\n";
    std::cout << "Max: " << findMax(grades, N) << "\n";
    std::cout << "Min: " << findMin(grades, N) << "\n";

    double bar_grade;
    std::cout << "\nEnter bar: ";
    std::cin >> bar_grade;
    std::cout << "Number of students abovwe " << bar_grade << ": "
        << amount_above_bar(grades, N, bar_grade) << "\n";

    // Освобождение ячеек
    delete[] grades;

    return 0;
}