#include "widgetmodel.h"

WidgetModel::WidgetModel() : QObject()
{
    this->myvar = 15;
}

int WidgetModel::getMyVar() const
{
    return this->myvar;
}

void WidgetModel::setMyVar(int v)
{
    this->myvar = v;
    emit(myVarChanged(this->myvar)); // EMIT CHANGED SIGNAL
}


