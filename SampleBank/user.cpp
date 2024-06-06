#include "user.h"

User::User(const QString & name , const QString & family , const QString & nationalCode , const QString & username ,
           const QString & password , const int & age) :
    m_name(name) , m_family(family) , m_nationalCode(nationalCode) , m_username(username) , m_password(password) , m_age(age) {}
const QString & User::getName() const { return m_name ; }
const QString & User::getFamily() const { return m_family ; }
const QString & User::getNationalCode() const { return m_nationalCode ; }
const QString & User::getUsername() const { return m_username ; }
const QString & User::getPassword() const { return m_password ; }
const int & User::getAge() const { return m_age ; }
void User::setName(const QString & name) { m_name = name ; }
void User::setFamily(const QString & family) { m_family = family ; }
void User::setNationalCode(const QString & nationalCode) { m_nationalCode = nationalCode ; }
void User::setUsername(const QString & username) { m_username = username ; }
void User::setPassword(const QString & password) { m_password = password ; }
void User::setAge(const int & age) { m_age = age ; }
