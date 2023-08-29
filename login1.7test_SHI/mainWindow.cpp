#include "mainWindow.h"
#include "ui_mainWindow.h"
#include <QListWidgetItem>
#include <QListView>
#include <QIcon>
#include "friend_msg_item.h"
#include <QMessageBox>
#include <addfriend.h>

extern bool addFlag;
extern QString fip;

mainWindow::mainWindow(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::mainWindow)
{
    ui->setupUi(this);
    //


}

mainWindow::~mainWindow()
{
    delete ui;
}


void mainWindow::on_pushButton_friends_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void mainWindow::on_pushButton_groups_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void mainWindow::on_pushButton_set_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


//切换聊天室
void mainWindow::on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{
    QListWidgetItem * item_clicked=ui->groupList->currentItem();
    qDebug()<<item_clicked;
    int row_clicked=ui->groupList->currentRow();
    QString row=QString::number(row_clicked);
    qDebug()<<row;
    ui->groupChat->setPlainText(row);
}
//
void mainWindow::on_pushButton_addGroup_clicked()
{
    QWidget *x=new friend_msg_item(this);
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    newItem->setSizeHint(QSize(40,60));
    ui->groupList->insertItem(0,newItem); //将该newItem插入到后面
    ui->groupList->setItemWidget(newItem, new friend_msg_item(this)); //将buddy赋给该newItem
}

void mainWindow::on_pushButton_exit_clicked() //退出登录
{
    this->close();//关闭
}

void mainWindow::pushButton_searchGroup()
{
    //搜索页面
}

void mainWindow::on_pushButton_addFriend_clicked()  //主页面点击添加好友
{
    addFriend *addfwindow = new addFriend();
    addfwindow->show();
    connect(addfwindow,&addFriend::backToMain,this,&mainWindow::friendAdded);
}

void mainWindow::friendAdded()  //添加好友成功
{
    QWidget *f=new friend_msg_item(this);
    QListWidgetItem *newItem = new QListWidgetItem();       //创建一个newItem
    newItem->setSizeHint(QSize(40,60));
    ui->friendList->insertItem(0,newItem); //将该newItem插入到后面
    ui->friendList->setItemWidget(newItem, new friend_msg_item(this)); //将buddy赋给该newItem

}
