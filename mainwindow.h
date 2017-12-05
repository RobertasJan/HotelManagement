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
#include "calendar.h" // Room reservation calendar
#include <groupbox.h> // Parent for one window mechanism

class RegisterClient;
class Calendar;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
signals:

public slots:
    void connectRefreshTable();
private:
    const int COLUMN_COUNT=4;
    QTableWidget *roomTable;
    QPushButton *registerButton;
    QPushButton *clientInfoButton;
    QPushButton *calendarButton;
    QPushButton *refreshButton;

    std::vector<Room*> roomList;
    std::vector<Client*> clientList;
    QSqlDatabase db;
    RegisterClient *registerClient;
    ClientInfo *clientInfo;
    Calendar *calendar;
    GroupBox *groupBox;

    void configureDatabase();
    void fillRoomClass();
    void fillClientClass();
    void fillQTableWidget();
private slots:
    void callRegisterWindow();
    void callClientWindow();
    void callCalendarWindow();
};

#endif // MAINWINDOW_H
