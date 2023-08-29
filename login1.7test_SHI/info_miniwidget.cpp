#include "info_miniwidget.h"
#include "ui_info_miniwidget.h"

Info_MiniWidget::Info_MiniWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Info_MiniWidget)
{
    ui->setupUi(this);
}

Info_MiniWidget::~Info_MiniWidget()
{
    delete ui;
}
//API
void Info_MiniWidget::setAvatar(QString Path)
{
    Pro_Path = Path;
    ui->Avatar_Label->setPixmap(QPixmap(Pro_Path).scaled(100,100,Qt::KeepAspectRatio));
}

void Info_MiniWidget::setID(QString ID)
{
    ui->ID_Label->setText(ID);
}

void Info_MiniWidget::setUserName(QString Name)
{
    ui->Username_Label->setText(Name);
}

