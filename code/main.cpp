#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <ios>    //used to get stream size
#include <limits> //used to get numeric limits
#include <vector>
using namespace std;

class item
{
    int id;
    string name;
    float cost;
    int discount, quantity;

public:
    item(){};
    item(int id, string name, float cost, int discount, int quantity)
    {
        this->id = id;
        this->cost = cost;
        this->discount = discount;
        this->name = name;
        this->quantity = quantity;
    }
    void get_details();
    void give_details(int &a, string &b, float &c, int &d, int &e)
    {
        a = id;   //
        b = name; //
        c = cost;
        d = discount;
        e = quantity;
    }
    void item_update(int quantity, int discount);
    void give_quantity(int &quantity);
    void give_discount(int &discount);
    void give_id(int &id);
};
class supermarket
{
    // int password=12345;
    map<int, item> item_list; // id,item ///////////
public:
    supermarket(){};
    void fill_map();
    void save_map();
    void show_all();
    void add_item();
    void update_item();
    void remove_item();
    void billing();
};
void item::item_update(int quantity, int discount)
{
    this->quantity += quantity;
    this->discount = discount;
}
void item::give_quantity(int &quantity)
{
    quantity = this->quantity;
}
void item::give_discount(int &discount)
{
    discount=this->discount;
}
void item::give_id(int &id)
{
    id=this->id;
}
void item::get_details()
{

    cout << "Enter item id: ";
    cin >> id;
    cout << "\n";
    cout << "Enter item cost: ";
    cin >> cost;
    cout << "\n";
    cout << "Enter discount: ";
    cin >> discount;
    cout << "\n";
    cout << "Enter item name: ";
    cin >> name;
    cout << "Enter item quantity: ";
    cin >> quantity;
}
int strToNum(string s)
{
    return stoi(s);
}
int strTofloat(string s)
{
    return stof(s);
}
void supermarket::fill_map()
{
    fstream f;
    f.open("../data/supermarket.csv", ios::in);
    string temp;
    // skipping the first row containing column headers;
    getline(f >> ws, temp);
    // analyzing each entry afterwards;
    while (getline(f >> ws, temp))
    {
        // item i;
        //  creating a string stream object to read from string 'temp';
        stringstream s(temp);
        string s1, name, s3, s4, s5;
        // reading from the string stream object 's';
        getline(s, s1, ',');
        int id = strToNum(s1);
        getline(s, name, ',');
        getline(s, s3, ',');
        float cost = strTofloat(s3);
        getline(s, s4, ',');
        getline(s, s5, ',');
        int discount = strToNum(s4);
        int quantity = strToNum(s5);
        item i(id, name, cost, discount, quantity);
        item_list[id] = i;
    }
    f.close();
    return;
}
void supermarket::save_map()
{

    fstream f;
    f.open("../data/temp.csv", ios::out);
    // `le first line conataining column headers:
    f << "itemId,itemName,itemCost,itemDiscount\n";
    for (auto p : this->item_list) ////
    {
        int a, d, e;
        string b;
        float c;
        p.second.give_details(a, b, c, d, e); /////
        f << to_string(a) << "," << b << "," << to_string(c) << "," << to_string(d) << "," << to_string(e) << endl;
    }
    f.close();
    remove("../data/supermarket.csv");
    rename("../data/temp.csv", "../data/supermarket.csv");
    return;
}
void supermarket::show_all()
{
     if(item_list.size()==0)
    {
        cout<<"Store is empty !!\n";
        return;
    }
    cout << "--------------------------------------------------------------------\n";
    cout << "Item Id     Itemname     ItemCost     ItemDiscount     Quantity" << endl;
    cout << "--------------------------------------------------------------------\n";

    for (auto it : item_list)
    {
        int a, d, e;
        string b;
        float c;
        it.second.give_details(a, b, c, d, e); /////
        cout << "   " << a << "        " << b << "         " << c << "           " << d << "%"
             << "             " << e << endl;
    }
    return;
}
void supermarket::add_item()
{
    system("cls");
    item i;
    i.get_details();
    int id, discount, quantity;
    float cost;
    string name;
    i.give_id(id);
    if (item_list.find(id) != item_list.end())
    {
        cout<<"Item with given id is present in the store !!!\n";
        cout<<"Are u trying to add the same?\n1.YES\n2.NO\n";
        int input;
        cin>>input;
        if(input==1)
        {
            item_list[id].item_update(quantity, discount);
        }
        else{
            cout<<"try with another id\n";
            item i2;
            i2.get_details();
            int id;
            i2.give_id(id);
            item_list[id]=i2;
            
        }
    }
    else
    {
        item_list[id] = i;
    }
}
void supermarket::update_item()
{
    system("cls");
    if(item_list.size()==0)
    {
        cout<<"Store is empty !!\n";
        return;
    }
    int id, discount, quantity;
    cout << "Enter item id to update it:  ";
    cin >> id;
    item i;
    cout << endl;
    if (item_list.find(id) == item_list.end())
    {
        cout << "Item not found, Please enter valid id\n";
        cout << "Do you want to see id's of all items\n";
        cout << "1.Yes\n2.No\n";
        int input;
        cin >> input;
        if (input == 1)
        {
            system("cls");
            supermarket::show_all();
            cout << "----------------------------------------------------------------------------------------------";
            cout << endl;
            cout << "Now Enter the id: ";
            cin >> id;
           // system("cls");
            i = item_list[id];
            // int discout,quantity;
            int check_discount;
            i.give_discount(check_discount);
            cout<<"previous discount on this item is "<<check_discount<<"%\n";
            cout << "Enter discount u want to update: ";
            cin >> discount;
            cout << endl;
            cout << "Enter quantity to add: ";
            cin >> quantity;
            i.item_update(quantity, discount);
            item_list[id] = i;
        }
        if (input == 2)
        {
            cout << "ok,then enter the correct id: ";
            cin >> id;
            i = item_list[id];
            cout<<endl;
            // int discout,quantity;
            int check_discount;
            i.give_discount(check_discount);
            cout<<"previous discount on this item is "<<check_discount<<"%\n";
            cout << "Enter discount u want to update: ";
            cin >> discount;
            cout << endl;

            cout << "Enter quantity to add: ";
            cin >> quantity;
            i.item_update(quantity, discount);
            item_list[id] = i;
        }
    }
    else
    {
        i = item_list[id];
        // int discout,quantity;
         int check_discount;
            i.give_discount(check_discount);
            cout<<"previous discount on this item is "<<check_discount<<"%\n";
        cout << "Enter discount u want to update: ";
        cin >> discount;
        cout << endl;
        cout << "Enter quantity to add: ";
        cin >> quantity;
        i.item_update(quantity, discount);
        item_list[id] = i;
    }
}
void supermarket::billing()
{
    system("cls");
    if(item_list.size()==0)
    {
        cout<<"No item present in stote !!!\n";
        return;
    }
    cout << "No of items purchased: \n";
    int n;
    cin >> n;
    while (n > item_list.size())
    {
        cout << "Sorry we do not have that much items, please enter correct number: ";
        cin >> n;
    }
    vector<pair<int, int>> purchased_items;
    int i = 1;
    while (purchased_items.size() < n)
    {
        int id, quantity;
        cout << "Enter the id of item: " << i << endl;
        cin >> id;
        while (item_list.find(id) == item_list.end())
        {
            cout << "Item not present in our store\nEnter the valid id: ";
            cin >> id;
        }
        while (1)
        {
            cout << "Enter quantity: ";
            cin >> quantity;
            int input_quntity;
            item_list[id].give_quantity(input_quntity);
            if (input_quntity < quantity)
            {
                cout << "sorry we are out of stock!!!!\n Please enter correct id: ";
                cin >> id;
            }
            else break;
        }

        cout << endl;
       
        purchased_items.push_back({id, quantity});
        i++;
    }
    system("cls");
    cout << "Printing your bill.............\n\n\n\n";
    float total = 0;
    int id, discount, purchased_quantity, quantity;
    float item_cost, item_price;
    string item_name;
    cout << "--------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << " sr.no"
         << "     "
         << "item id"
         << "     "
         << "item name"
         << "     "
         << "item cost"
         << "    "
         << "discount"
         << "    "
         << "quantity"
         << "      "
         << "item_price\n";
    cout << "--------------------------------------------------------------------------------------------------------------------------------------\n";
    for (int i = 0; i < purchased_items.size(); i++)
    {
        id = purchased_items[i].first;
        purchased_quantity = purchased_items[i].second;
        item item = item_list[id];
        item.give_details(id, item_name, item_cost, discount, quantity);
        item_price = purchased_quantity * item_cost * ((100 - discount) / 100.00);
        total += item_price;
        cout << "  " << i + 1 << "         " << id << "          " << item_name << "          " << item_cost << "            " << discount << "%          " << purchased_quantity << "          " << item_price << endl;
        item.item_update(-purchased_quantity, discount);
        item_list[id] = item;
    }
    cout << endl;
    cout << "----------------------------------------------------------------------------------------------------------------------------------------\n";
    cout << "Total BILL: ";
    cout << total << endl;
    cout<<"\n";
}
void supermarket::remove_item()
{
    system("cls");
     if(item_list.size()==0)
    {
        cout<<"Store is empty !!\n";
        return;
    }
    cout << "Enter the id of item: ";
    int id;
    cin >> id;
    cout << endl;
    while (item_list.find(id) == item_list.end())
    {
        cout << "Enter valid id: ";
        cin >> id;
    }
    cout << endl;
    item_list.erase(id);
    cout << "Item removed succefully!!!\n";
}

