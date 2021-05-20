#pragma once

#include "nodes.h"
#include <sstream>

//User List
class UList {
private:
	UNode* head;
	UNode* tail;
	UNode* current;
	int size;

public:
	UList()
	{
		head = NULL;
		tail = NULL;
		current = NULL;
		size = 0;
	}

	bool isEmpty()
	{
		if (!size)
			return true;

		return false;
	}

	void removeFirst()				// Remove the first value from the list
	{
		UNode* temp = new UNode;
		temp = head;
		head = head->next;
		delete temp;
		size--;
		current = head;

	}

	void insert(User user, Queue q)			// Inserting the values in the list
	{
		UNode* temp = new UNode;
		temp->usr = user;
		temp->documents.copyQueue(q);
		temp->next = NULL;

		if (head == NULL)
		{
			head = temp;
			tail = temp;
			temp->next = NULL;
			current = head;

		}

		else
		{
			tail->next = temp;
			tail = temp;
			current = tail;
		}

		size++;

	}

	void sort() {					// Sorting the list on basis of priority
		if (isEmpty())
			return;

		UNode* current;
		UNode* current2;
		UNode temp;

		for (current = head; current != NULL; current = current->next)
		{
			for (current2 = head; current2 != NULL; current2 = current2->next)
			{
				if (current->usr.getPriority() > current2->usr.getPriority())
				{

					temp.usr = current->usr;
					temp.documents.copyQueue(current->documents);

					current->usr = current2->usr;
					current->documents.copyQueue(current2->documents);

					current2->usr = temp.usr;
					current2->documents.copyQueue(temp.documents);
				}
			}
		}
	}

	Doc getNextDocument()				// Getting the next document from the queue
	{
		UNode* current = head;

		if (current != NULL)
		{
			Doc doc = current->documents.dequeue();

			if (current->documents.isEmpty())
				this->removeFirst();

			return doc;
		}
	}

	void Display()
	{
		UNode* newnode = new UNode;
		newnode = head;

		while (newnode != NULL)
		{
			cout << "ID: " << newnode->usr.getUid();
			cout << " Priority: " << newnode->usr.getPriority();
			cout << " No of Docs: " << newnode->usr.getDocs();
			cout << endl;
			newnode->documents.display();
			newnode = newnode->next;
		}
	}

	int getSize() const
	{
		return size;
	}

	~UList()
	{
		UNode* current2 = head;
		UNode* temp = current2;

		while (current2 != NULL)
		{
			current2 = current2->next;
			delete temp;
			temp = current2;
		}

		size = 0;
	}


};

//Printer List

class PList {
private:
	PNode* head;
	PNode* tail;
	PNode* current;
	int size;

public:
	PList()
	{
		head = NULL;
		tail = NULL;
		current = NULL;
		size = 0;
	}


	bool isEmpty()
	{
		if (!size)
			return true;

		return false;
	}


	void removeFirst()
	{
		PNode* temp = new PNode;
		temp = head;
		head = head->next;
		delete temp;
		size--;
		current = head;

	}


	~PList()
	{
		PNode* current2 = head;
		PNode* temp = current2;

		while (current2 != NULL)
		{
			current2 = current2->next;
			delete temp;
			temp = current2;
		}

		size = 0;
	}

	void insert(string id, int cap)				// Inserts a printer info in the class
	{
		Printer obj;
		obj.setPid(id);
		obj.setCap(cap);
		obj.setCurrCap(cap);

		PNode* s = new PNode;
		s->print = obj;
		s->next = NULL;

		if (head == NULL)
		{
			head = s;
			tail = s;
			s->next = NULL;
			current = head;

		}

		else
		{
			tail->next = s;
			tail = s;
			current = tail;
		}
		size++;
	}

