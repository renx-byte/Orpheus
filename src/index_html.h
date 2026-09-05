#ifndef INDEX_HTML_H
#define INDEX_HTML_H

#include <Arduino.h>

const char index_html[] PROGMEM = R"rawliteral(
<!doctype html>
<html lang="en">
  <head>
    <meta charset="UTF-8" />
    <meta name="viewport" content="width=device-width, initial-scale=1.0" />
    <title>Orpheus</title>
    <link rel="icon" type="image/svg+xml" href="/favicon.svg" />
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

  --bg-main: #0a0b10;
  --bg-panel: #1e1e2e;
  --text-main: #cdd6f4;
  --soft-red: #d0311e;
  --soft-blue: #4274d9;
  --accent-yellow: #ffb900;
  --accent-gold: #f9e2af;
  --accent-cyan: #89dceb;
  --accent-blue: #89b4fa;
  --shadow-color: #11111b;
}

* {
  font-family: "Raw Pixel", monospace, sans-serif;
  box-sizing: border-box;
}

body {
  margin: 0;
  background-color: var(--bg-main);
  color: var(--text-main);
  background-attachment: fixed;
}

body::before,
body::after {
  content: "";
  position: fixed;
  top: 0;
  left: 0;
  width: 200vw;
  height: 100vh;
  z-index: -1;
  pointer-events: none;
}

body::before {
  background-image:
    radial-gradient(
      2px 2px at 40px 60px,
      rgba(255, 255, 255, 0.8),
      transparent
    ),
    radial-gradient(
      2px 2px at 150px 200px,
      rgba(255, 255, 255, 0.7),
      transparent
    ),
    radial-gradient(
      2px 2px at 300px 80px,
      rgba(137, 220, 235, 0.9),
      transparent
    ),
    radial-gradient(
      2px 2px at 420px 330px,
      rgba(255, 255, 255, 0.8),
      transparent
    ),
    radial-gradient(
      2px 2px at 650px 120px,
      rgba(249, 226, 175, 0.8),
      transparent
    );
  background-size: 800px 400px;
  animation: starDrift 30s linear infinite;
}

body::after {
  background-image:
    radial-gradient(
      1px 1px at 20px 30px,
      rgba(255, 255, 255, 0.4),
      transparent
    ),
    radial-gradient(
      1px 1px at 120px 150px,
      rgba(255, 255, 255, 0.3),
      transparent
    ),
    radial-gradient(
      1px 1px at 220px 80px,
      rgba(255, 255, 255, 0.5),
      transparent
    ),
    radial-gradient(
      1px 1px at 350px 250px,
      rgba(137, 180, 250, 0.4),
      transparent
    ),
    radial-gradient(
      1px 1px at 500px 100px,
      rgba(255, 255, 255, 0.3),
      transparent
    );
  background-size: 600px 300px;
  animation: starDrift 60s linear infinite;
}

@keyframes starDrift {
  0% {
    background-position: 0 0;
  }
  100% {
    background-position: -800px 0;
  }
}

.screen {
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  z-index: 10;
}

#splash-screen {
  background-color: var(--bg-main);
}

#typewriter-heading {
  cursor: default;
  font-size: 48px;
  letter-spacing: 5px;
  color: var(--accent-gold);
  display: inline-block;
  border-right: 3px solid currentColor;
  white-space: nowrap;
  animation: blink 0.75s step-end infinite;
  margin: 0;
}

@keyframes blink {
  from,
  to {
    border-color: transparent;
  }
  50% {
    border-color: currentColor;
  }
}

.menu-button {
  font-size: 24px;
  letter-spacing: 3px;
  width: 300px;
  height: 70px;
  margin: 15px 0;
  background-color: transparent;
  border: 3px solid var(--accent-blue);
  color: var(--accent-cyan);
  clip-path: var(--pixel-shape);
  box-shadow: 6px 6px 0 0 var(--shadow-color);
  cursor: pointer;
  transition:
    transform 300ms ease,
    background-color 300ms ease;
}

.menu-button:hover {
  transform: translate(-3px, -3px);
  background-color: rgba(255, 255, 255, 0.05);
}

.back-button {
  position: absolute;
  top: 20px;
  left: 20px;
  font-size: 18px;
  background: transparent;
  border: none;
  color: var(--accent-cyan);
  cursor: pointer;
  letter-spacing: 2px;
  z-index: 15;
}

