#ifndef COMPENDIUM_H
#define COMPENDIUM_H

#include <Arduino.h>

const char compendium_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Orpheus-Compendium</title>
    <style>
:root {
  --pixel-shape: polygon(
    6px 0,
    calc(100% - 6px) 0,
    calc(100% - 6px) 3px,
    calc(100% - 3px) 3px,
    calc(100% - 3px) 6px,
    100% 6px,
    100% calc(100% - 6px),
    calc(100% - 3px) calc(100% - 6px),
    calc(100% - 3px) calc(100% - 3px),
    calc(100% - 6px) calc(100% - 3px),
    calc(100% - 6px) 100%,
    6px 100%,
    6px calc(100% - 3px),
    3px calc(100% - 3px),
    3px calc(100% - 6px),
    0 calc(100% - 6px),
    0 6px,
    3px 6px,
    3px 3px,
    6px 3px
  );
}

/* ---------- 8 Color Templates ---------- */
.template-1 {
  --song-primary: #d9a7b0;
  --song-dark: #8f4f5d;
  --song-shadow: #4a2730;
}

.template-2 {
  --song-primary: #8fb9d9;
  --song-dark: #3f7099;
  --song-shadow: #203b52;
}

.template-3 {
  --song-primary: #e0b85c;
  --song-dark: #98751f;
  --song-shadow: #51400f;
}

.template-4 {
  --song-primary: #91c9a5;
  --song-dark: #3f8057;
  --song-shadow: #21452f;
}

.template-5 {
  --song-primary: #b99bdd;
  --song-dark: #704a99;
  --song-shadow: #3b2752;
}

.template-6 {
  --song-primary: #e19a67;
  --song-dark: #a55224;
  --song-shadow: #572b13;
}

.template-7 {
  --song-primary: #72c8c8;
  --song-dark: #287878;
  --song-shadow: #164343;
}

.template-8 {
  --song-primary: #d6d6d6;
  --song-dark: #777777;
  --song-shadow: #383838;
}

* {
  box-sizing: border-box;
}

body {
  font-family: "Raw Pixel", monospace, sans-serif;
  display: flex;
  flex-direction: column;
  align-items: center;
  justify-content: flex-start;
  margin: 0;
  min-height: 100vh;
  background: #2a2a2a;
  padding: 50px 20px;
}

/* ---------- Big Heading ---------- */
.page-header {
  text-align: center;
  margin-bottom: 50px;
}

.page-title {
  margin: 0;
  font-size: 64px;
  line-height: 1;
  letter-spacing: 6px;
  color: #ffffff;
  text-shadow:
    4px 4px 0 #3f352f,
    8px 8px 0 rgba(0, 0, 0, 0.5);
  text-transform: uppercase;
  font-weight: bold;
}

/* ---------- Cards Container ---------- */
.cards-container {
  display: flex;
  flex-wrap: wrap;
  justify-content: center;
  align-items: flex-start;
  gap: 45px;
  max-width: 1400px;
}

/* ---------- Card Wrapper ---------- */
.song-card-wrapper {
  position: relative;
  transition: transform 0.3s ease;
}

.song-card-wrapper:hover {
  transform: translate(-1px, -10px);
}

/* ---------- Song Card ---------- */
.song-card {
  cursor: pointer;
  position: relative;
  width: 250px;
  height: 300px;
  padding: 30px 24px 24px;
  border: 3px solid var(--song-shadow);
  clip-path: var(--pixel-shape);
  background: linear-gradient(
    145deg,
    var(--song-primary) 0%,
    var(--song-primary) 58%,
    var(--song-dark) 100%
  );
  color: white;
  box-shadow: 10px 10px 0 var(--song-shadow);
  display: flex;
  flex-direction: column;
  overflow: hidden;
}

.song-card::before {
  content: "";
  position: absolute;
  inset: 0;
  background: linear-gradient(
    to bottom,
    rgba(255, 255, 255, 0.12),
    transparent 30%
  );
  pointer-events: none;
}

.song-card::after {
  content: "";
  position: absolute;
  inset: auto 0 0 0;
  height: 55%;
  background: linear-gradient(to top, rgba(0, 0, 0, 0.65), transparent);
  pointer-events: none;
}

/* ---------- Album Art ---------- */
.album-art {
  align-self: center;
  width: 85px;
  height: 85px;
  margin-top: 6px;
  flex-shrink: 0;
  border-radius: 50%;
  overflow: hidden;
  border: 4px solid rgba(255, 255, 255, 0.8);
  box-shadow: 5px 5px 0 rgba(0, 0, 0, 0.6);
  position: relative;
  z-index: 1;
}

.album-art img {
  width: 100%;
  height: 100%;
  display: block;
  object-fit: cover;
  transform: scale(1.8);
}

/* ---------- Song Title ---------- */
.song-title {
  flex: 1;
  display: flex;
  align-items: center;
  justify-content: center;
  text-align: center;
  position: relative;
  z-index: 1;
}

