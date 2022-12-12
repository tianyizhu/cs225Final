# CS 225 Final Project
Team members: 

James Zhu (tianyi9@illinois.edu)

Letian Hu (letianh3@illinois.edu)

Yibai Wang (yibaiw2@illinois.edu)

Zixiang Qu (zixiang7@illinois.edu)

(All names sorted in alphabetical orders)


## Presentation

The short video of our presentation can be found at: ------------------------------

## Final Purpose

This project enables users to look for their most preferred path between two airports. The output may vary depends on user’s preference, the shortest path, or the path that requires the least connecting flights.

## Use of algorithms (Answer for our leading questions)

We used different algorithms-based user's preference. If the user intends to simply search for the shortest path, then we use dijsktra algorithm. If we need to search for the option that need least connecting flights, then we use Iterative Deepening Depth-First Search to find the path with least number of edges and pick the shortest one if there are more than one choice. We did not implement BFS algorithm since IDDFS is an easier way to record every edge we been through, and try every path with the least amount of connecting flights and see which one is the best choice. We also utilized many geographical projection formulas to generate plane route animations. 

The data we use are text files that download from openflights.org. We used all these 67663 lines of route data, took all of them into consideration. As the data are the same as .txt files, they can be read directly by file steam and processed as strings. Each line of the file contains a route, described by the Airline, Airline ID, Source airport, Source airport ID, Destination airport, Destination airport ID, Codeshare, Stops, and Equipment. They are clearly separated by commas, and only contain letters and numbers, therefore can be very easily identified by the program.
The data is very well formatted, with each line includes nine data separated by eight commas, and no special cases in them, we can process them by straightforward logic without worrying about edge cases. Some "Codeshare" data are left blank, but the commas are still there. We can just ignore "Codeshare" data as it's unrelated to our project.



## Generate weighted directed graph
The second step is to generate a weighted directed graph. We constructed the graph by considering the airports as vertices and different routes to be the edges. We also input the distance between each two airports and record them as the weight of edges. All distances were calculated using mathematical formulas based on airports' latitudes and longitudes. After all that, we stored the graph into an adjecent matrix. The distance between each two airports is very accurate, as same as the official data we can find online (the total distance between the start airport and destination will be calculated as the sum of distances between every adjacent airports alongt the path, if there exists any transfer flight). 

## Find the shortest path

As stated above in the "Use of Algorithm", we use dijsktra to find the shortest path between two airports (the path that has the least sum of weight).

## Find the path with least connecting flights

As stated above in the "Use of Algorithm", we use IDDFS instead of BFS to find all paths with least edges and pick the one that has the least sum of weight as our final choice.

## Generate plane route animation

Then we generate a plane route animation using many geographical projection formulas. It can draw the path onto a plain world map and then use it to generate gif for a spinning earth model.

## The output and correctness of each algorithm

We test the correctness of each algorithm by using the codes we wrote in test_draw_earth.cpp and main.cpp, including the commented lines, such as some necessary print lines (cout<< << << endl;).

We built a search interface that can be used in the terminal:

By entering start and destination airport code along with a enter after each of them, three different preferences will be provided:
1) shortest distance onboard.  2) least transfer flights.  3) take a look at both.

Then the path will be provided, and you can clearly see all the airports that involved in this path, also the total distance (Kilometers) for this trip.

You can also choose to generate the path animation or not, and it will start generating the gif after you name the output file.

For example, I want to find the path from SHA to USH that has least transfer flights and save the gif in "Shortes.gif", this is what I should do after "./main" step by step: (Pick SHA and USH for example because the path will be complicated enough for us to see the differences between different preferences we choose above.)

SHA

USH

——————————

2

——————————

yes

——————————

Filename

——————————

The interface will looks like:

Welcome to plane path finder!!

Enter your start and destination ariport code:

SHA

USH

Choose the flight route you prefer:

1) shortest distance onboard.  2) least transfer flights.  3) take a look at both.

your choices:2

least transfer flights:

 -- "SHA" -- "PEK" -- "CDG" -- "EZE" -- "USH"  arrived
 
total distance: 22740.9 km

generate the path animation? (yes or no):yes

Enter the name of the output file:Filename

——————————

Then the gif file will be generated under the "build" folder. Please ignore the warning that similiar to:

"WARNING: Call to cs225::PNG::getPixel(1645,4294966922) tries to access y=4294966922, which is outside of the image (image height: 961).
       : Truncating y to 960"

And the image version can be found at "output-source.png" in the "build" folder.
