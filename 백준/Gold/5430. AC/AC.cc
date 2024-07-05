#include <iostream>
#include <vector>

using namespace std;

int main(){
    int n;
    cin >> n;

    for(int i=0; i<n; i++){
        string s;
        cin >> s;

        int nn;
        cin >> nn;

        int r=0, d=0;
        int start_idx=0, end_idx=nn-1;

        for(int j=0; j<s.length(); j++){
            if(s[j] == 'D'){
                d++;
                if(r % 2 == 0){
                    start_idx++;
                }
                else{
                    end_idx--;
                }
            }
            else{
                r++;
            }
        }

        char c;
        cin >> c;

        int result[nn];
        for(int j=0; j<nn; j++){
            int num;
            cin >> num;
            cin >> c;

            result[j] = num;
        }
        if(!nn){
            cin >> c;
        }

        if(d > nn){
            cout << "error\n";
            continue;
        }

        cout << '[';
        if(start_idx <= end_idx){
            if(r % 2 == 0){
                for(int j=start_idx; j<end_idx; j++){
                    cout << result[j] << ',';
                }
                cout << result[end_idx] << "]\n";
            }
            else{
                for(int j=end_idx; j>start_idx; j--){
                    cout << result[j] << ',';
                }
                cout << result[start_idx] << "]\n";
            }
        }
        else{
            cout << "]\n";
        }
    }
}