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
    transaction();                                                                                 // default constructor
    transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp); // non default constructor - P4: default 100 for from and to values
    // all setters and getters
    void setTID(int id);
    void setFromID(int id);
    void setToID(int id);
    void setTAmount(int amount);
    void setTimeStamp(string time);
    void setFromValue(int fromv);
    void setToValue(int tov);
    int getFromValue();
    int getToValue();
    int getTID();
    int getFromID();
    int getToID();
    int getTAmount();
    string getTimeStamp();
    // other methods as needed
    void displayTransaction();
};

// default constructor
transaction::transaction() {
    tID = 0;
    fromID = 0;
    toID = 0;
    tAmount = 0;
    timeStamp = "";
    fromValue = 100;
    toValue = 100;
}

transaction::transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string temptimeStamp)
{
    tID = temptID;
    fromID = tempfromID;
    toID = temptoID;
    tAmount = temptAmount;
    timeStamp = temptimeStamp;
    fromValue = 100;
    toValue = 100;
}

void transaction::displayTransaction()
{
    cout << tID << " " << fromID << " " << fromValue << " " << toID << " " << toValue << " " << tAmount << " " << timeStamp << endl;
}

// all setters and getters
void transaction::setTID(int id) {
    tID = id;
}
void transaction::setFromID(int id) {
    fromID = id;
}
void transaction::setToID(int id) {
    toID = id;
}
void transaction::setTAmount(int amount) {
    tAmount = amount;
}
void transaction::setTimeStamp(string time) {
    timeStamp = time;
}
int transaction::getTID() {
    return tID;
}

int transaction::getFromID() {
    return fromID;
}
int transaction::getToID() {
    return toID;
}
int transaction::getTAmount() {
    return tAmount;
}
string transaction::getTimeStamp() {
    return timeStamp;
}

