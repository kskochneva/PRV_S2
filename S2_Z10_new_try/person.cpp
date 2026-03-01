#include "person.h"
#include <iostream>

// Constructors
Person::Person() : name("Unknown") {}

Person::Person(const std::string& name) : name(name) {}

// Destructor
Person::~Person() {}

// Getters/Setters
std::string Person::getName() const { return name; }
void Person::setName(const std::string& newName) { name = newName; }

// Virtual methods
void Person::print() const {
    std::cout << "Person: " << name;
}

double Person::getAverage() const { return 0.0; }

std::string Person::getType() const { return "Person"; }