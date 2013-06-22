#-------------------------------------------------
#-------------------------------------------------
#
# Project created by QtCreator 2012-06-09T11:42:49
#
#-------------------------------------------------



 TEMPLATE        = lib
 CONFIG         += qt plugin
 QT             += quick

HEADERS         = \
    TestPlugin.h

 SOURCES         = \
    TestPlugin.cpp

#include development files
include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = TestPlugin                    #NAME OF THE PLUGIN LIBRAY
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries             #WHERE TO PUT THE LIBRARY
 DESTDIRQML      = qml_folder

# # install
# target.path = plugins/build
# sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS plugin.pro
# sources.path = ../plugins
# INSTALLS += target sources

OTHER_FILES += \
    qmldir \
    qmltestplugin.qmlproject \
    Menu.qml    \
    images/texture0.jpg \
    Batman/Cape.obj \
    Batman/Cape.mtl \
    Batman/Cape.lwo \
    Batman/BatmanArmoured.obj \
    Batman/BatmanArmoured.mtl \
    Batman/BatmanArmoured.lwo \
    Batman/Batman.obj \
    Batman/Batman.mtl \
    Batman/Batman.lwo \
    Batman/V2_Batman_Head_S.tga \
    Batman/V2_Batman_Head_N.tga \
    Batman/V2_Batman_Head_D.tga \
    Batman/V2_Batman_Cape_S2.tga \
    Batman/V2_Batman_Cape_N2.tga \
    Batman/V2_Batman_Cape_D2.tga \
    Batman/V2_Batman_Cape_A2.tga \
    Batman/V2_Batman_Body_S.tga \
    Batman//V2_Batman_Body_N.tga \
    Batman/V2_Batman_Body_D.tga \
    Batman/BatmanEye_N_2.tga \
    Batman/BatmanEye_D.tga \
    Batman/BatmanArmoured_Head_S.tga \
    Batman/BatmanArmoured_Head_N.tga \
    Batman/BatmanArmoured_Head_D.tga \
    Batman/BatmanArmoured_Body_S.tga \
    Batman/BatmanArmoured_Body_N.tga \
    Batman/BatmanArmoured_Body_D.tga \
    js/xauth.js \
    js/twitter.js \
    js/translate.js \
    js/script.js \
    js/pocket.js \
    js/lib/sha1.js \
    TestPlugin.qml \
    js/storage.js \
    storage.qml

# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = ../../Tepee3DEngine/plugins_qml/TestPlugin

DEPLOYMENT += qml_folder
INSTALLS += qml_folder

linux {

    QMAKE_CXXFLAGS_DEBUG += -Wundef -Wunused-function -Wunused -Wmissing-declarations
    QMAKE_CXXFLAGS_RELEASE += -Wundef -Wunused-function -Wunused -Wmissing-declarations

    coverage {
        LIBS += -lgcov
        QMAKE_CXXFLAGS_DEBUG += --coverage
        QMAKE_CXXFLAGS_RELEASE += --coverage
    }
}
