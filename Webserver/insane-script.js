/* =======================================================
   INSANE SOUND SYSTEM V5 - BOOTLOADER & DESIGN ENGINE
======================================================= */

// 1. Schritt: Das offizielle ESPHome "Gehirn" nachladen
const esphomeScript = document.createElement('script');
esphomeScript.type = 'module';
esphomeScript.src = 'https://oi.esphome.io/v2/www.js';
document.head.appendChild(esphomeScript);

// 2. Schritt: Deine Insane-Anpassungen anwenden, sobald alles geladen ist
esphomeScript.onload = () => {
    console.log("Insane Engine: ESPHome Core geladen.");
    
    // Wir warten kurz, bis die Elemente im Browser erstellt wurden
    setTimeout(() => {
        const header = document.querySelector("h1");
        if(header) {
            header.innerHTML = "⚡ INSANE SOUND SYSTEM <span style='color:#f1c40f'>V5</span>";
        }
    }, 500);
};

// Falls der Header sich später aktualisiert (ESPHome v2 Dynamik)
const observer = new MutationObserver(() => {
    const header = document.querySelector("h1");
    if (header && !header.innerHTML.includes("INSANE")) {
        header.innerHTML = "⚡ INSANE SOUND SYSTEM <span style='color:#f1c40f'>V5</span>";
    }
});
observer.observe(document.body, { childList: true, subtree: true });