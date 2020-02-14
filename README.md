## Introduction

A game like candy-crush, called VraXaPsaIII. Programmed using OpenGL library.
This game was developed as an assignment for the undergraduate course Computer Graphics and Interactive System of the Department of Computer Science and Engineering at the University of Ioannina.

## How to run

To compile run on terminal &quot;_g++ game.cpp -o VraXaPsaIII -lglut -lGLU -lGL_ &quot;.
Then just run ./VraXaPsaaIII to play the game.

Or you can just use the Makefile.

## Develop strategy

The basic idea is using a 15x15 grid as a layout (what the user sees).
From there we use a double buffer to make the changes.

## How to play

Starting the game the users can see a 15x15 grid of beige cubes.

By pressing right click you can access the menu. From there , you can choose the START GAME option.

Randomly the grid is now with different colors and shapes.
You can swap 2 shapes by left clicking one, and then click again the one you want to swap with.
You can only swap with up ,down ,left and right. If you click something else the click cancels.

If by swaping you create 3 or more same shapes and color they destroy. For every destroyed shape you get 10 points.

You can move shapes into empty spaces.

After 30 moves the game is over.

## Camera

There is a 3D camera you can move with the keys &quot;W&quot;, &quot;A&quot;, &quot;S&quot;, &quot;D&quot; for x and y axis.

With F1 and F2 you can zoom in/out.

With F4 camera resets to the starting position.

## Screeshots
![Iddle](https://github.com/Peter-Sav/Candy-Crush/blob/master/screenshots/86348330_191224805423450_6113790825215295488_n.png)
![Start Game](https://github.com/Peter-Sav/Candy-Crush/blob/master/screenshots/86457850_692981594901033_2479558368864239616_n.png)
![Rotate Camera](https://github.com/Peter-Sav/Candy-Crush/blob/master/screenshots/86386930_491856724859630_3237267260749905920_n.png)
![Game Over](https://github.com/Peter-Sav/Candy-Crush/blob/master/screenshots/86386253_741431406264771_8683383300720427008_n.png)