.back-button:hover {
  color: var(--accent-gold);
}

#compendium-screen {
  overflow-y: auto;
  padding: 80px 40px 40px;
}

.song-grid {
  display: grid;
  grid-template-columns: repeat(4, 1fr);
  gap: 40px;
  justify-items: center;
  align-items: start;
  width: 100%;
  max-width: 1200px;
  margin: 0 auto;
}

.song-card-wrapper {
  position: relative;
  transition: transform 0.3s ease;
}

.song-card-wrapper:hover {
  transform: translate(-1px, -10px);
}

.song-card {
  cursor: pointer;
  position: relative;
  width: 250px;
  height: 300px;
  padding: 30px 24px 24px;
  border: 3px solid var(--song-shadow, #3f352f);
  clip-path: var(--pixel-shape);
  background: linear-gradient(
    145deg,
    var(--song-primary, #c1afa0) 0%,
    var(--song-primary, #c1afa0) 58%,
    var(--song-dark, #6c584c) 100%
  );
  color: white;
  box-shadow: 10px 10px 0 var(--song-shadow, #3f352f);
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

.play-button {
  position: absolute;
  right: -18px;
  bottom: -18px;
  width: 55px;
  height: 55px;
  border: 3px solid var(--song-shadow, #3f352f);
  background: white;
  color: var(--song-shadow, #3f352f);
  font-family: inherit;
  font-size: 18px;
  cursor: pointer;
  border-radius: 50%;
  box-shadow: 5px 5px 0 var(--song-shadow, #3f352f);
  z-index: 10;
  transition:
    transform 0.15s ease,
    box-shadow 0.15s ease;
}

.play-button:hover {
  transform: scale(1.1);
  box-shadow: 3px 3px 0 var(--song-shadow, #3f352f);
}

#delete-screen {
  overflow-y: auto;
  padding: 80px 40px 40px;
}

.directory-container {
  width: 100%;
  max-width: 800px;
  margin: 0 auto;
  background: rgba(0, 0, 0, 0.3);
  border: 3px solid #313244;
  clip-path: var(--pixel-shape);
  padding: 20px;
  box-shadow: 12px 12px 0 0 var(--shadow-color);
}

#delete-directory-list {
  list-style: none;
  padding-left: 18px;
  margin: 0;
}

#delete-directory-list ul {
  list-style: none;
  padding-left: 18px;
  margin: 0;
}

#delete-directory-list li {
  position: relative;
  list-style-type: none;
  padding: 5px 0;
}

#delete-directory-list .file::before {
  content: "└─ ";
  font-family: monospace;
  color: var(--accent-cyan);
  font-weight: bold;
}

#delete-directory-list .folder {
  display: inline-block;
  font-size: 20px;
  color: var(--accent-gold);
  cursor: pointer;
}

#delete-directory-list .file {
  display: inline-block;
  cursor: pointer;
}

#delete-directory-list .size {
  font-size: 16px;
  color: var(--accent-cyan);
  margin-left: 20px;
}

#delete-directory-list .folder:hover,
#delete-directory-list .file:hover {
  background-color: rgba(208, 49, 30, 0.2);
  border-radius: 3px;
}

.modal-overlay {
  position: fixed;
  top: 0;
  left: 0;
  width: 100vw;
  height: 100vh;
  background: rgba(10, 11, 16, 0.85);
  backdrop-filter: blur(4px);
  display: flex;
  justify-content: center;
  align-items: center;
  z-index: 1000;
  opacity: 0;
  pointer-events: none;
  transition: opacity 300ms ease;
}

.modal-overlay.is-visible {
  opacity: 1;
  pointer-events: auto;
}

.modal-container {
  background: var(--bg-panel);
  border: 3px solid var(--accent-cyan);
  clip-path: var(--pixel-shape);
  padding: 30px;
  width: 450px;
  max-height: 90vh;
  overflow-y: auto;
  box-shadow: 8px 8px 0 0 var(--shadow-color);
  color: var(--text-main);
  display: flex;
  flex-direction: column;
  gap: 20px;
  transition: transform 300ms ease;
  transform: translateY(10px);
}

.modal-overlay.is-visible .modal-container {
  transform: translateY(0);
}

.modal-heading {
  color: var(--accent-gold);
  text-align: center;
  margin: 0;
  font-size: 22px;
  letter-spacing: 2px;
}

.metadata-fields {
  display: flex;
  flex-direction: column;
  gap: 12px;
}

.modal-input {
  background: var(--bg-main);
  border: 2px solid var(--accent-blue);
  color: var(--text-main);
  padding: 12px;
  font-family: inherit;
  outline: none;
  clip-path: var(--pixel-shape);
  transition: border-color 200ms ease;
  letter-spacing: 1px;
  font-size: 16px;
}

.modal-input:focus {
  border-color: var(--accent-cyan);
}

.color-inputs {
  display: flex;
  align-items: center;
  gap: 10px;
  margin: 5px 0;
}

.color-inputs label {
  font-size: 14px;
  letter-spacing: 1px;
  color: var(--text-main);
}

.color-inputs input[type="color"] {
  width: 40px;
  height: 40px;
  border: 2px solid var(--accent-blue);
  background: none;
  cursor: pointer;
  padding: 0;
}

.album-art-upload {
  margin: 10px 0;
  display: flex;
  flex-direction: column;
  gap: 5px;
}

.album-art-upload label {
  font-size: 14px;
  letter-spacing: 1px;
  color: var(--accent-cyan);
}

.album-art-upload input[type="file"] {
  background: var(--bg-main);
  border: 2px solid var(--accent-blue);
  color: var(--text-main);
  padding: 8px;
  font-family: inherit;
}

#drop-zone {
  border: 3px dashed var(--accent-blue);
  font-size: 14px;
  letter-spacing: 3px;
  color: var(--accent-cyan);
  border-radius: 8px;
  padding: 40px;
  text-align: center;
  background-color: var(--bg-main);
  cursor: pointer;
  transition:
    background-color 0.2s ease,
    border-color 0.2s ease;
}

