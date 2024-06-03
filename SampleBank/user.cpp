#include "user.h"

User::User(const std::string & name , const std::string & family , const std::string & nationalCode , const std::string & username ,
           const std::string & password , const int & age) :
    m_name(name) , m_family(family) , m_nationalCode(nationalCode) , m_username(username) , m_password(password) , m_age(age) {}
const std::string & User::getName() const { return m_name ; }
const std::string & User::getFamily() const { return m_family ; }
const std::string & User::getNationalCode() const { return m_nationalCode ; }
const std::string & User::getUsername() const { return m_username ; }
const std::string & User::getPassword() const { return m_password ; }
const int & User::getAge() const { return m_age ; }
void User::setName(const std::string & name) { m_name = name ; }
void User::setFamily(const std::string & family) { m_family = family ; }
void User::setNationalCode(const std::string & nationalCode) { m_nationalCode = nationalCode ; }
void User::setUsername(const std::string & username) { m_username = username ; }
void User::setPassword(const std::string & password) { m_password = password ; }
void User::setAge(const int & age) { m_age = age ; }
