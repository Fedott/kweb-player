#include "googlemusicplayer.h"

GoogleMusicPlayer::GoogleMusicPlayer(QWebEngineView *browser)
{
    this->browser = browser;
}

void GoogleMusicPlayer::playPause()
{
    jsClickButton("play-pause");
}

void GoogleMusicPlayer::next()
{
    jsClickButton("forward");
}

void GoogleMusicPlayer::prev()
{
    jsClickButton("rewind");
}

void GoogleMusicPlayer::trumbsUp()
{
    jsQuerySelectorClick(".player-rating-container sj-icon-button[data-rating=5]");
}

void GoogleMusicPlayer::trumbsDown()
{
    jsQuerySelectorClick(".player-rating-container sj-icon-button[data-rating=1]");
}

void GoogleMusicPlayer::shuffle()
{
    jsClickButton("shuffle");
}

int GoogleMusicPlayer::getStatus()
{
    QString code = QString("document.querySelector('sj-icon-button[data-id=play-pause]').disabled === true");
    QString code2 = QString("document.querySelector('sj-icon-button[data-id=play-pause]').className === 'playing'");
    getPage()->runJavaScript(code, [](const QVariant &result){ qDebug() << result;});
    getPage()->runJavaScript(code2, [](const QVariant &result){ qDebug() << result;});

    return 1;
}

QWebEnginePage *GoogleMusicPlayer::getPage()
{
    return browser->page();
}

void GoogleMusicPlayer::jsQuerySelectorClick(QString selector)
{
    QString code = QString("document.querySelector('%1').click();").arg(selector);
    getPage()->runJavaScript(code);
}

void GoogleMusicPlayer::jsClickButton(QString button)
{
    QString selector = QString("sj-icon-button[data-id=%1]").arg(button);
    jsQuerySelectorClick(selector);
}

