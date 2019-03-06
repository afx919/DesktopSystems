#ifndef SEARCHCONFIG_H
#define SEARCHCONFIG_H

#include <QObject>

#include "../Interface/IConfig.h"

class SearchConfig : public QObject, public IConfig
{
    Q_OBJECT
public:
    explicit SearchConfig(QObject *parent = nullptr);

public:
    Q_PROPERTY(bool isEnabled READ isEnabled WRITE setIsEnabled NOTIFY isEnabledChanged)
    Q_PROPERTY(QString customProgramSuffix READ customProgramSuffix WRITE setCustomProgramSuffix NOTIFY customProgramSuffixChanged)
    Q_PROPERTY(QString customDocumentSuffix READ customDocumentSuffix WRITE setCustomDocumentSuffix NOTIFY customDocumentSuffixChanged)
    Q_PROPERTY(QString customVideoSuffix READ customVideoSuffix WRITE setCustomVideoSuffix NOTIFY customVideoSuffixChanged)
    Q_PROPERTY(QString customSoundSuffix READ customSoundSuffix WRITE setCustomSoundSuffix NOTIFY customSoundSuffixChanged)
    Q_PROPERTY(QString customImageSuffix READ customImageSuffix WRITE setCustomImageSuffix NOTIFY customImageSuffixChanged)

public:
    bool isEnabled() const;
    void setIsEnabled(bool isEnabled);

    QString customProgramSuffix() const;
    void setCustomProgramSuffix(const QString &customProgramSuffix);

    QString customDocumentSuffix() const;
    void setCustomDocumentSuffix(const QString &customDocumentSuffix);

    QString customVideoSuffix() const;
    void setCustomVideoSuffix(const QString &customVideoSuffix);

    QString customSoundSuffix() const;
    void setCustomSoundSuffix(const QString &customSoundSuffix);

    QString customImageSuffix() const;
    void setCustomImageSuffix(const QString &customImageSuffix);
signals:
    void isEnabledChanged(bool isEnabled);
    void customProgramSuffixChanged(const QString &customProgramSuffix);
    void customDocumentSuffixChanged(const QString &customDocumentSuffix);
    void customVideoSuffixChanged(const QString &customVideoSuffix);
    void customSoundSuffixChanged(const QString &customSoundSuffix);
    void customImageSuffixChanged(const QString &customImageSuffix);

private:
    /**
     * @brief _isEnabled 是否启用
     */
    bool _isEnabled;

    /**
     * @brief _searchProgram 是否搜索程序
     */
    bool _searchProgram;

    /**
     * @brief _searchDocument 是否搜索文档
     */
    bool _searchDocument;

    /**
     * @brief _searchVideo 是否搜索视频
     */
    bool _searchVideo;

    /**
     * @brief _searchSound 是否搜索音频
     */
    bool _searchSound;

    /**
     * @brief _searchImage 是否搜索图片
     */
    bool _searchImage;

    /**
     * @brief _customProgramSuffix 自定义程序后缀
     */
    QString _customProgramSuffix;

    /**
     * @brief _customDocumentSuffix 自定义文档后缀
     */
    QString _customDocumentSuffix;

    /**
     * @brief _customVideoSuffix 自定义视频后缀
     */
    QString _customVideoSuffix;

    /**
     * @brief _customSoundSuffix 自定义音频后缀
     */
    QString _customSoundSuffix;

    /**
     * @brief _customImageSuffix 自定义图片后缀
     */
    QString _customImageSuffix;
public slots:

    // IConfig interface
public:
    virtual void loadSettings(QSettings *settings) override;
    virtual void saveSettings(QSettings *settings) override;
};

#endif // SEARCHCONFIG_H
