# build directory

NOTE: these steps all assume you will be running commands from the repo root (i.e. .. from here)

To wipe the configuration remove all files in this directory:
`find ./build/ -not -iname "README.md" -not -ipath "./build/" -delete -empty`

To configure cmake to use this directory:
`cmake -DCMAKE_BUILD_TYPE=Debug -S . -B ./build`

To build via unix makefile from this directory:
`make -C ./build`

