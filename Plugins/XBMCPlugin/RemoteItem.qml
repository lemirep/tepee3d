
import QtQuick 2.0

Item
{
    id : remote_item
    property bool isPlaying : false

    Item
    {
        id : joystick_item
        width : 150
        height : width
        anchors.centerIn: parent

        Rectangle
        {
            id : joystick_elem
            scale : joystick_ma.pressed ? 0.9 : 1
            property int x_angle : 0
            property int y_angle : 0

            x : 0 + y_angle
            y : 0 - x_angle
            color : "black"
            width : joystick_item.width
            height : width
            radius : width / 2
            border
            {
                width : 1
                color : "blue"
            }
            smooth : true
            transform: [Rotation { origin.x: 0; origin.y: joystick_elem.width / 2; axis { x: 1; y: 0; z: 0 } angle:  joystick_elem.x_angle},
                Rotation { origin.x: joystick_elem.width / 2; origin.y:0; axis { x: 0; y: 1; z: 0 } angle:  joystick_elem.y_angle}]
            Image
            {
                anchors.fill: parent
                anchors.centerIn: parent
                source : "red_cross.png"
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


    //    Item
    //    {
    Rectangle
    {
        color : "black"
        opacity : 0.3
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
            property real advance : 0.6
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
                height : 2
                opacity : 0.8
                anchors.centerIn: parent
            }
            Rectangle
            {
                id : advance_slide
                color : "#0099ff"
                radius : 5
                width : parent.width * time_slider.advance
                height : 3
                opacity : 0.8
                anchors.verticalCenter : parent.verticalCenter
                anchors.left: parent.left
            }
            MouseArea
            {
                anchors.fill: parent
                property bool lockedSlider : false
                onClicked:
                {
                    time_slider.advance = mouseX / width
                }
                onPressed:
                {
                    // IF PRESSED ON SLIDER
                    if (mouseX >= positioner.x && mouseX <= positioner.x + positioner.width)
                    {
                        mouse.accepted = true;
                        lockedSlider = true;
                    }
                    main_listview.interactive = !lockedSlider
                }
                onPositionChanged:
                {
                    if (lockedSlider)
                    {
                        time_slider.advance = (mouseX / width < 0) ? 0 : (mouseX / width > 1) ? 1 : mouseX / width
                        mouse.accepted = true
                    }
                }
                onReleased:
                {
                    lockedSlider = false;
                    main_listview.interactive = !lockedSlider
                    // ASK PLAYER TO CHANGE TO NEW VALUE OF time_slider.advance
                    XBMCPlugin.seekAction(time_slider.advance * 100)
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
                    onClicked: {isPlaying ? XBMCPlugin.pauseAction() : XBMCPlugin.playAction()}
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
    //    }
}
