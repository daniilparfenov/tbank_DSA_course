#include <iostream>
#include <map>
#include <queue>
#include <stack>
#include <utility>
#include <vector>
using namespace std;

typedef pair<int, int> cell;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<cell> moves = {{-1, -2}, {-1, 2}, {1, -2}, {1, 2}, {-2, -1}, {-2, 1}, {2, -1}, {2, 1}};
    size_t N;
    cin >> N;
    cell start, end;

    cin >> start.first >> start.second;
    cin >> end.first >> end.second;
    start.first--;
    end.first--;
    start.second--;
    end.second--;

    queue<cell> q;
    q.push(start);
    map<cell, bool> visited;
    map<cell, cell> prev;

    bool pathIsFound = false;

    while (!q.empty()) {
        cell curCell = q.front();
        q.pop();
        visited[curCell] = true;

        for (auto& [dx, dy] : moves) {
            int nx = curCell.first + dx;
            int ny = curCell.second + dy;
            cell nCell = {nx, ny};
            if (nx >= 0 && nx < N && ny >= 0 && ny < N && visited.count(nCell) == 0) {
                prev[nCell] = curCell;
                visited[nCell] = true;
                q.push(nCell);
                if (nCell.first == end.first && nCell.second == end.second) {
                    pathIsFound = true;
                    break;
                }
            }
        }
        if (pathIsFound) break;
    }

    stack<cell> path;
    cell curCell = end;
    while (curCell != start) {
        path.push(curCell);
        curCell = prev[curCell];
    }
    path.push(curCell);

    cout << path.size() - 1 << '\n';
    while (!path.empty()) {
        curCell = path.top();
        cout << curCell.first + 1 << ' ' << curCell.second + 1 << '\n';
        path.pop();
    }

    return 0;
}
