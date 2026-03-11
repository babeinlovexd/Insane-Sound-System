/* =======================================================
   INSANE SOUND SYSTEM V5 - BOOTLOADER (VERSION 1)
======================================================= */

// 1. Das offizielle ESPHome V1 Script nachladen (für Live-Werte)
const coreScript = document.createElement('script');
coreScript.src = 'https://oi.esphome.io/v1/webserver-v1.min.js';
document.head.appendChild(coreScript);

// 2. Das Design sofort anwenden
const header = document.querySelector("h2");
if(header) {
    header.innerHTML = "⚡ INSANE SOUND SYSTEM <span style='color:#f1c40f'>V5</span>";
    
    const subTitle = document.createElement("p");
    subTitle.innerHTML = "OFFICIAL WEB-HUB & TELEMETRY";
    subTitle.style.color = "#888888";
    subTitle.style.letterSpacing = "4px";
    subTitle.style.marginTop = "0px";
    subTitle.style.marginBottom = "25px";
    subTitle.style.fontSize = "11px";
    subTitle.style.fontWeight = "bold";
    subTitle.style.textAlign = "center";
    
    header.parentNode.insertBefore(subTitle, header.nextSibling);
}

// 3. Klick-Animation für die Schalter
document.body.addEventListener("mousedown", function(e) {
    if(e.target.tagName === "BUTTON") e.target.style.transform = "scale(0.92)";
});
document.body.addEventListener("mouseup", function(e) {
    if(e.target.tagName === "BUTTON") e.target.style.transform = "scale(1)";
});