/**
OOP PBL AUCTION
Grp Members:-
Name                Gr       Roll
Pranav Rodge	  21910464	233053
Pratham Solanki   21910112	233061
Chaitanya Uge	  21910718	233064
Yash Chaudhari	  21910388	233066
**/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <fstream>
#include <ctype.h>
#include <string>
#include <vector>
using namespace std;

class item
{
public:
    string name_of_item, name_of_owner, desc;
    float price;
    int b_id, flag;

    item()
    {
        price = 0;
        b_id = 0;
        flag = 1;
    }
};

void disp(item obji)
{
    if (obji.flag == 1)
    {
        cout << obji.name_of_item << "\t\t" << obji.name_of_owner << "\t\t" << obji.desc << endl;
    }
}

item create()
{
    item obji;
    cin.ignore();
    cout << "\nEnter the Name of the Item\n";
    getline(cin, obji.name_of_item);
    cout << "\nEnter the Name of the Owner\n";
    getline(cin, obji.name_of_owner);
    cout << "\nEnter Description of Item in less than 50 words\n";
    getline(cin, obji.desc);
    cout << "\nName of item\tName of Owner\tDescription\n";
    obji.flag = 1;
    disp(obji);
    return obji;
}

vector<string> take_auctioneers()
{
    int no_auctioneer = 0;
    string temp;
    vector<string> name;
    char again = 'y';
    cin.ignore();
    bool wflag = true;
    do
    {
        cin.ignore();
        no_auctioneer++;
        cout << "\nEnter Name of Auctioneer number " << no_auctioneer << endl;
        getline(cin, temp);
        name.push_back(temp);
        cout << "\nThe Auctioning ID of Auctioneer " << name[no_auctioneer - 1] << " is " << no_auctioneer << endl;

        cout << "\nDo you want to enter again(y/n) ?";
        cin >> again;

        if(again != 'y')
            wflag = false;
    } while (wflag);

    return name;
}

void auction(vector<item> obj)
{
    float price = 0.0, pre = 0.0;
    int i, j;

    int names_entered = 0;
    vector<string> name;

    string line = "\nSummary\n";
    fstream afile;
    afile.open("samp.txt", ios ::in | ios ::out | ios ::app);
    afile << line;
    line = "\nThe List of Items Sold are:\n";

    int no_auctioneer;
    bool wflag = true;
    while (wflag)
    {
        name = take_auctioneers();
        no_auctioneer = name.size();
        if (no_auctioneer < 2)
            cout << "\nNumber Auctioneers cannot be less than 2.....Try entering names again\n";
        else
        {
            wflag = false;
        }
    }

    cout << "\n\nStarting Auction..................";

    for (int i = 0; i < obj.size(); i++)
    {
    SALE:
        cout << "\nItem on sale is:\nName:\t" << obj[i].name_of_item << "\nDesc\t" << obj[i].desc << endl;
        cout << "\nBase Price: 100.00\n(Press 0 0 to Pass)";

    Lab:
        cout << "\nBidder Input Price as: Bidder_ID Price\n";
        cin >> j >> price;

        if ((j == 0) && (price == 0) && (obj[i].flag == 1))
        {
            //   obj[i].b_id = obj[i].price = j;
            i++;
            goto SALE;
        }

        if (((price < 100.00) || (price < pre)) || ((j < 1) || (j > no_auctioneer)))
        {
            cout << "\nCannot Except Either ID or Price\n";
            goto Lab;
        }
        else
        {
            pre = price;
            obj[i].b_id = j;
            obj[i].price = pre;
            obj[i].flag = 0;
            clock_t start = clock();
            cout << "\nTimer: 5 sec\nPlease enter the input:\n";

            while (!_kbhit()) //Check for keyboard hit
            {
                if (((clock() - start) / CLOCKS_PER_SEC) >= 5)
                {
                    cout << "\nTIMEOUT 5 sec . . .\n";

                    if (i < (no_auctioneer - 1))
                    {
                        pre = 0.0;
                        price = 0.0;
                        i++;
                        goto SALE;
                    }

                    else
                    {
                        goto time_out;
                    }
                }
            }

            goto Lab;
        }
    }

time_out:
    cout << "\nAuction Complete!\nThe List of Items Sold and to whom at price are:\nName of Item\tOwner ID\tPrice\n";
    afile << line;

    //	for(i = 0; ((i < n) && obj[i].flag == 0); i++)
    for (int i = 0; i < obj.size(); i++)
    {
        cout << obj[i].name_of_item << "\t\t" << obj[i].b_id << "\t\t" << obj[i].price << endl;
        afile << obj[i].name_of_item << "\t\t" << obj[i].b_id << "\t\t" << obj[i].price << endl;
    }

    cout << "\nDo you want to Display the complete file of the items sold?(1/0)\n";
    cin >> i;

    if (i == 1)
    {
        afile.seekg(0, ios ::beg);

        while (afile)
        {
            getline(afile, line);
            cout << line << endl;
        }
    }

    afile.close();
}

int main()
{
    int choice, no_of_items = 0;
    item temp;
    vector<item> obj;
    do
    {
        cout << "\nEnter Choice\n1. Add item to Auction\n2. To Display the list of items\n3. To Start the auction\n4. To Exit\n";

        cin >> choice;

        switch (choice)
        {
        case 1:
            temp = create();
            no_of_items++;
            obj.push_back(temp);
            cout << "\nItem added Successfully!\n";
            break;

        case 2:
            cout << "\nName of item\tName of Owner\tDescription\n";
            for (int i = 0; i < obj.size(); i++)
            {
                disp(obj[i]);
            }
            break;

        case 3:
            if (obj.empty())
                cout << "\nList is Empty\n";
            else
            {
                auction(obj);
            }
            break;

        default:
            cout << "\nInvalid Input\n";
            break;
        }
    } while (choice != 4);

    return 0;
}