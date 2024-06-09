#include "createbankaccount.h"
#include "home.h"
#include "bankaccount.h"
#include "home.h"
#include "ui_createbankaccount.h"
#include <cstdlib>
#include <ctime>
#include <QSqlError>
#include <random>
#include <QDateTime>

CreateBankAccount::CreateBankAccount(QWidget *parent , const QString & username)
    : QDialog(parent)
    , ui(new Ui::CreateBankAccount) , m_username(username)
{
    ui->setupUi(this);

    QPixmap cursorPixmap(":/Images/curser icon.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    ui->cmBoxKind->addItem("Current") ; ui->cmBoxKind->addItem("Saving") ; ui->cmBoxKind->addItem("Loan") ;

    std::srand(std::time(nullptr));
}

QString CreateBankAccount::createUniqueCardNumber() {
    static QString firstNumber = "5859831" ;
    std::mt19937 engine(static_cast<unsigned long>(std::time(nullptr))) ;
    std::uniform_int_distribution<unsigned long> distribution(100000000 , 999999999) ;
    QSqlQuery query ;
    while (1) {
        QString code = firstNumber ;
        unsigned long randomNumber = distribution(engine) ;
        code.append(QString::number(randomNumber)) ;
        query.prepare("SELECT CardNumber FROM BankAccounts WHERE CardNumber = :cardnumber") ;
        query.bindValue(":cardnumber" , code) ;
        if(query.exec()) {
            if(!query.next()) return code ;
        }
    }
}

QString CreateBankAccount::createUniqueShebaNumber() {
    static QString firstNumber = "87011000" ;
    std::mt19937 engine(static_cast<unsigned long>(std::time(nullptr))) ;
    std::uniform_int_distribution<unsigned long long> distribution(1000000000000000 , 9999999999999999) ;
    QSqlQuery query ;
    while (1) {
        QString code = firstNumber ;
        unsigned long long randomNumber = distribution(engine) ;
        code.append(QString::number(randomNumber)) ;
        query.prepare("SELECT ShebaNumber FROM BankAccounts WHERE CardNumber = :shebanumber") ;
        query.bindValue(":shebanumber" , code) ;
        if(query.exec()) {
            if(!query.next()) return code ;
        }
    }
}

long long CreateBankAccount::createUniqueBankAccountNumber() {
    std::mt19937 engine(static_cast<unsigned long>(std::time(nullptr))) ;
    std::uniform_int_distribution<unsigned long long> distribution(1000000000 , 9999999999) ;
    QSqlQuery query ;
    while (1) {
        unsigned long long randomNumber = distribution(engine) ;
        query.prepare("SELECT BankAccountNumber FROM BankAccounts WHERE CardNumber = :bankaccountnumber") ;
        query.bindValue(":bankaccountnumber" , randomNumber) ;
        if(query.exec()) {
            if(!query.next()) return randomNumber ;
        }
    }
}

int CreateBankAccount::createRandomCVV2() {
    std::mt19937 engine(static_cast<unsigned long>(std::time(nullptr))) ;
    std::uniform_int_distribution<unsigned int> distribution(1000 , 9999) ;
    unsigned int randomNumber = distribution(engine) ;
    return randomNumber ;
}

int CreateBankAccount::createEcpirationDate() {
    QDateTime currentDateTime = QDateTime::currentDateTime() ;
    QDate currentDate = currentDateTime.date() ;
    int year = currentDate.year() + 3 ;
    int month = currentDate.month() ;
    int day = currentDate.day() ;
    QString expDate ;
    expDate.append(QString::number(year)) ;
    if(month >= 10) expDate.append(QString::number(month)) ;
    else {
        expDate.append('0') ;
        expDate.append(QString::number(month)) ;
    }
    if(day >= 10) expDate.append(QString::number(day)) ;
    else {
        expDate.append('0') ;
        expDate.append(QString::number(day)) ;
    }
    int finalDate = expDate.toInt() ;
    return finalDate ;

}

CreateBankAccount::~CreateBankAccount()
{
    delete ui ;
    m_db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void CreateBankAccount::on_btnCreate_clicked()
{
    bool correctMoney = false , correctCode = false , correctOptCode = false ;

    static QRegularExpression NotNum("\\D") ;

    if(ui->lnEdtMoney->text().isEmpty()) ui->lblMoneyWrong->setText("The field must not be empty") ;
    else if(ui->lnEdtMoney->text().contains(" ")) ui->lblMoneyWrong->setText("Don't enter space") ;
    else if(!checkCorrectAmount(ui->lnEdtMoney->text())) ui->lblMoneyWrong->setText("Do not enter letters or more than 2 decimal places") ;
    else if(ui->lnEdtMoney->text().toDouble() <= 50 || ui->lnEdtMoney->text().toDouble() > 3000)  ui->lblMoneyWrong->setText("Amount should be between 50 and 3000 $") ;
    else {
        ui->lblMoneyWrong->setText("") ;
        correctMoney = true ;
    }

    if(ui->lnEdtPass->text().isEmpty()) ui->lblPassWrong->setText("The field must not be empty") ;
    else if(ui->lnEdtPass->text().contains(" ")) ui->lblPassWrong->setText("Don't enter space") ;
    else if(ui->lnEdtPass->text().contains(NotNum)) ui->lblPassWrong->setText("Don't enter letters") ;
    else if(ui->lnEdtPass->text().length() != 4) ui->lblPassWrong->setText("Code must be 4 digits") ;
    else {
        ui->lblPassWrong->setText("") ;
        correctCode = true ;
    }

    if(ui->lnEdtFixPass->text().isEmpty()) {
        correctOptCode =  true ;
    }
    else {
        if(ui->lnEdtFixPass->text().contains(" ")) ui->lblFixPassWrong->setText("Don't enter space") ;
        else if(ui->lnEdtFixPass->text().contains(NotNum)) ui->lblFixPassWrong->setText("Don't enter letters") ;
        else if(ui->lnEdtFixPass->text().length() != 7) ui->lblFixPassWrong->setText("Code must be 7 digits") ;
        else {
            ui->lblFixPassWrong->setText("") ;
            correctOptCode = true ;
        }
    }
    if(correctMoney && correctCode && correctOptCode) {
        m_db = QSqlDatabase::addDatabase("QSQLITE") ;
        m_db.setDatabaseName("bankDB.sqlite") ;
        m_db.open() ;
        if(m_db.isOpen()) {
            QSqlQuery query ;
            query.exec("PRAGMA busy_timeout = 20000");
            query.prepare("INSERT INTO BankAccounts (Kind , CardNumber , ShebaNumber , BankAccountNumber , cvv2 , Inventory ,"
                          " FourDigitCode , SecondFixedPass , OwnerUsername , ExpirationDate) "
                          "VALUES (:kind , :cardnumber , :shebanumber , :bankaccountnumber , :cvv2 , :inventory ,"
                          " :fourdigitcode , :secondfixedpass , :ownerusername , :expirationDate) ") ;
            query.bindValue( ":kind" , ui->cmBoxKind->currentText()) ;
            query.bindValue( ":cardnumber" , createUniqueCardNumber()) ;
            query.bindValue( ":shebanumber" , createUniqueShebaNumber()) ;
            query.bindValue( ":bankaccountnumber" , createUniqueBankAccountNumber()) ;
            query.bindValue( ":cvv2" , createRandomCVV2()) ;
            query.bindValue( ":inventory" , dollarToCent(ui->lnEdtMoney->text())) ;
            query.bindValue( ":fourdigitcode" , ui->lnEdtPass->text().toInt()) ;
            query.bindValue( ":secondfixedpass" , ui->lnEdtFixPass->text().toInt()) ;
            query.bindValue( ":ownerusername" , m_username) ;
            query.bindValue( ":expirationDate" , createEcpirationDate()) ; // ********* ناتمام
            if(query.exec()) {
                QMessageBox::information(this, "Create Card", "Your Card was created!") ;
                Home * homePage = new Home(nullptr , m_username) ;
                homePage->show() ;
                this->close() ;
            }
            else {
                QMessageBox::warning(this, "Failed", query.lastError().text()) ;
            }
        }
    }
}


void CreateBankAccount::on_btnBack_clicked()
{
    Home * homePage = new Home(nullptr , m_username) ;
    homePage->show() ;
    this->close() ;
}

