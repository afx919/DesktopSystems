#ifndef WALLPAPERWIDGET_H
#define WALLPAPERWIDGET_H

#include <QWidget>


namespace Ui {
class WallpaperWidget;
}

class WallpaperWidget : public QWidget
{
    Q_OBJECT
    
public:
    explicit WallpaperWidget(class WallpaperConfig* wallpaperConfig,QWidget *parent = nullptr);
    ~WallpaperWidget();
    
private:
    void initUI();
    
public:
    void refreshFileList();

public:
signals:
    void playPause();
    void playPrev();
    void playNext();
    void playFastForward();
    void playFastBackward();
    
private slots:
    void cleanFileDirectorys();
    void removeFile();
    void addFile();
    
private:
    Ui::WallpaperWidget *ui;
    
    /**
     * @brief _wallpaperConfig 视频壁纸系统配置
     */
    class WallpaperConfig* _wallpaperConfig;

};

#endif // WALLPAPERWIDGET_H
