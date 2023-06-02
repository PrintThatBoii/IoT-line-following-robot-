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
