# MiniRT
A simple ray tracer that renders spheres, cylinders and planes. It does that by reading a scene description.  
There is a spot light and ambient lighting and colors.   
The detailed project description is in the pdf file.  
The scenes had to be written in a certain format, specified in the pdf.  


## Usage
This project was written for and compiled on a Mac.  
We use libmlx42 and that needs glfw. The mlx42 is downloaded automatically, glfw must be installed.
```
make bonus  
./miniRT scenes/<scene>
```
For instance
```
./miniRT scenes/test_sphere_and_cylinder.rt
```
Scenes are in the scenes folder. Rendering might take a while.

## Caveats
This project was a 42School project, we had to program according to a strict norm, for instance using only while loops, having only 25 lines per function, not using inline comments etc.

## Thank you
This was a team project with the phenomenal Mohamed Ben Hassen (mben-has).  
Mohammed programmed the camera, and I the colored the pixels.  
