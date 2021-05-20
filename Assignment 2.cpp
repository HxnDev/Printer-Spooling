#include <iostream>
#include "PrinterSpooler.h"

int main()
{
	PrinterSpooler obj;
	//	obj.runAll();

	obj.ReadPrinter();
	obj.ReadUsers();
	obj.sortUsers();
	obj.AddingDocuments();

		obj.writeSortedByPrinter(); //Generates Output Printer Wise
	//	obj.writeSortedByDoc();		//Generates Output Doc Wise (Ascending)
	//	obj.writeSortedByUser();	//Generates Output User Wise
}