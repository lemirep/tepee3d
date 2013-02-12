import QtQuick 2.0
import "../content"

Item
{
    id : menuBottomMain
    width : minMenuWidth
    height : minMenuHeight

    // BOTTOM MENU IS USED FOR PLUGIN SETTINGS WHEN FOCUSED ON A PLUGIN
    // WHEN NOT FOCUSED IT IS THE APPLICATION MAIN/SETTINGS MENU

    property bool isShown : false
    property int  minMenuHeight : mainWindow.menuMinimumWidth
    property int  maxMenuHeight : mainWindow.height / 2
    property int  minMenuWidth : mainWindow.width / 2
    property int  maxMenuWidth : mainWindow.width
    property int  minMenuY : mainWindow.height - minMenuHeight
    property int  maxMenuY : mainWindow.height - maxMenuHeight
    property int  ySaved;
    property int  savedHeight;
    property alias pluginMenuSource : plugin_menu_loader.source

    function startDrag(xPos, yPos)
    {
        ySaved = yPos;
    }

    function dragMoved(offsetX, offsetY)
    {
        var newY = offsetY + ySaved
        if (newY <= minMenuY && newY >= maxMenuY)
            savedHeight = mainWindow.height - newY;
    }

    function dragEnd()
    {
        if ((savedHeight - minMenuHeight) / maxMenuHeight > 0.4)
            menuBottomMain.isShown = true;
        else
            menuBottomMain.isShown = false;
    }

//    function setListIndex(wallId)
//    {
//        console.log("Wall ID <><><><><><><><> " + wallId)
//        room_faces_listview.currentIndex = wallId;
//    }

    states : [
        State
        {
            name : "menuShown"
            PropertyChanges
            {
                target: menuBottomMain
                width : maxMenuWidth
                height : maxMenuHeight
                y : maxMenuY

            }
            PropertyChanges
            {
                target: menuBottomRec
                opacity : mainWindow.menu_opacity_deployed
            }
            PropertyChanges
            {
                target: arrow_image
                opacity : 0
            }
            when : menuBottomMain.isShown
        },
        State
        {
            name : "menuHidden"
            PropertyChanges
            {
                target: menuBottomMain
                width : minMenuWidth
                height : minMenuHeight
                y : minMenuY

            }
            PropertyChanges
            {
                target: menuBottomRec
                opacity : mainWindow.menu_opacity_retracted
            }
            PropertyChanges
            {
                target: arrow_image
                opacity : 0.8
            }
            when :!menuBottomMain.isShown
        }

    ]

    transitions : [
        Transition
        {
            from : "menuHidden"
            to : "menuShown"
        },
        Transition
        {
            from : "menuShown"
            to : "menuHidden"
        }
    ]

    BorderImage
    {
        id: menuBottomRec
        source: "../Resources/Pictures/panel_bg2.png"
        width: parent.width; height: parent.height;
        border.left: 2; border.bottom: 1

        Loader
        {
            id : plugin_menu_loader
            anchors.fill: parent
            onLoaded:
            {
                "Menu Loaded"
            }
        }

//        Clock
//        {
//            anchors
//            {
//                verticalCenter : parent.verticalCenter
//                left : parent.left
//                leftMargin :  mainWindow.menuMinimumWidth
//            }

//        }

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
    }

}
