/* 
 * File:   LinkedList.cpp
 * Author: Simon Powers
 * 
 * Modified by: Erik Sanne
 *
 * Last modified 02/04/2017
 *
 * Implements the LinkedList class.
 */

#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include "linked_list.h"
using namespace std;


//creates an empty list
LinkedList::LinkedList()
{
	head = tail = NULL;
}

//creates a list with an initial value to store
LinkedList::LinkedList(int value)
{
	head = new Node;
	head->data = value;
	tail = head;
}

//copy constructor (performs a deep copy)
LinkedList::LinkedList(const LinkedList& rhs)
{
	//Starting at the head of the list that is beeing copied.
	Node *temp = rhs.head;
	while (temp != NULL)
	{
		//Making a new Node
		Node *newNode = new Node;
		//Copying data to new Node.
		newNode->data = temp->data;
		newNode->next = NULL;
		//Checking new list is empty.
		if (head == NULL)
		{
			//Initialising the new list.
			head = newNode;
			tail = newNode;
		}
		//Placing the new Node in the new List.
		else
		{
			tail->next = newNode;
			tail = newNode;
		}

		//Moving to the next Node.
		temp = temp->next;

	}
}


//destroys (cleans up) the list
LinkedList::~LinkedList()
{
	Node* temp = head;
	//Going through the list deleting the head node and replacing it with the next until the list is empty.
	while (temp != NULL) 
	{
		head = head->next;
		delete temp;
		temp = head;
	}
}

//adds a value to the head of the list
void LinkedList::push(int value)
{
	//New node with new data.
	Node *newNode = new Node;
	newNode->data = value;
	newNode->next = NULL;
	//If list is empty initialise list with the new node as head and tail.
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	else
	{
		//Insert the new Node in front of the head and make it the new head.
		newNode->next = head;
		head = newNode;
	}
	
}

//gets the last element from the list, without removing it
//requires: list not empty
int LinkedList::peekTail()
{

	//Check if list is empty.
	if (!head)
	{
		cout << "Error: List is empty." << endl;
		return -1;
	}

	//Getting value of tail.

	int val = tail->data;
	return val;

}

//prints the list in order from head to tail
string LinkedList::toString() const
{
	int tmp; //temporary int to save the data
	string liststr; //string that lists values

	//Check if list is empty. 
	if (!head) {

		return liststr;
	}

	//Getting head value. This had to be done in order to not have any extra spaces.
	liststr = to_string(head->data);

	Node *temp = new Node;
	
	//Getting rest of values.
	if (head->next != NULL) {
		
		temp = head->next;

		while (temp != NULL)
		{
			tmp = temp->data;
			temp = temp->next;
			string tmpstr = to_string(tmp);
			liststr = liststr + " " + tmpstr;

		}
	}

	return liststr;
}

//removes and returns the value at the head of the list
//requires: list not empty
int LinkedList::pop()
{
	Node *temp = head;
	
	//Check if list is empty.
	if (!head)
	{
		cout << "Error: List is empty." << endl;
		return -1;
	}
	
	//Getting value.
	int val = temp->data;
	
	//Setting new head.
	head = temp->next;
	//Deleting the original head.
	delete temp;

    return val;
}

//adds a value to the end of the list
void LinkedList::append(int value)
{
	//Making new Node.
	Node *newNode = new Node;
	newNode->data = value;
	newNode->next = NULL;

	//If list is empty initialise new list.
	if (head == NULL)
	{
		head = newNode;
		tail = newNode;
	}
	//Add new node to end of list.
	else
	{
		tail->next = newNode;
		tail = newNode;
	}

}

//appends the deep copies of the nodes of rhs on to the end of this list
void LinkedList::appendList(const LinkedList& rhs)
{
	Node *temp = rhs.head;

	//Start at head of list to be copied.
	while (temp != NULL)
	{
		//Making new node
		Node *newNode = new Node;
		newNode->data = temp->data; //Copying data
		newNode->next = NULL;

		//Adding new node to the end of the original list.
		tail->next = newNode;
		tail = newNode;

		//Moving on to the next node.
		temp = temp->next;

	}
}

//inserts a value immediately after the first occurrence of afterValue,
//if afterValue is not in the list then inserts at the tail
void LinkedList::insertAfter(int value, int afterValue)
{
	
	int valuefound;

	//Makink new node with value
	Node *newNode = new Node;
	newNode->data = value;
	newNode->next = NULL;
    
	//Going through list to find value
	Node *temp = head;
	while (temp != NULL)
	{
		if (temp->data == afterValue)
		{
			//Insert value
			valuefound = 1;
			newNode->next = temp->next;
			temp->next = newNode;
			return;
		}
		else
		{
			//If value wasn't found valuefound is kept at 0.
			valuefound = 0;
		}

		temp = temp->next;
	}

	//If value wasn't found new node is inserted at the end of list.
	if (valuefound == 0) {
		tail->next = newNode;
		tail = newNode;
	}
}

