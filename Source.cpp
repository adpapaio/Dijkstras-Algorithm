//Dijkstras Algorithm with Priority Queues and Adjacency
//Author: Aristotelis Papaioannou
//Date Created: 4/1/2016
//Last Modification Date: 4/14/2016


#include <iostream>
#include <vector>	//call vector library
#include <cmath>	//call cmath library for the floor operation
#include <unordered_map>	//use the map to keep track of the binary heap
#include <time.h>	//to calculate the time

using namespace std;

struct nodes
{
	int data;		//node
	int weight;		//weight of the edge
	nodes *next;	//the next node
};

//class for the binary heap
class binHeap
{
private:

	vector<nodes *> binVec;	//vector that will hold the binary Heap
	unordered_map<int, int> track1;	//tracking map to keep track of the binary heap locations
	int MAXNUMB = 1995;	//mx numb is used in place of infinity

public:
	//prototypes for the functions 
	int min();	
	bool isEmpty();
	void binInsert(int, int);
	void decreaseKey(int, int);
	nodes* deleteMin();
	void heapify(int);
	void binDijk(vector<nodes *>&);
	//
};

//prototypes for the adjacency list functions
void adjacencyList(vector< nodes * >&);
void adjDijk(vector<nodes *>&);
void insertEdge(int, int, int, vector< nodes * >&);
//

int main()
{
	vector< nodes* > adjList;	//create the adjacency list vector
	binHeap bObj;				//to access the class
	clock_t t, t2;				//two sets of time

	adjList.resize(22);	//resize the adjacency list

	cout << "Shortest Path using Adjacency Lists: ";
	t = clock();	//start timer
	adjacencyList(adjList);	//create the adjacency list
	adjDijk(adjList);	//run dijkstra's for the adjacency list
	t = clock() - t;	//calculate the total time
	cout << "Time to run: " << (float)t / CLOCKS_PER_SEC << " Second(s)" << endl;	//convert clock ticks to seconds in float

	t2 = clock();	//start timer for bin heaps
	cout << endl << "Shortest Path using Binary Heaps: ";
	bObj.binDijk(adjList);	//do all the operations for binary heaps
	t2 = clock() - t2;	//find total time
	cout << "Time to run: " << (float)t2 / CLOCKS_PER_SEC << " Second(s)" << endl << endl;	//convert clock ticks to seconds in float

	system("pause");
	return 0;
}

//Name: adjacencyList
//Description: Send the node, weight, and next node to the insert function
//Type of Function: Void
//Input: vector of type nodes* of the adjacency vector
//Output: nothing
//Author: Aristotelis Papaioannou
//Date Created: 4/2/2016
void adjacencyList(vector<nodes *>&  adjList)
{
	//Hardcoded edges and weights
	insertEdge(20, 0, 0, adjList); //first node
	insertEdge(20, 7, 5, adjList);	//
	insertEdge(20, 3, 10, adjList);	//
	insertEdge(20, 1, 15, adjList);	//
	insertEdge(0, 10, 1, adjList);
	insertEdge(0, 7, 5, adjList);
	insertEdge(5, 5, 6, adjList);
	insertEdge(5, 7, 10, adjList);
	insertEdge(5, 7, 0, adjList);
	insertEdge(10, 7, 5, adjList);
	insertEdge(10, 1, 11, adjList);
	insertEdge(10, 1, 15, adjList);
	insertEdge(15, 1, 10, adjList);
	insertEdge(15, 4, 16, adjList);
	insertEdge(1, 10, 0, adjList);
	insertEdge(1, 1, 2, adjList);
	insertEdge(1, 3, 6, adjList);
	insertEdge(6, 3, 1, adjList);
	insertEdge(6, 10, 7, adjList);
	insertEdge(6, 0, 11, adjList);
	insertEdge(6, 5, 5, adjList);
	insertEdge(11, 0, 6, adjList);
	insertEdge(11, 6, 12, adjList);
	insertEdge(11, 8, 16, adjList);
	insertEdge(11, 1, 10, adjList);
	insertEdge(16, 8, 11, adjList);
	insertEdge(16, 10, 17, adjList);
	insertEdge(16, 4, 15, adjList);
	insertEdge(2, 1, 1, adjList);
	insertEdge(2, 7, 3, adjList);
	insertEdge(2, 0, 7, adjList);
	insertEdge(7, 0, 2, adjList);
	insertEdge(7, 1, 8, adjList);
	insertEdge(7, 6, 12, adjList);
	insertEdge(7, 10, 6, adjList);
	insertEdge(12, 6, 7, adjList);
	insertEdge(12, 10, 13, adjList);
	insertEdge(12, 0, 17, adjList);
	insertEdge(12, 6, 11, adjList);
	insertEdge(17, 0, 12, adjList);
	insertEdge(17, 0, 18, adjList);
	insertEdge(17, 10, 16, adjList);
	insertEdge(3, 7, 2, adjList);
	insertEdge(3, 5, 4, adjList);
	insertEdge(3, 4, 8, adjList);
	insertEdge(8, 4, 3, adjList);
	insertEdge(8, 8, 9, adjList);
	insertEdge(8, 1, 7, adjList);
	insertEdge(8, 3, 13, adjList);
	insertEdge(13, 3, 8, adjList);
	insertEdge(13, 10, 14, adjList);
	insertEdge(13, 3, 18, adjList);
	insertEdge(13, 10, 12, adjList);
	insertEdge(18, 3, 13, adjList);
	insertEdge(18, 10, 19, adjList);
	insertEdge(18, 0, 17, adjList);
	insertEdge(4, 5, 3, adjList);
	insertEdge(4, 1, 9, adjList);
	insertEdge(4, 1, 21, adjList);	//last node
	insertEdge(9, 1, 4, adjList);
	insertEdge(9, 8, 8, adjList);
	insertEdge(9, 1, 14, adjList);
	insertEdge(9, 4, 21, adjList);	//last node
	insertEdge(14, 1, 9, adjList);
	insertEdge(14, 10, 13, adjList);
	insertEdge(14, 4, 19, adjList);
	insertEdge(14, 4, 21, adjList);	//last node
	insertEdge(19, 4, 14, adjList);
	insertEdge(19, 10, 18, adjList);
	insertEdge(19, 3, 21, adjList); //Last node
}

