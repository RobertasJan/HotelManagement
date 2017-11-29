#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include "person.h"

class Client : public Person
{
public:
    Client(int, QString, QString, int, QString, bool);
private:
    int passport;
    QString info;
    bool disturb;
};

#endif // CLIENT_H
