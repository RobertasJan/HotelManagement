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
    explicit RegisterClient(std::vector<Room*> *roomList, std::vector<Client*> *clientList, MainWindow *mainWindow, QWidget *parent = 0);
    ~RegisterClient();
private:
    Ui::RegisterClient *ui;
    bool checkDate();
    QSqlDatabase db;
    std::vector<Room*> *roomList;
    std::vector<Client*> *clientList;
    MainWindow *mainWindow;

    void configureDatabase();
private slots:
    void saveRegistration();
    void clearInputs();
    void fillRoomList();
};

#endif // REGISTERCLIENT_H
