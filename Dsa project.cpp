#include <iostream>
using namespace std;

// Node for adjacency list
class Node 
{
public:
    int data;
    Node* next;  
    
    Node(int d) 
	{
        data = d;
        next = NULL;
    }
};

// Queue node for BFS
class QueueNode 
{
public:
    int data;
    QueueNode* next;
    
    QueueNode(int val) 
	{
        data = val;
        next = NULL;
    }
};

// Queue implementation
class Queue 
{
private:
    QueueNode* front;
    QueueNode* rear;
public:
    Queue() 
	{
        front = NULL;
        rear = NULL;
    }
    
    void enqueue(int value) 
	{
        QueueNode* newNode = new QueueNode(value);
        if (rear == NULL) 
		{
            front = rear = newNode;
            return;
        }
        rear->next = newNode;
        rear = newNode;
    }
    
    int dequeue() 
	{
        if (front == NULL) 
		{
            return -1;
        }
        QueueNode* temp = front;
        int val = temp->data;
        front = front->next;
        
        if (front == NULL) 
		{
            rear = NULL;
        }
        delete temp;
        return val;
    }
    
    bool isEmpty() 
	{
        return (front == NULL);
    }
};

// Stack node for DFS
class StackNode 
{
public:
    int data;
    StackNode* next;
    
    StackNode(int val) 
	{
        data = val;
        next = NULL;
    }
};

// Stack implementation
class Stack 
{
private:
    StackNode* top;
public:
    Stack() 
	{
        top = NULL;
    }
    
    void push(int value) 
	{
        StackNode* newNode = new StackNode(value);
        newNode->next = top;
        top = newNode;
    }
    
    int pop() 
	{
        if (top == NULL)
		{
            return -1;
        }
        StackNode* temp = top;
        int val = temp->data;
        top = top->next;
        delete temp;
        return val;
    }
    
    bool isEmpty() 
	{
        return (top == NULL);
    }
};

// Graph class
class Graph 
{
private:
    int numNodes;
    Node* adjList[6];
    char blockNames[6][50];
    
    void copyName(char* data, const char* start) 
	{
        int i = 0;
        while (start[i] != '\0' && i < 49) 
		{
            data[i] = start[i];
            i++;
        }
        data[i] = '\0';
    }
public:
    Graph(int nodes) 
	{
        numNodes = nodes;
        for (int i = 0; i < 6; i++) 
		{
            adjList[i] = NULL;
        }
        copyName(blockNames[0], "Main Gate");
        copyName(blockNames[1], "Admission Block");
        copyName(blockNames[2], "Aerospace & Engineering Block");
        copyName(blockNames[3], "Block-B");
        copyName(blockNames[4], "Block-A");
        copyName(blockNames[5], "Block-C");
    }
    
    void addConnections(int start, int data) 
	{
        Node* newNode = new Node(data);
        if (adjList[start] == NULL) 
		{
            adjList[start] = newNode;
        } 
		else 
		{
            Node* temp = adjList[start];
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNode;
        }
        newNode = new Node(start);
        if (adjList[data] == NULL) 
		{
            adjList[data] = newNode;
        } 
		else 
		{
            Node* temp = adjList[data];
            while (temp->next != NULL) temp = temp->next;
            temp->next = newNode;
        }
    }
    
    void displayGraph() 
	{
        cout<<endl;
        cout<<"Campus Navigation Map"<<endl;
        cout<<endl;
        for (int i = 0; i < numNodes; i++) 
		{
            cout<<"("<<i<<") "<<blockNames[i]<<endl;
            cout<<"Connected to: ";
            Node* temp = adjList[i];
            if (temp  ==  NULL) cout<<"No connections";
            while (temp != NULL) 
			{
                cout<<blockNames[temp->data];
                if (temp->next != NULL) cout<<", ";
                temp = temp->next;
            }
            cout<<endl<<endl;
        }
    }
    
    int getNumNodes() 
	{
        return numNodes;
    }
    
    Node* getAdjList(int index) 
	{
        return adjList[index];
    }
    
    char* getBlockName(int index) 
	{
        return blockNames[index];
    }
};

// BFS class
class BFS
{
private:
    Graph &g;
    int start, end;
    bool visited[6];
    int parent[6];
    int traversalOrder[6];
    int orderIndex;
    bool found;
public:
    BFS(Graph &graph, int s, int e) : g(graph), start(s), end(e) 
    {
        orderIndex = 0;
        found = false;
        for(int i=0;i<6;i++)
        {
            visited[i]=false;
            parent[i]=-1;
        }
    }
    
    void run() 
    {
        Queue q;
        visited[start]=true;
        q.enqueue(start);
        traversalOrder[orderIndex++] = start;
        while(!q.isEmpty()) 
        {
            int current = q.dequeue();
            if(current == end) found=true;
            Node* temp = g.getAdjList(current);
            while(temp!=NULL) 
            {
                if(!visited[temp->data]) 
                {
                    visited[temp->data]=true;
                    parent[temp->data]=current;
                    q.enqueue(temp->data);
                    traversalOrder[orderIndex++]=temp->data;
                }
                temp=temp->next;
            }
        }
    }
    
