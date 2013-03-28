import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : seriesplugin_item

    position : Qt.vector3d(0, 0, 0)

    property bool isFocused : false;
    property bool spinCube : false;

    // HAS TO BE IMPLEMENTED
    function roomEntered()    {}
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}
    // HAS TO BE IMPLEMENTED
    function switchToIdleFocusView()    {plugin_base.moveCamera(); isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()    {isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToFocusedView()
    {
        var eyePos = plugin_base.getRoomPosition();
        eyePos.z += (-10)

        var widgetPos = plugin_base.getRoomPosition();
        widgetPos.x += cube.x
        widgetPos.y += cube.y
        widgetPos.z += cube.z
        plugin_base.moveCamera(eyePos, widgetPos);
        isFocused = true;
    }

    Cube
    {
        property int rotAngle : 45;
        id : cube
        scale : 5
        effect : cube_effect
        Behavior on rotAngle {NumberAnimation {duration : 500}}

        transform : [Rotation3D {axis : Qt.vector3d(0, 0, 1); angle : 180},
            Rotation3D {id : cube_y_rotate;axis : Qt.vector3d(0, 1, 0); angle : 45}]

        onClicked :
        {
            console.log("------------------")
            switchToFocusedView();
        }
    }


    SequentialAnimation
    {
        id : rotate_cube
        SmoothedAnimation
        {
            target : cube_y_rotate
            duration : 750
            property : "angle"
            to : cube_y_rotate.angle >= 360 ? 0 : 360
        }
    }

    Effect
    {
        id : cube_effect
        color : "white"
        useLighting : true
        blending : true
    }

    Item
    {
        id : followed_series_item
        enabled : isFocused
        opacity : isFocused ? 1 : 0
        width : mainWindow.width / 4
        height : mainWindow.height / 2
        x : 80
        y : (mainWindow.height - height) / 2
        transform : Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: 25}

        Rectangle
        {
            color : "grey"
            opacity : 0.2
            anchors.fill: parent
        }

        ListView
        {
            smooth : true
            id : followed_series_listview
            clip : true
            anchors.fill : parent
            model : SeriesPlugin.getFollowedSeriesModel();
            delegate : SeriesListViewDelegate {
                img_src : model.imageUrl
                series_name: model.serieName
                width : parent.width
                height : 60
            }
            spacing : 10
        }
    }

    Item
    {
        id : episodes_series_item
        enabled : isFocused
        opacity : isFocused ? 1 : 0
        width : mainWindow.width / 4
        height : mainWindow.height / 2
        x : mainWindow.width - (width + 80)
        y : (mainWindow.height - height) / 2
        transform : Rotation { origin.x: mainWindow.width / 4; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: -25}

        Rectangle
        {
            color : "grey"
            opacity : 0.2
            anchors.fill: parent
        }
    }

    Item
    {
        id : search_bar_series_item
        enabled : isFocused
        opacity : isFocused ? 1 : 0
        width : mainWindow.width / 4
        height : 40
        x : (mainWindow.width / 2) - (width / 2)
        y : 70

        Rectangle
        {
            color : "black"
            opacity : 0.4
            smooth : true
            anchors.fill: parent
            radius : 15
        }

        TextInput
        {
            width : parent.width - 20
            wrapMode: TextInput.Wrap
            anchors
            {
                top : parent.top
                left : parent.left
//                verticalCenter : parent.verticalCenter
                leftMargin : 10
                bottom : parent.bottom
            }
            color : "white"
            font.pointSize: 12
        }

    }

}
