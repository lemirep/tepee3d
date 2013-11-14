TEMPLATE    = subdirs
SUBDIRS     =  RoomLibrary       \
               ServicesLibraries \
               Tepee3DCoreLibrary \
               Tepee3DEngine \
               Plugins

message($$QMAKESPEC)

# BUILD IS DONE ACCORD TO THE ORDER OF SUBDIRS
CONFIG += ordered

# FOR LOG ON WINDOWS
win32:win64 {
CONFIG += console
}

# DOC APPEARS ONLY FOR WINDOWS AND LINUX PLATFORMS

!android:!qnx {

    EXTRAS += UnitTests

    DOC_EXTRAS += Documentation/config.qdocconf \
                 Documentation/install.qdoc \
                 Documentation/vm_instruction.qdoc \
                 Documentation/how-to-plugins.qdoc \
                 Documentation/all_classes.qdoc \
                 Documentation/plugin_tutorial.qdoc \
                 Documentation/database_service.qdoc \
                 Documentation/web_service.qdoc \
                 Documentation/file_downloader_service.qdoc \
                 Documentation/leap_motion_service.qdoc \
                 Documentation/ui_components.qdoc \
                 Documentation/index.qdoc

    DOC_EXTRAS += DummyProject/DummyProject.cpp \
                  DummyProject/DummyProject.h \
                  DummyProject/DummyProject.pro \
                  DummyProject/DummyProject.qml
}

android {
    DOC_EXTRAS += android/AndroidManifest.xml
    qml_folder.files += Tepee3DEngine/qml/
    qml_folder.files += Tepee3DEngine/plugins_qml/
    qml_folder.files += Tepee3DEngine/libraries/
    qml_folder.files += Tepee3DEngine/databases/
    qml_folder.files += Tepee3DEngine/DeveloperAPIFiles/
    qml_folder.path = android/assets
    INSTALLS += qml_folder
    DEPLOYMENT += qml_folder
}

for(dir, EXTRAS) {
    exists($$dir) {
        SUBDIRS += $$dir
    }
}

for (doc, DOC_EXTRAS) {
    exists($$doc) {
        OTHER_FILES += $$doc
    }
}

OTHER_FILES += \
    android/src/org/kde/necessitas/ministro/IMinistro.aidl \
    android/src/org/kde/necessitas/ministro/IMinistroCallback.aidl \
    android/src/org/qtproject/qt5/android/bindings/QtApplication.java \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/res/values-et/strings.xml \
    android/res/values-nl/strings.xml \
    android/res/layout/splash.xml \
    android/res/values-pt-rBR/strings.xml \
    android/res/values-nb/strings.xml \
    android/res/values-id/strings.xml \
    android/res/values-es/strings.xml \
    android/res/values-el/strings.xml \
    android/res/values-ro/strings.xml \
    android/res/values-it/strings.xml \
    android/res/values-ms/strings.xml \
    android/res/values-de/strings.xml \
    android/res/values-pl/strings.xml \
    android/res/values-rs/strings.xml \
    android/res/values-zh-rTW/strings.xml \
    android/res/values-zh-rCN/strings.xml \
    android/res/values-fa/strings.xml \
    android/res/values-ru/strings.xml \
    android/res/values/libs.xml \
    android/res/values/strings.xml \
    android/res/values-ja/strings.xml \
    android/res/values-fr/strings.xml \
    android/AndroidManifest.xml \
    android/version.xml







