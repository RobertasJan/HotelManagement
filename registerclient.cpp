#include "registerclient.h"
#include "ui_registerclient.h"
#include <QPalette>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

RegisterClient::RegisterClient(std::vector<Room*> *roomList, std::vector<Client*> *clientList, MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterClient)
{
    ui->setupUi(this);

    this->roomList = roomList;
    this->clientList = clientList;
    this->mainWindow = mainWindow;

    QDate currentDate;
    ui->dateBeginCalendar->setDate(currentDate.currentDate());
    ui->dateEndCalendar->setDate(currentDate.currentDate().addDays(1));

    /* filling table widget and combobox with room information
     * fills with rooms which has no clients */
    connect(ui->dateBeginCalendar, SIGNAL(userDateChanged(QDate)),this, SLOT(fillRoomList()));
    connect(ui->dateEndCalendar, SIGNAL(userDateChanged(QDate)), this, SLOT(fillRoomList()));
    fillRoomList();


    ui->idField->setValidator(new QIntValidator(1, 9999, this));
    ui->passportField->setValidator(new QIntValidator(1, 99999999, this));

    // connecting saveButton click to saveRegistration function
    connect(ui->saveButton,SIGNAL(released()),this,SLOT(saveRegistration()));
    connect(ui->clearButton, SIGNAL(released()), this, SLOT(clearInputs()));

    QPalette palette = ui->warningDate->palette();
    palette.setColor(ui->warningDate->foregroundRole(), Qt::red);
    ui->warningDate->setPalette(palette);
    ui->warningInfo->setPalette(palette);
}

RegisterClient::~RegisterClient()
{
    delete ui;
}

void RegisterClient::saveRegistration()
{

    if (!checkDate())
        return;

    if (ui->extraInfo->toPlainText().length() >= 160) {
        ui->warningInfo->setText("Per ilgas tekstas");
        return;
    } else if (ui->idField->text().length() == 0) {
        QMessageBox::warning(this, "Klaida", "Neįvestas ID");
        return;
    } else if (ui->firstNameField->text().length() == 0) {
        QMessageBox::warning(this, "Klaida", "Neįvestas Vardas");
        return;
    } else if (ui->lastNameField->text().length() == 0) {
        QMessageBox::warning(this, "Klaida", "Neįvesta Pavardė");
        return;
    } else if (ui->passportField->text().length() == 0) {
        QMessageBox::warning(this, "Klaida", "Neįvestas paso kodas");
        return;
    }

    ui->warningInfo->setText("");

    /* Inserts Client info into database */
    QSqlQuery query;
    query.prepare("INSERT INTO client (id, firstname, lastname, passport, info, disturb, roomid)"
                  "VALUES (?, ?, ?, ?, ?, ?, ?)");
    query.addBindValue(ui->idField->text().toInt());
    query.addBindValue(ui->firstNameField->text());
    query.addBindValue(ui->lastNameField->text());
    query.addBindValue(ui->passportField->text().toInt());
    query.addBindValue(ui->extraInfo->toPlainText());
    query.addBindValue(!ui->disturbCheckBox->isChecked());
    query.addBindValue(ui->roomComboBox->currentText().toInt());
    query.exec();


   // Adds reservation to reservation table in database
    query.prepare("INSERT INTO reservation (clientid, checkin, checkout)"
                  "VALUES (?, ?, ?)");
    query.addBindValue(ui->idField->text().toInt());
    query.addBindValue(ui->dateBeginCalendar->date());
    query.addBindValue(ui->dateEndCalendar->date());
    query.exec();

    // Erases booked room from free rooms list
    std::vector<Room*>::iterator iter, end;
    int index=0;
    for (iter = roomList->begin(), end = roomList->end(); iter != end; ++iter) {
        if ((*iter)->getRoomNumber()==ui->roomComboBox->currentText().toInt()) {
            roomList->erase(roomList->begin() + index);
        }
        index++;
    }

    ui->roomComboBox->clear();
    ui->roomTableWidget->clear();

    fillRoomList();

    //Refreshing client. room vectors and main room table
    mainWindow->connectRefreshTable();
}

// Input Fields and other client Data
void RegisterClient::clearInputs()
{
    ui->idField->clear();
    ui->firstNameField->clear();
    ui->lastNameField->clear();
    ui->passportField->clear();
    ui->extraInfo->clear();
    if (ui->disturbCheckBox->isChecked())
        ui->disturbCheckBox->toggle();
    QDate currentDate;
    ui->dateBeginCalendar->setDate(currentDate.currentDate());
    ui->dateEndCalendar->setDate(currentDate.currentDate().addDays(1));
}

// Checks whether date is valid
bool RegisterClient::checkDate()
{
    if (ui->dateBeginCalendar->date() > ui->dateEndCalendar->date()) {
        ui->warningDate->setText("Netinkama data");
        return false;
    } else {
        ui->warningDate->setText("");
        return true;
    }
}

void RegisterClient::configureDatabase()
{
    db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");
    db.setDatabaseName("hotelschema");
    db.setUserName("root");
    db.setPassword("");
    if (!db.open())
        QMessageBox::warning(this, "Error", "Unable to connect to the database");
}

// Fills free room Table and free room comboBox with room info
void RegisterClient::fillRoomList()
{
    ui->roomComboBox->clear();
    QStringList headerLabels;
    headerLabels << "Kambario tipas" << "Kambario numeris" << "Tvarkingas";
    ui->roomTableWidget->setHorizontalHeaderLabels(headerLabels);
    std::vector<Client*>::iterator clientIter, clientEnd;
    std::vector<Reservation*>::iterator resIter, resEnd;

    QList<int> notFreeRooms;
    for (clientIter = clientList->begin(), clientEnd = clientList->end(); clientIter != clientEnd; ++clientIter) {
        std::vector<Reservation*> resList = (*clientIter)->getResList();
        for (resIter = resList.begin(), resEnd = resList.end(); resIter != resEnd; ++resIter) {
            /* checks whether checkin and checkout dates are not reserved
             * it also implies that on same day client checks out before another client comes in */
            if (
                (ui->dateBeginCalendar->date() >= (*resIter)->getCheckIn() && ui->dateBeginCalendar->date() < (*resIter)->getCheckOut())
                ||
                (ui->dateEndCalendar->date() > (*resIter)->getCheckIn() && ui->dateEndCalendar->date() <= (*resIter)->getCheckOut())
                ||
                (ui->dateBeginCalendar->date() < (*resIter)->getCheckIn() && ui->dateEndCalendar->date() > (*resIter)->getCheckOut())
               )
                notFreeRooms.push_back((*clientIter)->getRoomId());

        }
    }

    //Fills table with free rooms list
    std::vector<Room*>::iterator iter, end;

    int index=0;
    for (iter = roomList->begin(), end = roomList->end(); iter != end; ++iter) {
        if (!notFreeRooms.contains((*iter)->getRoomNumber())) {
            ui->roomTableWidget->setRowCount(index+1);
            ui->roomComboBox->addItem(QString::number((*iter)->getRoomNumber()));
            ui->roomTableWidget->setItem(index, 0, new QTableWidgetItem(QString::number((*iter)->getRoomNumber())));
            ui->roomTableWidget->setItem(index, 1, new QTableWidgetItem((*iter)->getRoomType()));
            if ((*iter)->getIsClean() == false)
                ui->roomTableWidget->setItem(index, 2, new QTableWidgetItem("Ne"));
            else
                ui->roomTableWidget->setItem(index, 2, new QTableWidgetItem("Taip"));
            index++;
        }
    }

}
