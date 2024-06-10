QT += core gui
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bankaccount.cpp \
    createbankaccount.cpp \
    generalfunctions.cpp \
    home.cpp \
    main.cpp \
    mainwindow.cpp \
    mlist.cpp \
    node.cpp \
    signup.cpp \
    test.cpp \
    transfermoney.cpp \
    user.cpp

HEADERS += \
    bankaccount.h \
    createbankaccount.h \
    generalfunctions.h \
    home.h \
    mainwindow.h \
    mlist.h \
    node.h \
    signup.h \
    test.h \
    transfermoney.h \
    user.h

FORMS += \
    createbankaccount.ui \
    home.ui \
    mainwindow.ui \
    signup.ui \
    test.ui \
    transfermoney.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc
