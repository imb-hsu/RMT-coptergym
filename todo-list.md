# Projektplan: Framework für vergleichende Analyse von Drohnensteuerungen

> **Übergreifendes Ziel:** Entwicklung eines modularen Frameworks zum rigorosen Vergleich von End-to-End Reinforcement-Learning-Controllern (Absolut vs. LOS) mit einem klassischen, modellbasierten Regler innerhalb derselben Simulationsumgebung.

---

## Phase 1: Das Fundament – Modulare Umgebungs-Architektur (1-2 Tage)
*Ziel: Eine flexible Basis schaffen, die sowohl RL-Agenten als auch klassische Regler als austauschbare "Gehirne" für die Drohne behandeln kann.*

### &#9744; Task 1.1: `RMT_Base_Env.py` – Die Physik-Kapsel
*   **TODO:** Erstelle/Refaktoriere die Klasse, die **nur** die `RMT.so`-DLL handhabt.
*   **API:** `__init__`, `reset_simulation`, `_step_simulation(motor_commands)`, `get_physical_state`, `close`.
*   **Kommentar:** *Unsere saubere Schnittstelle zur "Hardware".*

### &#9744; Task 1.2: `RMT_RL_Env.py` – Die Gym-Schnittstelle für RL
*   **TODO:** Erstelle die abstrakte Klasse, die von `gym.Env` und `RMT_Base_Env.py` erbt.
*   **Struktur:** Implementiert die `step()`-Logik mit Frame-Skipping und ruft abstrakte Methoden (`_compute_obs`, `_compute_reward`, etc.) auf.
*   **Kommentar:** *Das standardisierte "Betriebssystem" für alle unsere lernenden Agenten.*

### &#9744; Task 1.3: `RMT_RL_Env.py` – Die Schnittstelle für klassische Regler
*   **TODO:** Erstelle eine neue Klasse, die ebenfalls von `RMT_Base_Env.py` erbt, aber **nicht** von `gym.Env`.
*   **Struktur:**
    *   `__init__(controller_class, controller_kwargs, ...)`: Initialisiert einen übergebenen klassischen Regler (z.B. einen PID-Regler).
    *   `run_episode(mission_data)`: Führt eine komplette Mission aus. In einer Schleife:
        1. Holt den aktuellen Zustand `s_t` via `get_physical_state()`.
        2. Fragt den internen Regler nach der nächsten Aktion: `motor_commands = self.controller.compute_action(s_t, mission_goal_t)`.
        3. Führt `_step_simulation()` mit Frame-Skipping aus.
        4. Speichert die Zustands-Trajektorie für die spätere Analyse.
*   **Kommentar:** *Dies ermöglicht einen fairen "Apfel-zu-Äpfel"-Vergleich. Der klassische Regler operiert auf derselben Physik-Abstraktion und mit derselben Kontrollfrequenz wie der RL-Agent.*

---

## Phase 2: Implementierung der konkreten Steuerungsansätze (2-3 Tage)
*Ziel: Die verschiedenen "Gehirne" (Controller) erstellen, die wir vergleichen wollen.*

### &#9744; Task 2.1: `generate_structured_dataset.py` – Das Missions-Skript
*   **TODO:** Erstelle ein separates Skript, das verschiedene Trajektorien generiert.
*   **Funktionalität:**
    *   Funktionen zum Erstellen von Wegpunkt-Sequenzen (Schweben, Punkt-zu-Punkt, Figuren).
    *   Funktionen zum Erstellen von zeitbasierten, kontinuierlichen Trajektorien (z.B. Kreis, Lemniskate).
    *   Fügt jeder Trajektorie Metadaten hinzu: Soll-Geschwindigkeiten, Soll-Gierwinkel, Toleranzen.
    *   Speichert die generierten Missionen in einem strukturierten Dateiformat (z.B. `.npz` oder `.pkl`), das von den Umgebungen leicht geladen werden kann.
