# ShopInventoryManager

This software is written to ease the day-to-day activities of small shops and businesses. The source code is written in C++, and is packaged as CMake Projects. This software has the following requirements:

- Operating System: Windows (tested and working on Windows 10 and 11, but should work for 8 and 7 as well)
- Compilers: MinGW-x64 compiler required. Additionally, if you want to use the recommendation system, MSVSC-2022 compiler required as well
- Storage: around 2 GB storage is required, however, if you want to use the recommendation system, you would need 52 GB space. Yes, I know its bonkers, but the fine people at OR-tools are to blame for this. They have written their CMakeLists.txt in such a way that it is difficult to just build and use the components that are required by optimizer. Still trying to figure out how to reduce the space required.
-  Libraries and Frameworks:
    - Qt: Version 6 is required
    - Google OR-tools: Will be automatically cloned while building
    - SQLite3: Already comes with this package
    - CMake: Minimum version 3.10 is required
    - Git: Required for automatically cloning OR-tools and all its dependencies

## Install Instructions

The install instructions for all dependencies as well as the software is given here:

### Compilers

- Visual Studio 2022 can be downloaded by going to this [link](https://visualstudio.microsoft.com/downloads) and downloading  **Visual Studio with C++**. Then just follow the install instructions to install it correctly.

- MinGW-x64 pre-built binaries can be downloaded from [here](drive.google.com).


### Qt
Go to the [Qt Open Source Download](https://www.qt.io/download-open-source?hsCtaTracking=9f6a2170-a938-42df-a8e2-a9f0b1d6cdce%7C6cb0de4f-9bb5-4778-ab02-bfb62735f3e5) page and click on **Download the Qt Online Installer** button. Once the installer is downloaded, run it, and select 





