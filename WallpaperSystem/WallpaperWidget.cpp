#include "WallpaperWidget.h"
#include "ui_WallpaperWidget.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QDebug>
#include <QFileInfo>
#include <QSettings>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include <QMediaContent>

#include "WallpaperConfig.h"

WallpaperWidget::WallpaperWidget(WallpaperConfig *wallpaperConfig, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WallpaperWidget)
  , _wallpaperConfig(wallpaperConfig)
{
    ui->setupUi(this);

    initUI();
}

WallpaperWidget::~WallpaperWidget()
{
    delete ui;
}

void WallpaperWidget::initUI()
{
    //初始化config到ui
    ui->on_radio->setChecked(_wallpaperConfig->isEnabled());

    switch(_wallpaperConfig->playMode())
    {
    case 1:
        ui->once_radio->setChecked(true);
        break;
    case 3:
        ui->loop_radio->setChecked(true);
        break;
    case 4:
        ui->random_radio->setChecked(true);
        break;
    default:
        _wallpaperConfig->setPlayMode(3);
        ui->loop_radio->setChecked(true);
    }

    ui->volume_slider->setValue(_wallpaperConfig->volume());
    ui->mute_checkbox->setChecked(_wallpaperConfig->isMute());

    refreshFileList();
    
    
    //绑定ui变化到config
    connect(ui->on_radio,&QAbstractButton::toggled,_wallpaperConfig,&WallpaperConfig::setIsEnabled);

    connect(ui->once_radio,&QAbstractButton::clicked,[&]()
    {
        _wallpaperConfig->setPlayMode(1);
    });

    connect(ui->loop_radio,&QAbstractButton::clicked,[&]()
    {
        _wallpaperConfig->setPlayMode(3);
    });

    connect(ui->random_radio,&QAbstractButton::clicked,[&]()
    {
        _wallpaperConfig->setPlayMode(4);
    });

    connect(ui->listWidget,&QMenuListWidget::selectDeleteItem,this,&WallpaperWidget::removeFile);

    connect(ui->volume_slider,&QAbstractSlider::valueChanged,_wallpaperConfig,&WallpaperConfig::setVolume);

    connect(ui->mute_checkbox,&QAbstractButton::clicked,_wallpaperConfig,&WallpaperConfig::setIsMute);

    connect(_wallpaperConfig,&WallpaperConfig::playerStateChanged,[&](auto state)
    {
        if(static_cast<QMediaPlayer::State>(state) == QMediaPlayer::State::PlayingState)
        {
            ui->play_pause_button->setText(tr("暂停"));
        }
        else
        {
            ui->play_pause_button->setText(tr("播放"));
        }
    });

    //连接播放，上一曲下一曲，快进快退
    connect(ui->prev_button,&QAbstractButton::clicked,this,&WallpaperWidget::playPrev);
    connect(ui->play_pause_button,&QAbstractButton::clicked,this,&WallpaperWidget::playPause);
    connect(ui->next_button,&QAbstractButton::clicked,this,&WallpaperWidget::playNext);
    connect(ui->fast_forward_button,&QAbstractButton::clicked,this,&WallpaperWidget::playFastForward);
    connect(ui->fast_backward_button,&QAbstractButton::clicked,this,&WallpaperWidget::playFastBackward);

    //连接添加文件，删除文件，清空文件
    connect(ui->clean_file_button,&QPushButton::clicked,this,&WallpaperWidget::cleanFileDirectorys);
    connect(ui->remove_file_button,&QPushButton::clicked,this,&WallpaperWidget::removeFile);
    connect(ui->add_file_button,&QPushButton::clicked,this,&WallpaperWidget::addFile);

}

void WallpaperWidget::refreshFileList()
{
    ui->listWidget->clear();
    //初始化播放列表
    for(int i = 0; i < _wallpaperConfig->mediaPlayList()->mediaCount(); i++)
    {
        QUrl url = _wallpaperConfig->mediaPlayList()->media(i).canonicalUrl();

        ui->listWidget->addItem(new QListWidgetItem(url.toString(QUrl::PreferLocalFile),ui->listWidget));
    }
}

void WallpaperWidget::cleanFileDirectorys()
{
    if(ui->listWidget->count())
    {
        if(QMessageBox::warning(this,tr("确认清空文件？"),tr("即将清空文件"),QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes)
        {
            _wallpaperConfig->mediaPlayList()->clear();
            refreshFileList();
        }
    }
}

void WallpaperWidget::removeFile()
{
    for(auto item : ui->listWidget->selectedItems())
    {
        for(int i = 0; i < _wallpaperConfig->mediaPlayList()->mediaCount(); i++)
        {
            QUrl url = _wallpaperConfig->mediaPlayList()->media(i).canonicalUrl();
            if(url.toString(QUrl::PreferLocalFile) == item->text())
            {
                _wallpaperConfig->mediaPlayList()->removeMedia(i);
                qDebug()<<"删除文件:" << item->text();
                break;
            }
        }
    }

    ui->listWidget->deleteItem();
    //refreshFileList();
}

void WallpaperWidget::addFile()
{
    QFileDialog fileDialog(this,tr("选择媒体文件"),tr("/"),"All Media(*.gif *.mp4 *.avi);;GIF(*.gif);;Video(*.mp4 *.avi)");
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setFileMode(QFileDialog::ExistingFiles);
    fileDialog.setViewMode(QFileDialog::Detail);
    fileDialog.setFilter(QDir::Files);
    
    if(fileDialog.exec() == QDialog::Accepted)
    {
        for(auto file : fileDialog.selectedFiles())
        {
            _wallpaperConfig->mediaPlayList()->addMedia(QUrl::fromLocalFile(file));
            ui->listWidget->addItem(new QListWidgetItem(file,ui->listWidget));
            qDebug()<<"添加文件:" << file;
        }
        //refreshFileList();
    }
}
