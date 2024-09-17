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
#include <sstream> // for read input
#include <set> // 

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


// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

// function to convert the given flowchart to generate code
void convertFlowChart(vector<Node> allNodes, vector<vector<int> > adjList)
{
	// This code uses -2 to represent the end of the true branch and
    // -1 to represent the end of the false branch in an if statement.
    // When encountering -2, it indicates the end of the true branch.
    // When encountering -1, it indicates the end of the false branch.
    stack<int> nodeStack;
    nodeStack.push(0);
    set<int> visited; 

    while (!nodeStack.empty()) {
        int currNode = nodeStack.top();
        nodeStack.pop();

        if (currNode == -1) {
            // End of false branch of if statement
            // output }
            cout << "\n}" << endl;
        }
        else if (currNode == -2) {
            // End of true branch of if statement
            cout << "\n}" << endl;
            cout << "else" << endl;
            cout << "{" << endl;

        }
        else if (allNodes[currNode].getType() == "START") {
            nodeStack.push(adjList[currNode][0]); // Push the next node onto the stack
            cout << "start" << endl;
        }
        else if (allNodes[currNode].getType() == "BLOCK") {
            cout << allNodes[currNode].getTextWithin() << endl; // Output the text within the block
            if (!nodeStack.empty() && nodeStack.top() == -1) {
                cout << "\n}" << endl;
                nodeStack.pop();
                if (visited.count(adjList[currNode][0]) == 0) {
                    nodeStack.push(adjList[currNode][0]); // Push the next node onto the stack
                    visited.insert(adjList[currNode][0]);
                }
            }
            else if (!nodeStack.empty() && nodeStack.top() == -2) {
                cout << "\n}" << endl;
                cout << "else" << endl;
                cout << "{" << endl;
                nodeStack.pop();
            }
            else {
                //nodeStack.push(adjList[currNode][0]); // Push the next node onto the stack
                if (visited.count(adjList[currNode][0]) == 0) {
                    nodeStack.push(adjList[currNode][0]); // Push the next node onto the stack
                    visited.insert(adjList[currNode][0]);
                }
            }
        }
        else if (allNodes[currNode].getType() == "IF") {
            cout << "if (" << allNodes[currNode].getTextWithin() << ")" << endl;  // Output the if condition
            cout << "{" << endl; // Output "{" to indicate the start of the if statement block
            if (allNodes[adjList[currNode][1]].getType() != "IF") {
                if (visited.count(adjList[adjList[currNode][1]][0]) == 0) {
                    nodeStack.push(adjList[adjList[currNode][1]][0]);
                    visited.insert(adjList[adjList[currNode][1]][0]);
                }
            }
            nodeStack.push(-1); // Push the false branch end marker onto the stack
            nodeStack.push(adjList[currNode][1]); // Push the node corresponding to the false branch onto the stack
            nodeStack.push(-2); // Push the true branch end marker onto the stack
            nodeStack.push(adjList[currNode][0]);  // Push the node corresponding to the true branch onto the stack
        }

    }
    cout << "end" << endl;
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
            cout << nodeNumber << ": " << type << " node "<< endl;
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
