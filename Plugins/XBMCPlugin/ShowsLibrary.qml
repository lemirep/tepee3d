import QtQuick 2.0

Item
{
    id : shows_item
    property bool seasonView : false;
    anchors.fill: parent
    states : [
        State
        {
            name : "shows_view"
            AnchorChanges
            {
                target : shows_library_gridview
                anchors.top: shows_item.top
            }
            AnchorChanges
            {
                target : season_view_item
                anchors.bottom : shows_item.top
            }
            when : !seasonView
        },
        State
        {
            name : "season_view"
            AnchorChanges
            {
                target : shows_library_gridview
                anchors.top: shows_item.bottom
            }
            AnchorChanges
            {
                target : season_view_item
                anchors.bottom : shows_item.bottom
            }
            when : seasonView
        }]

    transitions: Transition {
        AnchorAnimation { duration: 250 }
    }


    Item
    {
        property alias model : seasons_listview.model

        id : season_view_item
        anchors
        {
            top : parent.top
            left : parent.left
            right : parent.right
            topMargin : 10
            bottomMargin : 10
        }
        ListView
        {
            id : seasons_listview
            anchors
            {
                fill: parent
                margins : 25
            }
            clip : true
            delegate : Component {
                Item
                {
                    id : season_delegate_item
                    width : seasons_listview.width
                    height : seasons_listview.width / 5
                    Rectangle
                    {
                        color : "black"
                        opacity : 0.1
                        border
                        {
                            width : 1
                            color : "white"
                        }
                        radius : 5
                        smooth : true
                        anchors.fill: parent
                    }
                    Item
                    {
                        id : season_image_item
                        width : parent.width / 4
                        anchors
                        {
                            left : parent.left
                            margins : 5
                            top : parent.top
                            bottom : parent.bottom
                        }
                        Rectangle
                        {
                            width : season_thumbnail.width
                            height : season_thumbnail.height
                            anchors
                            {
                                top : season_thumbnail.top
                                left : season_thumbnail.left
                                leftMargin : 8
                                topMargin : 8
                            }
                            radius : 2
                            color : "#44000000"
                            scale : season_thumbnail.scale
                        }
                        Image
                        {
                            id : season_thumbnail
                            height: parent.height - 50
                            fillMode: Image.PreserveAspectFit
                            source : (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
                            Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
                            scale : (status == Image.Ready) ? 1 : 0
                            anchors.centerIn: parent
                        }
                        Text
                        {
                            id : season_text
                            color : "white"
                            font.pixelSize: mainWindow.largeFontSize
                            text : "Season " + model.season + " (" + model.episode + ")";
                            anchors
                            {
                                top : season_thumbnail.bottom
                                topMargin : 5
                                horizontalCenter : season_thumbnail.horizontalCenter
                            }
                        }
                    }
                    ListView
                    {
                        id : episodes_listview
                        orientation: ListView.Horizontal
                        anchors
                        {
                            left : season_image_item.right
                            right : parent.right
                            top : parent.top
                            bottom : parent.bottom
                        }
                        model : seasons_listview.model.subModelFromId(season)
                        clip : true
                        spacing : 10
                        delegate : Component {
                            Item
                            {
                                width : episodes_listview.width / 4;
                                height : episodes_listview.height
                                scale : episode_delegate_ma.pressed ? 0.9 : 1
                                Item
                                {
                                    id : shadow_placement_item
                                    width : episode_thumbnail.paintedWidth
                                    height : episode_thumbnail.paintedHeight
                                    anchors.centerIn: episode_thumbnail
                                }
                                Rectangle
                                {
                                    width : episode_thumbnail.paintedWidth
                                    height : episode_thumbnail.paintedHeight
                                    anchors
                                    {
                                        top : shadow_placement_item.top
                                        left : shadow_placement_item.left
                                        leftMargin : 8
                                        topMargin : 8
                                    }
                                    radius : 2
                                    color : "#44000000"
                                    scale : season_thumbnail.scale
                                }
                                Image
                                {
                                    id : episode_thumbnail
                                    height: parent.height - 50
                                    width : parent.width - 10
                                    fillMode: Image.PreserveAspectFit
                                    source : (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
                                    Behavior on scale {NumberAnimation {duration : 1200; easing.type: Easing.InOutBack}}
                                    scale : (status == Image.Ready) ? 1 : 0
                                    anchors.centerIn: parent
                                }
                                Text
                                {
                                    id : episode_title
                                    color : "white"
                                    text : model.episodeNum + " - " + model.title
                                    font.pixelSize: mainWindow.defaultFontSize
                                    anchors
                                    {
                                        horizontalCenter : parent.horizontalCenter
                                        top : shadow_placement_item.bottom
                                        topMargin : 10                                   }
                                }
                                MouseArea
                                {
                                    id : episode_delegate_ma
                                    anchors.fill: parent
                                    onClicked:
                                    {
                                        XBMCPlugin.playFile(model.file)
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
        BackButton
        {
            width : 50
            onClicked : {shows_item.seasonView = false}
            anchors
            {
                right : parent.right
                bottom : parent.bottom
                margins : 5
            }
        }
    }

    GridView
    {
        id : shows_library_gridview
        anchors
        {
            left : parent.left
            right : parent.right
            bottom : parent.bottom
        }

        cellWidth : width / 5
        cellHeight : cellWidth
        model : XBMCPlugin.getTVShowsLibrary();
        clip : true
        delegate : LibraryGridViewDelegate {
            width : shows_library_gridview.cellWidth
            height :shows_library_gridview.cellHeight
            thumbnail: (model.thumbnail !== "") ? XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail) : "empty_cd.png"
            title : model.title
            onClicked:
            {
                console.log("Clicked")
                seasons_listview.model = shows_library_gridview.model.subModelFromId(model.tvShowId)
                shows_item.seasonView = true;
            }
        }
    }
}
