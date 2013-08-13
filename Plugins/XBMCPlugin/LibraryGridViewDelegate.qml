import QtQuick 2.1

Item
{
    id : delegate_item
    property alias title : title_text.text
    property alias thumbnail : show_image.source

    signal clicked()

    scale : delegate_ma.pressed ? 0.9 : 1
    Behavior on scale {NumberAnimation {duration : 200; easing.type: Easing.InOutBack}}

    Item
    {
        anchors.centerIn: parent
        scale : (delegate_item.height - 70) / show_image.height

        Image
        {
            id : show_image
            width : 180
            asynchronous : true
            anchors.centerIn: parent
            fillMode: Image.PreserveAspectFit
            onStatusChanged: {if (status == Image.Error) source = "empty_cd.png"}
            Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
            scale : (status == Image.Ready) ? 1 : 0
        }
        Image
        {
            id : cd_cover
            source : "dvdbox.png"
            anchors
            {
                left : show_image.left
                leftMargin : -23
                right : show_image.right
                rightMargin : -5
                top : show_image.top
                topMargin : -4
                bottom : show_image.bottom
                bottomMargin : -6
            }
            scale :show_image.scale
        }
    }
    Rectangle
    {
        color : "#0099ff"
        opacity : 0.3
        anchors
        {
            bottom : parent.bottom
        }
        anchors.fill: title_text
    }

    Text
    {
        id : title_text
        width : parent.width
        //        color : "#0066ff"
        styleColor : "#707070"
        style: Text.Raised
        //        styleColor: "#0099ff"
        color: "white"
        font.pixelSize: mainWindow.largeFontSize
        horizontalAlignment: Text.AlignHCenter
        wrapMode: Text.WrapAtWordBoundaryOrAnywhere
        clip : true
        anchors
        {
            bottom : parent.bottom
        }
    }
    MouseArea
    {
        id : delegate_ma
        anchors.fill: parent
        onClicked: delegate_item.clicked()
    }
}
