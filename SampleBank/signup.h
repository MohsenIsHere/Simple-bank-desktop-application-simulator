#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCursor>
#include <QPixmap>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

private slots:
    void on_btnSignup_clicked();

private:
    Ui::SignUp *ui;
};

#endif // SIGNUP_H
