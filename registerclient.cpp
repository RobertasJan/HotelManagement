#include "registerclient.h"
#include "ui_registerclient.h"
#include <QPalette>
#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>

RegisterClient::RegisterClient(std::vector<Room*> *roomList, MainWindow *mainWindow, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterClient)
{
    ui->setupUi(this);

    this->roomList = roomList;
    this->mainWindow = mainWindow;

    /* filling table widget and combobox with room information
     * fills with rooms which has no clients */

    fillRoomList();

    QDate currentDate;
    ui->dateBeginCalendar->setDate(currentDate.currentDate());
    ui->dateEndCalendar->setDate(currentDate.currentDate().addDays(1));

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

    /* updates room info according to client*/
    query.prepare("UPDATE room SET checkin = ?, checkout = ? WHERE roomnumber = ?");
    query.addBindValue(ui->dateBeginCalendar->date());
    query.addBindValue(ui->dateEndCalendar->date());
    query.addBindValue(ui->roomComboBox->currentText().toInt());
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
    QStringList headerLabels;
    headerLabels << "Kambario tipas" << "Kambario numeris" << "Tvarkingas";
    ui->roomTableWidget->setHorizontalHeaderLabels(headerLabels);
    std::vector<Room*>::iterator iter, end;
    int index=0;
    for (iter = roomList->begin(), end = roomList->end(); iter != end; ++iter) {
        if ((*iter)->getClientId()==0) {
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
