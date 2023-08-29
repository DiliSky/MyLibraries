#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QListWidget>
#include <QListWidgetItem>
#include <QtDebug>
#include <QMap>
#include <addfriend.h>

QT_BEGIN_NAMESPACE
namespace Ui { class mainWindow; }
QT_END_NAMESPACE

class mainWindow : public QWidget
{
    Q_OBJECT

public:
    mainWindow(QWidget *parent = nullptr);
    ~mainWindow();

private slots:
    void on_pushButton_groups_clicked();   //点击实现群聊
    void on_pushButton_friends_clicked();  //点击实现好友对话
    void on_pushButton_set_clicked();      //点击进行设置
    void on_listWidget_2_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous);  //切换聊天室
    void on_pushButton_addGroup_clicked(); //点击添加群聊
    void on_pushButton_exit_clicked();     //点击退出
    void pushButton_searchGroup();         //点击搜索群聊
    void on_pushButton_addFriend_clicked();  //点击添加好友
    //
    void friendAdded();

private:
    Ui::mainWindow *ui;
    QMap<QListWidgetItem *,QString> maps;
    addFriend *addfwindow;   //好友添加
};
#endif // WIDGET_H
