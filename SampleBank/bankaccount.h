#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <QString>

class BankAccount
{
public :
    BankAccount(const QString & kind = "" , const QString & cardNumber = "" , const QString & shebaNumber = "" ,
                const QString & bankAccountNumber = "" , const QString & secondFixedPassword = "" ,
                const QString & ownerUsername = "" , const int & cvv2 = 0 , const int & fourDigitCode = 0 ,
                const int & secondDynamicPassword  = 0 , const int & expirationDate = 0 , const long long & inventory = 0) ;
    const QString & getKind() const ;
    const QString & getCardNumber() const ;
    const QString & getShebaNumber() const ;
    const QString & getBankAccountNumber() const ;
    const QString & getSecondFixedPassword() const ;
    const QString & getOwnerUsername() const ;
    const int & getCVV2() const ;
    const int & get4digitCode() const ;
    const int & getSecondDynamicPassword() const ;
    const int & getExpirationDate() const ;
    const long long & getInventory() const ;
    void setKind(const QString & kind) ;
    void setCardNumber(const QString & cardNumber) ;
    void setShebaNumber(const QString & shebaNumber) ;
    void setBankAccountNumber(const QString & bankAccountNumber) ;
    void setSecondFixedPassword(const QString & secondFixedPassword) ;
    void setOwnerUsername(const QString & ownerUsername) ;
    void setCVV2(const int & cvv2) ;
    void set4digitCode(const int & fourDigitCode) ;
    void setSecondDynamicPassword(const int & secondDynamicPassword) ;
    void setExpirationDate(const int & expirationDate) ;
    void setInventory(const int & inventory) ;
private :
    QString m_kind , m_cardNumber , m_shebaNumber , m_bankAccountNumber , m_secondFixedPassword , m_ownerUsername ;
    int m_cvv2 , m_4digitCode ,  m_secondDynamicPassword , m_expirationDate ;
    long long m_inventory ;
} ;

#endif // BANKACCOUNT_H
