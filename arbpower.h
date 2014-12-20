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

private:
    Ui::ArbPower *ui;
};

#endif // ARBPOWER_H
