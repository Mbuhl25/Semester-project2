```
╰$ g++ \        
  -I external/min2phaseCXX/include \
  src/CppCubeSolver.cpp \
  -L external/min2phaseCXX/build \
  -lmin2phase \
  -o yourprogram \
  -Wl,-rpath,external/min2phaseCXX/build
```