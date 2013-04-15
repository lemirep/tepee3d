import QtQuick 2.0

Item {
    id: delegate

    property int clockId;
    property double clockUtc;
    property string clockCity;
    property int widthClock : cl.width
    height: 30
    width: delegate.ListView.view.width
   Clock { id : cl;city: clockCity; shift: clockUtc }

    Text {
        anchors.fill: parent;
        text: clockId +" ("+clockCity+")"
        color : "black"
    }
}
