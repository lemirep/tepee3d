// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Item
{
    id : menuRightMain
    width: minMenuWidth
    height: minMenuHeight

    anchors.right: parent.right

    property bool isShown : false
    property int  minMenuWidth : mainWindow.menuMinimumWidth
    property int  maxMenuWidth : mainWindow.width / 3
    property int  minMenuX : mainWindow.width - minMenuWidth
    property int  maxMenuX : mainWindow.width - maxMenuWidth
    property int  minMenuHeight : mainWindow.height
    property int  maxMenuHeight : mainWindow.height
    property int  offsetSaved;
    property int  xSaved;
    property bool isPressed;

    Behavior on width {NumberAnimation {duration : 200}}

    Component.onCompleted: {mainWindow.roomChanged.connect(unsetListIndex);
        mainWindow.roomFaceIdChanged.connect(unsetListIndex)}

    onIsShownChanged: {menuRightMain.width = (menuRightMain.isShown) ? maxMenuWidth : minMenuWidth}

    function unsetListIndex()
    {
        room_plugins_list_view.currentIndex = -1;
    }

    function startDrag(xPos, yPos)
    {
        xSaved = xPos;
    }

    function dragMoved(offsetX, offsetY)
    {
        var newX = offsetX + xSaved;
        if (newX <= minMenuX && newX >= maxMenuX)
            menuRightMain.width = mainWindow.width - newX;
        offsetSaved = offsetX
    }

    function dragEnd()
    {
        var oldstate = menuRightMain.isShown;
        var deployed = (menuRightMain.width - minMenuWidth) / maxMenuWidth > 0.4
        var dragLength = 30
        if (offsetSaved < -dragLength)
            menuRightMain.isShown = true;
        else if (offsetSaved > dragLength)
            menuRightMain.isShown = false;
        else
            menuRightMain.isShown = deployed
        if (oldstate === menuRightMain.isShown)
            menuRightMain.width = (menuRightMain.isShown) ? maxMenuWidth : minMenuWidth
    }

    states :     [
        State     {
            name: "menuShown"
            PropertyChanges    {target: menuRightRec; opacity : mainWindow.menu_opacity_deployed}
            PropertyChanges    {target : room_plugins_list_view; opacity : 1}
            PropertyChanges    {target : add_plugin_button; opacity : 1}
            PropertyChanges    {target: arrow_image; opacity : 0}
            when: menuRightMain.isShown || (menuRightMain.width - minMenuWidth) / maxMenuWidth > 0.4
        },
        State {
            name: "menuHidden"
            PropertyChanges    {target: menuRightRec; opacity : mainWindow.menu_opacity_retracted}
            PropertyChanges    {target : add_plugin_button; opacity : 0}
            PropertyChanges    {target : room_plugins_list_view; opacity : 0}
            PropertyChanges    {target: arrow_image; opacity : 0.8}
            when: !menuRightMain.isShown || !((menuRightMain.width - minMenuWidth) / maxMenuWidth > 0.4)
        }]

    transitions :    [
        Transition
        {
            NumberAnimation    {target : menuRightRec; properties : "opacity"; duration : 200}
        }
    ]

    BorderImage
    {
        id : menuRightRec
        //        width : parent.width
        //        height : parent.height
        anchors.fill: parent
        source : "../Resources/Pictures/panel_bg2.png"
        property bool add_plugins : false;
        opacity : 0

        border
        {
            left : 2
            bottom : 1
        }

        states : [
            State
            {
                name : "currentRoomPlugins"
                AnchorChanges    {target : available_plugins_rect; anchors.left : menuRightRec.right}
                PropertyChanges    {target: room_plugins_list_view; opacity : 1}
                when : !menuRightRec.add_plugins
            },
            State
            {
                name : "availablePlugins"
                AnchorChanges    {target : available_plugins_rect; anchors.left : menuRightRec.left}
                PropertyChanges    {target: room_plugins_list_view; opacity : 0}
                when : menuRightRec.add_plugins
            }
        ]
        transitions: [
            Transition
            {
                from: "currentRoomPlugins"
                to: "availablePlugins"
                AnchorAnimation    {duration : 500; easing.type: Easing.OutQuad}
                SmoothedAnimation    {target : room_plugins_list_view; properties : "opacity"; duration : -1; velocity : 10}
            },
            Transition
            {
                from: "availablePlugins"
                to: "currentRoomPlugins"
                AnchorAnimation    {duration : 500; easing.type: Easing.InQuart}
                SmoothedAnimation    {target : room_plugins_list_view; properties : "opacity"; duration : -1; velocity : 0.5}
            }
        ]

        ListView
        {
            id : room_plugins_list_view

            property real delegate_width :  menuRightMain.width / 2;
            property real delegate_height : menuRightMain.width / 3;

            opacity : 0
            enabled : (parent.opacity == 1)
            clip: true
            anchors
            {
                fill: parent
                margins : menuRightMain.width / 8
            }
            orientation: ListView.Vertical
            model : roomModel.subModelFromId(mainWindow.currentRoomId);
            delegate: RoomPluginDelegate {
                width : menuRightMain.width / 2
                height : menuRightMain.width / 3
                pluginName: model.pluginName
                pluginId: model.pluginId
            }
            spacing: 10
        }

        Item
        {
            id : available_plugins_rect
            width : parent.width
            height : parent.height
            enabled : menuRightRec.add_plugins
            anchors.left : parent.right

            ListView
            {
                id : available_plugins_list_view
                opacity : 1
                enabled : (parent.opacity == 1)
                clip: true
                spacing: 10
                anchors
                {
                    fill: parent
                    left : parent.right
                    margins : menuRightMain.width / 8
                }
                orientation: ListView.Vertical
                model : availablePluginsModel
                delegate: NewPluginDelegate {
                    width : menuRightMain.width / 2
                    height : menuRightMain.width / 3
                    pluginName: model.pluginName
                }
            }
        }

        Image
        {
            id : add_plugin_button
            width : 50
            height : 50
            smooth : true
            scale : add_plugin_button_ma.pressed ? 0.9 : 1.0
            anchors
            {
                bottom : parent.bottom
                horizontalCenter : parent.horizontalCenter
            }
            MouseArea
            {
                id : add_plugin_button_ma
                anchors.fill : parent
                onClicked :
                {
                    menuRightRec.add_plugins = !menuRightRec.add_plugins
                }
            }

            source : "../Resources/Pictures/plus.png"
        }

        //        Component
        //        {
        //            id : plugin_list_delegate
        //        }

    }
    Image
    {
        id : arrow_image
        anchors.centerIn: parent
        source : "../Resources/Pictures/arrow.png"
        fillMode: Image.PreserveAspectFit
        Behavior on opacity {SmoothedAnimation {velocity : 10}}
        rotation : 90
        height : mainWindow.menuMinimumWidth
        scale : isPressed ? 0.9 :  1
    }
}
