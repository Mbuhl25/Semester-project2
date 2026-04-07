
```
cd ./external/min2phaseCXX
mkdir build
cd build
cmake ..
make
```

Check if it created this file:
```
./min2phaseCXX/build/libmin2phase.so
```

Now in the root of the project run:
```
g++ \        
  -I external/min2phaseCXX/include \
  src/CppCubeSolver.cpp \
  -L external/min2phaseCXX/build \
  -lmin2phase \
  -o testprogram \
  -Wl,-rpath,external/min2phaseCXX/build
```

This will make an executable called "testprogram". Run it with
```