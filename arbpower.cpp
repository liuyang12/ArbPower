#include "arbpower.h"
#include "ui_arbpower.h"

ArbPower::ArbPower(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArbPower)
{
    ui->setupUi(this);
}

ArbPower::~ArbPower()
{
    delete ui;
}
