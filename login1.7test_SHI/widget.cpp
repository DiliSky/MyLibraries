#include "widget.h"
#include "login.h"
#include "ui_widget.h"
#include "addfriend.h"
#include "addgroup.h"
#include <QListWidgetItem>
#include <QListView>
#include <QIcon>
#include "friend_msg_item.h"
#include <QMessageBox>
#include <addfriend.h>
#include <QDataStream>
#include <QMessageBox>
#include <QDateTime>
#include <QColorDialog>
#include <QFileDialog>
#include <QFile>

extern bool addFlag;
extern QString fip;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    connect(ui->label_2,&Profile_Label::clicked,this,&Widget::on_Profile_Lable_clicked);
//群聊
    //初始化操作
    udpSocket = new QUdpSocket(this);
    //用户名获取
   /* uName = name;*/
    //端口号
    this->port = 8888;
    //绑定端口号 绑定模式 共享地址，断线重连 *****
    udpSocket->bind(QHostAddress::Any,port);

//    //发送新用户进入
//    sndMsg(UsrEnter);

    //点击发送按钮发送消息
    connect(ui->pushButton_sendgroupmessage,&QPushButton::clicked,[=](){
        sndMsg(Msg);
    });

    //监听别人发送的数据
    connect(udpSocket,&QUdpSocket::readyRead,this,&Widget::ReceiveMessage);

    //点击退出接触 实现关闭窗口***********
    connect(ui->pushButton_exit,&QPushButton::clicked,[=](){
        this->close();
    });

    // 辅助功能
    //字体
//    connect(ui->fontCbx,&QFontComboBox::currentFontChanged,[=](const QFont &font){
//        ui->msgTextEdit->setCurrentFont(font);
//        ui->msgTextEdit->setFocus();
//    });

    //字号
//    void(QComboBox:: *cbxsignal)(const QString &text) = &QComboBox::currentIndexChanged;
//    connect(ui->sizeCbx,cbxsignal,[=](const QString &text){
//        ui->msgTextEdit->setFontPointSize(text.toDouble());
//        ui->msgTextEdit->setFocus();
//    });

    //加粗
//    connect(ui->boldTBtn,&QToolButton::clicked,[=](bool isCheck){
//        if(isCheck)
//        {
//            ui->msgTextEdit->setFontWeight(QFont::Bold);
//        }
//        else
//        {
//            ui->msgTextEdit->setFontWeight(QFont::Normal);
//        }

//    });

    //倾斜
//    connect(ui->italicTBtn,&QToolButton::clicked,[=](bool check){
//        ui->msgTextEdit->setFontItalic(check);

//    });

    //下划线
//    connect(ui->underlineTBtn,&QToolButton::clicked,[=](bool check){
//        ui->msgTextEdit->setFontUnderline(check);
//    });

    //字体颜色
//    connect(ui->colorTBtn,&QToolButton::clicked,[=](){
//        QColor color = QColorDialog::getColor(Qt::red);
//        ui->msgTextEdit->setTextColor(color);
//    });

    //清空聊天记录
//    connect(ui->clearTBtn,&QToolButton::clicked,[=](){
//        ui->msgBrowser->clear();
//    });

    //保存聊天记录
//    connect(ui->saveTBtn,&QToolButton::clicked,[=](){
//        if(ui->msgBrowser->document()->isEmpty())
//        {
//            QMessageBox::warning(this,"警告","内容不能为空");
//            return;
//        }
//        else
//        {
//            QString path = QFileDialog::getSaveFileName(this,"保存记录","聊天记录","(*.txt)");
//            if(path.isEmpty())
//            {
//                QMessageBox::warning(this,"警告","路径不能为空");
//                return;
//            }
//            else
//            {
//                QFile file(path);
//                //打开模式加换行操作
//                file.open(QIODevice::WriteOnly | QIODevice::Text);
//                QTextStream stream(&file);
//                stream << ui->msgBrowser->toPlainText();
//                file.close();
//            }
//        }
//    });

    //群聊end
}

Widget::~Widget()
{
    delete ui;
    if(Miniw!=nullptr)
        delete Miniw;
}




