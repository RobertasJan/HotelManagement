#ifndef RESERVATIONS_H
#define RESERVATIONS_H

#include <QDate>
#include <vector>

class Reservations
{
public:
    Reservations();
private:
    std::vector<QDate> resBegin;
    std::vector<QDate> resEnd;
};

#endif // RESERVATIONS_H
