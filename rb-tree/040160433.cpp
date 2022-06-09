
/* Name Surname:  Serife Damla Konur
 * 
 * Student ID: 	  040160433
 * 
 * Analysis of Algorithm I - Homework III
 * 
 * 11/01/2022
*/
#include<iostream>
#include<fstream>
#include<string>
#include<cstdlib>
#include<cstdio>
#include<vector>

using namespace std;

class VideoGames{
	public:
	// Attributes of the each video game object
		string nameOfTheGame;
		string platform; 
		string yearOfRelease; 
		string nameOfThePublisher;     
		string NA_sales; 
		string EU_sales;
        string Other_sales;
	
		//Default Constructor
		VideoGames(){
			nameOfTheGame = " ";
			platform = " "; 			            
			yearOfRelease = " ";
			nameOfThePublisher = " "; 
			NA_sales = " ";
			EU_sales = " ";
            Other_sales = " ";
		}
		//Parametrized Constructor
		VideoGames(const string& _name, const string& _platform, const string& _releaseYear, const string& _pubName, const string& _naSale, const string& _euSale, const string& _otherSale){
			nameOfTheGame = _name; 
			platform = _platform; 			            
			yearOfRelease = _releaseYear;
			nameOfThePublisher = _pubName; 
			NA_sales = _naSale;
			EU_sales = _euSale;
            Other_sales = _otherSale;
		}
		//Getters
        string getPubName() const{
			return nameOfThePublisher;
		}
		string getName() const{
			return nameOfTheGame;
		}
		double getNASale() const{
			return stod(NA_sales);
		}
		double getEUSale() const{
			return stod(EU_sales);
		}
		double getOtherSale() const{
			return stod(Other_sales);
		}
		int getReleaseYear() const{
			return stoi(yearOfRelease);
		} 
		//Destructor
		~VideoGames(){}			
};

struct node{		
    // attributes of the each Red Black Tree node
	string pubName;         // key
	double naSale;
	double euSale;		
	double otherSale;
	string color;
	
	node*parent;    // parent node
	node*left;		// left child
	node*right;		// right child
	
};
typedef node*Node;  // Node pointer

class RedBlackTree{  // Red black tree class
	private:
		Node root;   // Node attribute is root of the tree
	public:
        RedBlackTree(){ root = NULL; }  			// default constructor
		Node getRoot(){ return root; }  			// getter
		
