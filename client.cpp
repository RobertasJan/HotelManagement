#include "client.h"

Client::Client(int id, QString firstName, QString lastName,
               int passport, QString info, bool disturb, int roomId, std::vector<Reservation*> resList)
    : Person(id, firstName, lastName)
{
    this->passport = passport;
    this->info = info;
    this->disturb = disturb;
    this->roomId = roomId;
    this->resList = resList;
}

int Client::getPassport() const
{
    return passport;
}

QString Client::getInfo() const
{
    return info;
}

bool Client::getDisturb() const
{
    return disturb;
}

int Client::getRoomId() const
{
    return roomId;
}

std::vector<Reservation*> Client::getResList()
{
    return resList;
}
