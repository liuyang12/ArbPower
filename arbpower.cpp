#include "arbpower.h"
#include "ui_arbpower.h"
#include <math.h>
#include "functions.h"  // 科学计数法 SciNumber 及其相关转换关系
#include "Taylor.h"     // Taylor 展开方法
#include "ode.h"        // 常微分方程初值问题解方法
#include "integral.h"   // 数值积分 - 龙贝格算法

#define SMALL_SIZE QSize(260, 322)
#define MIDDLE_SIZE QSize(896, 322)

ArbPower::ArbPower(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ArbPower)
{
    ui->setupUi(this);
    this->resize(SMALL_SIZE);
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
    if(StringtoSci(str_x).n < -307)
        x = 0;
    else
         x = str_x.toDouble(&ok_x);
    if(StringtoSci(str_y).n < -307)
        y = 0;
    else
        y = str_y.toDouble(&ok_y);
    ui->errorLabel->clear();
    ui->baseSignLabel->setText("有效位数："+QString::number(getSignificants(str_x)));
    ui->exponentSignLabel->setText("有效位数："+QString::number(getSignificants(str_y)));
    // 在进行计算之前需要校验 x, y 的合法性
    int prec = ui->prec_comboBox->currentText().toInt();    // 当前显示精度
    // 系统函数
    ans = pow(x, y);    // 此处利用了 math.h 的系统函数，只需要重写这个函数即可
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow->setText(QString::number(ansSci.a, 'g', prec));     // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel->setText(QString::number(ansSci.n));
//    // 方法一 Taylor展开
    ans = power_all(x, y, TAYLOR);
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow_2->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_2->setText(QString::number(ansSci.n));
    // 方法二 Taylor展开 - 科学计数法
//    ans = pow_ff(x, y);
    ansSci = power_sci(StringtoSci(str_x), StringtoSci(str_y), TAYLOR);      // 将浮点数转化为科学计数法
    ui->answerShow_3->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_3->setText(QString::number(ansSci.n));
//    // 方法三 Taylor展开
    ans = power_all(x, y, ODE);
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow_4->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_4->setText(QString::number(ansSci.n));
    // 方法四 Taylor展开 - 科学计数法
//    ans = pow_ff(x, y);
    ansSci = power_sci(StringtoSci(str_x), StringtoSci(str_y), ODE);      // 将浮点数转化为科学计数法
    ui->answerShow_5->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_5->setText(QString::number(ansSci.n));
//    // 方法五 数值微分 - 龙贝格算法
    ans = power_all(x, y, INTEGRAL);
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow_6->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_7->setText(QString::number(ansSci.n));
    // 方法六 数值微分 - 龙贝格算法 - 科学计数法
//    ans = pow_ff(x, y);
    ansSci = power_sci(StringtoSci(str_x), StringtoSci(str_y), INTEGRAL);      // 将浮点数转化为科学计数法
    ui->answerShow_7->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_6->setText(QString::number(ansSci.n));
//    // 方法七 方程求根
    ans = power_all(x, y, ROOT);
    ansSci = DoubletoSci(ans);      // 将浮点数转化为科学计数法
    ui->answerShow_8->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_8->setText(QString::number(ansSci.n));
    // 方法八 方程求根 - 科学计数法
//    ans = pow_ff(x, y);
    ansSci = power_sci(StringtoSci(str_x), StringtoSci(str_y), ROOT);      // 将浮点数转化为科学计数法
    ui->answerShow_9->setText(QString::number(ansSci.a, 'g', prec));   // 十位有效数字显示，小数点后九位
    ui->answerExponentlabel_9->setText(QString::number(ansSci.n));
}

void ArbPower::on_calculateButton_clicked()
{
    this->resize(MIDDLE_SIZE);
    ArbPower::calculate();      // 计算
}

void ArbPower::on_baseEdit_textChanged(const QString &arg1)
{
    ui->baseSignLabel->setText("有效位数："+QString::number(getSignificants(arg1)));
    this->resize(SMALL_SIZE);
//    calculatePressed = false;
//    ArbPower::calculate();      // 计算
    ui->statusBar->showMessage(QString("x = %1, y = %2, 结果显示精度：%3").arg(QString::number(ui->baseEdit->text().toDouble(), 'g', 5)).arg(QString::number(ui->exponentEdit->text().toDouble(), 'g', 5)).arg(ui->prec_comboBox->currentText()));
}

void ArbPower::on_exponentEdit_textChanged(const QString &arg1)
{
    ui->exponentSignLabel->setText("有效位数："+QString::number(getSignificants(arg1)));
    this->resize(SMALL_SIZE);
//    calculatePressed = false;
//    ArbPower::calculate();      // 计算
    ui->statusBar->showMessage(QString("x = %1, y = %2, 结果显示精度：%3").arg(QString::number(ui->baseEdit->text().toDouble(), 'g', 5)).arg(QString::number(ui->exponentEdit->text().toDouble(), 'g', 5)).arg(ui->prec_comboBox->currentText()));
}
//

void ArbPower::on_prec_comboBox_currentIndexChanged(int index)
{
    ArbPower::calculate();
    ui->statusBar->showMessage(QString("x = %1, y = %2, 结果显示精度：%3").arg(QString::number(ui->baseEdit->text().toDouble(), 'g', 5)).arg(QString::number(ui->exponentEdit->text().toDouble(), 'g', 5)).arg(ui->prec_comboBox->currentText()));
}

void ArbPower::on_action10_triggered()
{
    ui->prec_comboBox->setCurrentText("10");
}

void ArbPower::on_action14_triggered()
{
    ui->prec_comboBox->setCurrentText("14");
}

void ArbPower::on_action18_triggered()
{
    ui->prec_comboBox->setCurrentText("18");
}
