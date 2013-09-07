import QtQuick 2.1
import Qt.labs.folderlistmodel 1.0
import DeveloperAPIFiles.qml.UIComponents 1.0

Item
{
    id : menuBottomMain
    width : minMenuWidth
    height : minMenuHeight

    // BOTTOM MENU IS USED FOR PLUGIN SETTINGS WHEN FOCUSED ON A PLUGIN
    // WHEN NOT FOCUSED IT IS THE APPLICATION MAIN/SETTINGS MENU
    anchors.bottom: parent.bottom

    property bool isShown : false
    property int  minMenuHeight : mainWindow.menuMinimumWidth
    property int  maxMenuHeight : mainWindow.height / 2
    property int  minMenuWidth : mainWindow.width
    property int  maxMenuWidth : mainWindow.width
    property int  minMenuY : mainWindow.height - minMenuHeight
    property int  maxMenuY : mainWindow.height - maxMenuHeight
    property int  ySaved;
    property int offsetSaved;
    property alias pluginMenuSource : plugin_menu_loader.source
    property bool isPressed;

    Behavior on height {NumberAnimation {duration : 200}}

    onIsShownChanged: {menuBottomMain.height = (menuBottomMain.isShown) ? maxMenuHeight : minMenuHeight}


    function startDrag(xPos, yPos)
    {
        ySaved = yPos;
    }

    function dragMoved(offsetX, offsetY)
    {
        var newY = offsetY + ySaved
        if (newY <= minMenuY && newY >= maxMenuY)
            menuBottomMain.height = mainWindow.height - newY
        offsetSaved = offsetY
    }

    function dragEnd()
    {
        var oldstate = menuBottomMain.isShown
        var deployed = ((menuBottomMain.height - minMenuHeight) / maxMenuHeight > 0.4)
        var dragLength = 30
        console.log(offsetSaved)
        if (offsetSaved < dragLength)
            menuBottomMain.isShown = true;
        else if (offsetSaved > dragLength)
            menuBottomMain.isShown = false;
        else
            menuBottomMain.isShown = deployed;
        if (oldstate === menuBottomMain.isShown)
            menuBottomMain.height = (menuBottomMain.isShown) ? maxMenuHeight : minMenuHeight
    }

    states : [
        State
        {
            name : "menuShown"
            PropertyChanges    {target: menuBottomRec; opacity : mainWindow.menu_opacity_deployed}
            PropertyChanges    {target: arrow_image; opacity : 0}
            when : menuBottomMain.isShown || ((menuBottomMain.height - minMenuHeight) / maxMenuHeight > 0.4)
        },
        State
        {
            name : "menuHidden"
            PropertyChanges    {target: menuBottomRec; opacity : mainWindow.menu_opacity_retracted}
            PropertyChanges    {target: arrow_image; opacity : 0.8}
            when :!menuBottomMain.isShown || !((menuBottomMain.height - minMenuHeight) / maxMenuHeight > 0.4)
        }
    ]

    transitions : [
        Transition
        {
            NumberAnimation    {target : menuBottomRec; properties : "opacity"; duration : 200}
        }
    ]

    BorderImage
    {
        id: menuBottomRec
        source: "../Resources/Pictures/panel_bg2.png"
        anchors.fill: parent
        border.left: 2; border.bottom: 1

        Loader
        {
            id : plugin_menu_loader
            anchors.fill: parent
            enabled : isShown
            onLoaded:
            {
                "Menu Loaded"
            }
        }

        Item
        {
            id : app_conf_menu
            anchors.fill: parent
            enabled : (mainWindow.currentRoomId === -1 && height === maxMenuHeight)
            opacity : (enabled) ? 1 : 0

            PathView
            {
                id : skyboxes_view
                preferredHighlightBegin: 0.47
                preferredHighlightEnd: 0.47
                anchors
                {
                    fill : parent
                    margins : minMenuHeight
                }
                clip : true
                model : FolderListModel {
                    folder: "../Resources/Textures/skyboxes/";
                }

                onCurrentIndexChanged :
                {
                }

                path : Path {
                    // LEFT
                    startX: parent.x
                    startY: parent.y + parent.height / 4
                    PathPercent {value : 0}
                    PathAttribute {name : "delScale"; value : 0.6}
                    PathAttribute {name : "delAngle"; value : 60}


                    // CENTER
                    PathCurve {x : parent.width / 2; y : parent.y + parent.height / 5}
                    PathAttribute {name : "delScale"; value : 1}

                    // RIGHT
                    PathCurve {x : parent.width; y : parent.y + parent.height / 4}
                    PathAttribute {name : "delScale"; value : 0.6}
                    PathAttribute {name : "delAngle"; value : -60}


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
    }
    Image
    {
        id : arrow_image
        anchors.centerIn: parent
        source : "../Resources/Pictures/arrow.png"
        fillMode: Image.PreserveAspectFit
        Behavior on opacity {SmoothedAnimation {velocity : 10}}
        rotation : 180
        height : mainWindow.menuMinimumWidth
        scale : isPressed ? 0.9 :  1
    }
}
