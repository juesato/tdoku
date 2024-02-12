
## MacOS

1. Make sure everything is running with Rosetta 2 (to emulate x86_64). 
The solver requires immintrin (via simd_vectors.h), so we'll need to compile
with Rosetta 2, which means we should also compile Minisat for Rosetta 2.

To start iTerm2 with Rosetta 2:

```
arch -x86_64 /Applications/iTerm.app/Contents/MacOS/iTerm2 &
```

2. Install minisat.

2a. Clone this fork (the original version is broken): https://github.com/agurfinkel/minisat

2b. Change the single occurrence of -soname to -install_name (since on MacOS the
flag has a different name)

2c. Follow the instrucitons:

```
make config prefix="/usr/local"
sudo make install
```

sudo is necessary.

3. Compile tdoku

3a. Test run: ./BUILD.sh should run fine
3b. Change MINISAT to ON in CMakeLists.txt
3c. On my Mac, the default include/static linking/dynamic linking paths weren't
set up properly, so I had to add them to ~/.bashrc:

```
export LD_LIBRARY_PATH="/usr/local/lib"
export DYLD_LIBRARY_PATH="/usr/local/lib"  # macos

export LIBRARY_PATH="/usr/local/lib"

export CPATH="/usr/local/include"
export C_INCLUDE_PATH="/usr/local/include"
export CPLUS_INCLUDE_PATH="/usr/local/include"
```

3d. Can compile again, either ./BUILD.sh (everything) or ./BUILD.sh generate
3e. Should run now, and see output on `./build/generate`

Other steps:

- May need to remove -fno-exceptions from all mentions in CMakeLists.txt, in
order to allow use of `throw` in the code.