#include<bits/stdc++.h>
using namespace std;

static int winningLinesH = 0, winningLinesC = 0, n=10;
vector<int> game(27, 0);
vector<int> humanlist;
vector<int> computerlist;
vector<int> corner{0, 2, 6, 8, 18, 20, 24, 26};
vector<int> edgeCenter{1, 3, 5, 7, 9, 11, 15, 17, 19, 21, 23, 25};
vector<int> rest{4,10,12,13,14,16,22,27};

// 0 means _ -> emptyCell
// 1 means X -> computerMove
// 2 means O -> userMove


// To store magic Cube Values in a vector
vector<int> cubeToVec(int (&cube)[3][3][3]){
    vector<int> v;

    for (int k = 0; k < 3; k++){
        // cout<<"Layer "<<i+1<<"\n\n";
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                v.push_back(cube[k][i][j]);
            }
        }
    }
    return v;
}


// creates a magic square
void createMagicCube(int (&cube)[3][3][3]){
    int i=3/2, j=3-2, k=0;

    for (int it = 1; it <= 27;it++){
        if( cube[k][i][j] == 0){
            //if calculated position is not filled
            cube[k][i][j] = it;
        }else{
            //if calculated position is filled
             i = (i + 1) % 3;
                j = (j + 1) % 3;
            cube[k][i][j] = it;
        }

        if(it%3==0){
            i = (i + 2)%3;
            k = (k + 1)%3;
        }else{
            k = (k + 2)%3;
        }
        j = (j + 2)%3;
    }
}

// printing TicTacToe Board
void printGame(){
    cout << "\033[2J\033[1;1H";
    cout << "\n" << "Computer: " << winningLinesC << "\t"
         << "User: " << winningLinesH;

    for (int i = 0; i < 27;i++){
        if(i%3==0)
            cout << endl;
        if(i%9==0)
            cout << "\nBoard: " << (i / 9)+1 << endl;

        if(game[i]==0)
            cout << " _ ";
        else if(game[i]==1)
            cout << " X ";
        else if(game[i]==2)
            cout << " O ";
    }

    cout << "\n";
}


// By line sum check - Collinearity
bool checkCollinear(int a, int b, int c){
    int z1 = a / 9;
    int z2 = b / 9;
    int z3 = c / 9;

    int y1 = (a % 9) / 3;
    int y2 = (b % 9) / 3;
    int y3 = (c % 9) / 3;

    int x1 = (a % 9) % 3;
    int x2 = (b % 9) % 3;
    int x3 = (c % 9) % 3;

    // PQ+QR=PR  checks for collinearity of three points in 3D
    double line1=sqrt(pow((x2-x1), 2)+pow((y2-y1), 2)+pow((z2-z1), 2));
    double line2=sqrt(pow((x3-x2), 2)+pow((y3-y2), 2)+pow((z3-z2), 2));
    double line=sqrt(pow((x3-x1), 2)+pow((y3-y1), 2)+pow((z3-z1), 2));


    return ((line==line1+line2) || (line1+line==line2) || (line+line2==line1));
}

int getIndex(vector<int> v, int K)
{
    auto it = find(v.begin(), v.end(), K);

    // If element was found
    if (it != v.end())
    {
        // calculating the index
        // of K
        int index = it - v.begin();
        return index;
    }
    else {
        // If the element is not
        // present in the vector
        return -1;;
    }
}

