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

  /* Cohesive Modern Terminal Palette */
  --bg-main: #0a0b10; /* Deep dark slate background */
  --bg-panel: #1e1e2e; /* Slightly lighter elevated panel */

  --text-main: #cdd6f4; /* Soft off-white for high readability */

  --soft-red: #d0311e;
  --soft-blue: #4274d9;

  --accent-yellow: #ffb900;
  --accent-gold: #f9e2af; /* Soft gold for headings */
  --accent-cyan: #89dceb; /* Vibrant cyan for interactive elements */
  --accent-blue: #89b4fa; /* Deep blue for borders */

  --shadow-color: #11111b; /* Darker slate for shadows instead of harsh black */
}
/* ============================================================
   BACKGROUND OPTION 2: PARALLAX STARFIELD
   ============================================================ */
body::before,
body::after {
  content: "";
  position: fixed;
  top: 0;
  left: 0;
  width: 200vw; /* Double width so it can scroll seamlessly */
  height: 100vh;
  z-index: -1;
  pointer-events: none;
}

/* Foreground stars (larger, moving faster) */
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

/* Background stars (smaller, moving slower to create depth) */
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
    /* Moves the background exactly enough to seamlessly loop */
    transform: translate(59.4px, 59.4px);
  }
}

* {
  font-family: "Raw Pixel", monospace, sans-serif;
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

/* ============================================================
   HEADER AREA
   ============================================================ */
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

/* ============================================================
   MAIN LAYOUT
   ============================================================ */
.main-content {
  height: 85vh;
  display: flex;
  align-items: center;
}

.selection-area {
  display: flex;
  flex-direction: column;
  align-items: center;
  width: 30vw; /* Slightly tighter to bring elements closer */
}

.result-area {
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  width: 70vw;
}

/* ============================================================
   CARDS
   ============================================================ */
.selection-card {
  position: relative;
  display: flex;
  justify-content: center;
  align-items: center;
  min-width: 250px;
  height: 60px;
  margin: 15px 0;

  /* Sleek outlined look by default */
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
  color: var(--bg-main); /* Dark text on bright background */
  background-color: var(--accent-cyan);
  border-color: var(--accent-cyan);

  /* Physical push effect instead of just scaling */
  transform: translate(-3px, -3px);
  box-shadow: 9px 9px 0 0 var(--shadow-color);
}

.selection-text {
  font-size: 22px;
  letter-spacing: 2px;
  text-transform: uppercase;
}

/* ============================================================
   RESULT CONTAINER
   ============================================================ */
#result-container {
  position: relative;
  width: 50vw;
  min-height: 500px;
  display: flex;
  flex-direction: column;
  padding: 40px;

  background-color: #00000062;
  border: 3px solid #313244;
  box-shadow: 12px 12px 0 0 var(--shadow-color);

  clip-path: var(--pixel-shape);
  transition:
    border-color 400ms ease,
    transform 400ms ease;
}

#result-container:hover,
#result-container.is-active {
  /* cursor: pointer; */
  transform: scale(1.01);
  border-color: var(--accent-cyan);
}

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
  flex-grow: 1; /* Pushes the 'Click to enter' to the bottom */
}

.result-prompt {
  font-size: 28px;
  color: var(--accent-cyan);
  margin-top: 40px;
  animation: pulse 2s infinite;
}

/* Adds a subtle breathing effect to the call to action */
@keyframes pulse {
  0%,
  100% {
    opacity: 1;
  }
  50% {
    opacity: 0.5;
  }
}

#sd-directory {
  opacity: 0;
  transition: opacity 600ms ease;
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
  color: var(--accent-cyan); /* Subtle grey branch line */
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
  position: absolute;

  left: 50%;
  transform: translateX(-50%);

  bottom: 40px;
}

.result-button {
  font-size: 18px;
  letter-spacing: 3px;
  width: 180px;
  height: 70px;
  background-color: transparent;
  clip-path: var(--pixel-shape);

  box-shadow: 6px 6px 0 0 var(--shadow-color);
  clip-path: var(--pixel-shape);
  cursor: pointer;

  margin: 0 20px;
  transition: transform 300ms ease;
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

.result-button:hover {
  transform: translate(-3px, -3px);
}

/* Hide item add buttons by default */
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

/* Show + buttons when add mode is active */
#sd-directory.is-adding .add-item-btn {
  display: inline-block;
}

.add-item-btn {
  padding: 05px 10px;
}

/* When add mode is active, make elements look clickable */
#sd-directory.is-adding span.folder,
#sd-directory.is-adding span.file {
  cursor: pointer;
  border-bottom: 1px dashed #28a745; /* Green dashed line indicator */
}

/* Add a hover effect so they know exactly which item they are targeting */
#sd-directory.is-adding span.folder:hover,
#sd-directory.is-adding span.file:hover {
  background-color: rgba(40, 167, 69, 0.2);
  border-radius: 3px;
}

