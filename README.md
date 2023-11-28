# SO_LONG - README

![so_long](https://github.com/byaliego/42-project-badges/blob/main/badges/so_longm.png?raw=true)

## Überblick

In diesem Repository findest du die Umsetzung meines Projekts "So Long", bei dem ich mich entschieden habe, das klassische Spiel Pacman nachzuprogrammieren. Für die Umsetzung verwendete ich die MLX-42 Bibliothek, um ein Fenster zu zeichnen und bestimmte Tastenanschläge zu senden. Die Besonderheit meines Spiels besteht darin, dass es sich um Pacman handelt, inklusive der Gegner in Form von Geistern.

## Paco (Pacman) in Aktion

![Paco Pacman GIF](https://github.com/ShiiikK/42-so_long/raw/main/Paco_pacman.gif)

## Pacman-Details

- **Charaktere:**
  - Spieler: Pacman
  - Gegner: Geister
- **Steuerung:**
  - W, A, S, D oder Pfeiltasten: Bewegung von Pacman
- **Besondere Funktionen:**
  - Pacman und Geister können an den Rändern links und rechts zur gegenüberliegenden Seite teleportiert werden, inspiriert vom Originalspiel.
  - Die Geister folgen einem selbst entwickelten "Zirkular Pathfinding"-Algorithmus, der es ihnen ermöglicht, die Position des Spielers intuitiv zu bestimmen und zu verfolgen.

## Projektinformationen

- **Punktzahl bei der Evaluierung:** 125/100%
- **Spaßfaktor:** Ich hatte enormen Spaß an diesem Projekt und habe mich motiviert über die Anforderungen hinaus engagiert.


## Dateien und Verzeichnisstruktur

- `Makefile`: Kompilierungsregeln für die Quelldateien.
- `*.h`, `*.c`: Implementierung des Spiels.
- `maps`: Verzeichnis für Kartendateien.
- `textures`: Verzeichnis für Bilddateien.

## Kompilierung und Ausführung

- `make`: Kompiliert das Projekt.
- `make clean`: Entfernt temporäre Dateien.
- `make fclean`: Entfernt erstellte Dateien und das Spiel.
- `make re`: Kompiliert das Projekt neu.

- `./so_long maps/map.ber`: Startet das Spiel mit der angegebenen Kartendatei.

## Spielbeschreibung

### Ziel des Spiels

- Der Spieler muss alle Sammelobjekte auf der Karte einsammeln und dann den kürzesten Weg wählen, um zu entkommen.

### Steuerung

- Die Tasten W, A, S und D werden verwendet, um den Hauptcharakter zu bewegen.
- Der Spieler kann sich in vier Richtungen bewegen: nach oben, unten, links und rechts.

### Grafikverwaltung

- Das Programm zeigt das Bild in einem Fenster an.
- Die Fensterverwaltung muss reibungslos sein, z.B., wenn das Fenster gewechselt oder minimiert wird.
- Drücken von ESC oder Klicken auf das Schließen-Symbol schließt das Fenster und beendet das Programm sauber.

### Kartenbau

- Die Karte besteht aus Wänden, Sammelobjekten und freiem Raum.
- Erlaubte Zeichen: 0 für leeren Raum, 1 für eine Wand, C für ein Sammelobjekt, E für den Kartenausgang und P für die Startposition des Spielers.

### Validierung der Karte

- Die Karte muss rechteckig sein und von Wänden umgeben.
- Sie muss mindestens einen Ausgang, ein Sammelobjekt und eine Startposition enthalten.
- Doppelte Zeichen (Ausgang/Start) führen zu einer Fehlermeldung.
- Es wird überprüft, ob ein gültiger Pfad auf der Karte existiert.

### Fehlerbehandlung

- Das Programm beendet sich sauber mit einer Fehlermeldung, wenn eine ungültige Konfiguration in der Datei gefunden wird.

## Bonus

Zusätzliche Features:

- Der Spieler verliert, wenn er einen Gegner berührt.
- Sprite-Animationen.
- Die Anzeige der Zuganzahl direkt auf dem Bildschirm anstelle der Shell.

**Hinweis:** Obwohl der Bonus-Teil optional ist, habe ich mich dazu entschieden, diese zusätzlichen Funktionen zu implementieren, um das Spielerlebnis zu verbessern und meine Fähigkeiten weiter zu vertiefen.
