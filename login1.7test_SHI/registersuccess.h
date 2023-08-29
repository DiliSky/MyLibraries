#ifndef REGISTERSUCCESS_H
#define REGISTERSUCCESS_H

#include <QWidget>
#include <QMouseEvent>
#include <QPoint>
namespace Ui {
class registerSuccess;
}

class registerSuccess : public QWidget
{
    Q_OBJECT

public:
    explicit registerSuccess(QWidget *parent = nullptr);
    ~registerSuccess();
     QPoint r_point;
protected:
    void mousePressEvent(QMouseEvent *event); //鼠标按下事件
    void mouseMoveEvent(QMouseEvent *event);  //鼠标移动事件

private slots:
    void on_RegisterOK_clicked();
    void on_RegisterClose_clicked();

private:
    Ui::registerSuccess *ui;


};

#endif // REGISTERSUCCESS_H
