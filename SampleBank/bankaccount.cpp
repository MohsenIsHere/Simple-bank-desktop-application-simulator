#include "bankaccount.h"

BankAccount::BankAccount(const QString & kind , const QString & cardNumber , const QString & shebaNumber ,
                         const long long & bankAccountNumber , const int & secondFixedPassword ,
                         const QString & ownerUsername , const int & cvv2 , const int & fourDigitCode ,
                         const int & expirationDate , const QString & inventory) :
    m_kind(kind) , m_cardNumber(cardNumber) , m_shebaNumber(shebaNumber), m_ownerUsername(ownerUsername), m_inventory(inventory) ,
    m_cvv2(cvv2) , m_4digitCode(fourDigitCode) , m_secondFixedPassword(secondFixedPassword) ,
    m_expirationDate(expirationDate) , m_bankAccountNumber(bankAccountNumber) {}

const QString & BankAccount::getKind() const { return m_kind ; }

const QString & BankAccount::getCardNumber() const { return m_cardNumber ; }

const QString & BankAccount::getShebaNumber() const { return m_shebaNumber ; }

const QString & BankAccount::getInventory() const { return m_inventory ; }

const QString & BankAccount::getOwnerUsername() const { return m_ownerUsername ; }

const long long & BankAccount::getBankAccountNumber() const { return m_bankAccountNumber ; }

const int & BankAccount::getSecondFixedPassword() const { return m_secondFixedPassword ; }

const int & BankAccount::getCVV2() const { return m_cvv2 ; }

const int & BankAccount::get4digitCode() const { return m_4digitCode ; }

const int & BankAccount::getExpirationDate() const { return m_expirationDate ; }

void BankAccount::setKind(const QString & kind) { m_kind = kind ; }

void BankAccount::setCardNumber(const QString & cardNumber) { m_cardNumber = cardNumber ; }

void BankAccount::setShebaNumber(const QString & shebaNumber) { m_shebaNumber = shebaNumber ; }

void BankAccount::setInventory(const QString & inventory) { m_inventory = inventory ; }

void BankAccount::setOwnerUsername(const QString & ownerUsername) { m_ownerUsername = ownerUsername ; }

void BankAccount::setBankAccountNumber(const long long & bankAccountNumber) { m_bankAccountNumber = bankAccountNumber ; }

void BankAccount::setSecondFixedPassword(const int & secondFixedPassword) { m_secondFixedPassword = secondFixedPassword ; }

void BankAccount::setCVV2(const int & cvv2) { m_cvv2 = cvv2 ; }

void BankAccount::set4digitCode(const int & fourDigitCode) { m_4digitCode = fourDigitCode ; }

void BankAccount::setExpirationDate(const int & expirationDate) { m_expirationDate = expirationDate ; }

