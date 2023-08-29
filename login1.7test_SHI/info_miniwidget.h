#ifndef INFO_MINIWIDGET_H
#define INFO_MINIWIDGET_H

#include <QWidget>

namespace Ui {
class Info_MiniWidget;
}

class Info_MiniWidget : public QWidget
{
    Q_OBJECT

public:
    explicit Info_MiniWidget(QWidget *parent = nullptr);
    ~Info_MiniWidget();

    void setAvatar(QString Pro_Path);
    void setID(QString ID);
    void setUserName(QString Name);
private:
    Ui::Info_MiniWidget *ui;
    QString Pro_Path;
};

#endif // INFO_MINIWIDGET_H
