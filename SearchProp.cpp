#include<iostream>
#include<string.h>
#include<assert.h>
#include<conio.h>
#include<fstream>
using namespace std;
class BTreeNode
{
    string *filechu;
    string *keys;  // An array of keys
    int t;      // Minimum degree (defines the range for number of keys)
    BTreeNode **C; // An array of child pointers
    int n;     // Current number of keys
    int leaf; // Is true when node is leaf. Otherwise false
    //ifstream *cityfi;  // File pointer k liye


    public:
        BTreeNode(int _t, int leaf);
        void insertNonFull(string k,string);
        void splitChild(int i, BTreeNode *y,string);
        void traverse();
        string search1(string k);
        friend class BTree;

};
class BTree
{
    BTreeNode *root;
    int t;
    public:
        BTree(int _t)
        {
            root=NULL;
            t=_t;
        }
        void traverse()
        {
            if(root!=NULL)
                root->traverse();
        }
        string search1(string k)
        {

            return root->search1(k);

            //return(root==NULL)?NULL:root->search(k);
        }
        void insert1(string k,string city);
        //void fileinit(string r);

};
BTreeNode::BTreeNode(int t1, int leaf1)
{
    t=t1;
    leaf=leaf1;
    filechu=new string[2*t-1];
    keys=new string[2*t-1];
    C=new BTreeNode *[2*t];
    n=0;
}/*
void BTree::fileinit(string r,int i)
{
    cityfi[i].open(r.c_str());
}*/
void BTreeNode::traverse()
{
    int i;
    cout<<endl;
    for(i=0;i<n;i++)
    {
        if(leaf==0)
            C[i]->traverse();
        cout<<" "<<keys[i]<<" ";
    }
    //cout<<endl;
    if(leaf==0)
        C[i]->traverse();
    cout<<endl;
}
string BTreeNode::search1(string k)
{
    int i=0;
    while(i<n&&k.compare(keys[i])>0)
        i++;
    if(keys[i].compare(k)==0)
        return filechu[i];
    if(leaf==1)
        return NULL;
    return C[i]->search1(k);
}
void BTree::insert1(string k,string str2)
{
    if(root==NULL)
    {
        root=new BTreeNode(t,1);
        root->keys[0].assign(k);
      //  root->cityfi[0].open(str2.c_str());
        root->filechu[0].assign(str2);
        root->n=1;
    }
    else
    {
        if(root->n==2*t-1)
        {
            BTreeNode *s=new BTreeNode(t,0);
            s->C[0]=root;
            s->splitChild(0,root,str2);
            int i=0;
            if(s->keys[0].compare(k)<0)
                i++;
            s->C[i]->insertNonFull(k,str2);
            root=s;
        }
        else
            root->insertNonFull(k,str2);
    }
}
void BTreeNode::insertNonFull(string k,string cc)
{
    int i=n-1;
    if(leaf==1)
    {
        while(i>=0&&keys[i].compare(k)>0)
        {
            keys[i+1].assign(keys[i]);
            filechu[i+1].assign(filechu[i]);
        //    cityfi[i+1].open(filechu[i+1].c_str());
            i--;
        }
        keys[i+1].assign(k);
        filechu[i+1].assign(cc);
      //  cityfi[i+1].open(cc.c_str());
        n=n+1;
    }
    else
    {
        while(i>=0&&keys[i].compare(k)>0)
            i--;
        if(C[i+1]->n==2*t-1)
        {
            splitChild(i+1,C[i+1],cc);
            if(keys[i+1].compare(k)<0)
                i++;
        }
        C[i+1]->insertNonFull(k,cc);
    }
}
void BTreeNode::splitChild(int i, BTreeNode *y,string stt)
{
    BTreeNode *z=new BTreeNode(y->t,y->leaf);
    z->n=t-1;
    for(int j=0;j<t-1;j++)
    {
        z->keys[j].assign(y->keys[j+t]);
        z->filechu[j].assign(y->filechu[j+t]);
     //   z->cityfi[j].open(z->filechu[j].c_str());
    }
    if(y->leaf==0)
    {
        for(int j=0;j<t;j++)
            z->C[j]=y->C[j+t];
    }
    y->n=t-1;
    for(int k1=n;k1>=i+1;k1--)
        C[k1+1]=C[k1];
    C[i+1]=z;
    for(int l=n-1;l>=i;l--)
    {
        keys[l+1].assign(keys[l]);
        filechu[l+1].assign(filechu[l]);
       // cityfi[l+1].open(filechu[l+1].c_str());
    }
    keys[i].assign(y->keys[t-1]);
    filechu[i].assign(y->filechu[t-1]);
   // cityfi[i].open(filechu[i].c_str());
    n=n+1;
}
typedef struct residentinfo
{
    int age;
    string rname;
    string radd;
    string rcity;
}residentinfo;
class user
{
	public:

