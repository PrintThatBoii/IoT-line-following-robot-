# IoT-line-following-robot-
IoT line following robot with MQTT, influxdb and grafana  

De bedoeling is om een line following robot te maken dat een witte lijn moet volgen en data moet doorsturen naar een database waaruit grafana de waardes kan laten weergeven.

Gebruikte hardware:

• Esp32 als microcontroller waar alles op aangesloten word.
• Odroid c4 voor de MQTT server te draaien.
• Level shifter voor de 3.3V uitgang om te zetten naar een 5V uitgang voor de signaallampjes.
• L298N driver voor de dc motoren.
• TT motoren 3V-12V dc met wielen.
• 9V batterij houder + 9V batterij voor alles te voeden.
• Digitale IR sensoren (TCRT5000) voor de lijn te volgen.
• HC SR04 ultrasone sensor om vooraan te kunnen detecteren als er iemand voor de wagen komt.
• Verkeerslichtmodule voor de signaallampjes.
• Kabels
• Pin headers om alles makkelijk aan te sluiten.
• Prototype pcb om alle onderdelen op te solderen.
• Knoppen zowel op de esp32 als bij de odroid voor de wagen terug te doen starten.
• DHT-11 temperatuur sensor voor de temperatuur van de motoren te meten.

Concept: 
Ik ben begonnen met een concept uit te tekenen in het 3d teken programma genaamd shapr3d. Hierin ben ik gestart met de basis van de wagen uit te tekenen/schetsen en daar de componenten te schikken zodat ik de grote van de wagen kan bepalen om er voor te zorgen dat het op de bouwplaat van de 3d printer past. Daarna ben ik de hoogte ingegaan om de rest van de wagen uit te tekenen van basis tot de bovenkant van de wagen. Tijdens het tekenen heb ik ook rekening gehouden met hoe ik alles wil aansluiten zodat de kabels strak weggewerkt zijn en niet in de weg kunnen zitten. Nadat het tekenen er op zat (na een +-20 uur designen) ben ik begonnen met de kleuren te kiezen die ik wou gebruiken en ben ik gestart met het printen van de onderdelen. Dit duurde een kleine 15u om alles uit te printen op 2 van mijn 3d printers. 

Assemblage: 
Na het printen van de onderdelen is het tijd voor de assemblage. Omdat ik alles zo had gedesigned zodat alles makkelijk in elkaar past ging de assemblage vlot. Ik ben begonnen met de motoren aan de basis te monteren en deze aan te sluiten op de driver die er naast staat. 

Vervolgens heb ik de zwenkwiel gemonteerd en de ultrasone sensor op zijn plaats gezet. Daarna was het tijd voor de pcb te solderen en alle connecties te leggen. Om makkelijk de esp32 en de kabels te kunnen uittrekken maak ik gebruik van pinheaders die onderaan de pcb aan elkaar gesoldeerd zijn. Op de pcb zien we de twee voedingsdraden die de 5V van de driver doorgeven naar de Vin en de gnd pinnen van de esp32 zodat deze gevoed kan worden door een batterij. 
Links zien we de aansluiting voor de knop om de wagen terug te doen starten en rechts zien we de connecties voor de level shifter die het 3.3V signaal van de esp32 omzet naar een 5V signaal zodat de signalisatieledjes kunnen aangestuurd worden aangezien deze om 5V werken. 
Om de level shifter te kunnen gebruiken moet er een 3.3V en een 5V voeding aangesloten worden. De 3.3V komt van de esp32 en de 5V komt van de 5V voeding die de esp32 voed. 

Na het solderen was het tijd om alle kabels aan de juiste GPIO pinnen te hangen van de esp32 volgens het aansluitschema en kunnen we gaan programmeren. 
