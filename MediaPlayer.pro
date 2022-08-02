QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11
RC_IONS += logo.ico
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
QT       +=   sql
include(./record/record.pri)
include(./netapi/netapi.pri)
include(./MD5/md5.pri)
INCLUDEPATH += ./MD5
QT += multimedia

SOURCES += \
    main.cpp \
    onlinedialog.cpp \
    packetqueue.cpp \
    videodialog.cpp \
    videoplayer.cpp \
    videoshow.cpp \
    videoslider.cpp

HEADERS += \
    onlinedialog.h \
    packetqueue.h \
    videodialog.h \
    videoplayer.h \
    videoshow.h \
    videoslider.h

FORMS += \
    onlinedialog.ui \
    record/recorddialog.ui \
    videodialog.ui \
    videoshow.ui


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

INCLUDEPATH += $$PWD/ffmpeg-4.2.2/include\
 $$PWD/SDL2-2.0.10/include\
  $$PWD/uiapi\
  $$PWD/sqlapi
LIBS += $$PWD/ffmpeg-4.2.2/lib/avcodec.lib\
 $$PWD/ffmpeg-4.2.2/lib/avdevice.lib\
 $$PWD/ffmpeg-4.2.2/lib/avfilter.lib\
 $$PWD/ffmpeg-4.2.2/lib/avformat.lib\
 $$PWD/ffmpeg-4.2.2/lib/avutil.lib\
 $$PWD/ffmpeg-4.2.2/lib/postproc.lib\
 $$PWD/ffmpeg-4.2.2/lib/swresample.lib\
 $$PWD/ffmpeg-4.2.2/lib/swscale.lib\
 $$PWD/SDL2-2.0.10/lib/x86/SDL2.lib
LIBS += C:\Qt\opencv-release\lib\libopencv_calib3d420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_core420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_features2d420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_flann420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_highgui420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_imgproc420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_ml420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_objdetect420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_video420.dll.a\
 C:\Qt\opencv-release\lib\libopencv_videoio420.dll.a\


include (./uiapi/uiapi.pri)
include (./sqlapi/sqlapi.pri)
RESOURCES += \
    src.qrc

DISTFILES +=
