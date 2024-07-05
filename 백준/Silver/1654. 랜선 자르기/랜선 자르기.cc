#include <iostream>
#include <vector>

#define fast cin.tie(0), cout.tie(0), ios::sync_with_stdio(0)

using namespace std;

int main(){

    int k, n;
    long long int sum = 0;

    cin >> k >> n;
    vector<int> v(k);
    for(int i=0; i<k; i++){
        cin >> v[i];
        sum += v[i];
    }

    int start = 1;
    int end = sum/n;
    int result;
    while(1){
        int mid = (start+(long long int)end) / 2;
        int num = 0;
        for(int i=0; i<v.size(); i++){
            num += v[i] / mid;
            if(num >= n){
                break;
            }
        }
        if(num >= n){
            result = mid;
            if(mid == end){
                break;
            }
            start = mid + 1;
        }
        else{
            end = mid - 1;
        }
    }

    cout << result;
    return 0;
}