// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Item
{
    id : menuTopMain
    width: minMenuWidth
    height: minMenuHeight
    property bool isShown : false
    property int  minMenuHeight : mainWindow.height / 10
    property int  maxMenuHeight : mainWindow.height / 2
    property int  minMenuWidth : mainWindow.width / 2
    property int  maxMenuWidth : mainWindow.width
    property int  ySaved;
    property int  savedHeight;

    function startDrag(xPos, yPos)
    {
        ySaved = yPos;
        savedHeight = menuTopMain.height
    }

    function dragMoved(offsetX, offsetY)
    {
        var offset = offsetY;
        if ((savedHeight + offset) <=  maxMenuHeight &&
                (savedHeight + offset) >= minMenuHeight)
            menuTopMain.height = savedHeight + offset;
    }

    function  dragEnd()
    {
        if ((menuTopMain.height - minMenuHeight) / maxMenuHeight > 0.4)
        {
            if (menuTopMain.isShown)
                menuTopMain.isShown = false;
            menuTopMain.isShown = true;
        }
        else
        {
            if (!menuTopMain.isShown)
                menuTopMain.isShown = true;
            menuTopMain.isShown = false;
        }
    }

    states :     [
        State     {
            name: "menuShown"
            PropertyChanges
            {
                target: menuTopMain;
                height : maxMenuHeight
                width : maxMenuWidth
            }
            PropertyChanges {
                target: menuTopRec
                opacity : mainWindow.menu_opacity_deployed
            }
            when: menuTopMain.isShown
        },
        State {
            name: "menuHidden"
            PropertyChanges
            {
                target: menuTopMain
                height : minMenuHeight
                width : minMenuWidth
            }
            PropertyChanges {
                target: menuTopRec
                opacity : 0
            }
            when: !menuTopMain.isShown
        }]

    Rectangle
    {
        id : menuTopRec
        width : parent.width
        height : menuTopMain.height
        color : mainWindow.menu_background_color
        opacity : 0.2
        Behavior on height {NumberAnimation {duration: 100}}
        Behavior on width {PropertyAnimation { properties: "width"; easing.type: Easing.OutBounce; duration : 500 }}
        Behavior on opacity {NumberAnimation {duration: 500}}


        Text
        {

            text : getTime();

            Timer
            {
                running: true
                interval : 60000
                onTriggered:
                {
                    parent.text = parent.getTime();
                }
            }


            function getTime()
            {
                var d = new Date();
                return d.getHours() + ":" + d.getMinutes();
            }

            color : "white"
            anchors
            {
                bottom : parent.bottom
                horizontalCenter : parent.horizontalCenter
                margins : 10
            }
        }
    }

}
