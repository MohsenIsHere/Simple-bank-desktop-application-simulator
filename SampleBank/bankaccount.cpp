#include "bankaccount.h"

BankAccount::BankAccount(const QString & kind , const QString & cardNumber , const QString & shebaNumber ,
                         const QString & bankAccountNumber , const QString & secondFixedPassword ,
                         const QString & ownerUsername , const int & cvv2 , const int & fourDigitCode ,
                         const int & secondDynamicPassword , const int & expirationDate , const long long & inventory) :
    m_kind(kind) , m_cardNumber(cardNumber) , m_shebaNumber(shebaNumber) , m_bankAccountNumber(bankAccountNumber) ,
    m_secondFixedPassword(secondFixedPassword) , m_ownerUsername(ownerUsername) , m_cvv2(cvv2) , m_4digitCode(fourDigitCode) ,
    m_secondDynamicPassword(secondDynamicPassword) , m_expirationDate(expirationDate) , m_inventory(inventory) {}

const QString & BankAccount::getKind() const { return m_kind ; }

const QString & BankAccount::getCardNumber() const { return m_cardNumber ; }

const QString & BankAccount::getShebaNumber() const { return m_shebaNumber ; }

const QString & BankAccount::getBankAccountNumber() const { return m_bankAccountNumber ; }

const QString & BankAccount::getSecondFixedPassword() const { return m_secondFixedPassword ; }

const QString & BankAccount::getOwnerUsername() const { return m_ownerUsername ; }

const int & BankAccount::getCVV2() const { return m_cvv2 ; }

const int & BankAccount::get4digitCode() const { return m_4digitCode ; }

const int & BankAccount::getSecondDynamicPassword() const { return m_secondDynamicPassword ; }

const int & BankAccount::getExpirationDate() const { return m_expirationDate ; }

const long long & BankAccount::getInventory() const { return m_inventory ; }

void BankAccount::setKind(const QString & kind) { m_kind = kind ; }

void BankAccount::setCardNumber(const QString & cardNumber) { m_cardNumber = cardNumber ; }

void BankAccount::setShebaNumber(const QString & shebaNumber) { m_shebaNumber = shebaNumber ; }

void BankAccount::setBankAccountNumber(const QString & bankAccountNumber) { m_bankAccountNumber = bankAccountNumber ; }

void BankAccount::setSecondFixedPassword(const QString & secondFixedPassword) { m_secondFixedPassword = secondFixedPassword ; }

void BankAccount::setOwnerUsername(const QString & ownerUsername) { m_ownerUsername = ownerUsername ; }

void BankAccount::setCVV2(const int & cvv2) { m_cvv2 = cvv2 ; }

void BankAccount::set4digitCode(const int & fourDigitCode) { m_4digitCode = fourDigitCode ; }

void BankAccount::setSecondDynamicPassword(const int & secondDynamicPassword) { m_secondDynamicPassword = secondDynamicPassword ; }

void BankAccount::setExpirationDate(const int & expirationDate) { m_expirationDate = expirationDate ; }

void BankAccount::setInventory(const int & inventory) { m_inventory = inventory ; }

QString BankAccount::insertSpaceToCardNum() const {
    QString crdNum ;
    for(int i = 1 ; i <= 16 ; i++) {
        crdNum.push_back(m_cardNumber[i - 1]) ;
        if(i % 4 == 0) crdNum.push_back(" ") ;
    }
    return crdNum ;
}

QString BankAccount::insertSlashToExpirationDate() const {
    QString date , expirationDate = QString::number(m_expirationDate) ;
    for(int i = 1 ; i <= 6 ; i++) {
        date.push_back(expirationDate[i - 1]) ;
        if(i % 4 == 0) date.push_back("/") ;
    }
    return date ;
}

QString BankAccount::centToDollar() const {
    long double dollar = m_inventory ;
    dollar /= 100.00 ;
    char buffer[24] ;
    sprintf(buffer, "%.2Lf", dollar) ;
    QString strDollar = QString(buffer) ;
    return  strDollar ;
}
