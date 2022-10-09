#include <bits/stdc++.h>
using namespace std;
//depth =4 search depth=5
int h =5;
int branches=0;
//number of tupels in the training set =4
double state[15];
double train_mobility[15];
double train_corners[15];
double train_c_occupied[15];
double train_x_unoccupied[15];
double train_c_uno[15];
double train_no_pieces[15];

void interpolate(double t,double *weight){

    //weight[5]
    //index 0: mobility
    //index 1: corners
    //index 2:c_occupied
    //index 3:x_unoccupied
    //index 4:c_uno
    for(int i=0;i<4;i++){
        double a = train_mobility[i];
        double b = train_corners[i];
        double c = train_c_occupied[i];
        double d = train_x_unoccupied[i];
        double e = train_c_uno[i];
        double f = train_no_pieces[i];

        for(int j=0;j<4;j++){
            if(j!=i){
                a *= (t-state[j])/(state[i]-state[j]);
                b *= (t-state[j])/(state[i]-state[j]);
                c *= (t-state[j])/(state[i]-state[j]);
                d *= (t-state[j])/(state[i]-state[j]);
                e *= (t-state[j])/(state[i]-state[j]);
                f *= (t-state[j])/(state[i]-state[j]);
            }
            
        }
        *(weight+0) += a;
        *(weight+1) += b;
        *(weight+2) += c;
        *(weight+3) += d;
        *(weight+4) += e;
        *(weight+5) += f;
    }

}
double evaluate(int b[64],int w[64],int e[64] ,int m[64],bool my){
    //b[64] positions of pieces of black
    //w[64] positions of pieces of white
    //e[64] postions of empty squares 
    //if(my) m[64] corresponds to black 
    //if(!my) m[64] corresponds to white
    int l=0;double bc,wc;
    //count of black coins and white coins
    bc=0;wc=0;
    for(int i=0;i<64;i++){
        if(e[i]==1)l++;
        if(b[i]==1)bc++;
        if(w[i]==1)wc++;
    }
    if(l==0){
        //case1 : all the squares are completely filled
        //player wins
        if(bc>wc){return 1000;}
        //opponent wins
        if(bc<wc){return -1000;}
        //draw
        //similar to the postion state which evaluates to 0  
        if(bc=wc){return 0;}
    }
    else{
        //weights estimation
        double weight[6]={0,0,0,0,0,0};
        interpolate(bc+wc,weight);
        //cout<<"for this index after making the move total number of pieces are : "<<(bc+wc)<<endl;

        if(my){
            //feauture estimation
            double mobility =0;
            double corners=0;
            double c_occupied=0;
            double c_uno=0;
            double x_unoccupied=0;
            double pieces = (bc-wc);
            for(int i=0;i<64;i++){
                if(m[i]!=0){mobility++;}
            } 
            if(b[0]==1){
                corners++;
                if(e[1]==1){c_occupied++;}
                if(e[8]==1){c_occupied++;}
            }
            else{
                if(e[1]==1){c_uno++;}
                if(e[8]==1){c_uno++;}
                if(e[9]==1){x_unoccupied++;}
            }
            if(b[7]==1){
                corners++;
                if(e[6]==1){c_occupied++;}
                if(e[15]==9){c_occupied++;}
            }
            else{
                if(e[6]==1){c_uno++;}
                if(e[15]==9){c_uno++;}
                if(e[14]==1){x_unoccupied++;}
            }if(b[56]==1){
                corners++;
                if(e[48]==1){c_occupied++;}
                if(e[57]==1){c_occupied++;}
            }
            else{
                if(e[48]==1){c_uno++;}
                if(e[57]==1){c_uno++;}
                if(e[49]==1){x_unoccupied++;}
            }if(b[62]==1){
                corners++;
                if(e[55]==1){c_occupied++;}
                if(e[62]==9){c_occupied++;}
            }
            else{
                if(e[55]==1){c_uno++;}
                if(e[62]==1){c_uno++;}
                if(e[54]==1){x_unoccupied++;}
            }
            //individual weight calculation

            corners      *= weight[1];
            c_occupied   *= weight[2];
            c_uno        *= weight[4];
            x_unoccupied *= weight[3];
            mobility     *= weight[0];
            pieces       *= weight[5];
            double score;
            score = (pieces+corners+mobility+c_occupied - x_unoccupied- c_uno);
            return score;

        }
        if(!my){
            double mobility =0;
            double corners=0;
            double c_occupied=0;
            double c_uno=0;
            double x_unoccupied=0;
            double pieces =0;
            pieces = (wc-bc);
            for(int i=0;i<64;i++){
                if(m[i]!=0){mobility++;}
            } 
            if(w[0]==1){
                corners++;
                if(e[1]==1){c_occupied++;}
                if(e[8]==1){c_occupied++;}
            }
            else{
                if(e[1]==1){c_uno++;}
                if(e[8]==1){c_uno++;}
                if(e[9]==1){x_unoccupied++;}
            }
            if(w[7]==1){
                corners++;
                if(e[6]==1){c_occupied++;}
                if(e[15]==9){c_occupied++;}
            }
            else{
                if(e[6]==1){c_uno++;}
                if(e[15]==9){c_uno++;}
                if(e[14]==1){x_unoccupied++;}
            }if(w[56]==1){
                corners++;
                if(e[48]==1){c_occupied++;}
                if(e[57]==1){c_occupied++;}
            }
            else{
                if(e[48]==1){c_uno++;}
                if(e[57]==1){c_uno++;}
                if(e[49]==1){x_unoccupied++;}
            }if(w[62]==1){
                corners++;
                if(e[55]==1){c_occupied++;}
                if(e[62]==9){c_occupied++;}
            }
            else{
                if(e[55]==1){c_uno++;}
                if(e[62]==1){c_uno++;}
                if(e[54]==1){x_unoccupied++;}
            }
            corners      *= weight[1];
            c_occupied   *= weight[2];
            c_uno        *= weight[4] ;
            x_unoccupied *= weight[3] ;
            mobility     *= weight[0];
            pieces       *= weight[5];
            double score;
            score = (-pieces + x_unoccupied + c_uno-corners - mobility - c_occupied );
            return score;

        }
    }
}

