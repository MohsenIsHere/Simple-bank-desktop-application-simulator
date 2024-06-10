#include "mainwindow.h"
#include "signup.h"
#include "home.h"
#include "test.h"
#include "createbankaccount.h"
#include "transfermoney.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
