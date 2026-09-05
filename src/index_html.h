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

@keyframes slideLines {
  0% {
    transform: translate(0, 0);
  }

  100% {
    transform: translate(59.4px, 59.4px);
  }
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

h5 {
  font-size: 18px;
  letter-spacing: 2px;
  text-align: center;
  margin: 0;
}

.header-area {
  height: 10vh;

  text-align: center;

  display: flex;
  align-items: center;
  justify-content: center;

  margin-top: 20px;
}

#typewriter-heading {
  cursor: pointer;

  font-size: 48px;
  letter-spacing: 5px;

  color: var(--accent-gold);

  display: inline-block;

  border-right: 3px solid currentColor;

  white-space: nowrap;

  animation: blink 0.75s step-end infinite;

  transition:
    color 400ms ease,
    transform 400ms ease;

  margin: 0;
}

#typewriter-heading:hover {
  transform: scale(1.02);

  color: var(--accent-cyan);
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

.main-content {
  height: 85vh;

  display: flex;

  align-items: center;
}

.selection-area {
  display: flex;

  flex-direction: column;

  align-items: center;

  width: 30vw;
}

.result-area {
  display: flex;

  flex-direction: column;

  justify-content: center;

  align-items: center;

  width: 70vw;
}

.selection-card {
  position: relative;

  display: flex;

  justify-content: center;

  align-items: center;

  min-width: 250px;

  height: 60px;

  margin: 15px 0;

  color: var(--accent-cyan);

  background: var(--bg-panel);

  border: 3px solid var(--accent-blue);

  box-shadow: 6px 6px 0 0 var(--shadow-color);

  clip-path: var(--pixel-shape);

  cursor: pointer;

  transition:
    transform 300ms ease,
    background-color 300ms ease,
    color 300ms ease,
    border-color 300ms ease;
}

.selection-card:hover {
  color: var(--bg-main);

  background-color: var(--accent-cyan);

  border-color: var(--accent-cyan);

  transform: translate(-3px, -3px);

  box-shadow: 9px 9px 0 0 var(--shadow-color);
}

.selection-text {
  font-size: 22px;
  letter-spacing: 2px;
  text-transform: uppercase;
}

/* ============================================================
   RESULT CONTAINER - SCROLLING
   ============================================================ */

#result-container {
  position: relative;

  width: 50vw;

  /*
    The container has a fixed usable height.
    When its content becomes taller than this,
    the entire container can scroll vertically.
  */
  height: 500px;

  max-height: calc(85vh - 30px);

  min-height: 0;

  display: flex;

  flex-direction: column;

  padding: 20px 40px 0 40px;

  background-color: black;

  border: 3px solid #313244;

  box-shadow: 12px 12px 0 0 var(--shadow-color);

  clip-path: var(--pixel-shape);

  /*
    This is the important part.
    The result container itself becomes scrollable.
  */
  overflow-y: auto;

  overflow-x: hidden;

  /*
    Keeps the scrollbar from changing the layout width.
  */
  scrollbar-gutter: stable;

  transition:
    border-color 400ms ease,
    transform 400ms ease;
}

#result-container:hover,
#result-container.is-active {
  transform: scale(1.01);

  border-color: var(--accent-cyan);
}

/* Scrollbar */

#result-container::-webkit-scrollbar {
  width: 16px;
}

#result-container::-webkit-scrollbar-track {
  background: var(--bg-main);
}

#result-container::-webkit-scrollbar-thumb {
  background: var(--accent-blue);

  border-radius: 0;
}

#result-container::-webkit-scrollbar-thumb:hover {
  background: var(--accent-cyan);
  border-radius: 10px;
  border: 4px solid transparent;
  background-clip: padding-box;
}

/* Firefox */

#result-container {
  scrollbar-width: thin;

  scrollbar-color: var(--accent-blue) var(--bg-main);
}

/* ============================================================
   RESULT WRAPPER
   ============================================================ */

.result-wrapper {
  opacity: 0;

  transition: opacity 600ms ease;

  pointer-events: none;

  display: flex;

  flex-direction: column;

  height: 100%;
}

.result-wrapper.is-visible {
  opacity: 1;

  pointer-events: auto;
}

.result-heading {
  color: var(--accent-gold);

  margin-bottom: 30px;

  font-size: 24px;
}

.result-description {
  font-size: 22px;

  letter-spacing: 2px;

  line-height: 1.8;

  color: var(--text-main);

  flex-grow: 1;
}

.result-prompt {
  font-size: 28px;

  color: var(--accent-cyan);

  margin-top: 40px;

  animation: pulse 2s infinite;
}

@keyframes pulse {
  0%,
  100% {
    opacity: 1;
  }

  50% {
    opacity: 0.5;
  }
}

/* ============================================================
   SD DIRECTORY
   ============================================================ */

#sd-directory {
  opacity: 0;

  transition: opacity 600ms ease;

  /*
    Allow the directory to naturally grow.
    The parent result-container handles scrolling.
  */
  display: flex;

  flex-direction: column;

  min-height: 100%;
}

#sd-directory.is-visible {
  opacity: 1;
}

#sd-directory ul {
  list-style: none;

  padding-left: 18px;

  margin: 0;
}

