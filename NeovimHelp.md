# Neovim Movement Commands Cheat Sheet

### Basic cursor movement  
| Command | Description         |
|---------|---------------------|
| `h`     | Move left           |
| `j`     | Move down           |
| `k`     | Move up             |
| `l`     | Move right          |

---

### Word and line navigation  
| Command       | Description                      |
|---------------|--------------------------------|
| `w`           | Move to start of next word      |
| `b`           | Move to start of previous word  |
| `e`           | Move to end of current/next word|
| `0`           | Move to beginning of line       |
| `^`           | Move to first non-blank char    |
| `$`           | Move to end of line             |

---

### Screen navigation  
| Command        | Description                 |
|----------------|-----------------------------|
| `Ctrl + d`     | Scroll half-page down        |
| `Ctrl + u`     | Scroll half-page up          |
| `Ctrl + f`     | Scroll full page down        |
| `Ctrl + b`     | Scroll full page up          |
| `H`            | Move cursor to top of screen |
| `M`            | Move cursor to middle screen |
| `L`            | Move cursor to bottom screen |

---

### Jump to specific line  
| Command          | Description          |
|------------------|----------------------|
| `:<number>` + Enter | Jump to line number  |
| `G`              | Jump to end of file   |
| `gg`             | Jump to beginning     |

---

### Searching  
| Command      | Description                       |
|--------------|---------------------------------|
| `/pattern`   | Search forward for pattern       |
| `?pattern`   | Search backward for pattern      |
| `n`          | Repeat last search (same dir)    |
| `N`          | Repeat last search (opposite dir)|

---

### Window movement  
| Command        | Description                |
|----------------|----------------------------|
| `Ctrl + w h`   | Move to window left        |
| `Ctrl + w j`   | Move to window below       |
| `Ctrl + w k`   | Move to window above       |
| `Ctrl + w l`   | Move to window right       |
| `Ctrl + w w`   | Cycle through windows      |

---

### Tabs  
| Command      | Description         |
|--------------|---------------------|
| `:tabnew`    | Open new tab        |
| `gt`         | Go to next tab      |
| `gT`         | Go to previous tab  |
| `:tabclose`  | Close current tab   |

