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