void Widget::on_pushButton_friends_clicked()
{

    ui->stackedWidget->setCurrentIndex(1);
    QTcpSocket *socket=new QTcpSocket();
    socket->connectToHost(QHostAddress("127.0.0.1"),6666);
    QString str="SHOWFRIENDLIST##"+ID;
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
        QString flag1 = QString(buffer).section("##",0,0);
        //处理数据
        int friendsnum=QString(buffer).section("##",1,1).toInt();
        QList <QString> friendid;
        QList <QString> friendislogin;
        QList <QString> friendip;
        QList <QString> friendusername;
        QList <int> friendavatar;
        QList <QString> friendothers;
        for (int i=0;i<friendsnum;i++) {
            friendid.append(QString(buffer).section("##",2+i*6,2+i*6));
            friendislogin.append(QString(buffer).section("##",3+i*6,3+i*6));

            friendip.append(QString(buffer).section("##",4+i*6,4+i*6));
            friendusername.append(QString(buffer).section("##",5+i*6,5+i*6));
            friendavatar.append(QString(buffer).section("##",6+i*6,6+i*6).toInt());
            friendothers.append(QString(buffer).section("##",7+i*6,7+i*6));
        }
        ui->stackedWidget->setCurrentIndex(1);
        for (int i=0;i++;i<friendsnum) {
            QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
            newItem->setSizeHint(QSize(40,60));

            ui->friendList->insertItem(0,newItem); //将该newItem插入到后面
            ui->friendList->setItemWidget(newItem, new friend_msg_item(friendavatar.at(i),friendid.at(i),friendusername.at(i)));//将buddy赋给该newItem
        }



    });
    socket->disconnectFromHost();
}
void Widget::on_pushButton_groups_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);

    emit BtnGroup_clicked();
}

void Widget::on_pushButton_set_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
    ui->Avatar_Label0->setPixmap(QPixmap(":/new/prefix1/0.img").scaled(200,200,Qt::KeepAspectRatio));//set up the index when change picture file.
    ui->Avatar_Label1->setPixmap(QPixmap(":/new/prefix1/1.img").scaled(200,200,Qt::KeepAspectRatio));
    ui->Avatar_Label2->setPixmap(QPixmap(":/new/prefix1/2.img").scaled(200,200,Qt::KeepAspectRatio));
    ui->Avatar_Label3->setPixmap(QPixmap(":/new/prefix1/3.img").scaled(200,200,Qt::KeepAspectRatio));
    ui->Avatar_Label4->setPixmap(QPixmap(":/new/prefix1/4.img").scaled(200,200,Qt::KeepAspectRatio));
    ui->ID_Show->setText(ID);
    ui->Sex_ComboBox->setCurrentIndex(sex);
    ui->Other_LineEdit->setText(other);
    ui->UserNameEdit->setText(UserName);
}

//切换聊天室
void Widget::on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QListWidgetItem * item_clicked=ui->groupList->currentItem();
    qDebug()<<item_clicked;
    int row_clicked=ui->groupList->currentRow();
    QString row=QString::number(row_clicked);
    qDebug()<<row;
    ui->groupChat->setPlainText(row);
}

//
void Widget::on_pushButton_addGroup_clicked()//widget主页面点击添加群聊
{
    //new QListWidgetItem (QIcon(":/new/prefix1/Image/Tom-1.jpg"),"PROCESS",ui->listWidget_2);
    //ui->listWidget_2->setItemWidget(,this);
    //QListView *LIST=new QListView();
    QWidget *x=new friend_msg_item(this);
    //LIST->setIndexWidget(,x);

    //edit by whf 8.29
    emit Add_Group(QString("GroupID to add"));
    //end

    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    newItem->setSizeHint(QSize(40,60));
    ui->groupList->insertItem(0,newItem); //将该newItem插入到后面
    ui->groupList->setItemWidget(newItem, new friend_msg_item(this)); //将buddy赋给该newItem

    //sjyStart
    addGroup *addgwindow = new addGroup();
    addgwindow->show();
    connect(addgwindow,&addGroup::gBackToMain,this,&Widget::groupAdded);
    connect(addgwindow,&addGroup::gBackToLogin,this,&Widget::gToLogin);//弹出输入新群聊ID窗口，点击添加，发送backToLogin信号至login,login::receivesignal2向客服端写myid和addgid
    //sjyEnd
}

