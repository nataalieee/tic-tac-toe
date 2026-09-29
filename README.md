# Tic-Tac-Toe (X și 0) 🎮

An interactive 2D **Tic-Tac-Toe** (*X și 0*) game built in **C++** using **SDL2** and **SDL2_image**. It features a modern graphical interface, a local two-player mode, and a single-player mode powered by a strategic decision-making AI.

---

## 🌟 Features

- **Two Game Modes**:
  - **Single Player (vs. AI)**: Play against a computer opponent that dynamically defends against player threats, capitalizes on winning lines, and plays strategically across center, corner, and edge positions.
  - **Two Players (1v1 Local)**: Classic turn-based multiplayer on the same computer.
- **Graphical User Interface (GUI)**:
  - Custom main menu screen with interactive buttons (`button_1.png` and `button_2.png`).
  - Crisp $600 \times 600$ game canvas with colored grid lines and distinct symbol textures for **X** and **O**.
- **End-Game Screens & Animations**:
  - Distinct animated flashing win screens for **X** (`x_win.png`), **O** (`o_win.png`), and **Draw** (`draw.png`).
  - Automatic board reset after a game concludes so you can play again immediately.
- **Optimized 60 FPS Game Loop**:
  - Frame-rate capped loop using `SDL_GetTicks()` and `SDL_Delay()` for consistent physics and rendering across any machine.
- **Smooth Input Handling**:
  - Mouse-driven interaction with state debouncing to prevent unintended double-clicks.

---

## 🧠 AI Strategy (Single Player Mode)

The single-player mode employs a prioritized heuristic algorithm to challenge the player:

1. **Win**: Checks if the AI has 2 pieces in any row, column, or diagonal and places the 3rd to immediately win.
2. **Block**: Checks if the player has 2 pieces in any row, column, or diagonal and places a piece to block the player's winning move.
3. **Positional Advantage**:
   - Takes the **center** cell `(1, 1)` if available.
   - Takes one of the four **corners** `(0, 0)`, `(0, 2)`, `(2, 0)`, `(2, 2)` if available.
   - Takes one of the remaining **edges** `(0, 1)`, `(1, 0)`, `(1, 2)`, `(2, 1)`.

---

## 📁 Project Structure

```text
tic-tac-toe/
├── X SI 0.sln                 # Visual Studio Solution file
├── X SI 0.vcxproj             # Visual Studio Project configuration
├── X SI 0.vcxproj.filters     # Visual Studio file filters
├── X SI 0.cpp                 # Main source code (Game engine, AI, rendering)
├── SDL2/
│   └── include/               # SDL2 C++ header files
├── x64/
│   └── Debug/                 # Runtime directory containing game assets & binaries
│       ├── X SI 0.exe         # Pre-compiled executable (Windows x64)
│       ├── SDL2.dll           # SDL2 runtime library
│       ├── SDL2_image.dll     # SDL2_image runtime library
│       ├── fer_1.png          # Main menu background
│       ├── button_1.png       # 1 Player button sprite
│       ├── button_2.png       # 2 Players button sprite
│       ├── x.png              # X symbol texture
│       ├── o.png              # O symbol texture
│       ├── x_win.png          # Player X victory screen
│       ├── o_win.png          # Player O victory screen
│       └── draw.png           # Tie/Draw screen
└── README.md                  # Project documentation
```

---

## 🕹️ Controls

| Action | Control |
| :--- | :--- |
| **Select Menu Option** | Left Mouse Click on mode button |
| **Place X or O** | Left Mouse Click on any empty tile |
| **Exit Game** | Window Close Button (`✕`) or `Alt + F4` |

---

## 🛠️ Requirements & Setup

### Windows (Visual Studio)

1. **Prerequisites**:
   - [Microsoft Visual Studio 2019 / 2022](https://visualstudio.microsoft.com/) with the **Desktop development with C++** workload.
   - Platform toolset set to **x64**.
2. **Opening & Running**:
   - Open `X SI 0.sln` in Visual Studio.
   - Select configuration: **Debug** and platform: **x64**.
   - Press `F5` (or click **Local Windows Debugger**) to build and run.
   - *Note*: Ensure the working directory is set to the project directory so asset paths (`x64/debug/...`) resolve correctly.

### Running the Pre-compiled Executable (Windows)

A pre-compiled build is included in `x64/Debug/`:
1. Navigate into `x64/Debug/`.
2. Double-click `X SI 0.exe` to play immediately without building.


