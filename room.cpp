#include "room.h"

// constructs Room object
Room::Room(int roomNumber, QString roomType, bool isClean, QDate checkIn, QDate checkOut, int clientId)
{
    this->roomNumber = roomNumber;
    this->roomType = roomType;
    this->isClean = isClean;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
    this->clientId = clientId;
}

int Room::getRoomNumber() const
{
    return roomNumber;
}

QString Room::getRoomType() const
{
    return roomType;
}

bool Room::getIsClean() const
{
    return isClean;
}

QDate Room::getCheckIn() const
{
    return checkIn;
}

QDate Room::getCheckOut() const
{
    return checkOut;
}

int Room::getClientId() const
{
    return clientId;
}

void Room::setCheckIn(QDate checkIn)
{
    this->checkIn = checkIn;
}

void Room::setCheckOut(QDate checkOut)
{
    this->checkOut = checkOut;
}

void Room::setClientId(int clientId)
{
    this->clientId = clientId;
}

