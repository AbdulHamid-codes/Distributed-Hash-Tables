#pragma once

#include<iostream>
#include<string>
#include"../Project-Data_Strucures/Machine.h"
using namespace std;

struct MachineNode;
//class MachinesRing;

struct routingTableNode {          //Routing table Node
	int machineID;
	MachineNode* pointsToMachine;
	routingTableNode* next;
	routingTableNode* previous;
};

class RoutingTable {              //Routing table Class
private:
	routingTableNode* head;
public:
	RoutingTable() {
		head = nullptr;
	}
	routingTableNode* getHead() {
		return head;
	}
	void insert(MachineNode* machine, int id) {   //Insert machine in routing table
		routingTableNode* newNode = new routingTableNode;
		newNode->pointsToMachine = machine;
		newNode->machineID = id;
		newNode->next = newNode->previous = nullptr;
		if (head == nullptr) {
			head = newNode;
		}
		else {
			routingTableNode* temp = head;
			while (temp->next != nullptr)
				temp = temp->next;
			temp->next = newNode;
			newNode->previous = temp;
		}
	}
	void printRT() {
		if (head != nullptr) { 
			routingTableNode* temp = head;
			while (temp != nullptr) {
				cout << temp->machineID<<" ";
				temp = temp->next;
			}
			cout << endl;
		}
	}

};