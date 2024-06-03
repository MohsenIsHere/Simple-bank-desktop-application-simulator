#ifndef USER_H
#define USER_H
#include<string>

class User
{
public:
    User(const std::string & name , const std::string & family , const std::string & nationalCode , const std::string & username ,
         const std::string & password , const int & age) ;
    const std::string & getName() const ;
    const std::string & getFamily() const ;
    const std::string & getNationalCode() const ;
    const std::string & getUsername() const ;
    const std::string & getPassword() const ;
    const int & getAge() const ;
    void setName(const std::string & name) ;
    void setFamily(const std::string & family) ;
    void setNationalCode(const std::string & nationalCode) ;
    void setUsername(const std::string & username) ;
    void setPassword(const std::string & password) ;
    void setAge(const int & age) ;
private :
    std::string m_name , m_family , m_nationalCode , m_username , m_password ;
    int m_age ;
} ;

#endif // USER_H
