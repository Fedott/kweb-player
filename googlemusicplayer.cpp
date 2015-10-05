#include "googlemusicplayer.h"

GoogleMusicPlayer::GoogleMusicPlayer(QWebEngineView *browser)
{
    this->browser = browser;
    this->status = PlayerStatus();
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

void GoogleMusicPlayer::updateStatus()
{
    QString disabledCode = QString("document.querySelector('sj-icon-button[data-id=play-pause]').disabled === true");
    QString playingCode = QString("document.querySelector('sj-icon-button[data-id=play-pause]').className === 'playing'");

    getPage()->runJavaScript(disabledCode, [this](const QVariant &result){
        qDebug() << result;
        this->status.disabled = result.toBool();
    });
    getPage()->runJavaScript(playingCode, [this](const QVariant &result){
        qDebug() << result;
        this->status.playing = result.toBool();
    });
}

PlayerStatus* GoogleMusicPlayer::getStatus()
{
    return &status;
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


int PlayerStatus::getState()
{
    if (disabled) {
        return 0;
    } else if (playing) {
        return 1;
    } else {
        return 2;
    }
}
