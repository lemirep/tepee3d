import QtQuick 2.1
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : agendaplugin_item

    position : Qt.vector3d(0, 0, 0)

    property bool isFocused : false;
    property bool consultingEpisode : false
    property bool synchingWeb : agenda_plugin.synchingWebServices

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
        widgetPos.x += plugin_base.pluginPosition.x
        widgetPos.y += plugin_base.pluginPosition.y
        widgetPos.z += plugin_base.pluginPosition.z
        var up = Qt.vector3d(0, 1, 0)
        console.log("POSITION ------> P" + plugin_base.pluginPosition + " R " + plugin_base.getRoomPosition() + " W " + widgetPos)
        plugin_base.moveCamera(eyePos, widgetPos, up);
        isFocused = true;
    }

    Cube
    {
        id : cube_picture

        enabled : (isFocused == false)
        scale : 3
        effect : cube_effect
        transform : [Rotation3D {id : cube_x_rotate; axis : Qt.vector3d(0, 0, 1); angle : -90},
            Rotation3D {id : cube_y_rotate;axis : Qt.vector3d(0, 1, 0); angle : 45}]
        onClicked : {plugin_base.askForFocusedFocusState()}
    }

    ParallelAnimation
    {
        id : cube_anim_article
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 1000
            to : 0
            velocity : 1
        }
        SmoothedAnimation
        {
            target : cube_y_rotate
            duration : 750
            property : "angle"
            to : cube_y_rotate.angle >= 360 ? 0 : 360
        }
    }

    ParallelAnimation
    {
        id : cube_anim_article_close
        loops: 1
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 1000
            to : 5
            velocity : 1
        }
        SmoothedAnimation
        {
            target : cube_y_rotate
            duration : 750
            property : "angle"
            to : cube_y_rotate.angle >= 360 ? 0 : 360
        }
    }

    SequentialAnimation
    {
        id : loading_animation
        running: synchingWeb
        loops : Animation.Infinite
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 750
            to : 1
            velocity : 1
        }
        SmoothedAnimation
        {
            target : cube_picture
            property : "scale"
            duration : 750
            to : 3
            velocity : 1
        }
    }
    ParallelAnimation
    {
        id : rotate_cube
        SmoothedAnimation
        {
            target : cube_x_rotate
            duration : 750
            property : "angle"
            to : cube_x_rotate.angle >= 270 ? -90 : 270
        }
        SequentialAnimation
        {
            SmoothedAnimation
            {
                target : cube_picture
                property : "scale"
                duration : 375
                to : 1
                velocity : 1
            }
            SmoothedAnimation
            {
                target : cube_picture
                property : "scale"
                duration : 375
                to : 3
                velocity : 1
            }
        }
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
        useLighting : false
        blending : true
    }

    Item {
        id : agenda_plugin_content

        x : 0;
        y : 0;
        width : width
        height : height
        enabled : isFocused
        opacity : isFocused ? 1 : 0

        Rectangle
        {
            id : background

            x : (mainWindow.width * 0.1) - 10
            y : (mainWindow.height * 0.05) - 10
            width : (mainWindow.width * 0.8) + 20
            height : (mainWindow.height * 0.9) + 20
            opacity : 0.5
            gradient: Gradient {
                GradientStop { position : 0.0; color : "steelblue"}
                GradientStop { position : 1.0; color : "lightsteelblue"}
            }
            border
            {
                color: "white"
                width: 10
            }


        }

        AgendaCalendar
        {
            id :calendar_view

            anchors.fill: parent
        }

    }

}
