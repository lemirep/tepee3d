import QtQuick 2.1
import Tepee3D 1.0

Item
{
    property alias pluginMenuSource : bottomMenu.pluginMenuSource

    Rectangle
    {
        id : transparent_blur_rec
        anchors.fill: parent
        color : "black"
        opacity : (topMenu.isShown || bottomMenu.isShown || leftMenu.isShown || rightMenu.isShown) ? 0.2 : 0
        Behavior on opacity {NumberAnimation {duration: 500; easing.type: Easing.InOutQuad }}
    }

    // HANDLE TOUCH EVENTS EXCLUSIVELY
    Tepee3DTouchArea
    {
        id : multitoucharea
        anchors.fill: parent
        minimumTouchPoints: 2
        maximumTouchPoints: 15

        property var points : [];

        Repeater
        {
            model : multitoucharea.points
            delegate : Component {
                Rectangle
                {
                    z : 100
                    width : 25
                    height : 25
                    radius : 180
                    color : "lightsteelblue"
                    Behavior on scale {NumberAnimation {duration : 500;}}
                    x : modelData.x
                    y : modelData.y
                }
            }
        }

        onPressed:
        {
            // LIST OF NEW PRESSED POINTS
            multitoucharea.points = touchPoints;
        }

        onReleased:
        {
            // LIST OF RELEASE POINTS
            multitoucharea.points = touchPoints;
        }

        onUpdated:
        {
            // LIST OF UPDATED POINTS
            multitoucharea.points = touchPoints;
        }

        onTouchUpdated:
        {
            // LIST OF CURRENT TOUCH POINT UPDATED
            multitoucharea.points = touchPoints;
        }

        // HANDLE ZOOM AND ROTATION WITH MULTITOUCH IN A ROOM
        PinchArea
        {
            id : pincharea
            anchors.fill: parent
            property real oldZoom;
            enabled: multitoucharea.points.length === 2

            function zoomDelta(zoom, scale)    {return zoom - (Math.log(scale) / Math.log(4))}

            onPinchStarted:    {oldZoom = mainWindow.cameraZoom}

            onPinchUpdated:
            {
                var newZoom = zoomDelta(oldZoom, pinch.scale);
                mainWindow.cameraZoom = (newZoom > 1) ? 1 : (newZoom < 0.2) ? 0.2 : newZoom
            }
            onPinchFinished : {}
        }

    }

    // LEAP GESTURE AREA
    LeapGestureArea
    {
        id : leap_gesture_area
        anchors.fill: parent

        onSwipeGesture :
        {
            console.log("Swipe Gesture Detected;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        }

        onCircleGesture:
        {
            if (gesture.state === LeapCircleGesture.CircleGestureDone && gesture.turns >= 2 && mainWindow.inRoom())
            {
                var nextWallIdx = mainWindow.currentRoomFaceId;
                nextWallIdx += (gesture.clockwise) ? 1 : -1
                if (nextWallIdx < 0)
                    nextWallIdx = 3
                else if (nextWallIdx > 3)
                    nextWallIdx = 0;
                mainWindow.currentRoomFaceId = nextWallIdx;
            }
//            console.log("Circle Gesture Detected;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;; " + gesture.turns);
        }

        onScreenTapGesture:
        {
//            console.log("ScreenTap Gesture Detected;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        }

        onKeyTapGesture:
        {
//            console.log("KeyTap Gesture Detected;;;;;;;;;;;;;;;;;;;;;;;;;;;");
        }
    }

    // HANDLE MOUSE AND SINGLE TOUCH EVENTS
    MouseArea
    {
        Rectangle
        {
            property bool isPressing : false;
            id : pointer
            width : 50
            height : width
            color : isPressing ? "red" : "orange"
            scale : isPressing ? 1.5 : 1
            radius : 180
            Behavior on scale {NumberAnimation {duration : 250}}
        }


        id : main_mouse_area
        property int savedX;
        property int savedY;
        property variant obj;
        anchors.fill: parent
        propagateComposedEvents: (obj !== null) // PROPAGATE COMPOSE EVENTS (CLICK, DBCLICK ...)
        hoverEnabled: true

        onPressed:
        {
            savedX = mouseX;
            savedY = mouseY;
            obj = null;
            pointer.isPressing = true;
            console.log("Mouse Area Pressed")

            // CHECK ON WHICH MENU WE CLICKED
            if (savedX >= topMenu.x && savedX <= (topMenu.x + topMenu.width) &&
                    savedY >= topMenu.y && savedY <= (topMenu.y + topMenu.height))
                obj = topMenu;
            else if (savedX >= leftMenu.x && savedX <= (leftMenu.x + leftMenu.width) &&
                     savedY >= leftMenu.y && savedY <= (leftMenu.y + leftMenu.height))
                obj = leftMenu;
            else if (savedX >= rightMenu.x && savedX <= (rightMenu.x + rightMenu.width) &&
                     savedY >= rightMenu.y && savedY <= (rightMenu.y + rightMenu.height))
                obj = rightMenu;
            else if (savedX >= bottomMenu.x && savedX <= (bottomMenu.x + bottomMenu.width) &&
                     savedY >= bottomMenu.y && savedY <= (bottomMenu.y + bottomMenu.height))
                obj = bottomMenu;
            // ONE MENU CAN BE OPENED AT THE TIME
            topMenu.isShown = (obj === topMenu) ? topMenu.isShown : false;
            rightMenu.isShown = (obj === rightMenu) ? rightMenu.isShown : false;
            leftMenu.isShown = (obj === leftMenu) ? leftMenu.isShown : false
            bottomMenu.isShown = (obj === bottomMenu) ? bottomMenu.isShown : false;
            if (obj)
            {
                mouse.accepted = true; // DO NOT PROPAGATE PRESSED EVENT TO UNDERLYING MOUSEAREA SO SETTING THE ACCEPTED VALUE
                obj.startDrag(savedX, savedY)
                obj.isPressed = true
            }
            else
            {
                mouse.accepted = false
            }
        }
        onPositionChanged:
        {
            pointer.x = mouseX
            pointer.y = mouseY
            if (obj)
            {
                var offsetY = mouseY - savedY;
                var offsetX = mouseX - savedX;
                obj.dragMoved(offsetX, offsetY);
                mouse.accepted = true;
            }
            else if (mainWindow.mouseObjectGrabber)
            {
                // IF AN OBJECT IS REGISTERED IN mainWindow
                // WE CALL THAT OBJECT onMouseMove Method
                mainWindow.mouseObjectGrabber.onMouseMove(mouse);
            }
        }
        onReleased :
        {
            pointer.isPressing = false;
            console.log("Mouse Area released")
            if (obj)
            {
                if (mouse)
                    mouse.accepted = true
                obj.dragEnd();
                obj.isPressed = false;
                console.log("drag end")
                obj = null;
            }
        }
        onCanceled:
        {
            pointer.isPressing = false;
        }
    }


    //    MouseArea
    //    {
    //        anchors.fill: parent
    //        propagateComposedEvents: true
    //        onPressed:
    //        {
    //            console.log("Mouse 1 Pressed")
    //        }
    //        onClicked:
    //        {
    //            console.log("Mouse 1 Clicked")
    //        }
    //        onReleased:
    //        {
    //            console.log("Mouse 1 Released")
    //        }
    //    }

    //    MouseArea
    //    {
    //        anchors.fill: parent
    //        propagateComposedEvents: true
    //        onPressed:
    //        {
    //            console.log("Mouse 2 Pressed")
    //        }
    //        onClicked:
    //        {
    //            console.log("Mouse 2 Clicked")
    //        }
    //        onReleased:
    //        {
    //            console.log("Mouse 2 Released")
    //        }
    //    }

    MenuTop // TOP MENU
    {
        id : topMenu
        anchors.top: parent.top
        anchors.horizontalCenter : parent.horizontalCenter
    }

    MenuBottom // BOTTOM MENU
    {
        id : bottomMenu
        anchors.horizontalCenter : parent.horizontalCenter
    }

    MenuLeft // LEFTMENU
    {
        id : leftMenu
        anchors.verticalCenter : parent.verticalCenter
        anchors.left: parent.left
    }

    MenuRight // RIGHT MENU
    {
        id : rightMenu
        anchors.verticalCenter : parent.verticalCenter
    }
}
