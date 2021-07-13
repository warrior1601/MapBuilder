# MapBuilder
3D Map Builder for RPGs

MapBuilder utilizes QT and VTK to allow a user to build a scene by importing STL files. In this demo STL files from thingiverse and DragonLock are used. The program is designed to allow the user to import and calibrate their own STL files, to be used as terrain types (tile toppers) Once imported and calibrated the program writes these settings to a text file for ease of future use.

Another feature of this program is that the height of each grid square can be edited. A simple hill function with an elevation filter is provided which enables the user to create a more dynamic landscape. 

Once a scene is built it can be exported as a VRML file. This is a simple way to store the scene with all the chosen color options. Unfortunately, VRML files are not editable with this program. Future updates to this program will see that the save file will be a text file that can be loaded by the program with instructions on how to rebuild your scene.

# ScreenShots