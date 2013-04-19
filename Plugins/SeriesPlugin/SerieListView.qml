import QtQuick 2.0

Item
{
    property alias currentIndex : serie_list_view.currentIndex

    Rectangle
    {
        color : "grey"
        opacity : 0.2
        anchors.fill: parent
        radius : 5
    }

    ListView
    {
        id : serie_list_view
        clip : true
        anchors.fill: parent
        model : show_pathview_container.model
        highlightFollowsCurrentItem: true
        preferredHighlightBegin: 0.5
        preferredHighlightEnd: 0.6
        onCurrentIndexChanged : {show_pathview_container.currentIndex = currentIndex}

        highlight: Component{
            Rectangle
            {
                width : serie_list_view.width
                height : 50
                radius : 5
                color : "#88006699"
                Rectangle
                {
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
            }
        }

        delegate : Component   {
            Item
            {
                width : serie_list_view.width
                height : 50

                Text
                {
                    id : serie_title
                    text : model.serieName
                    color : "white"
                    anchors
                    {
                        left : parent.left
                        verticalCenter : parent.verticalCenter
                        leftMargin : 10
                    }
                    font.pointSize: mainWindow.defaultFontSize
                }

                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        serie_list_view.currentIndex = index;
                    }
                }
            }
        }
    }
}
