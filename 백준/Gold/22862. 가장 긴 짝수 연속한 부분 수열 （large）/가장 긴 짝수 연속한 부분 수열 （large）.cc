#include <iostream>
#include <algorithm>

using namespace std;

int main(){

  int n, k;
  cin >> n >> k;

  int* num = new int[n];

  for(int i=0; i<n; i++){
    cin >> num[i];
  }

  int even = 0;
  int odd = 0;

  int mmax=0;

  int start=0, end=0;
  while(end < n){
    if(num[end]%2 == 0){
      even++;
    }
    else{
      odd++;
      if(odd > k){
        mmax = max(mmax, even);
        odd--;

        if(num[start]%2 == 1){
          start++;
        }
        else{
          while(start <= end && num[start]%2 == 0){
            start++;
            even--;
          } 
          start++;
        }
      }
    }
    end++;
  }
  mmax = max(mmax, even);

  cout << mmax;
}