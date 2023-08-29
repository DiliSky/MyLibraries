#include "registersuccess.h"
#include "ui_registersuccess.h"
#include <login.h>
registerSuccess::registerSuccess(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerSuccess)
{
    ui->setupUi(this);
    //无边框效果
    this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

}

registerSuccess::~registerSuccess()
{
    delete ui;
}

void registerSuccess::on_RegisterOK_clicked()
{
    this->close();

}

void registerSuccess::on_RegisterClose_clicked()
{
    this->close();

}
//鼠标按下
void registerSuccess::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       r_point = event->globalPos() - pos(); //计算移动量
       event->accept();
   }
}

//鼠标移动
void registerSuccess::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - r_point);
        event->accept();
    }
}

