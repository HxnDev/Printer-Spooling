# Printer-Spooling

## Description

Printers typically can print only a single document at a time and require seconds or minutes to do so. If
more than one application requires printer’s access, it might result in delay and slow down the
application for as long as the printer is busy in serving other application. ‘ **Printer spooling** ’ has overcome
this delay, as the documents formatted for printing are stored into an area on a disk and retrieved and
printed by a printer at its own rate. With spooling, multiple processes can write documents to a print
queue without waiting. As soon as a process has written its document to the spool device, the process
can perform other tasks, while a separate printing process operates the printer.

In this activity, you are required to implement printer spooler for a working environment which is
equipped with **3 printers** using concepts of Linked Lists and Queues.


**PrinterSpooler** depicts a **printer** with a **printer_id** , **current_load percentage (** value will be calculated at
each insertion of the document from max capacity and current_load. The formula is as follows;

current_load = current_load + (

( no.of page / max_capacity ) *

)

**), maximum capacity & documentQueue**. Document Queue can have multiple documents and each
document will have **doc_id, no.of pages.** There will be an ordered linked list of **users** as well with
**user_id, priority and DocumentQueue (** Queue might contain more than one document **).** The **document
Queue** in user list will have documents in the first come first serve order whereas; the document Queue
of printers will be filled by facilitating the documents coming from the high priority users.

### Insertion:

```
 Every time when a high priority user sends a document to print; the spooler identifies the
suitable printer between the first 2 printers (Suitable printer will be the one having the
current_load less than 50% and space to accommodate the new document i.e. no. of pages in
the document must not be greater than the available limit of the printer.). if both of the first
two printers are not suitable for printing the document then the document will be added into
the Document Queue of the third printer.
```
### Deletion:

```
 If all the documents in a user ordered linked list gets printed and the user’s DocumentQueue is
empty then User node gets deleted.
 Once the printer has completed the print of a certain document; the node of the document will
be deleted from both User document queue and spooler document queue after writing the
status in the out.txt file.
```

![alt text](https://github.com/HxnDev/Printer-Spooling/blob/main/f1.png?raw=true)

Following is the format of user.txt file;

User_ID Priority TotalDocuments [Doc_ID TotalPages]List

Following is the format of printer.txt file;

Printer_ID MaxCapacity

The format of out.txt should be as follows;

User_ID Doc_ID Printer_ID