	string username;
	int age;
	string hometown;
	char gender;
	int status;
	int work;
	string wname;
	string wadd;
	string wcity;
	int numchild;
	string *school;
	int numvehicle;
	long salary;
	string citywanted;
	long budget;
	int numresidents;
	residentinfo *r;

	void userinput()
	{
		cout<<"USER INFORMATION:"<<endl;
		cout<<"Name:";
		cin>>username;
		cout<<endl;
		cout<<"Age:";
		cin>>age;
		cout<<endl<<"Gender:";
		cin>>gender;
		cout<<endl<<"Hometown:";
		cin>>hometown;
		cout<<endl<<"Marital Status:"<<"1. Single"<<endl<<"2. Married"<<endl;
		cin>>status;
		cout<<endl<<"WORKPLACE INFORMATION:"<<endl;
		cout<<"Name Of Organisation:";
		cin>>wname;
		cout<<endl<<"Address:";
        cin>>wadd;
		cout<<endl<<"City:";
		cin>>wcity;
		cout<<endl<<"Salary:";
		cin>>salary;
		cout<<endl<<"Number of vehicles:";
		cin>>numvehicle;
		if(status==2)
		{
			cout<<"CHILDREN INFORMATION:"<<endl;
			cout<<"Number of Children:";
			cin>>numchild;
			school=new string[numchild];
			cout<<endl<<"Enter school name of all:";
			for(int i=0;i<numchild;i++)
			{
				cout<<i+1<<".";
				cin>>school[i];
			}
		}
		cout<<"NEW RESIDENCE INFORMATION:"<<endl;
		cout<<"City(Moving In):";
		cin>>citywanted;
		cout<<endl<<"Budget of house required:";
		cin>>budget;
		cout<<endl<<"Number of residents:";
		cin>>numresidents;
		r=new residentinfo[numresidents];
		cout<<endl<<"RESIDENTS' INFORMATION(Except Children):"<<endl;
		for(int j=0;j<numresidents;j++)
		{
			cout<<j+1<<"."<<" ";
			cout<<"Age:";
			cin>>r->age;
			cout<<endl<<"Work Information:"<<endl;
			cout<<"Office Name:";
			cin>>r->rname;
			cout<<endl<<"Address:";
			cin>>r->radd;
			cout<<endl<<"City:";
			cin>>r->rcity;
		}
	}
	string getcitywanted()
	{
	    return citywanted;
	}
	long getbudget()
	{

	    return budget;
	}
	int getage(int k)
	{
	    return r[k].age;
	}
	string getradd(int k)
	{
	    return r[k].radd;
	}
};
struct Point
{
    unsigned k;
    int* coord; // Coordinate (A pointer to array of size k)
    int snum;
    string city,state;
    int locnum;
    int status;
    string type, cond;
    long price;
    string address;
    int buildnum;
};

// A structure to represent the Input
// n: Number of points in space
// pointArray: An array to keep information of each point
struct Input
{
    // n --> NUMBER OF POINTS
    unsigned n;
    Point* *pointArray;
    int num;
    int weight;
}globarr[30], obj23,globobj;

// A structure to represent node of 2 dimensional tree
struct Node
{
    Point point;
    Node *left, *right;
};

// Creates and return a Point structure
Point* CreatePoint(unsigned k)
{
    Point* point = new Point;

    // Memory allocation failure
    assert(NULL != point);

    point->k = k;
    point->coord = new int[k];

    // Memory allocation failure
    assert(NULL != point->coord);

    return point;
}
// Creates and returns an Input structure
struct Input CreateInput(unsigned k, unsigned n)
{
    //getch();
    struct Input input;
    input.num=0;
    input.weight=0;
    // Memory allocation failure
    //assert(NULL != input);
    input.n = n;
    input.pointArray = new Point*[n];
    // Memory allocation failure
    assert(NULL != input.pointArray);
    return input;
}
// A method to create a node of K D tree
struct Node* CreateNode(struct Point* point)
{
    //cout<<"sri sri"<<endl;
    struct Node* tempNode = new Node;

