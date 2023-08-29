#include "profile_label.h"


Profile_Label::Profile_Label(QWidget* parent):QLabel(parent)
{
    this->setMouseTracking(true);
}

void Profile_Label::mousePressEvent(QMouseEvent *ev)
{
    if(ev->button() == Qt::RightButton)
        emit clicked();
}
