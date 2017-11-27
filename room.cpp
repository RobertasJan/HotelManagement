#include "room.h"

// constructs Room object
Room::Room(int roomNumber, QString roomType, bool isFree, bool isClean)
{
    this->roomNumber = roomNumber;
    this->roomType = roomType;
    this->isFree = isFree;
    this->isClean = isClean;
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


