
SOURCES += $$PWD/LeapGestureArea/LeapGestureArea.cpp \
           $$PWD/Tepee3DTouchArea/Tepee3DTouchArea.cpp


HEADERS += $$PWD/LeapGestureArea/LeapGestureArea.h \
           $$PWD/Tepee3DTouchArea/Tepee3DTouchArea.h

INCLUDEPATH += $$PWD/LeapGestureArea
INCLUDEPATH += $$PWD/Tepee3DTouchArea
INCLUDEPATH += $$PWD

mac :{
QT += quick-private
}
