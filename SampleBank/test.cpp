#include "test.h"
#include "ui_test.h"
#include "generalfunctions.h"
Test::Test(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Test)
{
    ui->setupUi(this);
}

Test::~Test()
{
    delete ui;
}

void Test::on_pushButton_clicked()
{
    QString n1 = ui->lineEdit->text() , n2 = ui->lineEdit_2->text() ;
    QString res = mines(n1 , n2) ;
    ui->label->setText(res) ;
}