//Name: insertEdge
//Description: Insert the passed variables into tthe adjacency list
//Type of Function: Void
//Input: int Index, int weight, int next node, vector<nodes*> adjacency vector
//Output: nothing
//Author: Aristotelis Papaioannou
//Date Created: 4/2/2016
void insertEdge(int index, int wei, int node, vector< nodes * >& adjList)
{
	nodes *curr = new nodes;
	nodes *temp = new nodes; //create temporary nodes

	temp->data = node;	//node/weight to be inserted into the list
	temp->weight = wei;
	temp->next = NULL;

	if (adjList[index] == NULL)	//if the indexed location is NULL then insert first
	{
		curr->data = node;
		curr->weight = wei;
		curr->next = NULL;

		adjList.at(index) = curr;	//current index = currenct nodes
	}
	else  //indexed location has a node in it, so add to the back
	{
		curr = adjList.at(index);	//set curr to the list head
			
		while (curr->next != NULL)	//find the last location
			curr = curr->next;

		curr->next = temp;	//put the temp nodes into the end of the list
	}
}

//Name: adjDijk
//Description: Use Dijkstra's Algorithm on the Adjacency List(Vector)
//Type of Function: Void
//Input: vector of type nodes* of the adjacency vector
//Output: The Shortest Path of the Adjacency List(Vector)
//Author: Aristotelis Papaioannou
//Date Created: 4/4/2016
void adjDijk(vector<nodes *>& adjList)
{
	int v, w, weight, dist, MAXN = 1995;//MAXN is in place of infinity
	int start = 20;	//starting point
	const int MAX = 22;	//max nodes -1
	nodes *temp = new nodes;
	vector<bool> inside(MAX);	//initialize the vectors to be used to max size
	vector<int> distance(MAX);
	vector<int> parent(MAX);
	vector<int> shortest;
	int dex = 21;	//used for printing
	int currNode;	//

	//set all the default values in the vectors
	for (int i = 0; i < adjList.size(); i++)
	{
		inside[i] = false;	//default value: not in tree
		distance[i] = MAXN;	//distance = "infinity"
		parent[i] = -1;		//not visited parent
	}

	distance[start] = 0;	
	v = start;

	while (inside[v] == false)//while it is false 
	{
		inside[v] = true;	//set it to inside tree
		temp = adjList[v];

		while (temp != NULL)	//while the adjacency info is not NULL
		{
			w = temp->data;
			weight = temp->weight;

			if (distance[w] > (distance[v] + weight))	//if  current distance is more than other distance
			{
				distance[w] = distance[v] + weight;	//set distance to this new distance
				parent[w] = v;	//set the parent to that vertex with the lower distance
			}

			temp = temp->next;	//change to the next temp
		}

		v = 1;
		dist = MAXN; //distance equals "infinity"

		for (int i = 0; i < adjList.size(); i++) //go through all the distances
		{
			if ((inside[i] == false) && (dist > distance[i]))	//
			{
				dist = distance[i];	//change the distance form infinity
				v = i;
			}
		}
	}

	currNode = parent[dex];	//curr node equals parent[21]

	//while loop works back to front
	while (currNode != 20)	//while 20 has not been found
	{
		shortest.push_back(dex);	//push the current index on shortest path vector
		dex = currNode;				//change the dex to the next node
		currNode = parent[dex];		//change the currNode to the next index
	}

	shortest.push_back(currNode);	//add the 20 on

	//print the vector back to front so it is in order
	for (int k = shortest.size() - 1; k >= 0; k--)
	{
		cout << shortest[k];	//print out the shortest path

		if (k != 0)	//puts an arrow where needed, prevents arrow from appearring on end
			cout << "->";
	}
	cout << endl;
}

//Name: binInsert from the binHeap Class
//Description: Insert the nodes into the Binary Heap, update the tracking
//Type of Function: Void
//Input: int weight, int nodes, unordered_map track1, Vector Binary Heap
//Output: nothing
//Author: Aristotelis Papaioannou
//Date Created: 4/6/2016
void binHeap::binInsert(int wei, int node)
{
	nodes* temp = new nodes;
	int size;

	temp->data = node;	//set the temp to the passed in data
	temp->weight = wei;

	binVec.push_back(temp);	//push the temp onto the heap

	size = binVec.size() - 1;	//find the current size of the heap

	track1[binVec[binVec.size() - 1]->data] = size;	//let the tracking vector keep track

	decreaseKey(track1[binVec[binVec.size() - 1]->data], temp->weight);	//send the correct index and the weight to decreaseKey
}

//Name: min from the binHeap Class
//Description: find the min of the binary Heap
//Type of Function: int
//Input: binary Heap(Vector)
//Output: return the int min
//Author: Aristotelis Papaioannou
//Date Created: 4/6/2016
int binHeap::min()
{
	if (!isEmpty()) //if the binary heap is not empty
		return binVec[0]->data;	//return the min value
}

//Name: isEmpty from the binHeap Class
//Description: Check to see if the Binary Heap is Empty
//Type of Function: bool
//Input: Binary Heap(Vector)
//Output: return true/false
//Author: Aristotelis Papaioannou
//Date Created: 4/6/2016
bool binHeap::isEmpty()
{
	//check to see if the binary heap is empty
	if (binVec.size() == 1)
		return true;	//return yes
	else
		return false;	//else return no
}

//Name: DecreaseKey from binHeap Class
//Description: puts the given node into its correct spot
//Type of Function: Void
//Input: binHeap Vector, int nodes(i), int distance(weight)
//Output: nothing
//Author: Aristotelis Papaioannou
//Date Created: 4/8/2016
void binHeap::decreaseKey(int i, int distance)
{
	int numb;
	nodes *temp, *temp2;

	binVec[i]->weight = distance; //set the weight to the new weight passed in

	//while the current node is not NULL
	while (binVec[i] != NULL)
	{
		if (i != 0 && binVec[floor(i/2)]->weight > distance)	//iff i is not 0 and  the parent weight is more than the new weight
		{
			numb = track1[binVec[floor(i/2)]->data];	//temp value stored in numb

			track1[binVec[floor(i/2)]->data] = track1[binVec[i]->data];	//switch the index to keep track of the heap
			track1[binVec[i]->data] = numb;								//use temp value stored in numb

			temp = binVec[floor(i / 2)];	//create temp of parent
			temp2 = binVec[i];				//create temp of current

			binVec[floor(i / 2)] = temp2;	//switch them
			binVec[i] = temp;				//

			i = floor(i/2);	//set i to the parent value
		}
		else
			return;		//if i is 0 or parent weight is less than new weight return from the function
	}
}

//Name: DeleteMin from binHeap Class
//Description: Delete the min from the binary Heap
//Type of Function: nodes*
//Input: binary Heap(Vector)
//Output: return the min value that was deleted
//Author: Aristotelis Papaioannou
//Date Created: 4/8/2016
nodes* binHeap::deleteMin()
{
	nodes *temp = binVec[0]; //temp value of min
	int temp2;

	temp2 = track1[binVec[0]->data];	//temp value

	track1[binVec[0]->data] = track1[binVec[binVec.size() - 1]->data];	//update the tracking map with the new indexes
	track1[binVec[binVec.size() - 1]->data] = temp2;					//use temp value from temp2

	track1.erase(binVec[0]->data);	//erase the min node from the tracking map

	binVec[0] = binVec[binVec.size() - 1];	//switch the front and the back
	binVec[binVec.size() - 1] = temp;		//switch the back and the front

	binVec.pop_back();		//pop the back, deleting the min
	
	heapify(0);	//heapify the binary heap, 0 is so the index points to the min

	return temp;	//return the min value that was deleted
}

