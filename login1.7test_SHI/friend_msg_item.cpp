#include "friend_msg_item.h"
#include "ui_friend_msg_item.h"

friend_msg_item::friend_msg_item(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::friend_msg_item)
{
    ui->setupUi(this);

}

friend_msg_item::friend_msg_item(int i,QString id,QString username) :

    ui(new Ui::friend_msg_item)
{
    ui->setupUi(this);

    ui->label->setPixmap(QPixmap(QString(":/new/prefix1/%1.img").arg(i)));
    ui->lineEdit->setText(id);
    ui->lineEdit_2->setText(username);
}

friend_msg_item::~friend_msg_item()
{
    delete ui;
    //登录时


}
