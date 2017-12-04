#ifndef REGISTERCLIENT_H
#define REGISTERCLIENT_H

#include <QWidget>
#include "mainwindow.h"
#include <QSqlDatabase>
#include <vector>
#include "room.h"

namespace Ui {
class RegisterClient;
}

class MainWindow;

class RegisterClient : public QWidget
{
    Q_OBJECT

public:
    explicit RegisterClient(std::vector<Room*> *roomList, MainWindow *mainWindow, QWidget *parent = 0);
    ~RegisterClient();
private:
    Ui::RegisterClient *ui;
    bool checkDate();
    QSqlDatabase db;
    std::vector<Room*> *roomList;
    MainWindow *mainWindow;

    void configureDatabase();
    void fillRoomList();
private slots:
    void saveRegistration();
    void clearInputs();
};

#endif // REGISTERCLIENT_H
