#ifndef ADDGROUP_H
#define ADDGROUP_H

#include <QWidget>
#include <QMessageBox>

namespace Ui {
class addGroup;
}

class addGroup : public QWidget
{
    Q_OBJECT

public:
    explicit addGroup(QWidget *parent = nullptr);
    ~addGroup();

private:
    Ui::addGroup *ui;
    QMessageBox msgBox;

//sjy++
private slots:
    void on_pushButtonAddG_clicked();
signals:
    void gBackToMain();
    void gBackToLogin();//群聊双重连接

};

#endif // ADDGROUP_H
