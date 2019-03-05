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
    void playItem(const QString& itemText);
    void addMediaFile();
    
public slots:
    void deleteItem(bool checked = false);
private:
    class QMenu* _rightClickHasItemMenu;
    class QMenu* _rightClickNoItemMenu;
};

#endif // QMENULISTWIDGET_H
