function GPMgetPlayerStatus() {
    var status = {
        disabled: false,
        playing: false,
        artLocation: null,
        songTitle: '',
        songArtist: '',
        songAlbum: '',
        progressNow: 0,
        progressMin: 0,
        progressMax: 0,
        canNext: false,
        canPrev: false,
        volume: 100,
    };

    var playPauseButton = document.querySelector('paper-icon-button[data-id=play-pause]');
    var nextButton = document.querySelector('paper-icon-button[data-id=forward]');
    var prevButton = document.querySelector('paper-icon-button[data-id=rewind]');
    var volumeBar = document.querySelector('#material-vslider');
    var progressBar = document.querySelector('#material-player-progress');
    var artElement = document.getElementById('playerBarArt');
    var albumElement = document.querySelector("#playerSongInfo .player-album");

    try {
        var titleElement = document.getElementById('currently-playing-title').firstChild;
    } catch (e) { var titleElement = null; }
    try {
        var artistElement = document.getElementById('player-artist').firstChild;
    } catch (e) { var artistElement = null; }

    status.disabled = playPauseButton.disabled === true;
    status.playing = playPauseButton.classList.contains('playing');
    status.canNext = nextButton.disabled === false;
    status.canPrev = prevButton.disabled === false;
    status.volume = volumeBar.value;

    try {
        status.songTitle = titleElement.innerText || titleElement.textContent;
        status.songArtist = artistElement.innerText || artistElement.textContent;
        status.songAlbum = albumElement.innerText || albumElement.textContent;
        status.artLocation = artElement.src.replace("=s90-", "=s500-");
    } catch (e) { }

    status.progressNow = progressBar.getAttribute('aria-valuenow');
    status.progressMin = progressBar.getAttribute('aria-valuemin');
    status.progressMax = progressBar.getAttribute('aria-valuemax');

    return JSON.stringify(status);
}
