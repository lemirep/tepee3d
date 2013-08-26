 TEMPLATE        = lib
 CONFIG          += qt plugin
 QT              += quick
 QT              += multimedia

HEADERS += \
    HarlemShake.h

SOURCES += \
    HarlemShake.cpp

#include development files
include (../../Tepee3DEngine/DeveloperAPIFiles/DevelopmentFiles.pri)

 TARGET          = harlem_shake                     #NAME OF THE PLUGIN LIBRAY
 DESTDIR         = ../../Tepee3DEngine/libraries/widget_libraries             #WHERE TO PUT THE LIBRARY
 DESTDIRQML      = qml_folder

# # install
# target.path = plugins/build
# sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS plugin.pro
# sources.path = ../plugins
# INSTALLS += target sources

OTHER_FILES += \
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
    HS.mp3 \
    HarlemShake.qml \
    Menu.qml \
    qmlharlemshake.qmlproject \
    CustomCube.qml

# deploy qml files to correct dir
qml_folder.files = $$OTHER_FILES
qml_folder.path = ../../Tepee3DEngine/plugins_qml/harlem_shake

DEPLOYMENT += qml_folder
INSTALLS += qml_folder

