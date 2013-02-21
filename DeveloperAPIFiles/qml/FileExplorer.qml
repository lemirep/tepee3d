import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import Qt.labs.folderlistmodel 1.0

Item3D
{
    id : fileBrowserItem
    property alias rootDir : fileModel.folder;
    signal fileSelected(string file);

    function    setSelectedFile(file)    {fileSelected(file)}
    function    goToFolder(folder)    {filesRepeater.enabled = false; rootDir = folder; filesRepeater.enable=true}

    FolderListModel
    {
        id : fileModel;
        folder : "/"
        Component.onCompleted: {console.log("FolderModel created")}
    }

    Repeater
    {
        id : filesRepeater
        model : fileModel
        FileLoader
        {
            id : fileLoader;
            isFolder: fileModel.isFolder(index);
            fileName : model.fileName
            delegateIndex: index
            maxCount: fileModel.count
        }
    }
}
