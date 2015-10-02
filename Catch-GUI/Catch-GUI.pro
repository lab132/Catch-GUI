#-------------------------------------------------
#
# Project created by QtCreator 2015-09-19T16:49:15
#
#-------------------------------------------------

QT       += core gui \
            xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Catch-GUI
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    TagFilterWidget.cpp \
    ExePickerWidget.cpp \
    CatchTest.cpp \
    CatchCommandLine.cpp \
    TreeNode.cpp

HEADERS  += mainwindow.h \
    TagFilterWidget.h \
    ExePickerWidget.h \
    CatchTest.h \
    CatchCommandLine.h \
    TreeModel.h \
    TreeModel.inl \
    TreeNode.h

FORMS    += mainwindow.ui \
    TagFilterWidget.ui \
    ExePickerWidget.ui \
    CatchCommandLine.ui
