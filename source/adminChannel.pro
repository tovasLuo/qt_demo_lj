#-------------------------------------------------
#
# Project created by QtCreator 2016-09-14T10:46:03
#
#-------------------------------------------------

QT       += core gui uitools
QT       += network

unix:!macx{
QMAKE_CXXFLAGS += -std=c++11
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = adminChannel
TEMPLATE = app

INCLUDEPATH += . ./include ./include/bson \
                ./core \
                ./apps/include ./apps/common ./apps/controller ./apps/factory ./apps/view \
                ./apps/wrapper

SOURCES += apps/main.cpp\
    apps/view/doublechannelwidget.cpp \
    apps/controller/main_controller.cpp \
    apps/factory/ViewFactory.cpp \
    apps/view/main_view.cpp \
    apps/controller/tcpserver.cpp \
    apps/controller/options.cpp \
    apps/controller/client.cpp \
    apps/view/bottompiclabel.cpp \
    apps/view/keydialog.cpp

HEADERS  += apps/view/doublechannelwidget.h \
    apps/controller/main_controller.h \
    apps/factory/ViewFactory.h \
    apps/view/main_view.h \
    core/IMainController.h \
    core/IMainView.h \
    core/IView.h \
    core/IViewFactory.h \
    core/ViewModel.h \
    apps/controller/tcpserver.h \
    apps/controller/data_generated.h \
    apps/controller/options.h \
    apps/controller/channel_info.h \
    apps/controller/client.h \
    apps/controller/messagelbtd_generated.h \
    apps/view/bottompiclabel.h \
    apps/view/THIDImageHelper.h \
    apps/view/THIDErrorDef.h \
    apps/view/keydialog.h

unix:!macx{
LIBS += -L /usr/lib/hisign/VerifyEngine \
        -lTHIDImageHelper
}


win32{
LIBS += -L../libs/windows \
        -lTHIDImageHelper
}

FORMS    += apps/view/doublechannelwidget.ui \
    apps/view/keydialog.ui

RESOURCES += \
    resource.qrc
