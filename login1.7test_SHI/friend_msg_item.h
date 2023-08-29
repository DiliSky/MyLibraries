#ifndef FRIEND_MSG_ITEM_H
#define FRIEND_MSG_ITEM_H

#include <QWidget>

namespace Ui {
class friend_msg_item;
}

class friend_msg_item : public QWidget
{
    Q_OBJECT

public:
    explicit friend_msg_item(QWidget *parent = nullptr);
        friend_msg_item(int i,QString id,QString username);
    ~friend_msg_item();

private:
    Ui::friend_msg_item *ui;
};

#endif // FRIEND_MSG_ITEM_H
