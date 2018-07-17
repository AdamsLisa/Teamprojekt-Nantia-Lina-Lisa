
#-------------------------------------------------
#
# Project created by QtCreator 2018-05-24T13:09:45
#
#-------------------------------------------------
QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QTableViewTabelle
TEMPLATE = app
CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS-DQT_NO_VERSION_TAGGING

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

DEFINES *= QT_USE_QSTRINGBUILDER
DEFINES += "_SILENCE_STDEXT_HASH_DEPRECATION_WARNINGS=1"

SOURCES += \
        main.cpp \
        bardelegate.cpp \
        bardelegatepep.cpp \
    proteintabelle.cpp \
    peptidtabelle.cpp \


HEADERS += \
        bardelegate.h \
        bardelegatepep.h \
    proteintabelle.h \
    peptidtabelle.h

FORMS += \


SUBDIRS += \
    TablePeptides/QTableViewTabelle.pro

DISTFILES +=


