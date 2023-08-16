# Flasher
## Utility for flashing

TODO: description

## Build

You will need Linux (tested on ArchLinux), CMake, libudev, ninja and c++ compiler.

Clone this repository with submodules:
```sh
git clone --recurse-submodules https://github.com/Alzymologist/Pilkki
```

Build code:
```sh
mkdir build
cd build
cmake .. -G Ninja
ninja
```

## Install
```sh
[sudo] ninja install
```

## Usage

Help message contains comprehensive information about usage:
```sh
pilkki --help
```
You should get output like this:
```
Pilkki - SWD Flasher

All the following arguments require connection to the hardware part of the SWD flasher
The address and size can be specified in either decimal or hexadecimal format (prefixed with 0x).
Both values must be multiples of a word (4 bytes).

Usage: pilkki  [options...] [SUBCOMMAND: connect, crc, erase, halt, id, read, reset, run, write, ]

Options:
     -v,--version : Print version (of this program). [implicit: "true", default: false]
        -?,--help : print help [implicit: "true", default: false]


Subcommand: connect
Connect to the target and halt it.
Usage: connect  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]


Subcommand: crc
Calculate CRC32 checksum of memory region on the target.
Usage: crc  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]
        -a,--addr : Starting address on the target. [default: 0x08000000]
      -l,--length : Length of the memory region to read (in bytes). [default: none]


Subcommand: erase
Erase firmware from the target.
Usage: erase  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]
        -a,--addr : Starting address on the target. [default: 0x08000000]
          --pages : Number of pages to erase. [default: none]


Subcommand: halt
Halt the target.
Usage: halt  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]


Subcommand: id
Get SWD Programmer Hardware ID.
Usage: id  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]


Subcommand: read
Read firmware from the target.
Usage: read  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]
        -a,--addr : Starting address on the target. [default: 0x08000000]
      -o,--output : Output file name: <filename>.(bin/hex) [default: out.bin]
      -l,--length : Length of the memory region to read (in bytes). [default: none]


Subcommand: reset
Reset the target (soft/hard).
Usage: reset  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]
      --hw,--hard : Hard reset. [implicit: "true", default: false]


Subcommand: run
Run the target.
Usage: run  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]


Subcommand: write
Write firmware to the target.
Usage: write  [options...]

Options:
        -p,--port : Serial port to interact with flasher. Autodetect if not specified. [default: none]
        -a,--addr : Starting address on the target. [default: 0x08000000]
       -i,--input : Input file name: <file_name>.(bin/hex) [required]
      -l,--length : Length of the memory region to write (in bytes). [default: none]
```

For more information feel free to look at source code.