#sd-directory li {
  position: relative;

  list-style-type: none;
}

#sd-directory .file::before {
  content: "└─ ";

  font-family: monospace;

  color: var(--accent-cyan);

  font-weight: bold;
}

.folder {
  display: inline-block;

  font-size: 28px;

  color: var(--accent-gold);

  margin-bottom: 15px;
}

.file {
  display: inline-block;

  margin-bottom: 10px;
}

.options-container {
  display: flex;

  position: sticky;

  left: 0;

  bottom: 0;

  justify-content: center;

  flex-shrink: 0;

  gap: 10px;

  padding: 15px 10px 30px 10px;

  margin-top: 20px;

  background-color: black;
}

.result-button {
  font-size: 18px;

  letter-spacing: 3px;

  width: 180px;

  height: 70px;

  background-color: transparent;

  clip-path: var(--pixel-shape);

  box-shadow: 6px 6px 0 0 var(--shadow-color);

  cursor: pointer;

  margin: 0 20px;

  transition: transform 300ms ease;
}

.result-button:hover {
  transform: translate(-3px, -3px);
}

.size {
  font-size: 22px;

  color: var(--accent-cyan);

  margin-left: 20px;
}

#add-file {
  color: var(--soft-blue);

  border: 3px solid var(--soft-blue);
}

#add-file:hover {
  color: var(--bg-main);

  background-color: var(--soft-blue);
}

#remove-file {
  color: var(--soft-red);

  border: 3px solid var(--soft-red);
}

#remove-file:hover {
  color: var(--bg-main);

  background-color: var(--soft-red);
}

#download-file {
  color: #28a745;

  border: 3px solid #28a745;
}

#download-file:hover {
  color: var(--bg-main);

  background-color: #28a745;
}

/* ============================================================
   HIDDEN ITEMS
   ============================================================ */

#sd-directory-list li.hidden-item {
  display: none;
}

#result-container.show-hidden #sd-directory-list li.hidden-item {
  display: list-item;
}

/* ============================================================
   ADD / REMOVE / DOWNLOAD MODES
   ============================================================ */

.add-item-btn {
  display: none;

  margin-right: 6px;

  cursor: pointer;

  background: #28a745;

  color: white;

  border: none;

  border-radius: 3px;

  font-weight: bold;

  padding: 0 4px;
}

#sd-directory.is-adding .add-item-btn {
  display: inline-block;
}

.add-item-btn {
  padding: 5px 10px;
}

#sd-directory.is-adding span.folder {
  cursor: pointer;

  border-bottom: 1px dashed var(--soft-blue);
}

#sd-directory.is-adding span.folder:hover {
  background-color: rgba(66, 116, 217, 0.2);

  border-radius: 3px;
}

#sd-directory.is-adding span.file,
#sd-directory.is-adding span.size {
  cursor: default;

  border-bottom: none;

  background-color: transparent;
}

#sd-directory.is-removing span.folder,
#sd-directory.is-removing span.file {
  cursor: pointer;

  border-bottom: 1px dashed var(--soft-red);
}

#sd-directory.is-removing span.folder:hover,
#sd-directory.is-removing span.file:hover {
  background-color: rgba(208, 49, 30, 0.2);

  border-radius: 3px;
}

#sd-directory.is-downloading span.file {
  cursor: pointer;

  border-bottom: 1px dashed #28a745;
}

#sd-directory.is-downloading span.file:hover {
  background-color: rgba(40, 167, 69, 0.2);

  border-radius: 3px;
}

#sd-directory.is-downloading span.folder {
  cursor: default;

  border-bottom: none;

  background-color: transparent;
}

/* ============================================================
   DYNAMIC FETCH WRAPPER
   ============================================================ */

#dynamic-fetch-wrapper {
  display: flex;

  flex-direction: column;

  flex: 1;

  min-height: 0;

  width: 100%;
}

/* ============================================================
   MODAL
   ============================================================ */

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

  padding: 25px;

  width: 320px;

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

  font-size: 20px;
}

.modal-step {
  display: flex;

  flex-direction: column;

  gap: 15px;

  opacity: 1;

  transition: opacity 300ms ease;
}

.modal-text {
  text-align: center;

  margin: 0;

  font-size: 14px;

  color: var(--text-main);
}

.highlight-text {
  color: var(--accent-cyan);
}

.modal-btn-group {
  display: flex;

  justify-content: space-between;

  gap: 15px;
}

.modal-btn-group.mt-10 {
  margin-top: 10px;
}

.modal-btn {
  width: 100%;

  height: 45px;

  font-size: 16px;

  margin: 0;

  border-width: 2px;
}

.modal-btn.small {
  height: 40px;

  font-size: 14px;
}

.btn-sibling {
  border-color: var(--soft-blue);

  color: var(--soft-blue);
}

.btn-child {
  border-color: var(--accent-gold);

  color: var(--accent-gold);
}

.btn-type {
  border-color: var(--accent-blue);

  color: var(--accent-cyan);
}

.btn-type.is-active {
  background-color: var(--accent-blue);

  color: var(--bg-main);
}

