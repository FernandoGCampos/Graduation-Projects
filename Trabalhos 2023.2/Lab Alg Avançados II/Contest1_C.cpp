#include <iostream>

using namespace std;

int countNotC(const int start, const int end, const string& letters, const char c){
    int count = 0;
    for(int i = start; i < end; i++){
        count += (letters[i] != c);
    }
    return count;
}

int makeCGood(const int start, const int end, const string& letters, const char c){
    if(end - start == 1){
        return (letters[start] != c);
    }
    
    int middle = (start + end) >> 1;
    int buffer1 = countNotC(start, middle, letters, c)   + makeCGood(middle, end, letters, c+1);
    int buffer2 = makeCGood(start, middle, letters, c+1) + countNotC(middle, end, letters, c);
    
    if(buffer1 < buffer2){
        return buffer1;
    }
    else{
        return buffer2;
    }
}
int main()
{
    int nTests;
    cin >> nTests;
    for(int t = 0; t < nTests; t++){
        int nLetters;
        cin >> nLetters;
        
        string letters;
        cin >> letters;
        
        cout << makeCGood(0, nLetters, letters, 'a') << '\n';
    }

    return 0;
}