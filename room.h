#ifndef ROOM_H
#define ROOM_H

#include <QString>
#include <QDate>

class Room
{
public:
    Room(int, QString, bool, QDate, QDate, int);
    int getRoomNumber() const;
    QString getRoomType() const;
    bool getIsClean() const;
    QDate getCheckIn() const;
    QDate getCheckOut() const;
    int getClientId() const;

    void setCheckIn(QDate);
    void setCheckOut(QDate);
    void setClientId(int);
private:
    int roomNumber;
    QString roomType;
    bool isClean;
    QDate checkIn;
    QDate checkOut;
    int clientId;
};

#endif // ROOM_H
