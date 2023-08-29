#ifndef WIDGET_H
#define WIDGET_H

#include "addfriend.h"
#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtDebug>
#include <QMap>
#include "profile_label.h"
#include <QUdpSocket>
#include <QTextStream>

QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT
    enum MsgType {Msg,UsrEnter,UsrLeft};  //群聊消息枚举

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

    //move user data to public by whf 8.29
    int Avatar_path = 0;
    QString ID = "123456";
    QString UserName = "Alice";
    bool sex = true;//male = false,female = true
    QString other = "Null";
    //end

    //群聊实现
    void sndMsg(MsgType type); //广播UDP消息
    void usrEnter(QString usrName); //处理新用户加入
    void usrLeft(QString usrName,QString time); //处理用户离开
    QString getUsr(); //获取用户名
    QString getMsg(); //获取聊天信息
    void closeEvent(QCloseEvent *);//关闭事件



private slots:
    void on_pushButton_groups_clicked();   //点击实现群聊
    void on_pushButton_friends_clicked();  //点击实现好友对话
    void on_pushButton_set_clicked();      //点击进行设置
    void on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);  //切换聊天室
    void on_pushButton_addGroup_clicked(); //点击添加群聊
    void on_pushButton_exit_clicked();     //点击退出
    void pushButton_searchGroup();         //点击搜索群聊
    void on_pushButton_addFriend_clicked();  //点击添加好友
    void friendAdded();//收到信号函数执行
    void groupAdded();//收到信号函数执行
    void on_Profile_Lable_clicked();//click Profile_Label to show mini windows

    void on_Avatar_Change_clicked();

    void on_Btn_OK_clicked();

    void on_Btn_Cancel_clicked();

    void toLogin();
    void gToLogin();

    //edit by whf 8.29
    void on_pushButton_createGroup_clicked();
    //end



private:
    Ui::Widget *ui;
    QMap<QListWidgetItem *,QString> maps;

    Info_MiniWidget * Miniw = nullptr;//mini info windows

    //群聊
    QUdpSocket * udpSocket; //udp套接字
    qint16 port; //端口
    QString uName; //用户名
    void ReceiveMessage(); //接受UDP消息
    //end



signals:
    void signalToMain();
    //sjyStart
    void signalToMain1();//点击进入好友列表，给login界面发自己的ID信号
    void signalToMain2();//点击添加好友，在widget中转向login发送信号，与backtologin相关
    void signalToMain3();//点击添加群聊，在widget中转向login发送信号，与gbacktologin相关
    //sjyEnd

    //added by whf 8.29
    void BtnGroup_clicked();//request group list through login's socket
    void Info_Change();
    void Add_Group(QString GroupID_to_Add);
    void Create_Group(QString GroupID_to_Create);
    //end

    //added 群聊功能
    //关闭窗口发送关闭信息
    void closeWidget();
    //end

};

#endif // WIDGET_H
