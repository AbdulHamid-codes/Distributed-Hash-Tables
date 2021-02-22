#pragma once

#include"AVLtree.h"
#include"RoutingTable.h"

struct RoutingTableNode;
class RoutingTable;

struct MachineNode {           // Machine Node
	MachineNode* next;
	unsigned int machineID;
	RoutingTable RT;
	static int NoOfData;
	Node* AVLroot;
	

	void addData(unsigned int hashedKey, string data) {

		MachineNode* temp = this;

		if (hashedKey == temp->machineID) {
			int line = ++temp->NoOfData;
			string path = to_string(temp->machineID) + ".txt";
			temp->AVLroot = insert(temp->AVLroot, hashedKey, data, path, line);
		}
		else if (hashedKey < temp->machineID) {
			while (temp->next != this && hashedKey < temp->machineID) { // find the machine >= hashedKey
				temp = temp->next;
			}
			if (temp->next == this) {
				if (hashedKey > temp->machineID) {
					int line = ++temp->NoOfData;
					string path = to_string(temp->next->machineID) + ".txt";
					temp->next->AVLroot = insert(temp->next->AVLroot, hashedKey, data, path, line);
				}
				else {
					temp = temp->next;              // to find machine with minimum ID
					MachineNode* minimumID = temp;
					while (temp->next != this) {
						if (temp->machineID < minimumID->machineID)
							minimumID = temp;
						temp = temp->next;
					}
					if (temp->machineID < minimumID->machineID)
						minimumID = temp;
					string path = to_string(minimumID->machineID) + ".txt";
					int line = ++minimumID->NoOfData;
					minimumID->AVLroot = insert(minimumID->AVLroot, hashedKey, data, path, line);

				}

			}
			else {
				while (temp->next != this && hashedKey > temp->next->machineID) {
					temp = temp->next;
				}
				
					int line = ++temp->next->NoOfData;
					string path = to_string(temp->next->machineID) + ".txt";
					temp->next->AVLroot = insert(temp->next->AVLroot, hashedKey, data, path, line);
			
			}
			//int line = ++temp->NoOfData;
			//string path = to_string(temp->next->machineID) + ".txt";
			//temp->next->AVLroot = insert(temp->next->AVLroot, hashedKey, data, path, line); //store data in that machine
		}
		else if (hashedKey > temp->machineID) {
			while (temp->next != this && hashedKey > temp->machineID) {  //search all the way
				temp = temp->next;
			}
			if (temp->next == this) {         // if searched throughtout the chord and reach back
				if (hashedKey > temp->machineID) {  //if greater than all the machines
					// keep in the first/with minimum ID machine

				
					temp = temp->next;
					MachineNode* minimumID = temp;
					while (temp->next != this ) {
						if (temp->machineID < minimumID->machineID)
							minimumID = temp;
						temp = temp->next;
					}
					if (temp->machineID < minimumID->machineID)
						minimumID = temp;
					int line = ++minimumID->NoOfData;
					string path = to_string(minimumID->machineID) + ".txt";
					minimumID->AVLroot = insert(minimumID->AVLroot, hashedKey, data, path, line);
				}
				else { // if the final node is the node responsible
					int line = ++temp->NoOfData;
					string path = to_string(temp->machineID) + ".txt";
					temp->AVLroot = insert(temp->AVLroot, hashedKey, data, path, line);
				}
			}
			else { //if not searched throughout the chord and id is greater than machineID somewher in middle
					int line = ++temp->NoOfData;
					string path = to_string(temp->machineID) + ".txt";
					temp->AVLroot = insert(temp->AVLroot, hashedKey, data, path, line);
				
			}
		}
	}

