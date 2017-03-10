#-------------------------------------------------
#
# Project created by QtCreator 2016-10-08T15:31:30
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets\
 network\
multimedia

TARGET = excption_test
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    servers.cpp

HEADERS  += dialog.h \
    servers.h

FORMS    += dialog.ui \
    servers.ui

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_video \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann
