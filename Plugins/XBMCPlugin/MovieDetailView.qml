import QtQuick 2.0

Item
{
    opacity : movie_flow_loader.opacity
    property string movieFile;

    onOpacityChanged:
    {
        if (opacity === 1)
            setPathIndex(movie_flow_listview.currentMovieIdx)
    }

    function  setPathIndex(idx)
    {
        var idx_copy = idx;
        movie_pathview.currentIndex = idx_copy;
    }

    Item
    {
        anchors
        {
            left : parent.left
            leftMargin : 50
            top : parent.top
            topMargin : 10
            right : parent.right
            rightMargin : 50
            bottom : parent.verticalCenter
        }
        Rectangle
        {
            anchors.fill: parent
            color : "black"
            opacity : 0.3
            border
            {
                width : 1
                color : "#c0c0c0"
            }
            radius : 5
            smooth : true
        }
        Image
        {
            id : movie_pic
            height: parent.height - 20
            anchors
            {
                left : parent.left
                verticalCenter : parent.verticalCenter
                leftMargin : 15
            }
            fillMode: Image.PreserveAspectFit
        }
        Text
        {
            id : movie_title
            color : "white"
            anchors
            {
                left : movie_pic.right
                leftMargin : 15
                top : movie_pic.top
            }

            font.pixelSize: mainWindow.largeFontSize
        }


        Text
        {
            id : movie_year_label
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_title.left
                top : movie_title.bottom
                topMargin : 5
            }
            text : "YEAR"
        }
        Text
        {
            id : movie_year
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_year_label.right
                leftMargin : 50
                top : movie_year_label.top
            }
        }

        Text
        {
            id : movie_genre_label
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_title.left
                top : movie_year_label.bottom
                topMargin : 5
            }
            text : "GENRE"
        }
        Text
        {
            id : movie_genre
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_year_label.right
                leftMargin : 50
                top : movie_genre_label.top
            }
        }

        Text
        {
            id : movie_studio_label
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_title.left
                top : movie_genre_label.bottom
                topMargin : 5
            }
            text : "STUDIO"
        }
        Text
        {
            id : movie_studio
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_year_label.right
                leftMargin : 50
                top : movie_studio_label.top
            }
        }

        Text
        {
            id : movie_rating_label
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_title.left
                top : movie_studio_label.bottom
                topMargin : 5
            }
            text : "RATING"
        }
        Text
        {
            id : movie_rating
            color : "white"
            font.pixelSize: mainWindow.defaultFontSize
            anchors
            {
                left : movie_year_label.right
                leftMargin : 50
                top : movie_rating_label.bottom
            }
        }

        Flickable
        {
            anchors
            {
                left : movie_title.left
                right : back_button.left
                rightMargin : 5
                bottom : parent.bottom
                top : movie_rating_label.bottom
                topMargin : 10
            }
            clip : true
            contentWidth: width
            contentHeight: movie_summary.height
            Text
            {
                id : movie_summary
                color : "white"
                width : parent.width
                font.pixelSize: mainWindow.defaultFontSize
                wrapMode: Text.WrapAtWordBoundaryOrAnywhere
            }
        }

        BackButton
        {
            id : back_button
            width : 50
            anchors
            {
                right : parent.right
                bottom : parent.bottom
                margins : 5
            }
            onClicked :
            {
                movie_flow_loader.moveToGridView()
            }
        }
        Image
        {
            id : play_button
            width : 75
            fillMode: Image.PreserveAspectFit
            source : "player_play.png"
            scale : play_button_ma.pressed ? 0.9 : 1
            anchors
            {
                right : parent.right
                top : parent.top
                margins : 5
            }
            MouseArea
            {
                id : play_button_ma
                anchors.fill: parent
                onClicked:
                {
                    XBMCPlugin.playFile(movieFile)
                }
            }
        }
    }


    PathView
    {
        id : movie_pathview
        model : XBMCPlugin.getMoviesLibrary();
        pathItemCount: 10
        preferredHighlightBegin: 0.45
        preferredHighlightEnd: 0.55
        focus : true
        anchors
        {
            top : parent.verticalCenter
            bottom : parent.bottom
            left : parent.left
            leftMargin : 50
            right : parent.right
            rightMargin : 50
        }
        onCurrentIndexChanged:
        {
            movie_pic.source = currentItem.source
            movie_title.text = currentItem.movieTitle
            movie_summary.text = currentItem.movieSummary
            movie_year.text = currentItem.movieYear
            movie_studio.text = currentItem.movieStudio
            movie_genre.text = currentItem.movieGenre
            movieFile = currentItem.movieFile
        }

        path : Path  {
            // LEFT
            startX : parent.x
            startY: parent.y + (parent.height / 4)
            PathPercent {value : 0}
            PathAttribute {name : "delScale"; value : 0.6}
            PathAttribute {name : "delAngle"; value : 30}
            PathAttribute {name : "delZ"; value : -100}

            PathCurve {x : parent.width / 2 - 100; y : parent.y + (parent.height / 4)}
            PathAttribute {name : "delAngle"; value : 60}

            // CENTER
            PathCurve {x : parent.width / 2; y : parent.y + (parent.height / 4)}
            PathAttribute {name : "delScale"; value : 0.8}
            PathAttribute {name : "delZ"; value : 1}

            PathCurve {x : parent.width / 2 + 100; y : parent.y + (parent.height / 4)}
            PathAttribute {name : "delAngle"; value : -60}


            //RIGHT
            PathCurve {x : parent.width; y : parent.y + (parent.height / 4)}
            PathAttribute {name : "delScale"; value : 0.6}
            PathAttribute {name : "delAngle"; value : -30}
            PathAttribute {name : "delZ"; value : -100}
        }

        delegate : Component {
            Image
            {
                property string movieTitle : model.title
                property string movieSummary : model.plot
                property string movieGenre : model.genre
                property string movieStudio : model.studio
                property int    movieYear : model.year
                property int    movieRating : model.rating
                property string movieFile : model.file
                property bool isCurrentItem : (movie_pathview.currentIndex === index)
                fillMode: Image.PreserveAspectFit
                z : PathView.onPath ? PathView.delZ : 0
                scale : (PathView.onPath ? (!isCurrentItem) ? PathView.delScale : 1 : 0) * ((movie_pathview.height - 40) / height)
                property int rAngle : PathView.onPath ? (!isCurrentItem) ? PathView.delAngle : 0 : 0
                transform: [Rotation { origin.x: width / 2; origin.y: 0; axis { x: 0; y: 1; z: 0 } angle: rAngle}]
                source : XBMCPlugin.getXBMCImageProviderUrl(model.thumbnail)
                MouseArea
                {
                    anchors.fill: parent
                    onClicked:
                    {
                        movie_pathview.currentIndex = index;
                    }
                }
                Rectangle
                {
                    anchors.fill: parent
                    visible : isCurrentItem
                    anchors.margins: -5
                    z : -4
                    color : "transparent"
                    radius : 2
                    border
                    {
                        width : 3
                        color : "#0099ff"
                    }
                }
            }
        }

    }
}
