#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlDatabase>
#include <QPushButton>
#include <vector>
#include "room.h"
#include "client.h"
#include "registerclient.h"
#include <groupbox.h>


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
signals:

public slots:
    void callRegisterWindow();
private:
    const int COLUMN_COUNT=6;
    QTableWidget *roomTable;
    QPushButton *registerButton;
    QPushButton *unregisterButton;
    std::vector<Room*> roomList;
    QSqlDatabase db;
    RegisterClient *registerClient;
    GroupBox *groupBox;

    void configureDatabase();
    void fillRoomClass();
    void fillQTableWidget();
};

#endif // MAINWINDOW_H
