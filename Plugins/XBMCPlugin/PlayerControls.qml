import QtQuick 2.1

Item
{
    property bool isPlaying : XBMCPlugin.playing

    Item
    {
        anchors
        {
            top : parent.top
            bottom : control_column.top
            left : parent.left
            right : parent.right
            bottomMargin : 10
        }

        Rectangle
        {
            color : "black"
            opacity : 0.1
            anchors.fill: parent
            radius : 5
            smooth : true
            border
            {
                width : 1
                color : "white"
            }
        }


        ListView
        {
            id : currently_playing_item

            function printDuration(duration)
            {
                var hours = Math.floor(duration / 3600)
                var minutes = Math.floor((duration % 3600) / 60)
                var secondes = Math.floor((duration % 3600) % 60)

                if (hours < 10)
                    hours = "0" + hours
                if (minutes < 10)
                    minutes = "0" + minutes
                if (secondes < 10)
                    secondes = "0" + secondes
               return hours + ":" + minutes + ":" + secondes
            }

            anchors
            {
                left : parent.left
                right : parent.horizontalCenter
                top : parent.top
                bottom : parent.bottom
            }
            model : XBMCPlugin.getCurrentlyPlayedItemModel()
            interactive : false
            delegate : Component {
                Item
                {
                    width : currently_playing_item.width
                    height: currently_playing_item.height

                    Text
                    {
                        id : title_item
                        anchors
                        {
                            left : movie_pic.right
                            right : parent.right
                            verticalCenter : parent.verticalCenter
                        }
                        horizontalAlignment: Text.AlignHCenter
                        elide : Text.ElideRight
                        color : "white"
                        font.pixelSize: mainWindow.largeFontSize
                        text : model.title
                    }

                    Text
                    {
                        anchors
                        {
                            horizontalCenter : title_item.horizontalCenter
                            top : title_item.bottom
                            topMargin : 5
                        }
                        color : "white"
                        font.pixelSize: mainWindow.defaultFontSize
                        text : currently_playing_item.printDuration(model.runtime)
                    }

                    Image
                    {
                        id : movie_pic
                        height: parent.height - 40
                        anchors
                        {
                            left : parent.left
                            verticalCenter : parent.verticalCenter
                            leftMargin : 15
                        }
                        fillMode: Image.PreserveAspectFit
                        source : XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
                    }
                }
            }
        }

        ListView
        {
            id : playlist_listview
            property int maxHeight : 0
            onHeightChanged:
            {
                if (height > maxHeight)
                    maxHeight = height
            }
            clip : true
            anchors
            {
                left : parent.horizontalCenter
                right : parent.right
                top : parent.top
                bottom : parent.bottom
            }
            snapMode : ListView.SnapOneItem
            model : XBMCPlugin.getPlaylists();
            orientation : ListView.Horizontal
            delegate : PlaylistDelegate {
                width : playlist_listview.width
                height: playlist_listview.maxHeight
                idPlaylist: model.playlistId
                stringType : model.playlistTypeString
                itemModel : playlist_listview.model.subModelFromId(model.playlistId)
            }
        }
    }

    Rectangle
    {
        color : "black"
        opacity : 0.1
        radius : 5
        smooth : true
        border
        {
            width : 1
            color : "white"
        }
        anchors.fill: control_column
    }

    Column
    {
        id : control_column
        width : parent.width
        anchors
        {
            bottom : parent.bottom
            bottomMargin : 5
            horizontalCenter : parent.horizontalCenter
        }

        Item
        {
            id : time_slider
            focus : true
            height : 40
            property bool sliding : false
            property real tmp_advance : 0;
            property real advance : sliding ? tmp_advance : XBMCPlugin.playerAdvance
            enabled : isPlaying
            anchors
            {
                left : parent.left
                right : parent.right
                margins : 20
            }
            Rectangle
            {
                color : "grey"
                radius : 5
                width : parent.width
                height : 10
                opacity : 0.8
                border
                {
                    width : 1
                    color : "darkgrey"
                }

                anchors.centerIn: parent
            }
            Rectangle
            {
                id : advance_slide
                color : "#0099ff"
                border
                {
                    width : 1
                    color : "#6699ff"
                }

                radius : 5
                width : parent.width * time_slider.advance
                height : 12
                opacity : 0.8
                anchors.verticalCenter : parent.verticalCenter
                anchors.left: parent.left
            }
            MouseArea
            {
                anchors.fill: parent
                property bool lockedSlider : false
                onPressed:
                {
                    // IF PRESSED ON SLIDER
                    if (mouseX >= positioner.x && mouseX <= positioner.x + positioner.width)
                    {
                        lockedSlider = true;
                    }
                    mouse.accepted = true;
                    main_listview.interactive = !lockedSlider
                    console.log("Pressed ");
                }
                onPositionChanged:
                {
                    //                    if (lockedSlider)
                    //                    {
                    time_slider.tmp_advance = (mouseX / width < 0) ? 0 : (mouseX / width > 1) ? 1 : mouseX / width
                    mouse.accepted = true
                    //                    }
                }
                onReleased:
                {
                    lockedSlider = false;
                    main_listview.interactive = !lockedSlider
                    // ASK PLAYER TO CHANGE TO NEW VALUE OF time_slider.advance
                    //                    XBMCPlugin.seekAction(time_slider.tmp_advance * 100)
                    console.log("Released " + (time_slider.tmp_advance * 100));
                    time_slider.tmp_advance = 0
                }
            }
            Item
            {
                id : positioner
                width : 36
                height : width
                anchors
                {
                    verticalCenter : parent.verticalCenter
                    left : advance_slide.right
                    leftMargin : -18
                }

                Rectangle
                {
                    width : 36
                    height: width
                    opacity : 0.4
                    radius : width / 2
                    smooth : true
                    color : "#0099ff"
                    border
                    {
                        width : 1
                        color : "#006699"
                    }
                    anchors.centerIn: parent
                }
                Rectangle
                {
                    width : 16
                    height: width
                    opacity : 0.8
                    radius : width / 2
                    smooth : true
                    color : "#006699"
                    border
                    {
                        width : 1
                        color : "#0099ff"
                    }
                    anchors.centerIn: parent
                }
            }
            Text
            {
                id : currentPlayedTime
                color : "white"
                anchors
                {
                    horizontalCenter : parent.horizontalCenter
                    verticalCenter : advance_slide.verticalCenter
                }
                font.pixelSize: mainWindow.defaultFontSize
                text : currently_playing_item.printDuration(time_slider.advance * XBMCPlugin.getCurrentlyPlayedItemModel().get(currently_playing_item.currentIndex).runtime)
            }
        }

        Row
        {
            height : 128
            anchors.horizontalCenter: parent.horizontalCenter

            Image
            {
                id : backward_button
                height: parent.height
                source : "player_backward.png"
                fillMode: Image.PreserveAspectFit
                scale : backward_button_ma.pressed ? 0.9 : 1
                MouseArea
                {
                    id : backward_button_ma
                    anchors.fill: parent
                    onClicked: {XBMCPlugin.previousAction()}
                }
            }

            Image
            {
                id : fbackward_button
                height: parent.height
                source : "player_fbackward.png"
                fillMode: Image.PreserveAspectFit
                scale : fbackward_button_ma.pressed ? 0.9 : 1
                MouseArea
                {
                    id : fbackward_button_ma
                    anchors.fill: parent
                    onClicked: {XBMCPlugin.smallBackward()}
                    onPressAndHold: {XBMCPlugin.bigBackward()}
                }
            }

            Image
            {
                id : stop_button
                height: parent.height
                source : "player_stop.png"
                fillMode: Image.PreserveAspectFit
                scale : stop_button_ma.pressed ? 0.9 : 1
                MouseArea
                {
                    id : stop_button_ma
                    anchors.fill: parent
                    onClicked: {XBMCPlugin.stopAction()}
                }
            }

            Image
            {
                id : play_button
                height: parent.height
                source : isPlaying ? "player_pause.png" : "player_play.png"
                fillMode: Image.PreserveAspectFit
                scale : play_button_ma.pressed ? 0.9 : 1
                MouseArea
                {
                    id : play_button_ma
                    anchors.fill: parent
                    onClicked: {isPlaying ? XBMCPlugin.pauseAction() : XBMCPlugin.playAction(); isPlaying = !isPlaying}
                }
            }

            Image
            {
                id : fforward_button
                height: parent.height
                source : "player_fforward.png"
                fillMode: Image.PreserveAspectFit
                scale : fforward_button_ma.pressed ? 0.9 : 1
                MouseArea
                {
                    id : fforward_button_ma
                    anchors.fill: parent
                    onClicked: {XBMCPlugin.smallForward()}
                    onPressAndHold: {XBMCPlugin.bigForward()}
                }
            }

            Image
            {
                id : forward_button
                height: parent.height
                source : "player_forward.png"
                fillMode: Image.PreserveAspectFit
                scale : forward_button_ma.pressed ? 0.9 : 1
                MouseArea
                {
                    id : forward_button_ma
                    anchors.fill: parent
                    onClicked: {XBMCPlugin.nextAction()}
                }
            }
        }
    }
    ArrowButton
    {
        id : back_to_remote_view_button
        reversed: false
        anchors
        {
            bottom : parent.bottom
            right : parent.right
            rightMargin : 20
            bottomMargin : 20
        }
        onClicked: remote_item.playerControlsVisible = false;
    }
}
