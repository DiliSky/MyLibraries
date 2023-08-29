#ifndef TESTSTACKEDWIDGET_H
#define TESTSTACKEDWIDGET_H


#include "form.h"
#include "widget.h"
#include "addfriend.h"
#include <QWidget>
#include <QPushButton>
#include <registersuccess.h>
#include <QMouseEvent>
#include <QPoint>
#include <QTcpServer>
#include <QTcpSocket>
QT_BEGIN_NAMESPACE
namespace Ui { class login; }
QT_END_NAMESPACE

class login : public QWidget
{
    Q_OBJECT

public:
    login(QWidget *parent = nullptr);
    ~login();
    static QString test;


protected:
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件
private:
    Ui::login *ui;
//    Form *form;
    Widget *widget;
    addFriend *addfwindow;


    registerSuccess *ReSuccess;
    QPoint m_point;
    //通讯套接字
    QTcpSocket *m_client;




private slots:
    void on_ButtonToRegister_clicked();
    void on_ButtonLogin_clicked();
    void on_ButtonToLogin_clicked();
    void on_ButtonRegister_clicked();
    void on_ButtonLoginClose_clicked();
    void on_ButtonRegsiterClose_clicked();
    void on_subWin_Signal_Received();//
    void on_subWin_Signal1_Received();//点击进入好友列表 发自己ID信号
    void on_subWin_Signal2_Received();//接收到这个signalToMain2信号
    void on_subWin_Signal3_Received();//接收到这个signalToMain3信号

    //edit by whf 8.29
    void on_BtnGroup_clicked();
    void when_Info_Change();
    void when_Add_Group(QString Group_to_Add);
    void when_Create_Group(QString Group_to_Create);
    //whf end


};
#endif // TESTSTACKEDWIDGET_H
