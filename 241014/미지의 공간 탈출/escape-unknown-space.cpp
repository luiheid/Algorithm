#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct t {
    int y;
    int x;
    int d;
    int v;
};

struct loc {
    int cube;
    int y;
    int x;
    int turn;
};

int main() {
    int n, m, f;
    cin >> n >> m >> f;

    int padding[5][2] = {{m, m*2}, {m, 0}, {m*2, m}, {0, m}, {m, m}};
    int dir[4][2] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

    vector<vector<int>> map(n, vector<int>(n));
    vector<vector<bool>> visited(n, vector<bool>(n, false));
    vector<vector<vector<int>>> cube(5, vector<vector<int>>(m, vector<int>(m)));
    vector<vector<vector<bool>>> visited2(5, vector<vector<bool>>(m, vector<bool>(m, false)));
    vector<t> time(f);
    int start[2];
    int corner[2];
    bool found = false;
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            cin >> map[i][j];
            if(map[i][j] == 3 && !found){
                found = true;
                corner[0] = i;
                corner[1] = j;
            }
        }
    }

    for(int k=0; k<4; k++){
        for(int i=0; i<m; i++){
            for(int j=0; j<m; j++){
                cin >> cube[k][i][j];
            }
        }
    }

    // for(int k=0; k<4; k++){
    //     for(int i=0; i<m; i++){
    //         for(int j=0; j<m; j++){
    //             cout << cube[k][i][j];
    //         }
    //         cout << endl;
    //     }
    //     cout << endl;
    // }

    for(int i=0; i<m; i++){
        for(int j=0; j<m; j++){
            cin >> cube[4][i][j];
            if(cube[4][i][j] == 2){
                start[0] = i;
                start[1] = j;
                // cout << "start: " << start[0] << " " << start[1] << endl;
            }
        }
    }
    

    // for(int i=0; i<m*3; i++){
    //         for(int j=0; j<m*3; j++){
    //             cout << cube[i][j];
    //    }
    //    cout << endl;
    // }

    for(int i=0; i<f; i++){
        cin >> time[i].y;
        cin >> time[i].x;
        cin >> time[i].d;
        cin >> time[i].v;
    }

    queue<loc> q;
    q.push({4, start[0], start[1], 0});
    visited2[4][start[0]][start[1]] = true;

    int result;
    bool done = false;
    while(!q.empty()){
        if(done){
            break;
        }
        loc temp = q.front();
        q.pop();

        for(int i=0; i<4; i++){
            int dy = temp.y + dir[i][0];
            int dx = temp.x + dir[i][1];
            loc neww = {temp.cube, dy, dx, temp.turn + 1};
            if(neww.cube != 4 && dy == m-1 && cube[neww.cube][neww.y][neww.x] == 0){
                switch(temp.cube){
                    case 0:
                        start[0] = corner[0] + m - 1 - dx;
                        start[1] = corner[1] + m;
                        break;
                    case 1:
                        start[0] = corner[0] + dx;
                        start[1] = corner[1] - 1;
                        break;
                    case 2:
                        start[0] = corner[0] + m;
                        start[1] = corner[1] + dx;
                        break;
                    case 3:
                        start[0] = corner[0] - 1;
                        start[1] = corner[1] + m - 1 - dx;
                }
                // cout << "end: " << neww.y << " " << neww.x << endl;

                result = neww.turn + 1;
                done = true;
                break;
            }
            if(dy < 0 || dy > m-1 || dx < 0 || dx > m-1){
                if(temp.cube == 4){
                    if(dy < 0){
                        neww.cube = 3;
                        neww.y = 0;
                        neww.x = m-1 - dx;
                    }
                    else if(dy > m-1){
                        neww.cube = 2;
                        neww.y = 0;
                        neww.x = dx;
                    }
                    else if(dx < 0){
                        neww.cube = 1;
                        neww.y = 0;
                        neww.x = dy;
                    }
                    else{
                        neww.cube = 0;
                        neww.y = 0;
                        neww.x = m-1 - dy;
                    }
                }
                else{
                    if(dy > m-1){
                        continue;
                    }
                    else if(dy < 0){
                        neww.cube = 4;
                        switch(temp.cube){
                            case 0:
                                neww.y = m - 1 - dx;
                                neww.x = m - 1;
                                break;
                            case 1:
                                neww.y = dx;
                                neww.x = 0;
                                break;
                            case 2:
                                neww.y = m - 1;
                                neww.x = dx;
                                break;
                            case 3:
                                neww.y = 0;
                                neww.x = m - 1 - dx;
                        }
                    }
                    else{
                        if(dx < 0){
                            neww.x = m - 1;
                            switch(temp.cube){
                                case 0:
                                    neww.cube = 2;
                                    break;
                                case 1:
                                    neww.cube = 3;
                                    break;
                                case 2:
                                    neww.cube = 1;
                                    break;
                                case 3:
                                    neww.cube = 0;
                            }
                        }
                        else{
                            neww.x = 0;
                            switch(temp.cube){
                                case 0:
                                    neww.cube = 3;
                                    break;
                                case 1:
                                    neww.cube = 2;
                                    break;
                                case 2:
                                    neww.cube = 0;
                                    break;
                                case 3:
                                    neww.cube = 1;
                            }
                        }
                    }
                }
            }
            if(cube[neww.cube][neww.y][neww.x] == 0 && !visited2[neww.cube][neww.y][neww.x]){
                // cout << neww.cube << " " << neww.y << " " << neww.x << " " << neww.turn << endl;

                q.push(neww);
                visited2[neww.cube][neww.y][neww.x] = true;
            }
        }
    }
    if(start[0] < 0 || start[0] > n-1 || start[1] < 0 || start[1] > n-1){
        cout << -1;
        return 0;
    }
    // cout << "===" << result << " " << start[0] << " " << start[1] << endl;
    q = queue<loc>();

    q.push({0, start[0], start[1], result});
    visited[start[0]][start[1]] = true;

    while(!q.empty()){
        loc temp = q.front();
        q.pop();
        temp.turn++;

        for(int i=0; i<4; i++){
            int dy = temp.y + dir[i][0];
            int dx = temp.x + dir[i][1];

            if(dy >= 0 && dy < n && dx >= 0 && dx < n){
                if(map[dy][dx] == 4){
                    cout << temp.turn;
                    return 0;
                }
                if(!visited[dy][dx] && map[dy][dx] == 0){
                    bool bad = false;
                    for(int j = 0; j < f; j++){
                        int time_s[2] = {time[j].y, time[j].x};
                        int time_e[2] = {time[j].y, time[j].x};

                        int dist = temp.turn / time[j].v;

                        switch (time[j].d){
                            case 0:
                                time_e[1] += dist;
                                if(dy == time_s[0] && dx >= time_s[1] && dx <= time_e[1]){
                                    bad = true;
                                }
                                break;
                            case 1:
                                time_e[1] -= dist;
                                if(dy == time_s[0] && dx >= time_e[1] && dx <= time_s[1]){
                                    bad = true;
                                }
                                break;
                            case 2:
                                time_e[0] += dist;
                                if(dx == time_s[1] && dy >= time_s[0] && dy <= time_e[0]){
                                    bad = true;
                                }
                                break;
                            case 3:
                                time_e[0] -= dist;
                                if(dx == time_s[1] && dy >= time_e[0] && dy <= time_s[0]){
                                    bad = true;
                                }
                        }
                    }
                    if(bad){
                        continue;
                    }
                    visited[dy][dx] = true;
                    q.push({0, dy, dx, temp.turn});
                    // cout << dy << " "<<dx <<" "<< temp.turn << endl;
                }
            }
        }
    }

    cout << -1;

    return 0;
}