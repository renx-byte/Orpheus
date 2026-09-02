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

    if (!response.ok) {
      return "error";
    }

    return await response.text();
  } catch (error) {
    return "error";
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

              <button id="btn-upload" class="result-button modal-btn small btn-type">
                UPLOAD
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

            <div id="drop-zone" class="d-none">
              <p>Upload your media here</p>
              <input type="file" id="file-input" hidden>
            </div>

            <!-- Progress ring -->
            <div id="upload-progress-container" class="d-none">
              <svg width="120" height="120" viewBox="0 0 120 120">
                <circle cx="60" cy="60" r="54" fill="none" stroke="#333" stroke-width="8"/>
                <circle id="progress-circle" cx="60" cy="60" r="54" fill="none" stroke="var(--accent-cyan)" stroke-width="8" stroke-linecap="round" stroke-dasharray="339.292" stroke-dashoffset="339.292" transform="rotate(-90 60 60)"/>
                <text x="60" y="60" text-anchor="middle" dy="0.35em" fill="var(--accent-cyan)" font-size="18" id="progress-percent">0%</text>
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
      upload: document.getElementById("btn-upload"),
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

    elements.dropzone.addEventListener("click", (event) => {
      event.stopPropagation();
      elements.fileInput.click();
    });

    elements.fileInput.addEventListener("change", async (event) => {
      const chunkSize = 32768;

      const songFile = event.target.files[0];
      if (!songFile) return;

      const songName = songFile.name;
      const songSize = songFile.size;

      const totalIterations = Math.ceil(songSize / chunkSize);

      // Show progress ring, hide drop zone and action buttons
      elements.dropzone.classList.add("d-none");
      elements.submit.classList.add("d-none");
      elements.cancel.classList.add("d-none");
      elements.progressContainer.classList.remove("d-none");
      elements.uploadFilename.textContent = songName;
      elements.progressCircle.style.strokeDashoffset = "339.292";
      elements.progressPercent.textContent = "0%";

      for (let i = 0; i < totalIterations; i++) {
        const start = i * chunkSize;
        const end = Math.min(start + chunkSize, songSize);
        const chunk = songFile.slice(start, end);

        const result = await uploadSong(chunk, i, totalIterations, songName);

        if (result == "error") {
          console.log("aborted at chunk: ", i);
          elements.progressContainer.classList.add("d-none");
          elements.dropzone.classList.remove("d-none");
          elements.submit.classList.remove("d-none");
          elements.cancel.classList.remove("d-none");
          elements.fileInput.value = "";
          return;
        }

        const percent = Math.round(((i + 1) / totalIterations) * 100);
        elements.progressPercent.textContent = `${percent}%`;
        const circleLength = 339.292;
        const offset = circleLength - (percent / 100) * circleLength;
        elements.progressCircle.style.strokeDashoffset = offset;
      }

      console.log("Upload complete for file: ", songName);

      // Upload successful: close modal and refresh SD directory
      cleanup();

      const fetchWrapper = document.getElementById("dynamic-fetch-wrapper");
      if (fetchWrapper) {
        try {
          const response = await fetch("/selection_click", {
            method: "POST",
            headers: { "Content-Type": "application/json" },
            body: JSON.stringify({ title: "SD CARD" }),
          });
          if (response.ok) {
            const html = await response.text();
            fetchWrapper.innerHTML = html;
            sdDirectoryListener();
            const newSdDirectory = document.getElementById("sd-directory");
            if (newSdDirectory) {
              requestAnimationFrame(() => {
                newSdDirectory.classList.add("is-visible");
              });
            }
          }
        } catch (err) {
          console.error("Failed to refresh SD directory after upload:", err);
        }
      }
    });

    let asChild = false;
    let selectedType = "folder";

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

        if (selectedType !== "upload") {
          elements.name.focus();
        }
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
      } else if (selectedType === "file") {
        elements.name.classList.remove("d-none");
        elements.dropzone.classList.add("d-none");
        elements.content.classList.remove("d-none");
      } else if (selectedType === "upload") {
        elements.content.classList.add("d-none");
        elements.name.classList.add("d-none");
        elements.dropzone.classList.remove("d-none");
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
        itemType: selectedType,
        itemName: name,
        fileContent: selectedType === "file" ? elements.content.value : "",
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

    elements.upload.onclick = () => {
      selectType("upload");
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
  const removeBtn = document.getElementById("remove-file");
  const downloadBtn = document.getElementById("download-file");
  const sdDirectory = document.getElementById("sd-directory");

  if (!sdDirectory) return;

  // Helper to reset all modes
  function resetModes() {
    sdDirectory.classList.remove("is-adding", "is-removing", "is-downloading");
    if (addBtn) addBtn.textContent = "ADD ITEM";
    if (removeBtn) removeBtn.textContent = "REMOVE ITEM";
    if (downloadBtn) downloadBtn.textContent = "GET ITEM";
  }

  if (addBtn) {
    addBtn.addEventListener("click", (event) => {
      event.stopPropagation();
      if (sdDirectory.classList.contains("is-adding")) {
        resetModes();
      } else {
        resetModes();
        sdDirectory.classList.add("is-adding");
        addBtn.textContent = "CANCEL ADD";
      }
    });
  }

  if (removeBtn) {
    removeBtn.addEventListener("click", (event) => {
      event.stopPropagation();
      if (sdDirectory.classList.contains("is-removing")) {
        resetModes();
      } else {
        resetModes();
        sdDirectory.classList.add("is-removing");
        removeBtn.textContent = "CANCEL REMOVE";
      }
    });
  }

  if (downloadBtn) {
    downloadBtn.addEventListener("click", (event) => {
      event.stopPropagation();
      if (sdDirectory.classList.contains("is-downloading")) {
        resetModes();
      } else {
        resetModes();
        sdDirectory.classList.add("is-downloading");
        downloadBtn.textContent = "CANCEL GET";
      }
    });
  }

  sdDirectory.addEventListener("click", async (event) => {
    const target = event.target;
    const isFolder = target.classList.contains("folder");
    const isFile =
      target.classList.contains("file") || target.classList.contains("size");

    if (!isFolder && !isFile) return;

    // --- ADD MODE (folders only) ---
    if (sdDirectory.classList.contains("is-adding")) {
      if (!isFolder) return;
      event.stopPropagation();

      const clickedLi = target.closest("li");
      let targetName = "";
      const folderSpan = clickedLi.querySelector(".folder");
      if (folderSpan) targetName = folderSpan.textContent.trim();

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
            payloadParent = parentFolderSpan.textContent.trim();
        }
      }
      payloadParent = payloadParent.replace(/\/$/, "");

      const payload = {
        name: itemName,
        type: itemType,
        ...(itemType === "file" ? { content: fileContent } : {}),
        parent: payloadParent,
      };

      fetch("/create_payload", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify(payload),
      })
        .then((response) => response.text())
        .then((html) => {
          const fetchWrapper = document.getElementById("dynamic-fetch-wrapper");
          if (fetchWrapper) {
            fetchWrapper.innerHTML = html;
            sdDirectoryListener();
            const newSdDirectory = document.getElementById("sd-directory");
            if (newSdDirectory) newSdDirectory.classList.add("is-visible");
          }
        })
        .catch((error) => console.error("Payload request failed:", error));
    }
    // --- REMOVE MODE (files & folders) ---
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
          pathParts.unshift(folderSpan.textContent.trim().replace("/", ""));
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

      fetch("/remove_payload", {
        method: "POST",
        headers: { "Content-Type": "application/json" },
        body: JSON.stringify({ path: fullPath }),
      })
        .then((response) => response.text())
        .then((html) => {
          const fetchWrapper = document.getElementById("dynamic-fetch-wrapper");
          if (fetchWrapper) {
            fetchWrapper.innerHTML = html;
            sdDirectoryListener();
            const newSdDirectory = document.getElementById("sd-directory");
            if (newSdDirectory) newSdDirectory.classList.add("is-visible");
          }
        })
        .catch((error) => console.error("Remove request failed:", error));
    }
    // --- DOWNLOAD MODE (files only) ---
    else if (sdDirectory.classList.contains("is-downloading")) {
      if (!isFile) return; // only files
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
          pathParts.unshift(folderSpan.textContent.trim().replace("/", ""));
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

      // Trigger browser download
      window.location.href =
        "/download_file?path=" + encodeURIComponent(fullPath);

      resetModes();
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
      headers: { "Content-Type": "application/json" },
      body: JSON.stringify({ title }),
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
      .catch((error) => console.error("Selection request failed:", error));
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
