#include "client.h"

Client::Client(int id, QString firstName, QString lastName, int passport, QString info, bool disturb)
    : Person(id, firstName, lastName)
{
    this->passport = passport;
    this->info = info;
    this->disturb = disturb;
}
