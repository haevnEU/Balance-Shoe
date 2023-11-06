# Balance-Shoe

Bei dem Projekt BalanceShoe geht es darum, den Heilungsprozess eines Patienten nach einer Beinoperation zu unterstützen. Durch die erfundene Einlegesohle wird die aktuelle Belastung erfasst und gibt beim Überschreiten dieser einen Warnton. Über die App kann der Patient sein Körpergewicht und seine Belastungsgrenze festlegen. Die aktuelle Belastung wird mittels des Mikrocontrollers an die App kommuniziert und der Warnton ertönt bei Überschreitung auf dem Smartphone.

---

## Projektidee
Patienten nach einer Beinoperation haben oft Schwierigkeiten damit, die vom Arzt empfohlene Belastungsgrenze einzuhalten oder gar einzuschätzen. Über dieses Problem erzählte auch der Stiefvater von Kai Stredder - ebenfalls unser Nutzer - und dadurch entstand die Idee, ein Gerät zu entwickeln, das Patienten dabei unterstützt ihre vorgegebene Belastungsgrenze einzuhalten.

---

## Entwicklung
Die Entwicklung lässt sich in drei wesentlichen Hauptaufgaben aufteilen. Diese sind 3D-Druck, Elektronik und Programmierung. Während der Entwicklung orientierten wir uns an der Methode des Prototypings, um schnell erste Ergebnisse zu erzielen und danach auf diese aufzubauen und zu verbessern. So war es außerdem möglich besser auf Probleme oder Änderungswünsche zu reagieren.

---

## Entwurf
Zuerst wurde eine Skizze angelegt, damit alle die gleiche Vorstellung von dem Gerät haben.

Der Aufbau ist wie folgt: eine Einlegesohle mit den Gewichtssensoren, die man in den Schuh legt und ein daran befindlichen Sender. Außerdem noch ein Empfänger, um die aktuelle Belastung zu erhalten und daran befestigte Knöpfe, um das Körpergewicht und die Belastungsgrenze zu regulieren.

---

## Prototypen und Konstruktionsverlauf
Die erste Version umfasste eine Holzsohle mit den Wägezellen. Die Holzsohle wurde mithilfe eines Lasercutters zurecht geschnitten.

Als Materialien benutzen wir vorerst vier Wägezellen, die mit dem Arduino verbunden waren. Zwischen den Wägezellen und dem Arduino befand sich noch ein AD-Modul, das für die Stromverstärkung der Wägezellen nötig war. Dadurch konnten wir vorerst die Belastung über den Arduino auslesen und auf einem Bildschirm anzeigen lassen. Das gewählte Material Holz erwies sich als unzulässig, da das belastende Gewicht nicht gleichmäßig auf die Wägezellen verteilt wurde und Holz nicht sehr angenehm am Fuß ist. Demnach folgte die zweite Version der Einlegesohle, die 3D-gedruckt wurden.


Die zweite Version der Sohle besteht aus mehreren Schichten und einem weichen Material (weiß) und einem harten Material (blau). Durch das weiche Material war die Sohle deutlich angenehmer am Fuß und durch die gezielt gesetzten Platten auf der oberen Seite wurde das Gewicht gleichmäßiger verteilt.


Für eine ordnungsgemäße Verkabelung wurde eine Box 3D-gedruckt, um die Komponenten der Elektronik sauber und ordentlich zu verstecken. Desweiteren befindet sich an der Box eine Schnalle zur Befestigung an einem Schuh.

---

## 3D-Druck
Für die Einlegesohle wurden zwei verschiedene Materialien beim 3D-Druck genutzt. Das weiche weiße Material (PLU) und das harte blaue Material (PLA). Die Einlegesohle besteht aus folgenden Schichten:
- untere Schicht: besteht nur aus dem harten Material
- mittlere Schicht: besteht nur aus dem weichen Material und der Platz für die Wägezellen und der Verkabelung wurde berücksichtigt
- obere Schicht: über den Wägezellen wurde das harte Material für die gleichmäßige Verteilung verwendet und der Rest besteht aus dem weichen Material für den Komfort
Außerdem wurde eine Box 3D-gedruckt, um die Elektronik sauber zu verstauen und diese auch am Schuh mittels einer Schnalle zu befestigen.

---

## Elektronik
Der BalanceShoe benutzt zum Übertragen der Daten via Bluetooth einen ESP32 (genauer: LOLIN32). Angeschlossen an diesen sind die vier Wägezellen in der Einlegesohle, sowie ein AD-Modul (HX711), das für die Stromverstärkung der Wägezellen nötig war. Desweiteren wird eine LiPo-Batterie zur Stromversorgung genutzt. In der Box befinden sich außerdem noch eine grüne und eine rote LED. Die grüne LED leuchtet wenn der BalanceShoe angeschaltet ist und die rote LED leuchtet sobald der Ladestand der LiPo-Batterie gering wird. Der ESP32 wird softwaretechnisch in den Deep-Sleep gesetzt, wenn der Ladestand gering wird, um ein Aufblähen der Batterie zu vermeiden. Geladen werden kann die Batterie mittels der Micro-USB Schnittstelle am ESP32.

---

## App
Um die aktuelle Belastung zu erfassen, war es notwendig eine App zu entwickeln. Dabei wurde sich für die Entwicklungsumgebung Qt und der dazugehörigen Programmiersprache C++ entschieden. Durch Qt war es möglich die App sowohl auf Android als auch auf iOS zu benutzen.

Wenn ein Benutzer also die App benutzen möchte, kann er sich über ein Knopfdruck direkt mit dem ESP32 verbinden und auf der nächsten Seite den Namen und die maximale Belastung eingeben. Ab dann wird die Belastung der Sohle an die App übertragen und die App schaltet Alarm, sobald sich der Benutzer über der maximalen Belastung befindet.

Die App besteht aus folgenden Seiten:
- Startseite: auf Knopfdruck lässt sich die App mit dem ESP32 verbinden
- Hauptseite: hier wird die aktuelle Belastung und die maximale Belastung angezeigt
- Konfigurationsseite: hier kann man den Namen und die maximale Belastung eingeben

---

## Team
Das Team hinter dem Projekt BalanceShoe besteht aus:
- Kai Stredder
- Marc Nowakowski
- Nils Milewski

---

Wiki Eintrag wurde von der entsprechenden Seite des [Hochschule Ruhr West FabLab Wiki](https://wiki.hrw-fablab.de/index.php?title=BalanceShoe) übernommen
