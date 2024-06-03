#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H
#include <string>

class BankAccount
{
public :
    BankAccount(const std::string & kind , const std::string & cardNumber , const std::string & shebaNumber ,
                const std::string & bankAccountNumber , const std::string & secondFixedPassword ,
                const std::string & ownerUsername , const int & cvv2 , const int & fourDigitCode ,
                const int & secondDynamicPassword , const int & expirationDate , const long long & inventory) ;
    const std::string & getKind() const ;
    const std::string & getCardNumber() const ;
    const std::string & getShebaNumber() const ;
    const std::string & getBankAccountNumber() const ;
    const std::string & getSecondFixedPassword() const ;
    const std::string & getOwnerUsername() const ;
    const int & getCVV2() const ;
    const int & get4digitCode() const ;
    const int & getSecondDynamicPassword() const ;
    const int & getExpirationDate() const ;
    const long long & getInventory() const ;
    void setKind(std::string & kind) ;
    void setCardNumber(std::string & cardNumber) ;
    void setShebaNumber(std::string & shebaNumber) ;
    void setBankAccountNumber(std::string & bankAccountNumber) ;
    void setSecondFixedPassword(std::string & secondFixedPassword) ;
    void setOwnerUsername(std::string & ownerUsername) ;
    void setCVV2(int & cvv2) ;
    void set4digitCode(int & fourDigitCode) ;
    void setSecondDynamicPassword(int & secondDynamicPassword) ;
    void setExpirationDate(int & expirationDate) ;
    void setInventory(int & inventory) ;
private :
    std::string m_kind , m_cardNumber , m_shebaNumber , m_bankAccountNumber , m_secondFixedPassword , m_ownerUsername ;
    int m_cvv2 , m_4digitCode ,  m_secondDynamicPassword , m_expirationDate ;
    long long m_inventory ;
} ;

#endif // BANKACCOUNT_H
