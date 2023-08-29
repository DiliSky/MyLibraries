#include "login.h"
#include "ui_login.h"
#include "addfriend.h"
#include "widget.h"
#include <QLabel>
#include <registersuccess.h>
#include <QHostAddress>
#include <QTcpSocket>
#include <QByteArray>
#include <QDebug>

extern QString getfid;//全局变量传输新好友的ID
extern QString getgid;//全局变量传输新群聊的ID

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
//    form = new Form();
    widget = new Widget();


    ReSuccess = new registerSuccess();

    //sjyStart
    connect(widget,&Widget::signalToMain,this,&login::on_subWin_Signal_Received);
    connect(widget,&Widget::signalToMain1,this,&login::on_subWin_Signal1_Received);
    connect(widget,&Widget::signalToMain2,this,&login::on_subWin_Signal2_Received);//添加好友信号最终站
    connect(widget,&Widget::signalToMain3,this,&login::on_subWin_Signal3_Received);//添加好友信号最终站
    //sjyEnd

    //edit by whf 8.29
    connect(widget,&Widget::BtnGroup_clicked,this,&login::on_BtnGroup_clicked);//sent by group buttom when it's clicked.
    connect(widget,&Widget::Info_Change,this,&login::when_Info_Change);
    connect(widget,&Widget::Add_Group,this,&login::when_Add_Group);
    connect(widget,&Widget::Create_Group,this,&login::when_Create_Group);
    //end

    //无边框效果
    //this->setWindowFlag(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowSystemMenuHint | Qt::WindowMinimizeButtonHint|this->windowFlags());

    //连接服务器start

    //1 建立通讯套接字
    m_client = NULL;
    m_client = new QTcpSocket(this);
    this->setWindowTitle("客户端");
    m_client->connectToHost(QHostAddress("127.0.0.1"),6666);
    //2 当连接按钮被点击，向服务器发起连接请求
    //如果连接成功    返回成功字符串
    connect(m_client,&QTcpSocket::connected,
            [=]()
    {
        ui->textEditRead->setText("成功与服务器连接");
    });
    //3 收发数据
    connect(m_client,&QTcpSocket::readyRead,
            [=]()
    {
        //获取对方发送的内容
        QByteArray array = m_client->readAll();
        //追加到界面的文本区
        ui->textEditRead->append(array);

    });
    //4 断开

    //连接服务器end
}

login::~login()
{
    delete ui;
}

void login::on_ButtonToRegister_clicked()
{
    static int i = 1;
    ui->stackedWidget->setCurrentIndex( ++i % 2 );
}

void login::on_ButtonLogin_clicked()
{
    this->hide();
    widget->show();

    //从界面获取IP和PORT
    //QString ip = ui->lineEditIP->text();
    //qint16 port = ui->lineEditPort->text().toUInt();
    //向服务器发起连接
    //m_client->connectToHost(QHostAddress("127.0.0.1"),6666);

    //send
    //获取界面文本框内容
    QString str = ui->lineEditUser->text();
    QString str1 = ui->lineEditPassword->text();

    QString str2 = "LOGIN##";
    m_client->write(str2.toUtf8().data());
    //写入套接字

    m_client->write(str.toUtf8().data());
    QString str3 = "##";
    m_client->write(str3.toUtf8().data());//##
    m_client->write(str1.toUtf8().data());
    //清除界面发送区
    //ui->textEditWrite->clear();

    m_client->disconnectFromHost();


}

void login::on_ButtonToLogin_clicked()
{
    static int j = 1;
    ui->stackedWidget->setCurrentIndex( ++j % 2 );
}

void login::on_ButtonRegister_clicked()
{
    //if(数据库成功写入信息)
    ReSuccess->show();
    //else
    //Refail->show();
    //m_client->connectToHost(QHostAddress("127.0.0.1"),6666);
    QString str = ui->lineEditUserName->text();
    QString str1 = ui->lineEditSetPs->text();
    QString str5 = ui->lineEditConfirmPs->text();

    QString str2 = "REGISTER##";
    m_client->write(str2.toUtf8().data());
    m_client->write(str.toUtf8().data());
    QString str3 = "##";m_client->write(str3.toUtf8().data());//##
    m_client->write(str1.toUtf8().data());
    m_client->write(str3.toUtf8().data());//##
    m_client->write(str5.toUtf8().data());
}



//鼠标按下
void login::mousePressEvent(QMouseEvent *event)
{
   if(event->button() == Qt::LeftButton)
   {
       m_point = event->globalPos() - pos(); //计算移动量
       event->accept();
   }
}

//鼠标移动
void login::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() & Qt::LeftButton)
    {
        move(event->globalPos() - m_point);
        event->accept();
    }
}





void login::on_ButtonLoginClose_clicked()
{
    this->close();
}

void login::on_ButtonRegsiterClose_clicked()
{
    this->close();
}

void login::on_subWin_Signal_Received()
{

    //向服务器发送LOGOUT##id
    QString str = ui->lineEditUser->text();
    QString str2 = "LOGOUT##";
    m_client->write(str2.toUtf8().data());
    m_client->write(str.toUtf8().data());

    ui->lineEditUser->clear();
    ui->lineEditPassword->clear();
    widget->hide();
    this->show();
    //qDebug()<<"成功";


}

void login::on_subWin_Signal1_Received()
{
    QString str = ui->lineEditUser->text();
    QString str2 = "SHOWFRIENDLIST##"+str;
    m_client->write(str2.toUtf8().data());
}

void login::on_subWin_Signal2_Received()
{
    QString str = ui->lineEditUser->text();
    QString str2 = "ADDFRIEND##"+str+"##"+getfid;
    m_client->write(str2.toUtf8().data());
}

void login::on_subWin_Signal3_Received()
{
    QString str = ui->lineEditUser->text();
    QString str2 = "ADDGROUPS##"+str+"##"+getgid;
    m_client->write(str2.toUtf8().data());
}

//request write by whf 8.29
void login::on_BtnGroup_clicked()
{
    m_client->write((QString("SHOWGROUPLIST##")+widget->ID).toUtf8().data());

    //?
}
void login::when_Info_Change()
{
    m_client->write((QString("CHANGESETTINGS##")+widget->ID+"##"
                     + widget->UserName + "##"
                     + QString::number(widget->Avatar_path) + "##"
                     + widget->other).toUtf8().data());
}

void login::when_Add_Group(QString Group_to_Add)
{
    m_client->write((QString("ADDGROUP##") + widget->ID + "##"
                     + Group_to_Add).toUtf8().data());
}

void login::when_Create_Group(QString Group_to_Create)
{
    m_client->write((QString("NEWGROUP##") + widget->ID + "##"
                     + Group_to_Create).toUtf8().data());
}
//end






