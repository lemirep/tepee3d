import QtQuick 2.0
import Qt.labs.folderlistmodel 1.0
import DeveloperAPIFiles.qml.UIComponents 1.0

Item
{
    id : app_conf_menu
    anchors.fill: parent
    enabled : (mainWindow.currentRoomId === -1)
    opacity : (enabled) ? 1 : 0

    PathView
    {
        id : skyboxes_view
        preferredHighlightBegin: 0.47
        preferredHighlightEnd: 0.47
        anchors
        {
            fill : parent
            margins : parent.height / 8
        }
        clip : true
        model : FolderListModel {
            folder: "../Resources/Textures/skyboxes/";
        }

        path : Path {
            // LEFT
            startX: skyboxes_view.x
            startY: skyboxes_view.y + skyboxes_view.height / 4
            PathPercent {value : 0}
            PathAttribute {name : "delScale"; value : 0.6}
            PathAttribute {name : "delAngle"; value : 60}
            PathAttribute {name : "delZ"; value : 0}


            // CENTER
            PathCurve {x : skyboxes_view.width / 2; y : skyboxes_view.y + skyboxes_view.height / 5}
            PathAttribute {name : "delScale"; value : 1}
            PathAttribute {name : "delZ"; value : 1}


            // RIGHT
            PathCurve {x : skyboxes_view.width; y : skyboxes_view.y + skyboxes_view.height / 4}
            PathAttribute {name : "delScale"; value : 0.6}
            PathAttribute {name : "delAngle"; value : -60}
            PathAttribute {name : "delZ"; value : 0}
        }

        delegate : Component {
            Item
            {
                property bool isCurrentItem : (skyboxes_view.currentIndex === index)
                property string path : model.fileName
                property int rAngle : PathView.onPath ? (!isCurrentItem) ? PathView.delAngle : 0 : 0
                width : skyboxes_view.width / 4
                height : skyboxes_view.height
                scale : PathView.onPath ? PathView.delScale : 1
                z :  PathView.onPath ? PathView.delZ : 0
                transform: [Rotation { origin.x: width / 2; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: rAngle}]

                property variant fileModel : FolderListModel {
                    folder : path
                    nameFilters: [ "*.png", "*.jpg" ]
                }

                Repeater
                {
                    anchors.fill: parent
                    model : fileModel
                    delegate : Component {
                        Image
                        {
                            width : skyboxes_view.width / 4
                            height : skyboxes_view.height
                            fillMode : Image.PreserveAspectFit
                            asynchronous: true
                            source : "../Resources/Textures/skyboxes/" + path + "/_north.jpg"
                        }
                    }
                }
                OkButton
                {
                    anchors
                    {
                        right : parent.right
                        bottom : parent.bottom
                    }
                    opacity : isCurrentItem ? 1 : 0
                    enabled : isCurrentItem
                    onClicked :
                    {
                        roomManager.skyboxPath = path;
                        roomManager.saveSkyboxPath();
                    }
                }
            }
        }
    }
}