.btn-cancel {
  border-color: var(--soft-red);

  color: var(--soft-red);
}

.btn-submit {
  border-color: var(--soft-blue);

  color: var(--soft-blue);
}

.modal-btn:hover:not(.is-active) {
  background: rgba(255, 255, 255, 0.05);

  transform: translate(-2px, -2px);
}

.modal-input,
.modal-textarea {
  background: var(--bg-main);

  border: 2px solid var(--accent-blue);

  color: var(--text-main);

  padding: 12px;

  font-family: inherit;

  outline: none;

  clip-path: var(--pixel-shape);

  transition: border-color 200ms ease;

  letter-spacing: 1px;
}

.modal-input {
  font-size: 16px;
}

.modal-textarea {
  font-size: 14px;

  height: 100px;

  resize: none;
}

.modal-input.is-error {
  border-color: var(--soft-red);

  animation: shake 300ms;
}

.d-none {
  display: none !important;
}

.opacity-0 {
  opacity: 0 !important;
}

@keyframes shake {
  0%,
  100% {
    transform: translateX(0);
  }

  25% {
    transform: translateX(-5px);
  }

  75% {
    transform: translateX(5px);
  }
}

/* ============================================================
   DROP ZONE
   ============================================================ */

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

#drop-zone.dragover {
  background-color: #e2e6ea;

  border-color: #0056b3;
}

/* ============================================================
   UPLOAD PROGRESS
   ============================================================ */

#upload-progress-container {
  display: flex;

  flex-direction: column;

  justify-content: center;

  align-items: center;

  width: 100%;

  padding: 20px 0;
}

#upload-progress-container svg circle {
  transition: stroke-dashoffset 0.3s ease;
}

#upload-progress-container text {
  font-family: "Raw Pixel", monospace, sans-serif;

  letter-spacing: 1px;
}

.upload-filename {
  color: var(--accent-gold);

  font-size: 14px;

  letter-spacing: 1px;

  margin-top: 35px;

  text-align: center;

  word-break: break-all;
}

/* ============================================================
   PIXEL RING
   ============================================================ */

.pixel-ring {
  fill: none;

  stroke: #333;

  stroke-width: 8px;

  stroke-linecap: butt;

  stroke-linejoin: miter;
}

.pixel-ring.progress {
  stroke: var(--accent-cyan);

  stroke-dasharray: 100;

  stroke-dashoffset: 100;

  transition: stroke-dashoffset 0.3s ease;
}

/* ============================================================
   SONG METADATA
   ============================================================ */

#song-metadata {
  display: flex;

  flex-direction: column;

  gap: 10px;
}

/* ============================================================
   SHOW HIDDEN BUTTON
   ============================================================ */

.toggle-hidden-btn {
  clip-path: var(--pixel-shape);

  position: sticky;

  top: 0;

  align-self: flex-end;

  z-index: 10;

  background: var(--bg-main);

  border: 2px solid var(--accent-cyan);

  color: var(--accent-cyan);

  padding: 10px;

  cursor: pointer;

  font-family: inherit;

  font-size: 12px;

  transition:
    background 0.2s,
    color 0.2s;

  flex-shrink: 0;
}

.toggle-hidden-btn:hover {
  background: var(--accent-cyan);

  color: #000;
}

