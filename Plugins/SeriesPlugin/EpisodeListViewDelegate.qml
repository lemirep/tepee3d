import QtQuick 2.0

Item
{
    id : episode_delegate_item

    property int episodeNumber
    property date episodeAiring
    property string episodeTitle
    property string episodeOverview
    property string img_src
    property string episodeSickbeardStatus

    property real rotAngle : PathView.onPath ? PathView.delAngle : 0
    property bool isCurrentItem : PathView.isCurrentItem

    z : PathView.onPath ? PathView.delZ : 0
    scale : PathView.onPath ? PathView.delScale : 0
    opacity :PathView.onPath ? PathView.delOpacity : 0
    Behavior on scale {NumberAnimation { duration: 750; easing.type: Easing.OutElastic }}

    onIsCurrentItemChanged: {if (isCurrentItem && !rotate_cube.running)rotate_cube.restart()}

    transform: [Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: rotAngle}]

    Rectangle
    {
        color : "black"
        opacity : 0.4
        anchors.fill: parent
        border
        {
            width : 1
            color : isCurrentItem ? "white" : "black"
        }
    }
    Text
    {
        id : episode_delegate_nbr_text
        anchors
        {
            top : parent.top
            left :parent.left
            margins : 2
        }
        color : "white"
        text : episodeNumber
        font.pointSize: 14
    }

    Text
    {
        id : episode_delegate_text
        clip : true
        elide: Text.ElideRight
        anchors
        {
            margins : 4
            top : episode_delegate_nbr_text.bottom
            left : episode_delegate_nbr_text.right
        }
        color : "white"
        text : episodeTitle
        font.pointSize: 13
    }

    Text
    {
        id : episode_delegate__airing_text
        anchors
        {
            right : parent.right
            top : parent.top
            margins : 4
        }
        color : "white"
        text : episodeAiring.getHours() + ":"
               + ((episodeAiring.getMinutes() < 10) ? ("0" + episodeAiring.getMinutes()) : episodeAiring.getMinutes())
               + "-" + episodeAiring.getDate()
               + "/" + (episodeAiring.getMonth() + 1)
               + "/" + episodeAiring.getFullYear()
    }

    Item
    {
        visible : (show_pathview_container.currentItem) ? show_pathview_container.currentItem.serie_on_sickbeard : false
        anchors
        {
            left : parent.left
            bottom : parent.bottom
        }

        Image
        {
            id : sickbeard
            source : "sickbeard_logo.png"
            width : 20
            fillMode: Image.PreserveAspectFit
            anchors
            {
                bottom : parent.bottom
                left : parent.left
                margins : 4
            }
        }
        Text
        {
            id : sickbeard_status
            text : episodeSickbeardStatus
            anchors
            {
                left : sickbeard.right
                top : sickbeard.top
                leftMargin : 10
            }
            color : "white"
            font.pointSize: 13
        }
    }

    OkButton
    {
        id : seen
        width : 20
        anchors
        {
            bottom : parent.bottom
            right : parent.right
            rightMargin : 10
        }
    }

    //    back : Item {
    //        id : back_item
    //        anchors.fill: parent
    //        anchors.margins : -100
    //        enabled : flipped

    //        Rectangle
    //        {
    //            color : "black"
    //            opacity : 0.4
    //            anchors.fill: parent
    //            border
    //            {
    //                width : 1
    //                color : isCurrentItem ? "white" : "black"
    //            }
    //        }
    //        Text
    //        {
    //            id : episode_delegate_nbr_text_back
    //            anchors
    //            {
    //                top : parent.top
    //                left :parent.left
    //                margins : 2
    //            }
    //            color : "white"
    //            text : episodeNumber
    //            font.pointSize: 14
    //        }

    //        Text
    //        {
    //            id : episode_delegate_text_back
    //            clip : true
    //            elide: Text.ElideRight
    //            anchors
    //            {
    //                margins : 4
    //                top : episode_delegate_nbr_text_back.bottom
    //                left : episode_delegate_nbr_text_back.right
    //            }
    //            color : "white"
    //            text : episodeTitle
    //            font.pointSize: 13
    //        }
    //        Text
    //        {
    //            id : episode_delegate__airing_text_back
    //            anchors
    //            {
    //                right : parent.right
    //                top : parent.top
    //                margins : 4
    //            }
    //            color : "white"
    //            text : episodeAiring.getHours() + ":"
    //                   + ((episodeAiring.getMinutes() < 10) ? ("0" + episodeAiring.getMinutes()) : episodeAiring.getMinutes())
    //                   + "-" + episodeAiring.getDate()
    //                   + "/" + (episodeAiring.getMonth() + 1)
    //                   + "/" + episodeAiring.getFullYear()
    //        }

    //        Flickable
    //        {
    //            clip : true
    //            anchors
    //            {
    //                top : episode_delegate_text_back.bottom
    //                left : parent.left
    //                right : parent.right
    //                bottom : parent.bottom
    //                topMargin : 5
    //                leftMargin : 10
    //                rightMargin : 10
    //            }
    //            flickableDirection: Flickable.VerticalFlick
    //            contentWidth: parent.width - 20
    //            contentHeight: flickable_item.height
    //            Item
    //            {
    //                id : flickable_item
    //                width : parent.width
    //                height: episode_overview_text.height + episode_delegate_pic.height
    //                Image
    //                {
    //                    id : episode_delegate_pic
    //                    fillMode : Image.PreserveAspectFit
    //                    asynchronous : true
    //                    width : parent.width - 20
    //                    anchors
    //                    {
    //                        top : parent.top
    //                        left : parent.left
    //                        right : parent.right
    //                        leftMargin : 20
    //                        topMargin : 5
    //                    }
    //                    cache : true
    //                    source : img_src
    //                }

    //                Text
    //                {
    //                    id : episode_overview_text
    //                    text : episodeOverview
    //                    width : parent.width - 20
    //                    wrapMode: Text.WrapAtWordBoundaryOrAnywhere
    //                    anchors
    //                    {
    //                        top : episode_delegate_pic.bottom
    //                        topMargin : 5
    //                    }

    //                    color : "white"
    //                    font.pointSize: 12
    //                }
    //            }
    //        }
    //    }

    MouseArea
    {
        id : episode_delegate_ma
        anchors.fill: parent
        onClicked:
        {
            followed_series_episodes_pathview.currentIndex = index;
            console.log("path")
            if (isCurrentItem)
            {
                detailed_episode_view.title = episodeTitle
                detailed_episode_view.summary = episodeOverview
                detailed_episode_view.image_src = img_src.replace(".jpg", "-218.jpg")
                seriesplugin_item.consultingEpisode = true
            }
        }
    }
}
