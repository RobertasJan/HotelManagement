#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include "person.h"

class Client : public Person
{
public:
    Client(int, QString, QString, int, QString, bool, int);
    int getPassport();
    QString getInfo();
    bool getDisturb();
    int getRoomId();
private:
    int passport;
    QString info;
    bool disturb;
    int roomId;
};

#endif // CLIENT_H
