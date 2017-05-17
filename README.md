Introduction
--------------------
1. Window
This directory contains *CMake* files that can be used to build this project
with *MSVC* on *Windows*. You can build the project from *Command Prompt*
and using an *Visual Studio* IDE.

You need to have [CMake](http://www.cmake.org), [Visual Studio](https://www.visualstudio.com), [Opencv](http://opencv.org/)

Getting Dependencies
--------------------
1. OpenCV 2.4
	* Download OpenCV prebuild package and install it
	* Add system path
		-- CMAKE_PREFIX_PATH=C:\local\opencv\build;%CMAKE_PREFIX_PATH%

Environment Setup
--------------------
Open the appropriate Command Prompt from the Start menu.

For example VS2013 x64 Native Tools Command Prompt:

    C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64>
Change to your working directory:

    C:\Program Files (x86)\Microsoft Visual Studio 12.0\VC\bin\amd64>cd C:\Path\to
    C:\Path\to>
Where C:\Path\to is path to your real working directory.

CMake Configuration
------------------------
CMake supports a lot of different generators for various native build systems. We are only interested in Makefile and Visual Studio generators.

We will use shadow building to separate the temporary files from the project source code.

Create a temporary build folder and change your working directory to it:

    C:\Path\to\project\cmake>mkdir build & cd build
    C:\Path\to\project\cmake\build>

The Makefile generator can build the project in only one configuration, so you need to build a separate folder for each configuration.

To start using a Release configuration:

    C:\Path\to\project\cmake\build>mkdir release & cd release
    C:\Path\to\project\cmake\build\release>cmake -G "NMake Makefiles" ^
 -DCMAKE_BUILD_TYPE=Release ^
 -DCMAKE_INSTALL_PREFIX=../../../../install ^
 ../..
It will generate nmake Makefile in current directory.

To use Debug configuration:

    C:\Path\to\project\cmake\build>mkdir debug & cd debug
    C:\Path\to\project\cmake\build\debug>cmake -G "NMake Makefiles" ^
    -DCMAKE_BUILD_TYPE=Debug ^
    -DCMAKE_INSTALL_PREFIX=../../../../install ^
    ../..
It will generate nmake Makefile in current directory.

To create Visual Studio solution file:

    C:\Path\to\project\cmake\build>mkdir solution & cd solution
    C:\Path\to\project\cmake\build\solution>cmake -G "Visual Studio 12 2013 Win64" ^
    -DCMAKE_INSTALL_PREFIX=../../../../install ^
    ../..
It will generate Visual Studio solution file project.sln in current directory.

Compiling
------------------
To compile project:

    C:\Path\to\project\cmake\build\release>nmake
or

    C:\Path\to\project\cmake\build\debug>nmake
And wait for the compilation to finish.

If you prefer to use the IDE:

Open the generated project.sln file in Microsoft Visual Studio.
Choose "Debug" or "Release" configuration as desired.
From the Build menu, choose "Build Solution".
And wait for the compilation to finish.

Testing
-----------------
To run unit-tests, Please run:

    C:\Path\to\project\cmake\build\release\bin>inspectiontest.exe

Question
-----------------
Any other question. please contact *chenliang*.