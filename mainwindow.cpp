#include "mainwindow.h"
#include <QTableView> // table for room objects
#include <QHeaderView> // table config
#include <QStringList> // headerList for table
#include <QMessageBox> // for warnings
#include <QSqlQuery> // query for database
#include <QDate> // checkIn and checkOut dates
#include <QDebug>
#include "person.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // setting size of mainWindow to x=800, y=600
    setFixedSize(1250,600);

    // creating main room table (rows=0, columns=6, parent)
    roomTable = new QTableWidget(0,COLUMN_COUNT,this);

    // setting size and position;
    roomTable->setFixedSize(650,550);
    roomTable->move(30,20);

    /* setting header labels
     * roomNumber, roomType, isClean, checkIn, checkOut, clientId */
    QStringList headerLabels;
    headerLabels << "Kambario numeris" << "Kambario tipas" << "Tvarkingas"
                 << "Užsiregistravimas" << "Išsiregistravimas" << "Kliento ID";
    roomTable->setHorizontalHeaderLabels(headerLabels);

    // stretching columns to be width of widget
    roomTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    roomTable->setEditTriggers(QAbstractItemView::NoEditTriggers);

    // creating RegisterButton for registering clients
    registerButton = new QPushButton("Registruoti klientą", this);
    registerButton-> setFixedSize(100,30);
    registerButton->move(690,20);
    connect(registerButton, SIGNAL(released()), this, SLOT(callRegisterWindow()));

    unregisterButton = new QPushButton("Išregistruoti klientą", this);
    unregisterButton->setFixedSize(100,30);
    unregisterButton->move(690,60);

    //creating groupBox for future use
    groupBox = new GroupBox(this);
    groupBox->hide();

    configureDatabase();

    // filling roomList vector && roomTable table
    fillRoomClass();
    fillQTableWidget();

    registerButton->show();
    roomTable->show();
}

void MainWindow::callRegisterWindow()
{
    /* deleting groupbox to prevent memory leak
     * it also delets children widgets, releasing memory*/
    delete groupBox;
    GroupBox *groupBox = new GroupBox(this);
    groupBox->setTitle("Kliento registracija");
    groupBox->move(800,20);
    groupBox->show();
    // making registerClient children of groupBox, for memory control
    registerClient = new RegisterClient(groupBox);
    registerClient->move(10,20);
    registerClient->show();
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
        bool isClean = query.value(2).toBool();
        QDate checkIn = query.value(3).toDate();
        QDate checkOut = query.value(4).toDate();
        int clientId = query.value(5).toInt();
        roomList.push_back(new Room(roomNumber, roomType, isClean, checkIn, checkOut, clientId));
    }
}

void MainWindow::fillQTableWidget()
{
    // setting Row count to be size of vector roomList
    roomTable->setRowCount(roomList.size());

    /* Filling table from vector roomList;
     * index - table row;
     * 0 - roomNumber, 1 - roomType, 2 - isClean,
     * 3 - checkIn date, 4 - checkOut date, 5 - clientId */
    std::vector<Room*>::iterator iter, end;
    int index;
    for (iter = roomList.begin(), end = roomList.end(), index=0; iter != end; ++iter, ++index) {
        roomTable->setItem(index, 0, new QTableWidgetItem(QString::number((*iter)->getRoomNumber())));
        roomTable->setItem(index, 1, new QTableWidgetItem((*iter)->getRoomType()));
        if ((*iter)->getIsClean() == false)
            roomTable->setItem(index, 2, new QTableWidgetItem("Ne"));
        else
            roomTable->setItem(index, 2, new QTableWidgetItem("Taip"));
        roomTable->setItem(index, 3, new QTableWidgetItem((*iter)->getCheckIn().toString("yyyy-MM-dd")));
        roomTable->setItem(index, 4, new QTableWidgetItem((*iter)->getCheckOut().toString("yyyy-MM-dd")));
        roomTable->setItem(index, 5, new QTableWidgetItem(QString::number((*iter)->getClientId())));
    }
}
