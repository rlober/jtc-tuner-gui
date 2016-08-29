#-------------------------------------------------
#
# Project created by QtCreator 2016-08-26T14:45:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = jtcTunerGui
TEMPLATE = app



SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    jtcparameters.h

INCLUDEPATH += /usr/local/include
INCLUDEPATH += /usr/include

FORMS    += mainwindow.ui

LIBS += -lYARP_OS
LIBS += -lYARP_sig
LIBS += -lYARP_math
LIBS += -lYARP_dev
LIBS += -lYARP_name
LIBS += -lYARP_init


win32-msvc2010{
    INCLUDEPATH += $$(OPENCV_DIR)/include
    INCLUDEPATH += $$(OPENCV_DIR)/include/opencv
    INCLUDEPATH += $$(OPENCV_DIR)/include/opencv2/core
    INCLUDEPATH += $$(YARP_ROOT)/src/libYARP_OS/include
    INCLUDEPATH += $$(YARP_ROOT)/src/libYARP_dev/include
    INCLUDEPATH += $$(YARP_ROOT)/src/libYARP_sig/include
    INCLUDEPATH += $$(YARP_ROOT)/build/generated_include/
    INCLUDEPATH += $$(ICUB_ROOT)/src/idl_generated_code/include
    INCLUDEPATH += $$(YARP_ROOT)/src/yarpmanager/libymanager/include

    CONFIG(debug, debug|release) {

        DEFINES -= UNICODE
        DEFINES += WIN32
        DEFINES += _WINDOWS
        DEFINES += _DEBUG
        DEFINES += _REENTRANT
        DEFINES += _CRT_SECURE_NO_DEPRECATE
        DEFINES += _CRT_NONSTDC_NO_DEPRECATE
        DEFINES += _MBCS

        LIBS += -L"$$(OPENCV_DIR)/lib"
        LIBS += -L$$(YARP_ROOT)/build/lib/Debug
        LIBS += -L"$$(ACE_ROOT)/lib"
        LIBS += -L"$$(GSL_DIR)/lib"

        LIBS += -lYARP_OSd
        LIBS += -lYARP_sigd
        LIBS += -lYARP_mathd
        LIBS += -lYARP_devd
        LIBS += -lYARP_named
        LIBS += -lYARP_initd

        LIBS += -lkernel32
        LIBS += -luser32
        LIBS += -lgdi32
        LIBS += -lwinspool
        LIBS += -lshell32
        LIBS += -lole32
        LIBS += -loleaut32
        LIBS += -luuid
        LIBS += -lcomdlg32
        LIBS += -ladvapi32
    }else{

        DEFINES -= UNICODE
        DEFINES += WIN32
        DEFINES += _WINDOWS
        DEFINES += NDEBUG
        DEFINES += _REENTRANT
        DEFINES += _CRT_SECURE_NO_DEPRECATE
        DEFINES += _CRT_NONSTDC_NO_DEPRECATE
        DEFINES += _MBCS

        LIBS += -L"$$(OPENCV_DIR)/lib"
        LIBS += -L$$(YARP_ROOT)/build/lib/Release
        LIBS += -L"$$(ACE_ROOT)/lib"
        LIBS += -L"$$(GSL_DIR)/lib"

        LIBS += -lYARP_OS
        LIBS += -lYARP_sig
        LIBS += -lYARP_math
        LIBS += -lYARP_dev
        LIBS += -lYARP_name
        LIBS += -lYARP_init

        LIBS += -lkernel32
        LIBS += -luser32
        LIBS += -lgdi32
        LIBS += -lwinspool
        LIBS += -lshell32
        LIBS += -lole32
        LIBS += -loleaut32
        LIBS += -luuid
        LIBS += -lcomdlg32
        LIBS += -ladvapi32
    }

    LIBS += -lopencv_calib3d249
    LIBS += -lopencv_contrib249
    LIBS += -lopencv_core249
    LIBS += -lopencv_features2d249
    LIBS += -lopencv_flann249
    LIBS += -lopencv_gpu249
    LIBS += -lopencv_highgui249
    LIBS += -lopencv_imgproc249
    LIBS += -lopencv_legacy249
    LIBS += -lopencv_ml249
    LIBS += -lopencv_nonfree249
    LIBS += -lopencv_objdetect249
    LIBS += -lopencv_photo249
    LIBS += -lopencv_stitching249
    LIBS += -lopencv_ts249
    LIBS += -lopencv_video249
    LIBS += -lopencv_videostab249
}

RESOURCES += \
    resources.qrc
