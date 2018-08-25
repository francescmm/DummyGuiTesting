QT += testlib gui core widgets
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_mainwindowtest.cpp \
    ../DummyGui/MainWindow.cpp \
    ../DummyGui/PersonalInfoFrame.cpp

HEADERS += ../DummyGui/MainWindow.h \
    ../DummyGui/PersonalInfoFrame.h

FORMS += ../DummyGui/MainWindow.ui

INCLUDEPATH += ../DummyGui
