QT += testlib gui core widgets
CONFIG += c++14

TEMPLATE = app

SOURCES +=  \
    ../DummyGui/MainWindow.cpp \
    ../DummyGui/PersonalInfoFrame.cpp \
    main.cpp \
    MainWindowTest.cpp

HEADERS += ../DummyGui/MainWindow.h \
    ../DummyGui/PersonalInfoFrame.h \
    MainWindowTest.h

FORMS += ../DummyGui/MainWindow.ui

INCLUDEPATH += ../DummyGui
