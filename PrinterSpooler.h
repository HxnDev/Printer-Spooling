#pragma once

#include "List.h"
#include <fstream>

class PrinterSpooler {

	PList printlist;
	UList userlist;

public:

	void ReadPrinter()		//Reads printer.txt
	{
		string s, pname;
		int cmp;
		fstream in("printer.txt", ios::in);

		while (!in.eof())
		{
			in >> s;
			pname = s;

			in >> cmp;

			printlist.insert(pname, cmp);
		}
	}

	void ReadUsers()		// Reads user.txt
	{
		fstream in("user.txt", ios::in);

		string userid;
		int priority;
		int noOfDocuments;

		while (!in.eof())
		{
			in >> userid;
			in >> priority;
			in >> noOfDocuments;

			Queue q;
			string docid;
			int pages;

			for (int i = 0; i < noOfDocuments; i++)
			{
				in >> docid;
				in >> pages;

				Doc document;
				document.setDid(docid);
				document.setPages(pages);
				document.setUid(userid);

				q.enqueue(document);
			}

			User tempUser;
			tempUser.setUid(userid);
			tempUser.setPriority(priority);
			tempUser.setDocs(noOfDocuments);

			userlist.insert(tempUser, q);
		}

		in.close();
	}

	void sortUsers()
	{
		userlist.sort();
	}

	void AddingDocuments()
	{
		while (userlist.getSize() != 0)
		{
			Doc docu = userlist.getNextDocument();
			printlist.AddDocToPrinter(docu);
		}
	}

	void writeSortedByPrinter()
	{
		printlist.writeAllSortedByPrinter();
	}

	void writeSortedByDoc()
	{
		printlist.writeAllSortedByDocument();
	}

	void writeSortedByUser() {
		printlist.writeAllSortedByUser();
	}

	void displayPrinters()
	{
		printlist.Display();
	}

	void displayUsers()
	{
		userlist.Display();
	}

	void runAll()			// Runs all functions
	{
		this->ReadPrinter();
		this->ReadUsers();
		this->sortUsers();
		this->AddingDocuments();

		//	this->writeSortedByPrinter();
		//	this->writeSortedByDoc();
		//	this->writeSortedByUser();
	}
};