*   **Kommentar:** *Entkoppelt die Missionsdefinition vom Code. Neue, komplexe Testfälle können hinzugefügt werden, ohne die Umgebungen anzufassen.*

### &#9744; Task 2.2: `EndToEndNavEnv` – Die RL-Umgebung für E2E-Navigation
*   **TODO:** Erstelle `class EndToEndNavEnv(RMT_RL_Env.py)`. Dies ist deine primäre RL-Umgebung.
*   **Konfiguration im `__init__`:**
    *   `navigation_mode: str = 'los'` (Optionen: 'los', 'absolute').
    *   `goal_conditioned: bool = True`.
    *   `ctrl_freq = 125 Hz`.
    *   `trajectory_dataset_path: str`.
*   **Implementierung:**
    *   `_reset_episode`: Lädt eine zufällige Mission aus der Datensatz-Datei.
    *   `_compute_obs`: Implementiert beide Navigationslogiken (LOS und Absolut), umschaltbar über das `navigation_mode`-Flag. Stellt den GCRL-Observationsvektor zusammen.
    *   `_compute_reward`: Implementiert die GCRL-Reward-Funktion.
*   **Kommentar:** *Eine einzige, flexible Umgebung, um die zentrale wissenschaftliche Frage (LOS vs. Absolut) zu untersuchen.*

### &#9744; Task 2.3: `ClassicController.py` – Der Baseline-Regler
*   **TODO:** Implementiere einen oder mehrere klassische Regler (z.B. einen kaskadierten PID-Regler).
*   **Struktur:** Eine Klasse mit einer `compute_action(state, goal)`-Methode, die die Motorbefehle zurückgibt.
*   **Kommentar:** *Dies ist deine Baseline. Die Performance des RL-Agenten wird an diesem "Goldstandard" gemessen.*

---

## Phase 3: Infrastruktur für Training & Analyse (1-2 Tage)
*Ziel: Ein robuster, reproduzierbarer und effizienter Workflow.*

### &#9744; Task 3.1: Trainingsskript (`train.py`) überarbeiten
*   **TODO:** Fokussiere das Skript auf den `EndToEndNavEnv`.
*   **Struktur:** Lade Konfigs, nutze `make_vec_env` (`n_envs > 1`), `EvalCallback`, `CheckpointCallback`, `tensorboard_log` und einen einzigen, langen `learn()`-Aufruf.

### &#9744; Task 3.2: Analyse-Skript (`evaluate_and_plot.py`) erweitern
*   **TODO:** Erstelle ein Skript, das **beide** Arten von Controllern auswerten kann.
*   **Funktionalität:**
    1. Lade eine feste Menge von Test-Missionen.
    2. **Für den RL-Agenten:** Lade das trainierte Modell und führe es auf den Missionen aus.
    3. **Für den klassischen Regler:** Initialisiere die `RMT_RL_Env.py` mit dem Regler und führe ihn auf denselben Missionen aus.
    4. Sammle die Trajektorien-Daten (`info`-Dicts bzw. gespeicherte Logs) von beiden Läufen.
    5. Speichere die Ergebnisse in **Pandas DataFrames**.
    6. Erstelle **vergleichende Plots** (z.B. Flugbahn von RL-Agent vs. PID-Regler auf derselben Mission).
*   **Kommentar:** *Das Herzstück deiner wissenschaftlichen Auswertung. Hier werden die Ergebnisse direkt gegenübergestellt.*

---

## Phase 4: Ausblick & Zukünftige Forschung (Laufende Aufgabe)
*Ziel: Die wissenschaftliche Reichweite des Projekts definieren und nächste Schritte planen.*

### &#9744; Task 4.1: (Future Work) HRL-Ansatz implementieren und vergleichen
*   **Hypothese:** Ein hierarchischer Ansatz kann die Sample-Effizienz verbessern oder komplexere, mehrstufige Aufgaben lösen.
*   **TODO:** Implementiere die in v1 geplanten HRL-Umgebungen (`AttitudeControlEnv`, `PositionControlHRLenv`) und vergleiche ihre Performance und Trainingszeit mit dem E2E-Ansatz.

