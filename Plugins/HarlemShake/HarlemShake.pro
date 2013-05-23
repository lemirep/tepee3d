qml_folder.source = ../../Tepee3DEngine/plugins_qml
qml_folder.target = ./

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

 TARGET          = HarlemShake                     #NAME OF THE PLUGIN LIBRAY
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

# Copies the given files to the destination directory
defineTest(copyToDestDir) {
    files = $$1
    unix {
        QMAKE_POST_LINK  += rm -fr $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
        QMAKE_POST_LINK  += mkdir $$qml_folder.source/$$TARGET $$escape_expand(\\n\\t)
    }
    win32 {
        DDIR = ..\..\Tepee3DEngine\plugins_qml\\$$TARGET
        DESTDIR_WIN = $${DDIR}
        DESTDIR_WIN ~= s,/,\\,g
        QMAKE_POST_LINK +=$$quote(cmd /c  if not exist $${DDIR}\NUL\\$$escape_expand(\n\t) mkdir  $${DDIR}$$escape_expand(\n\t))
    }
    for(FILE, files) {
        DDIR = $$qml_folder.source/$$TARGET/

        win32{
        DDIR =  ..\..\Tepee3DEngine\plugins_qml\\$$TARGET
        FILE ~= s,/,\\,g
        QMAKE_POST_LINK +=$$quote(cmd /c copy /y $${FILE} $${DDIR}$$escape_expand(\n\t))
        }

        unix:QMAKE_POST_LINK += $$QMAKE_COPY $$quote($$FILE) $$quote($$DDIR) $$escape_expand(\\n\\t)      
    }
    message($$QMAKE_POST_LINK)
    export(QMAKE_POST_LINK)
}

# deploy qml files to correct dir
copyToDestDir($$OTHER_FILES)

