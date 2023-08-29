#include "addfriend.h"
#include "ui_addfriend.h"
#include "login.h"
#include "widget.h"

#include <QMessageBox>
#include <QDebug>
#include <QString>


QString getfid;


addFriend::addFriend(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addFriend)
{
    ui->setupUi(this);


}

addFriend::~addFriend()
{
    delete ui;
}

void addFriend::on_pushButtonAddF_clicked()  //点击提交id，添加好友
{

    fid = ui->inputID->text();
    getfid = fid;
//    emit backToLogin();
    QTcpSocket *socket=new QTcpSocket();
    socket->connectToHost(QHostAddress("127.0.0.1"),6666);
//    QString str="ADDFRIEND##"+ID+"##"+getfid;
    connect(socket,&QTcpSocket::connected,
            [=]()
    {
        //socket->write(str.toUtf8().data());

    }
    );

    connect(socket,&QTcpSocket::readyRead,
            [=]()
    {
        //获取对方发送的内容
        QByteArray buffer = socket->readAll();
        QString flag1 = QString(buffer).section("##",1,1);
        //处理数据

        if( "success" == flag1 )
        {
            qDebug() << fid;
            msgBox.setText("Add Friend Success!");
            msgBox.exec();
            //emit backToMain();
            int friendid= QString(buffer).section("##",2,2).toInt();
            QString friendislogin= QString(buffer).section("##",3,3);
            QString friendip= QString(buffer).section("##",4,4);
            QString friendusername =QString(buffer).section("##",5,5);
            int friendavatar= QString(buffer).section("##",6,6).toInt();
            QString friendothers= QString(buffer).section("##",7,7);

            QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
            newItem->setSizeHint(QSize(40,60));

            
            emit backToMain2();
          //  friendList->insertItem(0,newItem); //将该newItem插入到后面
        //    friendList->setItemWidget(newItem, new friend_msg_item(friendavatar,friendid,friendusername));//将buddy赋给该newItem
        }
        else if( "friend_added" == flag1)
        {
            msgBox.setText("You already had the friend!");
            msgBox.exec();
        }
        else
        {
            msgBox.setText("no_user!");
            msgBox.exec();
        }






    });
    socket->disconnectFromHost();




}