/* ============================================================
   CUSTOM MODAL STYLES
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

/* Button Variants */
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

/* Utility Classes */
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

</style>
    
  </head>
  <body>
    <header class="header-area">
      <a target="_blank" href="https://github.com/renx-byte"
        ><h1 id="typewriter-heading"></h1
      ></a>
    </header>

    <main class="main-content">
      <section class="selection-area">
        <!-- Using data attributes makes the JS completely dynamic and scalable -->
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
          <!-- <div id="sd-directory">
            <ul>
              <li>
                <span class="folder">System Volume Information/</span>
                <ul>
                  <li>
                    <span class="file">WPSettings.dat</span>
                    <span class="size">(0.0 kb)</span>
                  </li>
                  <li>
                    <span class="file">IndexerVolumeGuid</span>
                    <span class="size">(0.1 kb)</span>
                  </li>
                </ul>
              </li>
            </ul>
            <div class="options-container">
              <button class="result-button" id="add-file">ADD FILE</button>
              <button class="result-button" id="remove-file">
                REMOVE FILE
              </button>
            </div>
          </div> -->

          <div class="result-wrapper" id="result-wrapper">
            <h5 class="result-heading" id="result-heading"></h5>
            <div class="description-container">
              <p class="result-description" id="result-description"></p>
              <h5 class="result-prompt">CLICK TO ENTER...</h5>
            </div>
          </div>
        </div>
      </section>
    </main>
  <script>
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

    setTimeout(() => {
      const fetchWrapper = document.getElementById("dynamic-fetch-wrapper");

      if (!clickFlag && fetchWrapper) {
        fetchWrapper.remove();
      }
    }, 600);
  }
}

function openCustomModal(targetName, isFolderTarget) {
  return new Promise((resolve) => {
    const modalHTML = `
      <div id="custom-modal-overlay" class="modal-overlay">
        <div id="custom-modal" class="modal-container">
          <h5 class="modal-heading">ADD NEW ITEM</h5>
          
          <!-- Step 1: Placement -->
          <div id="modal-step-1" class="modal-step">
            <p class="modal-text">
              Placement relative to
              <span class="highlight-text">${targetName}</span>
            </p>

            <div class="modal-btn-group">
              <button id="btn-sibling" class="result-button modal-btn btn-sibling">
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
              <button id="btn-folder" class="result-button modal-btn small btn-type">
                FOLDER
              </button>

              <button id="btn-file" class="result-button modal-btn small btn-type">
                FILE
              </button>
            </div>
            
            <input
              id="modal-input-name"
              class="modal-input"
              type="text"
              placeholder="Enter Name..."
              autocomplete="off"
            >

            <textarea
              id="modal-input-content"
              class="modal-textarea d-none"
              placeholder="Enter file content (optional)..."
            ></textarea>

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
    `;

    document.body.insertAdjacentHTML("beforeend", modalHTML);

    const overlay = document.getElementById("custom-modal-overlay");
    const step1 = document.getElementById("modal-step-1");
    const step2 = document.getElementById("modal-step-2");

    const elements = {
      sibling: document.getElementById("btn-sibling"),
      child: document.getElementById("btn-child"),
      folder: document.getElementById("btn-folder"),
      file: document.getElementById("btn-file"),
      name: document.getElementById("modal-input-name"),
      content: document.getElementById("modal-input-content"),
      cancel: document.getElementById("btn-cancel"),
      submit: document.getElementById("btn-submit"),
    };

    let asChild = false;
    let isFolder = true;

    requestAnimationFrame(() => {
      overlay.classList.add("is-visible");
    });

    function cleanup() {
      overlay.classList.remove("is-visible");

      setTimeout(() => {
        overlay.remove();
      }, 300);
    }

    function expandToStep2() {
      step1.classList.add("opacity-0");

      setTimeout(() => {
        step1.classList.add("d-none");

        step2.classList.remove("d-none");

        void step2.offsetWidth;

        step2.classList.remove("opacity-0");

        elements.name.focus();
      }, 300);
    }

    function selectType(type) {
      isFolder = type === "folder";

      elements.folder.classList.toggle("is-active", isFolder);
      elements.file.classList.toggle("is-active", !isFolder);

      if (isFolder) {
        elements.content.classList.add("d-none");
      } else {
        elements.content.classList.remove("d-none");
      }
    }

    function submitForm() {
      const name = elements.name.value.trim();

      if (!name) {
        elements.name.classList.add("is-error");

        setTimeout(() => {
          elements.name.classList.remove("is-error");
        }, 300);

        return;
      }

      cleanup();

      resolve({
        asChild,
        createFolder: isFolder,
        itemName: name,
        fileContent: isFolder ? "" : elements.content.value,
      });
    }

    if (!isFolderTarget) {
      asChild = false;

      step1.classList.add("d-none");
      step2.classList.remove("d-none", "opacity-0");

      selectType("file");

      setTimeout(() => {
        elements.name.focus();
      }, 100);
    } else {
      elements.sibling.onclick = () => {
        asChild = false;
        expandToStep2();
      };

      elements.child.onclick = () => {
        asChild = true;
        expandToStep2();
      };

      selectType("folder");
    }

    elements.folder.onclick = () => {
      selectType("folder");
    };

    elements.file.onclick = () => {
      selectType("file");
    };

    elements.cancel.onclick = () => {
      cleanup();
      resolve(null);
    };

    elements.submit.onclick = submitForm;

    elements.name.addEventListener("keydown", (e) => {
      if (e.key === "Enter") {
        submitForm();
      }
    });
  });
}

