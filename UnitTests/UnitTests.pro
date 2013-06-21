
QT += qml
QT += quick
QT += widgets
QT += 3dquick
QT += sql
QT += testlib

HEADERS += \
      TestUnit.h
SOURCES += \
    TestUnit.cpp

# Include TestModelItem
include(./TestClasses/TestClasses.pri);

# Include Shared Development Files
include(../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)
include(../Tepee3DCoreLibrary/Platforms/Platforms.pri)
include(../Tepee3DCoreLibrary/Services/Services.pri)
include(../Tepee3DCoreLibrary/Room/Room.pri)
include(../Tepee3DCoreLibrary/Plugins/Plugins.pri)
include(../Tepee3DCoreLibrary/View/View.pri)


DEFINES += "COVERAGE_AND_UNITTESTS"

linux {

    QMAKE_CXXFLAGS_DEBUG += -Wundef -Wunused-function -Wunused -Wmissing-declarations
    QMAKE_CXXFLAGS_RELEASE += -Wundef -Wunused-function -Wunused -Wmissing-declarations

    coverage {
        LIBS += -lgcov
        QMAKE_CXXFLAGS_DEBUG += --coverage
        QMAKE_CXXFLAGS_RELEASE += --coverage
    }
}