void pm(int b[64] , int w[64] ,int e[64],int *m){
    int n=0,k=0;
//rows 
while(n<8){
    int i=8*n;
    while(i<8*(n+1)){
        if(b[i]==1&&i<8*n+6){
            while(b[i]==b[i+1] && i+1<8*n+6){
                i++;
            }
            if(b[i]==w[i+1]){
                int j=i+1;
                while(w[j]==w[j+1] && j+1<8*n+7){
                    j++;
                }
                if(w[j]==e[j+1]){
                    *(m+j+1)=2;k++;
                }
            }
        }
        if(e[i]==1 && i<8*n+6){
            while(e[i]==e[i+1] && i+1<8*n+6){
                i++;
            }
            if(e[i]==w[i+1]){
                int j= i+1;
                while(w[j]==w[j+1] && j+1<8*n+7){
                    j++;}

                if(w[j]==b[j+1]){
                    *(m+i)=2;k++;
                }
            }

        }
        i++;
    }
    n++;
}

//coloumn
n=0;
while(n<8){
    int i=0;
    while(i<8){
        if(b[8*i+n]==1 && i<6){
            while(b[8*i+n]==b[8*(i+1)+n] && i+1<6){
                i++;
            }
            if(b[8*i+n]==w[8*(i+1)+n]){
                int j =i+1;
                while(w[8*j+n]==w[8*(j+1)+n] && j+1<7){
                    j++;
                }
                if(w[8*j+n]==e[8*(j+1)+n]){
                    if(*(m+8*(j+1)+n)==0)
                    {*(m+8*(j+1)+n)=3;k++;}
                    else{
                        *(m+8*(j+1)+n)=(*(m+8*(j+1)+n))*3;
                    }
                    k++;
                }
            }
        }
        if(e[8*i+n]==1 && i<6){
            while(e[8*i+n]==e[8*(i+1)+n] && i+1<6){
                i++;
            }
            if(e[8*i+n]==w[8*(i+1)+n]){
                int j =i+1;
                while(w[8*j+n]==w[8*(j+1)+n] && j+1<7){
                    j++;
                }
                if(w[8*j+n]==b[8*(j+1)+n]){
                    if(*(m+8*(i)+n)==0){
                        *(m+8*(i)+n)=3;k++;
                    }
                    else{
                        *(m+8*(i)+n)=(*(m+8*(i)+n))*3;

                    }
                }
            }
        }
        i++;
    }
    n++;
}
//left to right diagonal
int u=0;n=0;
while(u<6){
    int i=0;
    while(u+i<8){
        if(b[8*u+9*i]==1 && u+i<6){
            while(u+i+1<6 && b[8*u+9*i] == b[8*(u+i+1)+i+1]){
                i++;
            }
            if(b[8*u+9*i]==w[8*(u+i+1)+i+1]){
                int j=i+1;
                while(w[8*u+9*j]==w[8*(u+j+1)+j+1] && u+j+1<7){
                    j++;
                }
                if(w[8*u+9*j]==e[8*(u+i+1)+i+1]){
                    if(*(m+8*(u+j+1)+j+1)==0){
                        *(m+8*(u+j+1)+j+1)=5;k++;
                    }
                    else{
                        *(m+8*(u+j+1)+j+1)=(*(m+8*(u+j+1)+j+1))*5;
                    }
                }
            }
        }
        if(e[8*u+9*i]==1 && u+i<6){
            while(e[8*u+9*i]==e[8*(u+i+1)+i+1] && u+i+1<6){
                i++;
            }
            if(e[8*u+9*i]==w[8*(u+i+1)+i+1]){
                int j =i+1;
                while(w[8*u+9*j]==w[8*(u+j+1)+j+1] && u+j+1<7){
                    j++;
                }
                if(w[8*u+9*j]==b[8*(u+j+1)+j+1]){
                    if(*(m+8*u+9*i)==0){
                        *(m+8*u+9*i)=5;k++;
                    }
                    else{
                        *(m+8*u+9*i)=(*(m+8*u+9*i))*5;
                    }
                    
                }
            }
        }
        i++;
    }
    u++;
}
u=0;n=1;
while(n<6){
    int i=0;
    while(n+i<8){
        if(b[8*i+n+i]==1 && n+i<6){
            while(b[8*i+n+i]==b[8*(i+1)+n+i+1] && n+i+1<6){
                i++;
            }
            if(b[8*i+n+i]==w[8*(i+1)+n+i+1]){
                int j =i+1;
                while(w[8*j+n+j]==w[8*(j+1)+n+j+1] && n+j+1<7){
                    j++;
                }
                if(w[8*j+n+j]==e[8*(j+1)+n+j+1]){
                    if(*(m+8*(j+1)+n+j+1)==0){
                        *(m+8*(j+1)+n+j+1)=5;k++;
                    }
                    else{
                        *(m+8*(j+1)+n+j+1)=(*(m+8*(j+1)+n+j+1))*5;
                    }
                }
            }
        }
        if(e[8*i+n+i]==1 && n+i<6){
            while(e[8*i+n+i]==e[8*(i+1)+n+i+1] && n+i+1<6){
                i++;
            }
            if(e[8*i+n+i]==w[8*(i+1)+n+i+1]){
                int j =i+1;
                while(w[8*j+n+j]==w[8*(j+1)+n+j+1] && n+j+1<7){
                    j++;
                }
                if(w[8*j+n+j]==b[8*(j+1)+n+j+1]){
                    if(*(m+8*i+n+i)==0){
                        *(m+8*i+n+i)=5;k++;
                    }
                    else{
                        *(m+8*i+n+i)=(*(m+8*i+n+i))*5;
                    }
                }
            }
        }
        i++;
    }
    n++;
}
//right to left diagnal
u=2;n=0;
while(u<8){
    int i=0;
    while(u-i>-1){
        if(b[8*(u-i)+i]==1 && u-i>1){
            while(b[8*(u-i)+i]==b[8*(u-i-1)+i+1] && u-i-1>1){
                i++;
            }
            if(b[8*(u-i)+i]== w[8*(u-i-1)+i+1]){
                int j=i+1;
                while(w[8*(u-j)+j]==w[8*(u-j-1)+j+1] && u-j-1>0){
                    j++;
                }
                if(w[8*(u-j)+j]==e[8*(u-j-1)+j+1]){
                    if(*(m+8*(u-j-1)+j+1)==0){
                        *(m+8*(u-j-1)+j+1)=7;k++;
                    }
                    else{
                        *(m+8*(u-j-1)+j+1)=(*(m+8*(u-j-1)+j+1))*7;
                    }
                }
            }
        }
        if(e[8*(u-i)+i]==1 && u-i>1){
            while(e[8*(u-i)+i]==e[8*(u-i-1)+i+1] && u-i-1>1){
                i++;
            }
            if(e[8*(u-i)+i]== w[8*(u-i-1)+i+1]){
                int j=i+1;
                while(w[8*(u-j)+j]==w[8*(u-j-1)+j+1] && u-j-1>0){
                    j++;
                }
                if(w[8*(u-j)+j]==b[8*(u-j-1)+j+1]){
                    if(*(m+8*(u-i)+i)==0){
                        *(m+8*(u-i)+i)=7;k++;
                    }
                    else{
                        *(m+8*(u-i)+i)=(*(m+8*(u-i)+i))*7;
                    }
                }
            }
        }
        i++;
    }
    u++;
}
u=7;n=1;
while(n<6){
    int i=0;
    while(n+i<8){
        if(b[8*(u-i)+n+i]==1 && n+i<6){
            while(b[8*(u-i)+n+i] == b[8*(u-i-1)+n+i+1] && n+i+1<6){
                i++;
            }
            if(b[8*(u-i)+n+i]==w[8*(u-i-1)+n+i+1]){
                int j= i+1;
                while(w[8*(u-j)+n+j]==w[8*(u-j-1)+n+j+1] && n+j+1<7){
                    j++;
                }
                if(w[8*(u-j)+n+j]==e[8*(u-j-1)+n+j+1]){
                    if(*(m+8*(u-j-1)+n+j+1)==0){
                        *(m+8*(u-j-1)+n+j+1)=7;k++;
                    }
                    else{
                        *(m+8*(u-j-1)+n+j+1)=(*(m+8*(u-j-1)+n+j+1))*7;
                    }
                }
            }
        }
        if(e[8*(u-i)+n+i]==1 && n+i<6){
            while(e[8*(u-i)+n+i] == e[8*(u-i-1)+n+i+1] && n+i+1<6){
                i++;
            }
            if(e[8*(u-i)+n+i]==w[8*(u-i-1)+n+i+1]){
                int j= i+1;
                while(w[8*(u-j)+n+j]==w[8*(u-j-1)+n+j+1] && n+j+1<7){
                    j++;
                }
                if(w[8*(u-j)+n+j]==b[8*(u-j-1)+n+j+1]){
                    if(*(m+8*(u-i)+n+i)==0){
                        *(m+8*(u-i)+n+i)=7;k++;
                    }
                    else{
                        *(m+8*(u-i)+n+i)=(*(m+8*(u-i)+n+i))*7;
                    }
                }
            }
        }
        i++;
    }
    n++;
}

}
double check_winning(int b[64] , int w[64] ,int new_m[64]){

    int count=0;int black_coins=0;int white_coins=0;
    for(int i=0;i<64;i++){
        if(new_m[i]!=0){
            count++;break;
        }
        else{
            if(b[i]==1)black_coins++;
            if(w[i]==1)white_coins++;
        }
    }
    if(count==0){
        if(black_coins > white_coins)return 1000;
        if(white_coins > black_coins)return -1000;
        return 0;
    }
    else if(count !=0){
        return 10;
    }

}
void make_move(int *b,int *w, int*e,int m[8],int k){
    //row
    if(m[k]%2==0){
        if(*(w+k+1)==1 && k%8<6){
            int i =1;
            while(*(w+k+i)==1 && (k+i)%8<7){
                i++;
            }
            if(*(b+k+i)==1){
                for(int j=1;j<i;j++){
                    *(w+k+j)=0;
                    *(b+k+j)=1;
                }
            }
        }
        if(*(w+k-1)==1 && k%8>1){
            int i=1;
            while(*(w+k-i)==1 && (k-i)%8>0){
                i++;
            }
            if(*(b+k-i)==1){
                for(int j=1;j<i;j++){
                    *(w+k-j)=0;
                    *(b+k-j)=1;
                }
            }
        }
        *(b+k)=1;
        *(e+k)=0;
    }
    //column
    if(m[k]%3==0){
        int r= k%8;
        int q= k/8;
        if(*(w+k+8)==1 && q<6){
            int i =1;
            while(*(w+k+8*i)==1 && (q+i)<7){
                i++;
            }
            if(*(b+k+8*i)==1){
                for(int j=1;j<i;j++){
                    *(w+k+8*j)=0;
                    *(b+k+8*j)=1;
                }
            }
        }
        if(*(w+k-8)==1 && q>1){
            int i=1;
            while(*(w+k-8*i)==1 && (q-i)>0){
                i++;
            }
            if(*(b+k-8*i)==1){
                for(int j=1;j<i;j++){
                    *(w+k-8*j)=0;
                    *(b+k-8*j)=1;
                }
            }
        }
        *(b+k)=1;
        *(e+k)=0;
    }
    //left to right diagonal
    if(m[k]%5==0){
        int r = k/8;
        int c= k%8;
        if(r<=c){
            if(*(w+k+9)==1 && c<6){
                int i =1;
                while(*(w+k+9*i)==1 && (c+i)<7){
                    i++;
                }
                if(*(b+k+9*i)==1){
                    for(int j=1;j<i;j++){
                        *(w+k+9*j)=0;
                        *(b+k+9*j)=1;
                    }
                }
            }
            if(*(w+k-9*1)==1 && c>1){
                int i=1;
                while(*(w+k-9*i)==1 && (c-i)>0){
                    i++;
                }
                if(*(b+k-9*i)==1){
                    for(int j=1;j<i;j++){
                        *(w+k-9*j)=0;
                        *(b+k-9*j)=1;
                    }
                }
            }           

        }
        if(r>c){
            if(*(w+k+9)==1 && r<6){
                int i =1;
                while(*(w+k+9*i)==1 && (r+i)<7){
                    i++;
                }
                if(*(b+k+9*i)==1){
                    for(int j=1;j<i;j++){
                        *(w+k+9*j)=0;
                        *(b+k+9*j)=1;
                    }
                }
            }
            if(*(w+k-9)==1 && r>1){
                int i=1;
                while(*(w+k-9*i)==1 && (r-i)>0){
                    i++;
                }
                if(*(b+k-9*i)==1){
                    for(int j=1;j<i;j++){
                        *(w+k-9*j)=0;
                        *(b+k-9*j)=1;
                    }
                }
            }           
        }
        *(b+k)=1;
        *(e+k)=0;
    }
    //right to left diagonal
    if(m[k]%7==0){
        int r=k/8;
        int c=k%8;
        if(r+c<=7){
            if(*(w+k+7)==1 && c>1){
                int i=1;
                while(*(w+k+7*i)==1 && c-i>0){
                    i++;
                }
                if(*(b+k+7*i)==1){
                    for(int j=1;j<i;j++){
                        *(b+k+7*j)=1;
                        *(w+k+7*j)=0;
                    }
                }
            }
            if(*(w+k-7)==1 && r>1){
                int i=1;
                while(*(w+k-7*i)==1 && r-i>0){
                    i++;
                }
                if(*(b+k-7*i)==1){
                    for(int j=1;j<i;j++){
                        *(b+k-7*j)=1;
                        *(w+k-7*j)=0;
                    }
                }
            }

        }
        if(r+c>7){
            if(*(w+k+7)==1 && r<6){
                int i=1;
                while(*(w+k+7*i)==1 && r+i<7){
                    i++;
                }
                if(*(b+k+7*i)==1){
                    for(int j=1;j<i;j++){
                        *(b+k+7*j)=1;
                        *(w+k+7*j)=0;
                    }

                }
            }
            if(*(w+k-7)==1 && c<6){
                int i=1;
                while(*(w+k-7*i)==1 && c+i<7){
                    i++;
                }
                if(*(b+k+7*i)==1){
                    for(int j=1;j<i;j++){
                        *(b+k-7*i)=1;
                        *(w+k-7*i)=0;
                    }
                }
            }
        }
        *(b+k)=1;
        *(e+k)=0;
    }
}


