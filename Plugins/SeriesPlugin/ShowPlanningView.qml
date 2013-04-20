import QtQuick 2.0

Item
{

    Rectangle
    {
        anchors.fill: planned_show_gridview
        border
        {
            color : "white"
            width : 1
        }
        radius : 5
        color : "grey"
        opacity : 0.2
    }

    GridView
    {
        id : planned_show_gridview
        model : SeriesPlugin.getShowsToAppearInTheWeek()
        anchors.fill: parent
        anchors.margins : 50
        delegate : show_planning_delegate
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
            width : planned_show_gridview.width / 5
            height: width

            Rectangle
            {
                color : "transparent"
                border
                {
                    color : "white"
                    width : 1
                }
                opacity : 0.2
            }

            Text
            {
                id : serie_title_text
                width : parent.width - 20
                anchors
                {
                    top : parent.top
                    horizontalCenter : parent.horizontalCenter
                }
                clip : true
                color : "white"
                font.pixelSize: mainWindow.defaultFontSize
                text : model.serieName
            }

            Image
            {
                fillMode: Image.PreserveAspectFit
                width : parent.width - 20
                anchors
                {
                    horizontalCenter : parent.horizontalCenter
                    top : serie_title_text.bottom
                }
                source : model.imageUrl.replace(".jpg", "-138.jpg")
            }
        }
    }
}
