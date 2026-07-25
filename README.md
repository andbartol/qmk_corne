# andbartol - QMK Keymap

Personal QMK keymap for the [Corne (crkbd/rev1)](https://github.com/foostan/crkbd) split keyboard.

## Features

| Feature | Description |
|---------|-------------|
| **8 layers** | BASE, NUMS (numbers/symbols), SYMB (symbols), FKEY (function keys), MVWN (window navigation), MOUS (mouse), VIML (vim motions), VIMN (vim number row) |
| **Auto-close** | Typing an opening bracket (`{[(`) followed by a closing bracket within `AUTOCLOSE_TERM` ms inserts the closing character and moves cursor between them |
| **Power accent** | On non-Windows only: hold a vowel (`a e i o u`), then press <kbd>Space</kbd> to insert a grave-accented letter (e.g., `è`); press <kbd>Space</kbd> again to cycle to acute-accented (e.g., `é`). Disabled on Windows, where the Quick Accent utility from [PowerToys](https://github.com/microsoft/PowerToys) can be used instead. |
| **Vim layer** | **Experimental** — Vim-style navigation via a dedicated layer. May not work correctly in all applications. Disabled by default (see `keymap.c`). |
| **Password macro** | `KC_PASS` sends a predefined password string (set in `passwd.c`) |
| **Ctrl+' / Ctrl+Esc** | Maps to <kbd>PgUp</kbd> / <kbd>PgDn</kbd> |
| **Ctrl+Alt+Backspace** | Maps to <kbd>Delete</kbd> |

## Layers

### BASE
Standard QWERTY layout with thumb cluster: `MVWN | NUMS | Space | Enter | SYMB | Alt`.

### NUMS
Number row, mouse layer access (<kbd>Z</kbd>), window close (<kbd>D</kbd>), Alt+F3 (<kbd>C</kbd>), vim-style arrow keys on <kbd>H</kbd><kbd>J</kbd><kbd>K</kbd><kbd>L</kbd>, Alt+Tab on <kbd>Q</kbd>.

### SYMB
Standard punctuation and symbols layer: shifted numbers on top row, brackets/slashes/backtick on right hand.

### FKEY
F1-F10 are on the same spots as the number row in the NUMS layer. F11 and F12 are on the keys directly below F1 and F2. Also includes media controls on the rightmost keys and the `KC_PASS` macro on <kbd>Z</kbd>.

### MVWN
Useful for windows: while on this layer the windows key is always pressed. Vim-style arrow keys to move the windows around and <kbd>Lock</kbd> has been moved one button to the right to not collide with the right arrow.

### MOUS
Mouse control: mouse movement on right hand with vim-style movements, scroll wheel, acceleration levels via <kbd>C</kbd>/<kbd>V</kbd>/<kbd>B</kbd>, mouse buttons on thumb cluster.

### VIML (Vim Layer) — Experimental

Disabled by default. To enable, uncomment `#define KC_VESC TD(TD_VESC)` in `keymap.c:39`.

Vim-like motions:
- **`w`/`b`**: Jump words (Ctrl+Right / Ctrl+Left)
- **`d`**: Delete prefix (combine with `w`, `b`, `h`, `l`, arrows, home/end)
- **`x`**: Delete character under cursor (Del)
- **`c`**: Change (delete then insert)
- **`i`** / **`I`** (Shift+I): Enter insert mode at cursor / beginning of line
- **`a`** / **`A`** (Shift+A): Enter insert mode after cursor / end of line
- **`h j k l`** / **arrows**: Move cursor (respects delete prefix and count)
- **`Home`** / **`End`**: Go to beginning/end of line (or delete to it with `d`)
- **`u`**: Undo (Ctrl+Z)
- **`Esc`** / **Ctrl+Esc**: Exit vim layer / Redo (Ctrl+Shift+Z)
- **`0-9`**: Count prefix for motions
- **`VIMN`** thumb key: Temporary number overlay on top row

### VIMN
Same as VIML but with number keys 0-9 on the top row instead of vim commands.

## Windows vs Linux

The firmware adapts to the OS based on which half of the keyboard is connected to the computer. By default the left half has the Windows configuration and the right half has the Linux configuration.

| Behavior | Windows (left half) | Linux (right half) |
|----------|---------------------|---------------------|
| Close window | <kbd>Alt</kbd>+<kbd>F4</kbd> | <kbd>Super</kbd>+<kbd>Shift</kbd>+<kbd>Q</kbd> (for i3) |
| Lock screen | <kbd>Super</kbd>+<kbd>L</kbd> | <kbd>Super</kbd>+<kbd>Shift</kbd>+<kbd>M</kbd> |
| Power accent | Disabled (use PowerToys) | Enabled |
| Password string | Windows-specific | Linux-specific |
| Tap code delay | 50ms | 0ms |
| Double report (see below in the Key Settings) | Enabled (for RDP compat) | Disabled |

## Configuration

### Build Options (`rules.mk`)
- Tap Dance, Mouse Keys, Digitizer enabled
- RGB Lighting and Console disabled

### Key Settings (`config.h`)
- `MASTER_LEFT`: Left half is the master
- `WINDOWS_CONF`: Defines OS-specific shortcuts for Windows (close window, lock screen, password, etc.).
- `DOUBLE_REPORT`: Sends each modifier key event twice, fixing modifier key reliability when using RDP. Requires the patch from [PR #19449](https://github.com/qmk/qmk_firmware/pull/19449).
- `AUTOCLOSE_TERM`: 200ms window for auto-close
- `POWERACCENT_TERM`: 200ms hold time to trigger accent
- `TAP_CODE_DELAY`: 50ms tap delay on Windows

### Password (`passwd.c`)
Edit `passwd.c` to set a different password string. Separate definitions for Windows and non-Windows builds.

## Building

Clone into your QMK firmware's `keyboards/<keyboard>/keymaps/andbartol/` directory and build:

```sh
qmk compile -kb crkbd/rev1 -km andbartol
```
