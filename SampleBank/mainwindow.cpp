#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "signup.h"
#include "home.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent , const QString & username , const QString & password)
    : QMainWindow(parent) , ui(new Ui::MainWindow) , m_username(username), m_password(password)
{
    ui->setupUi(this) ;
    ui->lineEditPass->setText(password) ;
    ui->lineEditUser->setText(username) ;
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
    // check input username and password from database :
    if(ui->lineEditUser->text().isEmpty() || ui->lineEditPass->text().isEmpty()) ui->labelWrong->setText("fields must be filled") ;
    else if(ui->lineEditUser->text().contains(" ") || ui->lineEditPass->text().contains(" ")) ui->labelWrong->setText("Do not use space") ;
    else
    {
        bool wrong = true ;
        QSqlDatabase db = QSqlDatabase :: addDatabase("QSQLITE") ;
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
        else
        {
            QMessageBox::warning(this,"Not Connected","The database is not connected");
        }
        db.close();
        QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        if(!wrong) {
            Home * homePage = new Home(nullptr , ui->lineEditUser->text()) ;
            homePage->show() ;
            this->close() ;
        }
    }
}

