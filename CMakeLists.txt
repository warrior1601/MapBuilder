# # This CMakeList file will create the Observer executable
cmake_minimum_required( VERSION 3.9.2 )

foreach(p
        CMP0071 # 3.10: Let AUTOMOC and AUTOUIC process GENERATED files
        )
    if(POLICY ${p})
        cmake_policy(SET ${p} NEW)
    endif()
endforeach()

# The name of the project and its curent version
PROJECT( Map_Builder VERSION 1.2.2 )

# The CMake build process might generate some new files in the current directory. This makes sure they can be found.
set( CMAKE_INCLUDE_CURRENT_DIR ON )

# This allows CMake to run one of Qt's build tools called moc if it is needed. moc.exe can be found in Qt's bin directory. We'll look at what moc does later.
set( CMAKE_AUTOMOC ON )
set( CMAKE_AUTOUIC ON )
set( CMAKE_AUTORCC ON )

# Find the Qt widgets package. This locates the relevant include and lib directories, and the necessary static libraries for linking.
find_package( Qt5Widgets )

# Doing the same for VTK
find_package( VTK REQUIRED )
include( ${VTK_USE_FILE} )

# This project contains many header files the "include_directories" sets the path for the header files to be located
include_directories( include )

set( UIS mainwindow.ui )
qt5_wrap_ui( UI_Srcs ${UIS} )

if (WIN32)
    # Define the executable output and its sources
    add_executable(Map_Builder #WIN32
        source/main.cpp
        source/mainwindow.h          source/mainwindow.cpp           source/mainwindow.ui
	source/terrain_square.h      source/terrain_square.cpp
	source/grid.h		     source/grid.cpp
	source/terrain_type.h        source/terrain_type.cpp
	source/mouse_interactor.h  source/mouse_interactor.cpp
        )
else()
    # Define the executable output and its sources
    add_executable(Map_Builder MACOSX_BUNDLE
        source/main.cpp
        source/mainwindow.h          source/mainwindow.cpp           source/mainwindow.ui
	source/terrain_square.h      source/terrain_square.cpp
	source/grid.h		     source/grid.cpp
	source/terrain_type.h        source/terrain_type.cpp
	source/mouse_interactor.hpp  source/mouse_interactor.cpp
        )
endif()

# Tell CMake that the executable depends on the Qt::Widget libraries.
target_link_libraries( Map_Builder Qt5::Widgets )

# Tell CMake that the executable depends on the VTK libraries
target_link_libraries( Map_Builder ${VTK_LIBRARIES} )
