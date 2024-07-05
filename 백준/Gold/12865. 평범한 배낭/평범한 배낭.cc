#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct item{
    int weight;
    int value;
};

int main(){
    int n, k;

    cin >> n >> k;

    vector<struct item> items(n);
    for(int i=0; i<n; i++){
        cin >> items[i].weight >> items[i].value;
    }

    vector<vector<int>> map(n+1, vector<int>(k+1, 0));

    for(int i=1; i<n+1; i++){
        for(int j=1; j<k+1; j++){
            map[i][j] = map[i-1][j];
            if(j >= items[i-1].weight){
                map[i][j] = max(map[i][j], map[i-1][j-items[i-1].weight] + items[i-1].value);
            }
        }
    }

    cout << map[n][k];

    return 0;
}
