import QtQuick 2.1

Item
{
    property alias currentIndex : serie_list_view.currentIndex

    Rectangle
    {
        color : "grey"
        opacity : 0.2
        anchors.fill: parent
        radius : 5
        border
        {
            width : 1
            color : "white"
        }
    }

    ListView
    {
        id : serie_list_view
        clip : true
        anchors.fill: parent
        model : show_pathview_container.model
        highlightFollowsCurrentItem: true
        highlightRangeMode : ListView.StrictlyEnforceRange
        highlight: Component{
            Rectangle
            {
                width : serie_list_view.width
                height : 50
                radius : 5
                color : "#88006699"
                Rectangle
                {
                    opacity : 0.4
                    radius : 5
                    anchors.fill : parent
                    gradient : Gradient {
                        GradientStop { position: 0;    color: "#88FFFFFF" }
                        GradientStop { position: .1;   color: "#55FFFFFF" }
                        GradientStop { position: .5;   color: "#33FFFFFF" }
                        GradientStop { position: .501; color: "#11000000" }
                        GradientStop { position: .8;   color: "#11FFFFFF" }
                        GradientStop { position: 1;    color: "#55FFFFFF" }
                    }
                }
                ForwardButton
                {
                    anchors
                    {
                        verticalCenter : parent.verticalCenter
                        right : parent.right
                    }
                }
            }
        }

        delegate : Component   {
            Item
            {
                width : serie_list_view.width
                height : 50
                scale : delegate_serie_ma.pressed ? 0.9 : 1.0

                Rectangle
                {
                    visible: (index > 0)
                    color : "white"
                    height: 1
                    opacity : 0.4
                    anchors
                    {
                        left : parent.left
                        top : parent.top
                        right : parent.right
                        leftMargin : 40
                        rightMargin : 40
                    }
                }

                Text
                {
                    id : serie_title
                    text : model.serieName
                    color : "white"
                    width : parent.width - 40
                    clip : true
                    elide: Text.ElideRight
                    anchors
                    {
                        left : parent.left
                        verticalCenter : parent.verticalCenter
                        leftMargin : 10
                    }
                    font.pixelSize: mainWindow.largeFontSize
                }

//                Image
//                {
//                    visible : model.serieOnSickbeard
//                    height : 25
//                    anchors
//                    {
//                        right : parent.right
//                        verticalCenter : parent.verticalCenter
//                        rightMargin : 10
//                    }
//                    fillMode: Image.PreserveAspectFit
//                    source : "sickbeard_logo.png"
//                }

                MouseArea
                {
                    id : delegate_serie_ma
                    anchors.fill: parent
                    onClicked:
                    {
                        if (serie_list_view.currentIndex === index)
                            show_pathview_item.state = "series_detailed_view";
                        else
                        {
                            serie_list_view.currentIndex = index;
                            show_pathview_container.currentIndex = currentIndex
                        }
                    }
                }
            }
        }
    }
}
