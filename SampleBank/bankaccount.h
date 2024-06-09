#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <QString>

class BankAccount
{
public :
    BankAccount(const QString & kind = "" , const QString & cardNumber = "" , const QString & shebaNumber = "" ,
                const long long & bankAccountNumber = 0 , const int & secondFixedPassword = 0 ,
                const QString & ownerUsername = "" , const int & cvv2 = 0 , const int & fourDigitCode = 0 ,
                const int & expirationDate = 0 , const QString & inventory = "") ;
    const QString & getKind() const ;
    const QString & getCardNumber() const ;
    const QString & getShebaNumber() const ;
    const QString & getOwnerUsername() const ;
    const QString & getInventory() const ;
    const long long & getBankAccountNumber() const ;
    const int & getSecondFixedPassword() const ;
    const int & getCVV2() const ;
    const int & get4digitCode() const ;
    const int & getExpirationDate() const ;
    void setKind(const QString & kind) ;
    void setCardNumber(const QString & cardNumber) ;
    void setShebaNumber(const QString & shebaNumber) ;
    void setInventory(const QString & inventory) ;
    void setOwnerUsername(const QString & ownerUsername) ;
    void setBankAccountNumber(const long long & bankAccountNumber) ;
    void setSecondFixedPassword(const int & secondFixedPassword) ;
    void setCVV2(const int & cvv2) ;
    void set4digitCode(const int & fourDigitCode) ;
    void setExpirationDate(const int & expirationDate) ;
private :
    QString m_kind , m_cardNumber , m_shebaNumber , m_ownerUsername , m_inventory ;
    int m_cvv2 , m_4digitCode , m_secondFixedPassword , m_expirationDate ;
    long long m_bankAccountNumber ;
} ;

#endif // BANKACCOUNT_H