//Name: heapify from binHeap Class
//Description: fix the binary heap to be valid
//Type of Function: Void
//Input: int i(min), binary Heap(Vector)
//Output: nothing
//Author: Aristotelis Papaioannou
//Date Created: 4/8/2016
void binHeap::heapify(int i)
{
	int left = 2 * i + 1;	//left child
	int right = 2 * i + 2;	//right child
	int vecSize = binVec.size() - 1, temp;	
	int dex;	//index for small value
	nodes *smallest;	//node to hold the smallest values

	//if left is smaller/equal than the size and the left childs weight is less than the current nodes weight
	if (left <= vecSize && binVec[left]->weight < binVec[i]->weight)	
	{
		smallest = binVec[left];	//set the left child to smallest node
		dex = left;					//keep track of its index number in the vector
	}
	else  //if the left is bigger or left childs weight is greater than
	{
		smallest = binVec[i];	//set smallest to current node
		dex = i;				//track the number in the vector
	}

	//if right is smaller/equal than the vector size and the right childs weight is less than the current nodes weight
	if (right <= vecSize && binVec[right]->weight < binVec[dex]->weight)
	{
		smallest = binVec[right];	//set the smallest to the right child
		dex = right;				//keep track of its number in the vector
	}
	
	//if the smallest does not equal the given node(means another one was smaller)
	if (smallest != binVec[i])
	{
		temp = track1[binVec[i]->data];	//set temp value

		track1[binVec[i]->data] = track1[smallest->data];	//update the tracking map
		track1[binVec[dex]->data] = temp;					//use temp values index
		
		binVec[dex] = binVec[i];	//switch the values
		binVec[i] = smallest;		//set the current node to the smallest node

		heapify(dex);	//fix the binary heap while passing the childs/nodes number
	}
}

//Name: binDijk from binHeap Class
//Description: use Dijkstra's Algorithm on the Binary Heap and print shortest path
//Type of Function: Void
//Input: the adjacency list
//Output: Shortest Path found
//Author: Aristotelis Papaioannou
//Date Created: 4/9/2016
void binHeap::binDijk(vector<nodes *>& adjList)
{
	int start = 20;	//starting point
	const int MAX = 22;
	nodes *temp, *temp2;
	vector<int> distance(MAX);	//initializes the vectors to their max capacities
	vector<int> parent(MAX);
	vector<int> shortest;	//will hold the shortest path
	int dex = 21;
	int currNode;

	distance[start] = 0;	//set the distance to 0

	//set the default values for all the vertexes
	for (int i = 0; i < adjList.size(); i++)
	{
		if (i != start)	//if i is not the start values(20)
			distance[i] = MAXNUMB;	//set distance to 1995(infinity)

		parent[i] = -1;	//default parent value
		binInsert(distance[i], i);	//insert it into the heap
	}

	//while the heap is not empty
	while (!isEmpty())
	{
		temp = deleteMin(); //set temp to the min that was deleted
		temp2 = adjList[temp->data];	//find the mins data on the adjacency list

		//while temp2 is not NULL
		while (temp2 != NULL)
		{
			if (distance[temp2->data] > distance[temp->data] + temp2->weight)	//if the current distance is greater than the new distance
			{
				distance[temp2->data] = distance[temp->data] + temp2->weight;	//update distance
				parent[temp2->data] = temp->data;								//update the parent
				decreaseKey(track1[temp2->data], distance[temp2->data]);		//decrease the key values
			}

			temp2 = temp2->next;	//shift to the next node in temp2
		}
	}

	currNode = parent[dex]; //set the currNode to parent[21]

	//while the currNode is not the starting point
	while (currNode != 20)
	{
		shortest.push_back(dex);	//push it onto the shortest path vector
		dex = currNode;				//update the dex to be used
		currNode = parent[dex];		//change the currNode
	}

	shortest.push_back(currNode);	//put the starting point on the Vector

	//print the shortest path Vector
	//prints the vector back to front to display correct order
	for (int k = shortest.size() - 1; k >= 0; k--)
	{
		cout << shortest[k];

		if (k != 0)	//if it is not the end add an arrow
			cout << "->";
	}
	cout << endl;	//extra space
}