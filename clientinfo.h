#ifndef CLIENTINFO_H
#define CLIENTINFO_H

#include <QWidget>
#include <vector>
#include "client.h"

namespace Ui {
class ClientInfo;
}

class ClientInfo : public QWidget
{
    Q_OBJECT

public:
    explicit ClientInfo(std::vector<Client*>, QWidget *parent = 0);
    ~ClientInfo();
private:
    Ui::ClientInfo *ui;
};

#endif // CLIENTINFO_H
