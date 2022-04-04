cd Database/build
cmake --build .
cd ../..

cd StateMachine/build
cmake --build .

cd ../..

cd UI/build
cmake --build .

cd ../..

cd main/build
cmake --build .
shop_inventory_manager.exe
cd ../..