</style>
    <script
      src="https://cdnjs.cloudflare.com/ajax/libs/jsmediatags/3.9.5/jsmediatags.min.js"
      defer
    ></script>
    
  </head>
  <body>
    <header class="header-area">
      <a target="_blank" href="https://github.com/renx-byte"
        ><h1 id="typewriter-heading"></h1
      ></a>
    </header>

    <main class="main-content">
      <section class="selection-area">
        <div
          class="selection-card"
          data-title="SD CARD"
          data-description="Explore the contents of Orpheus's SD card in one place. Browse through your stored music, albums, playlists, and other files, while keeping track of everything available on the device. Select songs to play them directly, navigate through folders, and manage your music library without needing to remove the SD card. This section serves as your central file browser for everything stored locally on Orpheus."
        >
          <h5 class="selection-text">SD Card</h5>
        </div>

        <div
          class="selection-card"
          data-title="UPLOAD"
          data-description="Upload your music directly to Orpheus and keep your library organized without needing to access the SD card manually. Add songs along with their name, cover image, artist, album, and other details, ensuring every track is properly identified and displayed on the device. This section provides a simple way to upload and manage new music while keeping your Orpheus library clean, organized, and ready to play."
        >
          <h5 class="selection-text">Upload</h5>
        </div>

        <div
          class="selection-card"
          data-title="MONITOR"
          data-description="Monitor Orpheus from one place with real-time system information and activity logs. Keep track of important details such as battery level, storage usage, system status, connectivity, and other device information, while viewing logs to help you understand what Orpheus is doing in the background. This section serves as your central terminal for monitoring, diagnosing, and keeping an eye on the overall health of the device."
        >
          <h5 class="selection-text">Terminal</h5>
        </div>
      </section>

      <section class="result-area">
        <div class="result-container" id="result-container">
          <!-- Toggle button for hidden items -->
          <button id="toggle-hidden-btn" class="toggle-hidden-btn">
            Show Hidden
          </button>

          <div class="result-wrapper" id="result-wrapper">
            <h5 class="result-heading" id="result-heading"></h5>
            <div class="description-container">
              <p class="result-description" id="result-description"></p>
              <h5 class="result-prompt">CLICK TO ENTER...</h5>
            </div>
          </div>

          <!-- Static container for dynamic content (SD card, etc.) -->
          <div id="dynamic-fetch-wrapper" class="d-none">
            <!-- SD Directory section (hidden by default) -->
            <div id="sd-directory" class="d-none">
              <ul id="sd-directory-list"></ul>
              <div class="options-container">
                <button class="result-button" id="add-file">ADD ITEM</button>
                <button class="result-button" id="remove-file">
                  REMOVE ITEM
                </button>
                <button class="result-button" id="download-file">
                  GET ITEM
                </button>
              </div>
            </div>

            <!-- Placeholder for other sections -->
            <div id="placeholder-section" class="d-none">
              <h2>Coming soon</h2>
            </div>
          </div>
        </div>
      </section>
    </main>

    <!-- Modal markup (static) -->
    <div id="custom-modal-overlay" class="modal-overlay">
      <div id="custom-modal" class="modal-container">
        <h5 class="modal-heading">ADD NEW ITEM</h5>

        <!-- Step 1: Placement -->
        <div id="modal-step-1" class="modal-step">
          <p class="modal-text">
            Placement relative to
            <span class="highlight-text" id="modal-target-name"></span>
          </p>

          <div class="modal-btn-group">
            <button
              id="btn-sibling"
              class="result-button modal-btn btn-sibling"
            >
              SIBLING
            </button>
            <button id="btn-child" class="result-button modal-btn btn-child">
              CHILD
            </button>
          </div>
        </div>

        <!-- Step 2: Details -->
        <div id="modal-step-2" class="modal-step d-none opacity-0">
          <div class="modal-btn-group">
            <button
              id="btn-folder"
              class="result-button modal-btn small btn-type"
            >
              FOLDER
            </button>
            <button
              id="btn-file"
              class="result-button modal-btn small btn-type"
            >
              FILE
            </button>
            <button
              id="btn-upload"
              class="result-button modal-btn small btn-type"
            >
              UPLOAD
            </button>
          </div>

          <input
            id="modal-input-name"
            class="modal-input"
            type="text"
            placeholder="Enter Name..."
            autocomplete="off"
          />
          <textarea
            id="modal-input-content"
            class="modal-textarea d-none"
            placeholder="Enter file content (optional)..."
          ></textarea>

          <div id="song-metadata">
            <input
              id="song-name"
              class="modal-input metadata-input"
              type="text"
              placeholder="Enter Song Name..."
              autocomplete="off"
            />
            <input
              id="artist-name"
              class="modal-input metadata-input"
              type="text"
              placeholder="Enter Artist Name..."
              autocomplete="off"
            />
            <input
              id="album-name"
              class="modal-input metadata-input"
              type="text"
              placeholder="Enter Album Name..."
              autocomplete="off"
            />
            <input
              id="release-year"
              class="modal-input metadata-input"
              type="number"
              placeholder="Enter Release Year..."
              autocomplete="off"
            />
            <input
              id="duration"
              class="modal-input metadata-input"
              type="text"
              placeholder="Enter Duration..."
              autocomplete="off"
            />
          </div>

          <div id="drop-zone" class="d-none">
            <p>CLICK TO UPLOAD</p>
            <input type="file" id="file-input" hidden />
          </div>

          <div id="upload-progress-container" class="d-none">
            <svg width="120" height="120" viewBox="0 0 120 120">
              <circle
                cx="60"
                cy="60"
                r="54"
                fill="none"
                stroke="#333"
                stroke-width="8"
              />
              <circle
                id="progress-circle"
                cx="60"
                cy="60"
                r="54"
                fill="none"
                stroke="var(--accent-cyan)"
                stroke-width="8"
                stroke-linecap="round"
                stroke-dasharray="339.292"
                stroke-dashoffset="339.292"
                transform="rotate(-90 60 60)"
              />
              <text
                x="60"
                y="60"
                text-anchor="middle"
                dy="0.35em"
                fill="var(--accent-cyan)"
                font-size="18"
                id="progress-percent"
              >
                0%
              </text>
            </svg>
            <p id="upload-filename" class="upload-filename"></p>
          </div>

          <div class="modal-btn-group mt-10">
            <button id="btn-cancel" class="result-button modal-btn btn-cancel">
              CANCEL
            </button>
            <button id="btn-submit" class="result-button modal-btn btn-submit">
              CREATE
            </button>
          </div>
        </div>
      </div>
    </div>
  <script type="module">
// ============================================================
// Typewriter Effect
// ============================================================

import { ID3Writer } from "https://cdn.jsdelivr.net/npm/browser-id3-writer@6.4.0/dist/browser-id3-writer.mjs";

