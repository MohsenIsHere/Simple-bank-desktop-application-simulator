#ifndef HOME_H
#define HOME_H

#include "mlist.h"
#include "bankaccount.h"
#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

namespace Ui {
class Home;
}

class Home : public QDialog
{
    Q_OBJECT

public:
    explicit Home(QWidget *parent = nullptr , const QString & username = "") ;
    const MList<BankAccount> & getBankAccounts() const ;
    ~Home();

private:
    Ui::Home *ui ;
    QString m_username ;
    MList<BankAccount> m_bankAccounts ;
    QSqlDatabase m_db ;
    void loadBankAccounts() ;
};

#endif // HOME_H
