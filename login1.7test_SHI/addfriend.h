#ifndef ADDFRIEND_H
#define ADDFRIEND_H

//#include "login.h"下层不包含上层
#include <QWidget>
#include <QDialog>
#include <QMessageBox>

namespace Ui {
class addFriend;
}

class addFriend : public QWidget
{
    Q_OBJECT

public:
    explicit addFriend(QWidget *parent = nullptr);
    ~addFriend();
    QString fid;   //记录所添加的好友的id

private:
    Ui::addFriend *ui;
    QMessageBox msgBox;

private slots:
    void on_pushButtonAddF_clicked();

signals:
    void backToMain();
    void backToLogin();//好友双重连接
    void backToMain2();




};



#endif // ADDFRIEND_H
