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
#include <string.h>
using namespace std;

class item
{
    public:
	    string name_of_item, name_of_owner, desc;
	    float price;
	    int b_id ,flag;

        item()
        {
            price = 0;
            b_id = 0;
            flag = 1;
        }

};

void disp(item obji)
{
	if(obji.flag == 1)
    {
		cout<<obji.name_of_item<<"\t\t"<<obji.name_of_owner<<"\t\t"<<obji.desc<<endl;
	}

}

item create(item obji)
{

    cin.ignore();
	cout<<"\nEnter the Name of the Item\n";
	getline(cin, obji.name_of_item);
	cout<<"\nEnter the Name of the Owner\n";
	getline(cin, obji.name_of_owner);
	cout<<"\nEnter Description of Item in less than 50 words\n";
	getline(cin, obji.desc);
	cout<<"\nName of item\tName of Owner\tDescription\n";
	obji.flag = 1;
	disp(obji);
	return (obji);
}

void auction(item objs[], int n)
{
    int i, j, no;
    float price, pre = 0.0;
	string name[15];
	string line = "\nSummary\n";
	fstream afile;
	afile.open("samp.txt", ios :: in | ios :: out | ios :: app);
	afile<<line;
	line = "\nThe List of Items Sold are:\n";

	NO: cout<<"\nEnter the Number of Auctioneers(max 15, min 2)\n";
	cin>>no;

	if(no < 2 || no >15)
	{
		cout<<"\nInvalid Input\n";
		goto NO;
	}

	cin.ignore();

	for(i = 1; i <= no; i++)
	{
		cout<<"\nEnter Name of Auctioneer number "<<i<<endl;
		getline(cin, name[(i - 1)]);
		cout<<"\nThe Auctioning ID of Auctioneer "<<name[(i - 1)]<<" is "<<i<<endl;
	}

	for(i = 0; i < n; i++)
	{
		SALE: cout<<"\nItem on sale is:\nName:\t"<<objs[i].name_of_item<<"\nDesc\t"<<objs[i].desc<<endl;
    	cout<<"\nBase Price: 100.00\n(Press 0 0 to Pass)";

        Lab: cout<<"\nBidder Input Price as: Bidder_ID Price\n";
        cin>>j>>price;

       if((j == 0) && (price == 0) && (objs[i].flag == 1))
        {
         //   objs[i].b_id = objs[i].price = j;
            i++;
            goto SALE;
        }

        if(((price < 100.00) || (price < pre)) || ((j < 1) || (j > no)))
        {
            cout<<"\nCannot Except Either ID or Price\n";
            goto Lab;
        }

        else
        {
            pre = price;
            objs[i].b_id = j;
            objs[i].price = pre;
            objs[i].flag = 0;
            clock_t start = clock();
            cout << "\nTimer: 5 sec\nPlease enter the input:\n";

            while ( ! _kbhit() ) //Check for keyboard hit
            {
                if (((clock () - start)/ CLOCKS_PER_SEC ) >= 5)
                {
                    cout << "\nTIMEOUT 5 sec . . .\n";

                    if(i < (n - 1))
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

    time_out: cout<<"\nAuction Complete!\nThe List of Items Sold and to whom at price are:\nName of Item\tOwner ID\tPrice\n";
    afile<<line;

//	for(i = 0; ((i < n) && objs[i].flag == 0); i++)
	for(int i =0;i<n;i++)
	{
	    cout<<objs[i].name_of_item<<"\t\t"<<objs[i].b_id<<"\t\t"<<objs[i].price<<endl;
	    afile<<objs[i].name_of_item<<"\t\t"<<objs[i].b_id<<"\t\t"<<objs[i].price<<endl;
	}

	cout<<"\nDo you want to Display the complete file of the items sold?(1/0)\n";
	cin>>i;

	if(i == 1)
    {
        afile.seekg(0, ios :: beg);

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
	int i;
	item obj[10];
    char k;
	L0: cout<<"\nCreate a list of items to auction\nEnter total number of items(max 10)\n";

    cin >> k;
    if(k < '0' || k > '9')
    {
       cout << "Invalid Input";
       goto L0;
    }

    int n = (int)k - 48;

	for(i = 0; i < n; i++)
	{
	   obj[i]=create(obj[i]);
	}
    i = 0;
	while(i != 5)
	{
		cout<<"\nEnter Choice\n1. To Create a new list of items for auction\n2. To Insert items in the auction\n3. To Display the list of items\n4. To Start the auction\n5. To Exit\n";
		cin>>i;

		switch(i)
		{
			case 1:
			{//Create
				L: cout<<"\nCreate a list of items to auction\nEnter total number of items(max 10)\n";
				cin>>n;

				if(n < 1 || n > 10)
				{
					cout<<"\nInvalid Input\n";
					goto L;
				}


				cin.ignore();

				for(i = 0; i < n; i++)
				{
				  obj[i] = create(obj[i]);
				}

				break;
			}

			case 2:
			{//insert
				if(n == 10)
				{
					cout<<"\nList is Full\n";
					break;
				}

				L1: cout<<"\nEnter total number of items to be inserted(max "<<(10 - n)<<")\n";
				cin>>i;

				if((i < 1) || ((i + n) > 10))
				{
					cout<<"\nInvalid Input\n";
					goto L1;
				}

				cin.ignore();

				for(int j = 0; j < i; j++)
				{
					obj[j + n] = create(obj[(j + n)]);
				}

				n += i;
				cout<<"\nItem(s) added Successfully!\n";
				break;
			}

			case 3:
			{//Display
			    cout<<"\nName of item\tName of Owner\tDescription\n";

			    for(i = 0; i < n; i++)
			    {
			        disp(obj[i]);
			    }

			    i = 0;
			    break;
			}

			case 4:
			{//auction
			    if(n == 0)
				{
					cout<<"\nList is Empty\n";
				}

    			else
    			{
    				auction(obj, n);
    			}

				break;
			}

			case 5:
			{//exit
				cout<<"\nExitting...\n";
				break;
			}
			default:
			{
				cout<<"\nInvalid Input\n";
				break;
			}

		}

	}

	return 0;
}