// ============================================================
// SD CARD DIRECTORY LISTENER
// ============================================================
function sdDirectoryListener() {
  const addBtn = document.getElementById("add-file");
  const sdDirectory = document.getElementById("sd-directory");

  if (!addBtn || !sdDirectory) return;

  addBtn.addEventListener("click", (event) => {
    event.stopPropagation();

    sdDirectory.classList.toggle("is-adding");

    addBtn.textContent = sdDirectory.classList.contains("is-adding")
      ? "CANCEL ADD"
      : "ADD FILE";
  });

  sdDirectory.addEventListener("click", async (event) => {
    if (!sdDirectory.classList.contains("is-adding")) return;

    const target = event.target;

    const isFolder = target.classList.contains("folder");

    const isFile =
      target.classList.contains("file") || target.classList.contains("size");

    if (isFolder || isFile) {
      event.stopPropagation();

      const clickedLi = target.closest("li");

      let targetName = "";

      const folderSpan = clickedLi.querySelector(".folder");
      const fileSpan = clickedLi.querySelector(".file");

      if (folderSpan) {
        targetName = folderSpan.textContent.trim();
      } else if (fileSpan) {
        targetName = fileSpan.textContent.trim();
      }

      const modalResult = await openCustomModal(targetName, !!folderSpan);

      if (!modalResult) return;

      const { asChild, createFolder, itemName, fileContent } = modalResult;

      // Exit add mode
      sdDirectory.classList.remove("is-adding");
      addBtn.textContent = "ADD FILE";

      // Determine parent folder
      let payloadParent = "root";

      if (asChild && folderSpan) {
        // Targeted folder becomes the parent
        payloadParent = targetName;
      } else {
        // Sibling placement or file target
        const parentLi = clickedLi.parentElement.closest("li");

        if (parentLi) {
          const parentFolderSpan = parentLi.querySelector(".folder");

          if (parentFolderSpan) {
            payloadParent = parentFolderSpan.textContent.trim();
          }
        }
      }

      payloadParent = payloadParent.replace(/\/$/, "");

      const payload = {
        name: itemName,
        type: createFolder ? "folder" : "file",
        ...(createFolder ? {} : { content: fileContent }),
        parent: payloadParent,
      };

      console.log("Sending payload:", payload);

      fetch("/create_payload", {
        method: "POST",

        headers: {
          "Content-Type": "application/json",
        },

        body: JSON.stringify(payload),
      })
        .then((response) => response.json())

        .then((data) => {
          console.log("ESP32 Response:", data);
        })

        .catch((error) => {
          console.error("Payload request failed:", error);
        });
    }
  });
}

selectionCards.forEach((card) => {
  card.addEventListener("mouseenter", (event) => {
    const { title, description } = event.currentTarget.dataset;

    showResult(title, description);
  });

  card.addEventListener("mouseleave", () => {
    if (!clickFlag) {
      hideResult();
    }
  });

  card.addEventListener("click", (event) => {
    event.stopPropagation();

    clickFlag = true;

    resultWrapper.classList.remove("is-visible");
    resultWrapper.style.display = "none";

    resultContainer.classList.add("is-active");

    const title = event.currentTarget.dataset.title;

    fetch("/selection_click", {
      method: "POST",

      headers: {
        "Content-Type": "application/json",
      },

      body: JSON.stringify({
        title,
      }),
    })
      .then((response) => response.text())

      .then((html) => {
        let fetchWrapper = document.getElementById("dynamic-fetch-wrapper");

        if (!fetchWrapper) {
          fetchWrapper = document.createElement("div");

          fetchWrapper.id = "dynamic-fetch-wrapper";

          resultContainer.appendChild(fetchWrapper);
        }

        fetchWrapper.innerHTML = html;

        sdDirectoryListener();

        const sdDirectory = document.getElementById("sd-directory");

        if (sdDirectory) {
          requestAnimationFrame(() => {
            requestAnimationFrame(() => {
              sdDirectory.classList.add("is-visible");
            });
          });
        }
      })

      .catch((error) => {
        console.error("Selection request failed:", error);
      });
  });
});

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

</script>
</body>
</html>

)rawliteral";

#endif // INDEX_HTML_H
