// ============================================================
// TYPING EFFECT
// ============================================================
const initTypewriter = () => {
    const heading = document.getElementById("typewriter-heading");
    const phrases = ["Something...", "Test ENV..."];
    
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

/**
 * Updates DOM with card data and displays the result panel
 */
function showResult(title, description) {
    resultHeading.textContent = title + " INTERFACE";
    resultDescription.textContent = description;

    resultWrapper.classList.add("is-visible");

    resultContainer.classList.add("is-active");
}

/**
 * Hides the result panel
 */
function hideResult() {
    resultWrapper.classList.remove("is-visible");

    resultContainer.classList.remove("is-active");
}

// Dynamically assign event listeners to all cards
selectionCards.forEach((card) => {
    card.addEventListener("mouseenter", (event) => {
        // Extract data dynamically from HTML attributes
        const { title, description } = event.currentTarget.dataset;
        showResult(title, description);
    });

    card.addEventListener("mouseleave", () => {
        hideResult();
    });


    card.addEventListener("click", (event) => {
      const title = event.currentTarget.dataset.title;

      const body = {title};

      fetch("/selection_click", {method: "POST", headers: {"Content-Type": "application/json"}, body: JSON.stringify(body)});

    })


});