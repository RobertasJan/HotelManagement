#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QDate>

class Room
{
public:
    Room(int, QString, bool, bool, QDate, QDate);
    int getRoomNumber() const;
    QString getRoomType() const;
    bool getIsFree() const;
    bool getIsClean() const;
    QDate getCheckIn() const;
    QDate getCheckOut() const;

    void setCheckIn(QDate);
    void setCheckOut(QDate);
private:
    int roomNumber;
    QString roomType;
    bool isFree;
    bool isClean;
    QDate checkIn;
    QDate checkOut;
};

#endif // ROOM_H