void Widget::on_pushButton_exit_clicked()
{
    emit signalToMain();
    //qDebug()<<"发信号成功";
    //this->close();//关闭

    //denglu.show();
}

void Widget::pushButton_searchGroup()
{
    //搜索页面
}
void Widget::on_pushButton_addFriend_clicked()  //主页面点击添加好友
{

    addFriend *addfwindow = new addFriend();
    addfwindow->show();
    connect(addfwindow,&addFriend::backToMain,this,&Widget::friendAdded);
    connect(addfwindow,&addFriend::backToLogin,this,&Widget::toLogin);//弹出输入新好友ID窗口，点击添加，发送backToLogin信号至login,login::receivesignal2向客服端写myid和addid
}


void Widget::friendAdded()  //添加好友成功
{
    QWidget *f=new friend_msg_item(this);
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    newItem->setSizeHint(QSize(40,60));
    ui->friendList->insertItem(0,newItem); //将该newItem插入到后面
    ui->friendList->setItemWidget(newItem, new friend_msg_item(this)); //将buddy赋给该newItem


}

void Widget::groupAdded()   //添加群聊成功
{
    qDebug()<<"添加群聊成功";
}
void Widget::on_Profile_Lable_clicked()
{
    if(nullptr == Miniw)
        Miniw = new Info_MiniWidget();
    Miniw->setAvatar(":/new/prefix1/"+QString::number(Avatar_path)+".img");
    Miniw->setID(ID);
    Miniw->setUserName(UserName);
    Miniw->show();
}

void Widget::on_Avatar_Change_clicked()
{
//    temp_Avatar_path = QFileDialog::getOpenFileName(this,"Select a photo.",":/new/prefix1/Image","picture(*.jpg *.png *.jpeg);;all(*.*)");
    //getOpenFileName can directly access .qrc file tree.

//    ui->Avatar_Label->setPixmap(QPixmap(temp_Avatar_path).scaled(200,200,Qt::KeepAspectRatio));

    //use stackwidget to show all avatars
    if(ui->Show_Avatar->currentIndex()<=3)
        ui->Show_Avatar->setCurrentIndex(ui->Show_Avatar->currentIndex()+1);
    else
        ui->Show_Avatar->setCurrentIndex(0);
}

void Widget::on_Btn_OK_clicked()
{
    auto ret = QMessageBox::question(this,"Question","Are you sure to save the configuration?",QMessageBox::Yes | QMessageBox::No , QMessageBox::No);
    switch (ret)
    {
        case QMessageBox::Yes:
            {
               Avatar_path = ui->Show_Avatar->currentIndex();
               UserName = ui->UserNameEdit->text();
               sex = ui->Sex_ComboBox->currentIndex();
               other = ui->Other_LineEdit->text();
               ui->label_2->setPixmap(QPixmap(":/new/prefix1/"+QString::number(Avatar_path)+".img").scaled(200,200,Qt::KeepAspectRatio));
               //edit by whf 8.29
               emit Info_Change();
               //end
               return;
            }
            ui->stackedWidget->setCurrentIndex(0);
            break;
        case QMessageBox::No:
            return;
            break;
    }
    //发CHANGESETTINGS##id##username##avatat##others信息至login中
}



void Widget::on_Btn_Cancel_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Widget::toLogin()
{
    //qDebug()<<"888";
    emit signalToMain2();//to login`s signal
}

void Widget::gToLogin()
{
    //qDebug()<<"888";
    emit signalToMain3();//to login`s signal
}

//edit by whf 8.29
void Widget::on_pushButton_createGroup_clicked()
{
    emit Create_Group(QString("GroupID to create"));
}



/************************************************/


