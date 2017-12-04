#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QPushButton>
#include <vector>
#include "room.h" // room info
#include "client.h" // client info
#include "registerclient.h" // Register Client widget for room registration
#include "clientinfo.h" // Client info widget with table
#include <groupbox.h> // Parent for one window mechanism

class RegisterClient;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
signals:

public slots:
    void connectRefreshTable();
private:
    const int COLUMN_COUNT=6;
    QTableWidget *roomTable;
    QPushButton *registerButton;
    QPushButton *unregisterButton;
    QPushButton *clientInfoButton;
    QPushButton *refreshButton;

    std::vector<Room*> roomList;
    std::vector<Client*> clientList;
    QSqlDatabase db;
    RegisterClient *registerClient;
    ClientInfo *clientInfo;
    GroupBox *groupBox;
    void configureDatabase();
    void fillRoomClass();
    void fillClientClass();
    void fillQTableWidget();
private slots:
    void unregisterClient();
    void callRegisterWindow();
    void callClientWindow();
};

#endif // MAINWINDOW_H