		~RedBlackTree(){}							//destructor
        // function for checking the tree, whether the given publisher is inserted before
        Node searchPublisher(VideoGames game){ 		// takes a game as an argument
			string key;                         	// to hold the name of publishers in the tree
            Node search = root;                 	// starts from root
				                    
			while(search != NULL){ 					//until the node is NULL
				key = search->pubName;              // pubName of the current node is assigned to key
				if(key == game.getPubName()){	    // if the pubName of the node is equal to the game that is searched	
					return search;			        // returns the existing node in order to update
				}
                else{                                          	// since the key is pubName we can search the tree with compare the pubNames
					if(search->pubName < game.getPubName()){  	// if game's pubname is bigger than the current node's pubname alphabetically
						search = search->right;  				// search goes to the right child
					}else{
						search = search->left;					// else search goes to the left child	
					}
				}
			}
			return NULL; //if there is no match, returns NULL
		}
        // function for inserting a node to the tree
        void RBTinsert(VideoGames game){    		//insert the video game into the tree 
			Node toInsert = new node;				// new node is created 
			Node toTraverse = root;					// toTraverse is used to determine the position of the node to be inserted 
			Node parentOftoInsert = NULL;			// parentOftoInsert is the parent of toInsert node, it determines if the toInsert is left or right child
			Node toSearch = NULL;					// to update the sales, if any publisher publishes games for different platforms 
			toInsert->right = NULL;					// as the leaves are NULL, right child of inserted node is NULL
			toInsert->left = NULL;					// also the left child is NULL
			toSearch = searchPublisher(game); 	    // determines if the video game is already in the tree
            // Case : 1 The video game is already exists in the tree
			if(toSearch != NULL){					// then if it is not null
				toSearch->naSale = toSearch->naSale + game.getNASale();                 // game's NA_sales
				toSearch->euSale = toSearch->euSale + game.getEUSale();	                // game's EU_sales
				toSearch->otherSale = toSearch->otherSale + game.getOtherSale();	    // game's Other_sales
				return;		  // existing game is not inserted again, just updated
			}	
            // Attributes of the given game are inserted as the attributes of the node
			toInsert->pubName = game.getPubName();      // given game's publisher name
			toInsert->naSale = game.getNASale();	    // given game's NA_sales
			toInsert->euSale = game.getEUSale();		// given game's EU_sales
			toInsert->otherSale = game.getOtherSale();  // given game's Other_sales 
			toInsert->color = "RED";                    // every inserted game is firstly assigned as RED color
			// Case : 2 The tree is empty
			if(root == NULL){		                    // if root is empty
				root = toInsert;	                    // the inserted node is root	
				toInsert->parent = NULL;                // since tree is empty parent is NULL
			}
            // Case : 3 If the tree is not empty
            else{
				// starts from root and continues until traverse is NULL 
				while(toTraverse != NULL){                          			// to insert the toInsert node at right position 
					parentOftoInsert = toTraverse;	                			// holds the last position of traverse
                    //if the inserting value is smaller than the current node
					if(toTraverse->pubName > toInsert->pubName){				// as the key of nodes is their publisher name   
						toTraverse = toTraverse->left;              			// traverse to the left child
					}else{
						toTraverse = toTraverse->right;	            			// else traverse to the right child
					}
				}
				// determine the parent of inserted node
				toInsert->parent = parentOftoInsert;							// the parentOftoInsert holds toTraverse's last positon
				if(parentOftoInsert->pubName > toInsert->pubName){  			// if the key of parentOftoInsert node is bigger than the toInsert's key
					parentOftoInsert->left = toInsert;   						// toInsert becomes the left child of the parent
				}else{
					parentOftoInsert->right = toInsert;  						// else it becomes the right child
				}	
			}
			maintainRBT(toInsert);	// after the insertion the tree must maintain the RBT properties
		}
        // function for finding the maximum NAsale in the tree by searching in pre-order
        double maxNAsales(Node r){
            double maxNAsale;                  									// holds the max naSale values of nodes
            double leftNAsale;                  								// holds the left child's naSale
            double rightNAsale;                									// holds the right child's naSale
			if(r != NULL){              										// if tree is not empty
				maxNAsale = r->naSale;        									// starting from root
				leftNAsale = maxNAsales(r->left);  								// then traversing to the left 
				rightNAsale = maxNAsales(r->right); 							// and to the right recursively 
				if(leftNAsale > maxNAsale){  									// if left child's naSales is bigger than the parent 
					maxNAsale = leftNAsale;   									// max naSales is in the left child node
				}
				if(rightNAsale > maxNAsale){									// if right child's naSales is bigger than the parent
					maxNAsale = rightNAsale;									// max naSales is in the right child node
				}
				return maxNAsale;              								   // returns maximum na sale
			}else{
				return 0;                      								   // if tree is empty return 0
			}			
		}
        // function for finding the max EUsale in the tree by searching in pre-order traversal
        double maxEUsales(Node r){
            double maxEUsale;                  								    // holds the max euSale values of nodes
            double leftEUsale;                  							    // holds the left child's euSale
            double rightEUsale;                								    // holds the right child's euSale
			if(r != NULL){               										// if tree is not empty
				maxEUsale = r->euSale;        									// starting from root
				leftEUsale = maxEUsales(r->left);  								// then traversing to the left 
				rightEUsale = maxEUsales(r->right); 							// and to the right recursively 
				if(leftEUsale > maxEUsale){  									// if left child's euSale is bigger than the parent 
					maxEUsale = leftEUsale;   									// max euSale is in the left child node
				}
				if(rightEUsale > maxEUsale){									// if right child's naSales is bigger than the parent
					maxEUsale = rightEUsale;									// max euSale is in the right child node
				}
				return maxEUsale;               								// returns maximum euSale
			}else{
				return 0;                       								// if tree is empty return 0
			}			
		}
        // function for finding the max Othersale in the tree by searching in pre-order traversal
        double maxOthsales(Node r){
            double maxOthsale;                   							 	// holds the max otherSale values of nodes
            double leftOthsale;                  								// holds the left child's otherSale
            double rightOthsale;                								// holds the right child's otherSale
			if(r != NULL){               										// if tree is not empty
				maxOthsale = r->otherSale;        								// starting from root
				leftOthsale = maxOthsales(r->left);  							// then traversing to the left 
				rightOthsale = maxOthsales(r->right); 							// and to the right recursively 
				if(leftOthsale > maxOthsale){  									// if left child's otherSale is bigger than the parent 
					maxOthsale = leftOthsale;   								// max otherSale is in the left child node
				}
				if(rightOthsale > maxOthsale){									// if right child's naSales is bigger than the parent
					maxOthsale = rightOthsale;									// max otherSale is in the right child node
				}
				return maxOthsale;               								// returns maximum otherSale
			}else{
				return 0;                       								// if tree is empty
			}			
		}
        // Publisher which has maximum NA Sale 
		void MaxNAPublisher(Node r, double mxNAsale){							// root and maximum na sale are the arguments 	
			if(r != NULL){	                            						// if tree is not empty
				if(r->naSale == mxNAsale){                     					// if the current node has the maximum na sale in the tree
					cout<< r->pubName << " - ";                					// prints the publisher name 
					return;
				}
				MaxNAPublisher(r->left, mxNAsale);	        					// else, recursively the tree is traversed in pre-order
				MaxNAPublisher(r->right, mxNAsale);	    						// then traversed to the right
			}	
		}
        // Publisher which has maximum EU Sale 
		void MaxEUPublisher(Node r, double mxEUsale){							// root and maximum eusale are the arguments 	
			if(r != NULL){	                            						// if tree is not empty
				if(r->euSale == mxEUsale){                     					// if the current node has the maximum eusale in the tree
					cout<< r->pubName << " - ";                					// prints the publisher name 
					return;
				}
				MaxEUPublisher(r->left, mxEUsale);	        					// else, recursively the tree is traversed in pre-order
				MaxEUPublisher(r->right, mxEUsale);	    						// then traversed to the right
			}	
		}
        // Publisher which has maximum Other Sale 
		void MaxOthPublisher(Node r, double mxOthsale){							// root and maximum other sale are the arguments 	
			if(r != NULL){	                            						// if tree is not empty
				if(r->otherSale == mxOthsale){                     				// if the current node has the maximum othSale in the tree
					cout<< r->pubName << " - ";                					// prints the publisher name 
					return;
				}
				MaxOthPublisher(r->left, mxOthsale);	        				// else, recursively the tree is traversed in pre-order
				MaxOthPublisher(r->right, mxOthsale);	    					// then traversed to the right
			}	
		}
        // function for rotating the given node to right
        void rotateRight(Node r){
			Node toRotate = r->left;		    								// left child of node r is stored in toRotate node
			r->left = toRotate->right;		    								// r's left subtree is the right subtree of the toRotate 
			toRotate->parent = r->parent;	    								// toRotate's parent is the parent of the r
			if(toRotate->right != NULL){	    								// if the toRotate's right child is not NULL
				toRotate->right->parent = r;									// parent of toRotate's right child is assigned to r
			}	
			if(r->parent == NULL){	            								// if the r's parent is NULL
				root=toRotate;		            								// then the root becomes toRotate node
			}
            else{ 
				if(r == r->parent->left){										// if r is left child
					r->parent->left = toRotate; 								// left child becomes toRotate
				}else{
					r->parent->right = toRotate;  								// else right child becomes toRotate
				}
			}	
			toRotate->right = r;                								// finally toRotate is the right child of its left child at first
			r->parent = toRotate;	            								// and the parent of the r is toRotate
		}
        // function for rotating the given node to left
        void rotateLeft(Node r){
			Node toRotate = r->right;		    								// right child of node r is stored in toRotate node
			r->right = toRotate->left;		    								// r's right subtree is the left subtree of the toRotate 
			toRotate->parent = r->parent;	    								// toRotate's parent is the parent of the r
			if(toRotate->left != NULL){	        								// if the toRotate's left child is not NULL
				toRotate->left->parent = r;	    								// parent of toRotate's left child is assigned to r
			}	
			if(r->parent == NULL){	            								// if the r's parent is NULL
				root=toRotate;		            								// then the root becomes toRotate node
			}
            else{ 
				if(r == r->parent->left){										// if r is left child
					r->parent->left = toRotate; 								// left child becomes toRotate
				}else{
					r->parent->right = toRotate;  								// else right child becomes toRotate
				}
			}	
			toRotate->left = r;                 								// finally toRotate is the left child of its left child at first
			r->parent = toRotate;	            								// and the parent of the r is toRotate
		}
        // function for fixing the tree for maintaining the RBT properties
        void maintainRBT(Node r){

            Node uncle;		    												// sibling of the r's parent
			Node gParent;	   												    // parent of the parent of the r
            // if there is only one node in the tree
			if(root == r){  
				r->color = "BLACK";  												// the root must be black
				return;
			}
			// if r is not root and the parent of the r is RED 
            // loop continues since the child is RED
			while((r != root) && (r->parent->color =="RED")){  
				gParent = r->parent->parent;		
				if(gParent->left == r->parent){     							// if the left child of gParent is the parent of r(given node)
					uncle = gParent->right;		    							// then uncle becomes the right child 
                    // Recoloring
					if((uncle != NULL) && (uncle->color == "RED")){  			// if uncle is not NULL and it's color RED 
						r->parent->color = "BLACK";		    					// since RED nodes must have BLACK parents
						gParent->color = "RED";									// grandpa is assigned as RED
						uncle->color = "BLACK";									// since the node is RED its children must be BLACK
						r = gParent;											// then r becomes the gParent 
					}
                    // if there is no uncle or  it's color BLACK 
                    else{
                        // Rotating the parent opposite side
						if(r->parent->right == r){  							// if the r is right child of its parent
							r = r->parent;		    							// r becomes its parent 
							rotateLeft(r);		    							// and r is left rotated
						}
                        // Rotate the gParent opposite side
						r->parent->color = "BLACK";								// after left rotation parent's color becomes BLACK
						gParent->color = "RED";									// and the gParent's color becomes RED 
                        // as the r is the left child of the gParent's left child	
						rotateRight(gParent);		    						// then gParent is right rotated
					}
				}
                //if the right child of the gParent is the parent of the r
                else{		
					uncle = gParent->left;		    							// uncle becomes left child 
                    // Recoloring
					if((uncle != NULL) && (uncle->color == "RED")){ 			// if uncle is not NULL and it's color RED 
						r->parent->color = "BLACK";								// RED nodes must have BLACK parents
						gParent->color = "RED";									// gParent becomes RED
						uncle->color = "BLACK";									// since the node is RED its children must be BLACK
						r = gParent;											// then r becomes the gParent 
					}
                    // if there is no uncle or  it's color BLACK 
                    else{
                        // Rotating the parent opposite side	  
						if(r->parent->left == r){								// if r is left child of its parent
							r = r->parent;			    						// r becomes its parent
							rotateRight(r);			    						// and r is left rotated
						}
                        // Rotate the gParent opposite side
						r->parent->color = "BLACK";								// after right rotation parent's color becomes BLACK
						gParent->color = "RED";									// and the gParent's color becomes RED 
                        // as the r is the right child of the gParent's right child
						rotateLeft(gParent);		    						// then gParent is left rotated
					}
				}			
			}
			root->color = "BLACK";	                    						// finally the root is always black
		}
        // function for printing the entire red black tree
        void printRBT(Node r,int depth){  										// depth argument is for indentation
			if(r != NULL){      
                // print indentation dashes
				for(int i=0; i < depth; i++){  									// depth is the depth of the given node 
					cout << "-";           
				}
                // prints color and publisher name of the node
				cout << "("<<r->color<<")" << " " << r->pubName << endl; 
				depth++;  														// increase depth value after print
				printRBT(r->left,depth);   										// prints firstly left side of the root 
				printRBT(r->right,depth);  										// then right side to print the tree in preorder
			}
		}
        // function for printing the best sellers after the end of each decade
        // arguments are the root and the game
		void printBestSellers(Node r, VideoGames game){ 
            double maxNa = maxNAsales(r);
            double maxEu = maxEUsales(r);
            double maxOth = maxOthsales(r);
			cout << "End of the " << game.getReleaseYear() << " Year" << endl;  //prints the year
			// For north america
            cout << "Best seller in North America: ";
			MaxNAPublisher(r, maxNa);		
            cout << maxNa << " million" << endl;
            // For europe
            cout << "Best seller in Europe: ";
			MaxEUPublisher(r, maxEu);		
            cout << maxEu << " million" << endl;			
			// for other countries					
            cout << "Best seller rest of the World: ";
			MaxOthPublisher(r, maxOth);		
            cout << maxOth << " million" << endl;
		}

};


