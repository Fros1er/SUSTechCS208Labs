#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>
#include <cstring>

int boysPref[1000][1000], girlsPref[1000][1000];
int boysPointer[1000], matches[1000];
std::string boysNames[1000], girlsNames[1000];

int main() {
    std::ios::sync_with_stdio(false);
    int n;
    std::cin >> n;
    std::unordered_map<std::string, int> boysMap(n), girlsMap(n);
    std::queue<int> q;
    memset(matches, -1, sizeof(matches));
    for (int i = 0; i < n; i++) {
        std::string name;
        std::cin >> name;
        boysMap.emplace(name, i);
        boysNames[i] = name;
        q.push(i);
    }
    for (int i = 0; i < n; i++) {
        std::string name;
        std::cin >> name;
        girlsNames[i] = name;
        girlsMap.emplace(name, i);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::string name;
            std::cin >> name;
            boysPref[i][j] = girlsMap[name];
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::string name;
            std::cin >> name;
            girlsPref[i][boysMap[name]] = j;
        }
    }

    while (!q.empty()) {
        int boy = q.front();
        int girl = boysPref[boy][boysPointer[boy]++];
        if (matches[girl] == -1) {
            q.pop();
            matches[girl] = boy;
        } else if (girlsPref[girl][matches[girl]] > girlsPref[girl][boy]) {
            q.pop();
            q.push(matches[girl]);
            matches[girl] = boy;
        }
    }
    for (int i = 0; i < n; i++) {
        std::cout << boysNames[matches[i]] << " " << girlsNames[i] << std::endl;
    }
}
