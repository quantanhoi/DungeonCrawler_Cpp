Praktikum 5: Dateiverarbeitung, Graphalgorithmen
Lernziele
• Anwenden von Graphalgorithmen
• Effiziente Suche von Objekten in Datenstrukturen
• Einlesen und Schreiben von Dateien
1 Gegner mit „künstlicher Intelligenz“
Es soll ein neuer Gegnertyp hinzugefügt werden, der sich in jeder Runde einen Schritt in Richtung des Spielers
bewegt und diesen angreift. Dazu implementieren Sie folgendes:
• Eine Methode Level::getPath(from, to)welche einen Pfad zwischen den beiden Kacheln from und
to berechnet und diesen zurück liefert. Der Pfad kann dargestellt sein als Container von Positionen (vector,
list, etc.). Die Parameter from und to sind von Ihnen frei wählbar und können beispielsweise Tile* oder
Positionen sein.
• Einen neuen Controller-Typ AttackController, welcher die move-Methode so überlädt, dass dieser
in jedem Zug einen Schritt in Richtung des Spielers macht, falls möglich.
• Hierfür benötigt der AttackController Zeiger auf das aktuelle Level und/oder den Spieler. Diese
können Sie als Attribute zum AttackController hinzufügen.
• Wir gehen davon aus, dass die NPCs von geringer Intelligenz sind und nicht durch „Absicht“ versuchen Türen
zu öffnen. Natürlich soll ein Switch prinzipiell auch von einem NPC aktiviert werden. Allerdings müssen Sie
nicht implementieren, dass ein NPC versucht, einen Switch zu finden falls kein Pfad zum Spieler ermittelt
werden konnte.
• NPSc sind allerdings intelligent genug, Portale zu benutzen und wissen auch, wo diese hin führen. Portale
sollen also für die Wegsuche als benachbarte Knoten gelten.
Die Frage, wie der Pfad von einer Kachel zu einer anderen aussieht, bzw. ob dieser überhaupt existiert, lässt sich
mit Algorithmen aus der Graphentheorie1 lösen:
• Einer einfachen Breitensuche2
• Dem Algorithmus von Dijkstra3
• Den A* Algorithmus 4
Ein Graph besteht aus zwei verschiedenen Mengen: Zum einen eine Menge an Knoten, und eine weitere Menge an
Kanten. Eine Kante verbindet dabei stets zwei Knoten. Eine Kante ist gerichtet, wenn Sie nur eine Verbindung in
eine Richtung darstellt, und ungerichtet, falls die Kante Verbindungen in beide Richtungen darstellt. Eine Kante
kann ebenfalls gewichtet sein, in diesem Fall ist der Kante ein Wert, manchmal auch Kosten genannt, zugeordnet.
Ein „klassisches“ anschauliches Beispiel für einen Graphen wäre ein Streckennetz, welches Städte verbindet.
In folgendem Graphen wären die Städte jeweils die Knoten des Graphen und die Kanten sind die möglichen
Verbindungen zwischen diesen Städten. Alle Kanten sind bidirektional, also ungerichtet. Darüber hinaus besitzen
Sie ein Kantengewicht in Form einer Entfernung.

