# Flash Game Downloader

![C](https://img.shields.io/badge/Language-C-blue.svg)
![License](https://img.shields.io/badge/License-GPL--3.0-green.svg)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-lightgrey.svg)

A lightweight, multi-platform C application designed to automatically download multi-file Flash games for local preservation and analysis.

Given the URL of the main Flash file (`.swf`) and its dependent configuration files (e.g., XML manifests), **Flash Game Downloader** recursively fetches all required game assets, recreating the correct directory structure locally.

---

## Key Features

- **Automated Multi-File Retrieval:** Downloads the main `.swf` asset alongside sub-assets referenced in configuration files (XML, assets list, etc.).
- **Cross-Platform:** Native compilation on Linux (Debian, Ubuntu, Fedora) and Windows (via MSYS2 / MinGW-w64).
- **Asynchronous I/O & Networking:** Built using `libuv` and `libcurl` for efficient network operations and file management.
- **CLI-Driven Workflow:** Fast execution with simple command-line arguments.

---

## Quick Start

### 1. Download
Download the latest executable binary for your operating system from the [{Releases}](https://github.com/{username}/{repository}/releases) section (or compile from source).

### 2. Execution
Open your terminal/command prompt at the location of the binary and run the executable with the required flags.

```bash
./flash-game-downloader -l -n "GameName" -m "https://example.com/game/main.swf" "files/config.xml"
```

---

| Flag | Description |
| :--- | :--- |
| `-l` | Enables command line interface (CLI) mode. |
| `-n` | Specifies the game name (used as the target directory name). |
| `-m` | Primary URL of the main Flash (`.swf`) file. |
| `[path]` | *(Positional)* Relative path of additional manifest/asset files to download relative to the main URL. |



## Building from Source
### Dependencies

The project relies on the following C libraries:

- `libcurl` Network data transfer
- `glib-2.0` Core data structures and utility functions

- `libuv` Cross-platform asynchronous I/O (make folder)

---

### Debian / Ubuntu

`sudo apt update`

`sudo apt install build-essential libcurl4-openssl-dev libglib2.0-dev libuv1-dev
`

### Fedora
`sudo dnf install gcc make libcurl-devel glib2-devel libuv-devel`


### Windows (with MSYS2 - UCRT64)
From the MSYS2 UCRT64 terminal, install the toolchain and required packages:

`
pacman -S --needed \
  mingw-w64-ucrt-x86_64-gcc \
  mingw-w64-ucrt-x86_64-make \
  mingw-w64-ucrt-x86_64-pkg-config \
  mingw-w64-ucrt-x86_64-curl \
  mingw-w64-ucrt-x86_64-glib2 \
  mingw-w64-ucrt-x86_64-libuv
`

---


## Compilation
Once dependencies are installed, compile the project using GCC:
`gcc main.c -o flash-game-downloader $(pkg-config --cflags --libs glib-2.0 libcurl libuv)`


## Local Development & Testing
When developing or testing game downloads locally, serve test files using a local web server (such as Apache, Nginx, or XAMPP).

Note on macOS support: While macOS is not officially tested, the codebase relies on cross-platform libraries (`libuv`, `glib`, `libcurl`) and should compile using standard Homebrew dependencies.


---

## Roadmap

Future planned features and improvements for upcoming releases:



- [ ] Graphical User Interface (GUI): Develop a native GTK3 desktop interface.

- [ ] Manifest Export: Export a .txt manifest file listing all downloaded relative paths alongside the root URL.

- [ ] Batch Import/Download: Allow offline/batch downloading from pre-generated .txt manifest files to bypass file parsing.

- [ ] Archive Integration: Implement game asset analysis to submit missing assets to the Wayback Machine.

- [ ] Automated Decompilation Analysis: Extract missing asset paths directly from .swf bytecode (using FFDec / JPEXS) or runtime execution logs from Flash Player Debugger.

---

## Known TODOs
- [ ] Add explicit HTTP error handling (e.g., 404 Not Found, 403 Forbidden) with custom user notices.

- [ ] Ensure atomic file/folder operations (verify downloaded integrity before moving assets to target folders).

- [ ] Sanitize relative vs. absolute URLs during parsing to ensure safe filesystem output.


## Contributing & Support

Forks and Pull Requests are welcome! Feel free to open an issue to report bugs or suggest new features.

Please note: Maintenance and response times may vary depending on project availability.

## Acknowledgments
* GCC (GNU Compiler Collection)

* MinGW-w64 & MSYS2

* curl / libcurl

* libuv

* GLib (GNOME Project)

* Google Gemini in the mentioned parts

---

## License

Distributed under the **GNU General Public License v3.0.** See the LICENSE file for details.







