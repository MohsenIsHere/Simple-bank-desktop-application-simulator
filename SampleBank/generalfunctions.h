#ifndef GENERALFUNCTIONS_H
#define GENERALFUNCTIONS_H
#include <QString>
#include <QRegularExpression>

bool checkNumbersAbsence(const QString & text) ;

bool checkNonNumericCharacterAbsence(const QString & text) ;

bool checkCorrectAmount(QString amount) ;

void deleteFirstZeros(QString & amount) ;

void reverseString(QString & str) ;
// ---------------------------------------------------------------
// Functions to convert information into a suitable display form :

QString insertSpaceToCardNum(QString cardNum) ;

QString insertSlashToExpirationDate(int expirationDate) ;

QString centToDollar(QString amount) ;

// ---------------------------------------------------------------
// Functions for calculations of very large numbers :

QString dollarToCent(QString amount) ;

QString plus(QString num1 , QString num2) ;

QString mines(QString num1 , QString num2) ;

// ---------------------------------------------------------------

#endif // GENERALFUNCTIONS_H
