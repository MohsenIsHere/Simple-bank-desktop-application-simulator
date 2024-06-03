#include "bankaccount.h"

BankAccount::BankAccount(const std::string & kind , const std::string & cardNumber , const std::string & shebaNumber ,
                         const std::string & bankAccountNumber , const std::string & secondFixedPassword ,
                         const std::string & ownerUsername , const int & cvv2 , const int & fourDigitCode ,
                         const int & secondDynamicPassword , const int & expirationDate , const long long & inventory) :
    m_kind(kind) , m_cardNumber(cardNumber) , m_shebaNumber(shebaNumber) , m_bankAccountNumber(bankAccountNumber) ,
    m_secondFixedPassword(secondFixedPassword) , m_ownerUsername(ownerUsername) , m_cvv2(cvv2) , m_4digitCode(fourDigitCode) ,
    m_secondDynamicPassword(secondDynamicPassword) , m_expirationDate(expirationDate) , m_inventory(inventory) {}
const std::string & BankAccount::getKind() const { return m_kind ; }
const std::string & BankAccount::getCardNumber() const { return m_cardNumber ; }
const std::string & BankAccount::getShebaNumber() const { return m_shebaNumber ; }
const std::string & BankAccount::getBankAccountNumber() const { return m_bankAccountNumber ; }
const std::string & BankAccount::getSecondFixedPassword() const { return m_secondFixedPassword ; }
const std::string & BankAccount::getOwnerUsername() const { return m_ownerUsername ; }
const int & BankAccount::getCVV2() const { return m_cvv2 ; }
const int & BankAccount::get4digitCode() const { return m_4digitCode ; }
const int & BankAccount::getSecondDynamicPassword() const { return m_secondDynamicPassword ; }
const int & BankAccount::getExpirationDate() const { return m_expirationDate ; }
const long long & BankAccount::getInventory() const { return m_inventory ; }
void BankAccount::setKind(std::string & kind) { m_kind = kind ; }
void BankAccount::setCardNumber(std::string & cardNumber) { m_cardNumber = cardNumber ; }
void BankAccount::setShebaNumber(std::string & shebaNumber) { m_shebaNumber = shebaNumber ; }
void BankAccount::setBankAccountNumber(std::string & bankAccountNumber) { m_bankAccountNumber = bankAccountNumber ; }
void BankAccount::setSecondFixedPassword(std::string & secondFixedPassword) { m_secondFixedPassword = secondFixedPassword ; }
void BankAccount::setOwnerUsername(std::string & ownerUsername) { m_ownerUsername = ownerUsername ; }
void BankAccount::setCVV2(int & cvv2) { m_cvv2 = cvv2 ; }
void BankAccount::set4digitCode(int & fourDigitCode) { m_4digitCode = fourDigitCode ; }
void BankAccount::setSecondDynamicPassword(int & secondDynamicPassword) { m_secondDynamicPassword = secondDynamicPassword ; }
void BankAccount::setExpirationDate(int & expirationDate) { m_expirationDate = expirationDate ; }
void BankAccount::setInventory(int & inventory) { m_inventory = inventory ; }
