#ifndef CALENDAR_H
#define CALENDAR_H

#include <QWidget>
#include <QSqlDatabase>
#include <vector>
#include "room.h"
#include "client.h"
#include "mainwindow.h"

namespace Ui {
class Calendar;
}

class MainWindow;

class Calendar : public QWidget
{
    Q_OBJECT

public:
    explicit Calendar(std::vector<Room*>*, std::vector<Client*>*, MainWindow *mainWindow, QWidget *parent = 0);
    ~Calendar();

private:
    Ui::Calendar *ui;
    std::vector<Client*> *clientList;
    QSqlDatabase db;
    MainWindow *mainWindow;

    void configureDatabase();
private slots:
    void refreshTable();
    void unregisterClient();
};

#endif // CALENDAR_H
