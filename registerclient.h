#ifndef REGISTERCLIENT_H
#define REGISTERCLIENT_H

#include <QWidget>

namespace Ui {
class RegisterClient;
}

class RegisterClient : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterClient(QWidget *parent = 0);
    ~RegisterClient();
private:
    Ui::RegisterClient *ui;
};

#endif // REGISTERCLIENT_H
