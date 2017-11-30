#include "registerclient.h"
#include "ui_registerclient.h"
#include <QDebug>

RegisterClient::RegisterClient(std::vector<Room*> roomList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RegisterClient)
{
    ui->setupUi(this);

    /* filling table widget and combobox with room information
     * fills with rooms which has no clients */
    std::vector<Room*>::iterator iter, end;
    int index=0;
    for (iter = roomList.begin(), end = roomList.end(); iter != end; ++iter) {
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

    // connecting saveButton click to saveRegistration function
    connect(ui->saveButton,SIGNAL(released()),this,SLOT(saveRegistration()));



}

RegisterClient::~RegisterClient()
{
    delete ui;
}

void RegisterClient::saveRegistration()
{
    qDebug() << "Hello";
}
