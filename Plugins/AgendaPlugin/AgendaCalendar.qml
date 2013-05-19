import QtQuick 2.0

Item
{
    id : monthly_view

    anchors.fill: parent
    x : 500
    y : (mainWindow.height * 0.1)
    width : (mainWindow.width * 0.8)
    height : (mainWindow.height * 0.8)

    property int daybeginning_month : {AgendaPlugin.getBeginDayOfTheMonth(); }
    property int monthlength : {AgendaPlugin.getMonthLength(); }

    Item
    {
        id : day_display

        Text {
          x : ((mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * 1))
          y : (mainWindow.height * 0.1)
          width : (mainWindow.width * 0.1)
          height : ((mainWindow.height * 0.8) / 7)
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text : "Mon"
          font.family : "Helvetica"
          font.pointSize : 24
          color : "white"
        }
     Text {
          x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * 2)
          y : (mainWindow.height * 0.1)
          width : (mainWindow.width * 0.1)
          height : ((mainWindow.height * 0.8) / 7)
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text : "Tue"
          font.family : "Helvetica"
          font.pointSize : 24
          color : "white"
        }
        Text {
          x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * 3)
          y : (mainWindow.height * 0.1)
          width : (mainWindow.width * 0.1)
          height : ((mainWindow.height * 0.8) / 7)
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text : "Wed"
          font.family : "Helvetica"
          font.pointSize : 24
          color : "white"
        }
        Text {
          x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * 4)
          y : (mainWindow.height * 0.1)
          width : (mainWindow.width * 0.1)
          height : ((mainWindow.height * 0.8) / 7)
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text : "Thr"
          font.family : "Helvetica"
          font.pointSize : 24
          color : "white"
        }
        Text {
          x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * 5)
          y : (mainWindow.height * 0.1)
          width : (mainWindow.width * 0.1)
          height : ((mainWindow.height * 0.8) / 7)
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text : "Fri"
          font.family : "Helvetica"
          font.pointSize : 24
          color : "white"
        }
        Text {
          x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * 6)
          y : (mainWindow.height * 0.1)
          width : (mainWindow.width * 0.1)
          height : ((mainWindow.height * 0.8) / 7)
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text : "Sat"
          font.family : "Helvetica"
          font.pointSize : 24
          color : "white"
        }
        Text {
          x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * 7)
          y : (mainWindow.height * 0.1)
          width : (mainWindow.width * 0.1)
          height : ((mainWindow.height * 0.8) / 7)
          verticalAlignment: Text.AlignVCenter
          horizontalAlignment: Text.AlignHCenter
          text : "Sun"
          font.family : "Helvetica"
          font.pointSize : 24
          color : "white"
        }
    }
    Item
    {
        id : month_display

        x : (parent.x)
        y : parent.y
        anchors.fill: parent

        Item
        {
            id : week1
            AgendaCalendarDayRect
            {
               daynb: 1

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 2

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 3

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 4

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 5

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 6

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 7

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }

        }
        Item
        {
            id : week2
            AgendaCalendarDayRect
            {
               daynb: 8

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 9

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 10

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 11

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 12

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 13

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 14

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
        }
        Item
        {
            id : week3
            AgendaCalendarDayRect
            {
               daynb: 15

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 16

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 17

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 18

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 19

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 20

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 21

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
        }
        Item
        {
            id : week4

            AgendaCalendarDayRect
            {
               daynb: 22

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 23

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 24

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 25

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 26

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 27

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 28

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
        }
        Item
        {
            id : week5

            AgendaCalendarDayRect
            {
               daynb: 29

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 30

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 31

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 32

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 33

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 34

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 35

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
        }
        Item
        {
            id : week6

            AgendaCalendarDayRect
            {
               daynb: 36

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 37

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 38

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 39

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 40

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 41

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
            AgendaCalendarDayRect
            {
               daynb: 42

               enabled: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month)))
               opacity: ((daynb >= monthly_view.daybeginning_month) && (daynb < (monthly_view.monthlength + monthly_view.daybeginning_month))) ? 1 : 0
               x : (mainWindow.width * 0.1) + ((mainWindow.width * 0.1) * (((daynb - 1) % 7) + 1))
               y : (mainWindow.height * 0.1) + (((mainWindow.height * 0.8) / 7) * ((((daynb - 1) - ((daynb - 1) % 7)) / 7) + 1))
               width : (mainWindow.width * 0.1)
               height : ((mainWindow.height * 0.8) / 7)
            }
        }
    }
}
