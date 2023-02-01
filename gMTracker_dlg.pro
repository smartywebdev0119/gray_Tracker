QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    activity.cpp \
    imagedlg.cpp \
    main.cpp \
    dialog.cpp \
    mylogindlg.cpp \
    mysavethread.cpp \
    qcontmessage.cpp \
    quicklogging.cpp

HEADERS += \
    activity.h \
    dialog.h \
    imagedlg.h \
    mylogindlg.h \
    mysavethread.h \
    qcontmessage.h \
    quicklogging.h

FORMS += \
    activity.ui \
    dialog.ui \
    imagedlg.ui \
    mylogindlg.ui \
    qcontmessage.ui \
    quicklogging.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resource.qrc

DISTFILES += \
    img/waste_16px_normal.png
