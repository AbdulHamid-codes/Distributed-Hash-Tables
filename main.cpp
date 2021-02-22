#include<iostream>
#include"Machine.h"
#include"SHA-1.h"
using namespace std;

string toBinnary(string text); // to convert hexadecimal string into binnary string
unsigned int generateID(string key, unsigned int range); // takes a string key/ip and create id in range of IS


int main(){
    MachinesRing DistributedSystem;
    int identifierSpace;
    unsigned int range;
    int numOfMachines;
 
    system("cls");
    cout << "\n\t====================Distributed Hash Table======================\n\n";


    cout << "\tEnter the identifier space in terms of number of bits (0-32): ";
    cin >> identifierSpace;
    if (identifierSpace > 32)  
        identifierSpace = identifierSpace % 33;   // To make sure IS in 32 bit range
    range = pow(2, identifierSpace);
    cout << "\n\tHow many machines do you want to add initially: ";
    cin >> numOfMachines;
    for (int i = 0; i < numOfMachines; i++) {
        int opt = 0;
        cout << "\n\t\tPress 1 to assign mannual id to your "<<i+1<<(i==0?"st":i==1?"nd":i==2?"rd":"th")<<" machine\n";
        cout << "\t\tPress 2 to auto generate id your "<<i+1<<(i==0?"st":i==1?"nd":i==2?"rd":"th")<<" machine\n\t\t";
        cin >> opt;
        int id;
        string ip;
        if (opt == 1) {
            cout << "\t\tEnter id ";
            cin >> id;
            if (DistributedSystem.searchMachine(id)) {
                cout << "\tMachine with id " << id << " is already present enter a different one\n";
                i--;
            }
            else if (id >= range) {
                cout << "\tThis id is above the range of our identifier space add smaller id\n";
                i--;
            }
            else {
                DistributedSystem.addMachine(id);
                cout << "\t---Machine with id " << id << " adde to the distributed system!---\n";
            }
        }
        else if (opt == 2) {
            cout << "\tEnter name/ip adress of the new machine\n\t";
            cin >> ip;
            // Generate the id for this ip and add the id into the distributed system
            unsigned int id = generateID(ip,range);

            if (DistributedSystem.searchMachine(id)) {
                cout << "\tMachine with id " << id << " is already present enter a different one\n";
                i--;
            }
            else if (id > range) {
                cout << "\tThis id is above the range of our identifier space add smaller id\n";
                i--;
            }
            else {
                DistributedSystem.addMachine(id);
                cout << "\t---Machine with id " << id << " added to the distributed system!---\n";
            }
        }
        else {
            cout << "\tPlease choose option 1 or 2\n";
            i--;
        }
    }
  
    DistributedSystem.fillRoutingTables(identifierSpace); //To fill the routing tables of added machines

    do
    {
        system("cls");
        DistributedSystem.printMachinesRing();
        cout << "\t================================\n";
        // cout << "\t   Done. Specify the number of machines \n";
        // cout << "\t   Done. Specify the size of identifier space \n";
        // cout << "\t   Done. Mannualy assign id to each machine \n";
        // cout << "\t   Done. Automatically assign id to each machine \n";
        cout << "\t   1. Insert data in the form of key, value pairs from any machine. \n";
        cout << "\t   2. Remove data by specifying the key from any machine. \n";
        cout << "\t   3. Print the routing table of any machine. \n";
        cout << "\t   4. Print the AVL tree maintain on any machine. \n";
        cout << "\t   5. Remove any machine on the fly without disrupting the functionality of Ring DHT. \n";
        cout << "\t   6. Add new machines on the fly without disrupting the functionality of Ring DHT. \n";
        cout << "\t   7. Searh for value with a key of the data. \n";
        cout << "\t================================\n"; 
        cout << "\t\toption: ";
        int option;
        cin >> option;

        string key, value;
        unsigned int id;

        switch (option)
        {
        case 1: {
            int id;
            cout << "\nEnter machine from which you want to enter data: ";
            cin >> id;
            if (DistributedSystem.searchMachine(id)) {
                string key, value;
                cout << "Enter the key of the data: ";
                cin >> key;
                unsigned int keyID = generateID(key, range);
                cout << "Key maped to: " << keyID << endl;
                cin.ignore();
                cout << "Enter the value of the data: ";
                getline(cin,value);
                MachineNode* temp = DistributedSystem.getHead();

                while (temp && temp != DistributedSystem.getTail()) {

                    if (temp->machineID == id) {
                        cout << " ";
                        break;
                    }
                    temp = temp->next;
                }

                temp->addData(keyID, value);

            }
            else {
                cout << "This machine does not exists in our distributed system\n";
            }
            /*In case required, data can be entered directly into to distributed system*/

            //cout << "Enter the key value pair to add\n";
            //cout << "Key: ";
            //cin >> key;
            //cout << "Value: ";
            //cin.ignore();
            //getline(cin, value);
            //id = generateID(key, range);
            //cout << "Key mapped to " << id << endl;
            //DistributedSystem.addData(id, value);
            break;
        }
        case 2: {
            cout << "Enter machine from where you want to perform remove operation:";
            cin >> id;
            if (DistributedSystem.searchMachine(id)) {
                string key, value;
                cout << "Enter the key of the data: ";
                cin >> key;
                unsigned int keyID = generateID(key, range);
                cout << "Key maped to: " << keyID << endl << endl;
                MachineNode* temp = DistributedSystem.getHead();

                while (temp && temp != DistributedSystem.getTail()) {

                    if (temp->machineID == id) {
                        cout << " ";
                        break;
                    }
                    temp = temp->next;
                }

                temp->removeData(keyID);
            }
            else {
                cout << "This machine does not exists in our distributed system\n";
            }
            break;
        }
        case 3: {
            cout << "Enter the machine id to prints its routing table: ";
            cin >> id;
            if (DistributedSystem.searchMachine(id)) {
                MachineNode* temp = DistributedSystem.getHead();
                while (temp && temp != DistributedSystem.getTail()) {
                    if (temp->machineID == id) {
                        cout << " ";
                        break;
                    }
                    temp = temp->next;
                }
                temp->RT.printRT();
            }
            else {
                cout << "This machine id is not present in the distributed system as of now\n";
            }

            break;
        }
        case 4: {
            cout << "Enter the machine id to print its AVL tree: ";
            cin >> id;
            if (DistributedSystem.searchMachine(id)) {
                MachineNode* temp = DistributedSystem.getHead();
                while (temp && temp != DistributedSystem.getTail()) {
                    if (temp->machineID == id) {
                        cout << " ";
                        break;
                    }
                    temp = temp->next;
                }

                preOrder(temp->AVLroot);
            }
            else
                cout << "This machine id is not present in the distributed system as of now\n";

            break;
        }
        case 5: {
            cout << "Enter machine id you want to remove\n";
            cin >> id;
            if (DistributedSystem.searchMachine(id)) {
                MachineNode* toRemove = DistributedSystem.getHead();
                while (toRemove != DistributedSystem.getTail() && toRemove->machineID != id)
                    toRemove = toRemove->next;
                MachineNode* successor = toRemove->next;

                // To accomodate its data in the successor before deleting it
                string dataToAdjust;
                preOrder1(toRemove->AVLroot, dataToAdjust);
                int length = dataToAdjust.length();
                for (int i = 0; i<length; i++) {
                    string key="", value="";
                    if (dataToAdjust[i] == '^') {
                        i++;
                        while ( i<length && dataToAdjust[i] != '*') {
                            key += dataToAdjust[i];
                            i++;
                        }
                        i++;
                        while (i<length && dataToAdjust[i] != '^') {
                            value += dataToAdjust[i];
                            i++;
                        }
                    }
                    unsigned int k = atoi(key.c_str());
                    string path = to_string(successor->machineID) + ".txt";
                    int line = ++successor->NoOfData;
                    successor->AVLroot = insert(successor->AVLroot, k, value, path, line);
                }


                DistributedSystem.deleteMachine(id);
                DistributedSystem.printMachinesRing();
            }
            else
                cout << "This mahcine id is not present in our distributed system as of now\n";
            break;
        }
        case 6: {
            int opt;
            cout << "\n\tPress 1 to assign mannual id to new machine\n ";
            cout << "\tPress 2 to auto generate id new machine\n";
            cin >> opt;
            unsigned int id=0;
            string ip;
            if (opt == 1) {
                cout << "\tEnter id ";
                cin >> id;
                if (DistributedSystem.searchMachine(id)) {
                    cout << "\tMachine with id " << id << " is already present enter a different one\n";
                }
                else if (id >= range) {
                    cout << "\tThis id is above the range of our identifier space add smaller id\n";
                }
                else {
                    DistributedSystem.addMachine(id);
                    cout << "\t---Machine with id " << id << " adde to the distributed system!---\n";
                }
            }
            else if (opt == 2) {
                cout << "Enter name/ip adress of the new machine\n";
                cin >> ip;
                // Generate the id for this ip and add the id into the distributed system
                 id = generateID(ip, range);

                if (DistributedSystem.searchMachine(id)) {
                    cout << "Machine with id " << id << " is already present enter a different one\n";
                }
                else if (id > range) {
                    cout << "This id is above the range of our identifier space add smaller id\n";
                }
                else {
                    DistributedSystem.addMachine(id);
                    cout << "---Machine with id " << id << " added to the distributed system!---\n";
                }
            }
            else {
                cout << "Please choose option 1 or 2\n";
            }
            //Adjust routing tables when new machine is added
            DistributedSystem.fillRoutingTables(identifierSpace);

            // To adjust the datas
            MachineNode* newAdded = DistributedSystem.getHead();
            while (newAdded != DistributedSystem.getTail() && newAdded->machineID != id)
                  newAdded = newAdded->next;
            MachineNode* successor = newAdded->next;
            string dataToAdjust;
            preOrder2(successor->AVLroot, dataToAdjust, newAdded->machineID);
            int length = dataToAdjust.length();
            for (int i = 0; i<length; ) {
                string key = "", value = "";
                if (dataToAdjust[i] == '^') {
                    i++;
                    while (i<length && dataToAdjust[i] != '*') {
                        key += dataToAdjust[i];
                        i++;
                    }
                    i++;
                    while (i<length && dataToAdjust[i] != '^') {
                        value += dataToAdjust[i];
                        i++;
                    }
                }
                unsigned int k = atoi(key.c_str());
                string path = to_string(newAdded->machineID) + ".txt";
                int line = ++newAdded->NoOfData;
                newAdded->AVLroot = insert(newAdded->AVLroot, k, value, path, line);
            }

            string nodesToDelete;
            preOrder3(successor->AVLroot, nodesToDelete, newAdded->machineID);
            int length2 = nodesToDelete.length();
            for (int i = 0; i < length2; i++) {
                string key = "";
                while (i < length && nodesToDelete[i] != ',') {
                    key += nodesToDelete[i];
                    i++;
                }
                unsigned int k = atoi(key.c_str());
                successor->AVLroot = deleteNode(successor->AVLroot, k);
            }

            break;
        }
        case 7: {
            cout << "Enter machine from where you want to perform search operation:";
            cin >> id;
            if (DistributedSystem.searchMachine(id)) {
                string key;
                cout << "Enter the key of the data: ";
                cin >> key;
                unsigned int keyID = generateID(key, range);
                cout << "Key maped to: " << keyID << endl << endl;
                MachineNode* temp = DistributedSystem.getHead();

                while (temp && temp != DistributedSystem.getTail()) {

                    if (temp->machineID == id) {
                        cout << " ";
                        break;
                    }
                    temp = temp->next;
                }

                temp->searchData(keyID);
            }
            else {
                cout << "This machine does not exists in our distributed system\n";
            }
            break;



        }
        default: exit(1);
        }
        cout << "\n";
      
        system("pause");
    } while (true);


    return 0;
}



