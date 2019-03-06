#ifndef WALLPAPERSYSTEM_H
#define WALLPAPERSYSTEM_H

#include <QObject>

#include "../Interface/ISystem.h"

class WallpaperSystem : public QObject, public ISystem
{
    Q_OBJECT
public:
    explicit Q_INVOKABLE WallpaperSystem(QObject *parent = nullptr);

signals:

public slots:
    /**
     * @brief playPausewallpaper 播放/暂停
     */
    void playPausewallpaper();

    /**
     * @brief playWallpaper 播放
     */
    void playWallpaper();

    /**
     * @brief pauseWallpaper 暂停
     */
    void pauseWallpaper();

    /**
     * @brief playNextWallpaper 下一曲
     */
    void playNextWallpaper();

    /**
     * @brief playPrevWallpaper 上一曲
     */
    void playPrevWallpaper();

    /**
     * @brief playFastForward 快进
     */
    void playFastForward();

    /**
     * @brief playFastBackward 快退
     */
    void playFastBackward();

    /**
     * @brief playMedia 播放指定媒体
     * @param filePath 媒体路径
     */
    void playMedia(const QString& filePath);

private:
    /**
     * @brief _mediaPlayer 当前的媒体播放对象
     */
    class QMediaPlayer* _mediaPlayer;

    /**
     * @brief _videoWidget 当前视频输出窗口
     */
    class QVideoWidget* _videoWidget;
private:
    class WallpaperConfig* _wallpaperConfig;
    class WallpaperWidget* _wallpaperWidget;

    // ISystem interface
public:
    void initSystem() override;
    void initSettingWidget(QTabWidget *parent) override;
    void exitSystem() override;
    void loadConfig(class QSettings *settings) override;
    void saveConfig(class QSettings *settings) override;

    virtual void setIsEnabled(const bool &value) override;
};

#endif // WALLPAPERSYSTEM_H
