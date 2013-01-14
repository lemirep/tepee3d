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
        property int  minMenuHeight : mainWindow.height / 2
//    property int  minMenuHeight : mainWindow.height
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
            PropertyChanges
            {
                target: menuRightRec
                opacity : mainWindow.menu_opacity_deployed
            }
            PropertyChanges
            {
                target : room_plugins_list_view
                opacity : 1
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
            PropertyChanges
            {
                target: menuRightRec
                opacity : 0.3
            }
            PropertyChanges
            {
                target : room_plugins_list_view
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
            NumberAnimation
            {
                target : room_plugins_list_view
                properties : "opacity"
                duration : 250
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
            NumberAnimation
            {
                target : room_plugins_list_view
                properties : "opacity"
                duration : 150
            }
        }
    ]

    Rectangle
    {
        id : menuRightRec
        width : parent.width
        height : parent.height
        color : mainWindow.menu_background_color
        property bool add_plugins : false;
        opacity : 0


        states : [
            State
            {
                name : "currentRoomPlugins"
                AnchorChanges
                {
                    target : available_plugins_rect
                    anchors.left : menuRightRec.right
                }
                when : !menuRightRec.add_plugins
            },
            State
            {
                name : "availablePlugins"
                AnchorChanges
                {
                    target : available_plugins_rect
                    anchors.left : menuRightRec.left
                }
                when : menuRightRec.add_plugins
            }
        ]
        transitions: [
            Transition
            {
                from: "currentRoomPlugins"
                to: "availablePlugins"
                AnchorAnimation
                {
                    duration : 500
                    easing.type: Easing.OutQuad
                }
            },
            Transition
            {
                from: "availablePlugins"
                to: "currentRoomPlugins"
                AnchorAnimation
                {
                    duration : 500
                    easing.type: Easing.InQuart
                }
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
            delegate: plugin_list_delegate
            spacing: 10
        }

        Rectangle
        {
            id : available_plugins_rect
            width : parent.width
            height : parent.height

            color : "red"

            anchors
            {
                left : parent.right
            }

            ListView
            {
                id : available_plugins_list_view

                property real delegate_width :  menuRightMain.width / 2;
                property real delegate_height : menuRightMain.width / 3;


                opacity : 1
                enabled : (parent.opacity == 1)
                clip: true
                anchors
                {
                    fill: parent
                    left : parent.right
                    margins : menuRightMain.width / 8
                }

                orientation: ListView.Vertical
                model : availablePluginsModel
                delegate: plugin_list_delegate
                spacing: 10
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

            source : "Resources/Pictures/add_button.svg"
        }

        Component
        {
            id : plugin_list_delegate

            Item
            {
                id : item_plugin_del
                width : room_plugins_list_view.delegate_width
                height :room_plugins_list_view.delegate_height
                anchors.horizontalCenter: parent.horizontalCenter
                scale : plugin_delegate_mouse_area.pressed ? 0.9 : 1.0

                MouseArea
                {
                    id : plugin_delegate_mouse_area
                    anchors.fill : parent
                    onClicked :
                    {
                        room_plugins_list_view.currentIndex = index;
                        roomManager.addNewPluginToCurrentRoom(model.pluginId)
                    }
                }

                Rectangle
                {
                    color : (room_plugins_list_view.currentIndex == index) ? mainWindow.plugin_list_selected_component_color: mainWindow.plugin_list_component_color
                    anchors.fill: parent
                }

                Text
                {
                    id: plugin_title
                    text: model.pluginName
                    anchors
                    {
                        horizontalCenter : parent.horizontalCenter
                        bottom : parent.bottom
                        margins : 10
                    }
                    color :  "white"
                }
            }

        }

    }
}