#drop-zone:hover {
  background-color: rgba(137, 220, 235, 0.05);
}

#selected-file-info {
  margin: 10px 0;
  font-size: 14px;
  color: var(--accent-cyan);
}

#upload-progress-container {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  width: 100%;
  padding: 20px 0;
}

.progress-bar-container {
  width: 100%;
  height: 20px;
  background-color: var(--bg-main);
  border: 2px solid var(--accent-blue);
  clip-path: var(--pixel-shape);
  overflow: hidden;
}

.progress-bar {
  height: 100%;
  background-color: var(--accent-cyan);
  width: 0%;
  transition: width 0.3s ease;
}

#progress-percent-text {
  text-align: center;
  margin: 10px 0 0;
  font-size: 18px;
  color: var(--accent-gold);
}

.upload-filename {
  color: var(--accent-gold);
  font-size: 14px;
  letter-spacing: 1px;
  margin-top: 10px;
  text-align: center;
  word-break: break-all;
}

.error-message {
  color: var(--soft-red);
  border: 2px solid var(--soft-red);
  padding: 10px;
  font-size: 14px;
  background: rgba(208, 49, 30, 0.1);
  clip-path: var(--pixel-shape);
}

.modal-btn {
  font-size: 18px;
  letter-spacing: 3px;
  width: 100%;
  height: 50px;
  background-color: transparent;
  clip-path: var(--pixel-shape);
  box-shadow: 6px 6px 0 0 var(--shadow-color);
  cursor: pointer;
  transition: transform 300ms ease;
  margin: 5px 0;
}

.modal-btn:hover {
  transform: translate(-3px, -3px);
}

.btn-cancel {
  color: var(--soft-red);
  border: 3px solid var(--soft-red);
}

.btn-cancel:hover {
  background-color: rgba(208, 49, 30, 0.1);
}

.btn-submit {
  color: var(--soft-blue);
  border: 3px solid var(--soft-blue);
}

.btn-submit:disabled {
  opacity: 0.5;
  cursor: not-allowed;
}

.d-none {
  display: none !important;
}

@media (max-width: 1200px) {
  .song-grid {
    grid-template-columns: repeat(3, 1fr);
  }
}

@media (max-width: 900px) {
  .song-grid {
    grid-template-columns: repeat(2, 1fr);
  }
}

@media (max-width: 600px) {
  .song-grid {
    grid-template-columns: 1fr;
  }
}