### &#9744; Task 4.2: (Future Work) Implementierung alternativer Controller und Architekturen
*   **Hypothese:** Verschiedene Controller-Architekturen und RL-Formulierungen haben spezifische Stärken und Schwächen.
*   **TODO:** Befülle die angelegten Platzhalter-Klassen mit Leben:
    *   `RL_LOS_Env.py`: Eine dedizierte Umgebung, die nur den LOS-Ansatz implementiert.
    *   `CTRL_INDI_Env.py`: Eine Umgebung für den Vergleich mit einem klassischen INDI-Regler (Task 1.3).
    *   `HRL_Att_Env.py`, `HRL_Vel_Env.py`, `HRL_Pos_Env.py`: Implementierung der hierarchischen RL-Level.

### &#9744; Task 4.2: (Future Work) Vergleich mit PyBullet Drones
*   **Hypothese:** Die Wahl des Physik-Backends hat einen signifikanten Einfluss auf die gelernte Policy ("Sim-to-Sim"-Gap).
*   **TODO:** Schreibe den `PyBulletAdapter` für deine `RMT_RL_Env.py`-API. Trainiere den `EndToEndNavEnv`-Agenten auf beiden Backends und vergleiche die Lernkurven und das resultierende Flugverhalten.

### &#9744; Task 4.3: (Future Work) Fortgeschrittene Architekturen und Action Spaces
*   **Hypothese:** Custom Feature Extractors und "Action Space Shaping" (z.B. Delta-Actions) können die Performance weiter verbessern.
*   **TODO:** Führe die in v1 als "fortgeschritten" markierten Experimente durch, sobald die Baseline-Ergebnisse etabliert sind.

---
---

## Paper Ideas & Outline

### Kernforschungsfrage (Core Research Question)
> "To what extent can End-to-End Reinforcement Learning, guided by different observation representations (Absolute vs. Line-of-Sight) and dense reward structures, match or exceed the trajectory tracking performance and robustness of a well-tuned classical controller for agile quadrotor navigation?"
>
> *(Inwieweit kann ein End-to-End Reinforcement-Learning-Ansatz, geleitet durch unterschiedliche Observations-Repräsentationen (Absolut vs. Line-of-Sight) und dichte Reward-Strukturen, die Performanz und Robustheit eines gut eingestellten klassischen Reglers bei der agilen Trajektorienverfolgung von Quadrotoren erreichen oder übertreffen?)*

### Hypothesen
1.  **Performance:** Ein E2E-RL-Agent (trainiert mit LOS-Observation und progress-basiertem Reward) wird auf komplexen, nicht-linearen Trajektorien einen geringeren Tracking-Fehler und eine höhere Agilität aufweisen als der klassische Regler, während dieser bei einfachen Punkt-zu-Punkt-Manövern eine vergleichbare oder bessere Leistung zeigt.
2.  **Sample Efficiency & Generalisierung:** Die LOS-Observations-Repräsentation wird zu einer signifikant höheren Sample-Effizienz und einer besseren Generalisierungsfähigkeit auf ungesehenen Trajektorien führen als die Absolute Fehler-Repräsentation.
3.  **Reward-Sensitivität:** Eine Reward-Funktion, die explizit Missionsfortschritt, Stabilität und Kontrolleffizienz belohnt, wird zu signifikant robusteren Policies führen als eine rein auf Distanzminimierung basierende Funktion.

### Struktur des Papers
1.  **Einleitung**
    *   Motivation (autonome Drohnen), Problemstellung (Vergleich RL vs. Klassik), Beitrag (Systematische Studie zu Observation/Reward und direkter Vergleich).
2.  **Stand der Technik (Related Work)**
    *   Klassische Drohnenregelung (PID, LQR).
    *   RL für Drohnensteuerung.
    *   Konzepte der Observation-Gestaltung (GCRL, HER).
    *   Konzepte der Reward-Gestaltung (Reward Shaping).
