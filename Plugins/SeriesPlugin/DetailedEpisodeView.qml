import QtQuick 2.0

Item
{
    id : detail_view_item
    width : mainWindow.width / 2
    height : mainWindow.height/ 2
    x : (mainWindow.width - width) / 2
    property alias title : episodeTitle.text
    property alias summary : episodeSummary.text
    property bool isShown : false;

    states : [
    State
        {
            name : "viewShown"
            PropertyChanges {target : detail_view_item; y : (mainWindow.height - detail_view_item.height) / 2}
            PropertyChanges {target : detail_view_item; opacity : 1}
            when : isShown
        },
        State
        {
            name : "viewHidden"
            PropertyChanges {target : detail_view_item; y : -mainWindow.height}
            PropertyChanges {target : detail_view_item; opacity : 0}
            when : !isShown
        }
        ]

    transitions : [
        Transition
        {
            SmoothedAnimation {target : detail_view_item; properties : "y"; duration : 750; velocity : 50}
            SmoothedAnimation {target : detail_view_item; properties : "opacity"; duration : 2000; velocity : 1}
        }
    ]

    Rectangle
    {
        color : "grey"
        opacity : 0.4
        anchors.fill: parent
    }

    Text
    {
        id : episodeTitle
        color : "white"
        width : parent.width -10
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        anchors
        {
            top : parent.top
            left : parent.left
            margins : 10
        }
    }

    Text
    {
        id : episodeSummary
        color : "white"
        width : parent.width - 20
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        anchors
        {
            top : episodeTitle.bottom
            left : parent.left
            topMargin : 20
            leftMargin : 10
            rightMargin : 10
        }
    }

    CloseButton
    {
        anchors
        {
            right : parent.right
            bottom : parent.bottom
        }
        onClicked :
        {
            isShown = false;
            seriesplugin_item.listviewRotateAngle = 15;
        }
    }
}

