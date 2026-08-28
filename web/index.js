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