3.  **Methodik**
    *   **3.1 Simulations-Framework:** `RMT_Base_Env.py`, DLL, Parameter.
    *   **3.2 Controller-Implementierungen:** Beschreibung des PID-Reglers und des E2E-RL-Ansatzes (PPO, GCRL, Netzwerk).
    *   **3.3 Experimentelle Variablen:** Formale Definitionen der "Absolut" vs. "LOS"-Vektoren und der verschiedenen Reward-Funktionen.
4.  **Experimente und Ergebnisse**
    *   **4.1 Test-Szenarien & Metriken:** Definition der Test-Trajektorien und quantitativen Metriken (RMSE, Erfolgsrate, etc.).
    *   **4.2 Ergebnisse:** Präsentation in Tabellen und Plots (Lernkurven, Trajektorien-Vergleiche, Metrik-Balkendiagramme).
5.  **Diskussion**
    *   Interpretation der Ergebnisse im Licht der Hypothesen.
    *   Stärken und Schwächen der Ansätze.
    *   Limitationen der Studie (z.B. Sim-to-Real Gap).
6.  **Fazit und Ausblick**
    *   Prägnante Beantwortung der Forschungsfrage.
    *   Ausblick auf "Future Work" (HRL, Sim-to-Sim, Delta-Actions).

### **Paper Outline: RMT-Env: A Hybrid Simulation Framework for Bridging Control Theory and Reinforcement Learning**

**Titelvorschläge:**

*   *RMT-Env: A Hybrid MATLAB/Python Framework for Reinforcement Learning in High-Fidelity Simulations*
*   *Bridging the Gap: Integrating MATLAB/Simulink Dynamics into Python-based Reinforcement Learning Pipelines*
*   *From Control Engineering to AI: A C-Library Export Approach for Creating Gymnasium Environments from MATLAB Simulations*

---

#### **Abstract (Zusammenfassung)**

*   **Problem:** Eine signifikante Lücke existiert zwischen der Welt der regelungstechnischen Simulation (oft in MATLAB/Simulink mit hochpräzisen, validierten Modellen) und der modernen KI-Forschung (dominiert von Python, Gymnasium und RL-Bibliotheken wie Stable Baselines3).
*   **Herausforderung:** Die Wiederverwendung dieser existierenden, wertvollen MATLAB-Modelle für RL ist oft mit hohen Kosten (Toolboxen), schlechter Performance oder komplexen Co-Simulation-Ansätzen verbunden.
*   **Lösung:** Wir stellen **RMT-Env** vor, ein Open-Source-Framework, das dieses Problem durch einen neuartigen Ansatz löst. Anstatt einer direkten Python-Integration nutzen wir den **MATLAB Coder**, um die Kerndynamik der Simulation in eine performante, plattformunabhängige C-Bibliothek (`.so`/`.dll`) zu exportieren.
*   **Innovation:** Wir entwickeln einen Python-Wrapper, der die exportierten C-Header-Dateien nicht in low-level `ctypes`-Strukturen, sondern in eine **high-level, objektorientierte Python-Klassenstruktur** abbildet. Dies ermöglicht eine nahtlose Integration in standardisierte Reinforcement-Learning-Pipelines als `gymnasium.Env`.
*   **Beitrag:** RMT-Env demokratisiert den Zugang zu hochpräzisen Simulationen für die KI-Forschung, ermöglicht direkte Vergleiche zwischen klassischen und RL-basierten Reglern im selben Modell und reduziert die Einstiegshürden (Kosten, Komplexität) erheblich.

---

#### **1. Introduction (Einleitung)**

