#ifndef SEARCHSETTINGWIDGET_H
#define SEARCHSETTINGWIDGET_H

#include <QWidget>

namespace Ui {
class SearchSettingWidget;
}

class SearchSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SearchSettingWidget(class SearchConfig* searchConfig,QWidget *parent = nullptr);
    ~SearchSettingWidget();

public:
    /**
     * @brief initUI 初始化UI
     */
    void initUI();

private:
    Ui::SearchSettingWidget *ui;

    class SearchConfig* _searchConfig;
};

#endif // SEARCHSETTINGWIDGET_H