</style>
    
    
  </head>
  <body>
    <!-- Splash Screen -->
    <div id="splash-screen" class="screen">
      <h1 id="typewriter-heading"></h1>
    </div>

    <!-- Main Menu -->
    <div id="menu-screen" class="screen d-none">
      <button id="btn-compendium" class="menu-button">Open Compendium</button>
      <button id="btn-create" class="menu-button">Create Files</button>
      <button id="btn-delete" class="menu-button">Delete Files</button>
    </div>

    <!-- Compendium Screen -->
    <div id="compendium-screen" class="screen d-none">
      <div id="song-grid" class="song-grid"></div>
      <button id="btn-back-menu" class="back-button">← Menu</button>
    </div>

    <!-- Delete Screen (Directory Tree) -->
    <div id="delete-screen" class="screen d-none">
      <div id="delete-directory-container" class="directory-container">
        <ul id="delete-directory-list"></ul>
      </div>
      <button id="btn-back-menu-delete" class="back-button">← Menu</button>
    </div>

    <!-- Upload Modal -->
    <div id="upload-modal-overlay" class="modal-overlay">
      <div id="upload-modal" class="modal-container">
        <h5 class="modal-heading">UPLOAD SONG</h5>

        <!-- MP3 Drop Zone -->
        <div id="drop-zone">
          <p>Click or drag an MP3 file here</p>
          <input type="file" id="file-input" accept="audio/mpeg" hidden />
        </div>
        <div id="selected-file-info" class="d-none">
          <span id="selected-file-name"></span>
        </div>

        <!-- Song name -->
        <label for="input-song-name">Song Name</label>
        <input type="text" id="input-song-name" />

        <!-- Artist -->
        <label for="input-artist">Artist</label>
        <input type="text" id="input-artist" />

        <!-- Album -->
        <label for="input-album">Album</label>
        <input type="text" id="input-album" />

        <!-- Release year (only 4‑digit year) -->
        <label for="input-release-year">Release Year</label>
        <input
          type="number"
          id="input-release-year"
          min="1000"
          max="9999"
          step="1"
          placeholder="YYYY"
        />

        <!-- Duration (readonly, auto‑filled) -->
        <label for="input-duration">Duration</label>
        <input type="text" id="input-duration" readonly />

        <!-- Card colors -->
        <label for="input-color-primary">Primary Color</label>
        <input type="color" id="input-color-primary" />
        <label for="input-color-dark">Dark Color</label>
        <input type="color" id="input-color-dark" />
        <label for="input-color-shadow">Shadow Color</label>
        <input type="color" id="input-color-shadow" />

        <!-- Upload progress -->
        <div id="upload-progress-container" class="d-none">
          <div id="progress-bar"></div>
          <span id="progress-percent-text">0%</span>
          <span id="upload-filename"></span>
        </div>

        <div id="upload-error" class="d-none"></div>

        <button id="btn-upload-song" disabled>Upload</button>
        <button id="btn-cancel-upload">Cancel</button>
      </div>
    </div>
  <script>
// ============================================================
// Typewriter Effect for Splash
// ============================================================
const initSplashTypewriter = () => {
  const heading = document.getElementById("typewriter-heading");
  const text = "Initializing SD Card...";
  let charIndex = 0;

  function typeLoop() {
    if (charIndex <= text.length) {
      heading.textContent = text.substring(0, charIndex) || "\u00A0";
      charIndex++;
      setTimeout(typeLoop, 80);
    } else {
      setTimeout(showMenu, 3000);
    }
  }
  typeLoop();
};

function showMenu() {
  document.getElementById("splash-screen").classList.add("d-none");
  document.getElementById("menu-screen").classList.remove("d-none");
}

// ============================================================
// Global state
// ============================================================
let currentScreen = "menu";
let selectedFile = null;

// ============================================================
// API endpoints (centralised)
// ============================================================
const API = {
  uploadSong: "/api/songs/upload",
  songsList: "/api/metadata",
  streamSong: "/api/songs",
  removePayload: "/remove_payload",
  sdDirectory: "/sd_directory",
  downloadFile: "/download_file",
};

