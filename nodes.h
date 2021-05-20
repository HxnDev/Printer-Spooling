#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstring>
#include <cmath>

using namespace std;

class User {

private:
	string u_id;
	int priority;
	int docs;

public:

	User()				// Constructor
	{
		u_id = '\0';
		priority = 0;
		docs = 0;
	}

	void setUid(string s)
	{
		u_id = s;
	}

	string getUid() const
	{
		return u_id;
	}

	void setPriority(int s)
	{
		priority = s;
	}

	int getPriority() const
	{
		return priority;
	}

	void setDocs(int s)
	{
		docs = s;
	}

	int getDocs() const
	{
		return docs;
	}


};

class Doc {

private:
	string d_id;
	int pages;
	string u_id;

public:
	Doc()
	{
		d_id[0] = '\0';
		pages = 0;
		u_id[0] = '\0';
	}

	void setDid(string s)
	{
		d_id = s;
	}

	void setUid(string s)
	{
		u_id = s;
	}

	string getDid() const
	{
		return d_id;
	}

	string getUid() const
	{
		return u_id;
	}

	void setPages(int s)
	{
		pages = s;
	}

	int getPages() const
	{
		return pages;
	}
};

class Printer {

private:
	string p_id;
	float load = 0;
	int capacity;
	int curr_cap;

public:
	Printer()
	{
		p_id[0] = '\0';
		load = 0;
		capacity = 0;
		curr_cap = 0;
	}

	void setPid(string s)
	{
		p_id = s;
	}

	string getPid()const
	{
		return p_id;
	}

	void setLoad(float s)
	{
		load = s;
	}

	int getLoad()
	{
		return load;
	}

	void setCap(int s)
	{
		capacity = s;
	}

	float getCap()
	{
		return capacity;
	}

	void setCurrCap(int s)
	{
		curr_cap = s;
	}

	int getCurrCap()
	{
		return curr_cap;
	}

	void Load(int pages)				// Will calculate the current load on a printer
	{
		load = load + (pages / getCap()) * 100;
		this->setLoad(load);
	}

	void adjustCapacity(int pages)			// Updating the capacity of a printer
	{
		curr_cap -= pages;
	}

};

struct DNode {
	DNode* next;
	Doc docu1;
};

class Queue {

	DNode* front;
	DNode* rear;
	int size;

public:

	Queue()
	{
		front = NULL;
		rear = NULL;
		size = 0;
	}

	void copyQueue(Queue& otherQueue)		// Copying the contents of one queue into another
	{
		Queue temp;

		while (!otherQueue.isEmpty())
		{
			Doc val = otherQueue.dequeue();
			temp.enqueue(val);
		}

		while (!temp.isEmpty())
		{
			Doc val = temp.dequeue();
			this->enqueue(val);
		}
	}

	~Queue()
	{
		DNode* current = front;

		while (front != NULL)
		{
			current = front;
			front = front->next;
			delete current;
		}
	}

	void enqueue(Doc n)
	{
		DNode* temp = new DNode;
		temp->docu1 = n;
		temp->next = NULL;

		if (front == NULL)
		{
			front = temp;
			rear = temp;
		}

		else
		{
			rear->next = temp;
			rear = temp;
		}

		size++;
	}

	Doc dequeue()
	{

		DNode* temp;
		temp = front;
		front = front->next;

		Doc val = temp->docu1;

		size--;

		return val;
	}

	bool isEmpty() const
	{

		if (!size)
			return true;

		return false;
	}

	void display() {
		DNode* temp = front;

		while (temp != NULL)
		{
			cout << temp->docu1.getDid() << " " << temp->docu1.getPages() << " ";
			temp = temp->next;
			cout << endl;
		}

		cout << "\n";
	}

	int getLength()				// Getting the length of the queue
	{
		return size;
	}

};


struct UNode
{

	UNode* next;
	User usr;

	Queue documents;
};

struct PNode
{
	PNode* next;
	Printer print;

	Queue documents;
};

struct ids
{
	string uid;
	string did;
	string pid;
};