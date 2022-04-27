QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    miller_rabin.cpp \
    src/CpuInfo.cpp \
    src/Erat.cpp \
    src/EratBig.cpp \
    src/EratMedium.cpp \
    src/EratSmall.cpp \
    src/IteratorHelper.cpp \
    src/LookupTables.cpp \
    src/MemoryPool.cpp \
    src/ParallelSieve.cpp \
    src/PreSieve.cpp \
    src/PrimeGenerator.cpp \
    src/PrimeSieve.cpp \
    src/PrintPrimes.cpp \
    src/SievingPrimes.cpp \
    src/api.cpp \
    src/iterator.cpp \
    src/nthPrime.cpp \
    src/popcount.cpp

HEADERS += \
    mainwindow.h \
    primesieve.hpp \
    primesieve/Bucket.hpp \
    primesieve/CpuInfo.hpp \
    primesieve/Erat.hpp \
    primesieve/EratBig.hpp \
    primesieve/EratMedium.hpp \
    primesieve/EratSmall.hpp \
    primesieve/IteratorHelper.hpp \
    primesieve/MemoryPool.hpp \
    primesieve/ParallelSieve.hpp \
    primesieve/PreSieve.hpp \
    primesieve/PrimeGenerator.hpp \
    primesieve/PrimeSieve.hpp \
    primesieve/PrintPrimes.hpp \
    primesieve/SievingPrimes.hpp \
    primesieve/StorePrimes.hpp \
    primesieve/Wheel.hpp \
    primesieve/bits.hpp \
    primesieve/calculator.hpp \
    primesieve/config.hpp \
    primesieve/forward.hpp \
    primesieve/intrinsics.hpp \
    primesieve/iterator.h \
    primesieve/iterator.hpp \
    primesieve/littleendian_cast.hpp \
    primesieve/macros.hpp \
    primesieve/malloc_vector.hpp \
    primesieve/pmath.hpp \
    primesieve/primesieve_error.hpp \
    primesieve/resizeUninitialized.hpp

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
