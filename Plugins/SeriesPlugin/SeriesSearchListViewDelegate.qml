import QtQuick 2.0

Item
{
    id : search_serie_delegate

    property int serieId : -1;
    property string img_src : ""
    property string series_name : ""
    property string slug : ""

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
    AddButton
    {
        id : add_show_to_follow
        anchors
        {
            left : parent.left
            verticalCenter : parent.verticalCenter
        }
        onClicked :
        {
            SeriesPlugin.addShowToFollow(slug)
            SeriesPlugin.removeShowFromSearchResult(serieId)
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
        source : img_src.replace(".jpg", "-138.jpg")
    }
}
