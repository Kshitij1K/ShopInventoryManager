cd Database
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cd ../..

cd StateMachine
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cd ../..

cd UI
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cd ../..

cd main
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
cd ../..