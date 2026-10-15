#include <string>      // std::string
#include <utility>     // std::pair
#include <functional>  // std::greater
#include <iostream>
#include <algorithm>
#include <limits>
#include <vector>
#include <queue>
#include <iomanip>

using namespace std;


// The Edge structure represents a connection between two conservation areas.
// Each edge stores the destination conservation area (neighbour) and the
// distance required to travel between the two locations.
struct Edge{
    int neighbour; // connected vertex
    int weight;    // distance in kilometres
};


class Graph{
private:

    // The number of vertices represents the total number of conservation
    // areas contained within the graph
    int numVertices;

    // Stores the names of all conservation areas.
    // The position of each name in the vector corresponds to its vertex index
    // used throughout the graph algorithms.
    vector<string> conservationAreaNames; // stores names of conservation areas

    // adjacency list:
    // each vertex has a list of edges connected to it
    vector<vector<Edge>> adjacentList;

    // adjacency matrix:
    // stores weights between vertices
    vector<vector<int>> adjacentMatrix;


public:

    // Creates a graph object containing the specified number of vertices.
    //
    // The constructor prepares the data structures required to store the
    // conservation network by creating the adjacency list and adjacency matrix.
    Graph(int vertices){

        numVertices = vertices;

        // Resize the adjacency list so that every vertex has its own list
        // of connected edges.
        adjacentList.resize(numVertices);

         // Create a square adjacency matrix containing numVertices rows and
        // columns, initially filled with zeros.
        adjacentMatrix.resize(numVertices, vector<int>(numVertices, 0));
    }

    //Add names of conservation areas to the parks vector that stores names:
    void addConservationArea(string name){

        conservationAreaNames.push_back(name); //push an item to the end of the park vector
    }

    // Creates a connection between two conservation areas.
    //
    // Each connection is represented as an edge containing:
    // - The neighbouring conservation area.
    // - The distance between the two locations.
    //
    // Since the conservation network represents two-way travel routes,
    // an edge is added in both directions. This allows each conservation
    // area to recognise the other as a neighbouring location.
    //
    // The connection distance is also stored in the adjacency matrix so
    // the network can be displayed as a distance table.
    void addEdge(int startingVertex, int destinationVertex, int connectionDistance){

        Edge edge1; //Initialise an instance of the Edge struct
        //Assign vertex and distance values to the Edge instance:
        edge1.neighbour = destinationVertex;
        edge1.weight = connectionDistance;

        adjacentList[startingVertex].push_back(edge1); // Add the Edge instance pointing to v to the adjacency list of vertex u, thereby associating the 2 vertices asneighbours, and storing distance betweeen them

        Edge edge2;

        edge2.neighbour = startingVertex;
        edge2.weight = connectionDistance;

        adjacentList[destinationVertex].push_back(edge2); // creating the reverse connection between the two vertices so they are neighbours in both directions

        //Adding weight/distance between the 2 vertices to the adjacent matrices
        adjacentMatrix[startingVertex][destinationVertex] = connectionDistance;
        adjacentMatrix[destinationVertex][startingVertex] = connectionDistance;
    }

    // Displays the conservation network using the adjacency list.
    //
    // Each conservation area is displayed with all directly connected
    // areas and the distance between them.
    void displayConservationNetwork(){

        cout << endl;
        cout << "Conservation Areas Network:" << endl;
        cout << endl;

        for (int i = 0; i < numVertices; i++) //loop through every vertex in the graph
        {
            cout << conservationAreaNames[i] << ":" << endl;

            for (Edge edge : adjacentList[i]) //For every edge instance stored in the adjacency list of vertex i:
            {
                cout << " --> " << conservationAreaNames[edge.neighbour] << " - " << edge.weight << "km" << endl; // display the neighbouring vertex and the edge weight/ distance between them
            }
            cout << endl;
        }
    }


    // Displays the conservation network as a distance matrix.
    //
    // Rows and columns represent conservation areas, while each cell
    // contains the distance between two locations.
    // A value of 0 indicates that no direct connection exists.
    void displayDistanceMatrix(){

        cout << endl;
        cout << "Adjacency Matrix (km)" << endl;
        cout << setw(15) << ""; //space formatting

        //Columns:
        //Iterate through each park and display the first three letters of its name as the matrix column headings
        for (int i = 0; i < numVertices; i++)
        {
            cout << setw(12)
                 << conservationAreaNames[i].substr(0,2);
        }
        cout << endl;


        for (int i = 0; i < numVertices; i++) //Outer loop that moves through each row
        {
            cout << setw(15)
                 << conservationAreaNames[i].substr(0,2); //prints the vertex label i per row

            for (int j = 0; j < numVertices; j++) //Inner loop that moves through columns to display distance values between locations
            {
                cout << setw(12)
                     << adjacentMatrix[i][j]; //Prints distance between the current location i and the destination location j
            }
            cout << endl;
        }
    }


