# ShopInventoryManager

This software is written to ease the day-to-day activities of small shops and businesses. The source code is written in C++, and is packaged as CMake Projects. This software has the following requirements:

- Operating System: Windows (tested and working on Windows 10 and 11, but should work for 8 and 7 as well)
- Compilers: MinGW-x64 compiler required. Additionally, if you want to use the recommendation system, MSVSC-2022 compiler required as well
- Storage: around 6 GB storage is required, however, if you want to use the recommendation system, you would need ~60-65 GB more space. Yes, I know its bonkers, but the fine people at OR-tools are to blame for this. They have written their CMakeLists.txt in such a way that it is difficult to just build and use the components that are required by optimizer. Still trying to figure out how to reduce the space required.
-  Libraries and Frameworks:
    - Qt: Version 6 is required
    - Google OR-tools: Will be automatically cloned while building
    - SQLite3: Already comes with this package
    - CMake: Minimum version 3.10 is required
    - Git: Required for automatically cloning OR-tools and all its dependencies

## Install Instructions

The install instructions for all dependencies as well as the software is given here:

### Git 

- To install git, just go to [this](https://github.com/git-for-windows/git/releases/download/v2.35.1.windows.2/Git-2.35.1.2-64-bit.exe) link, which will download the installer.
- Then run the installer, and keeping all settings default. 

### CMake

- To install CMake, just use this [online installer](https://github.com/Kitware/CMake/releases/download/v3.23.0/cmake-3.23.0-windows-x86_64.msi).
- When asked whether you want to add the variables to PATH or not, select "Add system variable to PATH for all users". 

### Compilers

- Visual Studio 2022 (This only needs to be installed if you plan to use the recommedation system)
    - It can be downloaded by going to this [link](https://visualstudio.microsoft.com/downloads) and downloading  **Visual Studio with C++**. 
    - Then just follow the install instructions to install it correctly. You might face the issue of the installer closing abruptly. To solve this, just fire up cmd, and run these 2 commands:

        ```
        cd "C:\Program Files (x86)\Microsoft Visual Studio\Installer"
        vs_installer.exe --locale en-US
        ```
        This should run the installer correctly. 9.5 GB required

    - While installing, in the workloads tab, select **Desktop Development with C++**. Additionally, if you are on Windows 10, in the individual components tab unselect "Windows 10 SDK (10.0.19041.0)" and instead of that select "Windows 10 SDK (10.0.20348.0)".

    - Click on install, and once you are done installing, restart your PC.

- MinGW-x64
    - The pre-built binaries can be downloaded from [here](https://github.com/brechtsanders/winlibs_mingw/releases/download/11.2.0-10.0.0-ucrt-r1/winlibs-x86_64-posix-seh-gcc-11.2.0-mingw-w64ucrt-10.0.0-r1.zip).
    - Once you download and extract this folder, go to the mingw64 folder, then to bin, and copy the full path to the bin folder. 
    - Then search for and open "Edit System Environment Variables", go to environment variables. Under the system variables section, double click on the "Path" environment variable, and add another entry.
    - Paste the path you just copied. This will allow your system to find the compiler.


### Qt
- Go to the [Qt Open Source Download](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) page, scroll down, and click on **Download the Qt Online Installer** button. 
- Once the installer is downloaded, run it. Follow the instructions. When you come to the **Select Components** page, Under Qt->Qt 6.2.4, select MinGW 11.2.0 64-bit. It will require about 3.5 GB of space. 
- After the installation is complete, you need to add the lib and bin folders inside your Qt installation to the PATH environment variable (just like you did for MinGW-x64). - Navigate to the place where you installed Qt, then go to the 6.2.4->mingw_64->bin folder and copy the full path. Paste it in your Path environment variable (just like you did for MinGW-x64 above). 
- Similarly go to the 6.2.4->ming_64->lib folder, copy the path, and paste it in your Path variable.

### Building the software
- Open cmd and run:
```
git clone https://github.com/Kshitij1K/ShopInventoryManager
cd ShopInventoryManager
configure_all
```
This will configure all the CMake projects. After this, copy the Dbmain.db database file from database\src\ directory and place it in main\build directory. This is so that the executable can find the database file.

After that, run the `make_all` command. This will build all files, and then run the software as well. You can run the software again by running the same command `make_all` (don't worry, the projects wont be built again every time you run this command).

For first time users, there are two users(1 regular employee and 1 admin) already created within the software, so that you can log in initially. After that you are free to create as many users (and log in as them) as you want.

Admin:
- Username: kabeer
- Password: 123

Employee:
- Username: rishk
- Password: 1234

### Building the OR-tools library to use the recommendation system
- First and foremost, MAKE SURE that you have ATLEAST 60-70 GB free space in the drive that you have cloned ShopInventoryManager on.
- Run the following commands in cmd, after navigating to the ShopInventoryManager folder:
```
cd optimizer
mkdir build
cmake .. -G "Visual Studio 17 2022"
cmake --build .
```

This will build optimizer.cpp