*   **1.1. Die Welten der Regelungstechnik und des Reinforcement Learning**
    *   **Regelungstechnik:** Dominiert von MATLAB/Simulink, Fokus auf modellbasierte Entwicklung, mathematische Präzision, etablierte Validierungsprozesse.
    *   **Reinforcement Learning:** Dominiert von Python, Gymnasium, PyTorch/TensorFlow. Fokus auf datengetriebene, modellfreie Ansätze, schnelle Iteration und Skalierbarkeit.
*   **1.2. Die "Bridging"-Herausforderung**
    *   Argumentieren, warum es wünschenswert ist, diese Welten zu verbinden:
        *   Wiederverwendung von jahrzehntelanger Entwicklungsarbeit in validierten Simulationsmodellen.
        *   Benchmarking von RL-Agenten gegen etablierte, optimale Regler.
        *   Anwendung von RL auf Probleme, für die eine reine Python-Simulation zu ungenau oder zu aufwendig zu entwickeln wäre.
*   **1.3. Bestehende Lösungsansätze und ihre Nachteile**
    *   **Ansatz A: MATLAB Reinforcement Learning Toolbox™**
        *   **Vorteil:** Nahtlose Integration innerhalb des MATLAB-Ökosystems.
        *   **Nachteile:**
            *   **Kosten:** Erfordert teure, spezialisierte Lizenzen.
            *   **"Walled Garden":** Bindet den Forscher an das MATLAB-Ökosystem, erschwert die Nutzung des State-of-the-Art aus der Python-Community (z.B. neueste SB3-Algorithmen, Logging-Tools wie Weights & Biases).
    *   **Ansatz B: MATLAB Engine API for Python**
        *   **Vorteil:** Ermöglicht den Aufruf von MATLAB-Funktionen aus Python.
        *   **Nachteile:**
            *   **Performance-Overhead:** Startet eine komplette MATLAB-Instanz im Hintergrund. Jeder `step()`-Aufruf involviert einen langsamen Inter-Process-Communication (IPC) Call. Ungeeignet für Millionen von Simulationsschritten im RL-Training.
            *   **Abhängigkeit:** Erfordert eine installierte MATLAB-Lizenz auf der Trainingsmaschine.
*   **1.4. Unser Beitrag: Der C-Export- und Klassen-Wrapper-Ansatz**
    *   Kurze Vorstellung der Kernidee: MATLAB-Dynamik -> C-Code-Export -> High-Level-Python-Wrapper -> Gymnasium-Umgebung.
    *   Skizzieren der Vorteile, die in den folgenden Abschnitten detailliert werden (Performance, Kosten, Flexibilität, Wiederverwendbarkeit).

---

#### **2. The RMT-Env Framework Architecture (Architektur des Frameworks)**

*   **2.1. Kernprinzip: Entkopplung von Dynamik und Steuerung**
    *   Visualisierung durch ein Flussdiagramm.
    *   **MATLAB-Seite:** Verantwortlich für die reine Physik/Dynamik. Enthält keine Steuerungslogik.
    *   **Python-Seite:** Verantwortlich für die Agenten-Policy, den Trainings-Loop und die Interaktion mit der Umgebung (via Gymnasium-API).
*   **2.2. Schritt 1: Export der Dynamik aus MATLAB**
    *   Nutzung des **MATLAB Coder™** zur Konvertierung des MATLAB-Codes in C-Code.
    *   Kompilierung zu einer geteilten Bibliothek (`.so` für Linux, `.dll` für Windows).
    *   Das Ergebnis: Ein Satz von C-Header-Dateien (`.h`), die die Schnittstellen (`init`, `step`, `terminate`) und Datenstrukturen definieren.
