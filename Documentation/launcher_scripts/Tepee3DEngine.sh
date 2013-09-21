#!/bin/sh
export LD_LIBRARY_PATH=`pwd`/Qt_Libraries:$LD_LIBRARY_PATH
export QML_IMPORT_PATH=`pwd`/Qt_Libraries/qml
export QML2_IMPORT_PATH=`pwd`/Qt_Libraries/qml
export QT_QPA_PLATFORM_PLUGIN_PATH=`pwd`/Qt_Libraries/plugins/platforms
export QT_PLUGIN_PATH=`pwd`/Qt_Libraries/plugins
`pwd`/Tepee3DEngine
