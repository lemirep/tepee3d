// import QtQuick 1.0 // to target S60 5th Edition or Maemo 5
import QtQuick 2.0

Item
{

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
            if (obj)
            {
                mouse.accepted = true; // DO NOT PROPAGATE PRESSED EVENT TO UNDERLYING MOUSEAREA SO SETTING THE ACCEPTED VALUE
                obj.startDrag(savedX, savedY)
            }
            else
                mouse.accepted = false;
        }
        onPositionChanged:
        {
            if (obj)
            {
                var offsetY = mouseY - savedY;
                var offsetX = mouseX - savedX;
                obj.dragMoved(offsetX, offsetY);
                obj.dragEnd();
            }
        }
        onReleased :
        {
            if (obj)
                obj.dragEnd();
        }
    }


    MenuTop // TOP MENU
    {
        id : topMenu
        anchors.top: parent.top
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
