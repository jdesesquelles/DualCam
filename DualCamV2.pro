TEMPLATE = app

QT += qml quick widgets core multimedia
CONFIG += c++11 release
CONFIG-=app_bundle
TARGET = DualCam

#QMAKE_LFLAGS += -static

SOURCES += main.cpp \
    capture.cpp \
    objectextractor.cpp

INCLUDEPATH += include
INCLUDEPATH += /usr/local/include

RESOURCES += qml.qrc

# Default rules for deployment.
include(deployment.pri)


LIBS += /usr/local/lib/libopencv_dnn.dylib /usr/local/lib/libopencv_ml.dylib /usr/local/lib/libopencv_objdetect.dylib /usr/local/lib/libopencv_shape.dylib /usr/local/lib/libopencv_stitching.dylib /usr/local/lib/libopencv_superres.dylib /usr/local/lib/libopencv_videostab.dylib /usr/local/lib/libopencv_calib3d.dylib /usr/local/lib/libopencv_features2d.dylib /usr/local/lib/libopencv_highgui.dylib /usr/local/lib/libopencv_videoio.dylib /usr/local/lib/libopencv_imgcodecs.dylib /usr/local/lib/libopencv_video.dylib /usr/local/lib/libopencv_photo.dylib /usr/local/lib/libopencv_imgproc.dylib /usr/local/lib/libopencv_flann.dylib /usr/local/lib/libopencv_core.dylib /usr/local/lib/libjpeg.dylib


DISTFILES += \
    ic_play.png \
    ic_record.png \
    ic_stop.png \
    ic_folder_open.png

HEADERS += \
    capture.h \
    objectextractor.h \
    main.h
