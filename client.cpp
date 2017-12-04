#include "client.h"

Client::Client(int id, QString firstName, QString lastName,
               int passport, QString info, bool disturb, int roomId)
    : Person(id, firstName, lastName)
{
    this->passport = passport;
    this->info = info;
    this->disturb = disturb;
    this->roomId = roomId;
}

int Client::getPassport()
{
    return passport;
}

QString Client::getInfo()
{
    return info;
}

bool Client::getDisturb()
{
    return disturb;
}

int Client::getRoomId()
{
    return roomId;
}
