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
