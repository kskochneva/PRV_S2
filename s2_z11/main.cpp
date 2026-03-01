#include <iostream>
#include <vector>
#include <memory>
#include "Student.hpp"
#include "Teacher.hpp"
#include "Group.hpp"
#include "FileManager.hpp"

int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 11: MULTI-MODULE PROJECT\n";
    std::cout << "========================================\n\n";

    // Создание студентов
    std::cout << "--- Creating students ---\n";
    Student* s1 = new Student("Alice", "2024001", { 4.5, 3.8, 5.0, 4.2 });
    Student* s2 = new Student("Bob", "2024002", { 3.5, 4.0, 3.8, 4.5 });
    Student* s3 = new Student("Charlie", "2024003", { 2.5, 3.0, 2.8, 3.2 });
    Student* s4 = new Student("Diana", "2024004", { 4.8, 4.5, 4.9, 4.7 });

    // Создание группы
    Group group("CS-2024");

    // Добавление студентов в группу
    std::cout << "\n--- Adding students to group ---\n";
    group.addStudent(s1);
    group.addStudent(s2);
    group.addStudent(s3);
    group.addStudent(s4);

    // Вывод группы
    group.print();

    // Сортировка по среднему баллу
    std::cout << "\n--- Sorting students by average (descending) ---\n";
    group.sortStudentsByAverage();
    group.print();

    // Фильтрация по порогу
    std::cout << "\n--- Filtering students with average >= 4.0 ---\n";
    auto filtered = group.filterByThreshold(4.0);
    for (const auto* student : filtered) {
        student->print();
        std::cout << "\n";
    }

    // Сохранение в файл
    std::cout << "\n--- Saving group to file ---\n";
    FileManager::saveGroup(group, "group.bin");

    // Загрузка из файла
    std::cout << "\n--- Loading group from file ---\n";
    Group loadedGroup;
    FileManager::loadGroup(loadedGroup, "group.bin");
    loadedGroup.print();

    // Удаление студента
    std::cout << "\n--- Removing Bob from group ---\n";
    group.removeStudent("Bob");
    group.print();

    // Освобождение памяти
    std::cout << "\n--- Cleaning up ---\n";
    delete s1;
    delete s2;
    delete s3;
    delete s4;

    std::cout << "\nAll memory freed. Program completed.\n";
    return 0;
}