#ifndef PERSON_H
#define PERSON_H

#include <QString>

class Person
{
public:
    virtual void setId(int);
    virtual void setFirstName(QString);
    virtual void setLastName(QString);
    virtual int getId();
    virtual QString getFirstName();
    virtual QString getLastName();
protected:
    int id;
    QString firstName;
    QString lastName;
};

#endif // PERSON_H
