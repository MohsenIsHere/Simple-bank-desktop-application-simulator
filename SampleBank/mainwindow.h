#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    QSqlDatabase db ;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_btnSignUp_clicked();

    void on_pushButtonLog_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
