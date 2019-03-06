#ifndef WALLPAPERCONFIG_H
#define WALLPAPERCONFIG_H

#include <QObject>

#include "../Interface/IConfig.h"

class WallpaperConfig : public QObject, public IConfig
{
    Q_OBJECT
public:
    explicit WallpaperConfig(QObject *parent = nullptr);

public:
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled NOTIFY isEnabledChanged)
    Q_PROPERTY(class QMediaPlaylist* mediaPlayList READ mediaPlayList)
    Q_PROPERTY(int volume READ volume WRITE setVolume NOTIFY volumeChanged)
    Q_PROPERTY(bool isMute READ isMute WRITE setIsMute NOTIFY isMuteChanged)
    Q_PROPERTY(int playMode READ playMode WRITE setPlayMode NOTIFY playModeChanged)
    Q_PROPERTY(int currentPlayIndex READ currentPlayIndex WRITE setCurrentPlayIndex NOTIFY currentPlayIndexChanged)
    Q_PROPERTY(qint64 currentPlayPosition READ currentPlayPosition WRITE setCurrentPlayPosition NOTIFY currentPlayPositionChanged)

public slots:
    bool isEnabled() const;
    void setIsEnabled(const bool& isEnabled);

    class QMediaPlaylist* mediaPlayList() const;

    int volume() const;
    void setVolume(int volume);

    bool isMute() const;
    void setIsMute(bool isMute);

    int playMode() const;
    void setPlayMode(int playMode);

    int currentPlayIndex() const;
    void setCurrentPlayIndex(int currentPlayIndex);

    qint64 currentPlayPosition() const;
    void setCurrentPlayPosition(const qint64 &currentPlayPosition);


signals:
    void isEnabledChanged(const bool& isEnabled);
    void volumeChanged(int volume);
    void isMuteChanged(bool isMute);
    void playModeChanged(int playMode);
    void currentPlayIndexChanged(int currentPlayIndex);
    void currentPlayPositionChanged(const qint64 &currentPlayPosition);

signals:
    void playerStateChanged(int state);

private:
    /**
     * @brief _isEnabled 是否启用
     */
    bool _isEnabled;

    /**
     * @brief _mediaPlayList 播放列表
     */
    class QMediaPlaylist* _mediaPlayList;

    /**
     * @brief _volume 音量
     */
    int _volume;

    /**
     * @brief _isMute 是否静音
     */
    bool _isMute;

    /**
     * @brief _currentPlayIndex 当前播放的索引
     */
    int _currentPlayIndex;

    /**
     * @brief _currentPlayPosition 当前媒体的播放进度
     */
    qint64 _currentPlayPosition;


private:
    /**
     * @brief _mediaPlayListPath 播放列表文件位置
     */
    static const char* _mediaPlayListPath;

    class QSettings* _settings;

public slots:

    // IConfig interface
public:
    void loadSettings(class QSettings *settings);
    void saveSettings(class QSettings *settings);
};

#endif // WALLPAPERCONFIG_H
