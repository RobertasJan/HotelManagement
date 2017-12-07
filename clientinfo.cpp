#include "clientinfo.h"
#include "ui_clientinfo.h"
#include <QDebug>

ClientInfo::ClientInfo(std::vector<Client*> clientList, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ClientInfo)
{
    ui->setupUi(this);

    ui->clientTable->setRowCount(clientList.size());

    // Fills clientTable with hotel clients info
    std::vector<Client*>::iterator iter, end;
    int index=0;
    for (iter = clientList.begin(), end = clientList.end(); iter != end; ++iter) {
        ui->clientTable->setItem(index, 0, new QTableWidgetItem(QString::number((*iter)->getId())));
        ui->clientTable->setItem(index, 1, new QTableWidgetItem((*iter)->getFirstName()));
        ui->clientTable->setItem(index, 2, new QTableWidgetItem((*iter)->getLastName()));
        ui->clientTable->setItem(index, 3, new QTableWidgetItem(QString::number((*iter)->getPassport())));
        ui->clientTable->setItem(index, 4, new QTableWidgetItem((*iter)->getInfo()));
        if ((*iter)->getDisturb() == true)
            ui->clientTable->setItem(index, 5, new QTableWidgetItem("Ne"));
        else
            ui->clientTable->setItem(index, 5, new QTableWidgetItem("Taip"));
        ui->clientTable->setItem(index, 6, new QTableWidgetItem(QString::number((*iter)->getRoomId())));
        index++;
    }

}

ClientInfo::~ClientInfo()
{
    delete ui;
}

