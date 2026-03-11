/* =======================================================
   INSANE SOUND SYSTEM V5 - DYNAMIC WEB ENGINE
======================================================= */

document.addEventListener("DOMContentLoaded", function() {
    // 1. Titel der Seite dynamisch zum "Insane" Branding ändern
    const header = document.querySelector("h1");
    if(header) {
        header.innerHTML = "⚡ INSANE SOUND SYSTEM <span style='color:#f1c40f'>V5</span>";
    }

    // 2. Einen coolen Subtitel unter die Überschrift packen
    const subTitle = document.createElement("p");
    subTitle.innerHTML = "OFFICIAL WEB-HUB & TELEMETRY";
    subTitle.style.color = "#888888";
    subTitle.style.letterSpacing = "4px";
    subTitle.style.marginTop = "0px";
    subTitle.style.marginBottom = "25px";
    subTitle.style.fontSize = "11px";
    subTitle.style.fontWeight = "bold";
    subTitle.style.textAlign = "center";
    
    if(header) {
        header.parentNode.insertBefore(subTitle, header.nextSibling);
    }

    // 3. Button Klick-Animation (fühlt sich reaktionsschneller an)
    // ESPHome lädt Buttons oft dynamisch nach, wir überwachen Klicks global
    document.body.addEventListener("mousedown", function(e) {
        if(e.target.tagName === "BUTTON") {
            e.target.style.transform = "scale(0.92)";
        }
    });
    
    document.body.addEventListener("mouseup", function(e) {
        if(e.target.tagName === "BUTTON") {
            e.target.style.transform = "scale(1)";
        }
    });
});