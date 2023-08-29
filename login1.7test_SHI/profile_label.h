#ifndef PROFILE_LABEL_H
#define PROFILE_LABEL_H

#include <QLabel>
#include <QObject>
#include <QWidget>
#include "info_miniwidget.h"
#include <QMouseEvent>

class Profile_Label : public QLabel//inheriting QLabel,for click operate.
{
    Q_OBJECT
public:
    Profile_Label(QWidget* parent);
signals:
    void clicked();
protected:
    void mousePressEvent(QMouseEvent *ev);//track mouse's press,release a new mini windows.
};

#endif // PROFILE_LABEL_H
