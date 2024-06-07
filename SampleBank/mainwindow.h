#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QCursor>
#include <QPixmap>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr , const QString & username = "" , const QString & password = "");
    ~MainWindow();

private slots:
    void on_btnSignUp_clicked();

    void on_pushButtonLog_clicked();

private:
    Ui::MainWindow *ui ;
    QString m_username ;
    QString m_password ;
};
#endif // MAINWINDOW_H