int main(int argc, char *argv[]){
	string fileName = argv[1]; 

    ifstream file;
    file.open(fileName);
    if (!file){
        cerr << "File cannot be opened!";
        exit(1);
    }
	// attribute names for the video game
    string _nameOfTheGame;
    string _platform; 
    string _yearOfRelease; 
    string _nameOfThePublisher;     
    string _NA_sales; 
    string _EU_sales;
    string _Other_sales;

    string _firstLine;                      	// line for taking headers
    getline(file, _firstLine);
    string line;
    vector<VideoGames> videoGames;				// vector of Video Game objects

    RedBlackTree rbTree;						// Red Black Tree object
    int counter = 0;							// to keep video game count
    while(file.good()){							// take lines until the end of the file 
        getline(file, _nameOfTheGame, ','); 
        getline(file, _platform, ','); 
        getline(file, _yearOfRelease, ','); 
        getline(file, _nameOfThePublisher, ','); 
        getline(file, _NA_sales, ','); 
        getline(file, _EU_sales, ','); 
        getline(file, _Other_sales, '\n'); 
		// for each line call parametrized constructor and store video game object in the vector
        videoGames.push_back(VideoGames(_nameOfTheGame, _platform, _yearOfRelease, _nameOfThePublisher, _NA_sales, _EU_sales, _Other_sales));
        counter++;								// increase the counter by one
    }
	file.close();								// close file 
    
	// loop for inserting the Video Game objects into the Red Black Tree
    for(int j = 0; j < counter-1; j++){  		
		// if the first decade ends, insert last object into the tree and print best sellers
		if((videoGames[j].getReleaseYear() == 1990) && (videoGames[j+1].getReleaseYear() == 1991)){ 
			rbTree.RBTinsert(videoGames[j]);		
			rbTree.printBestSellers(rbTree.getRoot(), videoGames[j]);  	
		}
		// if the second decade ends, insert last object into the tree and print best sellers
		else if((videoGames[j].getReleaseYear() == 2000) && (videoGames[j+1].getReleaseYear() == 2001)){ 
			rbTree.RBTinsert(videoGames[j]);		
			rbTree.printBestSellers(rbTree.getRoot(), videoGames[j]);  	
		}
		// if the third decade ends, insert last object into the tree and print best sellers
		else if((videoGames[j].getReleaseYear() == 2010) && (videoGames[j+1].getReleaseYear() == 2011)){ 
			rbTree.RBTinsert(videoGames[j]);		
			rbTree.printBestSellers(rbTree.getRoot(), videoGames[j]);  	
		}
		// normally insert the objects in the tree
		else{
			rbTree.RBTinsert(videoGames[j]);		
		}
		// if the 2020 ends, insert last object into the tree and print best sellers and entire tree
		if(j == counter - 2){
			rbTree.RBTinsert(videoGames[j]);		
			rbTree.printBestSellers(rbTree.getRoot(), videoGames[j]);
			rbTree.printRBT(rbTree.getRoot(),0);
		}	
	}
	return 0;
}



