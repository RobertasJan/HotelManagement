#include "mainwindow.h"
#include <QTableView> // table for room objects
//#include <QTableWidgetItem>
#include <QHeaderView> // table config
#include <QStringList> // headerList for table
#include <QMessageBox> // for warnings
#include <QSqlQuery> // query for database
#include <QDate> // checkIn and checkOut dates
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // setting size of mainWindow to x=800, y=600
    setFixedSize(800,600);

    // creating main room table (rows=0, columns=6, parent)
    roomTable = new QTableWidget(0,COLUMN_COUNT,this);

    // setting size and position;
    roomTable->setFixedSize(700,550);
    roomTable->move(50,30);

    /* setting header labels
     * roomNumber, roomType, isFree, isClean, checkIn, checkOut */
    QStringList headerLabels;
    headerLabels << "Kambario numeris" << "Kambario tipas" << "Laisvas" << "Tvarkingas"
                 << "Užsiregistravimas" << "Išsiregistravimas";
    roomTable->setHorizontalHeaderLabels(headerLabels);

    // stretching columns to be width of widget
    roomTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    roomTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    configureDatabase();

    // filling roomList vector && roomTable table
    fillRoomClass();
    fillQTableWidget();

    roomTable->show();
}

// Configuring database parameters for future query executions
void MainWindow::configureDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hotelschema");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open())
        QMessageBox::warning(this, "Error", "Unable to connect to the database");
}

/* Filling std::vector<Room> object with info from Database
 * Only one Database connection is made, therefore query uses it as default */
void MainWindow::fillRoomClass()
{
    QSqlQuery query;
    query.exec("SELECT * FROM room");
    while (query.next()) {
        int roomNumber = query.value(0).toInt();
        QString roomType = query.value(1).toString();
        bool isFree = query.value(2).toBool();
        bool isClean = query.value(3).toBool();
        QDate checkIn = query.value(4).toDate();
        QDate checkOut = query.value(5).toDate();
        roomList.push_back(new Room(roomNumber, roomType, isFree, isClean, checkIn, checkOut));
    }
}

void MainWindow::fillQTableWidget()
{
    // setting Row count to be size of vector roomList
    roomTable->setRowCount(roomList.size());

    std::vector<Room*>::iterator iter, end;
    int index;
    /* Filling table from vector roomList;
     * index - table row;
     * 1 - roomNumber, 2 - roomType 3 - isFree,
     * 4 - isClean, 5 - checkIn date, 6 - checkOut date; */
    for (iter = roomList.begin(), end = roomList.end(), index=0; iter != end; ++iter, ++index) {
        roomTable->setItem(index, 0, new QTableWidgetItem(QString::number((*iter)->getRoomNumber())));
        roomTable->setItem(index, 1, new QTableWidgetItem((*iter)->getRoomType()));
        if ((*iter)->getIsFree() == false)
            roomTable->setItem(index, 2, new QTableWidgetItem("false"));
        else
            roomTable->setItem(index, 2, new QTableWidgetItem("true"));
        if ((*iter)->getIsClean() == false)
            roomTable->setItem(index, 3, new QTableWidgetItem("false"));
        else
            roomTable->setItem(index, 3, new QTableWidgetItem("true"));
        roomTable->setItem(index, 4, new QTableWidgetItem((*iter)->getCheckIn().toString("yyyy-MM-dd")));
        roomTable->setItem(index, 5, new QTableWidgetItem((*iter)->getCheckOut().toString("yyyy-MM-dd")));
     //   qDebug() << (*iter)->getCheckIn();
    }
}