//removes all occurrences of value from the list
void LinkedList::removeAllOccurences(int value)
{

	Node *previous = new Node;
	previous = NULL;
	Node *current = head;

	//Going through list
	while (current != NULL)
	{
		//If value is found 
		if (current->data == value)
		{
			//If the current node is the head
			if (!previous) {
				head = current->next;
				delete current;
				current = head;
			}
			else
			{
				previous->next = current->next;
				delete current;
				current = previous->next;
			}

		}
		else
		{
			previous = current;
			current = current->next;
		}
		
	}
}

//reverses the list
void LinkedList::reverse()
{
	//Check if list is empty.
	if (head == NULL) 
	{
		cout << "Error: List is empty," << endl;
		return;
	}

	Node *current = head;
	Node *previous = NULL;
	Node *next = NULL;
	
	//Going through list reversing the order.
	while (current != NULL) {
		next = current->next;
		current->next = previous;
		previous = current;
		current = next;
	}

	head = previous;
}

//checks if two lists are equal in state (contain the same values in the same order)
bool LinkedList::operator ==(const LinkedList& other) const
{
	Node *l1 = head;
	Node *l2 = other.head;
	int areEqual = 0;

	//Checking values of each node.
	while (l1 != NULL) {

		if (l1->data = l2->data) {
			areEqual = 1;
		}
		else {

			areEqual = 0;
		}

		l1 = l1->next;
		l2 = l2->next;

	}

	//Returning result.
	if (areEqual = 0) {
		return false;
	} else {
		return true;
	}

  	
    
}

//checks if two lists are not equal in state
bool LinkedList::operator !=(const LinkedList& other) const
{
	Node *l1 = head;
	Node *l2 = other.head;
	int areEqual = 0;

	//Checking each value also updating the variable checking if they are still equal.
	while (l1 || l2) {

		if (!l1 && !l2) {
			return false;
		}
		else if (!l1) {
			return true;
		}
		else if (!l2){
			return true;
		}
		else {

			if (l1->next)

				if (l1->data = l2->data) {
					areEqual = 1;
				}
				else {

					areEqual = 0;
				}

				l1 = l1->next;
				l2 = l2->next;

		}
	}

	//If any value was not equal at any point return true.
	if (areEqual = 0) {
		return true;
	}
	else {
		return false;
	}
}

//pushes a new value onto the head of the list
LinkedList& LinkedList::operator +(int value)
{
	//Adding value to head of list, see push function for mor e information.   
	push(value);

    return *this;
}

//copy assignment operator (performs a deep copy)
LinkedList& LinkedList::operator =(const LinkedList& rhs)
{
	//Deleting nodes in the original list (If notes are eqal i.e. lhs == rhs the note is not changed.
	Node *temp = head;
	Node *rhstemp = rhs.head;

	while (temp != NULL)
	{
		if (temp != rhstemp) {
			head = head->next;
			delete temp;
			temp = head;
		}
		else {
			temp = temp->next;
			rhstemp = rhstemp->next;
		}

	}
	//Setting tail to NULL if list is empty.
	if (head == NULL) {
		head = tail = NULL;
	}
	

	Node *temp2 = rhs.head;
	//Copying list.
	while (temp2 != NULL)
	{
		//Making new node.
		Node *newNode = new Node;
		newNode->data = temp2->data;
		newNode->next = NULL;
		//If list is empty initialise with new node.
		if (head == NULL)
		{
			head = newNode;
			tail = newNode;
		}
		else
		{
			//Check that the node does not already exist. If not copy new node.
			if (temp != rhstemp) {
				tail->next = newNode;
				tail = newNode;
			}
			else {
				delete newNode;
			}
		}

		//Moving onto the next node.
		temp2 = temp2->next;
	
	}
	
    return *this;

	
}

//pushes values from an input stream onto the front of the list
std::istream& operator>>(std::istream &in, LinkedList &value)
{
	int val;

	while (in >> val) {

		//Making new Node.
		Node *newNode = new Node;
		newNode->data = val;
		newNode->next = NULL;

		//If given list is empty initialise it with the given data.
		if (value.head == NULL)
		{
			value.head = newNode;
			value.tail = newNode;
		}
		//Push value to front of the list.
		else
		{
			value.push(val);
		}
	}
    return in;
}

//writes the values, in order, to an output stream
std::ostream& operator<<(std::ostream &out, const LinkedList &value)
{
	int tmp;
	string liststr;

	//Check if list is empty.
	if (!value.head) {

		return out;
	}
	
	//Get initial value.
	out << to_string(value.head->data);
	
	//Get rest of values.
	Node *temp = new Node;
	temp = value.head->next;

		while (temp != NULL)
		{
			tmp = temp->data;
			temp = temp->next;
			
			string tempstr = to_string(tmp);

			out << " " << tempstr;
		}
	
    return out;
}
