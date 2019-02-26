QT += testlib gui core widgets
CONFIG += c++14

TEMPLATE = app

SOURCES +=  \
    ../DummyGui/MainWindow.cpp \
    ../DummyGui/PersonalInfoFrame.cpp \
    main.cpp \
    MainWindowTest.cpp \
    TestManager.cpp \
    BaseTest.cpp

HEADERS += ../DummyGui/MainWindow.h \
    ../DummyGui/PersonalInfoFrame.h \
    MainWindowTest.h \
    TestManager.h \
    BaseTest.h

FORMS += ../DummyGui/MainWindow.ui

INCLUDEPATH += ../DummyGui