void Widget::ReceiveMessage(){
    //拿到数据报文
    //获取长度
    qint64 size = udpSocket->pendingDatagramSize();

    QByteArray array = QByteArray(10000,0);
    udpSocket->readDatagram(array.data(),size);

    //解析数据
    //第一段 类型 第二段 用户名 第三段 内容
    QDataStream stream(&array,QIODevice::ReadOnly);
    int msgType; //读取到类型
    QString usrName;
    QString msg;

    //获取当前时间
    QString time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
    stream >> msgType;

    switch (msgType) {
    case Msg: //普通聊天
        stream >> usrName >>msg;

        //追加聊天记录
        ui->groupChatDialog->setTextColor(Qt::blue);
        ui->groupChatDialog->append("["+ usrName +"]" + time);
        ui->groupChatDialog->append(msg);
        break;
//    case UsrEnter:
//         stream >> usrName;
//         usrEnter(usrName);
//        break;
//    case UsrLeft:
//        stream >> usrName;
//        usrLeft(usrName,time);
//        break;
    }
} //接受UDP消息

void Widget::usrLeft(QString usrName,QString time) /**********************/
{
//    //更新右侧tableWidget
//    bool isEmpty = ui->usrBb1Widget->findItems(usrName,Qt::MatchExactly).isEmpty();
//    if(!isEmpty)
//    {
//        int row = ui->usrBb1Widget->findItems(usrName,Qt::MatchExactly).first()->row();
//        ui->usrBb1Widget->removeRow(row);
//        //追加聊天记录
//        ui->groupChatDialog->setTextColor(Qt::gray);
//        ui->groupChatDialog->append(QString("%1 于 %2 离开").arg(usrName).arg(time));
//        //在线人数更新
//        ui->usrNumLb1->setText(QString("在线用户：%1").arg(ui->usrBb1Widget->rowCount()));

 //   }

}

//void Widget::usrEnter(QString usrName)
//{
//    //更新右侧TableWidget

//    bool isEmpty = ui->usrBb1Widget->findItems(usrName,Qt::MatchExactly).isEmpty();
//    if(isEmpty)
//    {
//        QTableWidgetItem * usr = new QTableWidgetItem(usrName);

//        //插入行
//        ui->usrBb1Widget->insertRow(0);
//        ui->usrBb1Widget->setItem(0,0,usr);
//        //追加聊天记录
//        ui->msgBrowser->setTextColor(Qt::gray);
//        ui->msgBrowser->append(QString("%1 上线了").arg(usrName));
//        //在线人数更新
//        ui->usrNumLb1->setText(QString("在线用户：%1").arg(ui->usrBb1Widget->rowCount()));
//        //把自身信息广播出去
//        sndMsg(UsrEnter);
//    }
//}//处理新用户加入

void Widget::sndMsg(MsgType type)
{
    //发送的消息分为3种类型
    //发送的数据 做分段处理 第一段 类型 第二段 用户名 第三段 具体内容
    QByteArray array;

    QDataStream stream(&array, QIODevice::WriteOnly);

    stream << type << getUsr(); //第一段内容 添加到流中 第二段 用户名

    switch (type) {
    case Msg: //普通消息发送
        if(ui->groupChat->toPlainText() == "") //判断如果用户没有输入内容，不发任何消息
        {
            QMessageBox::warning(this,"警告","发送内容不能为空");
            return;
        }
        //第三段数据,具体说的话
        stream << getMsg();
        break;
    case UsrEnter: //新用户进入消息
        break;
    case UsrLeft: //用户离开消息
        break;
    default:
        break;
    }

    //书写报文 广播发送
    udpSocket->writeDatagram(array,QHostAddress::Broadcast,port);
}//广播UDP消息
QString Widget::getUsr()
{
    return this->uName;
}
QString Widget::getMsg() //获取聊天信息
{
    QString str = ui->groupChatDialog->toHtml();

    //清空输入框
    ui->groupChat->clear();
    ui->groupChat->setFocus();

    return str;
}
void Widget::closeEvent(QCloseEvent *)
{
    emit this->closeWidget();
    sndMsg(UsrLeft);
    //断开套接字
    udpSocket->close();
    udpSocket->destroyed();
}





