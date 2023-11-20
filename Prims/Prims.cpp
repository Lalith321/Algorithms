// Prims.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string.h>
#include <vector>

//Creates a graph and adjacency matrix
class Graph {
public:
    int** adjMatrix; //Obtains heap memory
    int countVertices;

public:
    //Creates matrix with 0 as its values
    Graph(int countVertices) {
        this->countVertices = countVertices;
        adjMatrix = new int* [countVertices];
        for (int i = 0; i < countVertices; i++) {
            adjMatrix[i] = new int[countVertices];
            for (int j = 0; j < countVertices; j++) {
                adjMatrix[i][j] = 0;
            }
        }
    }
    //Assigns weight
    void addEdge(int pointA, int pointB, int weight) {
        adjMatrix[pointA][pointB] = weight;
        adjMatrix[pointB][pointA] = weight;
    }

    void print() {
        for (int i = 0; i < countVertices; i++) {
            for (int j = 0; j < countVertices; j++) {
                std::cout << adjMatrix[i][j];
            }
            std::cout << "" << std::endl;
        }
    }

    int** getAdjMatrix() {
        return adjMatrix;
    }

};

void updateMST(int node, std::vector<int>& mstVector) {
    mstVector[node] = node;
}

void updateParentArray(int node, int nextNode, std::vector<int>& parentVector) {
    parentVector[nextNode] = node;
    //std::cout << parentVector[0];
}

/*Important*/
//Updates the distance array by finding the shortest distance
void updateDistanceArray(int node, int source, std::vector<int>& mstVector, std::vector<int>& disttVector, std::vector<int>& parentVector, int** adjMatrix, int countVertices) {
    /*if (node == source) {
        disttVector[node] = 0;
        parentVector[node] = node;
    }*/

    //Loops from first node to last node and assigns least value
    for (int nextNode = 0; nextNode < countVertices; nextNode++) {
        if (adjMatrix[node][nextNode] != 0 && !(std::count(mstVector.begin(), mstVector.end(), nextNode))) { //Checks if the value in adjacency matrix is not zero and node is not in mstVector to prevent looping and contacting previous nodes.
            if (disttVector[nextNode] > adjMatrix[node][nextNode]) {
                disttVector[nextNode] = adjMatrix[node][nextNode];
                updateParentArray(node, nextNode, parentVector);
            }
        }
    }
}

//Prints the parent array
void printParentArray(std::vector<int> parentVector, int countVertices) {
    for (int i = 0; i < countVertices; i++) {
        std::cout << parentVector[i];
    }
}

//Checking if all the nodes are visited or not by verifying the boolean value in visitedArray. Returns boolean
bool checkStatus(std::vector<bool> &visitedVector, int countVertices) {
    bool flag = true;
    for (int i = 0; i < countVertices; i++) {
        if (visitedVector[i] == false) {
            return true;
        }
        /*else {
            flag = false;
        }
        return false;*/
    }
    return false;
}

//Find the index of minimum value
int getIndexMinimumValue(int countVertices, std::vector<int> &disttVector, std::vector<int>& mstVector, int node) {
    int minValue = INT_MAX;
    for (int index = 0; index < countVertices; index++) {
        if ((disttVector[index] < minValue) && !(std::count(mstVector.begin(), mstVector.end(), index))) {
            minValue = disttVector[index];
            node = index;
        }
    }
    return node;
}

//Prims Shortest Path start point
void getPrimsMST(int source, int countVertices, int** adjMatrix) {
    int node = source;
    //int minValue = INT_MAX;
    std::vector<int> parentVector(countVertices);
    std::vector<int> disttVector(countVertices);
    std::vector<int> mstVector(countVertices);
    std::vector<bool> visitedVector(countVertices);

    //Initialize vectors
    for (int i = 0; i < countVertices; i++) {
        parentVector[i] = -1;
        mstVector[i] = -2;
        disttVector[i] = std::numeric_limits<int>::max();
        visitedVector[i] = false;
    }

    //Initialize source
    disttVector[source] = 0;
    parentVector[source] = source;

    //Keep running the loop until all the vertices are visited (Can be optimized to exclude the last vertex)
    while (checkStatus(visitedVector, countVertices)) {
        node = getIndexMinimumValue(countVertices, disttVector, mstVector, node);
        updateDistanceArray(node, source, mstVector, disttVector, parentVector, adjMatrix, countVertices);
        updateMST(node, mstVector);
        visitedVector[node] = true;
    }
    

    printParentArray(parentVector, countVertices);
    return;
}


int main()
{
    int **adjMatrix;
    int source = 0;
    int countVertices;
    std::cout << "Enter number of Vertices :";
    std::cin >> countVertices;

    std::vector<int> array(countVertices);
    
    Graph g(countVertices);
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 3);
    g.addEdge(2, 3, 2);
    

    std::cout << "Hello World!\n";
    adjMatrix = g.getAdjMatrix();

    getPrimsMST(source, countVertices, adjMatrix);
    //std::cout << adjMatrix[0][0];

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
