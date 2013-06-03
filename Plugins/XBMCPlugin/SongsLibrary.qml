import QtQuick 2.0

Item
{
    anchors.fill: parent
    GridView
    {
        id : sons_library_gridview
        anchors.fill: parent
        model : XBMCPlugin.getSongsLibrary();
        cellWidth : width / 5
        cellHeight : cellWidth
        delegate : Component {
            Item
            {
                width : sons_library_gridview.cellWidth
                height : sons_library_gridview.cellHeight
                Rectangle
                {
                    width : song_image.width
                    height : song_image.height
                    anchors
                    {
                        top : song_image.top
                        left : song_image.left
                        leftMargin : 8
                        topMargin : 8
                    }
                    radius : 2
                    color : "#44000000"
                    scale : song_image.scale
                }
                Image
                {
                    id : song_image
                    height : parent.height - 30
                    anchors
                    {
                        topMargin : 5
                        horizontalCenter: parent.horizontalCenter
                        top: parent.top
                    }
                    asynchronous : true
                    fillMode: Image.PreserveAspectFit
                    source : XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
                    Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
                    scale : (status == Image.Ready) ? 1 : 0
                    onStatusChanged: {if (status == Image.Error) source = "empty_cd.png"}
                }
                Image
                {
                    id : cd_cover
                    source : "cdbox.png"
                    anchors
                    {
                        left : song_image.left
                        leftMargin : -21
                        right : song_image.right
                        rightMargin : -5
                        top : song_image.top
                        topMargin : -8
                        bottom : song_image.bottom
                        bottomMargin : -6
                    }
                     scale : song_image.scale
                }
                Text
                {
                    id : title_text
                    text : model.title
                    width : parent.width
                    color : "white"
                    font.pixelSize: mainWindow.defaultFontSize
                    horizontalAlignment: Text.AlignHCenter
                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
                    clip : true
                    anchors
                    {
                        bottom : parent.bottom
                        bottomMargin : 8
                    }
                }
            }
        }
    }
}