    // Performs Breadth-First Search (BFS) starting from a selected
    // conservation area.
    //
    // BFS explores the graph level by level by visiting all directly
    // connected areas before moving to areas further away.
    // A queue is used to process locations in the order they are discovered,
    // while the visited vector prevents the same location from being explored
    // multiple times.
    void breadthFirstSearch(int startVertex) //start bfs from specified vertex index
    {
        vector<bool> visited(numVertices, false); //bool type vector that traks which vertices have been explored. by default marked as false meaning not yet visited

        queue<int> bfsQueue; //queue that will store vertex indexes to be processed during bfs

        visited[startVertex] = true; //marks the visited status of the index as true in the visited vector


        bfsQueue.push(startVertex); //add the starting vertex index to the queue to be processed first

        cout << endl;
        cout << "Reachable Conservation Areas from " << conservationAreaNames[startVertex] << ":" << endl;
        cout << endl;

        //When the while loop is reached for the very first time, the queue contains only one item, ie, the starting vertex.
        //bfs traverse whilst there are vertices waiting in the queue
        while (!bfsQueue.empty()){

            int currentVertex  = bfsQueue.front(); //store the vertex index at the front of the queue in an int variable
            bfsQueue.pop(); //remove the vertex from the queue

            cout << conservationAreaNames[currentVertex ]; //display the conservation area currently being explored using the index of int value matching current in the parks vector to access location names

            //Explores current vertex's/location's connections and decides which vertices to add to the queue:
            for (Edge edge : adjacentList[currentVertex ]){ //iterate through every edge connected to the current vertex

                //if statement that executes if the neighbouring vertex's visit status is fales
                if (visited[edge.neighbour] == false){
                    visited[edge.neighbour] = true; //if false, marks the naighbour as visited

                    bfsQueue.push(edge.neighbour); //pushes the neighbour into the queue to explore it's connections
                }
            }

            if (bfsQueue.empty() == false){
                cout << " --> ";
            }
        }
        cout << endl;
    }

    // Dijkstra's algorithm finds the shortest path between two conservation areas
    // in a weighted graph.
    //
    // The algorithm keeps track of:
    // - The shortest known distance from the starting area to every other area.
    // - The previous vertex used to reach each area, allowing the final route to be reconstructed.
    // - A priority queue that processes the area with the smallest current distance first.
    //
    // The algorithm repeatedly checks neighbouring areas and updates their distances
    // whenever a shorter route is discovered.
    void dijkstra(int start, int destination)
    {
        //vector that stores the shortest known distance from the starting vertex to every other vertex initially unknown and thus set to infinity
        vector<int> distance(numVertices, numeric_limits<int>::max());

        //// Stores the preceding vertex for each vertex in the shortest route, initially set to -1 until a route is discovered
        vector<int> previous(numVertices, -1); //Create a vector with V spaces, and put -1 in every space which means no previous vertex has been assigned yet.


        //priority queue that removes items based on priority
        priority_queue
        <pair<int,int>, //distance, vertex index
        vector<pair<int,int>>, //store distance and vertex index pairs inside a vector
        greater<pair<int,int>>> //makes the queue a min priority queue to process smallest distances first
        priorityQueue;


        distance[start] = 0; //Set the starting vertex's distance to zero

        priorityQueue.push({0,start});//add the starting vertex and its distance to the priority queue queue(distance, vertex index)


        //at the very first time the while loop is reached, there is only one item in the priority queue
        while (priorityQueue.empty() == false){ //continue looping whilst there are still vertices in the priority queue

            int currentVertex = priorityQueue.top().second; //store the vertex index of the closest vertex currently in the queue, accesses second part of the pair using .second

            int currentDistance = priorityQueue.top().first; //stores the distance of the closest vertex  currently in the queue, accesses the first part of the pair using .first


            priorityQueue.pop(); //remove item at the front of the queue

            //Always false in the first iteration, therefore code continues to the for loop
            //if true, ignore this vertex if the priority queue contains an older, longer route than the current shortest known distance
            //ensures that updates only occur when shorter paths are found
            if (currentDistance > distance[currentVertex]){
                continue;
            }

            //Loop through each edge connected to the current vertex using the agjacent list that stores the connections of each vertex
            for (Edge edge : adjacentList[currentVertex]){

                int neighbour = edge.neighbour; //// Store the index of the vertex connected to the current vertex through this edge

                int connectionDistance  = edge.weight; //store distance between the current vertex and its neighbouring vertex



                if (distance[currentVertex] + connectionDistance  < distance[neighbour]){ //Check if travelling through the current vertex provides a shorter route to the neighbour

                    distance[neighbour] = distance[currentVertex] + connectionDistance; //update the neighbour's shortest known distance with the newly calculated shorter route

                    previous[neighbour] = currentVertex; //stores where the route comes from

                    priorityQueue.push({distance[neighbour], neighbour}); //ddd the updated shortest distance and vertex back into the priority queue to be considered in following loop iterations
                }
            }
        }

        //check if the destination still has an infinite distance, meaning no route was discovered
        if (distance[destination] == numeric_limits<int>::max()){

            cout << endl;
            cout << "No route could be found" << endl;

            return;
        }


        vector<int> shortestRoute; //creates a vector that will store the vertex indexes used to compile the shortest route

        // Start at the destination vertex and trace backwards through the previous vector until reaching the starting vertex
        for (int currentVertex = destination; currentVertex != -1; currentVertex = previous[currentVertex]){

            shortestRoute.push_back(currentVertex); // Add the current vertex index to the path vector to record the shortest route
        }

            reverse(shortestRoute.begin(), shortestRoute.end()); // Reverse the order of the stored vertex indexes so the shortest route is displayed from start to destination

        cout << endl;
        cout << "Shortest Route:" << endl;
        cout << endl;


        for (int i = 0; i < shortestRoute.size(); i++){ //loop through the shortest path vector from the first vertex to the last

            cout << conservationAreaNames[shortestRoute[i]];//display park name of the given vertex of iteration i

            if (i != shortestRoute.size() - 1){
                cout << " --> ";
            }
        }


    // Display the total shortest distance from the starting vertex to the destination
        cout << endl;
        cout << "Total Distance: " << distance[destination] << " km" << endl;
    }




