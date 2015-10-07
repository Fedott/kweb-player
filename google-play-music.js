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

    var playPauseButton = document.querySelector('sj-icon-button[data-id=play-pause]');
    var nextButton = document.querySelector('sj-icon-button[data-id=forward]');
    var prevButton = document.querySelector('sj-icon-button[data-id=rewind]');
    var volumeBar = document.querySelector('#material-vslider');
    var progressBar = document.querySelector('#material-player-progress');
    var artElement = document.getElementById('playingAlbumArt');
    var albumElement = document.querySelector("#playerSongInfo .player-album");

    try {
        var titleElement = document.getElementById('player-song-title').firstChild;
    } catch (e) { var titleElement = null; }
    try {
        var artistElement = document.getElementById('player-artist').firstChild;
    } catch (e) { var artistElement = null; }

    status.disabled = playPauseButton.disabled === true;
    status.playing = playPauseButton.className === 'playing';
    status.canNext = nextButton.disabled === false;
    status.catPrev = prevButton.disabled === false;
    status.volume = volumeBar.value;

    try {
        status.artLocation = artElement.src.replace("=s90-", "=s500-");
        status.songTitle = titleElement.innerText || titleElement.textContent;
        status.songArtist = artistElement.innerText || artistElement.textContent;
        status.songTitle = albumElement.innerText || albumElement.textContent;
    } catch (e) {}

    status.progressNow = progressBar.getAttribute('aria-valuenow');
    status.progressMin = progressBar.getAttribute('aria-valuemin');
    status.progressMax = progressBar.getAttribute('aria-valuemax');

    return JSON.stringify(status);
}