	void AddDocToPrinter(Doc doc)
	{
		fstream out("out(user priority).txt", ios::out | ios::app);

		int pages = doc.getPages();

		PNode* printer1 = head;
		PNode* printer2 = printer1->next;
		PNode* printer3 = printer2->next;

		if (printer1->print.getLoad() < 50 && printer1->print.getCurrCap() >= pages)
		{
			printer1->documents.enqueue(doc);

			printer1->print.Load(pages);
			printer1->print.adjustCapacity(pages);

			out << doc.getUid() << "\t \t" << doc.getDid() << "\t \t" << printer1->print.getPid() << endl;
		}

		else if (printer2->print.getLoad() < 50 && printer2->print.getCurrCap() >= pages)
		{
			printer2->documents.enqueue(doc);

			printer2->print.Load(pages);
			printer2->print.adjustCapacity(pages);

			out << doc.getUid() << "\t \t" << doc.getDid() << "\t \t" << printer2->print.getPid() << endl;
		}

		else
		{
			printer3->documents.enqueue(doc);

			out << doc.getUid() << "\t \t" << doc.getDid() << "\t \t" << printer3->print.getPid() << endl;
		}

		out.close();
	}

	void writeAllSortedByPrinter()
	{
		fstream out("out(sortedbyprinter).txt", ios::out);
		string uid, did, pid;
		Doc d;

		PNode* current = head;

		while (current != NULL)
		{
			while (!current->documents.isEmpty())
			{
				d = current->documents.dequeue();
				uid = d.getUid();
				did = d.getDid();
				pid = current->print.getPid();
				
				//cout << did << "\t of user \t" << uid << "\t printed by \t" << pid << endl;
				out << did << "\t \t" << uid << "\t \t" << pid << endl;

			}

			current = current->next;
		}
		cout << "Please see the files to check the output .." << endl;
		out.close();
	}

	void writeAllSortedByDocument()
	{
		fstream out("out(sortedbydoc).txt", ios::out);
		string uid, did, pid;
		Doc d;

		ids* idArr = new ids[100];
		int size = 0;

		PNode* current = head;

		while (current != NULL)
		{
			while (!current->documents.isEmpty())
			{
				d = current->documents.dequeue();

				uid = d.getUid();
				did = d.getDid();
				pid = current->print.getPid();

				idArr[size].uid = uid;
				idArr[size].did = did;
				idArr[size].pid = pid;

				++size;
			}

			current = current->next;
		}


		// sorting according to doc id

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (convertIDToInt(idArr[i].did) < convertIDToInt(idArr[j].did))
				{
					ids temp;

					temp = idArr[i];
					idArr[i] = idArr[j];
					idArr[j] = temp;
				}
			}
		}


		// output 

		for (int i = 0; i < size; i++)
		{
			//cout << idArr[i].uid << "\t having doc \t" << idArr[i].did << "\t printed by \t" << idArr[i].pid << endl;
			out << idArr[i].uid << "\t \t" << idArr[i].did << "\t \t" << idArr[i].pid << endl;
		}

		out.close();
	}

	void writeAllSortedByUser()
	{
		fstream out("out(sortedbyuser).txt", ios::out);
		string uid, did, pid;
		Doc d;

		ids* idArr = new ids[100];
		int size = 0;

		PNode* current = head;

		while (current != NULL)
		{
			while (!current->documents.isEmpty())
			{
				d = current->documents.dequeue();

				uid = d.getUid();
				did = d.getDid();
				pid = current->print.getPid();

				idArr[size].uid = uid;
				idArr[size].did = did;
				idArr[size].pid = pid;

				++size;
			}

			current = current->next;
		}


		// sorting according to user id

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				if (convertIDToInt(idArr[i].uid) < convertIDToInt(idArr[j].uid))
				{
					ids temp;

					temp = idArr[i];
					idArr[i] = idArr[j];
					idArr[j] = temp;
				}
			}
		}


		// output 

		for (int i = 0; i < size; i++)
		{
			//cout << idArr[i].uid << "\t having doc \t" << idArr[i].did << "\t printer by \t" << idArr[i].pid << endl;
			out << idArr[i].uid << "\t \t" << idArr[i].did << "\t \t" << idArr[i].pid << endl;
		}

		out.close();
	}

	void Display()
	{
		PNode* newnode = new PNode;
		newnode = head;

		while (newnode != NULL)
		{
			cout << "ID: " << newnode->print.getPid();
			cout << " Capacity: " << newnode->print.getCap() << endl;
			cout << endl;
			newnode->documents.display();
			newnode = newnode->next;
		}
	}

	int convertIDToInt(string id)				// Converting id from string to int
	{
		for (int i = 0; i < id.size(); i++) // removing first character from the string
			id[i] = id[i + 1];

		int toReturn;
		stringstream ss(id);
		ss >> toReturn;
		return toReturn;
	}
};