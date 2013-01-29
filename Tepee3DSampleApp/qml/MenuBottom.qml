import QtQuick 2.0


Item
{
    id : menuBottomMain
    width : minMenuWidth
    height : minMenuHeight

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
        source: "Resources/Pictures/panel_bg2.png"
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

    }

}
