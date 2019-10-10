TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS_DEBUG += -O3

SOURCES += \
        #main.cpp \
        Gaussian_Laguerre.cpp \
        Gaussian_Legendre.cpp \
        integration_functions.cpp \
        lib.cpp \
        p3_functions.cpp

INCLUDEPATH += C:\Qt\armadillo-9.700.2\include
DEPENDPATH += C:\Qt\armadillo-9.700.2\include

INCLUDEPATH += C:\Qt\armadillo-9.700.2\include
DEPENDPATH += C:\Qt\armadillo-9.700.2\include



LIBS += \
    -LC:\Qt\armadillo-9.700.2\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT


HEADERS += \
    lib.h
