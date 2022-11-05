## Leading Question
We will utilize OpenFlight(https://openflights.org/data.html), the open source data set of flight routes and airports, to find the most preferred routes between two airports as well as to create a general travel plan, using airport(.dat) as vertex/node and routes(.dat) as edges. We will utilize the DSF to traverse through airports, the Dijkstra algorithm to build a search tool with the user inputting their start and destination airports, as well as Floyd Warshall algorithm for generating a travel plan matrix.


## Dataset Acquisition
The data are .dat files (just plain text) we download from flight openflights.org, the routes data: https://raw.githubusercontent.com/jpatokal/openflights/master/data/routes.dat We will be using all these 67663 lines of route data, taking all of them into consideration.

## Data Format
As they are the same as .txt files, can be read directly by file steam and processed as strings. Each line of the file contains a route, described by the Airline, Airline ID, Source airport, Source airport ID, Destination airport, Destination airport ID, Codeshare, Stops, and Equipment. They are clearly separated by "," (which these data only contain letters and numbers), therefore can be very easily identified by the program. As each route occupy a line, we can also separate them by recognizing "\n".

## Data Correction
The data is very well formatted, with each line nine data separated by eight commas, and no special cases in them, we can process them by straightforward logic without worrying about edge cases. Some "Codeshare" data are left blank, but the commas are still there. We can just ignore "Codeshare" data as it's unrelated to our project.

## Data Storage
The routes will be stored in ADTs including graphs and maps (red-black tree), which both have space complexity of O(n) (where n is the number of routes). The original data file is around 2MB, so the area used would only be around a small multiples of it, which we don't expect to take 10 times of it, that is 20MB, and can be easily fit into the program memory.

## Algorithm
In this project, we will create a graph connecting airports as nodes with routes as edges, which will be a directed and weighted graph. We will use DFS to traverse through our graph, Dijkstra’s algorithm to find the shortest distance between two user-selected nodes - start point and destination as well as Floyd Warshall algorithm to generate a travel plan matrix with start point and two user-designated destinations, where it will generate a travel matrix containing two separate plans for the user that helps for comparison.
For BFS, we will use it to traverse through all airports with routes connecting them.
For the Dijkstra’s algorithm, we will use the longitude and latitude contained in the .dat file to calculate the weights of edges. (distance between two airports). It will be used to calculate the shortest paths between two user-selected airports as well as indicate the travel distances.
(The use of the Floyd Warshall Algorithm is to help user to generate plans between two destinations so that users can make selections themselves using the given information. For example, if the user wants to have a short travel from champaign to either Chicago or Springfield, then he/she can utilize the output matrix containing shortest path distances matrix travel plan to make the decision.)(Information such as airplane models will be added if applicable. For Floyd Warshall algorithm, we will let the user input three airports, including the start point, and two destinations. It will be used to generate a shortest-paths matrix among the three destinations.

## Timeline
Below are some time deadlines that we are expected to finish, but could be flexible as needed.11/12 due file read, input graph creations and functions.h file ready. 11/17 due first algorithm and sample test. 12/3 due every functions and tests cases, be ready for report and presentations. 12/7 project self-demo