double minmax(int b[64],int w[64],int m[64],int e[64],int depth,bool my,int black_skips,int white_skips){
    //based on my :static evaluation function evaluates the board if my then black ,vice versa
    double score = evaluate(b,w,e,m,my);
    if(depth==h){branches++;}
    if(score==1000 ||score==-1000||score == 0)
        return score;

    //to see if there is a possible move for the cuurent player
    int count=0;
    for(int i=0;i<64;i++){
        if(m[i]!=0){
            count++;
            break;
        }
    }
        if(depth==h){
            if(count==0){
                int new_m[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
                if(my){
                    black_skips++;
                    pm(w,b,e,new_m);
                }
                if(!my){
                    white_skips++;
                    pm(b,w,e,new_m);
                }
                //if there is no move left even for the opponent(in the current game state):game over
                double win ;
                win = check_winning(b,w,new_m);
                if(win!=10){
                    cout<<"depth : "<<(depth+1)<<endl;
                    cout<<"true returned "<<win<<endl;
                    return win;
                }
            }

        score += ( white_skips - black_skips )*20;
        return score;
    }
    //if there is no possible move current player's turn will be skipped with depth remaining the same
    if(count==0){
        int new_m[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
        if(my){
            black_skips++;
            pm(w,b,e,new_m);
        }
        if(!my){
            white_skips++;
            pm(b,w,e,new_m);
        }
        //if there is no move left even for the opponent(in the current game state):game over
        double win ;
        win = check_winning(b,w,new_m);
        if(win!=10){
            branches++;
            cout<<"depth : "<<(depth+1)<<endl;
            cout<<"true returned "<<win<<endl;
            return win;
        }
        //if there is a move left for the opponent
        else if(win==10){
            double best;
            best = minmax(b,w,new_m,e,depth,!my,black_skips,white_skips);
            return best;
        }
    }

    //my move
    if(my){
        double best = -1001;
        for(int i=0;i<64;i++){
            if(m[i]!=0){
                //make move
                int dummy_b[64];
                int dummy_w[64];
                int dummy_e[64];
                int new_m[64];
                for(int j=0;j<64;j++){
                    dummy_e[j]=e[j];
                    dummy_w[j]=w[j];
                    dummy_b[j]=b[j];
                    new_m[j]=0;
                }
                //argument given to b will be considerd as the player and that given to w as the opponent
                make_move(b,w,e,m,i);
                //possible moves for new board stored in new_m 
                //moves for white evaluated w assigned to the player
                pm(w,b,e,new_m);
                //minmax
                best=max(best,minmax(b,w,new_m,e,depth+1,!my,black_skips,white_skips));
                //undo the move
                for(int j=0;j<64;j++){
                    e[j]=dummy_e[j];
                    b[j]=dummy_b[j];
                    w[j]=dummy_w[j];
                }
                

            }
        }
        return best;
    }
    //whites move
    if(!my){
        double best = 1001;
        for(int i=0;i<64;i++){
            if(m[i]!=0){
                //make move
                int dummy_b[64];
                int dummy_w[64];
                int dummy_e[64];
                int new_m[64];
                for(int j=0;j<64;j++){
                    dummy_e[j]=e[j];
                    dummy_w[j]=w[j];
                    dummy_b[j]=b[j];
                    new_m[j]=0;
                }
                //white is the player
                make_move(w,b,e,m,i);
                //possible moves for black as white has made a move
                //possible moves for black stored in new_m
                pm(b,w,e,new_m);
                //minmax
                best = min(best,minmax(b,w,new_m,e,depth+1,!my,black_skips,white_skips));
                //undo the move
                for(int j=0;j<64;j++){
                    e[j]=dummy_e[j];
                    w[j]=dummy_w[j];
                    b[j]=dummy_b[j];
                }
                
            }
        }
        return best;

    }
}

//best move for the player
int best_move(int b[64],int w[64],int e[64],int m[64]){
    int move_count =0;
    for(int i=0;i<64;i++){
        if(m[i]!=0){
            move_count++;
            break;
        }
    }
    //skip_move
    if(move_count==0){
        int new_m[64];
        for(int i=0;i<64;i++){
            new_m[i]=0;
        }
        pm(w,b,e,new_m);
        double win = check_winning(b,w,new_m);
        cout<<win<<endl;
        if(win!=10){
            cout<<"game over"<<endl;
            if(win==1000)cout<<"black won"<<endl;
            if(win==-1000)cout<<"white won"<<endl;
            if(win==0)cout<<"draw"<<endl;
            return win;
        }
        //else we will compute whites best move and the corresponding best move for black
        else if(win==10){
            double best_value =1001;
            int index =0;
            //index corresponding to best move
            for(int i=0;i<64;i++){
                if(new_m[i]!=0){
                    //make move
                    int dummy_b[64];
                    int dummy_e[64];
                    int dummy_w[64];
                    int new_b_m[64];
                    for(int j=0;j<64;j++){
                        dummy_e[j]=e[j];
                        dummy_w[j]=w[j];
                        dummy_b[j]=b[j];
                        new_b_m[j]=0;
                    }
                    //make the move cooresponding to new_m[i]
                    make_move(w,b,e,new_m,i);
                    for(int j=0;j<64;j++){cout<<w[j];
                    }
                    cout<<endl;
                    //for each move need to compute the possible moves for black
                    pm(b,w,e,new_b_m);
                    double move_value = minmax(b,w,new_b_m,e,0,true,0,0);
                    cout<<endl;
                    cout<<"hello"<<endl;
                    //undo the move
                    for(int j=0;j<64;j++){
                        w[j]=dummy_w[j];
                        e[j]=dummy_e[j];
                        b[j]=dummy_b[j];
                    }
                    if(move_value < best_value){
                        best_value = move_value;
                        index = i;
                    }

                }
        
            } 
            cout<<" whites best moves index : "<< index <<"  move value : "<<best_value<<endl;
            //coresspondingly, optimal move for black
            cout<<"correspondingly,optimal move for black :"<<endl;
            //make the move :white new_m[i]
            make_move(w,b,e,new_m,index);
            int new_b_m[64];
            for(int i=0;i<64;i++){
                new_b_m[i]=0;
            }
            pm(b,w,e,new_b_m);
            int b_index = best_move(b,w,e,new_b_m);
            return b_index;
        }
    }
//if the player has moves
    else if(move_count !=0){
        double best_value = -1001;
        //index corresponding to best move among the possible ones
        int index=0;
        for(int i=0;i<64;i++){
            if(m[i]!=0){
                //make move
                int dummy_b[64];
                int dummy_w[64];
                int dummy_e[64];
                int new_m[64];
                for(int j=0;j<64;j++){
                    dummy_w[j]=w[j];
                    dummy_e[j]=e[j];
                    dummy_b[j]=b[j];
                    new_m[j]=0;
                }
                //move corresponding to player
                make_move(b,w,e,m,i);
                //compute the evaluation function for this move
                //next move would be white's :false
                //possible moves
                pm(w,b,e,new_m);
                double move_value = minmax(b,w,new_m,e,0,false,0,0);
                cout<<"index :" << i<<"  move_value :"<<move_value<<endl;
                //undo the move
                for(int j=0;j<64;j++){
                    w[j]=dummy_w[j];
                    e[j]=dummy_e[j];
                    b[j]=dummy_b[j];
                }
                if(move_value > best_value){
                    best_value=move_value;
                    index = i;
                }
            
            }
        }
        cout<<"best_value : "<<best_value<<endl<<"corresponding index : ";
        return index;
    }


}

int main()
{
        freopen("input.txt", "r", stdin); // redirects standard input

        for(int i=0;i<15;i++){
        cin>>state[i];
        cin>>train_mobility[i];
        cin>>train_corners[i];
        cin>>train_c_occupied[i];
        cin>>train_c_uno[i];
        cin>>train_x_unoccupied[i];
        cin>>train_no_pieces[i];
    }

    int b[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,1,0,0,1,1,1,0,0,0,1,1,1,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int w[64]={0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    int e[64]={1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,0,0,1,0,1,1,1,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,1,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
    int m[64]={0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    pm(b,w,e,m);
    for(int i=0;i<64;i++){
        cout<<m[i];
    }
    cout<<endl;
    clock_t start, end;
    start = clock();
    int best = best_move(b,w,e,m);
    end = clock();
cout<<best<<endl;
    double time_taken = double(end - start) / double(CLOCKS_PER_SEC); 
    cout <<endl<< "Time taken by program is : " << fixed  
         << time_taken << setprecision(5); 
    cout << " sec " << endl;
    cout<<"total child nodes : "<<branches<<endl;
    return 0;
}