// ============================================================
// Upload helper – single request with both files
// ============================================================
function uploadSongWithMetadata(mp3File, jsonFile) {
  return new Promise((resolve, reject) => {
    const formData = new FormData();
    formData.append("audio", mp3File, mp3File.name);
    formData.append("metadata", jsonFile, jsonFile.name);

    const xhr = new XMLHttpRequest();
    xhr.open("POST", API.uploadSong, true);

    // Progress tracking
    xhr.upload.addEventListener("progress", (event) => {
      if (event.lengthComputable) {
        const percent = Math.round((event.loaded / event.total) * 100);
        updateProgressBar(percent, mp3File.name);
      }
    });

    xhr.addEventListener("load", () => {
      if (xhr.status >= 200 && xhr.status < 300) {
        resolve(true);
      } else {
        reject(new Error(`Upload failed with status ${xhr.status}`));
      }
    });

    xhr.addEventListener("error", () => {
      reject(new Error("Network error during upload."));
    });

    xhr.send(formData);
  });
}

function updateProgressBar(percent, filename) {
  const progressBar = document.getElementById("progress-bar");
  const progressPercentText = document.getElementById("progress-percent-text");
  const uploadFilename = document.getElementById("upload-filename");
  if (progressBar) progressBar.style.width = `${percent}%`;
  if (progressPercentText) progressPercentText.textContent = `${percent}%`;
  if (uploadFilename) uploadFilename.textContent = filename;
}

// ============================================================
// Metadata extraction with fallback (Dynamic Library Loading)
// ============================================================

// Helper function to dynamically load jsmediatags if it isn't already present
async function loadJsMediaTags() {
  if (typeof window.jsmediatags !== "undefined") {
    return true;
  }

  return new Promise((resolve, reject) => {
    const script = document.createElement("script");
    script.src =
      "https://cdnjs.cloudflare.com/ajax/libs/jsmediatags/3.9.5/jsmediatags.min.js";
    script.onload = () => resolve(true);
    script.onerror = () =>
      reject(new Error("Failed to load jsmediatags script."));
    document.head.appendChild(script);
  });
}

async function extractMp3Metadata(file) {
  try {
    await loadJsMediaTags();
  } catch (err) {
    console.warn(
      "jsmediatags could not be loaded, metadata extraction skipped.",
      err,
    );
    return {
      songName: "",
      artist: "",
      album: "",
      releaseYear: "",
      duration: "",
    };
  }

  return new Promise((resolve) => {
    window.jsmediatags.read(file, {
      onSuccess: (tag) => {
        const tags = tag.tags;
        const metadata = {
          songName: tags.title || "",
          artist: tags.artist || "",
          album: tags.album || "",
          releaseYear: tags.year || "",
          duration: "",
        };
        resolve(metadata);
      },
      onError: (error) => {
        console.warn("Could not read metadata", error);
        resolve({
          songName: "",
          artist: "",
          album: "",
          releaseYear: "",
          duration: "",
        });
      },
    });
  });
}

// ============================================================
// Sanitise filename: remove extension, replace spaces/special chars
// ============================================================
function sanitiseBaseName(originalName) {
  const withoutExt = originalName.replace(/\.[^/.]+$/, "");
  const safe = withoutExt
    .replace(/[^a-zA-Z0-9_\-]/g, "_") // replace unsafe characters with underscore
    .replace(/_+/g, "_") // collapse multiple underscores
    .replace(/^_+|_+$/g, ""); // trim leading/trailing underscores
  return safe || "song"; // fallback if empty
}

// ============================================================
// Modal handling
// ============================================================
function openUploadModal() {
  const overlay = document.getElementById("upload-modal-overlay");
  overlay.classList.add("is-visible");

  selectedFile = null;
  document.getElementById("input-song-name").value = "";
  document.getElementById("input-artist").value = "";
  document.getElementById("input-album").value = "";
  document.getElementById("input-release-year").value = "";
  document.getElementById("input-duration").value = "";
  document.getElementById("input-color-primary").value = "#c1afa0";
  document.getElementById("input-color-dark").value = "#6c584c";
  document.getElementById("input-color-shadow").value = "#3f352f";
  document.getElementById("drop-zone").classList.remove("d-none");
  document.getElementById("selected-file-info").classList.add("d-none");
  document.getElementById("upload-progress-container").classList.add("d-none");
  document.getElementById("upload-error").classList.add("d-none");
  document.getElementById("btn-upload-song").disabled = true;
  document.getElementById("file-input").value = "";
}

document.getElementById("btn-cancel-upload").addEventListener("click", () => {
  document
    .getElementById("upload-modal-overlay")
    .classList.remove("is-visible");
});

document.getElementById("drop-zone").addEventListener("click", () => {
  document.getElementById("file-input").click();
});

