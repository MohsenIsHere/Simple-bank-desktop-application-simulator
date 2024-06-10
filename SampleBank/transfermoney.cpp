#include "transfermoney.h"
#include "generalfunctions.h"
#include "ui_transfermoney.h"
#include <random>
#include <QTimer>
#include <QDateTime>

TransferMoney::TransferMoney(QWidget *parent , const MList<BankAccount> & bankAccounts)
    : QDialog(parent)
    , ui(new Ui::TransferMoney) , m_bankAccounts(bankAccounts)
{
    ui->setupUi(this) ;

    QPixmap cursorPixmap(":/Images/curser icon.png");
    QCursor customCursor(cursorPixmap);
    setCursor(customCursor);

    m_db = QSqlDatabase::addDatabase("QSQLITE") ;
    m_db.setDatabaseName("bankDB.sqlite") ;
    m_db.open() ;

    for(int i = 0 ; i < m_bankAccounts.getSize() ; i++) ui->cmbOriginCards->addItem(insertSpaceToCardNum(m_bankAccounts[i]->getData().getCardNumber())
                                    + "    " + centToDollar(m_bankAccounts[i]->getData().getInventory()) + "$") ;

}

int TransferMoney::currentDate() {
    QDateTime currentDateTime = QDateTime::currentDateTime() ;
    QDate currentDate = currentDateTime.date() ;
    int year = currentDate.year() ;
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

bool TransferMoney::permissibilityTransactionCeiling(QString money) {
    if(m_db.isOpen()) {
        QSqlQuery query ;
        int index = ui->cmbOriginCards->currentIndex() ;
        QString sumMoney = "0"  , minDate = QString::number(currentDate()) + "000001" , maxDate = QString::number(currentDate()) + "235959" ;
        query.prepare("SELECT MoneyTransfer , Date FROM Transactions WHERE CardNumber = :cardnumber") ;
        query.bindValue(":cardnumber" , m_bankAccounts[index]->getData().getCardNumber()) ;
        if(query.exec()) {
            while (query.next()) {
                if(comparisonNumbers(query.value("Date").toString() , minDate) && comparisonNumbers(maxDate , query.value("Date").toString()))
                    sumMoney = plus(sumMoney , dollarToCent(query.value("MoneyTransfer").toString())) ;
            }
        }
        sumMoney = plus(sumMoney , dollarToCent(dollarToCent(money))) ;
        if(comparisonNumbers(sumMoney , "30000000")) return false ;
        else return true ;
    }
    return 0 ;
}

int TransferMoney::makeSecondDynamicPass() {
    std::mt19937 engine(static_cast<unsigned long>(std::time(nullptr))) ;
    std::uniform_int_distribution<unsigned int> distribution(1000000 , 9999999) ;
    QSqlQuery query ;
    while (1) {
        unsigned int randomNumber = distribution(engine) ;
        query.prepare("SELECT SecondDynamicPass , Date FROM Transactions WHERE SecondDynamicPass = :seconddynamicpass") ;
        query.bindValue(":seconddynamicpass" , randomNumber) ;
        if(query.exec()) {
            bool check = true ;
            while(query.next()) {
                if(!(comparisonNumbers(mines(createTransactionDate() , query.value("Date").toString()) , "200"))) {
                    check = false ;
                    break ;
                }
            }
            if(check) return randomNumber ;
        }
    }
}

TransferMoney::~TransferMoney()
{
    delete ui ;
    m_db.close();
    QSqlDatabase::removeDatabase(QSqlDatabase::defaultConnection);
}

void TransferMoney::on_btnTransfer_clicked()
{
    bool correctAimCard = false , correctAmount = false , correctExpDate = false , correctFixPass = false , correctDynamicPass = false ;

    static QRegularExpression NotNum("\\D") ;

    // ----------------------------------------------
    // check correct Aim Card Number :
    if(ui->lnEdtAimCard->text().isEmpty()) {
        ui->lblAimCardWrong->setText("This field should not be empty") ;
        correctAimCard = false ;
    }
    else if(ui->lnEdtAimCard->text().contains(NotNum)) {
        ui->lblAimCardWrong->setText("Do not enter letters") ;
        correctAimCard = false ;
    }
    else if(ui->lnEdtAimCard->text().contains(" ")) {
        ui->lblAimCardWrong->setText("Do not enter space") ;
        correctAimCard = false ;
    }
    else if(ui->lnEdtAimCard->text().length() != 16) {
        ui->lblAimCardWrong->setText("Card number is 16 digits") ;
        correctAimCard = false ;
    }
    else {
        if(m_db.isOpen()) {
            QSqlQuery query ;
            query.prepare("SELECT CardNumber FROM BankAccounts WHERE CardNumber = :cardnumber") ;
            query.bindValue(":cardnumber" , ui->lnEdtAimCard->text()) ;
            if(query.exec()) {
                if(!query.next()) {
                    ui->lblAimCardWrong->setText("The card is invalid") ;
                    correctAimCard = false ;
                }
                else {
                    int index = ui->cmbOriginCards->currentIndex() ;
                    QString crdNum = query.value(0).toString() ;
                    if(crdNum == m_bankAccounts[index]->getData().getCardNumber()) {
                        ui->lblAimCardWrong->setText("The origin and destination are the same") ;
                        correctAimCard = false ;
                    }
                    else {
                        ui->lblAimCardWrong->setText("") ;
                        query.prepare("SELECT OwnerUsername FROM BankAccounts WHERE CardNumber = :cardnumber") ;
                        query.bindValue(":cardnumber" , ui->lnEdtAimCard->text()) ; query.exec() ;
                        QString username ;
                        if(query.next()) username = query.value(0).toString() ;
                        query.prepare("SELECT Name , Family FROM Users WHERE UserName = :username") ;
                        query.bindValue(":username" , username) ; query.exec() ;
                        while (query.next()) ui->lblName->setText(query.value("Name").toString() + " " + query.value("Family").toString()) ;
                        correctAimCard = true ;
                    }
                }
            }
        }
    }
    // -----------------------------------------------
    // check correct ExpDate :
    int index = ui->cmbOriginCards->currentIndex() ;
    if(m_bankAccounts[index]->getData().getExpirationDate() < currentDate()) {
        ui->lblDateWrong->setText("The card has expired") ;
        correctExpDate = false ;
    }
    else {
        ui->lblDateWrong->setText("") ;
        correctExpDate = true ;
    }
    // ------------------------------------------------
    // check correct amount :
    if(ui->lnEdtAmount->text().isEmpty()) {
        ui->lblAmountWrong->setText("The field must not be empty") ;
        correctAmount = false ;
    }
    else if(ui->lnEdtAmount->text().contains(" ")) {
        ui->lblAmountWrong->setText("Don't enter space") ;
        correctAmount = false ;
    }
    else if(!checkCorrectAmount(ui->lnEdtAmount->text())){
        ui->lblAmountWrong->setText("Do not enter letters or more than 2 decimal places") ;
        correctAmount = false ;
    }
    else {
        int index = ui->cmbOriginCards->currentIndex() ;
        QString withdrawalAmount = dollarToCent(dollarToCent(ui->lnEdtAmount->text())) ,
            availableAmount = dollarToCent(m_bankAccounts[index]->getData().getInventory()) ;
        if(comparisonNumbers(withdrawalAmount , "30000000")) {
            ui->lblAmountWrong->setText("limit of each transaction is 3000$") ;
            correctAmount = false ;
        }
        else if(!permissibilityTransactionCeiling(ui->lnEdtAmount->text())) {
            ui->lblAmountWrong->setText("The daily limit is 6000$") ;
            correctAmount = false ;
        }
        else if(comparisonNumbers(withdrawalAmount , availableAmount)) {
            ui->lblAmountWrong->setText("Insufficient inventory") ;
            correctAmount = false ;
        }
        else {
            ui->lblAmountWrong->setText("") ;
            correctAmount = true ;
        }
    }
    // ------------------------------------------------
    // check correct fix pass :
    QSqlQuery checkFixpass ;
    int element = ui->cmbOriginCards->currentIndex() ;
    checkFixpass.prepare("SELECT SecondFixedPass FROM BankAccounts WHERE CardNumber = :cardnumber") ;
    checkFixpass.bindValue(":cardnumber" , m_bankAccounts[element]->getData().getCardNumber()) ;
    if(checkFixpass.exec()){
        if(checkFixpass.next()){
            if(checkFixpass.value(0) != 0) {
                if(comparisonNumbers("1000" , dollarToCent(ui->lnEdtAmount->text()))) {
                    ui->lnEdtFixPass->setEnabled(true) ;
                    correctFixPass = true ;
                }
                else {
                    ui->lnEdtFixPass->setDisabled(true) ;
                    correctFixPass = false ;
                }
            }
            else {
                ui->lnEdtFixPass->setDisabled(true) ;
                correctFixPass = false ;
            }
        }
    }
    if(correctFixPass){
        if(ui->lnEdtFixPass->text().isEmpty()) {
            ui->lblFixPassWrong->setText("") ;
            correctFixPass = false ;
        }
        else if(ui->lnEdtFixPass->text().contains(NotNum)) {
            ui->lblFixPassWrong->setText("Do not enter letters") ;
            correctFixPass = false ;
        }
        else if(ui->lnEdtFixPass->text().contains(" ")) {
            ui->lblFixPassWrong->setText("Do not enter space") ;
            correctFixPass = false ;
        }
        else if(ui->lnEdtFixPass->text().length() != 7) {
            ui->lblFixPassWrong->setText("Fixed pass is 7 digits") ;
            correctFixPass = false ;
        }
        else {
            QSqlQuery checkFixpass ;
            int element = ui->cmbOriginCards->currentIndex() ;
            checkFixpass.prepare("SELECT SecondFixedPass FROM BankAccounts WHERE CardNumber = :cardnumber") ;
            checkFixpass.bindValue(":cardnumber" , m_bankAccounts[element]->getData().getCardNumber()) ;
            if(checkFixpass.exec()){
                if(checkFixpass.next()){
                    if(checkFixpass.value(0) == ui->lnEdtFixPass->text().toInt()) correctFixPass = true ;
                    else correctFixPass = false ;
                }
            }
        }
    }
    // --------------------------------------------------------
    // check correct dynamic pass :
    if(ui->lnEdtDynamicPass->text().isEmpty()) {
        ui->lblDynamicPassWrong->setText("The field must not be empty") ;
        correctDynamicPass = false ;
    }
    else if(ui->lnEdtDynamicPass->text().contains(NotNum)) {
        ui->lblDynamicPassWrong->setText("Do not enter letters") ;
        correctDynamicPass = false ;
    }
    else if(ui->lnEdtDynamicPass->text().contains(" ")) {
        ui->lblDynamicPassWrong->setText("Do not enter space") ;
        correctDynamicPass = false ;
    }
    else if(ui->lnEdtDynamicPass->text().length() != 7) {
        ui->lblDynamicPassWrong->setText("Fixed pass is 7 digits") ;
        correctDynamicPass = false ;
    }
    else if(ui->lnEdtDynamicPass->text() != QString::number(m_dynPass)) {
        ui->lblDynamicPassWrong->setText("Second Dynamic Pass is wrong") ;
        correctDynamicPass = false ;
    }
    else {
        ui->lblDynamicPassWrong->setText("") ;
        correctDynamicPass = true ;
    }

    // --------------------------------------------------------
    // set to database :
    if(correctAimCard && correctAmount && correctExpDate && (correctDynamicPass || correctFixPass)) {
        // Reduce fees :
        QString wage = dollarToCent(calculationOfTransactionPercentage(dollarToCent(ui->lnEdtAmount->text()))) ;
        QString finalTransferCentCentAmount = mines(dollarToCent(dollarToCent(ui->lnEdtAmount->text())) , wage) ;
        // -----------------------------------------------------
        if(m_db.isOpen()) {
            QSqlQuery query , changeMoneyOrigin , changeMoneyAim;
            query.prepare("INSERT INTO Transactions (CardNumber , MoneyTransfer , Date , SecondDynamicPass) "
                          "VALUES (:cardnumber , :moneytransfer , :date , :seconddynamicpass) ") ;
            int indx = ui->cmbOriginCards->currentIndex() ;
            query.bindValue( ":cardnumber" , m_bankAccounts[indx]->getData().getCardNumber()) ;
            query.bindValue( ":moneytransfer" , dollarToCent(ui->lnEdtAmount->text())) ;
            query.bindValue( ":date" , createTransactionDate()) ;
            query.bindValue( ":seconddynamicpass" , m_dynPass) ;
            // ---------------------------------------------------------------------

            changeMoneyOrigin.prepare("SELECT Inventory FROM BankAccounts WHERE CardNumber = :cardnumber") ;
            changeMoneyOrigin.bindValue( ":cardnumber" , m_bankAccounts[indx]->getData().getCardNumber()) ;
            QString increase ;
            if(changeMoneyOrigin.exec()){
                if(changeMoneyOrigin.next()) increase = mines(dollarToCent(changeMoneyOrigin.value(0).toString()) , dollarToCent(dollarToCent(ui->lnEdtAmount->text()))) ;
                increase = centToDollar(increase) ;
            }
            changeMoneyOrigin.prepare("UPDATE BankAccounts SET Inventory = :inventory WHERE CardNumber = :cardnumber") ;
            changeMoneyOrigin.bindValue( ":inventory" , increase) ;
            changeMoneyOrigin.bindValue( ":cardnumber" , m_bankAccounts[indx]->getData().getCardNumber()) ;

            // ---------------------------------------------------------------------

            changeMoneyAim.prepare("SELECT Inventory FROM BankAccounts WHERE CardNumber = :cardnumber") ;
            changeMoneyAim.bindValue( ":cardnumber" , ui->lnEdtAimCard->text()) ;
            QString decrease ;
            if(changeMoneyAim.exec()){
                if(changeMoneyAim.next()) decrease = plus(dollarToCent(changeMoneyAim.value(0).toString()) , finalTransferCentCentAmount) ;
                decrease = centToDollar(decrease) ;
            }
            changeMoneyAim.prepare("UPDATE BankAccounts SET Inventory = :inventory WHERE CardNumber = :cardnumber") ;
            changeMoneyAim.bindValue( ":inventory" , decrease) ;
            changeMoneyAim.bindValue( ":cardnumber" , ui->lnEdtAimCard->text()) ;

            //----------------------------------------------------------------------

            if(query.exec() && changeMoneyOrigin.exec() && changeMoneyAim.exec()) {
                QMessageBox::information(this, "Success", "The money was deposited successfully") ;
                Home * homePage = new Home(nullptr , m_bankAccounts[0]->getData().getOwnerUsername()) ;
                homePage->show() ;
                this->close() ;
            }
            else QMessageBox::warning(this, "Failed", "Your data was not saved please try again") ;
        }
    }
}

void TransferMoney::on_btnBack_clicked()
{
    QMessageBox msgBox;
    msgBox.setWindowTitle("Confirmation");
    msgBox.setText("Sure?second password will be reset...");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    msgBox.setDefaultButton(QMessageBox::No);
    int ans = msgBox.exec();
    switch (ans) {
    case QMessageBox::Yes:{
        Home * homePage = new Home(nullptr , m_bankAccounts[0]->getData().getOwnerUsername()) ;
        homePage->show() ;
        this->close() ;
        break;
    }
    case QMessageBox::No:
        break;
    }

}

void TransferMoney::on_lnEdtFixPass_cursorPositionChanged(int arg1, int arg2)
{
    // QSqlQuery checkFixpass ;
    // int element = ui->cmbOriginCards->currentIndex() ;
    // checkFixpass.prepare("SELECT SecondFixedPass FROM BankAccounts WHERE CardNumber = :cardnumber") ;
    // checkFixpass.bindValue(":cardnumber" , m_bankAccounts[element]->getData().getCardNumber()) ;
    // if(checkFixpass.exec()){
    //     if(checkFixpass.next()){
    //         if(checkFixpass.value(0) != 0) {
    //             if(comparisonNumbers("1000" , dollarToCent(ui->lnEdtAmount->text()))) ui->lnEdtFixPass->setEnabled(true) ;
    //             else ui->lnEdtFixPass->setEnabled(false) ;
    //         }
    //         else ui->lnEdtFixPass->setEnabled(false) ;
    //     }
    // }
}


void TransferMoney::on_btnSendPass_clicked()
{
    m_dynPass = makeSecondDynamicPass() ;
    ui->lnEdtDynamicPass->setText(QString::number(m_dynPass)) ;
    ui->btnSendPass->setEnabled(false) ;
    QTimer::singleShot(10000, [this]() {
        ui->btnSendPass->setEnabled(true) ;
        ui->lnEdtDynamicPass->setText("") ;
        m_dynPass = 0 ;
    });
}

