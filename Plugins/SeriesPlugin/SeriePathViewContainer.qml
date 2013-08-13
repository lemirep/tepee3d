import QtQuick 2.1

Item
{
    id : show_pathview_item
    property alias currentIndex : show_pathview_container.currentIndex
    property alias currentItem : show_pathview_container.currentItem

    states : [
        State
        {
            name : "series_list_view"
            PropertyChanges {target : serie_listview_detail_flip; flipped : false}
            PropertyChanges {target: back_show_detailed_button; opacity : 0}
        },
        State
        {
            name : "series_detailed_view"
            PropertyChanges {target : serie_listview_detail_flip; flipped : true}
            PropertyChanges {target: back_show_detailed_button; opacity : 1}

        },
        State
        {
            name : "series_planning_view"
        }
    ]

    transitions : [
        Transition
        {
            NumberAnimation { target: back_show_detailed_button; property: "opacity"; duration: 200; easing.type: Easing.InOutQuad }
        }
    ]

    Component.onCompleted: {state = "series_list_view"}

    SeriePathView
    {
        id : show_pathview_container
        anchors
        {
            left : parent.left
            right : parent.horizontalCenter
            top : parent.top
            bottom : parent.bottom
        }
    }

    Flipable
    {
        id : serie_listview_detail_flip
        property bool flipped : false
        anchors
        {
            right : parent.right
            top : parent.top
            bottom : show_main_toolbar.top
            left : parent.horizontalCenter
            leftMargin : 100
            rightMargin : 100
            topMargin : 100
            bottomMargin : 10
        }

        transform: Rotation {
            id: rotation_flip
            origin.x: serie_listview_detail_flip.width / 2
            origin.y: serie_listview_detail_flip.height / 2
            axis.x: 0; axis.y: 1; axis.z: 0
            angle: 0
        }

        states: [
            State
            {
                PropertyChanges { target: rotation_flip; angle: 180 }
                PropertyChanges {target: serie_detailed_view; opacity : 1}
                PropertyChanges {target: serie_list_view; opacity : 0}
                when: serie_listview_detail_flip.flipped
            },
            State
            {
                PropertyChanges { target: rotation_flip; angle: 0 }
                PropertyChanges {target: serie_detailed_view; opacity : 0}
                PropertyChanges {target: serie_list_view; opacity : 1}
                when: !serie_listview_detail_flip.flipped
            }
        ]

        transitions: Transition {
            NumberAnimation { target: rotation_flip; property: "angle"; duration: 750 }
            NumberAnimation { target: serie_list_view; property: "opacity"; duration: 200; easing.type: Easing.InOutQuad }
            NumberAnimation { target: serie_detailed_view; property: "opacity"; duration: 200; easing.type: Easing.InOutQuad }
        }

        front : SerieListView {
            id : serie_list_view
            enabled : (opacity === 1)
            anchors.fill : parent
        }

        back :SeriesDetailedView {
            id : serie_detailed_view
            enabled : (opacity === 1)
            anchors.fill : parent
        }
    }

    Item
    {
        id : show_main_toolbar
        height : 60
        anchors
        {
            left : parent.horizontalCenter
            right : parent.right
            bottom : parent.bottom
            bottomMargin : 50
            leftMargin : 100
            rightMargin : 100
        }
        Rectangle
        {
            color : "grey"
            opacity : 0.4
            radius : 5
            anchors.fill: parent
            border
            {
                width : 1
                color : "white"
            }
        }
        Image
        {
            id : planning_button
            height : 50
            width : 50
            scale : planning_button_ma.pressed ? 0.9 : 1
            source : "planning.png"
            fillMode: Image.PreserveAspectFit
            MouseArea
            {
                id : planning_button_ma
                anchors.fill: parent
                onClicked: {SeriesPlugin.pluginState = "show_planning_view"}
            }
            anchors
            {
                verticalCenter : parent.verticalCenter
                left : parent.horizontalCenter
            }
        }

        BackButton
        {
            id : back_show_detailed_button
            anchors
            {
                bottom : parent.bottom
                right : parent.horizontalCenter
                leftMargin : 2
            }
            onClicked : {show_pathview_item.state = "series_list_view";}
        }
    }
}
