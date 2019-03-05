#include "WallpaperConfig.h"

#include <QSettings>
#include <QMediaPlaylist>
#include <QFile>

const char* WallpaperConfig::_mediaPlayListPath("WallpaperPlayList.m3u");
const QString WallpaperConfig::_configScope("WallpaperSystem/");

//#define CONFIG_KEY(NAME) _configScope + NAME


WallpaperConfig::WallpaperConfig(QObject *parent) : QObject(parent)
  , IConfig()
  , _isEnabled(true)
  , _mediaPlayList(new QMediaPlaylist(this))
  , _volume(50)
  , _isMute(false)
{

}

bool WallpaperConfig::isEnabled() const
{
    return _isEnabled;
}

void WallpaperConfig::setIsEnabled(const bool &isEnabled)
{
    _isEnabled = isEnabled;
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
    emit isMuteChanged(isMute);
}

int WallpaperConfig::playMode() const
{
    return _mediaPlayList->playbackMode();
}

void WallpaperConfig::setPlayMode(int playMode)
{
    _mediaPlayList->setPlaybackMode(static_cast<QMediaPlaylist::PlaybackMode>(playMode));
    emit playModeChanged(playMode);
}

void WallpaperConfig::loadSettings(class QSettings *settings)
{
    //加载播放列表
    QFile file(_mediaPlayListPath);
    if(file.open(QIODevice::ReadOnly))
    {
        _mediaPlayList->load(&file,"m3u");
    }

    //加载配置
    QVariant retData;

    retData = settings->value(CONFIG_KEY("isEnabled"),true);
    if(retData.canConvert<bool>())
    {
        setIsEnabled(retData.toBool());
    }

    retData = settings->value(CONFIG_KEY("volume"),50);
    if(retData.canConvert<int>())
    {
        setVolume(retData.toInt());
    }

    retData = settings->value(CONFIG_KEY("isMute"),false);
    if(retData.canConvert<bool>())
    {
        setIsMute(retData.toBool());
    }

    retData = settings->value(CONFIG_KEY("playMode"),static_cast<int>(QMediaPlaylist::PlaybackMode::Loop));
    if(retData.canConvert<int>())
    {
        _mediaPlayList->setPlaybackMode(static_cast<QMediaPlaylist::PlaybackMode>(retData.toInt()));
    }

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
    /*
    settings->setValue(CONFIG_KEY("isEnabled"),isEnabled());
    settings->setValue(CONFIG_KEY("volume"),volume());
    settings->setValue(CONFIG_KEY("isMute"),isMute());
    settings->setValue(CONFIG_KEY("playMode"),static_cast<int>(_mediaPlayList->playbackMode()));
    */

    SAVE_CONFIG(settings,isEnabled);
    SAVE_CONFIG(settings,volume);
    SAVE_CONFIG(settings,isMute);
    SAVE_CONFIG(settings,playMode);
}
