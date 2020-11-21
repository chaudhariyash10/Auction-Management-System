/*************
OOP PBL AUCTION
Grp Members:-
Name		     Gr		 Roll
Pranav Rodge	  21910464	233053
Pratham Solanki   21910112	233061
Chaitanya Uge	  21910718	233064
Yash Chaudhari	  21910388	233066
*************/

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

using namespace std;

class item
{
    public:
	    string name_of_item, name_of_owner, desc;
	    float price;
	    int b_id;

};

item create(item obji)
{
	cout<<"\nEnter the Name of the Item\n";
	getline(cin, obji.name_of_item);
	cout<<"\nEnter the Name of the Owner\n";
	getline(cin, obji.name_of_owner);
	cout<<"\nEnter Description of Item in less than 50 words\n";
	getline(cin, obji.desc);


	cout<<obji.name_of_item<<"\t"<<obji.name_of_owner<<"\t"<<obji.desc<<endl;
	return (obji);
}

void disp(item obji)
{
    cout<<obji.name_of_item<<"\t"<<obji.name_of_owner<<"\t"<<obji.desc<<endl;

}

void auction(item objs[], int n)
{
	char ch;
    int i, j, no;
    float price, pre = 0.0;
	string name[15];
	NO: cout<<"\nEnter the Number of Auctioneers(max 15)\n";
	cin>>no;

	if(no < 1 || no >15)
	{
		cout<<"\nInvalid Input\n";
		goto NO;
	}

	for(i = 1; i <= no; i++)
	{
	    cin.ignore();
		cout<<"\nEnter Name of Auctioneer number"<<i<<endl;
		getline(cin, name[(i - 1)]);
		cout<<"\nThe Auctioning ID of Auctioneer "<<name[(i - 1)]<<" is "<<i<<endl;
	}

	for(i = 0; i < n; i++)
	{
		cout<<"\nItem on sale is:\nName:\t"<<objs[i].name_of_item<<"\nDesc\t"<<objs[i].desc<<endl;
    	cout<<"\nBase Price: ?100.00\n";

    	do
    	{
        	Lab: cout<<"\nBidder Input Price as: Bidder_ID Price\n";
        	cin>>j>>price;

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
        	    cout<<"\nDoes anybody else wants to bid?(N/n to Exit)\n";
        	    cin>>ch;
        	}

    	}while((ch != 'n') || (ch != 'N'));

	}

	cout<<"\nAuction Complete!\nThe List of Items Sold and to whom at price are:\nName of Item\tOwner ID\nPrice\n";

	for(i = 0; i < n; i++)
	{
	    cout<<objs[i].name_of_item<<"\t"<<objs[i].b_id<<"\t"<<objs[i].price<<endl;
	}

}

int main()
{
	int n, i;
	item obj[10];

	L0: cout<<"\nCreate a list of items to auction\nEnter total number of items(max 10)\n";
	cin>>n;

	if(n < 1 || n > 10)
	{
		cout<<"\nInvalid Input\n";
		goto L0;
	}

	cin.ignore();

	for(i = 0; i < n; i++)
	{
	   obj[i]=create(obj[i]);
	}

	while(i != 5)
	{
		cout<<"\nEnter Choice\n1. To Create a list of items to auction\n2. To Insert items in the auction\n3. To Display the list of items\n4. To Start the auction\n5. To Exit\n";
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
				  obj[i]=create(obj[i]);

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

				for(int j = 0; j < i; j++)//(i + n) < 11; i++)
				{
					create(obj[(i + n - 1)]);
				}

				n += i;
				break;
			}

			case 3:
			{//Display
			    cout<<"\nName of item\tName of Owner\tDescription\n";

			    for(i = 0; i < n; i++)
			    {
			        disp(obj[i]);
			       // cout<<obj[i].name_of_item<<"\t"<<obj[i].name_of_owner<<"\t"<<obj[i].desc<<endl;
			    }

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
