// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Item
{
    id : menuRightMain
    width: minMenuWidth
    height: minMenuHeight
    x : minMenuX

    property bool isShown : false
    property int  minMenuWidth : mainWindow.width / 10
    property int  maxMenuWidth : mainWindow.width / 3
    property int  minMenuX : mainWindow.width - minMenuWidth
    property int  maxMenuX : mainWindow.width - maxMenuWidth
//    property int  minMenuHeight : mainWindow.height / 2
    property int  minMenuHeight : mainWindow.height
    property int  maxMenuHeight : mainWindow.height
    property int  xSaved;
    property int  savedWidth;

    function startDrag(xPos, yPos)
    {
        xSaved = xPos;
    }

    function dragMoved(offsetX, offsetY)
    {
        var newX = offsetX + xSaved;
        if (newX <= minMenuX && newX >= maxMenuX)
        {
            menuRightMain.x = newX
            menuRightMain.width = mainWindow.width - newX;
        }
    }

    function dragEnd()
    {
        if ((menuRightMain.width - minMenuWidth) / maxMenuWidth > 0.4)
        {
            if (menuRightMain.isShown)
                menuRightMain.isShown = false;
            menuRightMain.isShown = true;
        }
        else
        {
            if (!menuRightMain.isShown)
                menuRightMain.isShown = true;
            menuRightMain.isShown = false;
        }
    }

    states :     [
        State     {
            name: "menuShown"
            PropertyChanges
            {
                target: menuRightMain;
                width : maxMenuWidth
                height : maxMenuHeight
                x: maxMenuX
            }
            PropertyChanges {
                target: menuRightRec
                opacity : mainWindow.menu_opacity_deployed
            }
            when: menuRightMain.isShown
        },
        State {
            name: "menuHidden"
            PropertyChanges
            {
                target: menuRightMain
                x : minMenuX
                height : minMenuHeight
                width : minMenuWidth
            }
            PropertyChanges {
                target: menuRightRec
                opacity : 0
            }
            when: !menuRightMain.isShown
        }]

    transitions :    [
        Transition
        {
            from: "menuHidden"
            to: "menuShown"
            NumberAnimation
            {
                target : menuRightRec
                properties : "width, opacity"
                duration : 200
            }
        },
        Transition
        {
            from: "menuShown"
            to: "menuHidden"
            NumberAnimation
            {
                target : menuRightRec
                properties : "width, opacity"
                duration : 200
            }
        }
    ]

    Rectangle
    {
        id : menuRightRec
        width : parent.width
        height : parent.height
        color : mainWindow.menu_background_color
        opacity : 0.2
//        Behavior on x {NumberAnimation {duration: 100}}
//        Behavior on opacity {NumberAnimation {duration: 500}}
//        Behavior on height {PropertyAnimation { properties: "height"; easing.type: Easing.OutBounce; duration : 500 }}
    }
}
