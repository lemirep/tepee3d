// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0
import QtGraphicalEffects 1.0

Item
{
    property alias pluginMenuSource : bottomMenu.pluginMenuSource

    Rectangle
    {
        id : transparent_blur_rec
        anchors.fill: parent
        color : "black"
        opacity : (topMenu.isShown || bottomMenu.isShown || leftMenu.isShown || rightMenu.isShown) ? 0.2 : 0
    }

    MouseArea
    {
        property int savedX;
        property int savedY;
        property variant obj;
        anchors.fill: parent
        propagateComposedEvents: true // PROPAGATE COMPOSE EVENTS (CLICK, DBCLICK ...)
        onPressed:
        {
            savedX = mouseX;
            savedY = mouseY;
            obj = null;

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
            topMenu.isShown = false;
            rightMenu.isShown = false;
            leftMenu.isShown = false;
            bottomMenu.isShown = false;
            if (obj)
            {
                mouse.accepted = true; // DO NOT PROPAGATE PRESSED EVENT TO UNDERLYING MOUSEAREA SO SETTING THE ACCEPTED VALUE
                obj.startDrag(savedX, savedY)
                obj.isPressed = true
            }
        }
        onPositionChanged:
        {
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
            if (obj)
            {
                mouse.accepted = true
                obj.dragEnd();
                obj.isPressed = false;
            }
        }
    }

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
