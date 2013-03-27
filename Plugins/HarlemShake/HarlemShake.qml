import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0
import QtQuick.Particles 2.0
import QtGraphicalEffects 1.0


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


    position : Qt.vector3d(0, 0, 0)
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
        widgetPos.x += hs_container.x
        widgetPos.y += hs_container.y
        widgetPos.z += hs_container.z
        plugin_base.moveCamera(eyePos, widgetPos);
        isFocused = true;
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
    Timer {

        interval: 5000
        repeat: false
        running: true
        onTriggered: {buttonsHS.enabled = true;ra_orange.running = true;ra_blue.running = true;ra_red.running = true}

    }
    Item3D
    {
        id : buttons
        enabled : true
        Cube
        {
            id : cube_orange
            effect: Effect {color: "orange"}
            scale : 1
            position : Qt.vector3d(-1, 1, -2)
            onClicked:{cube_plugin.effect.color = "orange";}
            transform: [
                Rotation3D {
                    id : xRT
                    angle: 0
                    axis: Qt.vector3d(1, 0, 0)
                },
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(0, 0, 1)
                },
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(0, -1, 0)
                }
            ]
            RotationAnimation {id :ra_orange; target: xRT; running: false; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }
        }

        Cube
        {
            id : cube_red
            effect: Effect {color: "red"}
            scale : 1
            position : Qt.vector3d(2, 1, 1)
            onClicked:{cube_plugin.effect.color = "red";}
            transform: [
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(1, 0, 0)
                },
                Rotation3D {
                    id : zRT
                    angle: 0.0
                    axis: Qt.vector3d(0, 0, 1)
                },
                Rotation3D {

                    angle: 45.0
                    axis: Qt.vector3d(0, -1, 0)
                }
            ]
            RotationAnimation {id :ra_red; target: zRT; running: false; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }

        }

        Cube
        {
            id : cube_blue
            effect: Effect {color: "blue"}
            scale : 1
            position : Qt.vector3d(-2, 1, 0)
            transform: [
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(1, 0, 0)
                },
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(0, 0, 1)
                },
                Rotation3D {
                    id: yRT
                    angle: 0
                    axis: Qt.vector3d(0, -1, 0)
                }
            ]
            onClicked:{cube_plugin.effect.color = "blue";}
            RotationAnimation {id :ra_blue; target: yRT; running: false; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }


        }

    }


    Item3D
    {
        id : buttonsHS
        enabled : false
        Cube
        {
            id : cube_yellow
            effect: Effect {color: "yellow"}
            scale : 1
            position : Qt.vector3d(-3, 1, -2)
            onClicked:{cube_plugin.effect.color = "yellow";}
            transform: [
                Rotation3D {
                    id : xRTyellow
                    angle: 0
                    axis: Qt.vector3d(1, 0, 0)
                },
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(0, 0, 1)
                },
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(0, -1, 0)
                }
            ]
            RotationAnimation {id :ra_yellow; target: xRTyellow; running: true; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }
        }

        Cube
        {
            id : cube_green
            effect: Effect {color: "green"}
            scale : 1
            position : Qt.vector3d(3, 1, 2)
            onClicked:{cube_plugin.effect.color = "green";}
            transform: [
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(1, 0, 0)
                },
                Rotation3D {
                    id : zRTgreen
                    angle: 0.0
                    axis: Qt.vector3d(0, 0, 1)
                },
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(0, -1, 0)
                }
            ]
            RotationAnimation {id :ra_green; target: zRTgreen; running: true; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }
        }
        Cube
        {
            id : cube_violet
            effect: Effect {color: "violet"}
            scale : 1
            position : Qt.vector3d(0, 1, 2)
            transform: [
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(1, 0, 0)
                },
                Rotation3D {
                    angle: 45.0
                    axis: Qt.vector3d(0, 0, 1)
                },
                Rotation3D {
                    id: yRTviolet
                    angle: 0
                    axis: Qt.vector3d(-2, -1, 0)
                }
            ]
            onClicked:{cube_plugin.effect.color = "violet";}
            RotationAnimation {id :ra_violet; target: yRTviolet; running: true; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }
        }
    }

    Rectangle
    {
        id : focusRec
        enabled : isFocused
        opacity : enabled ? 0.3 : 0
        Behavior on opacity {SmoothedAnimation {velocity : 1; duration : -1}}
        color : "grey"
        x : mainWindow.width / 4
        y : mainWindow.height / 4
        width : mainWindow.width / 2
        height : mainWindow.height / 2
    }


    Item3D
    {
        id : cube_plugin
        mesh: Mesh { source: "./Batman.obj" }
        scale : 0.03
        position : Qt.vector3d(0, -5, 0)
        effect: Effect {color :"black"; useLighting : true}
        // APPLY TRANSFORMATIONS SO THAT PLUGIN MODEL FACES US
        transform : [Rotation3D {id : yBat; angle : 180; axis : Qt.vector3d(0, 1, 0)}]


        RotationAnimation {id :ra_bat; target: yBat; running: true; loops: Animation.Infinite; property: "angle"; from: 0; to : 360.0; duration: 3000; }

/*        SequentialAnimation {
            id : animation_bat
            running : true
            loops : Animation.Infinite
            NumberAnimation{ target: yBat;
                property: "angle";
                from : 0;
                to: 360;
                duration : 1000;
                easing.type: Easing.InOutElastic
            }
        }*/
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
            // SHOW 3 ARROWS ONE FOR EACH AXIS
            // THE USER PRESSES THE ARROW HE WISHES
            // THE THE OBJECT CAN MOVE WITH THE MOUSE ACCORDING TO THE SELECTED AXIS

            console.log("Hover Moved Signal has been triggered " + x + " " + y);
            console.log("Item Pos " + cube_plugin.position)
            if (savedX === -10000 && savedY === -10000)
            {
                console.log("-------------")
                savedX = x;
                savedY = y;
                savedXPos = cube_plugin.x
                savedYPos = cube_plugin.y


                savedCameraOrientation = plugin_base.getCameraOrientation();
                console.log("><><><><> " + savedCameraOrientation + " " + savedXPos + " " + savedYPos)
            }
            else
            {
                var xDiff = ((x  * savedXPos) / savedX);
                var yDiff = ((y  * savedYPos) / savedY);
                cube_plugin.x = xDiff;
                cube_plugin.y = yDiff;
                console.log("Item Pos After" + cube_plugin.position)

            }

            // GET ITEM AXIS ON WHICH IT CAN MOVE
            // ITEM POS VALUE ON AXIS / WINDOW WIDTH IF X
            // ITEM POS VALUE ON AXIS / WINDOW WIDTH IF Y
        }

        SequentialAnimation {
            id : animation
            running : false
            loops : Animation.Infinite
            NumberAnimation{ target: cube_plugin;
                property: "scale";
                to: 0.95;
                duration : 200;
                easing.type: Easing.InOutElastic
            }
            PauseAnimation { duration: 100 }
            NumberAnimation {
                target: cube_plugin;
                property: "scale";
                to: 1;
                duration : 200;
                easing.type: Easing.InOutElastic
            }
        }
    }
}


