#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T15:17:19
#
#-------------------------------------------------

QT       += core
QT       += widgets

TARGET = Thermal_Stitcher_Proj
CONFIG   += console
CONFIG   += c++11
CONFIG   -= app_bundle

INCLUDEPATH += /usr/local/include/opencv2
LIBS += -L/usr/local/lib -lopencv_core -lopencv_imgcodecs -lopencv_highgui -lopencv_stitching

TEMPLATE = app


SOURCES += \
    main.cpp \
    Drivers/Imager.cpp \
    Drivers/PanTilt.cpp \
    Modules/Retriever.cpp \
    Third-Party/Lepton/Lepton_I2C.cpp \
    Third-Party/Lepton/LeptonThread.cpp \
    Third-Party/Lepton/MyLabel.cpp \
    Third-Party/Lepton/Palettes.cpp \
    Third-Party/Lepton/SPI.cpp \
    Third-Party/Lepton/leptonSDKEmb32PUB/bbb_I2C.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/crc16fast.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_AGC.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Protocol.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Service.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SDK.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SYS.c \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_VID.c \
    Drivers/Display.cpp \
    Modules/TStitcher.cpp

HEADERS += \
    Drivers/Imager.h \
    Drivers/PanTilt.h \
    Modules/Retriever.h \
    Third-Party/Lepton/Lepton_I2C.h \
    Third-Party/Lepton/LeptonThread.h \
    Third-Party/Lepton/MyLabel.h \
    Third-Party/Lepton/Palettes.h \
    Third-Party/Lepton/SPI.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/bbb_I2C.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/crc16.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_AGC.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_ErrorCodes.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Protocol.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Reg.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_I2C_Service.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_Macros.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SDK.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SDKConfig.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_SYS.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_Types.h \
    Third-Party/Lepton/leptonSDKEmb32PUB/LEPTON_VID.h \
    Drivers/Display.h \
    Modules/TStitcher.h

SUBDIRS += \
    Third-Party/Lepton/raspberrypi_video.pro

OTHER_FILES +=
