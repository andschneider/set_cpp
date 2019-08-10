# set_cpp

This project is an attempt at creating a program that can play the game of SET[0] against human opponents. The goal is to have a Raspberry Pi with a camera and use OpenCV to perform image recognition and play (win) the game.

## why

The motivation for creating this comes from a time I was playing the game with friends and not doing as well as I thought I could. My frustrations were magnified by the fact that it seemed like a perfect game for a computer to play. Unhappy with losing, I set (no pun intended) out on this project. In addition, I wanted a project that would allow me to learn and practice C++.

## overview

The goal of the game of SET is to collect SETs of three cards. In the deck of 81 unique cards there are four properties that vary on each card. These properties are: __color__, __number__, __shape__, and __shading__. Each card has three possibilities in each property: *red, green, or purple* for color; *1, 2, or 3* for number; *diamond, oval, or squiggle* for shape; and *outlined, solid, or striped* for shading.

A SET is a collection of three cards where, in each property, either all possibilities are present or only one is present.

For example, three cards that are all __red__, all have __1__ shape, all are __oval__, and all have a __different__ shape would be a set.

If you map all the properties to 0, 1, or 2 (e.g. red = 0, green = 1, purple = 2, ect.) the previous SET could be described as:

card | color | number | shape | shading  
-----|:-----:|:------:|:-----:|:-------:
  1  |   0   |   1    |   1   |   0  
  2  |   0   |   1    |   1   |   1  
  3  |   0   |   1    |   1   |   2  

This mapping allows for a simple calculation of whether three cards form a SET. In each property, the sum of the cards (or the total sum) must be divisible by three. For example:

operation | color | number | shape | shading  
----:|:-----:|:------:|:-----:|:-------:
 sum |   0   |   3    |   3   |   3  
 %3  |   0   |   0    |   0   |   0  

By simply taking the modulo a SET can be determined if the result is 0.

## installation

*WIP*

This has only been ran on Ubuntu 16.04 at this time.

1) OpenCV needs to be installed. Their documentation[1] has platform specific instructions.
2) Build using CMake:

    ```bash
    cmake .
    ```

    ```bash
    make
    ```

3) Verify by running the tests:

    ```bash
    ./bin/all_tests
    ```

4) Or test a single card and for visual verifcation:

    ```bash
    ./bin/classifyCard ./images/r_3_o_h_noBorder.jpg
    ```

----

[0] [SET](https://www.setgame.com/set)

[1] [install OpenCV](https://docs.opencv.org/master/df/d65/tutorial_table_of_content_introduction.html)