const initTypewriter = () => {
  const heading = document.getElementById("typewriter-heading");
  const phrases = ["renx-byte...", "Test ENV..."];

  let phraseIndex = 0;
  let charIndex = 0;
  let isDeleting = false;

  const typeSpeed = 200;
  const eraseSpeed = 200;
  const pauseDelay = 1500;

  function typeLoop() {
    const currentText = phrases[phraseIndex];

    if (!isDeleting && charIndex <= currentText.length) {
      heading.textContent = currentText.substring(0, charIndex) || "\u00A0";
      charIndex++;
      setTimeout(typeLoop, typeSpeed);
    } else if (!isDeleting && charIndex > currentText.length) {
      isDeleting = true;
      setTimeout(typeLoop, pauseDelay);
    } else if (isDeleting && charIndex >= 0) {
      heading.textContent = currentText.substring(0, charIndex) || "\u00A0";
      charIndex--;
      setTimeout(typeLoop, eraseSpeed);
    } else {
      isDeleting = false;
      charIndex = 0;
      phraseIndex = (phraseIndex + 1) % phrases.length;
      setTimeout(typeLoop, 500);
    }
  }

  typeLoop();
};

initTypewriter();

// ============================================================
// Result Container (Hover / Click)
// ============================================================
const resultContainer = document.getElementById("result-container");
const resultWrapper = document.getElementById("result-wrapper");
const resultHeading = document.getElementById("result-heading");
const resultDescription = document.getElementById("result-description");
const selectionCards = document.querySelectorAll(".selection-card");

let clickFlag = false;

function showResult(title, description) {
  if (!clickFlag) {
    resultWrapper.style.display = "";
    resultHeading.textContent = title + " INTERFACE";
    resultDescription.textContent = description;
    resultWrapper.classList.add("is-visible");
    resultContainer.classList.add("is-active");
  }
}

function hideResult() {
  if (!clickFlag) {
    resultWrapper.classList.remove("is-visible");
    resultContainer.classList.remove("is-active");
  }

  const sdDirectory = document.getElementById("sd-directory");
  if (sdDirectory && !clickFlag) {
    sdDirectory.classList.remove("is-visible");
    // Optionally hide completely after transition
    setTimeout(() => {
      if (!clickFlag) {
        sdDirectory.classList.add("d-none");
        const dynamicWrapper = document.getElementById("dynamic-fetch-wrapper");
        if (dynamicWrapper) dynamicWrapper.classList.add("d-none");
      }
    }, 600);
  }
}

// ============================================================
// Upload Helper
// ============================================================
async function uploadSong(data, iteration, totalIterations, songName) {
  try {
    const formData = new FormData();
    formData.append("file", data, songName);

    const response = await fetch("/upload_song", {
      method: "POST",
      headers: {
        "X-Song-Name": songName,
        "X-Chunk-Index": iteration.toString(),
        "X-Total-Chunks": totalIterations.toString(),
      },
      body: formData,
    });

    if (!response.ok) return "error";
    return await response.text();
  } catch (error) {
    return "error";
  }
}

async function uploadMetadata(metadata) {
  try {
    const response = await fetch("/upload_metadata", {
      method: "POST",
      headers: {
        "Content-Type": "application/json",
      },
      body: JSON.stringify(metadata),
    });

    if (!response.ok) return "error";
    return await response.text();
  } catch (error) {
    return "error";
  }
}

async function uploadCover(coverFile, songName) {
  try {
    const formData = new FormData();
    formData.append("file", coverFile, "cover.png");

    const response = await fetch("/upload_cover", {
      method: "POST",
      headers: {
        "X-Song-Name": songName, // optional, helps associate cover with song on ESP32
      },
      body: formData,
    });

    if (!response.ok) return "error";
    return await response.text();
  } catch (error) {
    return "error";
  }
}

