#include "room.h"

// constructs Room object
Room::Room(int roomNumber, QString roomType, bool isFree, bool isClean, QDate checkIn, QDate checkOut)
{
    this->roomNumber = roomNumber;
    this->roomType = roomType;
    this->isFree = isFree;
    this->isClean = isClean;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
}

int Room::getRoomNumber() const
{
    return roomNumber;
}

QString Room::getRoomType() const
{
    return roomType;
}

bool Room::getIsFree() const
{
    return isFree;
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

void Room::setCheckIn(QDate checkIn)
{
    this->checkIn = checkIn;
}

void Room::setCheckOut(QDate checkOut)
{
    this->checkOut = checkOut;
}


