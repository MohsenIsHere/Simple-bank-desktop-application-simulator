#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase :: addDatabase("QSQLITE") ;
    db.setDatabaseName("mydb.sqlite") ;
    db.open() ;
    if(db.isOpen()) ui->labelMessage->setText("YES") ;
    else ui->labelMessage->setText("NO") ;

}

MainWindow::~MainWindow()
{
    delete ui;
}