document
  .getElementById("file-input")
  .addEventListener("change", async (event) => {
    const file = event.target.files[0];
    if (!file) return;

    // Accept only MP3 files
    if (
      !file.type.match("audio/mpeg") &&
      !file.name.toLowerCase().endsWith(".mp3")
    ) {
      alert("Please select a valid MP3 file.");
      event.target.value = "";
      return;
    }

    selectedFile = file;
    document.getElementById("selected-file-name").textContent = file.name;
    document.getElementById("selected-file-info").classList.remove("d-none");

    try {
      const metadata = await extractMp3Metadata(file);
      if (!document.getElementById("input-song-name").value)
        document.getElementById("input-song-name").value = metadata.songName;
      if (!document.getElementById("input-artist").value)
        document.getElementById("input-artist").value = metadata.artist;
      if (!document.getElementById("input-album").value)
        document.getElementById("input-album").value = metadata.album;
      if (!document.getElementById("input-release-year").value)
        document.getElementById("input-release-year").value =
          metadata.releaseYear;

      // Automatically extract duration
      const audio = new Audio(URL.createObjectURL(file));
      audio.addEventListener("loadedmetadata", () => {
        const duration = audio.duration;
        const minutes = Math.floor(duration / 60);
        const seconds = Math.floor(duration % 60);
        document.getElementById("input-duration").value =
          `${minutes}:${seconds.toString().padStart(2, "0")}`;
      });
    } catch (err) {
      console.warn("Metadata extraction failed, user can fill manually", err);
    }

    document.getElementById("btn-upload-song").disabled = false;
  });

document
  .getElementById("btn-upload-song")
  .addEventListener("click", async () => {
    if (!selectedFile) return;

    const songName = document.getElementById("input-song-name").value.trim();
    const artist = document.getElementById("input-artist").value.trim();
    const album = document.getElementById("input-album").value.trim();
    const releaseYear = document
      .getElementById("input-release-year")
      .value.trim();
    const durationText = document.getElementById("input-duration").value.trim();

    // Validate required fields
    if (!songName || !artist || !album || !releaseYear || !durationText) {
      alert("Please fill in all metadata fields.");
      return;
    }

    // Release year must be a 4‑digit year
    if (!/^\d{4}$/.test(releaseYear)) {
      alert("Release year must be a 4‑digit year (e.g., 2024).");
      return;
    }

    // Convert duration string to seconds
    const durationParts = durationText.split(":");
    let durationSeconds = 0;
    if (durationParts.length === 2) {
      const minutes = parseInt(durationParts[0], 10);
      const seconds = parseInt(durationParts[1], 10);
      if (!isNaN(minutes) && !isNaN(seconds)) {
        durationSeconds = minutes * 60 + seconds;
      }
    }
    if (durationSeconds <= 0) {
      alert("Invalid duration. Please check the duration field.");
      return;
    }

    const colorPrimary = document.getElementById("input-color-primary").value;
    const colorDark = document.getElementById("input-color-dark").value;
    const colorShadow = document.getElementById("input-color-shadow").value;

    // Construct base name for both files
    const baseName = sanitiseBaseName(selectedFile.name);
    const mp3FileName = `${baseName}.mp3`;
    const jsonFileName = `${baseName}.json`;
    const mp3Path = `/songs/${mp3FileName}`; // remote path inside /songs

    // Build metadata JSON object (no album art)
    const metadataJSON = {
      title: songName,
      artist: artist,
      album: album,
      releaseYear: parseInt(releaseYear, 10),
      duration: durationSeconds,
      cardColors: [colorPrimary, colorDark, colorShadow],
      file_path: mp3Path,
    };

    // Create a Blob for the JSON file
    const jsonBlob = new Blob([JSON.stringify(metadataJSON, null, 2)], {
      type: "application/json",
    });
    const jsonFile = new File([jsonBlob], jsonFileName, {
      type: "application/json",
    });

    // Disable UI during upload
    document.getElementById("drop-zone").classList.add("d-none");
    document.getElementById("selected-file-info").classList.add("d-none");
    document
      .getElementById("upload-progress-container")
      .classList.remove("d-none");
    document.getElementById("upload-error").classList.add("d-none");
    document.getElementById("btn-upload-song").disabled = true;
    document.getElementById("btn-cancel-upload").disabled = true;

    updateProgressBar(0, selectedFile.name);

    try {
      // Send both files in one multipart request
      await uploadSongWithMetadata(selectedFile, jsonFile);

      updateProgressBar(100, selectedFile.name);
      setTimeout(() => {
        document
          .getElementById("upload-modal-overlay")
          .classList.remove("is-visible");
        selectedFile = null;
        document.getElementById("btn-upload-song").disabled = true;
        document.getElementById("btn-cancel-upload").disabled = false;
        if (currentScreen === "compendium") loadCompendium();
      }, 500);
    } catch (err) {
      console.error("Upload failed:", err);
      document.getElementById("upload-error").textContent =
        "Upload failed: " + err.message;
      document.getElementById("upload-error").classList.remove("d-none");
      document.getElementById("btn-upload-song").disabled = false;
      document.getElementById("btn-cancel-upload").disabled = false;
      document.getElementById("drop-zone").classList.remove("d-none");
      document.getElementById("selected-file-info").classList.remove("d-none");
    }
  });

