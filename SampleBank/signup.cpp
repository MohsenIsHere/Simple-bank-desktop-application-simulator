#include "signup.h"
#include "ui_signup.h"
#include "mainwindow.h"
#include <QRegularExpression>
#include <QMessageBox>
#include <QString>

SignUp::SignUp(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::SignUp)
{
    ui->setupUi(this);
}

SignUp::~SignUp()
{
    delete ui;
}

void SignUp::on_btnSignup_clicked()
{
    bool correctName = true , correctFamily = true , correctAge = true , correctNatCode = true , correctUsername = true , correctPass = true ;
    static QRegularExpression IsNum("\\d") , NotNum("\\D");

    // check input name :
    if(ui->lnEdtName->text().isEmpty()) {
        ui->lblWrongName->setText("This box should not be empty") ;
        correctName = false ;
    }
    else if(ui->lnEdtName->text().contains(IsNum) || ui->lnEdtName->text().contains(" ")) {
        ui->lblWrongName->setText("Name should not contain spaces or numbers") ;
        correctName = false ;
    }
    else {
        ui->lblWrongName->setText("") ;
        correctName = true ;
    }

    // check input famiyl :
    if(ui->lnEdtFamily->text().isEmpty()) {
        ui->lblWrongFamily->setText("This box should not be empty") ;
        correctFamily = false ;
    }
    else if(ui->lnEdtFamily->text().contains(IsNum) || ui->lnEdtFamily->text().contains(" ")) {
        ui->lblWrongFamily->setText("Family should not contain spaces or numbers") ;
        correctFamily = false ;
    }
    else {
        ui->lblWrongFamily->setText("") ;
        correctFamily = true ;
    }

    // check input age :
    if(ui->lnEdtAge->text().isEmpty()) {
        ui->lblWrongAge->setText("This box should not be empty") ;
        correctAge = false ;
    }
    else if(ui->lnEdtAge->text().contains(NotNum)) {
        ui->lblWrongAge->setText("Do not enter letters or spaces") ;
        correctAge = false ;
    }
    else if(ui->lnEdtAge->text().toInt() < 18 && ui->lnEdtAge->text().toInt() > 120) {
        ui->lblWrongAge->setText("Your age is not allowed") ;
        correctAge = false ;
    }
    else {
        ui->lblWrongAge->setText("") ;
        correctAge = true ;
    }

    // check input national code :
    if(ui->lnEdtNatCode->text().isEmpty()) {
        ui->lblWrongNatCode->setText("This box should not be empty") ;
        correctNatCode = false ;
    }
    else if(ui->lnEdtNatCode->text().contains(NotNum)) {
        ui->lblWrongNatCode->setText("Do not enter letters or spaces") ;
        correctNatCode = false ;
    }
    else if (ui->lnEdtNatCode->text().size() != 10) {
        ui->lblWrongNatCode->setText("National code is invalid") ;
        correctNatCode = false ;
    }
    else if (ui->lnEdtNatCode->text().toLongLong() < 1000000000  && ui->lnEdtNatCode->text().toLongLong() >= 10000000000) {
        ui->lblWrongNatCode->setText("National code is invalid") ;
        correctNatCode = false ;
    }
    else {
        ui->lblWrongNatCode->setText("") ;
        correctNatCode = true ;
    }

    // check input username :
    if(ui->lnEdtUser->text().isEmpty()) {
        ui->lblWrongUsername->setText("This box should not be empty") ;
        correctUsername = false ;
    }
    else if(ui->lnEdtUser->text().contains(" ")) {
        ui->lblWrongUsername->setText("Do not enter a space") ;
        correctUsername = false ;
    }
    else {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE") ;
        db.setDatabaseName("bankDB.sqlite") ;
        db.open() ;
        if(db.isOpen()) {
            QSqlQuery query ;
            query.prepare("SELECT Username FROM Users WHERE Username = :username") ;
            query.bindValue(":username" , ui->lnEdtUser->text()) ;
            query.exec() ;
            bool uniqueUsername = true ;
            while (query.next())
                uniqueUsername = false ;
            if(uniqueUsername) {
                ui->lblWrongUsername->setText("") ;
                correctUsername = true ;
            }
            else {
                ui->lblWrongUsername->setText("This username is already selected") ;
                correctUsername = false ;
            }
            db.close();
            QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        }
        else
        {
            QMessageBox::warning(this,"Not Connected","The database is not connected");
        }
    }

    // check input password :
    if(ui->lnEdtPass->text().isEmpty()) {
        ui->lblWrongPassword->setText("This box should not be empty") ;
        correctPass = false ;
    }
    else if(ui->lnEdtPass->text().contains(" ")) {
        ui->lblWrongPassword->setText("Do not enter a space") ;
        correctPass = false ;
    }
    else if(ui->lnEdtPass->text().size() < 8) {
        ui->lblWrongPassword->setText("Password must be more than 8 characters") ;
        correctPass = false ;
    }
    else if (!ui->lnEdtPass->text().contains(NotNum)) {
        ui->lblWrongPassword->setText("Password must include letters") ;
        correctPass = false ;
    }
    else if (!ui->lnEdtPass->text().contains(IsNum)) {
        ui->lblWrongPassword->setText("Password must include numbers") ;
        correctPass = false ;
    }
    else {
        ui->lblWrongPassword->setText("") ;
        correctPass = true ;
    }

    // check all input for allow to make account :
    if(correctName == true && correctFamily == true && correctAge == true &&
        correctNatCode == true && correctUsername == true && correctPass == true) {
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE") ;
        db.setDatabaseName("bankDB.sqlite") ;
        db.open() ;
        if(db.isOpen()) {
            QSqlQuery query ;
            query.prepare("INSERT INFO Users (Name , Family , Age , NationalCode , Username , Password)") ;
            // query.bindValue( ":name" , ui->lnEdtName->text()) ;
            // query.bindValue( ":family" , ui->lnEdtFamily->text()) ;
            // query.bindValue( ":age" , ui->lnEdtAge->text().toInt()) ;
            // query.bindValue( ":nationalcode" , ui->lnEdtNatCode->text()) ;
            // query.bindValue( ":username" , ui->lnEdtUser->text()) ;
            // query.bindValue( ":password" , ui->lnEdtPass->text()) ;
            query.addBindValue(ui->lnEdtName->text()) ;
            query.addBindValue(ui->lnEdtFamily->text()) ;
            query.addBindValue(ui->lnEdtAge->text().toInt()) ;
            query.addBindValue(ui->lnEdtNatCode->text()) ;
            query.addBindValue(ui->lnEdtUser->text()) ;
            query.addBindValue(ui->lnEdtPass->text()) ;
            if(query.exec()) {
                QMessageBox::information(this, "Saved", "Your data was saved successfully, please log in") ;
                MainWindow * loginPage = new MainWindow() ;
                loginPage->show() ;
                this->close() ;
            }
            else {
                QMessageBox::warning(this, "Failed", "Your data was not saved, please try again") ;
            }
            db.close();
            QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
        }
        else
        {
            QMessageBox::warning(this,"Not Connected","The database is not connected");
        }
    }
}

