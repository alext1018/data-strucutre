// Project 5
// CS 2413 Data Structures
// Spring 2023

// Code generated for input 1 would be:
// if(expression1)
// {
// 	statement1;
// }
// else
// {
// 	statement2;
// }

#include <iostream>
#include <string> // for the fields in the class
#include <vector> // for the flowchart structures
#include <stack>  // for conversion
#include <sstream>
#include <set>

using namespace std;

// class to store node information
class Node
{
private:
    int nodeNumber;    // to store the node number
    string type;       // can either be START, END, IF, BLOCK
    string textWithin; // can be expression or statement - for START and END this will be empty string
public:
    // TODO: construtors, getters, setters and other methods as needed
    Node()
    {
        nodeNumber = -1;
        type = "START";
        textWithin = "";
    }
    Node(int num, string t, string text)
    {
        nodeNumber = num;
        type = t;
        textWithin = text;
    }

    int getNodeNumber() 
    {
        return nodeNumber;
    }

    void setNodeNumber(int num)
    {
        nodeNumber = num;
    }

    string getType() 
    {
        return type;
    }

    void setType(string t)
    {
        type = t;
    }

    string getTextWithin() 
    {
        return textWithin;
    }

    void setTextWithin(string text)
    {
        textWithin = text;
    }
};




// recursive helper function
void convertFlowChartRecursive(vector<Node> allNodes, vector<vector<int> > adjList, int currNode, bool isIf) {
    if (allNodes[currNode].getType() == "START") {
        cout << "start" << endl;
        convertFlowChartRecursive(allNodes, adjList, adjList[currNode][0], false); // Traverse the next node recursively
    }
    else if (allNodes[currNode].getType() == "BLOCK") {
        cout << allNodes[currNode].getTextWithin() << endl; // Output the text within the block
        if (!isIf) {
            convertFlowChartRecursive(allNodes, adjList, adjList[currNode][0], false);
        }
    }
    else if (allNodes[currNode].getType() == "IF") {
        cout << "if (" << allNodes[currNode].getTextWithin() << ")" << endl; // Output the if condition
        cout << "{" << endl; // Output "{" to indicate the start of the if statement block
        convertFlowChartRecursive(allNodes, adjList, adjList[currNode][0], true); // Traverse the true branch recursively
        cout << "\n}" << endl;
        cout << "else" << endl;
        cout << "{" << endl;
        convertFlowChartRecursive(allNodes, adjList, adjList[currNode][1], true); // Traverse the false branch recursively
        cout << "\n}" << endl;
        if (!isIf) {
            convertFlowChartRecursive(allNodes, adjList, adjList[adjList[currNode][1]][0], false);
        }
    }
    else {
        cout << "end" << endl; // End 
    }
}

// function to convert the given flowchart to generate code
void convertFlowChart(vector<Node> allNodes, vector<vector<int> > adjList)
{
    // recursive helper function
    convertFlowChartRecursive(allNodes, adjList, 0, false);

}


int main()
{
    int numNodesInFlowChart; // number of nodes in the flow chart

    cin >> numNodesInFlowChart;
    cout << "Number of nodes: " << numNodesInFlowChart << endl;

    // Node objects array to store all the information
    vector<Node> allNodes(numNodesInFlowChart);

    // TODO: read in the information about the nodes and store it in allNodes
    for (int i = 0; i < numNodesInFlowChart; i++) {
        int nodeNumber;
        string type;
        string textWithin;
        cin >> nodeNumber >> type;
        allNodes[i].setNodeNumber(nodeNumber);
        allNodes[i].setType(type);
        if (type == "START" || type == "END") {
            allNodes[i].setTextWithin("");
            cout << nodeNumber << ": " << type << " node " << endl;
        }
        else {
            cin >> textWithin;
            allNodes[i].setTextWithin(textWithin);
            cout << nodeNumber << ": " << type << " node - " << allNodes[i].getTextWithin() << endl;
        }

    }

    // adjacency list to store the flow chart
    vector<vector<int> > adjList(numNodesInFlowChart);

    // TODO: read in the adjaceny list
    string line;
    // Read input, with newline as the delimiter for each line
    while (getline(cin, line)) {
        istringstream ss(line);
        int from;
        // the first number is start
        ss >> from;
        int to;
        // Read the remaining numbers and add them to the adjacency list of the node on that line.
        while (ss >> to) {
            adjList[from].push_back(to);
        }
    }

    cout << "AdjList:" << endl;
    // output
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << ": ";
        for (int v : adjList[i]) {
            cout << v << " ";
        }
        cout << endl;
    }

    // TODO: call the convertFlowChart function with the allNodes and adjList parameters

    convertFlowChart(allNodes, adjList);
    

    return 0;
}