// ============================================================
// Modal Logic (unchanged, using static HTML in index.html)
// ============================================================
function openCustomModal(targetName, isFolderTarget) {
  return new Promise((resolve) => {
    const overlay = document.getElementById("custom-modal-overlay");
    const step1 = document.getElementById("modal-step-1");
    const step2 = document.getElementById("modal-step-2");
    const targetNameSpan = document.getElementById("modal-target-name");

    const elements = {
      sibling: document.getElementById("btn-sibling"),
      child: document.getElementById("btn-child"),
      folder: document.getElementById("btn-folder"),
      file: document.getElementById("btn-file"),
      upload: document.getElementById("btn-upload"),
      metadata: document.getElementById("song-metadata"),
      dropzone: document.getElementById("drop-zone"),
      fileInput: document.getElementById("file-input"),
      name: document.getElementById("modal-input-name"),
      content: document.getElementById("modal-input-content"),
      cancel: document.getElementById("btn-cancel"),
      submit: document.getElementById("btn-submit"),
      progressContainer: document.getElementById("upload-progress-container"),
      progressCircle: document.getElementById("progress-circle"),
      progressPercent: document.getElementById("progress-percent"),
      uploadFilename: document.getElementById("upload-filename"),
    };

    // Reset modal state
    elements.name.value = "";
    elements.content.value = "";
    elements.fileInput.value = "";
    elements.progressContainer.classList.add("d-none");
    elements.dropzone.classList.remove("d-none");
    elements.submit.classList.remove("d-none");
    elements.cancel.classList.remove("d-none");
    elements.content.classList.add("d-none");
    elements.name.classList.remove("d-none");

    targetNameSpan.textContent = targetName;

    let asChild = false;
    let selectedType = "folder";

    if (!isFolderTarget) {
      step1.classList.add("d-none");
      step2.classList.remove("d-none", "opacity-0");
      selectedType = "file";
      elements.name.focus();
    } else {
      step1.classList.remove("d-none", "opacity-0");
      step2.classList.add("d-none", "opacity-0");
    }

    overlay.classList.add("is-visible");

    function cleanup() {
      overlay.classList.remove("is-visible");
    }

    function expandToStep2() {
      step1.classList.add("opacity-0");
      setTimeout(() => {
        step1.classList.add("d-none");
        step2.classList.remove("d-none");
        void step2.offsetWidth;
        step2.classList.remove("opacity-0");
        if (selectedType !== "upload") elements.name.focus();
      }, 300);
    }

    function selectType(type) {
      selectedType = type;
      elements.folder.classList.toggle("is-active", selectedType === "folder");
      elements.file.classList.toggle("is-active", selectedType === "file");
      elements.upload.classList.toggle("is-active", selectedType === "upload");

      if (selectedType === "folder") {
        elements.name.classList.remove("d-none");
        elements.dropzone.classList.add("d-none");
        elements.content.classList.add("d-none");
        elements.metadata.classList.add("d-none");
      } else if (selectedType === "file") {
        elements.name.classList.remove("d-none");
        elements.dropzone.classList.add("d-none");
        elements.content.classList.remove("d-none");
        elements.metadata.classList.add("d-none");
      } else if (selectedType === "upload") {
        elements.content.classList.add("d-none");
        elements.name.classList.add("d-none");
        elements.dropzone.classList.remove("d-none");
        elements.metadata.classList.remove("d-none");
      }
    }

    function submitForm() {
      const name = elements.name.value.trim();
      if (!name) {
        elements.name.classList.add("is-error");
        setTimeout(() => elements.name.classList.remove("is-error"), 300);
        return;
      }
      cleanup();
      resolve({
        asChild,
        itemType: selectedType,
        itemName: name,
        fileContent: selectedType === "file" ? elements.content.value : "",
      });
    }

    elements.fileInput.onchange = async (event) => {
      const songNameInput = document.getElementById("song-name").value;
      const songArtistInput = document.getElementById("artist-name").value;
      const songAlbumInput = document.getElementById("album-name").value;
      const songReleaseInput = document.getElementById("release-year").value;
      const songDurationInput = document.getElementById("duration").value;

      const chunkSize = 32768;
      const tempFile = event.target.files[0];
      if (!tempFile) return;

      let pictureWrapper;
      let pictureFormat;

      const tag = await new Promise((resolve, reject) => {
        jsmediatags.read(tempFile, {
          onSuccess: resolve,
          onError: reject,
        });
      });

      pictureWrapper = tag.tags.picture.data;
      pictureFormat = tag.tags.picture.format;

      const blob = new Blob([new Uint8Array(pictureWrapper)], {
        type: pictureFormat,
      });

      const coverPng = new File([blob], "cover.png", {
        type: "image/png",
      });

      const metadata = {
        name: songNameInput,
        artist: songArtistInput,
        album: songAlbumInput,
        releaseYear: songReleaseInput,
        duration: songDurationInput,
      };

      // Show progress UI (optional: you might want to indicate metadata/cover upload)
      elements.dropzone.classList.add("d-none");
      elements.submit.classList.add("d-none");
      elements.cancel.classList.add("d-none");
      elements.progressContainer.classList.remove("d-none");
      elements.uploadFilename.textContent = tempFile.name;
      elements.progressCircle.style.strokeDashoffset = "339.292";
      elements.progressPercent.textContent = "0%";

      // 1. Send metadata
      const metadataResult = await uploadMetadata(metadata);
      if (metadataResult === "error") {
        console.log("Metadata upload failed");
        resetUploadUI();
        return;
      }

      // 2. Send cover image
      const coverResult = await uploadCover(coverPng, tempFile.name);
      if (coverResult === "error") {
        console.log("Cover upload failed");
        resetUploadUI();
        return;
      }

      // 3. Continue with song chunk upload as before
      const arrayBuffer = await tempFile.arrayBuffer();
      const writer = new ID3Writer(arrayBuffer);

      writer
        .setFrame("TIT2", songNameInput)
        .setFrame("TPE1", [songArtistInput])
        .setFrame("TALB", songAlbumInput)
        .setFrame("TCON", ["Music"])
        .setFrame("TYER", songReleaseInput)
        .setFrame("APIC", {
          type: 3,
          data: new Uint8Array(pictureWrapper).buffer,
          description: "cover",
        });

      writer.addTag();

      const newSong = new File([writer.getBlob()], tempFile.name, {
        type: "audio/mpeg",
      });

      const songName = newSong.name;
      const songSize = newSong.size;
      const totalIterations = Math.ceil(songSize / chunkSize);

      // Reset progress for song upload (metadata/cover progress may have altered it)
      elements.progressCircle.style.strokeDashoffset = "339.292";
      elements.progressPercent.textContent = "0%";

      for (let i = 0; i < totalIterations; i++) {
        const start = i * chunkSize;
        const end = Math.min(start + chunkSize, songSize);
        const chunk = newSong.slice(start, end);

        const result = await uploadSong(chunk, i, totalIterations, songName);
        if (result == "error") {
          console.log("aborted at chunk: ", i);
          resetUploadUI();
          return;
        }

        const percent = Math.round(((i + 1) / totalIterations) * 100);
        elements.progressPercent.textContent = `${percent}%`;
        const circleLength = 339.292;
        const offset = circleLength - (percent / 100) * circleLength;
        elements.progressCircle.style.strokeDashoffset = offset;
      }

      console.log("Upload complete for file: ", songName);
      cleanup();

      await refreshSdDirectory();

      // Helper function to reset UI after error (extracted for reuse)
      function resetUploadUI() {
        elements.progressContainer.classList.add("d-none");
        elements.dropzone.classList.remove("d-none");
        elements.submit.classList.remove("d-none");
        elements.cancel.classList.remove("d-none");
        elements.fileInput.value = "";
      }
    };

    elements.dropzone.onclick = (e) => {
      e.stopPropagation();
      elements.fileInput.click();
    };

    elements.sibling.onclick = () => {
      asChild = false;
      expandToStep2();
    };
    elements.child.onclick = () => {
      asChild = true;
      expandToStep2();
    };
    elements.folder.onclick = () => selectType("folder");
    elements.file.onclick = () => selectType("file");
    elements.upload.onclick = () => selectType("upload");
    elements.cancel.onclick = () => {
      cleanup();
      resolve(null);
    };
    elements.submit.onclick = submitForm;
    elements.name.onkeydown = (e) => {
      if (e.key === "Enter") submitForm();
    };

    if (!isFolderTarget) selectType("file");
    else selectType("folder");
  });
}

