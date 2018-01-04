#include <iostream>
#include <string>

#define DISPLAY 1
#define REMOVE 0

using namespace std;

struct dataNode{
    string attribA;
    string attribB;
    string attribC;

    dataNode(string a = "", string b = "", string c = ""){
        attribA = a;
        attribB = b;
        attribC = c;
    }
};

struct hashNode{
    dataNode* dataPtr;
    hashNode* nextPtr;

    hashNode(){
        dataPtr = NULL;
        nextPtr = NULL;
    }

    hashNode(dataNode* dptr){
        dataPtr = dptr;
        nextPtr = NULL;
    }
};

class multiAccessHash{
private:
    hashNode*** attrArr;
    int SIZE;
	const char TAB = '\t';
public:
    multiAccessHash(int size){
        SIZE = size;
        attrArr = new hashNode**[3];
        attrArr[0] = new hashNode*[size];
        attrArr[1] = new hashNode*[size];
        attrArr[2] = new hashNode*[size];

        for(int i = 0; i < size; i++) {
	        // Pointers
	        attrArr[0][i] = attrArr[1][i] = attrArr[2][i] = NULL;
        }
    }

    // Green Code Ahead
    int hash(string str){
        if(str == ""){
            return 0xDEAD;
        }
        else{
            unsigned hash = 0;
            int str_length = static_cast<int>(str.length());
            for(int i = 0; i < str.length(); i++)
                hash = hash*10 + str[i];
            return hash % SIZE;
        }
    }

    void insertByAttrib(string str, int atr, dataNode* dptr){
        // Go to the hash Location
        hashNode* trav = attrArr[atr][hash(str)];

        // First Element
        if(trav == NULL){
            attrArr[atr][hash(str)] = new hashNode(dptr);
            return;
        }

        while(trav->nextPtr != NULL) {
	        if(trav->dataPtr == NULL){
		        trav->dataPtr = dptr;
		        return;
	        }
	        trav = trav->nextPtr;
        }

        trav->nextPtr = new hashNode(dptr);
        return;
    }

    void insertData(string A, string B, string C){
        dataNode* temp = new dataNode(A, B, C);
	    insertByAttrib(A, 0, temp);
        insertByAttrib(B, 1, temp);
        insertByAttrib(C, 2, temp);

        return;
    }

    void insertData(dataNode dn){
        insertData(dn.attribA, dn.attribB, dn.attribC);
        return;
    }

    void display(dataNode* dataPtr){
		if(dataPtr == NULL)
			return;
        cout << "AttrA" << TAB << "AttrB" << TAB << "AttrC" << endl;
        cout << dataPtr->attribA << TAB << dataPtr->attribB << TAB << dataPtr->attribC;
        cout << endl;

	    return;
    }

	void remove(dataNode* dPtr){
		if(dPtr == NULL)
			return;
		// Pointers to the possible locations in all the three hashes
		hashNode* travA = attrArr[0][hash(dPtr->attribA)];
		hashNode* travB = attrArr[1][hash(dPtr->attribB)];
		hashNode* travC = attrArr[2][hash(dPtr->attribC)];

		// Step1: While loops will NULLify all references to the dataNode

		// For first attrib
		while(travA != NULL){
			if(travA->dataPtr == dPtr)
				travA->dataPtr = NULL;
			travA = travA->nextPtr;
		}
		// For second attrib
		while(travB != NULL){
			if(travB->dataPtr == dPtr)
				travB->dataPtr = NULL;
			travB = travB->nextPtr;
		}
		// For third attrib
		while(travC != NULL){
			if(travC->dataPtr == dPtr)
				travC->dataPtr = NULL;
			travC = travC->nextPtr;
		}

		// Step 2: Once no references exist, delete the object from the memory
		delete dPtr;
	}

    void operateDataByAttrib(string str, int atr, int action){
        hashNode* trav = attrArr[atr][hash(str)];
	    void (multiAccessHash:: *function)(dataNode*);

	    if(action == 1)
		    function = &multiAccessHash::display;
	    else
		    function = &multiAccessHash::remove;

        if(trav == NULL)
            return;

        while(trav != NULL && atr == 0){
	        if(trav->dataPtr == NULL){
		        trav = trav->nextPtr;
		        continue;
	        }
            if(trav->dataPtr->attribA == str) {
	            (this->*function)(trav->dataPtr);
            }
            trav = trav->nextPtr;
        }

	    while(trav != NULL && atr == 1){
		    if(trav->dataPtr == NULL){
			    trav = trav->nextPtr;
			    continue;
		    }
		    if(trav->dataPtr->attribB == str) {
			    (this->*function)(trav->dataPtr);
		    }
		    trav = trav->nextPtr;
	    }

	    while(trav != NULL && atr == 2){
		    if(trav->dataPtr == NULL){
			    trav = trav->nextPtr;
			    continue;
		    }
		    if(trav->dataPtr->attribC == str) {
			    (this->*function)(trav->dataPtr);
			    trav = trav->nextPtr;
		    }
	    }
    }
};

int main() {
	multiAccessHash mHash(20);
	dataNode dn("Asad", "126978", "MGen");

	mHash.insertData(dn);
	mHash.insertData("HashMatt", "179865", "Gen");
	mHash.insertData("Carbon", "3456", "Maj");
	mHash.insertData("Lewis", "3456", "DCol");

	mHash.operateDataByAttrib("126978", 1, DISPLAY);
	mHash.operateDataByAttrib("126978", 1, REMOVE);
	mHash.operateDataByAttrib("126979", 1, DISPLAY);
	cin.get();
	mHash.operateDataByAttrib("HashMatt", 0, DISPLAY);
	mHash.operateDataByAttrib("Maj", 2, DISPLAY);
	mHash.operateDataByAttrib("3456", 1, DISPLAY);
}
