#include<bits/stdc++.h>
using namespace std;r


void print(int cube[3][3][3]){
    for (int k = 0; k < 3; k++){
        for (int i = 0; i < 3; i++){
            for (int j = 0; j < 3; j++){
                cout<<cube[k][i][j]<<" ";
            }
            cout<<"\n";
        }
        cout<<"\n";
    }
}

void variationHeight(int cube [3][3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            swap(cube[0][i][j], cube[2][i][j]);
        }
    }
}

void variationColumn(int cube [3][3][3]){
    for(int k=0; k<3; k++){
        for(int j=0; j<3; j++){
            swap(cube[k][2][j], cube[k][0][j]);
        }
    }
}

void variationRow(int cube[3][3][3]){
    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            swap(cube[i][j][0], cube[i][j][2]);
        }
    }
}

void printCube(int cube[3][3][3]){

    srand(time(0));
    int random = rand() % 7;
    switch(random){
    case 0: {
            print(cube);
            break;
    }
    case 1:{
        variationHeight(cube);
        print(cube);
        break;
    }
    case 2:{
        variationRow(cube);
        print(cube);
        break;
    }
    case 3:{
        variationColumn(cube);
        print(cube);
        break;
    }
    case 4:{
        variationColumn(cube);
        variationRow(cube);
        print(cube);
        break;
    }
    case 5:{
        variationHeight(cube);
        variationRow(cube);
        print(cube);
        break;
    }
    case 6:{
        variationColumn(cube);
        variationHeight(cube);
        print(cube);
        break;
    }
    };
}





int main(){
    srand(time(0));
    int i = 1, j = 1, k = 0;
    int cube[3][3][3] = {};

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

    printCube(cube);
    return 0;
}