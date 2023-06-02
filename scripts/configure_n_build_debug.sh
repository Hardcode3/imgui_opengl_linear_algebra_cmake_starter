#!bin/bash

echo "> Starting the configuration of the project via a bash script"
echo "> Mode: configure and build debug"
echo ""

cd ..
mkdir build
cd build
cmake ..
cmake -DCMAKE_BUILD_TYPE=Debug .

echo "> Debug configuration and build of the project successful"

echo ""
echo "> Press any key to close the window"
# Wait for input from the user
read -n 1 -s -r -p ""

# The script will stay open until the user presses a key
