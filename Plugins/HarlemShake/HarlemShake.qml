import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Particles 2.0
import QtGraphicalEffects 1.0
import QtMultimedia 5.0


Item3D
{
    id : hs_container

    property real zRot : 1;
    property real yRot : 0;
    property color col : "red";
    property int savedX;
    property int savedY;
    property real savedXPos;
    property real savedYPos;
    property vector3d savedCameraOrientation;
    property bool isFocused : false;
    property bool delayAnimHarlem : false;

    Audio
    {
        id: playMusic
        source: "HS.mp3"
        autoPlay: false
        volume : 0.15
    }

    Timer {
        id : harlem_timer_intro
        interval: 18500
        repeat: false
        running: false
        onTriggered: {delayAnimHarlem = true;}
    }

    Timer {
        id : harlem_timer_total
        interval: playMusic.duration
        repeat: false
        running: false
        onTriggered: {delayAnimHarlem = false;playMusic.stop();}
    }

    position : Qt.vector3d(0, 0, 0)
    // HAS TO BE IMPLEMENTED
    function roomEntered()    {}
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}
    // HAS TO BE IMPLEMENTED
    function switchToIdleFocusView()    {plugin_base.moveCamera(); isFocused = false; playMusic.stop(); delayAnimHarlem = false;    harlem_timer_intro.stop() ;harlem_timer_total.stop()}
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()    {isFocused = false}
    // HAS TO BE IMPLEMENTED
    function switchToFocusedView()
    {
        var eyePos = plugin_base.getRoomPosition();
        eyePos.z += (-10)

        var widgetPos = plugin_base.getRoomPosition();
        widgetPos.x += hs_container.x
        widgetPos.y += hs_container.y
        widgetPos.z += hs_container.z
        plugin_base.moveCamera(eyePos, widgetPos);
        isFocused = true;
        playMusic.play();
        harlem_timer_intro.restart()
        harlem_timer_total.restart()
    }

    states : [
        State {
            name : "idle"
            PropertyChanges {target: hs_container;}
            when : plugin_base.getFocusState() === 0
        },
        State {
            name : "selected"
            PropertyChanges {target: hs_container;}
            when : plugin_base.getFocusState() === 1
        },
        State {
            name : "focused"
            PropertyChanges {target: hs_container;}
            when : plugin_base.getFocusState() === 2
        }
    ]

    Item3D
    {
        enabled : true
        CustomCube {
            //set main properties
            id : cube_orange; cubeColor : "orange"; position : Qt.vector3d(-1, 1, -2); scale : 1
            angleX : 45.0; angleY : 45.0; angleZ : 0;
            //set transform scale properties
            cubeScaleToStart : 0.50; cubeScaleToEnd : 1.5; cubeScaleDuration : 1500; cubeScalePauseDuration : 100;
            //set transform ColorAnimation properties
            cubeColorAnimationStart : "green"; cubeColorAnimationEnd : "red"; cubeColorAnimationDuration : 1000;
            //set transform RotationTarget properties
            cubeRotationTarget : cube_orange.axisZ; cubeRotationDuration : 3000;
            // transformation on/off
            globalrunning: delayAnimHarlem;
        }
        CustomCube {
            id : cube_red; cubeColor : "red"; position : Qt.vector3d(2, 1, 1); scale : 1
            angleX : 0; angleY : 45; angleZ : 45;
            cubeScaleToStart : 0.80; cubeScaleToEnd : 1.7; cubeScaleDuration : 1500; cubeScalePauseDuration : 100;
            cubeColorAnimationStart : "orange"; cubeColorAnimationEnd : "yellow"; cubeColorAnimationDuration : 1000;
            cubeRotationTarget : cube_red.axisX; cubeRotationDuration : 3000;
            globalrunning: delayAnimHarlem;
        }
        CustomCube {
            id : cube_blue; cubeColor : "blue"; position : Qt.vector3d(-2, 1, 0); scale : 1
            angleX : 45.0; angleY : 0; angleZ : 45.0;
            cubeScaleToStart : 0.50; cubeScaleToEnd : 1.5; cubeScaleDuration : 1500; cubeScalePauseDuration : 200;
            cubeColorAnimationStart : "yellow"; cubeColorAnimationEnd : "red"; cubeColorAnimationDuration : 1000;
            cubeRotationTarget : cube_blue.axisY; cubeRotationDuration : 3000;
            globalrunning: delayAnimHarlem;
        }
    }

    Item3D
    {
        enabled : delayAnimHarlem
        CustomCube {
            id : cube_yellow; cubeColor : "yellow"; position : Qt.vector3d(-3, 1, -2); scale : 1
            angleX : 0; angleY : 45.0; angleZ : 45.0;
            cubeScaleToStart : 0.30; cubeScaleToEnd : 0.80; cubeScaleDuration : 1500; cubeScalePauseDuration : 200;
            cubeColorAnimationStart : "blue"; cubeColorAnimationEnd : "orange"; cubeColorAnimationDuration : 1000;
            cubeRotationTarget : cube_yellow.axisX; cubeRotationDuration : 3000;
            globalrunning: delayAnimHarlem;
        }
        CustomCube {
            id : cube_green; cubeColor : "green"; position : Qt.vector3d(5, 1, -3); scale : 1
            angleX : 45.0; angleY : 45.0; angleZ : 0;
            cubeScaleToStart : 1; cubeScaleToEnd : 3.5; cubeScaleDuration : 1500; cubeScalePauseDuration : 800;
            cubeColorAnimationStart : "orange"; cubeColorAnimationEnd : "green"; cubeColorAnimationDuration : 1000;
            cubeRotationTarget : cube_green.axisZ; cubeRotationDuration : 3000;
            globalrunning: delayAnimHarlem;
        }
        CustomCube {
            id : cube_violet; cubeColor : "yellow"; position : Qt.vector3d(0, 1, 2); scale : 1
            angleX : 45.0; angleY : 0; angleZ : 45.0;
            cubeScaleToStart : 2.5; cubeScaleToEnd : 1.8; cubeScaleDuration : 1500; cubeScalePauseDuration : 200;
            cubeColorAnimationStart : "red"; cubeColorAnimationEnd : "green"; cubeColorAnimationDuration : 1000;
            cubeRotationTarget : cube_violet.axisY; cubeRotationDuration : 3000;
            globalrunning: delayAnimHarlem;
        }

    }

    Item3D
    {
        id : modelBatman
        mesh: Mesh { source: "./Batman.obj" }
        scale : 0.03
        position : Qt.vector3d(0, -5, 0)
        effect: Effect {color :"black"; useLighting : true}
        // APPLY TRANSFORMATIONS SO THAT PLUGIN MODEL FACES US
        transform : [Rotation3D {id : yBat; angle : 180; axis : Qt.vector3d(0, 1, 0)}]

        SequentialAnimation
        {
            id : scale_animation_bat
            running : delayAnimHarlem
            loops : Animation.Infinite
            NumberAnimation{ target: modelBatman;property: "scale"; to:0.04;duration : 1500;easing.type: Easing.InOutElastic}
            PauseAnimation { duration: 200 }
            NumberAnimation {target: modelBatman;property: "scale";to: 0.02;duration : 1500; easing.type: Easing.InOutElastic}
        }
        RotationAnimation {id :ra_bat; target: yBat; running: true; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }
        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }

        onPressed :
        {
            console.log("Plugin Pressed")
            savedX = -10000;
            savedY = -10000;
        }

        onHoverMove :
        {
        }

        SequentialAnimation {
            id : animation
            running : false
            loops : Animation.Infinite
            NumberAnimation{ target: modelBatman;
                property: "scale";
                to: 0.95;
                duration : 200;
                easing.type: Easing.InOutElastic
            }
            PauseAnimation { duration: 100 }
            NumberAnimation {
                target: modelBatman;
                property: "scale";
                to: 1;
                duration : 200;
                easing.type: Easing.InOutElastic
            }
        }
    }
}