	//To remove the data with the the given key
	void removeData(unsigned int hashedKey) {
		MachineNode* temp = this;

		if (hashedKey == temp->machineID) {
			temp->AVLroot = deleteNode(temp->AVLroot, hashedKey);
		}
		else if (hashedKey < temp->machineID) {
			while (temp->next != this && hashedKey < temp->machineID) { // find the machine >= hashedKey
				temp = temp->next;
			}
			if (temp->next == this) {
				if (hashedKey > temp->machineID) {
					temp->AVLroot = deleteNode(temp->AVLroot, hashedKey);
				}
				else {
					temp = temp->next;              // to find machine with minimum ID
					MachineNode* minimumID = temp;
					while (temp->next != this) {
						if (temp->machineID < minimumID->machineID)
							minimumID = temp;
						temp = temp->next;
					}
					if (temp->machineID < minimumID->machineID)
						minimumID = temp;
					minimumID->AVLroot = deleteNode(minimumID->AVLroot, hashedKey);

				}

			}
			else {
				while (temp->next != this && hashedKey > temp->next->machineID) {
					temp = temp->next;
				}

				temp->AVLroot = deleteNode(temp->AVLroot, hashedKey);

			}
			//int line = ++temp->NoOfData;
			//string path = to_string(temp->next->machineID) + ".txt";
			//temp->next->AVLroot = insert(temp->next->AVLroot, hashedKey, data, path, line); //store data in that machine
		}
		else if (hashedKey > temp->machineID) {
			while (temp->next != this && hashedKey > temp->machineID) {  //search all the way
				temp = temp->next;
			}
			if (temp->next == this) {         // if searched throughtout the chord and reach back
				if (hashedKey > temp->machineID) {  //if greater than all the machines
					// keep in the first/with minimum ID machine

					temp = temp->next;
					MachineNode* minimumID = temp;
					while (temp->next != this) {
						if (temp->machineID < minimumID->machineID)
							minimumID = temp;
						temp = temp->next;
					}
					if (temp->machineID < minimumID->machineID)
						minimumID = temp;
					minimumID->AVLroot = deleteNode(minimumID->AVLroot, hashedKey);
				}
				else { // if the final node is the node responsible
					temp->AVLroot = deleteNode(temp->AVLroot, hashedKey);
				}
			}
			else { //if not searched throughout the chord and id is greater than machineID somewher in middle
				temp->AVLroot = deleteNode(temp->AVLroot, hashedKey);

			}
		}
	}
	//To search the data with the the given key
	void searchData( unsigned int hashedKey) {
		MachineNode* temp = this;

		if (hashedKey == temp->machineID) {
			preOrderSearch(temp->AVLroot, hashedKey);
		}
		else if (hashedKey < temp->machineID) {
			while (temp->next != this && hashedKey < temp->machineID) { // find the machine >= hashedKey
				temp = temp->next;
			}
			if (temp->next == this) {
				if (hashedKey > temp->machineID) {
					preOrderSearch(temp->AVLroot, hashedKey);
				}
				else {
					temp = temp->next;              // to find machine with minimum ID
					MachineNode* minimumID = temp;
					while (temp->next != this) {
						if (temp->machineID < minimumID->machineID)
							minimumID = temp;
						temp = temp->next;
					}
					if (temp->machineID < minimumID->machineID)
						minimumID = temp;
					preOrderSearch(minimumID->AVLroot, hashedKey);

				}

			}
			else {
				while (temp->next != this && hashedKey > temp->next->machineID) {
					temp = temp->next;
				}

				preOrderSearch(temp->AVLroot, hashedKey);

			}
		}
		else if (hashedKey > temp->machineID) {
			while (temp->next != this && hashedKey > temp->machineID) {  //search all the way
				temp = temp->next;
			}
			if (temp->next == this) {         // if searched throughtout the chord and reach back
				if (hashedKey > temp->machineID) {  //if greater than all the machines
					// keep in the first/with minimum ID machine

					temp = temp->next;
					MachineNode* minimumID = temp;
					while (temp->next != this) {
						if (temp->machineID < minimumID->machineID)
							minimumID = temp;
						temp = temp->next;
					}
					if (temp->machineID < minimumID->machineID)
						minimumID = temp;
					preOrderSearch(minimumID->AVLroot, hashedKey);
				}
				else { // if the final node is the node responsible
					preOrderSearch(temp->AVLroot, hashedKey);
				}
			}
			else { //if not searched throughout the chord and id is greater than machineID somewher in middle
				preOrderSearch(temp->AVLroot, hashedKey);

			}
		}
	}
};
int MachineNode::NoOfData = 0;

