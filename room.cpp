#include "room.h"

// constructs Room object
Room::Room(int roomNumber, QString roomType, bool isClean)
{
    this->roomNumber = roomNumber;
    this->roomType = roomType;
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

bool Room::getIsClean() const
{
    return isClean;
}



