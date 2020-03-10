#include<iostream>
#include<vector>

using namespace std;

class lift{
    public:
        int floor;
        char state;
};

int move(char state,int floor){
    if(state == 'U'){
        floor++;
    }
    
    if(state == 'D'){
        floor--;
    }

    return floor; 
}

class order{
    public:
        int src,dest;
        char dir;
        int boarding;
};

int open(int lfloor, char ldir, order user){
    if(lfloor == user.src && ldir == user.dir && user.boarding == 0){ 
        return 15 ;

    }
    else if(lfloor == user.dest){
        return -15 ;
    }
    return 45 ;
}

vector <order> p;

int main(){
    int n;
    cout<<"enter the no. of passengers: ";
    cin>>n;
    int max = -9999;
    int min = 9999;
    for(int i = 0 ;i < n ; i++){
        order temp;
        cin >> temp.src;
        if(temp.src > max){
            max = temp.src;
        }
        if(temp.src < min){
            min = temp.src;
        }
        cin >> temp.dir;
        cin >> temp.dest;
        if(temp.dest > max){
            max = temp.dest;
        }
        if(temp.dest < min){
            min = temp.dest;
        }
        temp.boarding = 0;
        p.push_back(temp);
    }

    lift l1,l2;
    char state_1,state_2;
    l1.floor = 0 ;
    
    l1.state = 'R';
    l2.state = 'R';

    if(max>0){
        l1.state = 'U';
    }
    if(min<0){
        l2.state = 'D';
    }

    state_1 = l1.state;
    state_2 = l2.state;

    while(l1.state != 'R'){
        int temp_1 = move(l1.state,l1.floor);
        l1.floor = temp_1;
        for(int i = 0 ; i < n ; i++){
            order temp1 = p[i];
            int key = open(l1.floor, l1.state, temp1) ;
            if(key == 15){
                cout << "lift1 picks passenger " << i+1 << " from " << l1.floor << endl;
                temp1.boarding = 1;
                p[i] = temp1;
            }
            if(key == -15 && temp1.boarding == 1){
                cout << "lift1 drops passenger " << i+1 << " to " << l1.floor << endl;
                temp1.dir = 'R';
                temp1.boarding = -10;
                p[i] = temp1;
            }
        }
        if(temp_1 == max)
            l1.state = 'R';
    }

    while(l2.state != 'R'){
        int temp_2 = move(l2.state,l2.floor);
        l2.floor = temp_2;
        for(int i = 0 ; i < n ; i++){
            order temp2 = p[i];
            int key = open(l2.floor, l2.state, temp2) ;
            if(key == 15){
                cout << "lift2 picks passenger " << i+1 << " from " << l2.floor << endl;
                temp2.boarding = 2;
                p[i] = temp2;
            }
            if(key == -15 && temp2.boarding == 2){
                cout << "lift2 drops passenger " << i+1 << " to " << l2.floor << endl;
                temp2.dir = 'R';
                temp2.boarding = -10;
                p[i] = temp2;
            }
        }
        if(temp_2 == min)
            l2.state = 'R';
    }

    if(state_1 == 'U'){
        l1.state = 'D';
    }else if(state_1 == 'D'){
        l1.state = 'U';
    }

    if(state_2 == 'U'){
        l2.state = 'D';
    }else if (state_2 == 'D'){
        l2.state = 'U';
    }

    while(l1.state != 'R'){
        int temp_1 = move(l1.state,l1.floor);
        l1.floor = temp_1;
        for(int i = 0 ; i < n ; i++){
            order temp1 = p[i];
            int key = open(l1.floor, l1.state, temp1) ;
            if(key == 15){
                cout << "lift1 picks passenger " << i+1 << " from " << l1.floor << endl;
                temp1.boarding = -1;
                p[i] = temp1;
            }
            if(key == -15 && temp1.boarding == -1){
                cout << "lift1 drops passenger " << i+1 << " to " << l1.floor << endl;
                temp1.dir = 'R';
                temp1.boarding = -10;
                p[i] = temp1;
            }
        }
        if(temp_1 == min)
            l1.state = 'R';
    }

    while(l2.state != 'R'){
        int temp_2 = move(l2.state,l2.floor);
        l2.floor = temp_2;
        for(int i = 0 ; i < n ; i++){
            order temp2 = p[i];
            int key = open(l2.floor, l2.state, temp2) ;
            if(key == 15){
                cout<<"lift2 picks passenger "<< i+1 << " from " << l2.floor << endl;
                temp2.boarding = -2;
                p[i] = temp2;
            }
            if(key == -15 && temp2.boarding == -2){
                cout << "lift2 drops passenger "<< i+1 <<" to " << l2.floor << endl;
                temp2.dir = 'R';
                temp2.boarding = -10;
                p[i] = temp2;
            }
        }
        if(temp_2 == max)
            l2.state = 'R';
    }

}
