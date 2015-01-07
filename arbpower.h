#ifndef ARBPOWER_H
#define ARBPOWER_H

#include <QMainWindow>

namespace Ui {
class ArbPower;
}

class ArbPower : public QMainWindow
{
    Q_OBJECT

public:
    explicit ArbPower(QWidget *parent = 0);
    ~ArbPower();

private slots:
    void on_calculateButton_clicked();

    void on_baseEdit_textChanged(const QString &arg1);

    void on_exponentEdit_textChanged(const QString &arg1);

private:
    Ui::ArbPower *ui;
    void calculate(void);

//    bool calculatePressed;
};

#endif // ARBPOWER_H
