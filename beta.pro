QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.15
CONFIG += c++11, sdk_no_version_check

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    buygoodsdialog.cpp \
    chosetabledialog.cpp \
    forgetpasswddialog.cpp \
    main.cpp \
    logindialog.cpp \
    mainwindow.cpp \
    myordersdialog.cpp \
    registerdialog.cpp \
    menuwidget.cpp \
    myprofiledialog.cpp \
    releasegoodsdialog.cpp

HEADERS += \
    buygoodsdialog.hpp \
    chosetabledialog.hpp \
    forgetpasswddialog.hpp \
    logindialog.hpp \
    mainwindow.h \
    myordersdialog.hpp \
    registerdialog.hpp \
    menuwidget.hpp \
    myprofiledialog.hpp \
    releasegoodsdialog.hpp

FORMS += \
    buygoodsdialog.ui \
    chosetabledialog.ui \
    forgetpasswddialog.ui \
    logindialog.ui \
    myordersdialog.ui \
    registerdialog.ui \
    menuwidget.ui \
    myprofiledialog.ui \
    releasegoodsdialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    pic.qrc
