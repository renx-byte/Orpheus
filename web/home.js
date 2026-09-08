// ============================================================
// Typewriter Effect
// ============================================================

import { ID3Writer } from "https://cdn.jsdelivr.net/npm/browser-id3-writer@6.4.0/dist/browser-id3-writer.mjs";

const initTypewriter = () => {
  const heading = document.getElementById("typewriter-heading");
  const phrases = ["renx-byte...", "Test ENVIRONMENT..."];

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
      const coverResult = await uploadCover(coverPng, songNameInput);
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

      const songName = songNameInput + ".mp3";
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

const toggleHiddenBtn = document.getElementById("toggle-hidden-btn");
if (toggleHiddenBtn) {
  toggleHiddenBtn.addEventListener("click", () => {
    const container = document.getElementById("result-container");
    container.classList.toggle("show-hidden");
    const isShowing = container.classList.contains("show-hidden");
    toggleHiddenBtn.textContent = isShowing ? "Conceal" : "Reveal";
  });
}

sdDirectoryListener();
