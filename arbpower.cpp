#include "arbpower.h"
#include "ui_arbpower.h"
#include <math.h>

ArbPower::ArbPower(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArbPower)
{
    ui->setupUi(this);
    // calculateButtun 初始化
    ui->calculateButton->setMouseTracking(true);
    ui->calculateButton->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border-image: url(:/Res/button_calculate_normal.png);background-image: url(:/Res/kb.png);}"
                                       "QPushButton:hover{border-image: url(:/Res/button_calculate_hover.png);background-image: url(:/Res/kb.png);}"
                                       "QPushButton:pressed{border-image: url(:/Res/button_calculate_down.png);background-image: url(:/Res/kb.png);}"
                                       );
}

ArbPower::~ArbPower()
{
    delete ui;
}

void ArbPower::on_calculateButton_clicked()
{
    double x;   // 底数 base number
    double y;   // 指数 exponent number
    double ans; // 结果 answer
    QString ansString;  // 结果字符串 answer string，方便在 LineEdit 中显示
    x = ui->baseEdit->text().toDouble();
    y = ui->exponentEdit->text().toDouble();
    // 在进行计算之前需要校验 x, y 的合法性
    ans = pow(x, y);    // 此处利用了 math.h 的系统函数，只需要重写这个函数即可

    ansString = QString::number(ans, 'f', 10);
    ui->answerShow->setText(ansString);

}