    // Memory allocation failure
    assert(NULL != tempNode);

    // Avoid shallow copy [We could have directly use
    // the below assignment, But didn't, why?]
    /*tempNode->point = point;*/
    (tempNode->point).k = point->k;
    (tempNode->point).coord = new int[point->k];
    // Copy coordinate values
    for (int i=0; i<(tempNode->point).k; ++i)
        (tempNode->point).coord[i] = point->coord[i];
    ((tempNode->point).city).assign(point->city);
    ((tempNode->point).state).assign(point->state);
    ((tempNode->point).locnum)=(point->locnum);
    ((tempNode->point).status)=(point->status);
    ((tempNode->point).type).assign(point->type);
    ((tempNode->point).cond).assign(point->cond);
    ((tempNode->point).price)=(point->price);
    ((tempNode->point).address).assign(point->address);
    ((tempNode->point).buildnum)=(point->buildnum);
    tempNode->left = tempNode->right = NULL;
    return tempNode;
}

// Root is passed as pointer to pointer so that
// The parameter depth is used to decide axis of comparison
void InsertKDTreeUtil(Node * * root, Node* newNode, unsigned depth)
{
 //   cout<<"areee"<<endl<<(*root)<<endl;
    // Tree is empty?
    if (!*root)
    {
        *root = newNode;
        return;
    }
   // cout<<"insertion wala point "<<(newNode->point).coord[0]<<","<<(newNode->point).coord[1]<<endl;
   // cout<<"root wala point "<<((*root)->point).coord[0]<<","<<((*root)->point).coord[1]<<endl;
   // getch();
    // Calculate axis of comparison to determine left/right
    unsigned axisOfComparison = depth % (newNode->point).k;
   // Node *rot;
    // Compare the new point with root and decide the left or
    // right subtree
    if ((newNode->point).coord[axisOfComparison] <
                    ((*root)->point).coord[axisOfComparison])
        InsertKDTreeUtil(&((*root)->left), newNode, depth + 1);
    else
        InsertKDTreeUtil(&((*root)->right), newNode, depth + 1);
   // return rot;
}

// Function to insert a new point in KD Tree. It mainly uses
// above recursive function "InsertKDTreeUtil()"
void InsertKDTree(Node* *root, Point* point)
{

    //Node* rot;
    Node* newNode = CreateNode(point);
    unsigned zeroDepth = 0;
    //cout<<(*root);
    //cout<<"ise kehte hai hip hop"<<endl;
    //getch();
    InsertKDTreeUtil(root, newNode, zeroDepth);
  //  cout<<"wierd"<<endl;
  //return rot;
}

// A utility method to determine if two Points are same
// in K Dimensional space
int ArePointsSame(Point firstPoint, Point secondPoint)
{
    if (firstPoint.k != secondPoint.k)
        return 0;

    // Compare individual coordinate values
    for (int i = 0; i < firstPoint.k; ++i)
        if (firstPoint.coord[i] != secondPoint.coord[i])
            return 0;

    return 1;
}

// Searches a Point in the K D tree. The parameter depth is used
// to determine current axis.
int SearchKDTreeUtil(Node* root, Point point, unsigned depth)
{
    if (!root)
        return 0;

    if (ArePointsSame(root->point, point))
        return 1;

    unsigned axisOfComparison = depth % point.k;

    if (point.coord[axisOfComparison] <
                      (root->point).coord[axisOfComparison])
        return SearchKDTreeUtil(root->left, point, depth + 1);

    return SearchKDTreeUtil(root->right, point, depth + 1);
}

// Searches a Point in the K D tree. It mainly uses
// SearchKDTreeUtil()
int SearchKDTree(Node* root, Point point)
{
    unsigned zeroDepth = 0;
    return SearchKDTreeUtil(root, point, zeroDepth);
}

// Creates a KD tree from given input points. It mainly
// uses InsertKDTree
Node* CreateKDTree(Input input)
{
    Node* root = NULL;
    //cout<<input.num<<endl;
    getch();
    for(int i=0;i<input.num;++i)
        {
      //      cout<<"hey"<<(root)<<endl;
            InsertKDTree(&root, input.pointArray[i]);
       //     cout<<(root)<<endl;
        //    getch();
        }
      //  cout<<"holaaa"<<endl;
    //getch();
    //cout<<root<<endl;
    return root;
}

