#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTableWidget>
#include <QSqlDatabase>
#include <vector>
#include "room.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
private:
    const int COLUMN_COUNT=6;
    QTableWidget *roomTable;
    std::vector<Room*> roomList;
    QSqlDatabase db;

    void configureDatabase();
    void fillRoomClass();
    void fillQTableWidget();
};

#endif // MAINWINDOW_H
