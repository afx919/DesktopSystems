#include "SearchConfig.h"

#include <QSettings>

SearchConfig::SearchConfig(QObject *parent) : QObject(parent)
  , _isEnabled(true)
  , _searchProgram(true)
  , _searchDocument(true)
  , _searchVideo(true)
  , _searchSound(true)
  , _searchImage(true)
  , _customProgramSuffix("")
  , _customDocumentSuffix("")
  , _customVideoSuffix("")
  , _customSoundSuffix("")
  , _customImageSuffix("")
{

}

QString SearchConfig::customImageSuffix() const
{
    return _customImageSuffix;
}

void SearchConfig::setCustomImageSuffix(const QString &customImageSuffix)
{
    _customImageSuffix = customImageSuffix;
    emit customImageSuffixChanged(customImageSuffix);
}

QString SearchConfig::customSoundSuffix() const
{
    return _customSoundSuffix;
}

void SearchConfig::setCustomSoundSuffix(const QString &customSoundSuffix)
{
    _customSoundSuffix = customSoundSuffix;
    emit customSoundSuffixChanged(customSoundSuffix);
}

QString SearchConfig::customVideoSuffix() const
{
    return _customVideoSuffix;
}

void SearchConfig::setCustomVideoSuffix(const QString &customVideoSuffix)
{
    _customVideoSuffix = customVideoSuffix;
    emit customVideoSuffixChanged(customVideoSuffix);
}

QString SearchConfig::customDocumentSuffix() const
{
    return _customDocumentSuffix;
}

void SearchConfig::setCustomDocumentSuffix(const QString &customDocumentSuffix)
{
    _customDocumentSuffix = customDocumentSuffix;
    emit customDocumentSuffixChanged(customDocumentSuffix);
}

QString SearchConfig::customProgramSuffix() const
{
    return _customProgramSuffix;
}

void SearchConfig::setCustomProgramSuffix(const QString &customProgramSuffix)
{
    _customProgramSuffix = customProgramSuffix;
    emit customProgramSuffixChanged(customProgramSuffix);
}

bool SearchConfig::isEnabled() const
{
    return _isEnabled;
}

void SearchConfig::setIsEnabled(bool isEnabled)
{
    _isEnabled = isEnabled;
    emit isEnabledChanged(isEnabled);
}

void SearchConfig::loadSettings(QSettings *settings)
{
    LOAD_PROPERTYS(settings);
}

void SearchConfig::saveSettings(QSettings *settings)
{
    SAVE_PROPERTYS(settings);
}
