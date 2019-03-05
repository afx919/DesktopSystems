#include "QMenuListWidget.h"

#include <QDebug>
#include <QMenu>

QMenuListWidget::QMenuListWidget(QWidget *parent)
    : QListWidget(parent)
    , rightClickMenu(new QMenu(this))
{
    //初始化右键菜单，绑定信号
    QAction* action = new QAction(tr("删除"), this);
    rightClickMenu->addAction(action);
    connect(action,&QAction::triggered,this,&QMenuListWidget::selectDeleteItem);
}

void QMenuListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);

    //如果选中了Item 则显示菜单
    if(this->itemAt(mapFromGlobal(QCursor::pos())) != nullptr) 
    {
        rightClickMenu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
    }
}

void QMenuListWidget::deleteItem(bool checked)
{
    Q_UNUSED(checked)
    for(auto item : selectedItems())
    {
        takeItem(row(item));
    }
}
