import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : alarm_clock_container
    position : Qt.vector3d(0, 0, 0);
    property bool isFocused : false;

    function roomEntered()
    {
    }
    // HAS TO BE IMPLEMENTED
    function roomLeft()    {}
    // HAS TO BE IMPLEMENTED
    function switchToIdleFocusView()
    {
        plugin_base.moveCamera();
        isFocused= false;
    }
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()
    {
        isFocused = false;      
    }
    // HAS TO BE IMPLEMENTED
    function switchToFocusedView()
    {
        var eyePos = plugin_base.getRoomPosition();
        eyePos.z = (-10)

        var widgetPos = plugin_base.getRoomPosition();
        widgetPos.x += alarm_clock_container.x
        widgetPos.y += alarm_clock_container.y
        widgetPos.z += alarm_clock_container.z
        plugin_base.moveCamera(eyePos, widgetPos);    
        isFocused = false;
    }

    Item3D
    {
        id : modelAlarm
        mesh: Mesh { source: "./AlarmClock-2.dae" }
        scale : 5
        position : Qt.vector3d(-4, 2, 7)
        transform : [Rotation3D { angle : 180; axis : Qt.vector3d(1, 0, 0)}]
        onClicked :
        {
            console.log("plugin clicked");
            if (plugin_base.getFocusState() === 0)
                plugin_base.askForRoomSelectedFocusState();
            if (plugin_base.getFocusState() === 1)
                plugin_base.askForFocusedFocusState();
        }
    }
    FontLoader { id: ledFont; source: "./enhanced_led_board-7.ttf" }
  /*  Item
    {
        id : printclock
        enabled: isFocused
        x : ((mainWindow.width / 2) - (mainWindow.width / 3.4))
        y : ((mainWindow.height / 2)- (mainWindow.width / 30))
        Rectangle
        {
            visible: isFocused
            height : 125
            width: 285
            radius : 5
            color : "black"
            Text
            {
                anchors{
                    verticalCenter : parent.verticalCenter
                    horizontalCenter: parent.horizontalCenter
                }
                font.family: ledFont.name
                color : "red"
                text: time
                font.pixelSize: 34
            }
        }
    }
    Item
    {
        id : printclock_selected
        enabled: isNotFocused
        x : ((mainWindow.width / 2) - (mainWindow.width / 7.2))
        y : ((mainWindow.height / 2) - (mainWindow.width / 65))
        Rectangle
        {
            visible: isNotFocused
            height : 58
            width: 137
            radius : 4
            color : "black"
            Text
            {
                anchors{
                    verticalCenter : parent.verticalCenter
                    horizontalCenter: parent.horizontalCenter
                }
                font.family: ledFont.name
                color : "red"
                text: time
                font.pixelSize: 15
            }
        }
    }
*/
    Item {
        id : listview_container
        width: 360
        height: 360
        enabled :isFocused
        x : (mainWindow.width / 3)
        y : (mainWindow.height / 3)
        ListView {
            id: clockView
            anchors.fill: parent
            orientation: ListView.Horizontal
          // spacing: 10
            model: WatchPlugin.getClockModel();
            delegate: ClockDelegate
            {
             clockId : model.clockId
             clockCity : model.clockCity
             clockUtc : model.clockUtc
        }
    }
    }

}

