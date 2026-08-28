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

body {
  font-family: "Raw Pixel", monospace, sans-serif;
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
  width: 50vw;
  min-height: 500px;
  display: flex;
  flex-direction: column;
  padding: 40px;

  background-color: var(--bg-panel);
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

</style>
    
  </head>
  <body>
    <header class="header-area">
      <h1 id="typewriter-heading"></h1>
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
                    <span class="file">📄 WPSettings.dat</span>
                    <span class="size">(0.0 kb)</span>
                  </li>
                  <li>
                    <span class="file">📄 IndexerVolumeGuid</span>
                    <span class="size">(0.1 kb)</span>
                  </li>
                </ul>
              </li>
            </ul>
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
// ============================================================
// TYPING EFFECT
// ============================================================
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
// CARD INTERACTION LOGIC
// ============================================================
const resultContainer = document.getElementById("result-container");
const resultWrapper = document.getElementById("result-wrapper");
const resultHeading = document.getElementById("result-heading");
const resultDescription = document.getElementById("result-description");
const selectionCards = document.querySelectorAll(".selection-card");

let click_flag = false;

/**
 * Updates DOM with card data and displays the hover UI
 */
function showResult(title, description) {
    if (!click_flag) {
        // Restore wrapper to document flow for hover state
        resultWrapper.style.display = ""; 
        
        resultHeading.textContent = title + " INTERFACE";
        resultDescription.textContent = description;

        resultWrapper.classList.add("is-visible");
        resultContainer.classList.add("is-active");
    }
}

/**
 * Hides the UI and gracefully clears fetched content
 */
function hideResult() {
    if (!click_flag) {
        resultWrapper.classList.remove("is-visible");
        resultContainer.classList.remove("is-active");
    }

    const sdDirectory = document.getElementById("sd-directory");
    if (sdDirectory && !click_flag) {
        sdDirectory.classList.remove("is-visible");
        
        // Clear fetched HTML safely after the CSS fade-out completes
        setTimeout(() => {
            const fetchWrapper = document.getElementById("dynamic-fetch-wrapper");
            if (!click_flag && fetchWrapper) {
                fetchWrapper.remove();
            }
        }, 600);
    }
}

// Dynamically assign event listeners to all cards
selectionCards.forEach((card) => {
    card.addEventListener("mouseenter", (event) => {
        const { title, description } = event.currentTarget.dataset;
        showResult(title, description);
    });

    card.addEventListener("mouseleave", () => {
        if (!click_flag) {
            hideResult();
        }
    });

    card.addEventListener("click", (event) => {
        event.stopPropagation(); // Prevents body click from firing instantly
        click_flag = true;

        // Hide the original text and remove it from flow so new content mounts at top
        resultWrapper.classList.remove("is-visible");
        resultWrapper.style.display = "none";
        
        resultContainer.classList.add("is-active");

        const title = event.currentTarget.dataset.title;

        fetch("/selection_click", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ title })
        })
        .then(response => response.text())
        .then(html => {
            let fetchWrapper = document.getElementById("dynamic-fetch-wrapper");
            if (!fetchWrapper) {
                fetchWrapper = document.createElement("div");
                fetchWrapper.id = "dynamic-fetch-wrapper";
                resultContainer.appendChild(fetchWrapper);
            }
            
            fetchWrapper.innerHTML = html;

            const sdDirectory = document.getElementById("sd-directory");
            if (sdDirectory) {
                requestAnimationFrame(() => {
                    requestAnimationFrame(() => {
                        sdDirectory.classList.add("is-visible");
                    });
                });
            }
        })
        .catch(error => { console.error("Selection request failed: ", error) });
    });
});

// Click anywhere on body to close/reset content
document.body.addEventListener("click", (event) => {
    // If the click happened inside the result container, ignore it
    if (event.target.closest("#result-container")) {
        return;
    }

    if (click_flag) {
        click_flag = false;
        hideResult();
    }
});
</script>
</body>
</html>

)rawliteral";

#endif // INDEX_HTML_H
