#include "calendar.h"
#include "ui_calendar.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

Calendar::Calendar(std::vector<Room*> *roomList, std::vector<Client*> *clientList, MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Calendar)
{
    ui->setupUi(this);
    this->mainWindow = mainWindow;
    this->clientList = clientList;

    ui->calendarTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->calendarTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // setting so items in table can be selected only one row
    ui->calendarTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->calendarTable->setSelectionMode(QAbstractItemView::SingleSelection);

    std::vector<Room*>::iterator iter, end;
    for (iter = roomList->begin(), end = roomList->end(); iter!=end; ++iter) {
        ui->roomComboBox->addItem(QString::number((*iter)->getRoomNumber()));
    }

    connect(ui->unregisterButton, SIGNAL(released()), this, SLOT(unregisterClient()));
    connect(ui->roomComboBox, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshTable()));
    refreshTable();
}

Calendar::~Calendar()
{
    delete ui;
}

void Calendar::configureDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hotelschema");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open())
        QMessageBox::warning(this, "Error", "Unable to connect to the database");
}

void Calendar::refreshTable()
{
    ui->calendarTable->clear();
    QStringList headerLabels;
    headerLabels << "Kliento ID" << "Kliento vardas" << "Kliento Pavardė" << "Rez pradžia" << "Rez pabaiga";
    ui->calendarTable->setHorizontalHeaderLabels(headerLabels);

    ui->calendarTable->setRowCount(0);

    std::vector<Client*>::iterator clientIter, clientEnd;
    std::vector<Reservation*>::iterator resIter, resEnd;

    int index=0;
    for (clientIter = clientList->begin(), clientEnd = clientList->end(); clientIter!=clientEnd; ++clientIter) {
        if ((*clientIter)->getRoomId() == ui->roomComboBox->currentText().toInt()) {
            std::vector<Reservation*> resList = (*clientIter)->getResList();
            for (resIter = resList.begin(), resEnd = resList.end(); resIter != resEnd; ++resIter) {
                ui->calendarTable->setRowCount(index+1);
                ui->calendarTable->setItem(index, 0, new QTableWidgetItem(QString::number((*clientIter)->getId())));
                ui->calendarTable->setItem(index, 1, new QTableWidgetItem((*clientIter)->getFirstName()));
                ui->calendarTable->setItem(index, 2, new QTableWidgetItem((*clientIter)->getLastName()));
                ui->calendarTable->setItem(index, 3, new QTableWidgetItem((*resIter)->getCheckIn().toString("yyyy-MM-dd")));
                ui->calendarTable->setItem(index, 4, new QTableWidgetItem((*resIter)->getCheckOut().toString("yyyy-MM-dd")));
                index++;
            }
        }
    }
}

void Calendar::unregisterClient()
{
    if (ui->calendarTable->selectionModel()->hasSelection()) {

        int index = ui->calendarTable->selectionModel()->selectedRows().first().row();
        int deleteId = ui->calendarTable->item(index, 0)->text().toInt();
       // qDebug () << deleteId;

        std::vector<Client*>::iterator clientIter, clientEnd;
        std::vector<Reservation*>::iterator resIter, resEnd;
        for (clientIter = clientList->begin(), clientEnd = clientList->end(); clientIter!=clientEnd; ++clientIter) {
            if ((*clientIter)->getId() == deleteId)
            {
                if ((*clientIter)->getResList().size() == 1)
                {
                    QDate begin = QDate::fromString(ui->calendarTable->item(index, 3)->text(), "yyyy-MM-dd");
                    QDate end = QDate::fromString(ui->calendarTable->item(index, 4)->text(), "yyyy-MM-dd");
                    QSqlQuery query;
                    query.prepare("DELETE FROM reservation WHERE checkin = ? and checkout = ?");
                    query.addBindValue(begin);
                    query.addBindValue(end);
                    query.exec();

                    query.prepare("DELETE FROM client WHERE id = ?");
                    query.addBindValue(deleteId);
                    query.exec();

                    mainWindow->connectRefreshTable();
                }
                else
                {
                    QDate begin = QDate::fromString(ui->calendarTable->item(index, 3)->text(), "yyyy-MM-dd");
                    QDate end = QDate::fromString(ui->calendarTable->item(index, 4)->text(), "yyyy-MM-dd");
                    std::vector<Reservation*> resList = (*clientIter)->getResList();
                    for (resIter = resList.begin(), resEnd = resList.end(); resIter != resEnd; ++resIter) {
                        if (begin == (*resIter)->getCheckIn() && end == (*resIter)->getCheckOut()) {
                            QSqlQuery query;
                            query.prepare("DELETE FROM reservation WHERE checkin = ? and checkout = ?");
                            query.addBindValue(begin);
                            query.addBindValue(end);
                            query.exec();

                            mainWindow->connectRefreshTable();
                        }
                    }
                }
            }
        }

        refreshTable();
    }
    else
        QMessageBox::warning(this, "Klaida", "Nepasirinktas klientas");
        return;
}

