#include <iostream>

using namespace std;

int main() {
    int nTests;
    cin >> nTests;
    for(int t = 0; t < nTests; t++) {
        long long y, x;
        cin >> y >> x;

        if(y > x){
            if(y % 2){
                cout << (y-1)*(y-1) + x << '\n';
            }
            else{
                cout << y*y - (x-1) << '\n';
            }
        }
        else{
            if(x % 2){
                cout << x*x - (y-1) << '\n';
            }
            else{
                cout << (x-1)*(x-1) + y << '\n';
            }
        }
    }
}
