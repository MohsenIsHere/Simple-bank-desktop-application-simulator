#include "generalfunctions.h"
#include <QDateTime>

bool checkNumbersAbsence(const QString & text) {
    static QRegularExpression re("\\d") ;
    QRegularExpressionMatch match = re.match(text) ;
    if(match.hasMatch()) return true ;
    else return false ;
}
bool checkNonNumericCharacterAbsence(const QString & text) {
    static QRegularExpression re("\\D") ;
    QRegularExpressionMatch match = re.match(text) ;
    if(match.hasMatch()) return true ;
    else return false ;
}
bool checkCorrectAmount(QString amount) {
    static QRegularExpression NotNum("\\D") ;
    if(amount.contains(NotNum)) {
        if(amount[0] == '.') return false ;
        int countDat = 0 ;
        for(int i = 0 ; i < amount.length() ; i++) {
            if(amount[i] == '.') {
                countDat ++ ;
                if(countDat > 1) return false ;
                if(amount.length() - 1 - i > 2 || amount.length() - 1 - i == 0) return false ;
            }
            else if (!amount[i].isDigit()) return false ;
        }
        return true ;
    }
    else return true ;
    return 0 ;
}
void deleteFirstZeros(QString & amount) {
    int count = 0 ;
    while (count < amount.length() && amount[count] == '0') count ++ ;
    if(count < amount.length() && count != 0 && amount[count] == '.') count -- ;
    while (count --) amount.erase(0) ;
}

void reverseString(QString & str) {
    QString revStr ;
    int len = str.length();
    for (int i = len - 1 ; i >= 0; --i) revStr.push_back(str[i]) ;
    str = revStr ;
}

QString createTransactionDate() {
    QDateTime currentDateTime = QDateTime::currentDateTime() ;
    QDate currentDate = currentDateTime.date() ;
    int year = currentDate.year() ;
    int month = currentDate.month() ;
    int day = currentDate.day() ;
    QTime currentTime = currentDateTime.time() ;
    int hour = currentTime.hour() ;
    int minute = currentTime.minute() ;
    int second = currentTime.second() ;
    QString date ;
    date.append(QString::number(year)) ;
    if(month >= 10) date.append(QString::number(month)) ;
    else {
        date.append('0') ;
        date.append(QString::number(month)) ;
    }
    if(day >= 10) date.append(QString::number(day)) ;
    else {
        date.append('0') ;
        date.append(QString::number(day)) ;
    }
    if(hour >= 10) date.append(QString::number(hour)) ;
    else {
        date.append('0') ;
        date.append(QString::number(hour)) ;
    }
    if(minute >= 10) date.append(QString::number(minute)) ;
    else {
        date.append('0') ;
        date.append(QString::number(minute)) ;
    }
    if(second >= 10) date.append(QString::number(second)) ;
    else {
        date.append('0') ;
        date.append(QString::number(second)) ;
    }
    return date ;
}

// ---------------------------------------------------------------
// Functions to convert information into a suitable display form :

QString insertSpaceToCardNum(QString cardNum) {
    cardNum.insert( 4, ' ') ;
    cardNum.insert(9 , ' ') ;
    cardNum.insert(14 , ' ') ;
    return cardNum ;
}

QString insertSlashToExpirationDate(int expirationDate) {
    QString expDate = QString::number(expirationDate) ;
    expDate.insert(4 , '/') ;
    expDate.insert(7 , '/') ;
    return expDate ;
}

QString centToDollar(QString amount) {
    static QRegularExpression NotNum("\\D") ;
    if(!amount.contains(NotNum)) {
    if(amount.length() > 2) amount.insert(amount.length() - 2 , '.') ;
    else if(amount.length() == 2) amount.prepend("0.") ;
    else if(amount.length() == 1) amount.prepend("0.0") ;
    }else{
        amount.remove(amount.length() - 3 , 1) ;
        amount.insert(amount.length() - 4 , '.') ;
    }
    return amount ;
}

//-----------------------------------------------------------------
// Functions for calculations of very large numbers :

bool comparisonNumbers(QString num1 , QString num2) {
    if(num1.length() > num2.length()) return true ;
    else if (num1.length() < num2.length()) return false ;
    else {
        int len = num1.length() ;
        for(int i = 0 ; i < len ; i++) {
            if(num1[i].digitValue() > num2[i].digitValue()) return true ;
            else if(num1[i].digitValue() < num2[i].digitValue()) return false ;
        }
    }
    return false ;
}

QString calculationOfTransactionPercentage(QString amount) {
    if(amount.length() == 1) amount.prepend("0.0") ;
    else if (amount.length() == 2) amount.prepend("0.") ;
    else amount.insert(amount.length() - 2 , '.') ;
    return amount ;
}

QString dollarToCent(QString amount) {
    static QRegularExpression NotNum("\\D") ;
    if(amount.contains(NotNum)) {
        int datIndex = 0 , len = amount.length() ;
        for(int i = 0 ; i < len ; i++) {
            if(amount[i] == '.') {
                datIndex = i ;
                break ;
            }
        }
        amount.remove(datIndex , 1) ;
        if(len - 1 - datIndex == 1) amount.append('0') ;
    }
    else amount.append("00") ;
    return amount ;
}

QString plus(QString num1 , QString num2) {
    QString res ;
    if(num1.length() < num2.length()) {
        QString mover = num1 ;
        num1 = num2 ;
        num2 = mover ;
    }
    int len1 = num1.length() , len2 = num2.length() , pluss , add = 0 ;
    reverseString(num1) ; reverseString(num2) ;
    for(int i = 0 ; i < len1 ; i++) {

        if(i < len2) pluss = num1[i].digitValue() + num2[i].digitValue() + add ;
        else pluss = num1[i].digitValue() + add ;

        if(pluss >= 10) {
            pluss -= 10 ;
            add = 1 ;
        }
        else add = 0 ;
        res.push_front(QChar('0' + pluss)) ;
    }
    if(add) res.push_front('1') ;
    return res ;
}

QString mines(QString num1 , QString num2) {
    QString res ;
    if(num1.length() < num2.length()) {
        QString mover = num1 ;
        num1 = num2 ;
        num2 = mover ;
    }
    else if(num1.length() == num2.length()) {
        int len = num1.length() ;
        for(int i = 0 ; i < len ; i++) {
            if(num1[i].digitValue() > num2[i].digitValue()) break ;
            else if (num1[i].digitValue() < num2[i].digitValue()){
                QString mover = num1 ;
                num1 = num2 ;
                num2 = mover ;
            }
        }
    }
    int len1 = num1.length() , len2 = num2.length() , miness , add = 0 ;
    reverseString(num1) ; reverseString(num2) ;
    for(int i = 0 ; i < len1 ; i++) {

        if(i < len2) miness = num1[i].digitValue() - num2[i].digitValue() + add ;
        else miness = num1[i].digitValue() + add ;

        if(miness < 0) {
            miness += 10 ;
            add = -1 ;
        }
        else add = 0 ;
        res.push_front(QChar('0' + miness)) ;
    }
    return res ;


}

// ---------------------------------------------------------------