void computerMove(vector<int> chances)
{
    int val=0;
    int flag=0;

    //Below nested loop for computer to make a winning line
    for(int i=0;i<computerlist.size()-1;i++)
    {
        //flag=0;
        for(int j=i+1;j<computerlist.size();j++)
        {
            val=42-chances[computerlist[i]]-chances[computerlist[j]];

            //checking if the desired value is present in either of the lists of comp or human
            if(!(find(humanlist.begin(), humanlist.end(),getIndex(chances,val))!=humanlist.end()||find(computerlist.begin(),computerlist.end(),getIndex(chances,val))!=computerlist.end()))
            {
                if(checkCollinear(computerlist[i],computerlist[j],getIndex(chances,val))){
                    //cout<<"New line formed is(indexes)(from 0-26) :-  ("<<computerlist[i]<<", "<<computerlist[j]<<", "<<getIndex(chances,val)<<")"<<endl;
                    computerlist.push_back(getIndex(chances,val));
                    game[getIndex(chances,val)]=1;
                    winningLinesC++;
                    flag=1;
                    break;   //computer makes one winning line
                } 
            }
        }
        if(flag==1)
        break;
    }


    if(flag==0)
    {
        for(int i=0;i<humanlist.size()-1;i++)
        {
            for(int j=i+1;j<humanlist.size();j++)
            {
                val=42-chances[humanlist[i]]-chances[humanlist[j]];

                //checking if the desired value is present in either of the lists of comp or human
                if(!(find(humanlist.begin(), humanlist.end(),getIndex(chances,val))!=humanlist.end()||find(computerlist.begin(),computerlist.end(),getIndex(chances,val))!=computerlist.end()))
                {
                    if(checkCollinear(humanlist[i],humanlist[j],getIndex(chances,val))){
                        //cout<<"New line formed is(indexes)(from 0-26) :-  ("<<computerlist[i]<<", "<<computerlist[j]<<", "<<getIndex(chances,val)<<")"<<endl;
                        computerlist.push_back(getIndex(chances,val));
                        game[getIndex(chances,val)]=1;
                        flag=1;
                        break;//inserting the move in our list so that we can block the user from winning
                        //won't increment the winningLineC since we aren't forming a line but simply blocking
                    }
                }
            }
            if(flag==1)
            break;
        }
    }

    if(flag==0)
    {
        for(int i=0;i<corner.size();i++)
        {
            val=corner[i];
            if(!(find(humanlist.begin(), humanlist.end(),val)!=humanlist.end()||find(computerlist.begin(),computerlist.end(),val)!=computerlist.end()))
            {
                computerlist.push_back(val);
                game[val]=1;
                flag=1;
                break;
            }
        }
    }

    if(flag==0)
    {
        for(int i=0;i<edgeCenter.size();i++)
        {
            val=edgeCenter[i];
            if(!(find(humanlist.begin(), humanlist.end(),val)!=humanlist.end()||find(computerlist.begin(),computerlist.end(),val)!=computerlist.end()))
            {
                computerlist.push_back(val);
                game[val]=1;
                flag=1;
                break;
            }
        }
    }
    
    if(flag==0)
    {
        for(int i=0;i<rest.size();i++)
        {
            val=rest[i];
            if(!(find(humanlist.begin(), humanlist.end(),val)!=humanlist.end()||find(computerlist.begin(),computerlist.end(),val)!=computerlist.end()))
            {
                computerlist.push_back(val);
                game[val]=1;
                flag=1;
                break;
            }
        }
    }
    
}

void checkhumanline(vector<int> chances,int move)
{
    move=chances[move];
    int val=0;
    for(int i=0;i<humanlist.size()-2;i++)
    {
        for(int j=i+1;j<humanlist.size()-1;j++)
        {
            if(42-chances[humanlist[i]]-chances[humanlist[j]]-move==0)
            {
                if(checkCollinear(humanlist[i],humanlist[j],getIndex(chances,move)))
                {
                    cout<<humanlist[i]<<humanlist[j]<<getIndex(chances,move);
                    winningLinesH++;
                }
            }
        }
    }
}


int main(){

    int cube[3][3][3]={};
    createMagicCube(cube);
    vector<int> chances = cubeToVec(cube);

    int pos, k=0, i=0, j=0;

    //if computer plays first
    computerlist.push_back(13);
    game[13]=1;

    printGame();

    cout<<"\nEnter (k,i,j): ";
    cin>>k>>i>>j;
    while(k==1&&i==1&&j==1)
    {
        cout<<"\nAlready filled!";
        cout <<"\nEnter (k,i,j): ";
        cin>>k>>i>>j;
    }
    humanlist.push_back(9*k+i*3+j);
    game[9*k+i*3+j] = 2;

    if(9*k+i*3+j==corner[0]){
        computerlist.push_back(corner[1]);
        game[corner[1]]=1;
    }
    else {
        computerlist.push_back(corner[0]);
        game[corner[0]]=1;
    }

    
    for(int b=0; b<12 && winningLinesC!=n && winningLinesH!=n;b++)
    {
        printGame();

        cout<<"\nEnter K,I,J respectively: ";
        cin>>k>>i>>j;
        while(find( humanlist.begin(), humanlist.end(), 9*k+i*3+j ) != humanlist.end() || find(computerlist.begin(), computerlist.end(), 9*k+i*3+j) != computerlist.end())
        {
        cout<<"\nCell Already taken \nEnter K,I,J respectively: ";
        cin>>k>>i>>j;
        }
        humanlist.push_back(9*k+i*3+j);
        game[9*k+i*3+j] = 2;
        if(b>0)
        {
            checkhumanline(chances,9*k+i*3+j);
        }
        
        computerMove(chances);
    }
    printGame();

    

    if(winningLinesC==10)
    {
        cout<<endl<<endl<<endl<<"-------------------------------------COMPUTER WINS-----------------------------------------"<<endl;
    }
    else if(winningLinesH==10)
    {
        cout<<endl<<endl<<endl<<"-------------------------------------HUMAN WINS-----------------------------------------"<<endl;
    }
    else
    cout<<endl<<endl<<endl<<"-------------------------------------Draw-----------------------------------------"<<endl;

        return 0;
}