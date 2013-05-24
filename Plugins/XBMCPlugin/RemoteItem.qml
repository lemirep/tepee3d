import QtQuick 2.0

Item
{
    id : remote_item

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
            }
            onPressed:     {displaceCursor(mouseX - 75, mouseY - 75)}
            onPositionChanged:    {displaceCursor(mouseX - 75, mouseY - 75)}
            onReleased:    {displaceCursor(0, 0)}
        }
    }
}