    void displayResults() 
    {
        // Display BFS Traversal
        cout<<"BFS Traversal Order:"<<endl;
        for(int i=0;i<orderIndex;i++) 
        {
            cout<<g.getBlockName(traversalOrder[i])<<" ("<<traversalOrder[i]<<")";
            if(i<orderIndex-1) cout<<" --> ";
        }
        cout<<endl<<endl;
        
        // Display Shortest Path
        if(found) 
        {
            int pathArray[10], pathLength=0;
            int node=end;
            while(node!=-1) 
            {
                pathArray[pathLength++]=node;
                node=parent[node];
            }
            cout<<"Shortest Path Found!"<<endl;
            cout<<"Number of blocks: "<<pathLength<<endl<<endl;
            cout<<"Route:"<<endl;
            for(int i=pathLength-1;i>=0;i--) 
            {
                cout<<"  "<<g.getBlockName(pathArray[i])<<" ("<<pathArray[i]<<")";
                if(i>0) cout<<endl<<"      |"<<endl<<"      v"<<endl;
            }
            cout<<endl<<endl;
        } 
        else 
        {
            cout<<"No path found!"<<endl<<endl;
        }
    }
};

// DFS class
class DFS
{
private:
    Graph &g;
    int start;
    bool visited[6];
    int traversalOrder[6];
    int orderIndex;
public:
    DFS(Graph &graph, int s) : g(graph), start(s) 
    {
        orderIndex=0;
        for(int i=0;i<6;i++) visited[i]=false;
    }
    
    void run() 
    {
        Stack s;
        s.push(start);
        while(!s.isEmpty()) 
        {
            int current=s.pop();
            if(!visited[current]) 
            {
                visited[current]=true;
                traversalOrder[orderIndex++]=current;
                int neighborCount=0;
                Node* temp=g.getAdjList(current);
                while(temp!=NULL) 
                {
                    if(!visited[temp->data]) neighborCount++;
                    temp=temp->next;
                }
                int neighbors[6], idx=0;
                temp=g.getAdjList(current);
                while(temp!=NULL) 
                {
                    if(!visited[temp->data]) neighbors[idx++]=temp->data;
                    temp=temp->next;
                }
                for(int i=0;i<neighborCount;i++) s.push(neighbors[i]);
            }
        }
    }
    
    void displayResults() 
    {
        cout<<"DFS Traversal Order:"<<endl;
        for(int i=0;i<orderIndex;i++) 
        {
            cout<<g.getBlockName(traversalOrder[i])<<" ("<<traversalOrder[i]<<")";
            if(i<orderIndex-1) cout<<" --> ";
        }
        cout<<endl<<endl;
        
        cout<<"Reachable blocks:"<<endl;
        for(int i=0;i<orderIndex;i++) 
        {
            cout<<"  "<<i+1<<". "<<g.getBlockName(traversalOrder[i])<<" ("<<traversalOrder[i]<<")"<<endl;
        }
        cout<<endl<<"Total reachable: "<<orderIndex<<endl<<endl;
    }
};

// Main function
int main() 
{
    cout<<endl;
    cout<<"CAMPUS NAVIGATION SYSTEM"<<endl;
    cout<<"Using Graph with BFS and DFS"<<endl;
    cout<<endl;
    
    Graph campus(6);
    campus.addConnections(0,1);
    campus.addConnections(0,2);
    campus.addConnections(2,3);
    campus.addConnections(3,4);
    campus.addConnections(4,5);
    
   // campus.displayGraph();
    
    int choice;
    while(true) 
	{
        cout<<endl<<"MENU"<<endl;
        cout<<"1. Find Shortest Path (BFS)"<<endl;
        cout<<"2. Show All Reachable Blocks (DFS)"<<endl;
        cout<<"3. Display Campus Map"<<endl;
        cout<<"4. Exit"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;
        
        if(choice == 1) 
		{
            int start,end;
            cout<<"Enter starting block (0-5): ";
            cin>>start;
            cout<<"Enter destination block (0-5): ";
            cin>>end;
            if(start>=0 && start<campus.getNumNodes() && end>=0 && end<campus.getNumNodes()) 
			{
                BFS bfs(campus,start,end);
                bfs.run();
                bfs.displayResults();
            } 
			else cout<<"Invalid block numbers!"<<endl;
        }
        else if(choice == 2) 
		{
            int start;
            cout<<"Enter starting block (0-5): ";
            cin>>start;
            if(start>=0 && start<campus.getNumNodes()) 
			{
                DFS dfs(campus,start);
                dfs.run();
                dfs.displayResults();
            } 
			else cout<<"Invalid block number!"<<endl;
        }
        else if(choice == 3) campus.displayGraph();
        else if(choice == 4) 
		{
            cout<<"Thank you for using Campus Navigation!"<<endl<<"Exiting..."<<endl<<endl;
            break;
        }
        else cout<<"Invalid choice!"<<endl;
    }
}

