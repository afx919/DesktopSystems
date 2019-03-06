#include "SearchSettingWidget.h"
#include "ui_SearchSettingWidget.h"

#include <QInputDialog>
#include <QDebug>

#include "SearchConfig.h"

#define CONNECT_UI_TOOLBUTTON_INPUT_DIALOG(OBJECT_NAME,DIALOG_TITLE,DIALOG_TEXT,DIALOG_CONTEXT_PROPERTY,RESULT_PROPERTY) \
connect(ui->OBJECT_NAME,&QToolButton::clicked,[&]() \
{ \
    bool isOk(false); \
    QString result = QInputDialog::getText(this,tr(DIALOG_TITLE),tr(DIALOG_TEXT),QLineEdit::Normal,_searchConfig->DIALOG_CONTEXT_PROPERTY(),&isOk); \
    if(isOk) \
    { \
        _searchConfig->RESULT_PROPERTY(result); \
    } \
});

SearchSettingWidget::SearchSettingWidget(SearchConfig *searchConfig, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SearchSettingWidget)
  , _searchConfig(searchConfig)
{
    ui->setupUi(this);

    initUI();
}

SearchSettingWidget::~SearchSettingWidget()
{
    delete ui;
}

void SearchSettingWidget::initUI()
{
    //连接config变化到ui
    connect(_searchConfig,&SearchConfig::isEnabledChanged,ui->on_radio,&QRadioButton::setChecked);
    connect(_searchConfig,&SearchConfig::customProgramSuffixChanged,ui->program_label,&QLabel::setText);
    connect(_searchConfig,&SearchConfig::customDocumentSuffixChanged,ui->document_label,&QLabel::setText);
    connect(_searchConfig,&SearchConfig::customVideoSuffixChanged,ui->video_label,&QLabel::setText);
    connect(_searchConfig,&SearchConfig::customSoundSuffixChanged,ui->sound_label,&QLabel::setText);
    connect(_searchConfig,&SearchConfig::customImageSuffixChanged,ui->image_label,&QLabel::setText);

    //连接ui变化到config
    connect(ui->on_radio,&QRadioButton::toggled,_searchConfig,&SearchConfig::setIsEnabled);

    //初始化config到UI
    _searchConfig->setIsEnabled(_searchConfig->isEnabled());
    _searchConfig->setCustomProgramSuffix(_searchConfig->customProgramSuffix());
    _searchConfig->setCustomDocumentSuffix(_searchConfig->customDocumentSuffix());
    _searchConfig->setCustomVideoSuffix(_searchConfig->customVideoSuffix());
    _searchConfig->setCustomSoundSuffix(_searchConfig->customSoundSuffix());
    _searchConfig->setCustomImageSuffix(_searchConfig->customImageSuffix());

    //绑定按钮事件
    CONNECT_UI_TOOLBUTTON_INPUT_DIALOG(program_button,"修改自定义程序后缀","修改自定义程序后缀,使用符号;来隔开。比如:txt;exe;png;",
                                       customProgramSuffix,setCustomProgramSuffix);

    CONNECT_UI_TOOLBUTTON_INPUT_DIALOG(document_button,"修改自定义文档后缀","修改自定义文档后缀,使用符号;来隔开。比如:txt;exe;png;",
                                       customDocumentSuffix,setCustomDocumentSuffix);

    CONNECT_UI_TOOLBUTTON_INPUT_DIALOG(video_button,"修改自定义视频后缀","修改自定义视频后缀,使用符号;来隔开。比如:txt;exe;png;",
                                       customVideoSuffix,setCustomVideoSuffix);

    CONNECT_UI_TOOLBUTTON_INPUT_DIALOG(sound_button,"修改自定义音频后缀","修改自定义音频后缀,使用符号;来隔开。比如:txt;exe;png;",
                                       customSoundSuffix,setCustomSoundSuffix);

    CONNECT_UI_TOOLBUTTON_INPUT_DIALOG(image_button,"修改自定义图片后缀","修改自定义图片后缀,使用符号;来隔开。比如:txt;exe;png;",
                                       customImageSuffix,setCustomImageSuffix);
}
