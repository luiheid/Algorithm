#include <iostream>
#include <algorithm>

using namespace std;

struct Thing{
  int w;
  int v;
};

bool compare(Thing a, Thing b){
  if(a.w == b.w){
    return a.v > b.v;
  }
  return a.w < b.w;
}

int main(){

  int n, k;
  cin >> n >> k;

  Thing* things = new Thing[n];
  for(int i=0; i<n; i++){
    cin >> things[i].w >> things[i].v;
  }

  sort(things, things + n, compare);
  int** weights = new int*[n+1];
  for(int i=0; i<n+1; i++){
    weights[i] = new int[k+1];
  }
  for(int i=0; i<n+1 ; i++){
    for(int j=0; j<k+1 ; j++){
      weights[i][j] = 0;
    }
  }

  for(int i=1; i<n+1; i++){
    for(int j=1; j<k+1; j++){
      if(j >= things[i-1].w){
        if(weights[i-1][j] < weights[i-1][j-things[i-1].w] + things[i-1].v){
          weights[i][j] = weights[i-1][j-things[i-1].w] + things[i-1].v;
        }
        else{
          weights[i][j] = weights[i-1][j];
        }
      }
      else{
        weights[i][j] = weights[i-1][j];
      }
    }
  }

  cout << weights[n][k];
}