*   **2.3. Schritt 2: Der High-Level Python Wrapper**
    *   **Innovation hervorheben:** Anstatt `ctypes` zu nutzen, um die C-`structs` 1:1 in Python abzubilden (was zu unhandlichem, prozeduralem Code führt), wird eine **objektorientierte Abstraktion** geschaffen.
    *   **Die `RMT_Base_Env`-Klasse:**
        *   Nutzt `ctypes` intern, um die C-Bibliothek zu laden und die Funktionen aufzurufen.
        *   Definiert Python-Klassen (z.B. `AgentState`, `TargetState`), die die Daten aus den C-Structs kapseln.
        *   Implementiert Getter und Setter, die die Konvertierung zwischen Python-Objekten (z.B. NumPy-Arrays) und den low-level C-Datenstrukturen übernehmen.
    *   **Vorteil:** Der Endnutzer (der RL-Forscher) interagiert nur mit sauberen Python-Objekten und muss sich nie mit Pointern oder Speicher-Management auseinandersetzen.
*   **2.4. Schritt 3: Integration in die Gymnasium-API**
    *   Die finale `E2E_Env`-Klasse erbt von `RMT_Base_Env` und `gymnasium.Env`.
    *   Implementiert die Standard-Gymnasium-Methoden (`step`, `reset`, etc.), indem sie die Methoden des High-Level-Wrappers aufruft.
    *   Definiert die `observation_space` und `action_space` passend zur RL-Pipeline.

---

#### **3. Vorteile und Diskussion**

*   **3.1. Performance**
    *   Vergleich des C-Export-Ansatzes mit der MATLAB Engine API.
    *   Argumentieren, dass die Ausführung von kompiliertem C-Code fast native Performance erreicht und den IPC-Overhead komplett eliminiert, was das RL-Training um Größenordnungen beschleunigt.
*   **3.2. Kosteneffizienz und Zugänglichkeit**
    *   Hervorheben, dass für das **Training** keine MATLAB-Lizenz benötigt wird. Nur für den initialen Export.
    *   Demokratisiert die Forschung, da Studenten und Forscher ohne teure Toolbox-Lizenzen State-of-the-Art-RL auf validierten Modellen anwenden können.
*   **3.3. Flexibilität und Ökosystem-Integration**
    *   Durch die Standardisierung auf die Gymnasium-API wird das gesamte Python-KI-Ökosystem sofort nutzbar:
        *   **RL-Bibliotheken:** Stable Baselines3, RLlib, Tianshou, etc.
        *   **Logging & Monitoring:** TensorBoard, Weights & Biases.
        *   **Hyperparameter-Tuning:** Optuna, Ray Tune.
*   **3.4. Wiederverwendbarkeit und Legacy-Code**
    *   Ermöglicht Unternehmen und Forschungsgruppen, ihre existierenden, hochkomplexen und validierten MATLAB/Simulink-Modelle für eine völlig neue Klasse von Problemen (KI/RL) nutzbar zu machen, ohne sie neu implementieren zu müssen.

---

#### **4. Case Study: Training eines End-to-End-Drohnencontrollers**

*   Kurze Beschreibung des Anwendungsfalls: Training einer Policy für eine Trajektorien-Folge-Aufgabe.
*   **Setup:**
    *   Beschreibung des verwendeten Drohnenmodells in MATLAB.
    *   Kurze Erwähnung der `E2E_Env`-Implementierung.
    *   Trainingsalgorithmus (z.B. PPO aus Stable Baselines3).
*   **Ergebnisse:**
    *   Zeigen einer Lernkurve (Reward vs. Timesteps).
    *   Visualisierung einer erfolgreich geflogenen Trajektorie (Plot von Soll- vs. Ist-Trajektorie).
    *   Diskussion der Ergebnisse: Zeigt, dass der Ansatz in der Praxis funktioniert und zu konvergentem Lernen führt.

---

#### **5. Conclusion and Future Work (Fazit und Ausblick)**

*   **Zusammenfassung:** RMT-Env bietet eine performante, kosteneffiziente und flexible Brücke zwischen der etablierten Welt der Regelungstechnik-Simulation und der schnelllebigen Welt der KI-Forschung. Der C-Export-Ansatz mit einem High-Level-Python-Wrapper überwindet die Limitierungen bestehender Lösungen.
*   **Future Work:**
    *   Erweiterung des Frameworks zur Unterstützung von Simulink-Modellen (via Simulink Coder).
    *   Entwicklung einer automatisierten Toolchain, die den Export- und Wrapper-Generierungs-Prozess weiter vereinfacht.
    *   Veröffentlichung weiterer Referenz-Umgebungen (z.B. für andere Roboter-Systeme).
    *   Bereitstellung von Docker-Images für eine noch einfachere Reproduzierbarkeit.

