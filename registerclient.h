#ifndef REGISTERCLIENT_H
#define REGISTERCLIENT_H

#include <QWidget>
#include <vector>
#include "room.h"

namespace Ui {
class RegisterClient;
}

class RegisterClient : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterClient(std::vector<Room*>,QWidget *parent = 0);
    ~RegisterClient();
private:
    Ui::RegisterClient *ui;
private slots:
    void saveRegistration();
};

#endif // REGISTERCLIENT_H
