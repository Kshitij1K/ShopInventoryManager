cd Database/build
cmake .. -G "MinGW Makefiles"
cd ../..

cd StateMachine/build
cmake .. -G "MinGW Makefiles"
cd ../..

cd UI/build
cmake .. -G "MinGW Makefiles"
cd ../..

cd main/build
cmake .. -G "MinGW Makefiles"
cd ../..