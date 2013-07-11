
import QtQuick 2.0

Item
{
    id : remote_item
    property bool isPlaying : XBMCPlugin.playing

    Item
    {
        width : parent.width
        anchors
        {
            top : parent.top
            bottom : joystick_item.top
            leftMargin : 30
            rightMargin : 30
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
                        text : " (" + Math.floor(model.runtime / 3600) + ":" + Math.floor((model.runtime % 3600) / 60)  + ":" + Math.floor((model.runtime % 3600) % 60) + ")";
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
                height: playlist_listview.height
                idPlaylist: model.playlistId
                stringType : model.playlistTypeString
                itemModel : playlist_listview.model.subModelFromId(model.playlistId)
            }
        }
    }

    Item
    {
        id : joystick_item
        width : 150
        height : width
        anchors.centerIn: parent

        Item
        {
            id : joystick_elem
            scale : joystick_ma.pressed ? 0.95 : 1
            property int x_angle : 0
            property int y_angle : 0

            x : 0 + y_angle
            y : 0 - x_angle
            width : joystick_item.width
            height : width

            //            border
            //            {
            //                width : 1
            //                color : "blue"
            //            }
            transform: [Rotation { origin.x: 0; origin.y: joystick_elem.width / 2; axis { x: 1; y: 0; z: 0 } angle:  joystick_elem.x_angle},
                Rotation { origin.x: joystick_elem.width / 2; origin.y:0; axis { x: 0; y: 1; z: 0 } angle:  joystick_elem.y_angle}]

            Behavior on x_angle {NumberAnimation {duration : 250}}
            Behavior on y_angle {NumberAnimation {duration : 250}}
            Image
            {
                anchors.fill: parent
                anchors.centerIn: parent
                fillMode: Image.PreserveAspectFit
                source : "JoystickControl.png"
            }
        }

        MouseArea
        {
            id : joystick_ma
            anchors.fill: parent
            function displaceCursor(x, y)
            {
                // COMPUTE VECTOR BETWEEN MOUSE POINT AND ORIGIN
                // COMPUTE COS AND SIN
                var ox = Qt.vector3d(1, 0, 0);
                var oa = Qt.vector3d(x, y, 0)
                // MAGNITUDES OF THE VECTORS
                var m_oa = Math.sqrt((oa.x * oa.x) + (oa.y * oa.y) + (oa.z * oa.z));
                var m_ox = 1
                // DOT PRODUCT (SCALAR) of m_oa and m_ox
                var oax = Qt.vector3d(oa.x * ox.x, oa.y * ox.y, oa.z * ox.z)
                var d_oax = oax.x + oax.y + oax.z;
                // COS
                var cos_a = d_oax / (m_oa * m_ox);
                // CROSS PRODUCT OF OA AND OX
                var c_oax = (oa.x * ox.y) - (oa.y * ox.x);
                // SIN
                var sin_a = c_oax / (m_oa * m_ox)
                var factor = 30;
                joystick_elem.y_angle = cos_a * factor
                joystick_elem.x_angle = sin_a * factor

                console.log("cos a " + cos_a + " sin a" + sin_a);

                if (Math.max(Math.abs(sin_a), Math.abs(cos_a)) >= 0.995)
                {
                    if (Math.abs(sin_a) > Math.abs(cos_a))
                        XBMCPlugin.pressNavigationKey((sin_a > 0) ? XBMCPlugin.Up : XBMCPlugin.Down)
                    else
                        XBMCPlugin.pressNavigationKey((cos_a > 0) ? XBMCPlugin.Right : XBMCPlugin.Left)
                }
            }
            onPressed:     {displaceCursor(mouseX - 75, mouseY - 75); main_listview.interactive = false}
            onPositionChanged:    {displaceCursor(mouseX - 75, mouseY - 75)}
            onReleased:    {displaceCursor(0, 0); main_listview.interactive = true}
        }
    }

    BackButton
    {
        id : back_button
        anchors
        {
            top : joystick_item.bottom
            right : joystick_item.left
        }
        onClicked : {XBMCPlugin.pressNavigationKey(XBMCPlugin.Back)}
    }

    OkButton
    {
        id : ok_button
        anchors
        {
            top : joystick_item.bottom
            left : joystick_item.right
        }
        onClicked : {XBMCPlugin.pressNavigationKey(XBMCPlugin.Select)}
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
                    onClicked: {XBMCPlugin.previousAction()}
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
                    onClicked: {XBMCPlugin.nextAction()}
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
}
