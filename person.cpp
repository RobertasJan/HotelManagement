#include "person.h"


void Person::setId(int id)
{
    this->id = id;
}

void Person::setFirstName(QString firstName)
{
    this->firstName = firstName;
}

void Person::setLastName(QString lastName)
{
    this->lastName = lastName;
}

int Person::getId()
{
    return id;
}

QString Person::getFirstName()
{
    return firstName;
}

QString Person::getLastName()
{
    return lastName;
}