// ============================================================
// Compendium loading – now fetches from /api/metadata
// ============================================================
async function loadCompendium() {
  const grid = document.getElementById("song-grid");
  grid.innerHTML = "";
  try {
    const response = await fetch(API.songsList);
    if (!response.ok) throw new Error("Failed to fetch songs");
    const songs = await response.json();
    songs.forEach((song) => {
      const card = createSongCard(song);
      grid.appendChild(card);
    });
  } catch (err) {
    console.error("Error loading songs:", err);
  }
}

function createSongCard(song) {
  const wrapper = document.createElement("div");
  wrapper.className = "song-card-wrapper";

  const card = document.createElement("div");
  card.className = "song-card";
  card.style.setProperty("--song-primary", song.cardColors?.[0] || "#c1afa0");
  card.style.setProperty("--song-dark", song.cardColors?.[1] || "#6c584c");
  card.style.setProperty("--song-shadow", song.cardColors?.[2] || "#3f352f");

  // Album art removed – just use a plain background
  const artDiv = document.createElement("div");
  artDiv.className = "album-art";
  artDiv.style.backgroundColor = "rgba(0,0,0,0.3)";

  const titleDiv = document.createElement("div");
  titleDiv.className = "song-title";
  const h1 = document.createElement("h1");
  h1.textContent = song.title;
  titleDiv.appendChild(h1);

  const detailsDiv = document.createElement("div");
  detailsDiv.className = "song-details";
  const rows = [
    { label: "ARTIST", value: song.artist },
    { label: "ALBUM", value: song.album },
    { label: "RELEASE", value: song.releaseYear },
    { label: "DURATION", value: formatDuration(song.duration) },
  ];
  rows.forEach((row) => {
    const detail = document.createElement("div");
    detail.className = "detail";
    const labelSpan = document.createElement("span");
    labelSpan.className = "label";
    labelSpan.textContent = row.label;
    const valueSpan = document.createElement("span");
    valueSpan.className = "value";
    valueSpan.textContent = row.value;
    detail.appendChild(labelSpan);
    detail.appendChild(valueSpan);
    detailsDiv.appendChild(detail);
  });

  card.appendChild(artDiv);
  card.appendChild(titleDiv);
  card.appendChild(detailsDiv);
  wrapper.appendChild(card);

  const playBtn = document.createElement("button");
  playBtn.className = "play-button";
  playBtn.textContent = "▶";
  playBtn.addEventListener("click", (e) => {
    e.stopPropagation();
    // Future playback: stream MP3 from API.streamSong + song.file_path
    // e.g., window.location.href = API.streamSong + song.file_path;
  });
  wrapper.appendChild(playBtn);

  // Click to download (or stream)
  card.addEventListener("click", () => {
    if (song.file_path) {
      window.location.href =
        API.downloadFile + "?path=" + encodeURIComponent(song.file_path);
    }
  });

  return wrapper;
}

// Helper to format seconds as M:SS
function formatDuration(totalSeconds) {
  if (!totalSeconds || isNaN(totalSeconds)) return "0:00";
  const minutes = Math.floor(totalSeconds / 60);
  const seconds = totalSeconds % 60;
  return `${minutes}:${seconds.toString().padStart(2, "0")}`;
}

