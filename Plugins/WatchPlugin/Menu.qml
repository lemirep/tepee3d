import QtQuick 2.0

Item
{
    anchors.fill: parent
    state : WatchPlugin.pluginState

    states : [
        State
        {
            name : "add_clocks"
            PropertyChanges {target : add_clock_menu; opacity : 1}
            PropertyChanges {target : normal_menu; opacity : 0}
        },
        State
        {
            name : "clocks_view"
            PropertyChanges {target : add_clock_menu; opacity : 0}
            PropertyChanges {target : normal_menu; opacity : 1}
        },
        State
        {
            name : "edit_clocks"
            PropertyChanges {target : edit_clock_menu; opacity : 1}
            PropertyChanges {target : normal_menu; opacity : 0}
        },
        State
        {
            name : "remove_clocks"
            PropertyChanges {target : remove_clock_menu; opacity : 1}
            PropertyChanges {target : normal_menu; opacity : 0}
        }
    ]

    transitions: [
        Transition {
            NumberAnimation { target: edit_clock_menu; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
            NumberAnimation { target: normal_menu; property: "opacity"; duration: 750; easing.type: Easing.InOutQuad }
        }]

    Item
    {
        id : add_clock_menu
        enabled : opacity === 1
        opacity : 0
        anchors.fill: parent
        AddBox
        {
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin : parent.height / 3
            }
            //onClicked : {WatchPlugin.pluginState = "clocks_view"; menuBottomMain.isShown = false}
        }

    }
    Item
    {
        id : edit_clock_menu
        enabled : opacity === 1
        opacity : 0
        anchors.fill: parent
        EditBox
        {
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin : parent.height / 3
            }
            //onClicked : {WatchPlugin.pluginState = "clocks_view"; menuBottomMain.isShown = false}
        }

    }

    Item
    {
        id : remove_clock_menu
        enabled : opacity === 1
        opacity : 0
        anchors.fill: parent
        RemoveBox
        {
            anchors
            {
                verticalCenter: parent.verticalCenter
                left: parent.left
                leftMargin : parent.height / 3
            }
            //onClicked : {WatchPlugin.pluginState = "clocks_view"; menuBottomMain.isShown = false}
        }

    }
    Item
    {
        id : normal_menu
        enabled : opacity === 1
        anchors.fill: parent
        opacity : 1

        Item
        {
            width : add_clock_button_text.width
            height : parent.height
            anchors.right: parent.horizontalCenter
            anchors.rightMargin: parent.height / 3

            Image
            {
                id : add_clock_button
                width : 50
                height : 50

                smooth : true
                scale : add_clock_button_ma.pressed ? 0.9 : 1.0
                anchors    {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter : add_clock_button_text.horizontalCenter
                }
                MouseArea
                {
                    id : add_clock_button_ma
                    anchors.fill : parent
                    onClicked : WatchPlugin.pluginState = "add_clocks";
                }
                source : "./plus.png"
            }
            Text
            {
                id : add_clock_button_text
                text : "Add New Clock"
                font.pointSize: mainWindow.defaultFontSize
                color : "white"
                anchors
                {
                    top : add_clock_button.bottom
                    topMargin : 25
                }
            }
        }
        Item
        {
            id : edit_clock_item
            width : edit_clock_button_text.width
            height : parent.height
            anchors.horizontalCenter: parent.horizontalCenter
            Image
            {
                id : edit_clock_button
                width : 50
                height : 50

                smooth : true
                scale : edit_clock_button_ma.pressed ? 0.9 : 1.0
                anchors    {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter : edit_clock_button_text.horizontalCenter
                }
                MouseArea
                {
                    id : edit_clock_button_ma
                    anchors.fill : parent
                    onClicked : WatchPlugin.pluginState = "edit_clocks";
                }
                source : "./edit.png"
            }
            Text
            {
                id : edit_clock_button_text
                text : "Edit Clock"
                font.pointSize: mainWindow.defaultFontSize
                color : "white"
                anchors
                {
                    top : edit_clock_button.bottom
                    topMargin : 25
                }
            }
        }
        Item
        {
            width : remove_clock_button_text.width
            height : parent.height
            anchors.left : parent.horizontalCenter
            anchors.leftMargin: parent.height / 3
            Image
            {
                id : remove_clock_button
                width : 50
                height : 50
                smooth : true
                scale : remove_clock_button_ma.pressed ? 0.9 : 1.0
                anchors    {
                    verticalCenter: parent.verticalCenter
                    horizontalCenter : remove_clock_button_text.horizontalCenter
                }
                MouseArea
                {
                    id : remove_clock_button_ma
                    anchors.fill : parent
                    onClicked :
                    {

                        WatchPlugin.pluginState = "remove_clocks";
                    }
                }
                source : "./red_cross.png"
            }
            Text
            {
                id : remove_clock_button_text
                text : "Remove Clock"
                font.pointSize: mainWindow.defaultFontSize
                color : "white"
                anchors
                {
                    top : remove_clock_button.bottom
                    topMargin : 25
                }
            }
        }

    }
}
