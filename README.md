# Text Editor (Qt) & DOS Simulator (C++ Console)

This repository contains two projects:  
1. **DOS Simulator** – A console-based simulation of DOS commands.  
2. **Text Editor** – A Qt-based graphical text editor with features similar to Notepad.  

---

## 🖥️ DOS Simulator (C++ Console)

A terminal-based project that simulates the classic **Disk Operating System (DOS)**.  
It supports a variety of commands for file and directory operations.

### ✨ Features
- `CD`, `CD.`, `CD..`, `CD/` – Navigate directories  
- `MKDIR` – Create a new directory  
- `DIR` – List directories and files  
- `CREATE` – Create a new file  
- `DEL` – Delete a file  
- `MOVE` – Move a file  
- `COPY` – Copy a file  
- `FINDd` – Find a directory in the tree  
- `FINDf` – Find a file in the current directory  
- `FINDstr` – Find a string in the current file  
- `FINDSTR` – Find a string in all files in the directory  
- `ATTRIB` – Display file attributes  
- `CLS` – Clear the screen  
- `FORMAT` – Reset the directory tree  
- `LOADTREE` – Load a saved directory tree  
- `HELP` – List available commands  
- `VER` – Display version  
- `EDIT` – Open the text editor for a file  
- `EXIT` – Exit the simulator  

---

## 📝 Text Editor (Qt)

A graphical text editor built in C++ with **Qt**, providing core features of a notepad application.

### ✨ Features
- Open and save text files  
- Edit text with standard operations (cut, copy, paste, undo, redo)  
- Find and replace text  
- Multiple dialogs for user input  
- Minimal UI with Qt framework  

---

## 🛠️ Tech Stack
- **Languages:** C++  
- **Frameworks:** Qt (for Text Editor), Console (for DOS)  
- **Concepts:** File system simulation, GUI programming, event-driven design  

---

## 🚀 How to Run

### DOS Simulator
1. Navigate to `DOS-Simulator` folder.  
2. Compile and run:
   ```bash
   g++ dos.cpp -o dos
   ./dos

### Text editor
1. Install QT creator and then past the files in it and run it
