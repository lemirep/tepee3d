import QtQuick 2.0

Item
{
    property int scheduleType : 1

    onEnabledChanged:
    {
        if (enabled)
            SeriesPlugin.refreshShowsInPlanning(scheduleType)
    }

    onScheduleTypeChanged:
    {
        SeriesPlugin.refreshShowsInPlanning(scheduleType)
    }

    Rectangle
    {
        id : background_rec
        anchors.fill: parent
        anchors.margins: 50
        border
        {
            color : "white"
            width : 1
        }
        radius : 5
        color : "grey"
        opacity : 0.2
    }

    Row
    {
        spacing : 5
        anchors
        {
            left : background_rec.left
            right : background_rec.right
            top : background_rec.top
            bottom : planned_show_gridview.top
        }
        Rectangle
        {
            width : ((background_rec.width - 10) / 3)
            height : parent.height
            color : scheduleType == 1 ? "#44006699": "transparent"

            Text
            {
                anchors.centerIn: parent
                text : "Tonight"
                color : "white"
                font.pixelSize: mainWindow.largeFontSize
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked: scheduleType = 1
            }

        }
        Rectangle
        {
            width : ((background_rec.width - 10) / 3)
            height : parent.height
            color : scheduleType == 2 ? "#44006699": "transparent"
            Text
            {
                anchors.centerIn: parent
                text : "This week"
                color : "white"
                font.pixelSize: mainWindow.largeFontSize
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked: scheduleType = 2
            }
        }
        Rectangle
        {
            width : ((background_rec.width - 10) / 3)
            height : parent.height
            color : scheduleType == 3 ? "#44006699": "transparent"
            Text
            {
                anchors.centerIn: parent
                text : "This month"
                color : "white"
                font.pixelSize: mainWindow.largeFontSize
            }
            MouseArea
            {
                anchors.fill: parent
                onClicked: scheduleType = 3
            }
        }
    }

    GridView
    {
        id : planned_show_gridview
        model : SeriesPlugin.getShowsToAppearInTheWeek()
        anchors
        {
            fill: background_rec
            topMargin : 50
        }
        delegate : show_planning_delegate
        cellWidth: width / 5
        cellHeight: cellWidth
        clip : true
    }

    BackButton
    {
        id : back_button
        anchors
        {
            right : planned_show_gridview.right
            bottom : planned_show_gridview.bottom
        }
        onClicked : {SeriesPlugin.pluginState = "shows_view"}
    }

    Component
    {
        id : show_planning_delegate
        Item
        {
            id : show_delegate_item
            width : planned_show_gridview.width / 5
            height: width
            scale : show_delegate_ma.pressed ? 0.9 : 1

            Image
            {
                id : serie_image
                fillMode: Image.PreserveAspectFit
                width : parent.width - 20
                height : show_delegate_item.height - 30
                anchors
                {
                    horizontalCenter : parent.horizontalCenter
                    top : parent.top
                    topMargin : 4
                }
                source : model.imageUrl.replace(".jpg", "-138.jpg")
                Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
                scale : (status == Image.Ready) ? 1 : 0
            }

            Text
            {
                id : serie_title_text
                width : show_delegate_item.width
                horizontalAlignment: Text.AlignHCenter
                anchors
                {
                    bottom : parent.bottom
                    bottomMargin : 5
                }

                clip : true
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                color : "white"
                font.pixelSize: mainWindow.defaultFontSize
                text : model.serieName
            }

            MouseArea
            {
                id : show_delegate_ma
                anchors.fill: parent
            }
        }
    }
}
