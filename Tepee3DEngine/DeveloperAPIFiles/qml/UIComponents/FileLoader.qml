import QtQuick 2.1
import Qt3D 2.0

Item3D
{
    id : fileLoaderItem
    property string fileName;
    property bool   isFolder;
    property int    delegateIndex;
    property int    maxCount;

    Loader
    {
        id : fileLoader

        function getFileName() {return fileLoaderItem.fileName}
        function getDelegateIndex() {return delegateIndex}
        function getMaxCount() {return maxCount}

        source : (isFolder) ? "FolderDelegate.qml" : "FileDelegate.qml"
    }
}
