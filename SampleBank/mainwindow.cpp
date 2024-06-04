#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btnSignUp_clicked()
{
    SignUp * signupPage = new SignUp() ;
    signupPage->show() ;
    this->close() ;
}


void MainWindow::on_pushButtonLog_clicked()
{
    bool wrong = true ;
    db = QSqlDatabase :: addDatabase("QSQLITE") ;
    db.setDatabaseName("bankDB.sqlite") ;
    db.open() ;
    if(db.isOpen()) {
        QSqlQuery query;
        query.prepare("SELECT Password From Users WHERE Username = :username");
        query.bindValue(":username" , ui->lineEditUser->text()) ;
        query.exec() ;
        while(query.next()) {
            if(query.value(0).toString() != ui->lineEditPass->text())
                ui->labelWrong->setText("password is incorrect") ;
            else ui->labelWrong->setText("") ;
            wrong = false ;
        }
        if(wrong) ui->labelWrong->setText("username not exist") ;
    }
    db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

