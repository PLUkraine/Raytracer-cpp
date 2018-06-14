# Raytracer-cpp
Implementation of a raytracing algorithm for CG.

## Features
This project features an implementation of a basic raycasting algorithm to create rich and beautiful images. It is capable of rendering spheres, ellipsoids and triangles.

To shade the scene the Blinn-Phong lighning model was used. In addition, this project has recursive raytracing imlemented to support reflectivity (and refraction in a future).

It doesn't feature early collision test to reduce number of ray-object intersection tests yet. However, it features multithreaded solution to speed the rendering process up.

## Dependencies
This project uses [GLM](https://glm.g-truc.net/0.9.9/index.html) and [FreeImage](http://freeimage.sourceforge.net/) libraries.
Include both of them before compiling this application.

*FreeImage* is used only for saving the image to a file. You can replace it if you have troubles compiling it for your system.

## Screenshots

Default Scene

![screenshot3](https://image.ibb.co/gBY3co/out.png)

Standford Dragon

![screenshot4](https://image.ibb.co/jxU408/scene7.png)

1000 Spheres

![screenshot2](https://image.ibb.co/iVygkJ/scene5.png)

Table with 4 spheres and 2 ellipsoids

![screenshot1](https://image.ibb.co/bDJ8Xy/scene4_specular.png)



