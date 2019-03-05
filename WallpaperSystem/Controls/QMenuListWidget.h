#ifndef QMENULISTWIDGET_H
#define QMENULISTWIDGET_H

#include <QListWidget>

class QMenuListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit QMenuListWidget(QWidget *parent = nullptr);
    
protected:
    virtual void contextMenuEvent( QContextMenuEvent * event ) override;
    
signals:
    void selectDeleteItem();
    
public slots:
    void deleteItem(bool checked = false);
private:
    class QMenu* rightClickMenu;
};

#endif // QMENULISTWIDGET_H
