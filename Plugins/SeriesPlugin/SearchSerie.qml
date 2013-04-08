import QtQuick 2.0

Item
{
    id : search_bar_container
    smooth : true
    SerieBackground {anchors.fill: parent}
    Item
    {
        id : search_bar_series_item
        height : 40
        anchors
        {
            left : parent.left
            right : parent.right
            top : parent.top
            margins : 5
        }
        Rectangle
        {
            color : "black"
            opacity : 0.2
            smooth : true
            anchors.fill: parent
            radius : 15
            border
            {
                width : 2
                color : "gray"
            }
        }

        TextInput
        {
            id : search_input
            width : parent.width - 20
            enabled : (parent.opacity === 1)
            clip : true
            anchors
            {
                verticalCenter : parent.verticalCenter
                left : parent.left
                leftMargin : 10
            }
            color : "white"
            font.pointSize: 12
            onAccepted:    {SeriesPlugin.searchForShow(search_input.text); search_result.focus = true; search_input.text = ""}
        }

        Image
        {
            width : 40
            height : 40
            scale : search_button_ma.pressed ? 0.9 :1
            source : "mag_glass.png"
            anchors
            {
                right : parent.right
                verticalCenter : parent.verticalCenter
            }
            MouseArea
            {
                id : search_button_ma
                anchors.fill: parent
                onClicked:    {SeriesPlugin.searchForShow(search_input.text)}
            }
        }
    }

    Item
    {
        id : search_result
        anchors
        {
            top : search_bar_series_item.bottom
            margins : 5
            left : parent.left
            right : parent.right
            bottom : parent.bottom
        }
        ListView
        {
            id : search_result_listview
            clip : true
            anchors.fill: parent
            model : SeriesPlugin.getSearchSeriesModel()
            delegate : SeriesSearchListViewDelegate {
                slug : model.slug
                serieId : model.serieId
                img_src : model.imageUrl
                series_name: model.serieName
                width : parent.width
                height : 80
            }
        }
        BackButton
        {
            anchors
            {
                top : search_result_listview.bottom
                horizontalCenter : search_result_listview.horizontalCenter
            }
            onClicked : { SeriesPlugin.addShow = false; }
        }
    }
}
