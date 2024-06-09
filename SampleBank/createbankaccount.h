#ifndef CREATEBANKACCOUNT_H
#define CREATEBANKACCOUNT_H

#include "generalfunctions.h"
#include <QDialog>
#include <QRegularExpression>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class CreateBankAccount;
}

class CreateBankAccount : public QDialog
{
    Q_OBJECT

public:
    explicit CreateBankAccount(QWidget *parent = nullptr , const QString & username = "");
    ~CreateBankAccount();

private slots:
    void on_btnCreate_clicked();

    void on_btnBack_clicked();

private:
    Ui::CreateBankAccount * ui ;
    QString m_username ;
    QSqlDatabase m_db ;
    QString createUniqueCardNumber() ;
    QString createUniqueShebaNumber() ;
    long long createUniqueBankAccountNumber() ;
    int createRandomCVV2() ;
    int createEcpirationDate() ;


};

#endif // CREATEBANKACCOUNT_H
