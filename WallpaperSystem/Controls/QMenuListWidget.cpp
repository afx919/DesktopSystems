#include "QMenuListWidget.h"

#include <QDebug>
#include <QMenu>

QMenuListWidget::QMenuListWidget(QWidget *parent)
    : QListWidget(parent)
    , _rightClickHasItemMenu(new QMenu(this))
    , _rightClickNoItemMenu(new QMenu(this))
{
    //初始化右键菜单，绑定信号
    QAction* action = new QAction(tr("播放"), this);
    _rightClickHasItemMenu->addAction(action);
    connect(action,&QAction::triggered,this,[&]()
    {
        if(selectedItems().length() > 0)
            emit playItem(selectedItems()[0]->text());
    });

    action = new QAction(tr("删除"), this);
    _rightClickHasItemMenu->addAction(action);
    connect(action,&QAction::triggered,this,&QMenuListWidget::selectDeleteItem);



    action = new QAction(tr("添加文件"), this);
    _rightClickNoItemMenu->addAction(action);
    connect(action,&QAction::triggered,this,&QMenuListWidget::addMediaFile);

    //绑定Item的双击事件,双击播放选择的Item
    connect(this,&QListWidget::itemDoubleClicked,[&](auto item)
    {
        emit playItem(item->text());
    });
}

void QMenuListWidget::contextMenuEvent(QContextMenuEvent *event)
{
    Q_UNUSED(event);

    //如果选中了Item 则显示菜单有Item选项的菜单
    if(this->itemAt(mapFromGlobal(QCursor::pos())) != nullptr) 
    {
        _rightClickHasItemMenu->exec(QCursor::pos());
    }
    else
    {
        _rightClickNoItemMenu->exec(QCursor::pos());
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
