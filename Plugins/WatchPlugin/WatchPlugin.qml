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
        modelAlarm.scale = 5;
    }
    // HAS TO BE IMPLEMENTED
    function switchToSelectedFocusView()
    {
        isFocused = false;
        modelAlarm.scale = 5;
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
        isFocused = true;
        modelAlarm.scale = 0;
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

    Item {
        id : listview_container
        visible  : isFocused
        width: mainWindow.width / 1.4
        height: 250
        x : (mainWindow.width / 8)
        y : (mainWindow.height / 4)
        PathView {
            id: view
            smooth : true
            anchors.fill : parent
            focus : true
            flickDeceleration : 200
            pathItemCount : 4
            cacheItemCount : 8
            model:  WatchPlugin.getClockModel();
            delegate: ClockDelegate
            {
            clockId : model.clockId
            clockCity : model.clockCity
            clockUtc : model.clockUtc
        }
        path: Path {
            startX: 0; startY: 0
            PathQuad { x:listview_container.width ; y: 0; controlX: (listview_container.width / 2); controlY: (listview_container.height /2) }
        }
    }
    AddBox
    {
        id : addbox
        visible: false
    }
}
Image
{
    id : add_clock_button
    width : 50
    height : 50
    visible  : isFocused
    smooth : true
    scale : add_clock_button_ma.pressed ? 0.9 : 1.0
    anchors    {bottom : listview_container.bottom; horizontalCenter : listview_container.horizontalCenter}
    MouseArea
    {
        id : add_clock_button_ma
        anchors.fill : parent
        onClicked :
        {
            view.visible = false;
            addbox.visible = true;
            add_clock_button.visible = false;
        }
    }
    source : "./plus.png"
}

}

