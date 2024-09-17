// Project 4
// CS 2413 Data Structures
// Spring 2023

#include <iostream>
#include <vector> // for array of transactions and array of blockChains
#include <list>   // for blockchain


using namespace std;

class transaction
{
    int tID;          // transaction id
    int fromID;       // source ID
    int fromValue;    // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int toID;         // target ID
    int toValue;      // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int tAmount;      // how much is being transfered
    string timeStamp; // time of the transaction read from the input file

public:
 

// default constructor
transaction() {
    tID = 0;
    fromID = 0;
    toID = 0;
    tAmount = 0;
    timeStamp = "";
    fromValue = 100;
    toValue = 100;
}
transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp)
{
    tID = temptID;
    fromID = tempfromID;
    toID = temptoID;
    tAmount = temptAmount;
    timeStamp = temptimeStamp;
    fromValue = 100;
    toValue = 100;
}

void displayTransaction(){ // cout each transaction
    cout << tID << " " << fromID << " " << fromValue << " " << toID << " " << toValue << " " << tAmount << " " << timeStamp << endl;
}

// all setters and getters
void setTID(int id) {
    tID = id;
}
void setFromID(int id) {
    fromID = id;
}
void setToID(int id) {
    toID = id;
}
void setTAmount(int amount) {
    tAmount = amount;
}
void setTimeStamp(string time) {
    timeStamp = time;
}
int getTID() {
    return tID;
}

int getFromID() {
    return fromID;
}
int getToID() {
    return toID;
}
int getTAmount() {
    return tAmount;
}
string getTimeStamp() {
    return timeStamp;
}

void setFromValue(int fromv) {
    fromValue = fromv;
}
void setToValue(int tov) {
    toValue = tov;
}
int getFromValue() {
    return fromValue;
}
int getToValue() {
    return toValue;
}
};
class block
{
    int blockNumber;                   // block number of the current block
    int currentNumTransactions;        // how many transactions are currently in the block
    int maxNumTransactions;            // how many maximum transactions can be in the block
    vector<transaction> bTransactions; // vector of transaction objects
    int nodeNumber;

public:

// default constructor
block() {
    blockNumber = 0;
    currentNumTransactions = 0;
    maxNumTransactions = 0;
    nodeNumber = 0;
} 

// non default constructor
block(int bNumber, int maxTransactions, int nodeNum) {
    blockNumber = bNumber;
    maxNumTransactions = maxTransactions;
    currentNumTransactions = 0;
    nodeNumber = nodeNum;
}

// P4: search for an ID in the bTransaction vector
int serach(int tID) {
    // iterator to check id if match toid or fromid from back to front
    for (vector<transaction>::reverse_iterator it = bTransactions.rbegin(); it != bTransactions.rend(); ++it) {
        if ((*it).getToID() == tID) { // if tId is a toID, return value + toAmount
            return (*it).getToValue() + (*it).getTAmount();
        }
        if ((*it).getFromID() == tID) { // if tID is a fromID, return value - toAmount
            return (*it).getFromValue() - (*it).getTAmount();
        }
    }

    return -1;
}

void display() {
    cout << "Block Number: " << blockNumber << " -- Number of Transaction: " << currentNumTransactions << endl;
    for (int i = 0; i < currentNumTransactions; i++) {
        bTransactions[i].displayTransaction(); // for loop - print out every element in transaction vector 
    }
}

bool isFull() {
    if (currentNumTransactions < maxNumTransactions) { //  currentNumTransactions less than maxNumTransactions, then is not full
        return false;
    }
    return true; // currentNumTransactions greater than maxNumTransactions
}

void insert(transaction t) { // insert transaction
    if (!isFull()) { // first check if not full
        currentNumTransactions++; // increment currentNumTransactions
        bTransactions.push_back(t); // add transation to vector
        cout << "Inserting transaction to block #" << blockNumber <<" in node "<< nodeNumber << endl; // print out message 
    }
}
};

