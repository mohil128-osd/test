#include <bits/stdc++.h>
#include <conio.h>
using namespace std;
#define V 7
#define INF INT_MAX
vector<vector<int>> cost(7, vector<int>(7));
vector<vector<int>> path(7, vector<int>(7));
vector <int> truckV[20];
int costPrice,sellingPrice =0;
int dist[V][V];
vector <pair <string,int>> reqpaths;
void StringGenerator();
void printPaths();
void calctrucks();
void billingprice();
void printTruckRoutes();
class item
{
    public:
    int weight;
    char src;
    char dest;
    int price;
    item *next;
    int num;
};
item *Head=new item();
void floydWarshall()
{
    int graph[V][V] = { { 0  , 7  , INF, 3  , 2  , INF, INF},
                        { 7  , 0  , 5  , 9  , INF, 2  , INF},
                        { INF, 5  , 0  , INF, 5  , INF,  6 },
                        { 3  , 9  , INF, 0  , INF, INF,  1 },
                        { 2  , INF, 5  , INF, 0  , INF, INF},
                        { INF, 2  , INF, INF, INF, 0  , 3  },
                        { INF, INF, 6  , 1  , INF, 3  , 0  } };
    int i, j, k;

    for (i = 0; i < V; i++)
        for (j = 0; j < V; j++)
            dist[i][j] = graph[i][j];


    for (k = 0; k < V; k++) {

        for (i = 0; i < V; i++) {

            for (j = 0; j < V; j++) {

                if (dist[i][j] > (dist[i][k] + dist[k][j]) && (dist[k][j] != INF && dist[i][k] != INF))
                dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
}
void floydPath()
{
     vector<vector<int>> adjMatrix =
    {
        { 0  , 7  , INF, 3  , 2  , INF, INF},
                        { 7  , 0  , 5  , 9  , INF, 2  , INF},
                        { INF, 5  , 0  , INF, 5  , INF,  6 },
                        { 3  , 9  , INF, 0  , INF, INF,  1 },
                        { 2  , INF, 5  , INF, 0  , INF, INF},
                        { INF, 2  , INF, INF, INF, 0  , 3  },
                        { INF, INF, 6  , 1  , INF, 3  , 0  }
    };
    int n = adjMatrix.size();
    if (n == 0) {
        return;
    }
    for (int v = 0; v < n; v++)
    {
        for (int u = 0; u < n; u++)
        {
            cost[v][u] = adjMatrix[v][u];

            if (v == u) {
                path[v][u] = 0;
            }
            else if (cost[v][u] != INT_MAX) {
                path[v][u] = v;
            }
            else {
                path[v][u] = -1;
            }
        }
    }
    for (int k = 0; k < n; k++)
    {
        for (int v = 0; v < n; v++)
        {
            for (int u = 0; u < n; u++)
            {
                if (cost[v][k] != INT_MAX && cost[k][u] != INT_MAX
                    && cost[v][k] + cost[k][u] < cost[v][u])
                {
                    cost[v][u] = cost[v][k] + cost[k][u];
                    path[v][u] = path[k][u];
                }
            }
            if (cost[v][v] < 0)
            {
                cout << "Negative-weight cycle found!!";
                return;
            }
        }
    }
}
item *insertElements()
{
    system("cls");
    int n;
    cout<<"Enter number of parcels to load.\n";
    cin>>n;
    item *head=NULL;
    item *temp=NULL;
    item *p=NULL;
    for (int i = 0; i < n; i++)
    {
        temp=new item();
        temp->num=i;
        wta:
        cout<<"Enter the weight of parcel "<<i+1<<"\n";
        cin>>temp->weight;
        if(temp->weight>100)
        {
            cout<<"Sorry , item to heavy to be shipped. Enter a value under 100.\n";
            goto wta;
        }
        sta:
        cout<<"Enter the source of parcel "<<i+1<<"\n";
        cin>>temp->src;
        if(temp->src!='A' && temp->src!='B' && temp->src!='C' && temp->src!='D' && temp->src!='E' && temp->src!='F' && temp->src!='G')
        {
            cout<<"Sorry we don't serve at this city yet.\n";
            goto sta;
        }
        dta:
        cout<<"Enter the destination of parcel "<<i+1<<"\n";
        cin>>temp->dest;
        if(temp->dest!='A' && temp->dest!='B' && temp->dest!='C' && temp->dest!='D' && temp->dest!='E' && temp->dest!='F' && temp->dest!='G')
        {
            cout<<"Sorry we don't serve at this city yet.\n";
            goto dta;
        }
        temp->next=NULL;
        if(head==NULL)
        {
            head=temp;
        }
        else
        {
            p=head;
            while(p->next!=NULL)
            {
                p=p->next;
            }
                p->next=temp;
        }
    }
    cout<<"Insertion successful.\n";
   _sleep(1000);
    return head;
}
void deleteAt(item *head)
{
    system("cls");
    int ind;
    cout<<"\nWhere do you want to delete.\n";
    cin>>ind;
    item *p=head;
    item *temp=new item();
    for (int i = 1; i < ind-1; i++)
    {
        p=p->next;
    }
    temp=p->next;
    p->next=p->next->next;
    delete temp;
    cout<<"Deletion Successful.\n";
    _sleep(1000);
}
void displayParcels(item *head)
{
    system("cls");
    cout<<"Displaying list from start.\n";
    int c=0;
   while(head!=NULL){
       c++;
       cout<<"Parcel "<<c<<" weight : "<<head->weight<<"\n";
       cout<<"Parcel "<<c<<" source : "<<head->src<<"\n";
       cout<<"Parcel "<<c<<" destination : "<<head->dest<<"\n";
       //cout<<"Parcel "<<c<<" weight : "<<head->weight<<"\n";
       head=head->next;
       cout<<endl;
   }
   cout<<"Press any key to go back.\n";
   getch();
}
void ssort()
{
    for (int i=1 ;i<reqpaths.size(); i++)
    {
        string temp = reqpaths[i].first;
        int temp1=reqpaths[i].second;
        int j = i - 1;
        while (j >= 0 && temp.length() < reqpaths[j].first.length())
        {
            reqpaths[j+1].first = reqpaths[j].first;
            reqpaths[j+1].second = reqpaths[j].second;
            j--;
            reqpaths[j+1].first = temp;
            reqpaths[j+1].second = temp1;
        }

    }
}

void frontPage()
{
    system("cls");
    system("Color 3F");
    cout<<"\t\t\t\t\tWelcome to XPresso Client Page.\n";
    cout<<endl<<endl;
    cout<<"Select one option from below.\n\n";
    cout<<"1. Enter item \n";
    cout<<"2. Delete item.\n";
    cout<<"3. View items.\n";
    cout<<"4. Compute Billing Price.\n";
    cout<<"5. Compute Details.\n";
    cout<<"6. Exit.\n";
    int c;
    cin>>c;
    if(c==1)
    {
        Head=insertElements();
        StringGenerator();
    }
    if(c==2)
    deleteAt(Head);
    if(c==3)
    displayParcels(Head);
    if(c==4)
    billingprice();
    if(c==5)
    {
        printTruckRoutes();
        cout<<"Press any key to go back.\n";
        getch();
    }
    if(c==6)
    {
        cout<<"\n\n\nThank you for using Xpresso. Hope to serve you again later.\n\n\n";
         exit(0);
    }
    frontPage();
}
void StringGenerator()
{
    item *temp=Head;
    int it=1;
    while(temp!=NULL)
    {
        string s;
        int i=temp->src-65;
        int j=temp->dest-65;
        s+=temp->dest;
        while(path[i][j]!=i)
        {
            char d=(char)(path[i][j]+65);
            s=d+s;
            j=path[i][j];
        }
        s=temp->src+s;
        reqpaths.push_back(make_pair(s,temp->weight));
        temp=temp->next;
    }
    ssort();
    calctrucks();
    //printPaths();
}
void printPaths()
{
    for (int i = 0; i < reqpaths.size(); i++)
    {
        cout<<reqpaths[i].first<<" "<<reqpaths[i].second<<endl;
    }
    getche();
}
int itemChanger(char s,char d,int w)
{
    item *temp=Head;
    while(temp!=NULL)
    {
        if(temp->src==s && temp->dest==d && temp->weight==w)
        return temp->num;
        else
        temp=temp->next;
    }
    return -1;
}
int check_substring(string str1, string str2)
{   int i,j;
    int len1 = str1.length();
    int len2 = str2.length();

    for (i = 0; i <= len2 - len1; i++) {
        for (j = 0; j < len1; j++)
            if (str2[i + j] != str1[j])
                break;

        if (j == len1)
            return 1;
    }

    return 0;
}
void calctrucks()
{
    for (int i = 0; i < reqpaths.size(); i++)
    {
        string si=reqpaths[i].first;
        int inum=itemChanger(si[0],si[si.length()-1],reqpaths[i].second);
        truckV[i].push_back(inum);
    }
    for (int i = 0; i < reqpaths.size()-1; i++)
    {
        string si=reqpaths[i].first;
        for (int j = i+1; j < reqpaths.size(); j++)
        {
            string sj=reqpaths[j].first;
            if(check_substring(si,sj) && (reqpaths[i].second+reqpaths[j].second <= 100))
            {
                int inum=itemChanger(si[0],si[si.length()-1],reqpaths[i].second);
                //truckV[j].push_back(inum);
                for (int k = 0; k < truckV[i].size(); k++)
                {
                    truckV[j].push_back(truckV[i][k]);
                }
                //cout<<inum<<endl;
                reqpaths[j].second+=reqpaths[i].second;
                reqpaths[i].second=0;
                break;
            }
        }

    }
    getch();
}
void  billingprice()
{
    system("cls");
    cout<<"Item Bills for the following items.\n";
    item *temp=Head;
    int result=0;
    int it=1;
    while(temp!=NULL)
    {
        int i=temp->src-65;
        int j=temp->dest-65;
        int distance =dist[i][j];
        result=10+distance*5+(temp->weight)*4;
        sellingPrice+=result;
        cout<<"Selling Price of Item "<<it++<<" is "<<result<<endl;
        cout<<endl;
        temp=temp->next;
    }
    cout<<"Total Price = "<<sellingPrice<<endl;
    cout<<"\n\nPress any key to go back.\n";
    getche();
}
void printTruckRoutes()
{
    system("cls");
    int ctr=0;
    cout<<"Printing Now.\n";
    for (int i = 0; i<reqpaths.size(); i++)
    {
        if(reqpaths[i].second == 0)
        continue;


        string a=reqpaths[i].first;
        int in=a[0]-65;
        int jn=a[a.length()-1]-65;
        costPrice+=dist[in][jn]*10;
        cout<<"Truck "<<++ctr<<" to follow route "<<reqpaths[i].first<<" with "<<reqpaths[i].second<<" kg of parcel.\n";
        cout<<"Items in truck "<<ctr<<" : ";
        for (int j = 0; j < truckV[i].size(); j++)
        {
            cout<<truckV[i][j]+1;
            if(j!=truckV[i].size()-1)
            cout<<",";
        }
        cout<<"\n\n";
    }
    cout<<"Total number of trucks needed = "<<ctr<<"\n";
    cout<<"\nTotal Cost to company for shipping item = Rs."<<costPrice;
    cout<<"\nTotal Selling price obtained = Rs."<<sellingPrice;
    cout<<"\nProfit made = Rs."<<sellingPrice-costPrice;
    cout<<"\nProfit% = "<<((sellingPrice-costPrice)*100)/costPrice<<"%"<<endl;
}
int main()
{
    system("cls");
    floydWarshall();
    floydPath();
    frontPage();
}