string toBinnary(string text) {        // To conver the hexa decimal text into binnary
    string binnary;
    for (int i = 0; i < text.size(); ++i) {
        if (text[i] == '0')
            binnary += "0000";            // Appending the corresponding 4 bit binnary value of each hexa decimal digit
        else if (text[i] == '1')
            binnary += "0001";
        else if (text[i] == '2')
            binnary += "0010";
        else if (text[i] == '3')
            binnary += "0011";
        else if (text[i] == '4')
            binnary += "0100";
        else if (text[i] == '5')
            binnary += "0101";
        else if (text[i] == '6')
            binnary += "0110";
        else if (text[i] == '7')
            binnary += "0111";
        else if (text[i] == '8')
            binnary += "1000";
        else if (text[i] == '9')
            binnary += "1001";
        else if (text[i] == 'a')
            binnary += "1010";
        else if (text[i] == 'b')
            binnary += "1011";
        else if (text[i] == 'c')
            binnary += "1100";
        else if (text[i] == 'd')
            binnary += "1101";
        else if (text[i] == 'e')
            binnary += "1110";
        else if (text[i] == 'f')
            binnary += "1111";
    }
    return binnary;
}

unsigned int generateID(string key,unsigned int range) {
    SHA1 sha1;
    string hashedValue = sha1(key);
    string binnaryOfHashValue = toBinnary(hashedValue);
    string least64Bits;
    for (int i = 128; i < 160; i++)
        least64Bits.push_back(binnaryOfHashValue[i]);
    // cout << "Length of least64BIts string is: " << least64Bits.length() << endl;
    unsigned int  decimalValue = 0, count = 0;

    for (int i = 31; i >= 0; i--) {
        decimalValue += (int(least64Bits[i]) - 48) * pow(2, count);
        count++;
    }
    return decimalValue % range;
}