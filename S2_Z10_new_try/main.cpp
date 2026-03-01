#include <iostream>
#include <vector>
#include <memory>
#include "person.h"
#include "student.h"
#include "teacher.h"
#include "group.h"
#include "recordbook.h"

int main() {
    std::cout << "========================================\n";
    std::cout << "TASK 10: HEADER/CPP SEPARATION\n";
    std::cout << "========================================\n\n";

    // Create students
    Student s1("Alice", "2024001", { 4.5, 3.8, 5.0, 4.2 });
    Student s2("Bob", "2024002", { 3.5, 4.0, 3.8, 4.5 });

    // Test inline methods
    std::cout << "Inline method test:\n";
    std::cout << "Alice has name? " << (s1.hasName() ? "Yes" : "No") << "\n";
    std::cout << "Alice has record? " << (s1.hasRecordBook() ? "Yes" : "No") << "\n\n";

    // Create group
    Group group("CS-101");
    group.addStudent(s1);
    group.addStudent(s2);

    group.print();

    std::cout << "\nGroup empty? " << (group.isEmpty() ? "Yes" : "No") << "\n";

    return 0;
}