.song-title h1 {
  margin: 0;
  font-size: 20px;
  line-height: 1.15;
  letter-spacing: 2px;
  text-shadow: 3px 3px 0 rgba(0, 0, 0, 0.65);
}

/* ---------- Song Details ---------- */
.song-details {
  position: relative;
  z-index: 1;
  width: 100%;
  padding-top: 12px;
  border-top: 2px solid rgba(255, 255, 255, 0.25);
  display: flex;
  flex-direction: column;
  gap: 6px;
}

.detail {
  display: flex;
  justify-content: space-between;
  align-items: baseline;
  gap: 10px;
  font-size: 11px;
  line-height: 1.2;
}

.label {
  font-size: 9px;
  letter-spacing: 1.5px;
  opacity: 0.6;
}

.value {
  text-align: right;
  max-width: 65%;
  overflow: hidden;
  text-overflow: ellipsis;
  white-space: nowrap;
  opacity: 0.9;
}

/* ---------- Responsive ---------- */
@media (max-width: 1300px) {
  .cards-container {
    gap: 35px;
  }
}

@media (max-width: 650px) {
  .page-title {
    font-size: 42px;
    letter-spacing: 4px;
    text-shadow:
      3px 3px 0 #3f352f,
      6px 6px 0 rgba(0, 0, 0, 0.5);
  }
  .cards-container {
    gap: 30px;
  }
  .song-card {
    width: 220px;
    height: 275px;
    padding: 24px 18px 20px;
  }
  .album-art {
    width: 70px;
    height: 70px;
    border-width: 3px;
  }
  .song-title h1 {
    font-size: 17px;
    letter-spacing: 1.5px;
  }
  .detail {
    font-size: 10px;
  }
  .label {
    font-size: 8px;
  }
}

</style>
  </head>
  <body>
    <header class="page-header">
      <h1 class="page-title">ORPHEUS COMPENDIUM</h1>
    </header>
    <div id="cards-container" class="cards-container">
      <!-- Cards will be injected here by test.js -->
    </div>
    
  <script>
const API_URL = "/songs.json";

const templates = [
  "template-1",
  "template-2",
  "template-3",
  "template-4",
  "template-5",
  "template-6",
  "template-7",
  "template-8",
];

function randomTemplate() {
  return templates[Math.floor(Math.random() * templates.length)];
}

function createSongCard(song) {
  const wrapper = document.createElement("div");
  wrapper.className = "song-card-wrapper";

  const card = document.createElement("div");
  card.className = "song-card";
  card.classList.add(randomTemplate());

  // Album art with fallback
  const albumArt = document.createElement("div");
  albumArt.className = "album-art";
  const img = document.createElement("img");
  img.src = "/coverart?file=" + encodeURIComponent(song.coverFilename);
  img.alt = song.name || "Album artwork";
  img.onerror = function () {
    this.style.display = "none";
    albumArt.style.backgroundColor = "#ccc";
  };
  albumArt.appendChild(img);

  // Song title
  const titleDiv = document.createElement("div");
  titleDiv.className = "song-title";
  const titleH1 = document.createElement("h1");
  titleH1.textContent = song.name || song.title || "Unknown";
  titleDiv.appendChild(titleH1);

  // Song details
  const detailsDiv = document.createElement("div");
  detailsDiv.className = "song-details";

  const detailConfig = [
    { label: "ARTIST", value: song.artist },
    { label: "ALBUM", value: song.album },
    { label: "RELEASE", value: song.releaseYear },
    { label: "DURATION", value: song.duration },
  ];

  detailConfig.forEach((item) => {
    const detailRow = document.createElement("div");
    detailRow.className = "detail";
    const labelSpan = document.createElement("span");
    labelSpan.className = "label";
    labelSpan.textContent = item.label;
    const valueSpan = document.createElement("span");
    valueSpan.className = "value";
    valueSpan.textContent = item.value || "Unknown";
    detailRow.appendChild(labelSpan);
    detailRow.appendChild(valueSpan);
    detailsDiv.appendChild(detailRow);
  });

  card.appendChild(albumArt);
  card.appendChild(titleDiv);
  card.appendChild(detailsDiv);
  wrapper.appendChild(card);
  return wrapper;
}

async function loadSongs() {
  const container = document.getElementById("cards-container");
  try {
    const response = await fetch(API_URL);
    if (!response.ok) {
      throw new Error(`HTTP error! status: ${response.status}`);
    }
    const data = await response.json();
    const songs = data.songs || [];
    container.innerHTML = "";
    songs.forEach((song) => {
      const cardElement = createSongCard(song);
      container.appendChild(cardElement);
    });
  } catch (error) {
    console.error("Failed to load songs:", error);
    container.innerHTML = '<p style="color:white;">Could not load songs.</p>';
  }
}

document.addEventListener("DOMContentLoaded", loadSongs);

</script>
</body>
</html>

)rawliteral";

#endif // COMPENDIUM_H