class MachinesRing {         // Circular linked list of machines
private:
	MachineNode* head;
	MachineNode* tail;
public:
	MachinesRing() {
		head = nullptr;
		tail = nullptr;
	}
	MachineNode* getHead() {
		return head;
	}
	MachineNode* getTail() {
		return tail;
	}
	bool searchMachine(unsigned int id) {    // if there is machine with the given id
		if (head != nullptr) {
			MachineNode* temp = head;
			while (temp != tail) {
				if (temp->machineID == id)
					return true;
				temp = temp->next;
			}
			if (tail->machineID == id)
				return true;
		}
		return false;
	}
	void addMachine(unsigned int id) {                // to add new machine into the Distributed network
		MachineNode* newMachine = new MachineNode;
		newMachine->machineID = id;
		newMachine->AVLroot = nullptr;
		newMachine->next = nullptr;

		if (head == nullptr) {
			head = newMachine;
			tail = newMachine;
			head->next = tail;
			tail->next = head;
		}
		else if (head->machineID > id) {
			newMachine->next = head;
			tail->next = newMachine;
			head = newMachine;
		}
		else {
			MachineNode* temp = head;
			while (temp != tail && temp->next->machineID<id) {
				temp = temp->next;
			}
			if (temp ==  tail) {
				temp->next = newMachine;
				newMachine -> next = head;
				tail = newMachine;
			}
			else {
				newMachine->next = temp->next;
				temp->next = newMachine;
			}
			
		}
	}
	void deleteMachine(unsigned int hashedKey) {

		if (head==tail && hashedKey==head->machineID) {  // if only one node is ther
			delete head;
			head = nullptr;

		}
		else if (hashedKey == head->machineID) {  // if head is the node to delete
			MachineNode* temp = head;
			head = head->next;
			tail->next = head;
			delete temp;
			temp = nullptr;
		}
		else if (hashedKey == tail->machineID) {   // if tail is the node to delete
			MachineNode* temp = head;
			while (temp->next != tail) {
				temp = temp->next;
			}
			MachineNode* toRemove = temp->next;
			temp->next = head;
			tail = temp;
			delete toRemove;
			toRemove = nullptr;
		}
		else {                          // if node to delete is in middle somewhere
			MachineNode* temp = head;
			while (temp->next != tail && temp->next->machineID != hashedKey)
				temp = temp->next;
			MachineNode* toRemove = temp->next;
			temp->next = temp->next->next;
			delete toRemove;
			toRemove = nullptr;
		}
		string file = to_string(hashedKey) + ".txt";
		remove(file.c_str());     // Delete the file associated with this machine
	}
	void printMachinesRing() { // To display all the current machines ids present in the distributed network
		cout << "\n\t************Machines in the distributed System*****************\n\t";
		MachineNode* temp = head;
		while (temp != tail) {
			cout << temp->machineID << " ";
			temp = temp->next;
		}
		cout << temp->machineID << endl<<endl;
	}
	void addData(unsigned int key, string value) {     // Key value pair can also be inserted directly in machines list
		MachineNode* temp = getMachineResponsibleFor(key);
		string path = to_string(temp->machineID) + ".txt";
		int line = ++temp->NoOfData;
		temp->AVLroot = insert(temp->AVLroot, key, value, path,line);
		
	}
	MachineNode* getMachineResponsibleFor(int id) { //to find the machine with machineID => id
		MachineNode* temp = head;
		while (temp!=tail && temp->machineID < id)
			temp = temp->next;
		if (temp == tail && temp->machineID < id)
			return head;
		return temp;
	}
	void fillRoutingTables(int length) {  // To fill routing table of each Node
		if (head != nullptr) {
			MachineNode* temp = head;
			unsigned int id;
			while (temp != tail) {
				for (int i = 1; i <= length; i++) {
					id = temp->machineID + pow(2, i-1);
					int range = pow(2, length);
					id = id % range;
					MachineNode* responsibleMachine = this->getMachineResponsibleFor(id);
					temp->RT.insert(responsibleMachine, responsibleMachine->machineID);
				}	
				temp = temp->next;
			}
			for (int i = 1; i <= length; i++) {        //  for the tail node
				id = temp->machineID + pow(2, i - 1);
				int range = pow(2, length);
				id = id % range;
				MachineNode* responsibleMachine = this->getMachineResponsibleFor(id);
				temp->RT.insert(responsibleMachine, responsibleMachine->machineID);
			}
		}
	
	}
};
