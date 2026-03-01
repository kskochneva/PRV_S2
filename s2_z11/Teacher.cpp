#include "Teacher.hpp"
#include <iostream>

Teacher::Teacher() : Person(), subject("Unknown"), experience(0) {}

Teacher::Teacher(const std::string& name, const std::string& subject)
    : Person(name), subject(subject), experience(0) {
}

Teacher::Teacher(const std::string& name, const std::string& subject, int experience)
    : Person(name), subject(subject), experience(experience) {
}

std::string Teacher::getSubject() const { return subject; }
int Teacher::getExperience() const { return experience; }
void Teacher::setSubject(const std::string& newSubject) { subject = newSubject; }
void Teacher::setExperience(int years) { experience = years; }

void Teacher::print() const {
    std::cout << "Teacher: " << name << ", " << subject
        << " (" << experience << " years)";
}

std::string Teacher::getType() const { return "Teacher"; }

void Teacher::teach() const {
    std::cout << name << " is teaching " << subject << "\n";
}