int main()
{
    supermarket d_mart;
    d_mart.fill_map();
    cout << "\n\n\n\n";

    while (1)
    {
        // system("cls");
        cout << "\n\n\n\n\n";
        cout << "************************************************  MAIN MENU  ************************************************************\n\n\n\n";
        cout << "1. Adminitrative login" << endl;
        cout << "2. Biller Login\n"
             << "3. exit\n\n\n";
        cout << "************************************************************************************************************************\n";
        cout << "Enter login choice: ";

        int login_choice;
        cin >> login_choice;
        system("cls");
        if (login_choice == 3)
        {
            cout << "System shutting down.......";
            break;
        }
        if (login_choice == 1)
        {
            cout << "1. view all items \n2. add new item\n3. update item\n4. remove item\n\n";
            int choice;
            cout << "Enter your choice: ";

            cin >> choice;
            system("cls");
            // item i;
            // i.get_details();
            if (choice == 1)
            {
                d_mart.show_all();
            }
            else if (choice == 2)
            {
                //d_mart.add_item();
                int a=1;
                while(a)
                {
                    d_mart.add_item();
                    cout<<"want to add anoter item? \n";
                    cout<<"1.Yes\n2.NO\n";
                    int input;
                    cin>>input;
                    if(input==1)
                    {
                        continue;
                    }
                    else
                    {
                        cout<<"Thank you!!\n Items added succesfully\n";
                        break;
                    }

                }
            }
            else if (choice == 3)
            {
                int a=1;
                while(a)
                {
                    d_mart.update_item();
                    cout<<"want to update anoter item? \n";
                    cout<<"1.Yes\n2.NO\n";
                    int input;
                    cin>>input;
                    if(input==1)
                    {
                        continue;
                    }
                    else
                    {
                        cout<<"Thank you!!\n Items updated succesfully\n";
                        break;
                    }

                }
            }
            else if (choice == 4)
            {
               int a=1;
                while(a)
                {
                    d_mart.remove_item();
                    cout<<"want to remove anoter item? \n";
                    cout<<"1.Yes\n2.NO\n";
                    int input;
                    cin>>input;
                    if(input==1)
                    {
                        continue;
                    }
                    else
                    {
                        cout<<"Thank you!!\n Items removed succesfully\n";
                        break;
                    }

                }

            }else{
                cout<<"choice is incorrect!!\n";
            }
        }
        if (login_choice == 2)
        {
            d_mart.billing();
        }
    }
    d_mart.save_map();

    return 0;
}