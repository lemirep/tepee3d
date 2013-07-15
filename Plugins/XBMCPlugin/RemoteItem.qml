
import QtQuick 2.0

Item
{
    id : remote_item
    property bool playerControlsVisible : false

    states : [
        State
        {
            name :  "remote_view"
            AnchorChanges {target: remote_controls; anchors.top : remote_item.top}
            AnchorChanges {target: player_controls; anchors.bottom : remote_item.top}
            PropertyChanges {target: remote_controls; opacity : 1}
            PropertyChanges {target: player_controls; opacity : 0}
            when : !playerControlsVisible
        },
        State
        {
            name : "player_view"
            AnchorChanges {target: remote_controls; anchors.top : remote_item.bottom}
            AnchorChanges {target: player_controls; anchors.bottom : remote_item.bottom}
            PropertyChanges {target: remote_controls; opacity : 0}
            PropertyChanges {target: player_controls; opacity : 1}
            when : playerControlsVisible
        }
    ]

    transitions: [
        Transition
        {
            AnchorAnimation {duration: 750}
            NumberAnimation {duration : 750; property : "opacity"}
        }
    ]

    RemoteControls
    {
        id : remote_controls
        anchors
        {
            left : parent.left
            right : parent.right
            bottom : parent.bottom
        }
    }

    PlayerControls
    {
        id : player_controls
        anchors
        {
            left : parent.left
            right : parent.right
            top : parent.top
        }
    }
}
