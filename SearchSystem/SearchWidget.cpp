#include "SearchWidget.h"
#include "ui_SearchWidget.h"

#include <QDesktopWidget>
#include <QDebug>

#include "SearchConfig.h"

SearchWidget::SearchWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchWidget)
  , _searchConfig(nullptr)
{
    ui->setupUi(this);

    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint | Qt::SubWindow);

    /*
     *
     * void (const QString &);
    void textEdited(const QString &);
     * */
    //绑定输入框输入信号
    connect(ui->search_lineedit,&QLineEdit::textChanged,this,&SearchWidget::searchFiles);
}

SearchWidget::~SearchWidget()
{
    delete ui;
}

void SearchWidget::initUI()
{
    if(!_searchConfig)
        return ;

    connect(_searchConfig,&SearchConfig::isEnabledChanged,[&](auto isEnable)
    {
        if(!isEnable)
            this->hide();
    });
}

void SearchWidget::widgetActiveChanged(bool isActive)
{
    if(isActive)
    {
        ui->search_lineedit->setFocus();
    }
    else
    {
        hide();
    }
}

void SearchWidget::searchFiles(const QString &searchText)
{
    qDebug()<<"SEARCH"<<_searchConfig;
    if(_searchConfig && _searchConfig->isEnabled())
    {
        qDebug()<<searchText;
    }
}

void SearchWidget::showEvent(QShowEvent *event)
{
    QWidget::showEvent(event);

    static int width = 500;
    static int height = 100;
    static QRect rect;

    rect.setX((QApplication::desktop()->width() - width) / 2);
    rect.setY(100);
    rect.setWidth(width);
    rect.setHeight(height);

    setGeometry(rect);
}

bool SearchWidget::event(QEvent *event)
{

    if(event->type() == QEvent::ActivationChange)
    {
        widgetActiveChanged(isActiveWindow());
    }

    return QWidget::event(event);
}

SearchConfig *SearchWidget::searchConfig() const
{
    return _searchConfig;
}

void SearchWidget::setSearchConfig(SearchConfig *searchConfig)
{
    _searchConfig = searchConfig;
    initUI();
}