void transaction::setFromValue(int fromv) {
    fromValue = fromv;
}
void transaction::setToValue(int tov) {
    toValue = tov;
}
int transaction::getFromValue() {
    return fromValue;
}
int transaction::getToValue() {
    return toValue;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class block
{
    int blockNumber;                   // block number of the current block
    int currentNumTransactions;        // how many transactions are currently in the block
    int maxNumTransactions;            // how many maximum transactions can be in the block
    vector<transaction> bTransactions; // vector of transaction objects
    int nodeNumber;

public:
    block();                                 // default constructor
    block(int bNumber, int maxTransactions, int nodeNum); // non default constructor
    // insert method to insert a new transaction
    void insert(transaction t);
    // setters and getters as needed
    // P4: search for an ID in the bTransaction vector
    int serach(int tID); // return -1 if the tID non-existent, return the value if the tID exist
    // other methods as needed
    void display();
    bool isFull();
    
};

// default constructor
block::block() {
    blockNumber = 0;
    currentNumTransactions = 0;
    maxNumTransactions = 0;
    nodeNumber = 0;
}

// non default constructor
block::block(int bNumber, int maxTransactions, int nodeNum) {
    blockNumber = bNumber;
    maxNumTransactions = maxTransactions;
    currentNumTransactions = 0;
    nodeNumber = nodeNum;
}

// P4: search for an ID in the bTransaction vector
int block::serach(int tID) {
    // Traversal from back to front
    for (auto it = bTransactions.rbegin(); it != bTransactions.rend(); ++it) {
        if ((*it).getToID() == tID) {
            return (*it).getToValue() + (*it).getTAmount();
        }
        if ((*it).getFromID() == tID) {
            return (*it).getFromValue() - (*it).getTAmount();
        }
    }

    return -1;
}

void block::display() {
    cout << "Block Number: " << blockNumber << " -- Number of Transaction: " << currentNumTransactions << endl;
    for (int i = 0; i < currentNumTransactions; i++) {
        bTransactions[i].displayTransaction(); // for loop - print out every element in transaction vector
    }
}

bool block::isFull() {
    if (currentNumTransactions < maxNumTransactions) { //  currentNumTransactions less than maxNumTransactions, then is not full
        return false;
    }
    return true; // currentNumTransactions greater than maxNumTransactions
}

void block::insert(transaction t) { // insert transaction
    if (!isFull()) { // first check if not full
        currentNumTransactions++; // increment currentNumTransactions
        bTransactions.push_back(t); // add transation to vector
        cout << "Inserting transaction to block #" << blockNumber <<" in node "<< nodeNumber << endl; // print out message
    }
}
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class blockChain
{
    int currentNumBlocks; // maintain the size of the list/block chain list
    list<block> bChain;   // blockchain as a linked list
    int maxTransactions; // max transaction in the block
    int nodeNumber;
public:
    blockChain();          // default constructor
    blockChain(int tPerB, int nodeNum); // non default constructor
    // insert method to insert new transaction into the block chain - add new block if existing block is full
    // while inserting new block into list, insert front
    void insert(transaction t);
    // setters and getters as needed
    int getNodeNum();
    // P4: search for an ID across all blocks in bChain
    int search(int tID);
    // other methods as needed
    void display();
};

// default constructor
blockChain::blockChain() {
    int currentNumBlocks = 0;
    maxTransactions = 0; // set max as 0;
    nodeNumber = 0;
}

// non default constructor
blockChain::blockChain(int tPerB, int nodeNum) {
    currentNumBlocks = 0;   // set current to 0
    maxTransactions = tPerB;
    nodeNumber = nodeNum;
}

void blockChain::insert(transaction t) {
    if (bChain.size()==0 || bChain.front().isFull()) {
        block* b = new block(++currentNumBlocks, maxTransactions, nodeNumber);
        bChain.push_front(*b); // add to bchain
    }
    block* b = &bChain.front();
    b->insert(t);
}

int blockChain::search(int tID){
    for (auto it = bChain.begin(); it != bChain.end(); ++it) {
        int value = (*it).serach(tID);
        if (value != -1) {
            return value;
        }
    }
    // Unable to find tID, return initial value of 100
    return 100;
}

void blockChain::display() {
    cout << "Current number of blocks: " << currentNumBlocks << endl;
    for (auto iterator = bChain.rbegin(); iterator != bChain.rend(); ++iterator)
    {
        iterator->display();  // use iterator to print out linked list
    }
}

int blockChain::getNodeNum() {
    return nodeNumber;
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

class blockNetwork
{
    int numNodes;                // maintain the number of nodes in the network
    vector<blockChain> allNodes; // vector of all the blockChains in the network
    vector<int> u;               // edge list u node
    vector<int> v;               // edge list v node

public:
    blockNetwork();                  // default constructor
    blockNetwork(int numberOfNodes); // non default constructor
    // insert method to insert new transaction into the block chain in a specific node - there will be a block chain existent in each node (allNodes vector)
    void insert(int nodeNumber, transaction t);
    // setters and getters as needed
    void setUV(int s, int t);
    blockChain* getBlockChain(int ind); // get blockChain which nodeNumber equal to ind
    // other methods as needed
    void initNodes(int tPerB);
    void display();
};

blockNetwork::blockNetwork() {
    numNodes = 0;
}

blockNetwork::blockNetwork(int numberOfNodes) {
    numNodes = numberOfNodes;
}

void blockNetwork::initNodes(int tPerB) {
    for (int i = 0; i < numNodes; i++) {
        blockChain* bc = new blockChain(tPerB, i);
        allNodes.push_back(*bc);
    }
}

void blockNetwork::insert(int nodeNumber, transaction t) {
    allNodes[nodeNumber].insert(t);
}


void blockNetwork::setUV(int s, int t) {
    u.push_back(s);
    v.push_back(t);
}

void blockNetwork::display() {
    for (auto it = allNodes.begin(); it != allNodes.end(); ++it) {
        cout << "~~~ Node " << (*it).getNodeNum() << ":" << endl;
        (*it).display();
    }
}

blockChain* blockNetwork::getBlockChain(int ind) {
    return &allNodes[ind];
}

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
    int numEdge;
    int nodeNum;
    int tID;          // transaction id
    int fromID;       // source ID
    int toID;         // target ID
    int tAmount;      // how much is being transfered
    string timeStamp; // time of the transaction read from the input file

    cin >> numEdge;
    for (int i = 0; i < numEdge; i++) {
        int u, v;
        cin >> u >> v;
        n1->setUV(u, v);
    }

    for (int i = 0; i < totalNumTransactions; i++) {
        cin >> nodeNum >> tID >> fromID >> toID >> tAmount >> timeStamp;
        transaction t(tID, fromID, toID, tAmount, timeStamp);
        blockChain* blc = n1->getBlockChain(nodeNum);
        // get fromValue
        int fromValue = blc->search(fromID);
        t.setFromValue(fromValue);
        // get toValue
        int toValue = blc->search(toID);
        t.setToValue(toValue);
        n1->insert(nodeNum,t);
    }

    n1->display(); // make sure you write display methods for each class

    return 0;
}
