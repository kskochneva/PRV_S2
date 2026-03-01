#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>
#include <iostream>

class Person {
protected:
    std::string name;

public:
    Person();
    explicit Person(const std::string& name);
    virtual ~Person();

    std::string getName() const;
    void setName(const std::string& newName);

    virtual void print() const;
    virtual double getAverage() const = 0;
    virtual std::string getType() const;

    inline bool hasName() const { return !name.empty(); }
};

#endif