#ifndef TRANSFERMONEY_H
#define TRANSFERMONEY_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include "bankaccount.h"
#include "home.h"
#include "mlist.h"

namespace Ui {
class TransferMoney;
}

class TransferMoney : public QDialog
{
    Q_OBJECT

public:
    explicit TransferMoney(QWidget *parent , const MList<BankAccount> & bankAccounts);
    ~TransferMoney();

private slots:
    void on_btnTransfer_clicked();

    void on_btnBack_clicked();

    void on_lnEdtFixPass_cursorPositionChanged(int arg1, int arg2);

    void on_btnSendPass_clicked();

private:
    Ui::TransferMoney * ui ;
    const MList<BankAccount> m_bankAccounts ;
    QSqlDatabase m_db ;
    int m_dynPass ;
    int currentDate() ;
    bool permissibilityTransactionCeiling(QString money) ;
    int makeSecondDynamicPass() ;
};

#endif // TRANSFERMONEY_H
