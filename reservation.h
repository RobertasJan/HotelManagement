#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDate>

class Reservation
{
public:
    Reservation(int, QDate, QDate);
    int getClientId() const;
    QDate getCheckIn() const;
    QDate getCheckOut() const;
private:
    int clientId;
    QDate checkIn;
    QDate checkOut;
};

#endif // RESERVATION_H
