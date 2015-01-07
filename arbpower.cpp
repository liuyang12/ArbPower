#include "arbpower.h"
#include "ui_arbpower.h"
#include <QDebug>
#include <math.h>
#include "functions.h"
#include "Taylor.h"
#include "powP.cpp"

ArbPower::ArbPower(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArbPower)
{
    ui->setupUi(this);
    this->resize(258, 182);
//    calculatePressed = false;
    // calculateButtun 初始化
    ui->calculateButton->setMouseTracking(true);
    ui->calculateButton->setStyleSheet("QPushButton{color: rgb(255, 255, 255);border-image: url(:/Res/button_calculate_normal.png);background-image: url(:/Res/kb.png);}"
                                       "QPushButton:hover{border-image: url(:/Res/button_calculate_hover.png);background-image: url(:/Res/kb.png);}"
                                       "QPushButton:pressed{border-image: url(:/Res/button_calculate_down.png);background-image: url(:/Res/kb.png);}"
                                       );
    // baseEdit 和 exponentEdit 进行数字范围限定
    ui->baseEdit->setValidator(new QDoubleValidator(0.0, 100.0, 20, this));     // 限定 baseEdit double型输入 x∈[0, 100]，超出范围则无法按下回车，但可以强制计算
    ui->exponentEdit->setValidator(new QDoubleValidator(0.0, 3.0, 20, this));   // 限定 exponentEdit double型输入 y∈[0, 3]，超出范围则无法按下回车，但可以强制计算
    connect(ui->baseEdit, SIGNAL(returnPressed()),ui->exponentEdit, SLOT(setFocus()));
    connect(ui->exponentEdit, SIGNAL(returnPressed()), this, SLOT(on_calculateButton_clicked()));
}

ArbPower::~ArbPower()
{
    delete ui;
}

void ArbPower::calculate()
{
    double x;   // 底数 base number
    double y;   // 指数 exponent number
    double ans; // 结果 answer
//    QString ansString;  // 结果字符串 answer string，方便在 LineEdit 中显示
    SciNumber ansSci;   // 科学计数法
    bool ok_x, ok_y;
    QString str_x, str_y;
    str_x = ui->baseEdit->text();
    str_y = ui->exponentEdit->text();
    if(str_x.isEmpty())
    {
        ui->baseSignLabel->clear();
        ui->exponentSignLabel->clear();
        ui->errorLabel->setText("底数不能为空！");
        return ;
    }
    if(str_y.isEmpty())
    {
        ui->baseSignLabel->clear();
        ui->exponentSignLabel->clear();
        ui->errorLabel->setText("指数不能为空！");
        return ;
    }
    x = str_x.toDouble(&ok_x);
    qDebug() << QString::number(ln_taylor(x), 'f', 15);
    qDebug() << QString::number(log(x), 'f', 15);
    y = str_y.toDouble(&ok_y);
    qDebug() << QString::number(exp_taylor(y), 'f', 15);
    qDebug() << QString::number(exp(y), 'f', 15);
    ui->errorLabel->clear();
    ui->baseSignLabel->setText("有效位数："+QString::number(getSignificants(str_x)));
    ui->exponentSignLabel->setText("有效位数："+QString::number(getSignificants(str_y)));
//    qDebug() << getSignificants("10221.21");
//    if(calculatePressed)
//    this->resize(558, 182);
    // 在进行计算之前需要校验 x, y 的合法性
    // 系统函数
    ans = pow(x, y);    // 此处利用了 math.h 的系统函数，只需要重写这个函数即可
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow->setText(QString::number(ansSci.a, 'g', 18));     // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel->setText(QString::number(ansSci.n));
    // 方法一 Taylor展开
    ans = power_taylor(x, y);
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow_2->setText(QString::number(ansSci.a, 'g', 18));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_2->setText(QString::number(ansSci.n));
    // 方法二
    ans = pow_ff(x, y);
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow_3->setText(QString::number(ansSci.a, 'g', 18));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_3->setText(QString::number(ansSci.n));
//    ansString = QString::number(ans, 'f', 10);
//    ui->answerShow_2->setText(ansString);
    // 验证 QString::number(); 为四舍五入的结果
    // 注意：此处若为 1.25 精确两位有效数字为 1.2 若为 1.250000000000001（16位有效数字），结果为 1.3
    qDebug() << QString::number(0.0012500000000000001, 'g', 2);         // 两位有效数字
}

void ArbPower::on_calculateButton_clicked()
{
    this->resize(613, 182);
    ArbPower::calculate();      // 计算
}

void ArbPower::on_baseEdit_textChanged(const QString &arg1)
{
    ui->baseSignLabel->setText("有效位数："+QString::number(getSignificants(arg1)));
    this->resize(258, 182);
//    calculatePressed = false;
//    ArbPower::calculate();      // 计算
}

void ArbPower::on_exponentEdit_textChanged(const QString &arg1)
{
    ui->exponentSignLabel->setText("有效位数："+QString::number(getSignificants(arg1)));
    this->resize(258, 182);
//    calculatePressed = false;
//    ArbPower::calculate();      // 计算
}
