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

