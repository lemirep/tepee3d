import QtQuick 2.1

Item
{
    id : carousel
    property alias model : carousel_path_view.model
    property alias delegate : carousel_path_view.delegate
    property alias pathItemCount : carousel_path_view.pathItemCount
    property int depth : 550

    Path
    {
        id : carousel_path
        startX : 0
        startY : carousel_path_view.height / 2

        Component.onCompleted: console.log("--------------->>> " + 180 * Math.atan(depth / (carousel_path_view.width / 2)) / Math.PI)

        PathPercent   {value : 0}
        PathAttribute {name : "rotAngle"; value : 180 * Math.atan(depth / (carousel_path_view.width / 2)) / Math.PI}
        PathAttribute {name : "opacity"; value : 1}
        PathAttribute {name : "delZ"; value : 1}
        PathAttribute {name : "delScale"; value : 1}

        // CENTER
        PathLine {x : carousel_path_view.width / 2; y : carousel_path.startY}
        PathPercent   {value : 0.5}
        PathAttribute {name : "rotAngle"; value : 0}
        PathAttribute {name : "opacity"; value : 1}
        PathAttribute {name : "delZ"; value : 0.5}
        PathAttribute {name : "delScale"; value : 0.85}

        // RIGHT
        PathLine {x : carousel_path_view.width; y : carousel_path.startY}
        PathPercent   {value : 1}
        PathAttribute {name : "rotAngle"; value : -180 * Math.atan(depth / (carousel_path_view.width / 2)) / Math.PI}
        PathAttribute {name : "opacity"; value : 1}
        PathAttribute {name : "delZ"; value : 1}
        PathAttribute {name : "delScale"; value : 1}

    }

    PathView
    {
        id : carousel_path_view
        anchors.fill: parent
        path : carousel_path
        pathItemCount: 7
        smooth : true
        focus : true
        preferredHighlightBegin: 0.50
        preferredHighlightEnd : 0.55
    }
}