// ============================================================
// Directory Rendering (only dynamic list items)
// ============================================================
function buildDirectoryDOM(node, container) {
  const ul = document.createElement("ul");

  if (node.type === "folder") {
    node.children?.forEach((child) => {
      const li = document.createElement("li");

      // Check if name starts with "_" and mark as hidden item
      if (child.name.startsWith("_")) {
        li.classList.add("hidden-item");
      }

      if (child.type === "folder") {
        const span = document.createElement("span");
        span.className = "folder";
        span.textContent = child.name + "/";
        li.appendChild(span);
        buildDirectoryDOM(child, li); // recursion
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

      ul.appendChild(li);
    });
  }

  container.appendChild(ul);
}

function renderDirectory(data) {
  const listElement = document.getElementById("sd-directory-list");
  if (!listElement) return;

  listElement.innerHTML = ""; // clear existing list
  buildDirectoryDOM(data, listElement);
}

async function refreshSdDirectory() {
  try {
    const response = await fetch("/sd_directory");
    if (!response.ok) throw new Error("Failed to fetch directory");
    const data = await response.json();
    renderDirectory(data);

    // Show SD directory and its wrapper
    const sdDirectory = document.getElementById("sd-directory");
    const dynamicWrapper = document.getElementById("dynamic-fetch-wrapper");
    if (sdDirectory) {
      sdDirectory.classList.remove("d-none");
      // Trigger opacity transition
      requestAnimationFrame(() => {
        sdDirectory.classList.add("is-visible");
      });
    }
    if (dynamicWrapper) {
      dynamicWrapper.classList.remove("d-none");
    }
  } catch (err) {
    console.error("Directory refresh failed:", err);
  }
}

// ============================================================
// SD Directory Interaction Listener
// ============================================================
function sdDirectoryListener() {
  const sdDirectory = document.getElementById("sd-directory");
  if (!sdDirectory) return;

  const addBtn = document.getElementById("add-file");
  const removeBtn = document.getElementById("remove-file");
  const downloadBtn = document.getElementById("download-file");

  function resetModes() {
    sdDirectory.classList.remove("is-adding", "is-removing", "is-downloading");
    if (addBtn) addBtn.textContent = "ADD ITEM";
    if (removeBtn) removeBtn.textContent = "REMOVE ITEM";
    if (downloadBtn) downloadBtn.textContent = "GET ITEM";
  }

  if (addBtn) {
    addBtn.onclick = (e) => {
      e.stopPropagation();
      if (sdDirectory.classList.contains("is-adding")) {
        resetModes();
      } else {
        resetModes();
        sdDirectory.classList.add("is-adding");
        addBtn.textContent = "CANCEL ADD";
      }
    };
  }

  if (removeBtn) {
    removeBtn.onclick = (e) => {
      e.stopPropagation();
      if (sdDirectory.classList.contains("is-removing")) {
        resetModes();
      } else {
        resetModes();
        sdDirectory.classList.add("is-removing");
        removeBtn.textContent = "CANCEL REMOVE";
      }
    };
  }

  if (downloadBtn) {
    downloadBtn.onclick = (e) => {
      e.stopPropagation();
      if (sdDirectory.classList.contains("is-downloading")) {
        resetModes();
      } else {
        resetModes();
        sdDirectory.classList.add("is-downloading");
        downloadBtn.textContent = "CANCEL GET";
      }
    };
  }

  sdDirectory.onclick = async (event) => {
    const target = event.target;
    const isFolder = target.classList.contains("folder");
    const isFile =
      target.classList.contains("file") || target.classList.contains("size");

    if (!isFolder && !isFile) return;

    // ADD MODE
    if (sdDirectory.classList.contains("is-adding")) {
      if (!isFolder) return;
      event.stopPropagation();

      const clickedLi = target.closest("li");
      let targetName = "";
      const folderSpan = clickedLi.querySelector(".folder");
      if (folderSpan)
        targetName = folderSpan.textContent.trim().replace(/\/$/, "");

      const modalResult = await openCustomModal(targetName, !!folderSpan);
      if (!modalResult) return;

      const { asChild, itemType, itemName, fileContent } = modalResult;
      resetModes();

      let payloadParent = "root";
      if (asChild && folderSpan) {
        payloadParent = targetName;
      } else {
        const parentLi = clickedLi.parentElement.closest("li");
        if (parentLi) {
          const parentFolderSpan = parentLi.querySelector(".folder");
          if (parentFolderSpan)
            payloadParent = parentFolderSpan.textContent
              .trim()
              .replace(/\/$/, "");
        }
      }
      payloadParent = payloadParent.replace(/\/$/, "");

      const payload = {
        name: itemName,
        type: itemType,
        ...(itemType === "file" ? { content: fileContent } : {}),
        parent: payloadParent,
      };

      try {
        const response = await fetch("/create_payload", {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify(payload),
        });
        if (!response.ok) throw new Error("Create failed");
        await refreshSdDirectory();
      } catch (err) {
        console.error("Payload request failed:", err);
      }
    }
    // REMOVE MODE
    else if (sdDirectory.classList.contains("is-removing")) {
      event.stopPropagation();

      let clickedLi = target.closest("li");
      let pathParts = [];
      let currentLi = clickedLi;

      while (currentLi && currentLi.closest("#sd-directory")) {
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

      if (
        !confirm(`Are you sure you want to permanently delete:\n${fullPath}?`)
      )
        return;

      resetModes();

      try {
        const response = await fetch("/remove_payload", {
          method: "POST",
          headers: { "Content-Type": "application/json" },
          body: JSON.stringify({ path: fullPath }),
        });
        if (!response.ok) throw new Error("Remove failed");
        await refreshSdDirectory();
      } catch (err) {
        console.error("Remove request failed:", err);
      }
    }
    // DOWNLOAD MODE
    else if (sdDirectory.classList.contains("is-downloading")) {
      if (!isFile) return;
      event.stopPropagation();

      let clickedLi = target.closest("li");
      let pathParts = [];
      let currentLi = clickedLi;

      while (currentLi && currentLi.closest("#sd-directory")) {
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
      window.location.href =
        "/download_file?path=" + encodeURIComponent(fullPath);
      resetModes();
    }
  };
}

// ============================================================
// Selection Card Event Listeners
// ============================================================
selectionCards.forEach((card) => {
  card.addEventListener("mouseenter", (event) => {
    const { title, description } = event.currentTarget.dataset;
    showResult(title, description);
  });

  card.addEventListener("mouseleave", () => {
    if (!clickFlag) hideResult();
  });

  card.addEventListener("click", (event) => {
    event.stopPropagation();
    clickFlag = true;

    resultWrapper.classList.remove("is-visible");
    resultWrapper.style.display = "none";
    resultContainer.classList.add("is-active");

    const title = event.currentTarget.dataset.title;
    const dynamicWrapper = document.getElementById("dynamic-fetch-wrapper");
    const sdDirectory = document.getElementById("sd-directory");
    const placeholder = document.getElementById("placeholder-section");

    // Hide all sections first
    if (sdDirectory) sdDirectory.classList.add("d-none");
    if (placeholder) placeholder.classList.add("d-none");
    if (dynamicWrapper) dynamicWrapper.classList.remove("d-none");

    if (title === "SD CARD") {
      // Show SD directory and fetch data
      sdDirectory.classList.remove("d-none");
      // Fetch and render directory
      refreshSdDirectory();
    } else {
      // Show placeholder for other sections
      placeholder.classList.remove("d-none");
    }
  });
});

// ============================================================
// Global Click Handler
// ============================================================
document.body.addEventListener("click", (event) => {
  if (
    event.target.closest("#result-container") ||
    event.target.closest("#custom-modal-overlay")
  ) {
    return;
  }
  if (clickFlag) {
    clickFlag = false;
    hideResult();
  }
});

// Toggle hidden items (directories starting with "_")
const toggleHiddenBtn = document.getElementById("toggle-hidden-btn");
if (toggleHiddenBtn) {
  toggleHiddenBtn.addEventListener("click", () => {
    const container = document.getElementById("result-container");
    container.classList.toggle("show-hidden");
    const isShowing = container.classList.contains("show-hidden");
    toggleHiddenBtn.textContent = isShowing ? "Hide Hidden" : "Show Hidden";
  });
}

sdDirectoryListener();

</script>
</body>
</html>

)rawliteral";

#endif // INDEX_HTML_H
