#include "generalfunctions.h"

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
