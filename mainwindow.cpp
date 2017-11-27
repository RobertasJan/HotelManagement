#include "mainwindow.h"
#include <QTableView> // table for room
#include <QHeaderView> // table config
#include <QStringList> // headerList for table
#include <QMessageBox> // for warnings
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // setting size of mainWindow to x=800, y=600
    setFixedSize(800,600);

    // creating main room table (rows=0, columns=4, parent)
    roomTable = new QTableWidget(0,COLUMN_COUNT,this);
    // setting size and position;
    roomTable->setFixedSize(500,550);
    roomTable->move(50,30);
    // setting header labels
    QStringList headerLabels;
    headerLabels << "Kambario numeris" << "Kambario tipas" << "Laisvas" << "Tvarkingas";
    roomTable->setHorizontalHeaderLabels(headerLabels);
    // stretching columns to be width of widget
    roomTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    configureDatabase();

    roomTable->show();
}

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

void MainWindow::fillRoomClass()
{

}
