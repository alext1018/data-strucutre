#include <iostream>
#include <vector> // for array of transactions and array of blockChains
#include <list> // for blockchain
using namespace std;
class transaction
{
    int tID; // transaction id
    int fromID; // source ID
    int fromValue; // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int toID; // target ID
    int toValue; // P4: how much funds does the source ID person have? If first time, then initialize with 100 coins
    int tAmount; // how much is being transfered
    string timeStamp; // time of the transaction read from the input file
public:
transaction();
// default constructor
transaction(int temptID, int tempfromID, int temptoID, int temptAmount, string
            temptimeStamp);// non default constructor - P4: default 100 for from and to values
// all setters and getters
// other methods as needed
void display();
};
transaction::transaction(int temptID, int tempfromID, int temptoID, int
temptAmount, string temptimeStamp)
{
tID = temptID;
fromID = tempfromID;
toID = temptoID;
tAmount = temptAmount;
timeStamp = temptimeStamp;
fromValue = 100;
toValue = 100;
}
void transaction::display()
{
cout << tID << " " << fromID << " " << fromValue << " " << toID << " " <<
toValue << " " << tAmount << " " << timeStamp << endl;
}



class block {
    int blockNumber; // block number of the current block
    int currentNumTransactions; // how many transactions are currently in the block
    int maxNumTransactions; // how many maximum transactions can be in the block
    vector<transaction> bTransactions; // vector of transaction objects
public:
    block() {
        blockNumber = 0;
        currentNumTransactions = 0;
        maxNumTransactions = 0;
    } // default constructor
    block(int bNumber, int maxTransactions) {
        blockNumber = bNumber;
        maxNumTransactions = maxTransactions;
        currentNumTransactions = 0;
    } // non default constructor
    // search method for searching through array of transactions

    // insert method to insert a new transaction
    // void insertTransaction(transaction t) {
    //     if (currentNumTransactions < maxNumTransactions) { // if current less than max, insert the transaction
    //         bTransactions.push_back(t);
    //         currentNumTransactions = currentNumTransactions + 1; // increase current transaction
    //     }
    // }
    bool isFull(){
			if(currentNumTransactions < maxNumTransactions){ //  currentNumTransactions less than maxNumTransactions, then is not full
				return false;
			}
			return true; // currentNumTransactions greater than maxNumTransactions
		}
     void insert(transaction t){ // insert transaction
			if(!isFull()){ // first check if not full
            currentNumTransactions++; // increment currentNumTransactions
				bTransactions.push_back(t); // add transation to vector
				cout << "Inserting transaction to block #" << blockNumber  << endl; // print out message
		}
     }
    // setters and getters as needed
    void setBlockNumber(int bNumber) {
        blockNumber = bNumber;
    }
    void setCurrentNumTransactions(int numTransactions) {
        currentNumTransactions = numTransactions;
    }
    void setMaxNumTransactions(int maxTransactions) {
        maxNumTransactions = maxTransactions;
    }
    void setBTransactions(vector<transaction> transactions) {
        bTransactions = transactions;
    }
    int getBlockNumber() {
        return blockNumber;
    }
    int getCurrentNumTransactions() {
        return currentNumTransactions;
    }
    int getMaxNumTransactions() {
        return maxNumTransactions;
    }
    vector<transaction> getBTransactions() {
        return bTransactions;
    }
    void printBlock() {
       cout <<  "Block Number: " << blockNumber  << " -- Number of Transaction: "  << currentNumTransactions << endl;
        for (int i = 0; i < currentNumTransactions; i++) {
            bTransactions[i].display(); // for loop - print out every element in transaction vector
        }
    }
};
class blockChain
{
    int currentNumBlocks; // maintain the size of the list/block chain list
    list<block> bChain; // blockchain as a linked list
    int max; // max transaction in the block
public:
    blockChain() {
    int currentNumBlocks = 0;
    max = 0; // set max as 0;

    } // default constructor
    blockChain(int tPerB) {
    currentNumBlocks = 0;   // set current to 0
    max  = tPerB;
    add(); // create a new block object add to linkedlist
  }
    // non default constructor
    // insert method to insert new transaction into the block chain - add new block if existing block is full
   		void insertTransaction(transaction t){
			 block* b = &bChain.back();  //  a pointer to the last block in the blockchain.
			if(b->isFull()){  // check if last block is full
				add(); // call add() function, add new block
				b = &bChain.back();
			}
			b->insert(t); // insert transaction to block
        }
		void add(){
            currentNumBlocks = currentNumBlocks + 1; // increments currentNumBlock
			block* b = new block(currentNumBlocks, max); // create a new block
			bChain.push_back(*b); // add to bchain
			cout << "Adding block #" << currentNumBlocks << endl; //print out the message

		}
    // while inserting new block into list, insert front
    void insertFront(transaction t){
        bChain.front().insert(t);
    }
    void setCurrentNumBlocks(int number) {
        currentNumBlocks = number;
    }
    int getCurrentNumBlocks() {
        return currentNumBlocks;
    }
    void printChain() {
        cout << "Current number of blocks: " << currentNumBlocks << endl;
        list<block>::iterator iterator;
        for (iterator = bChain.begin(); iterator != bChain.end(); ++iterator)
        {
            iterator->printBlock();  // use iterator to print out linked list
        }
    }

};
int main()
{
    int numTransactionsPerBlock; // max transactions per block
    cin >> numTransactionsPerBlock;
    cout << "Number of transactions per block: " << numTransactionsPerBlock << endl;
    int totalNumTransactions; // total transactions to be read from the input file
    cin >> totalNumTransactions;
    cout << "Total number of transactions: " << totalNumTransactions << endl;
    // object of block chain
    blockChain* b1 = new blockChain(numTransactionsPerBlock);
    // insert transactions into the blockchain

    int currentNumBlocks; // maintain the size of the list/block chain list
   int tid, fromid, toid, tamout;
    string timestamp;

while (cin >> tid >> fromid >> toid >> tamout >> timestamp) {  // while loop to read every input
    transaction t(tid, fromid, toid, tamout, timestamp); // transaction with input value
    b1->insertTransaction(t); // insert to b1
}
b1->printChain(); // call printChain(), cout the transactio

    return 0;
}
