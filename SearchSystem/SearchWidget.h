#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>

namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchWidget(QWidget *parent = nullptr);
    ~SearchWidget();

public:
    /**
     * @brief initUI 初始化UI
     */
    void initUI();

    /**
     * @brief widgetActiveChanged 窗口焦点发生变化时调用
     * @param isActive
     */
    void widgetActiveChanged(bool isActive);

    /**
     * @brief searchFiles 搜索文件
     * @param searchText
     */
    void searchFiles(const QString& searchText);

public:
    class SearchConfig *searchConfig() const;
    void setSearchConfig(class SearchConfig *searchConfig);
public:
    virtual void showEvent(QShowEvent *event) override;
    bool event(QEvent *event) override;

private:
    Ui::SearchWidget *ui;
    class SearchConfig* _searchConfig;
};

#endif // SEARCHWIDGET_H
