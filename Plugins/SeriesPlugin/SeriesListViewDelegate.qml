import QtQuick 2.0

Item
{
    id : followed_serie_delegate

    property int serieId : -1;
    property string img_src : ""
    property string series_name : ""    

    scale : followed_series_delegate_ma.pressed ? 0.9 : 1.0

    Rectangle
    {
        id : followed_serie_delegate_bg
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

    Text
    {
        id : followed_series_delegate_text
        anchors
        {
            left : parent.left
            verticalCenter : parent.verticalCenter
            leftMargin : 10
        }
        color : "white"
        text : series_name
    }

    Image
    {
        id : followed_series_delegate_pic
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
        id : followed_series_delegate_ma
        anchors.fill: parent
        onClicked:
        {
            cube_effect.texture = img_src
            rotate_cube.restart()
            followed_series_listview.currentIndex = index;
            console.log("serieId " + serieId)
            season_list_view.model = SeriesPlugin.getSeasonsModelFromSerieId(serieId)
            episodes_series_listview.model = null;
        }
    }
}
