// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.1

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

    onIsShownChanged: {menuRightMain.width = (menuRightMain.isShown) ? maxMenuWidth : minMenuWidth; menuRightRec.add_plugins = false}

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
            PropertyChanges    {target : room_plugins_list_view_item; opacity : 1}
            PropertyChanges    {target : add_plugin_button; opacity : 1}
            PropertyChanges    {target: arrow_image; opacity : 0}
            when: menuRightMain.isShown || (menuRightMain.width - minMenuWidth) / maxMenuWidth > 0.4
        },
        State {
            name: "menuHidden"
            PropertyChanges    {target: menuRightRec; opacity : mainWindow.menu_opacity_retracted}
            PropertyChanges    {target : add_plugin_button; opacity : 0}
            PropertyChanges    {target : room_plugins_list_view_item; opacity : 0}
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
                AnchorChanges    {target : room_plugins_list_view_item; anchors.right : menuRightRec.right}
                PropertyChanges    {target: room_plugins_list_view_item; opacity : 1}
                PropertyChanges    {target: available_plugins_rect; opacity : 0}
                when : !menuRightRec.add_plugins
            },
            State
            {
                name : "availablePlugins"
                AnchorChanges    {target : available_plugins_rect; anchors.left : menuRightRec.left}
                AnchorChanges    {target : room_plugins_list_view_item; anchors.right : menuRightRec.left}
                PropertyChanges    {target: room_plugins_list_view_item; opacity : 0}
                PropertyChanges    {target: available_plugins_rect; opacity : 1}
                when : menuRightRec.add_plugins
            }
        ]
        transitions: [
            Transition
            {
                from: "currentRoomPlugins"
                to: "availablePlugins"
                AnchorAnimation    {duration : 500; easing.type: Easing.OutQuad}
                NumberAnimation    {target : room_plugins_list_view_item; properties : "opacity"; duration : 100}
                NumberAnimation    {target : available_plugins_rect; properties : "opacity"; duration : 1500}
            },
            Transition
            {
                from: "availablePlugins"
                to: "currentRoomPlugins"
                AnchorAnimation    {duration : 500; easing.type: Easing.OutQuart}
                NumberAnimation    {target : room_plugins_list_view_item; properties : "opacity"; duration : 1500}
                NumberAnimation    {target : available_plugins_rect; properties : "opacity"; duration : 100}
            }
        ]

        Item
        {
            id : room_plugins_list_view_item
            anchors
            {
                left : parent.left
                top : parent.top
                bottom : parent.bottom
                margins : menuRightMain.width / 8
            }
            ListView
            {
                id : room_plugins_list_view
                clip: true
                anchors.fill: parent
                orientation: ListView.Vertical
                enabled : (parent.opacity === 1 && menuRightMain.isShown)
                spacing: 10
                model : roomModel.subModelFromId(mainWindow.currentRoomId);
                delegate: RoomPluginDelegate {
                    width : maxMenuWidth / 2
                    height : maxMenuWidth / 3
                    pluginName: model.pluginName
                    pluginId: model.pluginId
                }
            }
        }

        Item
        {
            id : available_plugins_rect
            anchors
            {
                right : parent.right
                top : parent.top
                bottom : parent.bottom
                bottomMargin : menuRightMain.width / 8
                leftMargin : menuRightMain.width / 8
                rightMargin : menuRightMain.width / 8
            }


            ListModel
            {
                id : add_plugin_listview_model
                ListElement
                {
                    title : "Downloaded Plugins"
                    idx : 0
                }
                ListElement
                {
                    title : "Online Plugins"
                    idx : 1
                }
            }

            ListView
            {
                id : available_plugins_title_listview
                orientation: ListView.Horizontal
                model : add_plugin_listview_model
                interactive: false
                anchors
                {
                    left : parent.left
                    right : parent.right
                    top : parent.top
                    bottom : available_plugins_master_list_view.top
                }
                delegate : Component {
                    Item
                    {
                        width : available_plugins_title_listview.width / 2
                        height : available_plugins_title_listview.height
                        Text
                        {
                            text : model.title
                            color : "white"
                            anchors.centerIn: parent
                        }
                        Rectangle
                        {
                            opacity : (index === available_plugins_master_list_view.currentIndex) ? 1 : 0
                            Behavior on opacity {NumberAnimation {duration : 200}}
                            color : "#0099ff"
                            anchors
                            {
                                left : parent.left
                                right : parent.right
                                bottom : parent.bottom
                            }
                            height : 4
                        }
                        MouseArea
                        {
                            anchors.fill: parent
                            onClicked: available_plugins_master_list_view.currentIndex = index
                        }
                    }
                }
            }

            ListView
            {
                id : available_plugins_master_list_view
                anchors
                {
                    left : parent.left
                    right : parent.right
                    bottom : parent.bottom
                    top : parent.top
                    topMargin : 50
                }
                model : add_plugin_listview_model
                orientation: ListView.Horizontal
                clip : true
                snapMode : ListView.SnapOneItem
                highlightRangeMode: ListView.StrictlyEnforceRange
                delegate : Component {
                    Item
                    {
                        width : available_plugins_rect.width
                        height : available_plugins_rect.height
                        ListView
                        {
                            id : available_plugins_list_view
                            clip: true
                            spacing: 10
                            anchors.fill: parent
                            anchors.bottomMargin : menuRightMain.width / 8
                            orientation: ListView.Vertical
                            model : idx === 0 ? availablePluginsModel : onlinePluginsModel
                            delegate: NewPluginDelegate {
                                width : maxMenuWidth / 2
                                height : maxMenuWidth / 3
                                pluginName: model.pluginName
                                downloaded: !(idx === 0) ? model.pluginDownloaded : false
                                downloading : !(idx === 0) ? model.pluginDownloading : false
                                error : !(idx === 0) ? model.pluginDownloadError : false
                                online : !(idx === 0)
                            }
                        }
                    }
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

            source : (!menuRightRec.add_plugins) ? "../Resources/Pictures/plus.png" : "../Resources/Pictures/back_curved_arrow.png"
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
