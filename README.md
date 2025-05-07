# numerical
Library for numerical computations

# Dependencies
autodiff and eigen are header only. 

## NLOPT
Configure build process 
```
cd nlopt
mkdir build
cd build
cmake .. -G "MinGW Makefiles" -DCMAKE_C_COMPILER=gcc -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release
```

Build files
```
mingw32-make
```

Install (as Admin)
```
mingw32-make install
```
Installs into `C:\Program Files (x86)\nlopt`.
Add `C:\Program Files (x86)\nlopt\bin` to your PATH.

Link when compiling
```
g++ .\main.cpp -I"C:\Users\Dennis\Documents\Projekte\numerical" -I"C:\Program Files (x86)\nlopt\include" -L"C:\Program Files (x86)\nlopt\bin" -lnlopt -std=c++17 -o main
```