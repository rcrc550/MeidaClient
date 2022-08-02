QT += multimedia
INCLUDEPATH+=C:/Qt/opencv-release/include/opencv2\
C:/Qt/opencv-release/include\
$$PWD/ffmpeg-4.2.2/include
LIBS += $$PWD/SDL2-2.0.10/lib/x86/SDL2.lib
HEADERS += \
    $$PWD/picinpic_read.h \
    $$PWD/recorddialog.h \
    $$PWD/savevideofile.h \
    $$PWD/screenrecorder.h \
     $$PWD/common.h \
      $$PWD/audio_read.h


SOURCES += \
    $$PWD/picinpic_read.cpp \
    $$PWD/recorddialog.cpp \
    $$PWD/savevideofile.cpp \
    $$PWD/screenrecorder.cpp \
    $$PWD/audio_read.cpp

FORMS    +=  \
     $$PWD/recorddialog.ui \

