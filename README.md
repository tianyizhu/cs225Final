# cs225Final

## to compile:

cd build

add the .dat files

add and cleanup the motion folder

g++ ../src/main.cpp ../src/io.cpp ../cs225/PNG.cpp ../cs225/HSLAPixel.cpp ../lodepng/lodepng.cpp -o main

g++ ../src/test_draw_earth.cpp ../cs225/PNG.cpp ../cs225/HSLAPixel.cpp ../lodepng/lodepng.cpp -o exe
