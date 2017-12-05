#ifndef CLIENT_H
#define CLIENT_H

#include <QString>
#include <vector>
#include "reservation.h"
#include "person.h"

class Client : public Person
{
public:
    Client(int, QString, QString, int, QString, bool, int, std::vector<Reservation*>);
    int getPassport() const;
    QString getInfo() const;
    bool getDisturb() const;
    int getRoomId() const;
    std::vector<Reservation*> getResList();
private:
    int passport;
    QString info;
    bool disturb;
    int roomId;
    std::vector<Reservation*> resList;

};

#endif // CLIENT_H
