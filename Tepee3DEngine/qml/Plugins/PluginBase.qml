import QtQuick 2.1
import Qt3D 2.0
import Plugins 1.0
import "../js/CameraManagement.js" as CameraManagement
import "../js/Walls.js" as Walls

/*
\qmlType PluginBase
\inherits Item3D
\brief Provides a container that holds a visual widget.

When loaded, a widget is contained in a PluginBase component. This container provides various helper methods
that can be calls from the widget's own qml files using plugin_base.method. The provides methods allow the widget to :
\list
\li Request a new focus state
\li Get room dimensions and positions
\li Move the camera
\li Compute rotations and distance betwneen two points
\li Post notifications
\endlist

*/

Item3D
{
    id : plugin_base

    /*!
    \qmlproperty int PluginBase::pluginId
    Holds the identifier of the plugin in the room in which it is loaded.
    */
    property int pluginId : -1
    /*!
    \qmlproperty int PluginBase::pluginRoomId
    Holds the identifier of the room in which the plugin is loaded.
    */
    property int pluginRoomId :-1
    /*!
    \qmlproperty string PluginBase::roomQmlFile
    Contains the name of the qml file that is the entry point of the widget.
    */
    property string roomQmlFile : ""
    /*!
    \qmlproperty string PluginBase::menuQmlFile
    Contains the name of the qml file that contains the widget's menu.
    */
    property string menuQmlFile : ""
    /*!
    \qmlproperty string PluginBase::pluginName
    Contains the name of the plugin.
    */
    property string pluginName : ""
    /*!
    \qmlproperty string PluginBase::pluginRepoName
    Contains the repo_name of the plugin. It matches the one in the C++ plugin file.
    */
    property string pluginRepoName : ""
    /*!
    \qmlproperty vector3d PluginBase::pluginPosition
    Holds a vector containing the 3D position of the widget relative to the room's position.
    */
    property vector3d pluginPosition : Qt.vector3d(0, 0, 0)

    // TO ASK FOR A GIVEN FOCUS STATE CALL
    // plugin_base.askForFocusState(State)
    // IF CHANGE ACCEPTED, corresponding handler will be called

    /*
      \qmlmethod PluginBase::askForRoomFocusState()
      Requests the engine to switch the plugin to the "idle" state. If the plugin is already in that state, it has no effect.
      */
    function askForRoomFocusState()            {plugin_properties.askForFocusState(0)}
    /*
      \qmlmethod PluginBase::askForRoomSelectedFocusState()
      Requests the engine to switch the plugin to the "selected" state. If the plugin is already in that state, it has no effect.
      */
    function askForRoomSelectedFocusState()    {plugin_properties.askForFocusState(1)}
    /*
      \qmlmethod PluginBase::askForRoomFocusedFocusState()
      Requests the engine to switch the plugin to the "focused" state. If the plugin is already in that state, it has no effect.
      */
    function askForFocusedFocusState()         {plugin_properties.askForFocusState(2)}
    /*
      \qmlmethod PluginBase::getFocusState()
      Returns the current focus state of the widget.
      */
    function getFocusState()                   {return plugin_properties.focusState}
    /*
      \qmlmethod PluginBase::moveCamera(vector3d eye, vector3d center, vector3d up = Qt.vector3d(0,1,0))
      Provides with at least a vector3d for the eye and a vector3d for the center, moves the camera's eye to eye and the camera's center to center.
      */
    function moveCamera(eye, center, up)       {CameraManagement.moveCamera(camera, eye, center, up)}
    /*
      \qmlmethod PluginBase::getCameraOrientation()
      Returns a vector3d that holds a unit vector of the camera orientation,
      */
    function getCameraOrientation()            {return camera.getCameraOrientation()}
    // RETURN DEEP COPY OF ROOM VARIABLES SO THEY CANNOT MODIFY THE ROOM DIRECTLY
    /*
      \qmlmethod PluginBase::getRoomPosition()
      Returns a vector3d holding the room's position in which the widget is loaded.
      */
    function getRoomPosition()                 {return room_item.getRoomPosition()}
    /*
      \qmlmethod PluginBase::getRoomScale()
      Returns a vector3d holding the rooms scale in which the widget is loaded.
      */
    function getRoomScale()                    {return room_item.getRoomScale()}
    // REGISTER PLUGIN SO THAT IT CAN RECEIVE MOUSE MOVE EVENTS
    //    function setEditMode(obj)                  {mainWindow.mouseObjectGrabber = obj}
    // TO DISPLAY NOTIFICATION MESSAGE AND POP UP
    /*
      \qmlmethod PluginBase::postNotification(string message, string type)
      */
    function postNotification(message, type)   {mainWindow.postNotification(message, type)}
    /*
      \qmlmethod PluginBase::showPopUp(string popupUrl)
      */
    function showPopUp(popupUrl)               {mainWindow.showPopUp(url)}

    // RETURNS THE DISTANCE BETWEEN TWO POINTS
    /*
      \qmlmethod PluginBase::computeDistance(vector3d pointA, vector3d pointB)
      Returns the distance between \a pointA and \a pointB.
      */
    function computeDistance(pointA, pointB)
    {
        return Math.sqrt(Math.pow((pointA.x - pointB.x), 2) +
                         Math.pow((pointA.y - pointB.y), 2) +
                         Math.pow((pointA.z - pointB.z), 2))
    }

    // RETURNS ROTATION OF A POINT AROUND AN ORIGIN POINT AND AN ANGLE
    /*
      \qmlmethod PluginBase::computeRotation(vector3d originPoint, vector3d rotPoint, vector3d rotAxis, real rotAngle)
      Returns a vector3d holding the position of the point specified by the rotation of the point \a rotPoint around \a rotAngle degrees on \a rotAxis on the origin \a originPoint.
    */
    function computeRotation(originPoint, rotPoint, rotAxis, rotAngle)
    {
        var radAngle = Math.PI * rotAngle / 180;
        var translatedOrigin = Qt.vector3d(rotPoint.x -originPoint.x,
                                           rotPoint.y -originPoint.y,
                                           rotPoint.z -originPoint.z);
        var rotatedPoint;
        if (rotAxis.x !== 0)
            rotatedPoint = Walls.xAxisRotation(translatedOrigin, rotAxis.x * radAngle)
        else if (rotAxis.y !== 0)
            rotatedPoint = Walls.yAxisRotation(translatedOrigin, rotAxis.y * radAngle)
        else
            rotatedPoint = Walls.zAxisRotation(translatedOrigin, rotAxis.z * radAngle);
        rotatedPoint.x += originPoint.x;
        rotatedPoint.y += originPoint.y;
        rotatedPoint.z += originPoint.z;
        return rotatedPoint;
    }

    PluginProperties
    {
        id : plugin_properties
        pluginId : plugin_base.pluginId
        pluginRoomId: plugin_base.pluginRoomId

        onPluginIdChanged :        {}
        onPluginRoomIdChanged: {console.log("RoomId " + pluginRoomId)}

        // WHEN CREATED A PLUGIN IS NOT LOADED BEFORE IT HAS BEEN INITIALIZED WITH A pluginId AND A roomId
        // ONCE THAT IS DONE, THE FOCUS STATE IS SET TO IDLE
        // IF THE LOADER HAS NOT LOADED ANY ELEMENT YET THEN IT LOADS THE PLUGINS
        // OTHERWISE IT TRANSMITS THE SIGNAL TO THE PLUGIN ITEM

        onFocusStateChanged:
        {
            console.log("v State " + newFocusStateValue + "  "  + focusState);
            // IF THE PLUGIN HAS NEVER BEEN LOADED WE LOAD IT
            if (newFocusStateValue === 0 && !plugin_loader.item)
                plugin_loader.source =  "../../plugins_qml/" + pluginRepoName + "/" + roomQmlFile;
            if (!plugin_loader.item)
                return ;
            // CALL THE FOCUS HANDLER MATCHING THE NEW FOCUS STATE
            if (newFocusStateValue === 2)
            {
                // TELL THE PARENT ROOM THERE IS A PLUGIN FOCUSED
                room_item.isAPluginFocused = true;
                console.log("MENU IS >>>> " + menuQmlFile)
                mainWindow.pluginMenuSource = "../../plugins_qml/" + pluginRepoName + "/" + menuQmlFile;
                plugin_loader.item.switchToFocusedView();
            }
            else
            {
                // MENU IS UNLOADED WHEN NOT IN FOCUSED MODE
                mainWindow.pluginMenuSource = "";
                // TELLS THE ROOM THE PLUGIN IS NO MORE FOCUSED
                if (previousFocusState === 2)
                    room_item.isAPluginFocused = false;
                // CALL MATCHING FOCUS HANDLER IN THE PLUGIN
                if (newFocusStateValue === 0)
                    plugin_loader.item.switchToIdleFocusView();
                else
                    plugin_loader.item.switchToSelectedFocusView();
            }
        }

        onRoomEntered :
        {
            console.log("Room Entered ???");
            if (plugin_loader.item)
                plugin_loader.item.roomEntered();
        }

        onRoomLeft :
        {
            if (plugin_loader.item)
                plugin_loader.item.roomLeft();
            console.log("Room Left ????");
        }
    }

    Item3D
    {
        position : plugin_base.pluginPosition
        Loader    {id : plugin_loader}
    }
}
