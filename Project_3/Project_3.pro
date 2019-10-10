TEMPLATE = app

CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS_DEBUG += -O3

SOURCES += \
        main.cpp


INCLUDEPATH += C:\Qt\armadillo-9.700.2\include
DEPENDPATH += C:\Qt\armadillo-9.700.2\include

INCLUDEPATH += C:\Qt\armadillo-9.700.2\include
DEPENDPATH += C:\Qt\armadillo-9.700.2\include



LIBS += \
    -LC:\Qt\armadillo-9.700.2\examples\lib_win64 \
    -llapack_win64_MT \
    -lblas_win64_MT

# MPI Settings
QMAKE_CXX = \"C:\Program Files\Microsoft MPI\Bin\mpiexec.exe\"
QMAKE_CXX_DEBUG = $$QMAKE_CXX
QMAKE_CXX_RELEASE = $$QMAKE_CXX
QMAKE_LINK = $$QMAKE_CXX
QMAKE_CC = $$QMAKE_CXX

#QMAKE_CFLAGS += $$system($$QMAKE_CXX --showme:compile)
#QMAKE_LFLAGS += $$system($$QMAKE_CXX --showme:link)
#QMAKE_CXXFLAGS += $$system($$QMAKE_CXX --showme:compile) -DMPICH_IGNORE_CXX_SEEK
#QMAKE_CXXFLAGS_DEBUG += $$system($$QMAKE_CXX --showme:compile) -DMPICH_IGNORE_CXX_SEEK