// A utility function to print an array
void PrintArray(int x, int y)
{
    //cout<<"hey"<<endl;
    cout<<"("<<x<<","<<y<<")";
    cout << endl;
}
Input reset(Input var)
{
    var.num=0;
    var.weight=0;
}
Input inserttoinput(Input var,Point *p)
{
    cout<<endl<<endl<<endl<<"inserting to obj23 "<<"("<<p->coord[0]<<","<<p->coord[1]<<")"<<endl;
    var.num++;
    getch();
    Point *p1=CreatePoint(2);
    if(p1==NULL)
        cout<<"shit"<<endl;
   // getch();
     for(int i=0;i<2;i++)
        p1->coord[i]=p->coord[i];
    //cout<<"1"<<endl;
    //getch();
     p1->snum=p->snum;
    //  cout<<"1"<<endl;
    //getch();
    (p1->city).assign(p->city);
    // cout<<"1"<<endl;
    //getch();
    (p1->state).assign(p->state);
     //cout<<"1"<<endl;
    //getch();
    p1->locnum=p->locnum;
    // cout<<"1"<<endl;
    //getch();
    p1->status=p->status;
     //cout<<"1"<<endl;
    //getch();
    (p1->type).assign(p->type);
    // cout<<"1"<<endl;
    //getch();
    (p1->cond).assign(p->cond);
     //cout<<"1"<<endl;
    //getch();
    p1->price=p->price;
     //cout<<"1"<<endl;
    //getch();
    (p1->address).assign(p->address);
     //cout<<"1"<<endl;
    //getch();
    p1->buildnum=p->buildnum;
    // cout<<"1"<<endl;
    //getch();
    var.pointArray[var.num-1]=p1;
     //cout<<"1"<<endl;
    //getch();
   // cout<<endl<<endl<<endl<<"inserted to obj23 "<<"("<<p->coord[0]<<","<<p->coord[1]<<")"<<endl;
   //getch();
  //  cout<<endl<<endl<<"*********************value inserted*******************************"<<endl<<endl;
 //    cout<<"coord "<<"("<<(var.pointArray[var.num-1])->coord[0]<<","<<(var.pointArray[var.num-1])->coord[1]<<")"<<endl;
    return var;
}
void lookHouse(Point pt,long bud)
{
   /* cout<<"type "<<pt.type<<endl;
    cout<<"status "<<pt.status<<endl;
    cout<<"price"<<pt.price<<endl<<endl;
    */if(((pt.type).compare("house"))==0 && pt.status==1 && pt.price<(bud+90000))
    {
     //   cout<<"("<<pt.coord[0]<<","<<pt.coord[1]<<")"<<endl;
        obj23=inserttoinput(obj23,&pt);
      //  cout<<obj23.pointArray[obj23.num-1]->type<<endl;
       // cout<<obj23.num<<endl;
       // if(obj23.num!=1)
       //     cout<<obj23.pointArray[obj23.num-1]->type<<endl;
      //  cout<<"2"<<endl;
    }
}
void inorderKD(Node* root)
{
       // cout<<"ROOTNOT"<<endl;
    if (root!= NULL)
    {
      //  cout<<"in"<<endl;
        inorderKD(root->left);
        PrintArray((root->point).coord[0], (root->point).coord[1]);
        inorderKD(root->right);
    }
}
void chooseHouse(Node* root,long bud)
{
    if (root!=NULL)
    {
        //cout<<"choosing house :p "<<endl;
        chooseHouse(root->left,bud);
        lookHouse((root->point),bud);
        //cout<<"3"<<endl;
        chooseHouse(root->right,bud);
    }
}
void nearestNeighbour(Point *p,Node *root,int distance,int depth,int i)       //sending the root to the tree and the range of distance(not sqrt'ed) required
{//i for debugging
    if(root!=NULL)
    {
        unsigned axisOfComparison=depth%(root->point).k;
       // PrintArray((root->point).coord[0],(root->point).coord[1]);
       // cout<<"aOC "<<axisOfComparison<<endl;
  //  unsigned nonTarget=depth%(root->point).k;
  //getch();
        int dis,dis1;
        if (p->coord[axisOfComparison] < (root->point).coord[axisOfComparison])
        {
            nearestNeighbour(p,root->left, distance,depth + 1,i);
        }
        else
            nearestNeighbour(p,root->right, distance,depth + 1,i);
        dis=((p->coord[0]-(root->point).coord[0])*(p->coord[0]-(root->point).coord[0]))+
            ((p->coord[1]-(root->point).coord[1])*(p->coord[1]-(root->point).coord[1]));
        cout<<"dis"<<dis<<endl;
        if(dis<=distance)
        {
            globobj=inserttoinput(globobj,&(root->point));
        }
        dis1=(p->coord[axisOfComparison]-(root->point).coord[axisOfComparison])*(p->coord[axisOfComparison]-(root->point).coord[axisOfComparison]);
        cout<<"dis1 "<<dis1<<endl;
        if(dis1<=distance)
        {
            if (p->coord[axisOfComparison] > (root->point).coord[axisOfComparison])
                nearestNeighbour(p,root->left, distance,depth + 1,i);
            else
                nearestNeighbour(p,root->right, distance,depth + 1,i);
        }
    }
}
void ans()
{
    int i,j;
    int max=0;
    for(i=0;i<obj23.num;i++)
    {
            if((globarr[i].weight)>max)
            {
                j=i;
                max=globarr[i].weight;
            }

    }
    cout<<obj23.pointArray[j]->coord[0]<<","<<obj23.pointArray[j]->coord[0]<<endl;
    globarr[j].weight=0;
}
int main()
{
    BTree t(3);
    int i,num=0;
    string str1, str2,xy;
    string newcity;
    //str1: city name str2: filename
    ifstream ct;
    ct.open("cities.txt");
    while(!ct.eof())
    {
        ct>>str1;
        ct>>str2;
       // getch();
        t.insert1(str1,str2);
        num++;
    }
    cout << "Traversal of the constucted tree is ";
    t.traverse();
    string str;
//    str.assign(t.search1("abc"));
 //   cout<<endl<<endl<<str;
    user u;
	u.userinput();
	newcity=u.getcitywanted();
    xy.assign(t.search1(newcity));
    //cout<<xy<<endl;
    ifstream inf;
    inf.open(xy.c_str());
   //inf.open("c1.txt");
    //if(inf==NULL)
    //{
     //   cout<<"hello";
     //   return 0;
   // }
   // else
      //  cout<<"going"<<endl;
    // 2 Dimensional tree [For the sake of simplicity]
    unsigned k = 2;
    // Total number of Points is 60
    unsigned n = 60;
    Input input = CreateInput(k, n);
    // itc --> ITERATOR for coord
    // itp --> ITERATOR for POINTS
    //getch();
    int itp=0;
    while(!inf.eof())
    {
        input.pointArray[itp] = CreatePoint(k);
        inf>>input.pointArray[itp]->snum;
      //  cout<<input.pointArray[itp]->snum<<endl;
       // getch();
        inf>>input.pointArray[itp]->city;
       // cout<<input.pointArray[itp]->city<<endl;
        inf>>input.pointArray[itp]->state;
        inf>>input.pointArray[itp]->locnum;
        inf>>input.pointArray[itp]->type;
       // cout<<input.pointArray[itp]->type<<endl;
        inf>>input.pointArray[itp]->cond;
        inf>>input.pointArray[itp]->status;
       // cout<<input.pointArray[itp]->status<<endl;
        inf>>input.pointArray[itp]->price;
       //  cout<<input.pointArray[itp]->price<<endl;
        inf>>input.pointArray[itp]->address;
        inf>>input.pointArray[itp]->buildnum;
        inf>>input.pointArray[itp]->coord[0];
        inf>>input.pointArray[itp]->coord[1];
        itp++;
        input.num++;
    }
    //input.num=itp;
    //getch();
    //cout<<input.num;
    getch();
    //return 0;
    inf.close();
    getch();
    Node* root = CreateKDTree(input);
   // cout<<"WTF"<<endl;
    obj23=CreateInput(2,60);           //has houses that satisfy the budget
    long bud=u.getbudget();
    getch();
    chooseHouse(root,bud);
    getch();
   // for(i=0;i<30;i++)
    //{
        //globarr[i]=createInput(2,60);
    //}
    cout << "Inorder traversal of K-D Tree created is:\n";
    inorderKD(root);

   cout<<endl<<endl<<"**************************budget shorlisted vacant houses**********************"<<endl;
   //getch();
  // cout<<"num"<<obj23.num<<endl;
   for(i=0;i<obj23.num;i++)
   {
        PrintArray((obj23.pointArray[i])->coord[0],(obj23.pointArray[i])->coord[1]);
   }
    cout<<endl<<endl<<"*************************nearest neiighbours**********************"<<endl;
   for(i=0;i<obj23.num;i++)
   {
        cout<<endl<<endl<<"*******************nearest nei of ";
         PrintArray((obj23.pointArray[i])->coord[0],(obj23.pointArray[i])->coord[1]);
         cout<<"*********************"<<endl;
       globobj=reset(globobj);
        nearestNeighbour(obj23.pointArray[i],root,225,0,i);
        for(int j=0;j<globobj.num;j++)
        {
            PrintArray((globobj.pointArray[i])->coord[0],(globobj.pointArray[i])->coord[1]);
        }
        globarr[i]=globobj; //from where to obtain depth
   }
   int j;
    for(i=0;i<obj23.num;i++)
    {
        for(j=0;j<globarr[i].num;j++)
        {
            cout<<globarr[i].pointArray[j]->type<<endl;
            cout<<globarr[i].pointArray[j]->coord[0]<<endl;
            cout<<globarr[i].pointArray[j]->coord[1]<<endl;
        }
    }
   /* ****** giving weights to different locations based on different criterias****** */

    for(j=0;j<obj23.num;j++)
    {
        globarr[j].weight=0;
    }
    for(i=0;i<obj23.num;i++)
    {
        for(j=0;j<globarr[i].num;j++)
        {
            //to check shops which are not meant to be sold
            if(((globarr[i].pointArray[j]->type).compare("shop"))==1 && (globarr[i].pointArray[j]->status)==0)
                globarr[i].weight+=100;
            //to check shops which can be sold
            else
            if(((globarr[i].pointArray[j]->type).compare("shop"))==1 && (globarr[i].pointArray[j]->status)==1)
                globarr[i].weight+=80;
            //to check hospitals
            else
            if(((globarr[i].pointArray[j]->type).compare("hospital"))==1)
                globarr[i].weight+=95;
            //if he has no vehicles auto/ bus will be a priority
            else
            if(((globarr[i].pointArray[j]->type).compare("autostand"))==1 || ((globarr[i].pointArray[j]->type).compare("busstand"))==1)
                if(u.numvehicle==0)
                    globarr[i].weight+=85;
                else
                    globarr[i].weight+=70;
            //looking for workplace.. if single higher priority
            else
            if(((globarr[i].pointArray[j]->address).compare(u.wadd))==1)
                if(u.status==1)
                    globarr[i].weight+=90;
                else
                    globarr[i].weight+=80;
            //if hometown and moving town are not same trains will have a higher priority
            else
            if(((globarr[i].pointArray[j]->type).compare("railway"))==1)
                if(((u.hometown).compare(u.citywanted))==1)
                    globarr[i].weight+=30;
                else
                    globarr[i].weight+=60;
            //if kids then check everyone's school and give them a high priority
            else
            if(((globarr[i].pointArray[j]->type).compare("school"))==1)
                if(u.numchild==0)
                    globarr[i].weight+=0;
                else
                    for(int k=0;k<u.numchild;k++)
                        if((u.school[k]).compare((globarr[i].pointArray[j]->address)))
                            globarr[i].weight+=85;
            //if single then malls are given less weight
            else
            if(((globarr[i].pointArray[j]->type).compare("mall"))==1)
                if(u.status==1)
                    globarr[i].weight+=40;
                else
                    globarr[i].weight+=50;
            //if there are aged people then parks will be given a higher priority
            else
            if(((globarr[i].pointArray[j]->type).compare("park"))==1)
                if(u.numresidents!=0)
                    for(k=0;k<u.numresidents;k++)
                        if((u.getage(k))>60)
                            {
                                globarr[i].weight+=30;
                                break;
                            }


            // if there are other residents their workplace is also a priority
            else
            if(u.numresidents!=0)
                for(k=0;k<u.numresidents;k++)
                    if(((u.getradd(k)).compare(globarr[i].pointArray[j]->address))==1)
                        globarr[i].weight+=85;
                    else
                        globarr[i].weight+=0;


        }
    }
    cout<<"**********************************printing weights**********************************"<<endl;
    for(i=0;i<obj23.num;i++)
    {
            cout<<globarr[i].weight<<endl;
    }
    int max=0;
    /*now for every location in obj23.pointarray we have its weight in globarr[i], we sort them on the basis of these weights*/
    /* swapping: obj23's pointArray's pointers are swapped and then final printing is done for first five positions*/
    cout<<"*********************************best points for you*********************************"<<endl;
    for(i=0;i<3;i++)
    ans();
    return 0;
}

