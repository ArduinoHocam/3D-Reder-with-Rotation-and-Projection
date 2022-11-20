# Polar-Cartesian-conversion

Youtube Video:
[3D Rendering with Rotation and Projection, Computer Graphics](https://www.youtube.com/watch?v=zjUquEwRjJk&t=997s)

For the SDL2 Tutorials: https://www.willusher.io/pages/sdl2/
For the SDL2 wiki page: https://wiki.libsdl.org


## How to build?
### Linux

- If you have installed the SDL2 library on your Linux Machine,
- If you have installed the Eigen library on your Linux Machine,
- You can build the main.cpp by this command : `g++ main_with_Eigen.cpp -I /usr/include/eigen3 -L/usr/local/lib -lSDL2`
- Run the created executable by `./a.out`
- You should see the opening window and a rotating line in the circle as follows:
![](https://github.com/ArduinoHocam/3D-Reder-with-Rotation-and-Projection/blob/main/example_linux.gif)


### Arduino & OLED Screen

- In order to test on the Arduino Nano & 0.96inch OLED Screen, use the following schematic
![](https://github.com/ArduinoHocam/Polar-Cartesian-conversion/blob/main/arduino-oled-display-connections.png)
- OLED output should be as follows:

![](https://github.com/ArduinoHocam/3D-Reder-with-Rotation-and-Projection/blob/main/example_arduino_oled.gif)
- You can try this project online [wokwi_online_arduino](https://wokwi.com/projects/347390722698117715)
