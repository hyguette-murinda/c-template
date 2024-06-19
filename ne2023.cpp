 #include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<string>
#include<bits/stdc++.h>
using namespace std;

void addItem( const string& item_id, const string& item_name, const string& item_quantity,const string& item_registration_date ){
    ofstream file("inventory.csv", ios::app);
    if (file.is_open()){
        file <<"item id: "<< item_id << ',' <<"item name: "<< item_name << ',' <<"item quantity: "<< item_quantity << ',' <<"item registration date: "<< item_registration_date << '\n';
        file.close();
        cout<<"items added successfully\n";
    }
    else{
        cout<<"please try again";
    }
}
void listItems(){
    ifstream file("inventory.csv");
    if(file.is_open()){
        vector<string> items;
        string line;
        while(getline(file, line)){
            items. push_back(line);
        }
            sort(items.begin(), items.end());
            cout << "Items in stock (sorted alphabetically):\n";
        for (const string& item : items) {
            cout << item << '\n';
        }
        file.close();
    }
}
int main(){
    string cont = "yes";
    while(cont != "exit"){
    string command1;
    string itemDetails;
    string item_id;
    string item_name;
    string item_quantity;
    string item_registration_date;
    cout<<" please enter the command:itemadd to add an item, itemsLists to list items : ";
    cin>>command1;
    transform(command1.begin(), command1.end(), command1.begin(), ::tolower);
    if(command1 =="itemadd"){
        cout<<"enter the item_id, name, quantity and registeration date, add them at the same time separate them using space: ";
        cin>> item_id>>item_name>>item_quantity>>item_registration_date;
        addItem(item_id, item_name, item_quantity, item_registration_date);
    }
        else if ( command1 =="itemslists"){
            listItems();
        }
        else if (command1 == "help"){
            cout<<"------------"<<endl;
            cout<<"command syntax"<<endl;
            cout<<"------------"<<endl;
            cout<<"itemadd <item_id> <item_name> <item_quantity> <item_registration_date>"<<endl;
            cout<<"itemsLists";
        }
        else if(command1 == "exit"){
            return 0;
        }
        else{
            cout<<"the code was incorecct\n ";
        }

        cout<<"\ndo you want to continue?(enter exit to terminate):";
        cin>>cont;
    }

    return 0;
}
