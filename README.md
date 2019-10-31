# OpenStreetMap Route Planner

This Route Planner can find the shortest path between two points on [OpenStreetMap](https://wiki.openstreetmap.org/wiki/Main_Page) using A star search.

<img src="map.png" width="600" height="450" />

## Cloning

When cloning this project, be sure to use the `--recurse-submodules` flag. Using HTTPS:
```
git clone https://github.com/barzanisar/Astar-Route-Planner.git --recurse-submodules
```
or with SSH:
```
git clone git@github.com:barzanisar/Astar-Route-Planner.git --recurse-submodules
```

## Dependencies for Running Locally
* cmake >= 3.11.3
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 7.4.0
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same instructions as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)
* IO2D
  * Download and extract a fresh build of libc++ from [here](https://releases.llvm.org/download.html). For example, for     ubuntu 18.04, download the [pre-built binary](https://releases.llvm.org/9.0.0/clang+llvm-9.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz).
  * Export appropriate CXX and LD flags to make clang use this version of the standard library (replace NEWPATH with a path of extracted archive contents):
  ```
  export CXXFLAGS="-nostdinc++ -isystemNEWPATH/include/c++/v1"
  export LDFLAGS="-LNEWPATH/lib -Wl,-rpath,NEWPATH/lib"
  ```
   * Installation steps for Linux:
      1. Refresh apt: `sudo apt update`
      2. Install GCC: `sudo apt install build-essential`
      3. Install CMake: `sudo apt install cmake`
      4. Install Cairo: `sudo apt install libcairo2-dev`
      5. Install graphicsmagick: `sudo apt install libgraphicsmagick1-dev`
      6. Install libpng: `sudo apt install libpng-dev`

     ```
     git clone --recurse-submodules https://github.com/cpp-io2d/P0267_RefImpl
     cd P0267_RefImpl
     mkdir Debug
     cd Debug
     cmake --config Debug "-DCMAKE_BUILD_TYPE=Debug" ..
     cmake --build .
     sudo make install
     ```
    * Installation instructions for all other operating systems can be found [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)
 
## Compiling and Running

### Compiling
To compile the project, first, create a `build` directory and change to that directory:
```
cd Astar-Route-Planner
mkdir build && cd build
```
From within the `build` directory, then run `cmake` and `make` as follows:
```
cmake ..
make
```
### Running
The executable will be placed in the `build` directory. From within `build`, you can run the project as follows:
```
./OSM_A_star_search
```
Or to specify a map file:
```
./OSM_A_star_search -f ../<your_osm_file.osm>
```
You will be prompted to enter the x,y coordinates of the two points on the map for which you want to plan the route.

## Testing

The testing executable is also placed in the `build` directory. From within `build`, you can run the unit tests as follows:
```
./test
```

