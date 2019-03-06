#include "WallpaperConfig.h"

#include <QSettings>
#include <QMediaPlaylist>
#include <QFile>

const char* WallpaperConfig::_mediaPlayListPath("WallpaperPlayList.m3u");

WallpaperConfig::WallpaperConfig(QObject *parent) : QObject(parent)
  , IConfig()
  , _isEnabled(true)
  , _mediaPlayList(new QMediaPlaylist(this))
  , _volume(50)
  , _isMute(false)
  , _currentPlayIndex(0)
  , _settings(nullptr)
{

}

bool WallpaperConfig::isEnabled() const
{
    return _isEnabled;
}

void WallpaperConfig::setIsEnabled(const bool &isEnabled)
{
    _isEnabled = isEnabled;
    SAVE_CONFIG(_settings,isEnabled);
    emit isEnabledChanged(isEnabled);
}

QMediaPlaylist *WallpaperConfig::mediaPlayList() const
{
    return _mediaPlayList;
}

int WallpaperConfig::volume() const
{
    return _volume;
}

void WallpaperConfig::setVolume(int volume)
{
    _volume = volume;
    emit volumeChanged(volume);
}

bool WallpaperConfig::isMute() const
{
    return _isMute;
}

void WallpaperConfig::setIsMute(bool isMute)
{
    _isMute = isMute;
    SAVE_CONFIG(_settings,isMute);
    emit isMuteChanged(isMute);
}

int WallpaperConfig::playMode() const
{
    return _mediaPlayList->playbackMode();
}

void WallpaperConfig::setPlayMode(int playMode)
{
    _mediaPlayList->setPlaybackMode(static_cast<QMediaPlaylist::PlaybackMode>(playMode));
    SAVE_CONFIG(_settings,playMode);
    emit playModeChanged(playMode);
}

int WallpaperConfig::currentPlayIndex() const
{
    return _currentPlayIndex;
}

void WallpaperConfig::setCurrentPlayIndex(int currentPlayIndex)
{
    _currentPlayIndex = currentPlayIndex;
    SAVE_CONFIG(_settings,currentPlayIndex);
    emit currentPlayIndexChanged(currentPlayIndex);
}

qint64 WallpaperConfig::currentPlayPosition() const
{
    return _currentPlayPosition;
}

void WallpaperConfig::setCurrentPlayPosition(const qint64 &currentPlayPosition)
{
    _currentPlayPosition = currentPlayPosition;
    emit currentPlayPositionChanged(currentPlayPosition);
}

void WallpaperConfig::loadSettings(class QSettings *settings)
{
    _settings = settings;

    //加载播放列表
    QFile file(_mediaPlayListPath);
    if(file.open(QIODevice::ReadOnly))
    {
        _mediaPlayList->load(&file,"m3u");
    }

    //加载配置
    LOAD_PROPERTYS(settings);

    _mediaPlayList->setCurrentIndex(_currentPlayIndex);
    connect(_mediaPlayList,&QMediaPlaylist::currentIndexChanged,this,&WallpaperConfig::setCurrentPlayIndex);
}

void WallpaperConfig::saveSettings(class QSettings *settings)
{
    //保存播放列表
    QFile file(_mediaPlayListPath);
    if(file.open(QIODevice::WriteOnly))
    {
        _mediaPlayList->save(&file,"m3u");
    }

    //保存配置
    SAVE_PROPERTYS(settings);
}
