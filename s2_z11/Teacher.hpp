#ifndef TEACHER_HPP
#define TEACHER_HPP

#include "Person.hpp"
#include <string>

class Teacher : public Person {
private:
    std::string subject;
    int experience;

public:
    Teacher();
    Teacher(const std::string& name, const std::string& subject);
    Teacher(const std::string& name, const std::string& subject, int experience);

    std::string getSubject() const;
    int getExperience() const;
    void setSubject(const std::string& newSubject);
    void setExperience(int years);

    void print() const override;
    std::string getType() const override;
    double getAverage() const override { return 0.0; }

    void teach() const;

    inline bool isExperienced() const { return experience >= 5; }
};

#endif