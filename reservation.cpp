#include "reservation.h"

Reservation::Reservation(int clientId, QDate checkIn, QDate checkOut)
{
    this->clientId = clientId;
    this->checkIn = checkIn;
    this->checkOut = checkOut;
}

int Reservation::getClientId() const
{
    return clientId;
}

QDate Reservation::getCheckIn() const
{
    return checkIn;
}

QDate Reservation::getCheckOut() const
{
    return checkOut;
}
