Pilkki - Flasher Utility
===============

Description
-----------

TODO: Add a detailed description of the Flasher utility.

Prerequisites
-------------

### For Linux

*   CMake
*   Ninja
*   C++ Compiler
*   libudev

#### Installing Dependencies on Ubuntu

Specifically for Ubuntu (probably relevant for most debian distro), install the required packages:

```sh
sudo apt install ninja-build libudev-dev
```

### For MacOS

*   CMake
*   Ninja
*   GCC Compiler

#### Installing Dependencies on MacOS

Install the necessary tools using [Homebrew](https://brew.sh/):

```sh
brew install cmake ninja gcc
```

Building the Code
-----------------

### Cloning the Repository

Clone the repository with all its submodules:

```sh
git clone --recurse-submodules https://github.com/Kalapaja/Pilkki
```

### Compiling the Code

Navigate to the cloned directory and compile the code:

```sh
mkdir build 
cd build 
cmake .. -G Ninja 
ninja
```

### Installation

Install the utility:

```sh
sudo ninja install
```

### Verifying Installation

To verify the installation, check the installed version:

```sh
pilkki -v
```

The output should show `Pilkki (current version)`.

Usage
-----

*   Find the port to which your device is connected:

**Linux**    
```sh
ls /dev/ttyUSB*
```

**MacOS**    
```sh    
ls /dev/tty.* /dev/cu.*
```

*   Verify port by connecting to the device:
    
```sh
pilkki connect --port /port/address
```
    
*   Flash a new binary:
    
```sh
pilkki write --port /port/address --input /path/to/your/binary.bin
```
    
### Getting Firmware Binary

Build the binary using code in [kampela-firmware](https://github.com/Kalapaja/kampela-firmware) repo or get compiled binary from the [releases](https://github.com/Kalapaja/kampela-firmware/releases) section
