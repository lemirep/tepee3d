import QtQuick 2.1

Item
{
    property int scheduleType : 1

    onEnabledChanged:
    {
        if (enabled)
            series_plugin.refreshShowsInPlanning(scheduleType)
    }

    onScheduleTypeChanged:
    {
        series_plugin.refreshShowsInPlanning(scheduleType)
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
        id : planning_tab
        spacing : 5
        height : 50
        anchors
        {
            left : background_rec.left
            right : background_rec.right
            top : background_rec.top
        }
        Item
        {
            width : ((background_rec.width - 10) / 3)
            height : parent.height
            Rectangle
            {
                color : scheduleType == 1 ? "#44006699": "transparent"
                anchors
                {
                    left : parent.left
                    top : parent.top
                    bottom : parent.bottom
                    right : separator_v_t.left
                }
            }
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
            Image
            {
                id : separator_v_t
                source : "shadow_separator_v.png"
                height : parent.height
                anchors
                {
                    right: parent.right
                }
                fillMode: Image.Stretch
                anchors.verticalCenter : parent.verticalCenter
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
        Item
        {
            width : ((background_rec.width - 10) / 3)
            height : parent.height
            Rectangle
            {
                color : scheduleType == 3 ? "#44006699": "transparent"
                anchors
                {
                    left : separator_v_m.right
                    top : parent.top
                    bottom : parent.bottom
                    right : parent.right
                }
            }
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
            Image
            {
                id : separator_v_m
                source : "shadow_separator_v.png"
                height : parent.height
                fillMode: Image.Stretch
                anchors
                {
                    left : parent.left
                    verticalCenter : parent.verticalCenter
                }
            }
        }
    }

    Image
    {
        id : separator_img
        anchors
        {
            top : planning_tab.bottom
            horizontalCenter : planning_tab.horizontalCenter
        }
        width : parent.width
        fillMode: Image.Stretch
        source : "shadow_separator_h.png"
    }

    GridView
    {
        id : planned_show_gridview
        model : series_plugin.getShowsToAppearInTheWeek()
        anchors
        {
            left : parent.left
            right : parent.right
            bottom : parent.bottom
            top : separator_img.bottom
            leftMargin : 30
            rightMargin : 30
            bottomMargin : 60
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
            right : background_rec.right
            bottom : background_rec.bottom
        }
        onClicked : {series_plugin.pluginState = "shows_view"}
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
