#ifndef USER_H
#define USER_H
#include<QString>

class User
{
public:
    User(const QString & name , const QString & family , const QString & nationalCode , const QString & username ,
         const QString & password , const int & age) ;
    const QString & getName() const ;
    const QString & getFamily() const ;
    const QString & getNationalCode() const ;
    const QString & getUsername() const ;
    const QString & getPassword() const ;
    const int & getAge() const ;
    void setName(const QString & name) ;
    void setFamily(const QString & family) ;
    void setNationalCode(const QString & nationalCode) ;
    void setUsername(const QString & username) ;
    void setPassword(const QString & password) ;
    void setAge(const int & age) ;
private :
    QString m_name , m_family , m_nationalCode , m_username , m_password ;
    int m_age ;
} ;

#endif // USER_H