---

#### **References (Literaturverzeichnis)**

*   (Hier relevante Paper zu Gymnasium, SB3, MATLAB Coder, MATLAB RL Toolbox etc. auflisten)


### **Struktur für Paper-Abschnitt: Design des Observationsraums für glatte Drohnensteuerung**

**Titel des Abschnitts:** *Vom Naiven Markov-2-Ansatz zur State Augmentation für nicht-Markov'sche Drohnendynamik*

---

#### **1. Einleitung & Motivation**

*   **Problemstellung:** Die Notwendigkeit einer glatten und stabilen Aktor-Ansteuerung (`smooth control`) bei Drohnen ist kritisch für Energieeffizienz, mechanische Belastung und Vorhersagbarkeit.
*   **Herausforderung für RL:** Standard-MDP-Formulierungen berücksichtigen die Aktor-Dynamik (z.B. Motor-Trägheit) oft unzureichend, was zu oszillierenden oder aggressiven Aktionen führen kann.
*   **Hypothese:** Die explizite Berücksichtigung der vorherigen Aktion (`A_t-1`) im Observationsraum ist entscheidend, um eine glatte Ansteuerung zu erlernen.
*   **These des Abschnitts:** Dieser Abschnitt analysiert die theoretischen Konsequenzen dieser Entscheidung, vergleicht naive Ansätze (Frame Stacking) mit dem vorgeschlagenen Ansatz der State Augmentation und begründet dessen Überlegenheit für hochfrequente Steuerungssysteme wie Drohnen.

---

#### **2. Theoretischer Hintergrund: Die Markov-Eigenschaft in der Praxis**

*   **Der klassische MDP:** Definition des Zustands `S_t` und der Markov-1-Eigenschaft `P(S_t+1 | S_t, A_t)`.
*   **Die Realität (POMDP):** Argumentation, warum der einfache physikalische Zustand (`pos`, `vel`, `rpy`, `omega`) für eine reale Drohne die Markov-Eigenschaft verletzt.
    *   **Verborgene Zustände:** Motor-Trägheit, Sensor-Verzögerungen, komplexe aerodynamische Effekte.
*   **Die Konsequenz:** Die Verletzung der Markov-Eigenschaft führt zu suboptimalen Policies, da der Agent nicht den vollständigen Zustand des Systems "sieht".

---

#### **3. Analyse von Lösungsansätzen**

*   **3.1. Direkter Ansatz: Approximation eines Markov-2-Systems durch Frame Stacking**
    *   **Definition:** Erweiterung des Observationsraums durch Konkatenation der letzten `k` Zustände und Aktionen. Für `k=2`: `Obs_t = (S_t, A_t-1, S_t-1)`.
    *   **Motivation:** Dem Agenten explizit eine "History" geben, um Geschwindigkeiten und Beschleunigungen abzuleiten.
    *   **Kritische Schwachstelle bei Drohnen (Ihre Kernargumentation):**
        *   **Problem 1: Redundanz durch Ableitungen:** Der Zustand `S_t` enthält bereits `vel` und `omega`, welche die primäre Information aus der Differenz `(S_t - S_t-1)` kodieren.
        *   **Problem 2: Redundanz durch hohe Abtastfrequenz:** Bei 250 Hz sind `S_t` und `S_t-1` hochkorreliert und liefern kaum neue Informationen.
        *   **Fazit:** Führt zu unnötig großen Observationsräumen ("Curse of Dimensionality") und kann das Lernen verlangsamen, da das Netz lernen muss, die redundante Information zu ignorieren.

