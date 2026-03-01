#include "Person.hpp"
#include <iostream>

Person::Person() : name("Unknown") {}

Person::Person(const std::string& name) : name(name) {}

Person::~Person() {}

std::string Person::getName() const { return name; }

void Person::setName(const std::string& newName) { name = newName; }

void Person::print() const {
    std::cout << "Person: " << name;
}

std::string Person::getType() const { return "Person"; }