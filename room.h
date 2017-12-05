#ifndef ROOM_H
#define ROOM_H

#include <QString>

class Room
{
public:
    Room(int, QString, bool);
    int getRoomNumber() const;
    QString getRoomType() const;
    bool getIsClean() const;
private:
    int roomNumber;
    QString roomType;
    bool isClean;
};

#endif // ROOM_H
