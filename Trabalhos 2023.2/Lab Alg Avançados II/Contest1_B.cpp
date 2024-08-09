#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct order_t{
    int startTime;
    int finishTime;
    int price;
};

istream& operator>>(istream& is, order_t& order){
    is >> order.startTime;
    
    int duration;
    cin >> duration;
    order.finishTime = order.startTime + duration;
    
    
    is >> order.price;
    return is;
}

bool operator<(const order_t& orderA, const order_t& orderB){
    return orderA.startTime < orderB.startTime;
}

long long solve(const int curOrder, const int curTime, const vector<order_t>& orders, vector<long long>& memo){
    if(curOrder == orders.size()){
        return 0;
    }
    else if(memo[curTime] != -1){
        return memo[curTime];
    }
    else if(orders[curOrder].startTime < curTime){
        return memo[curTime] = solve(curOrder+1, curTime, orders, memo);
    }
    else if(orders[curOrder].startTime != curTime){
        return memo[curTime] = solve(curOrder, curTime+1, orders, memo);
    }
    else{
        int buffer1 = orders[curOrder].price + solve(curOrder+1, orders[curOrder].finishTime, orders, memo);
        int buffer2 = solve(curOrder+1, curTime, orders, memo);
        
        if(buffer1 > buffer2){
            return memo[curTime] = buffer1;
        }
        else{
            return memo[curTime] = buffer2;
        }
    }
}

int main()
{
    int nTests;
    cin >> nTests;
    for(int t = 0; t < nTests; t++){
        int nOrders, maxTime = 0;
        cin >> nOrders;
        vector<order_t> orders(nOrders);
        for(int i = 0; i < nOrders; i++){
            cin >> orders[i];
            if(orders[i].finishTime > maxTime){
                maxTime = orders[i].finishTime;
            }
        }
        sort(orders.begin(), orders.end());
        
        vector<long long> memo(maxTime+1, -1);
        memo[maxTime] = 0;
        
        cout << solve(0, 0, orders, memo) << '\n';
    }
    
    return 0;
}