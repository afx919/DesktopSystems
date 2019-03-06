#include "WallpaperSystem.h"

#include <QTabWidget>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QVideoWidget>
#include <QDebug>
#include <QMessageBox>

#include "Helper/DesktopHelper.h"
#include "WallpaperConfig.h"
#include "WallpaperWidget.h"


WallpaperSystem::WallpaperSystem(QObject *parent) : QObject(parent)
  , _mediaPlayer(new QMediaPlayer(this))
  , _videoWidget(new QVideoWidget())

  , _wallpaperConfig(new WallpaperConfig(this))
  , _wallpaperWidget(nullptr)
{
    _videoWidget->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);//无边框Dialog(不为Dialog无法显示在最前面)
    _videoWidget->setAutoFillBackground(true);//全屏
    _videoWidget->setAspectRatioMode(Qt::KeepAspectRatioByExpanding);//设置窗口自适应
    _videoWidget->showFullScreen();

    //设置media输出
    _mediaPlayer->setPlaylist(_wallpaperConfig->mediaPlayList());
    _mediaPlayer->setVideoOutput(_videoWidget);

    //绑定播放状态
    connect(_mediaPlayer,&QMediaPlayer::stateChanged,_wallpaperConfig,&WallpaperConfig::playerStateChanged);

    //绑定volume
    connect(_wallpaperConfig,&WallpaperConfig::volumeChanged,_mediaPlayer,&QMediaPlayer::setVolume);

    //绑定mute
    connect(_wallpaperConfig,&WallpaperConfig::isMuteChanged,_mediaPlayer,&QMediaPlayer::setMuted);

    //绑定position
    connect(_mediaPlayer,&QMediaPlayer::positionChanged,[&](auto position)
    {
        if(!position && !_mediaPlayer->duration())
            return;//第一次调用到该信号的时候position和duration都为0会导致bug闪退
        _wallpaperConfig->setCurrentPlayPosition(position);
        if(position >= _mediaPlayer->duration())
        {
            _wallpaperConfig->mediaPlayList()->next();
        }
    });

    qDebug()<<"WallpaperSystem:创建播放窗口完成";
}

void WallpaperSystem::playPausewallpaper()
{
    if(!isEnabled)
        return ;
    Q_ASSERT(_mediaPlayer);
    if(_mediaPlayer->state() == QMediaPlayer::State::PlayingState)
    {
        _mediaPlayer->pause();
    }
    else
    {
        playWallpaper();
    }
}

void WallpaperSystem::playWallpaper()
{
    if(!isEnabled)
        return ;
    _mediaPlayer->play();
}

void WallpaperSystem::pauseWallpaper()
{
    if(!isEnabled)
        return ;
    _mediaPlayer->pause();
}

void WallpaperSystem::playNextWallpaper()
{
    if(!isEnabled)
        return ;
    Q_ASSERT(_wallpaperConfig);

    _wallpaperConfig->mediaPlayList()->next();
}

void WallpaperSystem::playPrevWallpaper()
{
    if(!isEnabled)
        return ;
    Q_ASSERT(_wallpaperConfig);

    _wallpaperConfig->mediaPlayList()->previous();
}

void WallpaperSystem::playFastForward()
{
    if(!isEnabled)
        return ;

    Q_ASSERT(_mediaPlayer);
    qint64 newPos = _mediaPlayer->position() + (5 * 1000);
    _mediaPlayer->setPosition(newPos >= _mediaPlayer->duration() ? _mediaPlayer->duration() : newPos);
}

void WallpaperSystem::playFastBackward()
{
    if(!isEnabled)
        return ;

    Q_ASSERT(_mediaPlayer);
    qint64 newPos = _mediaPlayer->position() - (5 * 1000);
    _mediaPlayer->setPosition(newPos < 0 ? 0 : newPos);
}

void WallpaperSystem::playMedia(const QString &filePath)
{
    Q_ASSERT(_mediaPlayer);
    Q_ASSERT(_wallpaperConfig);

    for(int i = 0; i < _wallpaperConfig->mediaPlayList()->mediaCount(); i++)
    {
        auto media = _wallpaperConfig->mediaPlayList()->media(i);
        if(media.canonicalUrl().toString(QUrl::PreferLocalFile) == filePath)
        {
            //如果当前播放的是目标壁纸，这不重新播放
            if(_wallpaperConfig->mediaPlayList()->media(_wallpaperConfig->currentPlayIndex()).canonicalUrl().toString(QUrl::PreferLocalFile) == filePath)
                return ;

            _wallpaperConfig->mediaPlayList()->setCurrentIndex(i);
            playWallpaper();
            qDebug()<<"WallpaperSystem"<<"直接播放" <<filePath;
            break;
        }
    }
}

void WallpaperSystem::initSystem()
{
    //初始化桌面窗口
    if(!DesktopHelper::getInstance()->getDesktopIconWnd())
    {
        QMessageBox::critical(_wallpaperWidget,tr("桌面窗口初始化失败!"),tr("桌面窗口初始化失败!"));
        _wallpaperConfig->setIsEnabled(false);
    }

    DesktopHelper::getInstance()->setDisktopParent((HWND)(_videoWidget->winId()));
    qDebug()<<"WallpaperSystem:初始化桌面壁纸窗口完成";
}

void WallpaperSystem::initSettingWidget(QTabWidget *parent)
{
    _wallpaperWidget = new WallpaperWidget(_wallpaperConfig,parent);
    parent->addTab(_wallpaperWidget, tr("壁纸"));

    //连接Widget信号
    connect(_wallpaperWidget,&WallpaperWidget::playPause,this,&WallpaperSystem::playPausewallpaper);
    connect(_wallpaperWidget,&WallpaperWidget::playNext,this,&WallpaperSystem::playNextWallpaper);
    connect(_wallpaperWidget,&WallpaperWidget::playPrev,this,&WallpaperSystem::playPrevWallpaper);
    connect(_wallpaperWidget,&WallpaperWidget::playFastForward,this,&WallpaperSystem::playFastForward);
    connect(_wallpaperWidget,&WallpaperWidget::playFastBackward,this,&WallpaperSystem::playFastBackward);
    connect(_wallpaperWidget,&WallpaperWidget::playMedia,this,&WallpaperSystem::playMedia);

    //自动播放
    playPausewallpaper();
    //设置为上次的播放位置
    _mediaPlayer->setPosition(_wallpaperConfig->currentPlayPosition());
}

void WallpaperSystem::initTrayMenu(QMenu *trayMenu)
{

}

void WallpaperSystem::exitSystem()
{
    _videoWidget->close();
    _videoWidget->deleteLater();
}

void WallpaperSystem::loadConfig(QSettings *settings)
{
    _wallpaperConfig->loadSettings(settings);

    //连接isEnabled信号
    connect(_wallpaperConfig,&WallpaperConfig::isEnabledChanged,this,&WallpaperSystem::setIsEnabled);

    qDebug()<<"WallpaperConfig 加载完毕!";
}

void WallpaperSystem::saveConfig(QSettings *settings)
{
    _wallpaperConfig->saveSettings(settings);

    qDebug()<<"WallpaperConfig 保存完毕!";
}

void WallpaperSystem::setIsEnabled(const bool &value)
{
    ISystem::setIsEnabled(value);

    Q_ASSERT(_mediaPlayer);
    if(value)
    {
        _videoWidget->showFullScreen();
        _mediaPlayer->play();
        _videoWidget->show();
    }
    else
    {
        _videoWidget->hide();
        _videoWidget->showNormal();
        _mediaPlayer->pause();
    }
}
