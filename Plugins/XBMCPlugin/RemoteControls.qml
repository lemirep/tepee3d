import QtQuick 2.0

Item
{
    id : remote_view

    Item
    {
        id : joystick_item
        width : 250
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
                        XBMCPlugin.pressNavigationKey((sin_a > 0) ? 0 : 1)
                    else
                        XBMCPlugin.pressNavigationKey((cos_a > 0) ? 3 : 2)
                }
            }
            onPressed:     {displaceCursor(mouseX - (width / 2), mouseY - (width / 2)); main_listview.interactive = false}
            onPositionChanged:    {displaceCursor(mouseX - (width / 2), mouseY - (width / 2))}
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
        onClicked : {XBMCPlugin.pressNavigationKey(4)}
    }

    OkButton
    {
        id : ok_button
        anchors
        {
            top : joystick_item.bottom
            left : joystick_item.right
        }
        onClicked : {XBMCPlugin.pressNavigationKey(5)}
    }

    ArrowButton
    {
        id : playlist_view
        reversed: true
        anchors
        {
            right : parent.right
            top : parent.top
            rightMargin : 20
            topMargin : 20
        }
        onClicked: remote_item.playerControlsVisible = true;
    }
}