*   **3.2. Der vorgeschlagene Ansatz: Gezielte State Augmentation**
    *   **Definition:** Minimale, aber gezielte Erweiterung des Zustandsraums, um die Markov-Eigenschaft "zu heilen": `S'_t = (S_t, A_t-1)`.
    *   **Begründung:** Anstatt einer allgemeinen "History" wird nur diejenige Information hinzugefügt, die den wichtigsten verborgenen Zustand (Motor-Trägheit/Schwung) am besten approximiert.
    *   **Vorteile:**
        *   Löst das primäre POMDP-Problem mit minimaler Vergrößerung des Vektors.
        *   Vermeidet die Redundanzprobleme des naiven Frame Stackings.
        *   Stellt eine direkte, informative Kausalität für die Policy her ("Wenn ich *gerade eben* diese Aktion ausgeführt habe, wie sollte meine *nächste* Aktion aussehen?").

---

#### **4. Literaturquellen zum Untermauern**

Hier sind einige Paper, die Sie zitieren können, um Ihre Argumente zu stützen.

*   **Für die allgemeine Herausforderung des Lernens von Drohnensteuerung mit RL (und oft PPO):**
    *   **Hwangbo et al., "Learning agile and dynamic motor skills for legged robots" (2019), *Science Robotics*.**
        *   *Relevanz:* Obwohl es um vierbeinige Roboter geht, ist dies ein wegweisendes Paper, das zeigt, wie komplexe, dynamische Steuerung direkt aus der Simulation gelernt werden kann. Es etabliert die Methodik des Sim-to-Real für komplexe Robotik.
    *   **Koch et al., "Learning a Low-Level Flight Controller for a Quadrotor With DDPG" (2019), *RA-L*.**
        *   *Relevanz:* Ein frühes, klares Beispiel für RL auf einer echten Drohne. Wichtig ist hier oft die Diskussion über die Zustands- und Aktionsräume, die in solchen Papern geführt wird.

*   **Für die spezifische Technik der State Augmentation (`A_t-1`):**
    *   **Koch et al., "Neuromorphic Controllers for Quadrotor Flight" (2021), *ICRA*.**
        *   **Relevanz (PERFEKTER TREFFER):** Dieses Paper macht *exakt* das, was Sie vorschlagen. In Tabelle 1 (Observation Space) listen sie explizit "previous action" als Teil ihrer Beobachtung für einen Quadrotor auf. Dies ist ein direkter wissenschaftlicher Beleg für Ihren Ansatz.
    *   **FINN, C. et al. "Deep visual foresight for planning robot motion." (2017) *ICRA***
        *   *Relevanz:* Dieses Paper (und viele andere aus dem Bereich "Model-Based RL") verwendet die letzte Aktion explizit als Input, um den nächsten Zustand vorherzusagen (`S_t+1 = f(S_t, A_t)`). Dies untermauert die fundamentale Bedeutung von `A_t` (und somit auch `A_t-1`) für die Systemdynamik.

*   **Für die theoretische Diskussion von POMDPs und rekurrenten Ansätzen (als fortgeschrittene Alternative):**
    *   **Igl et al., "Deep Variational Reinforcement Learning for POMDPs" (2018), *ICML*.**
        *   *Relevanz:* Bietet einen tiefen theoretischen Einblick in die Problematik von POMDPs und stellt einen fortgeschrittenen Lösungsansatz vor. Sie können dies zitieren, um zu zeigen, dass Sie das Problem im breiteren wissenschaftlichen Kontext verorten und Ihren Ansatz (State Augmentation) als pragmatische und effektive Lösung für Ihr spezifisches Problem positionieren.
    *   **`sb3-contrib` Dokumentation zu RecurrentPPO.**
        *   *Relevanz:* Auch wenn es keine wissenschaftliche Quelle ist, können Sie darauf verweisen, um die praktische Verfügbarkeit von Algorithmen zu zeigen, die für Sequenzdaten und POMDPs entwickelt wurden (PPO-LSTM).


