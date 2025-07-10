CONFIG += qt debug
QT += widgets
HEADERS += hello.h
SOURCES += hello.cpp hellounix.cpp hellowin.cpp main.cpp
win32 {
    SOURCES += hellowin.cpp
}
unix {
    SOURCES += hellounix.cpp
}
win32: debug {
    CONFIG += console
}