#ifndef PERSON_H
#define PERSON_H

#include <string>
#include <iostream>

// Forward declaration
class Group;

class Person {
protected:
    std::string name;

public:
    // Constructors
    Person();
    explicit Person(const std::string& name);

    // Virtual destructor
    virtual ~Person();

    // Getters/Setters
    std::string getName() const;
    void setName(const std::string& newName);

    // Virtual methods
    virtual void print() const;
    virtual double getAverage() const;
    virtual std::string getType() const;

    // Inline method in header
    inline bool hasName() const { return !name.empty(); }
};

#endif // PERSON_H