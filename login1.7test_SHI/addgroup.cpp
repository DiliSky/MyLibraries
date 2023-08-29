#include "addgroup.h"
#include "ui_addgroup.h"
#include "login.h"
#include <QMessageBox>
#include <QDebug>

QString getgid;

addGroup::addGroup(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::addGroup)
{
    ui->setupUi(this);
}

addGroup::~addGroup()
{
    delete ui;
}

void addGroup::on_pushButtonAddG_clicked()
{

    getgid = ui->inputGID->text();
    emit gBackToLogin();

    
//    emit backToLogin();
    QTcpSocket *socket=new QTcpSocket();
    socket->connectToHost(QHostAddress("127.0.0.1"),6666);
    QString str="ADDFRIEND##ID##"+getgid;
    connect(socket,&QTcpSocket::connected,
            [=]()
    {
        socket->write(str.toUtf8().data());

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
            qDebug() << getgid;
            msgBox.setText("Add Group Success!");
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

            
            //friendList->insertItem(0,newItem); //将该newItem插入到后面
            //friendList->setItemWidget(newItem, new friend_msg_item(friendavatar,friendid,friendusername));//将buddy赋给该newItem
        }
        else if( "friend_added" == flag1)
        {
            msgBox.setText("You already had the group!");
            msgBox.exec();
        }
        else
        {
            msgBox.setText("no_group!");
            msgBox.exec();
        }






        });
    socket->disconnectFromHost();
      }
