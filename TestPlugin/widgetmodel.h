#ifndef WIDGETMODEL_H
#define WIDGETMODEL_H

#include <QObject>

class WidgetModel : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int myvar READ getMyVar WRITE setMyVar NOTIFY myVarChanged)

signals:
    void myVarChanged(int);

public:
         WidgetModel();
    int  getMyVar() const;
    void setMyVar(int);
private :
    int myvar;
};

#endif // WIDGETMODEL_H
