#ifndef HOME_H
#define HOME_H

#include "mlist.h"
#include "bankaccount.h"
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QtSql/QSqlQuery>
#include <QString>
#include <QCursor>
#include <QPixmap>
#include <QDialog>
#include <QFont>


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

private slots:
    void on_btnRightPtr_clicked();

    void on_btnLeftPtr_clicked();

private:
    Ui::Home *ui ;
    QString m_username ;
    MList<BankAccount> m_bankAccounts ;
    QSqlDatabase m_db ;
    int m_currentCardIndex ;
    QPropertyAnimation *animation;
    QGraphicsOpacityEffect *opacityEffect;
    void loadBankAccounts() ;
    void setCardInfo() ;
};

#endif // HOME_H
