#ifndef ROOM_H
#define ROOM_H

#include <QString>

class Room
{
public:
    Room(int, QString, bool, bool);
    int getRoomNumber() const;
    QString getRoomType() const;
    bool getIsFree() const;
    bool getIsClean() const;
private:
    int roomNumber;
    QString roomType;
    bool isFree;
    bool isClean;
};

#endif // ROOM_H