// ============================================================
// Delete Mode - Directory Tree
// ============================================================
function buildDeleteDirectoryDOM(node, container) {
  const ul = document.createElement("ul");

  if (node.type === "folder") {
    node.children?.forEach((child) => {
      const li = document.createElement("li");

      if (child.type === "folder") {
        const span = document.createElement("span");
        span.className = "folder";
        span.textContent = child.name + "/";
        li.appendChild(span);
        buildDeleteDirectoryDOM(child, li);
      } else {
        const span = document.createElement("span");
        span.className = "file";
        span.textContent = child.name;

        const sizeSpan = document.createElement("span");
        sizeSpan.className = "size";
        const sizeText =
          child.size < 1048576
            ? (child.size / 1024).toFixed(1) + " kb"
            : (child.size / 1048576).toFixed(1) + " Mb";
        sizeSpan.textContent = `(${sizeText})`;

        li.appendChild(span);
        li.appendChild(sizeSpan);
      }

      li.style.cursor = "pointer";
      li.addEventListener("click", async (event) => {
        event.stopPropagation();
        const target = event.target;
        const isFolder = target.classList.contains("folder");
        const isFile =
          target.classList.contains("file") ||
          target.classList.contains("size");
        if (!isFolder && !isFile) return;

        let clickedLi = target.closest("li");
        let pathParts = [];
        let currentLi = clickedLi;

        while (currentLi && currentLi.closest("#delete-directory-list")) {
          let folderSpan = Array.from(currentLi.children).find((el) =>
            el.classList.contains("folder"),
          );
          let fileSpan = Array.from(currentLi.children).find((el) =>
            el.classList.contains("file"),
          );

          if (folderSpan) {
            pathParts.unshift(folderSpan.textContent.trim().replace(/\/$/, ""));
          } else if (fileSpan) {
            pathParts.unshift(fileSpan.textContent.trim());
          }

          let parentUl = currentLi.parentElement;
          if (!parentUl || parentUl.tagName.toLowerCase() !== "ul") break;
          let parentLi = parentUl.parentElement.closest("li");
          if (!parentLi) break;
          currentLi = parentLi;
        }

        let fullPath = "/" + pathParts.join("/");
        if (fullPath === "/") return;

        if (
          !confirm(`Are you sure you want to permanently delete:\n${fullPath}?`)
        )
          return;

        try {
          const response = await fetch(API.removePayload, {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ path: fullPath }),
          });
          if (!response.ok) throw new Error("Remove failed");
          await refreshDeleteDirectory();
        } catch (err) {
          console.error("Remove request failed:", err);
          alert("Deletion failed");
        }
      });

      ul.appendChild(li);
    });
  }

  container.appendChild(ul);
}

async function refreshDeleteDirectory() {
  try {
    const response = await fetch(API.sdDirectory);
    if (!response.ok) throw new Error("Failed to fetch directory");
    const data = await response.json();
    const listElement = document.getElementById("delete-directory-list");
    if (!listElement) return;
    listElement.innerHTML = "";
    buildDeleteDirectoryDOM(data, listElement);
  } catch (err) {
    console.error("Directory refresh failed:", err);
  }
}

// ============================================================
// Screen navigation
// ============================================================
document.getElementById("btn-compendium").addEventListener("click", () => {
  currentScreen = "compendium";
  document.getElementById("menu-screen").classList.add("d-none");
  document.getElementById("compendium-screen").classList.remove("d-none");
  loadCompendium();
});

document.getElementById("btn-back-menu").addEventListener("click", () => {
  currentScreen = "menu";
  document.getElementById("compendium-screen").classList.add("d-none");
  document.getElementById("menu-screen").classList.remove("d-none");
});

document.getElementById("btn-create").addEventListener("click", () => {
  openUploadModal();
});

document.getElementById("btn-delete").addEventListener("click", () => {
  currentScreen = "delete";
  document.getElementById("menu-screen").classList.add("d-none");
  document.getElementById("delete-screen").classList.remove("d-none");
  refreshDeleteDirectory();
});

document
  .getElementById("btn-back-menu-delete")
  .addEventListener("click", () => {
    currentScreen = "menu";
    document.getElementById("delete-screen").classList.add("d-none");
    document.getElementById("menu-screen").classList.remove("d-none");
  });

// ============================================================
// Initialize
// ============================================================
document.addEventListener("DOMContentLoaded", () => {
  initSplashTypewriter();
});

</script>
</body>
</html>

)rawliteral";

#endif // INDEX_HTML_H
