import QtQuick 2.0

Item {
    id: delegate

    property int clockId;
    property double clockUtc;
    property string clockCity;
    property int widthClock : cl.width
    height: cl.height
    width: cl.width
    Clock { id : cl;city: clockCity; shift: clockUtc }
}
