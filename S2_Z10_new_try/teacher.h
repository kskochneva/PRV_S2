#ifndef TEACHER_H
#define TEACHER_H

#include "person.h"
#include <string>

class Teacher : public Person {
private:
    std::string subject;
    int experience;

public:
    // Constructors
    Teacher();
    Teacher(const std::string& name, const std::string& subject);
    Teacher(const std::string& name, const std::string& subject, int experience);

    // Getters/Setters
    std::string getSubject() const;
    int getExperience() const;
    void setSubject(const std::string& newSubject);
    void setExperience(int years);

    // Override methods
    void print() const override;
    std::string getType() const override;

    // Teacher specific
    void teach() const;

    // Inline method
    inline bool isExperienced() const { return experience >= 5; }
};

#endif // TEACHER_H