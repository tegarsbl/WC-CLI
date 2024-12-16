# WC-CLI - A Simple Word Count CLI Tool

`WC-CLI` is a command-line tool for counting words, lines, bytes, and characters in a text file. It provides a clean and interactive output with the help of a progress bar and color formatting.

## Features

- Count lines, words, bytes, and characters in a file.
- Interactive progress bar during processing.
- Beautifully formatted output using `tabulate` and `termcolor`.

## Installation

You can install WC-CLI either globally or locally.

### For Linux or Termux (System-Wide)

1. Clone the repository:
   ```bash
   git clone https://github.com/yourusername/wc-cli.git
   cd WC-CLI
   ```
2. Build and install the project:
   ```bash
   make
   make install
   ```

This will compile the source code and install the binary (wct) into /usr/local/bin for global access.


3. Verify the installation:
   ```bash
   wct -h
   ```
   
## Uninstall

4. Uninstall the project:
   ```bash
   make uninstall
   ```

5. Clean build files:
   ```bash
   make clean
   ```

## Usage

   ```bash
   wct [OPTIONS] [FILE]
   ```

### Options:

- `-l : Count lines`
- `-w : Count words`
- `-c : Count bytes`
- `-m : Count characters`
- `-h : Display help and usage information`


### Example:
   ```bash
   wct -lwm file.txt
   ```

This will count lines, words, and characters in file.txt.

   
