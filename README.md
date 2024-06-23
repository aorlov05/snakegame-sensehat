
# Snake Game Sense Hat

Classic snake game implementation on the Raspberry Pi Sense Hat in C.

## Installation

Install the libsensehat dependency onto the Raspberry Pi:

```bash
git clone https://github.com/aorlov05/libsensehat.git
cd libsensehat/
bash build.sh
```

This installs the static library's headers into ~/include/sensehat and library file into ~/lib/sensehat.

You can then cd into this snake game project and build it with CMake:
```bash
  bash run.sh
```
And run the snake game executable in the generated build/ directory:
```bash
  ./build/snakegamesensehat
```