#ifndef TEST_H
#define TEST_H

#include <QDialog>
#include "generalfunctions.h"
namespace Ui {
class Test;
}

class Test : public QDialog
{
    Q_OBJECT

public:
    explicit Test(QWidget *parent = nullptr);
    ~Test();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Test *ui;
};

#endif // TEST_H
