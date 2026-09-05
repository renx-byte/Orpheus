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