    void listAreas(){
        cout << endl;
        cout << "Conservation areas:" << endl;
        cout << endl;

        //Loop through each index in the conservation area string vector to output corresponding conservation area names
        for (int i = 0; i < numVertices; i++)
        {
            cout << i << ". " << conservationAreaNames[i] << endl;
        }
    }

};



int main()
{

    // Create a Graph object containing 6 vertices/conservation areas:
    Graph conservationAreaGraph(6);

    // Add conservation area names to the graph's park vector, assigning each area a vertex index:
    conservationAreaGraph.addConservationArea("Kruger");
    conservationAreaGraph.addConservationArea("Limpopo");
    conservationAreaGraph.addConservationArea("Hwange");
    conservationAreaGraph.addConservationArea("Chobe");
    conservationAreaGraph.addConservationArea("Etosha");
    conservationAreaGraph.addConservationArea("Kgalagadi");

    // Add routes between conservation areas with their corresponding distances.
    conservationAreaGraph.addEdge(0,1,260);
    conservationAreaGraph.addEdge(1,2,290);
    conservationAreaGraph.addEdge(2,3,720);
    conservationAreaGraph.addEdge(4,5,670);
    conservationAreaGraph.addEdge(5,2,300);
    conservationAreaGraph.addEdge(0,3,600);
    conservationAreaGraph.addEdge(2,4,60);

    int option = 0;//variable that stores the user's menu selection

    //Display the menu and facilitate selections until the exit con is met
    while (option !=5){
        cout << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "|Wildlife Conservation Connectivity in Southern Africa|" << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << "|1. Display conservation network                      |" << endl;
        cout << "|2. Display adjacency matrix                          |" << endl;
        cout << "|3. Perform BFS traversal                             |" << endl;
        cout << "|4. Find shortest path between parks                  |" << endl;
        cout << "|5. Exit                                              |" << endl;
        cout << "-------------------------------------------------------" << endl;
        cout << endl;

        //Store the user's selected menu option
        cout << "Enter option: ";
        cin >> option;
        cout << endl;

        //Display the conservation network
        if(option == 1){
            conservationAreaGraph.displayConservationNetwork();
        }

        //Display the distance matrix
        else if(option == 2){
            conservationAreaGraph.displayDistanceMatrix();
        }

        //Request a starting location and perform BFS traversal
        else if(option == 3){
            conservationAreaGraph.listAreas();
            int startArea;
            cout << endl;
            cout << "Enter starting conservation area number: ";
            cin >> startArea;
            if(startArea >= 0 && startArea < 6){
                conservationAreaGraph.breadthFirstSearch(startArea);
            }
            else{
                cout << "Invalid entry" << endl;
            }

        }

        //Request starting and destination locations and find shortest route using Dijkstra
        else if(option == 4){

            conservationAreaGraph.listAreas();
            int startArea;
            int end;

            cout << endl;
            cout << "Enter starting area number: ";
            cin >> startArea;
            cout << "Enter destination area number: ";
            cin >> end;

            if(startArea >= 0 && startArea < 6 && end >= 0 && end < 6)
                conservationAreaGraph.dijkstra(startArea,end);
            else{
                cout << "Invalid entry." << endl;
            }

        }

        //Terminate the menu loop
        else if(option == 5){
            cout << endl;
            cout << "Session ended" << endl;
        }

        else{
            cout << endl;
            cout << "Invalid entry" << endl;
        }



    }

    return 0;
}
