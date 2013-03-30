import QtQuick 2.0
import Qt3D 2.0
import Qt3D.Shapes 2.0

Item3D
{
    id : seriesplugin_item

    position : Qt.vector3d(0, 0, 0)

    property bool isFocused : false;
    property bool addingShow : false;

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
        widgetPos.x += cube.x
        widgetPos.y += cube.y
        widgetPos.z += cube.z
        plugin_base.moveCamera(eyePos, widgetPos);
        isFocused = true;
    }

    Cube
    {
        id : cube
        scale : 5
        effect : cube_effect
        transform : [Rotation3D {id : cube_x_rotate; axis : Qt.vector3d(0, 0, 1); angle : -90},
            Rotation3D {id : cube_y_rotate;axis : Qt.vector3d(0, 1, 0); angle : 45}]

        onClicked :
        {
            console.log("------------------")
            switchToFocusedView();
        }
    }


    ParallelAnimation
    {
        id : rotate_cube
        SmoothedAnimation
        {
            target : cube_x_rotate
            duration : 750
            property : "angle"
            to : cube_x_rotate.angle >= 270 ? -90 : 270
        }
        SequentialAnimation
        {
            SmoothedAnimation
            {
                target : cube
                property : "scale"
                duration : 375
                to : 1
                velocity : 1
            }
            SmoothedAnimation
            {
                target : cube
                property : "scale"
                duration : 375
                to : 5
                velocity : 1
            }
        }
        SmoothedAnimation
        {
            target : cube_y_rotate
            duration : 750
            property : "angle"
            to : cube_y_rotate.angle >= 360 ? 0 : 360
        }
    }

    Effect
    {
        id : cube_effect
        color : "white"
        useLighting : false
        blending : true
    }




    Item
    {
        id : followed_series_item
        enabled : isFocused
        opacity : isFocused ? 1 : 0
        width : mainWindow.width / 4
        height : mainWindow.height / 2
        x : 80
        y : (mainWindow.height - height) / 2
        transform : Rotation { origin.x: 0; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: 15}

        Item
        {
            id : search_bar_container
            smooth : true
            Rectangle
            {
                color : "grey"
                opacity : 0.2
                anchors.fill: parent
            }
            width : parent.width
            height : 40
            anchors.bottom : parent.top
            anchors.bottomMargin: 5

            Item
            {
                id : search_bar_series_item
                enabled : isFocused
                opacity : (isFocused && addingShow) ? 1 : 0

                anchors
                {
                    fill : parent
                    margins : 5
                }
                Rectangle
                {
                    color : "black"
                    opacity : 0.3
                    smooth : true
                    anchors.fill: parent
                    radius : 15
                    border
                    {
                        width : 2
                        color : "gray"
                    }
                }

                TextInput
                {
                    id : search_input
                    width : parent.width - 20
                    wrapMode: TextInput.Wrap
                    anchors
                    {
                        top : parent.top
                        left : parent.left
                        //                verticalCenter : parent.verticalCenter
                        leftMargin : 10
                        bottom : parent.bottom
                    }
                    color : "white"
                    font.pointSize: 12
                }

                Image
                {
                    width : 40
                    height : 40
                    scale : search_button_ma.pressed ? 0.9 :1
                    source : "mag_glass.png"
                    anchors
                    {
                        right : parent.right
                        verticalCenter : parent.verticalCenter
                    }
                    MouseArea
                    {
                        id : search_button_ma
                        anchors.fill: parent
                        onClicked:
                        {
                            SeriesPlugin.searchForShow(search_input.text)
                        }
                    }
                }
            }
        }

        Item
        {
            id : listview_containers
            anchors.fill: parent
            Rectangle
            {
                color : "grey"
                opacity : 0.2
                anchors.fill: parent
            }
            ListView
            {
                id : search_result_listview
                opacity : addingShow ? 1 : 0
                enabled : addingShow
                clip : true
                anchors.fill : parent
                model : SeriesPlugin.getSearchSeriesModel();
                delegate : SeriesSearchListViewDelegate {
                    serieId : model.serieId
                    img_src : model.imageUrl
                    series_name: model.serieName
                    width : parent.width
                    height : 60
                }
                spacing : 10
            }

            ListView
            {
                id : followed_series_listview
                opacity : addingShow ? 0 : 1
                enabled : !addingShow
                smooth : true
                clip : true
                anchors.fill : parent
                addDisplaced: Transition {
                    NumberAnimation { properties: "x,y"; duration: 1000 }
                }
                model : SeriesPlugin.getFollowedSeriesModel();
                delegate : SeriesListViewDelegate {
                    serieId : model.serieId
                    img_src : model.imageUrl
                    series_name: model.serieName
                    width : parent.width
                    height : 60
                }
                spacing : 10
            }
        }
        Image
        {
            height : 50
            width : 50
            scale : add_show_ma.pressed ? 0.9 : 1
            source : addingShow ? "red_cross.png" : "plus.png"
            anchors.top: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            MouseArea
            {
                id : add_show_ma
                anchors.fill: parent
                onClicked:
                {
                    addingShow = !addingShow
                }
            }
        }
    }

    Item
    {
        id : episodes_series_item
        enabled : isFocused
        opacity : isFocused ? 1 : 0
        width : mainWindow.width / 4
        height : mainWindow.height / 2
        x : mainWindow.width - (width + 80)
        y : (mainWindow.height - height) / 2
        transform : Rotation { origin.x: mainWindow.width / 4; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: -15}


        ListView
        {
            id : season_list_view
            height : 80
            orientation: ListView.Horizontal
            clip : true
            displaced: Transition {
                NumberAnimation { properties: "x,y"; duration: 1000 }
            }
            anchors
            {
                top : parent.top
                left : parent.left
                right : parent.right
            }
            delegate : SeasonListViewDelegate {
                img_src : model.imageUrl
                season : model.seasonId
                height : parent.height
                width : season_list_view.width / 4
            }
            Rectangle
            {
                color : "grey"
                opacity : 0.2
                anchors.fill: season_list_view
            }
        }


        ListView
        {
            id : episodes_series_listview
            anchors
            {
                top : season_list_view.bottom
                left : parent.left
                right : parent.right
                bottom : parent.bottom
                topMargin : 5
            }
            populate: Transition {
                NumberAnimation { properties: "x,y"; duration: 1000 }
            }
            clip : true
            delegate : EpisodeListViewDelegate   {
                episodeNumber : model.episodeNumber
                episodeTitle : model.episodeTitle
                episodeOverview : model.episodeSummary
                episodeAiring : model.episodeAiring
                img_src : model.imageUrl
                width : parent.width
                height : 60
            }
            Rectangle
            {
                color : "grey"
                opacity : 0.2
                anchors.fill: parent
            }
        }
    }
}
