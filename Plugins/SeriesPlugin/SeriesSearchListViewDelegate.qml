import QtQuick 2.0

Item
{
    id : search_serie_delegate

    property int serieId : -1;
    property string img_src : ""
    property string series_name : ""

    scale : search_series_delegate_ma.pressed ? 0.9 : 1.0
    Behavior on scale {SmoothedAnimation {velocity : 10}}

    Rectangle
    {
        id : search_serie_delegate_bg
        color : "grey"
        opacity : 0.4
        border
        {
            width : 1
            color : "darkgrey"
        }
        radius : 15
        anchors.fill: parent
        smooth : true
    }


    Image
    {
        id : add_show_to_follow
        scale : add_show_to_follow_ma.pressed ? 0.9 : 1.0
        height : parent.height - 20
        fillMode: Image.PreserveAspectFit
        source : "plus.png"
        anchors
        {
            left : parent.left
            verticalCenter : parent.verticalCenter
        }

        MouseArea
        {
            id : add_show_to_follow_ma
            anchors.fill: parent
            onClicked :
            {
                SeriesPlugin.addShowToFollow(series_name)
                SeriesPlugin.removeShowFromSearchResult(serieId)
            }
        }
    }

    Text
    {
        id : search_series_delegate_text
        anchors
        {
            left : add_show_to_follow.right
            verticalCenter : parent.verticalCenter
            leftMargin : 10
        }
        color : "white"
        text : series_name
    }
    Image
    {
        id : search_series_delegate_pic
        fillMode: Image.PreserveAspectFit
        height : parent.height - 10
        cache : true
        anchors
        {
            right : parent.right
            verticalCenter : parent.verticalCenter
            margins : 10
        }
        asynchronous : true
        source : img_src
    }
    MouseArea
    {
        id : search_series_delegate_ma
        anchors
        {
            left : add_show_to_follow.right
            right : parent.right
            top : parent.top
            bottom : parent.bottom
        }
        onClicked:
        {
            cube_effect.texture = img_src
            rotate_cube.restart()
            search_result_listview.currentIndex = index;
        }
    }
}