class blockChain
{
    int currentNumBlocks; // maintain the size of the list/block chain list
    list<block> bChain;   // blockchain as a linked list
    int maxTransactions; // max transaction in the block 
    int nodeNumber; // node number 
public:
   
// default constructor
blockChain() {
    int currentNumBlocks = 0;
    maxTransactions = 0; // set max as 0; 
    nodeNumber = 0;
}

// non default constructor
blockChain(int tPerB, int nodeNum) {
    currentNumBlocks = 0;   // set current to 0
    maxTransactions = tPerB;
    nodeNumber = nodeNum;
}

void insert(transaction t) {
    // if bChain is empty or the front node of bChain is full, insert a new node in the front of bChain
    if (bChain.size()==0 || bChain.front().isFull()) {
        block* b = new block(++currentNumBlocks, maxTransactions, nodeNumber);
        bChain.push_front(*b); // add to bchain
    }
    // insert transaction t in the first node
    block* b = &bChain.front();
    b->insert(t);
}

int search(int tID){
    // for loop to search tID in every node in the bChain
    for (list<block>::iterator it = bChain.begin(); it != bChain.end(); ++it) {
        int value = (*it).serach(tID); 
        if (value != -1) { // value != -1 means find the tID, the value is the current amount of tID 
            return value;
        }
    }
    // Unable to find tID, return initial value of 100
    return 100;
}

void display() {
    cout << "Current number of blocks: " << currentNumBlocks << endl;
    for (list<block>::reverse_iterator iterator = bChain.rbegin(); iterator != bChain.rend(); ++iterator)
    {
        iterator->display();  // use iterator to print out linked list
    }
}

int getNodeNum() {
    return nodeNumber;
}
};


class blockNetwork
{
    int numNodes;                // maintain the number of nodes in the network
    vector<blockChain> allNodes; // vector of all the blockChains in the network
    vector<int> u;               // edge list u node
    vector<int> v;               // edge list v node

public:
 blockNetwork() {
    numNodes = 0;
}

blockNetwork(int numberOfNodes) {
    numNodes = numberOfNodes;
}

void initNodes(int tPerB) {
    // for loop to init node in vector allNodes
    for (int i = 0; i < numNodes; i++) {
        blockChain* bc = new blockChain(tPerB, i);
        allNodes.push_back(*bc);
    }
}

void insert(int nodeNumber, transaction t) {
    allNodes[nodeNumber].insert(t); // insert transaction into node nodeNumber
}


void setUV(int s, int t) { // set two edge list u v
    u.push_back(s); 
    v.push_back(t);
}

void display() {
    // for loop to display every node in vector allNodes
    for (vector<blockChain>::iterator it = allNodes.begin(); it != allNodes.end(); ++it) {
        cout << "~~~ Node " << (*it).getNodeNum() << ":" << endl;
        (*it).display();
    }
}
blockChain* getBlockChain(int i) {
    return &allNodes[i]; // return the node
}
};

int main()
{
    int numNodesInNetwork; // number of nodes in the network

    cin >> numNodesInNetwork;
    cout << "Number of nodes: " << numNodesInNetwork << endl;

    int numTransactionsPerBlock; // max transactions per block

    cin >> numTransactionsPerBlock;
    cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;

    int totalNumTransactions; // total transactions to be read from the input file

    cin >> totalNumTransactions;
    cout << "Total number of transactions: " << totalNumTransactions << endl;

    // object of block network
    blockNetwork *n1 = new blockNetwork(numNodesInNetwork);
    n1->initNodes(numTransactionsPerBlock);

    // TODO: input the transaction information and insert to n1
    int numEdge, nodeNum, tID, fromID, toID, tAmount;  
    string timeStamp; 

    // read numEdge and u v
    cin >> numEdge;
    for (int i = 0; i < numEdge; i++) {
        int u, v;
        cin >> u >> v;
        n1->setUV(u, v);
    }

    // for loop read all transaction until reach totalNumTransactions
    for (int i = 0; i < totalNumTransactions; i++) { 
        cin >> nodeNum >> tID >> fromID >> toID >> tAmount >> timeStamp; // user input 
        transaction t(tID, fromID, toID, tAmount, timeStamp); // creater a new transacation
        // get the blockChain corresponding to nodeNum
        blockChain* b1 = n1->getBlockChain(nodeNum);
        // get fromValue
        int fromValue = b1->search(fromID); 
        t.setFromValue(fromValue);
        // get toValue
        int toValue = b1->search(toID);
        t.setToValue(toValue);
        n1->insert(nodeNum,t);
    }
    n1->display(); // make sure you write display methods for each class 

    return 0;
}