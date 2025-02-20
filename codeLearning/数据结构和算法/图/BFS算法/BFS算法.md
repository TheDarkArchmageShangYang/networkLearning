# BFS算法

## 基本原理

与图的BFS基本一致

## 模板

```c++
int bfs(const Graph& graph, int s, int target) {
    vector<bool> visited(graph.size(), false);
    queue<int> q;
    q.push(s);
    visited[s] = true;
    int step = 0;
    while (!q.empty()) {
        int n = q.size();
        for (int i = 0; i < n; i++) {
            auto cur = q.front();
            q.pop();
            if (cur == target) {
                return step;
            }
            for (int& to : neighborsOf(cur)) {
                if (!visited[to]) {
                    q.push(to);
                    visited[to] = true;
                }
            }
        }
        step++;
    }
    return -1;
}
```



## 例题

- 841.[钥匙和房间](https://leetcode.cn/problems/keys-and-rooms/description/)
- 1306.[跳跃游戏III](https://leetcode.cn/problems/jump-game-iii/description/)
- 433.[最小基因变化](https://leetcode.cn/problems/minimum-genetic-mutation/description/)
- 1926.[迷宫中离入口最近的出口](https://leetcode.cn/problems/nearest-exit-from-entrance-in-maze/description/)
- 542.[01矩阵](https://leetcode.cn/problems/01-matrix/description/)
- 773.[滑动谜题](https://leetcode.cn/problems/sliding-puzzle/description/)
- 752.[打开转盘锁](https://leetcode.cn/problems/open-the-lock/description/)
- 994.[腐烂的橘子](https://leetcode.cn/problems/rotting-oranges/description/)
- 2101.[引爆最多的炸弹](https://leetcode.cn/problems/detonate-the-maximum-bombs/description/)
- 399.[除法求值](https://leetcode.cn/problems/evaluate-division/description/)
- 924.[尽量减少恶意软件的传播](https://leetcode.cn/problems/minimize-malware-spread/description/)
- 417.[太平洋大西洋水流问题](https://leetcode.cn/problems/pacific-atlantic-water-flow/description/)
- 365.[水壶问题](https://leetcode.cn/problems/water-and-jug-problem/description/)



841,1306,433,1926,542最基础的BFS

773,752,994,2101,399把问题抽象成BFS

924对多个连通分量依次BFS

417两次BFS来优化搜索效率

365向旁边节点探索的过程比较特殊



### 841.[钥匙和房间](https://leetcode.cn/problems/keys-and-rooms/description/)

有 `n` 个房间，房间按从 `0` 到 `n - 1` 编号。最初，除 `0` 号房间外的其余所有房间都被锁住。你的目标是进入所有的房间。然而，你不能在没有获得钥匙的时候进入锁住的房间。

当你进入一个房间，你可能会在里面找到一套 **不同的钥匙**，每把钥匙上都有对应的房间号，即表示钥匙可以打开的房间。你可以拿上所有钥匙去解锁其他房间。

给你一个数组 `rooms` 其中 `rooms[i]` 是你进入 `i` 号房间可以获得的钥匙集合。如果能进入 **所有** 房间返回 `true`，否则返回 `false`。

 



**示例 1：**

```
输入：rooms = [[1],[2],[3],[]]
输出：true
解释：
我们从 0 号房间开始，拿到钥匙 1。
之后我们去 1 号房间，拿到钥匙 2。
然后我们去 2 号房间，拿到钥匙 3。
最后我们去了 3 号房间。
由于我们能够进入每个房间，我们返回 true。
```

**示例 2：**

```
输入：rooms = [[1,3],[3,0,1],[2],[0]]
输出：false
解释：我们不能进入 2 号房间。
```

 

**提示：**

- `n == rooms.length`
- `2 <= n <= 1000`
- `0 <= rooms[i].length <= 1000`
- `1 <= sum(rooms[i].length) <= 3000`
- `0 <= rooms[i][j] < n`
- 所有 `rooms[i]` 的值 **互不相同**

==**代码**==

```c++
class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>>& rooms) {
        int n = rooms.size();
        queue<int> q;
        unordered_set<int> visited;
        q.push(0);
        visited.insert(0);
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < rooms[cur].size(); i++) {
                int next = rooms[cur][i];
                if (visited.count(next)) continue;
                q.push(next);
                visited.insert(next);
                if (visited.size() == n) return true;
            }
        }
        return false;
    }
};
```



### 1306.[跳跃游戏III](https://leetcode.cn/problems/jump-game-iii/description/)

这里有一个非负整数数组 `arr`，你最开始位于该数组的起始下标 `start` 处。当你位于下标 `i` 处时，你可以跳到 `i + arr[i]` 或者 `i - arr[i]`。

请你判断自己是否能够跳到对应元素值为 0 的 **任一** 下标处。

注意，不管是什么情况下，你都无法跳到数组之外。

 

**示例 1：**

```
输入：arr = [4,2,3,0,3,1,2], start = 5
输出：true
解释：
到达值为 0 的下标 3 有以下可能方案： 
下标 5 -> 下标 4 -> 下标 1 -> 下标 3 
下标 5 -> 下标 6 -> 下标 4 -> 下标 1 -> 下标 3 
```

**示例 2：**

```
输入：arr = [4,2,3,0,3,1,2], start = 0
输出：true 
解释：
到达值为 0 的下标 3 有以下可能方案： 
下标 0 -> 下标 4 -> 下标 1 -> 下标 3
```

**示例 3：**

```
输入：arr = [3,0,2,1,2], start = 2
输出：false
解释：无法到达值为 0 的下标 1 处。 
```

 

**提示：**

- `1 <= arr.length <= 5 * 10^4`
- `0 <= arr[i] < arr.length`
- `0 <= start < arr.length`



==**代码**==

```c++
class Solution {
public:
    bool canReach(vector<int>& arr, int start) {
        queue<int> q;
        vector<bool> visited(arr.size());
        q.push(start);
        visited[start] = true;
        while (!q.empty()) {
            int cur = q.front();
            q.pop();
            if (arr[cur] == 0) return true;
            for (int i : {1, -1}) {
                int next = cur + i * arr[cur];
                if (next < 0 || next >= arr.size()) continue;
                if (visited[next]) continue;
                q.push(next);
                visited[next] = true;
            }
        }
        return false;
    }
};
```



### 433.[最小基因变化](https://leetcode.cn/problems/minimum-genetic-mutation/description/)

基因序列可以表示为一条由 8 个字符组成的字符串，其中每个字符都是 `'A'`、`'C'`、`'G'` 和 `'T'` 之一。

假设我们需要调查从基因序列 `start` 变为 `end` 所发生的基因变化。一次基因变化就意味着这个基因序列中的一个字符发生了变化。

- 例如，`"AACCGGTT" --> "AACCGGTA"` 就是一次基因变化。

另有一个基因库 `bank` 记录了所有有效的基因变化，只有基因库中的基因才是有效的基因序列。（变化后的基因必须位于基因库 `bank` 中）

给你两个基因序列 `start` 和 `end` ，以及一个基因库 `bank` ，请你找出并返回能够使 `start` 变化为 `end` 所需的最少变化次数。如果无法完成此基因变化，返回 `-1` 。

注意：起始基因序列 `start` 默认是有效的，但是它并不一定会出现在基因库中。

 

**示例 1：**

```
输入：start = "AACCGGTT", end = "AACCGGTA", bank = ["AACCGGTA"]
输出：1
```

**示例 2：**

```
输入：start = "AACCGGTT", end = "AAACGGTA", bank = ["AACCGGTA","AACCGCTA","AAACGGTA"]
输出：2
```

**示例 3：**

```
输入：start = "AAAAACCC", end = "AACCCCCC", bank = ["AAAACCCC","AAACCCCC","AACCCCCC"]
输出：3
```

 

**提示：**

- `start.length == 8`
- `end.length == 8`
- `0 <= bank.length <= 10`
- `bank[i].length == 8`
- `start`、`end` 和 `bank[i]` 仅由字符 `['A', 'C', 'G', 'T']` 组成



==**代码**==

```c++
class Solution {
public:
    int minMutation(string startGene, string endGene, vector<string>& bank) {
        queue<string> q;
        unordered_set<string> visited;
        q.push(startGene);
        visited.insert(startGene);
        int step = 0;
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                string cur = q.front();
                q.pop();
                if (cur == endGene) return step;
                for (int j = 0; j < bank.size(); j++) {
                    if (visited.count(bank[j])) continue;
                    if (!check(cur, bank[j])) continue;
                    q.push(bank[j]);
                    visited.insert(bank[j]);
                }
            }
            step++;
        }
        return -1;
    }
    bool check(string& str1, string& str2) {
        int diff = 0;
        for (int i = 0; i < str1.length(); i++) {
            if (str1[i] != str2[i]) {
                diff++;
            }
        }
        return diff == 1;
    }
};
```



### 1926.[迷宫中离入口最近的出口](https://leetcode.cn/problems/nearest-exit-from-entrance-in-maze/description/)

给你一个 `m x n` 的迷宫矩阵 `maze` （**下标从 0 开始**），矩阵中有空格子（用 `'.'` 表示）和墙（用 `'+'` 表示）。同时给你迷宫的入口 `entrance` ，用 `entrance = [entrancerow, entrancecol]` 表示你一开始所在格子的行和列。

每一步操作，你可以往 **上**，**下**，**左** 或者 **右** 移动一个格子。你不能进入墙所在的格子，你也不能离开迷宫。你的目标是找到离 `entrance` **最近** 的出口。**出口** 的含义是 `maze` **边界** 上的 **空格子**。`entrance` 格子 **不算** 出口。

请你返回从 `entrance` 到最近出口的最短路径的 **步数** ，如果不存在这样的路径，请你返回 `-1` 。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211012330237.jpeg)

```
输入：maze = [["+","+",".","+"],[".",".",".","+"],["+","+","+","."]], entrance = [1,2]
输出：1
解释：总共有 3 个出口，分别位于 (1,0)，(0,2) 和 (2,3) 。
一开始，你在入口格子 (1,2) 处。
- 你可以往左移动 2 步到达 (1,0) 。
- 你可以往上移动 1 步到达 (0,2) 。
从入口处没法到达 (2,3) 。
所以，最近的出口是 (0,2) ，距离为 1 步。
```

**示例 2：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211012330219.jpeg)

```
输入：maze = [["+","+","+"],[".",".","."],["+","+","+"]], entrance = [1,0]
输出：2
解释：迷宫中只有 1 个出口，在 (1,2) 处。
(1,0) 不算出口，因为它是入口格子。
初始时，你在入口与格子 (1,0) 处。
- 你可以往右移动 2 步到达 (1,2) 处。
所以，最近的出口为 (1,2) ，距离为 2 步。
```

**示例 3：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211012330234.jpeg)

```
输入：maze = [[".","+"]], entrance = [0,0]
输出：-1
解释：这个迷宫中没有出口。
```

 

**提示：**

- `maze.length == m`
- `maze[i].length == n`
- `1 <= m, n <= 100`
- `maze[i][j]` 要么是 `'.'` ，要么是 `'+'` 。
- `entrance.length == 2`
- `0 <= entrancerow < m`
- `0 <= entrancecol < n`
- `entrance` 一定是空格子。



==**代码**==

```c++
class Solution {
public:
    int nearestExit(vector<vector<char>>& maze, vector<int>& entrance) {
        int m = maze.size(), n = maze[0].size();
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        queue<pair<int, int>> q;
        q.emplace(entrance[0], entrance[1]);
        maze[entrance[0]][entrance[1]] = '+';
        int step = 0;
        while (!q.empty()) {
            step++;
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto cur = q.front();
                q.pop();
                for (int j = 0; j < 4; j++) {
                    int x = cur.first + dirs[j][0];
                    int y = cur.second + dirs[j][1];
                    if (x < 0 || x >= m || y < 0 || y >= n) continue;
                    if (maze[x][y] == '+') continue;
                    if (x == 0 || x == m - 1 || y == 0 || y == n - 1) return step;
                    q.emplace(x, y);
                    maze[x][y] = '+';
                }
            }
        }
        return -1;
    }
};
```



### 542.[01矩阵](https://leetcode.cn/problems/01-matrix/description/)

给定一个由 `0` 和 `1` 组成的矩阵 `mat` ，请输出一个大小相同的矩阵，其中每一个格子是 `mat` 中对应位置元素到最近的 `0` 的距离。

两个相邻元素间的距离为 `1` 。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211193105653.png)

```
输入：mat = [[0,0,0],[0,1,0],[0,0,0]]
输出：[[0,0,0],[0,1,0],[0,0,0]]
```

**示例 2：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211193105662.png)

```
输入：mat = [[0,0,0],[0,1,0],[1,1,1]]
输出：[[0,0,0],[0,1,0],[1,2,1]]
```

 

**提示：**

- `m == mat.length`
- `n == mat[i].length`
- `1 <= m, n <= 10^4`
- `1 <= m * n <= 10^4`
- `mat[i][j] is either 0 or 1.`
- `mat` 中至少有一个 `0 `



==**代码**==

```c++
class Solution {
public:
    vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
        int m = mat.size(), n = mat[0].size();
        vector<vector<int>> ans(m, vector<int>(n, -1));
        queue<pair<int, int>> q;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (mat[i][j] == 0) {
                    ans[i][j] = 0;
                    q.emplace(i, j);
                }
            }
        }
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        int cost = 1;
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto [x, y] = q.front();
                q.pop();
                for (auto [dx, dy] : dirs) {
                    int nx = x + dx;
                    int ny = y + dy;
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || ans[nx][ny] >= 0) continue;
                    q.emplace(nx, ny);
                    ans[nx][ny] = cost;
                }
            }
            cost++;
        }
        return ans;
    }
};
```



### 773.[滑动谜题](https://leetcode.cn/problems/sliding-puzzle/description/)

在一个 `2 x 3` 的板上（`board`）有 5 块砖瓦，用数字 `1~5` 来表示, 以及一块空缺用 `0` 来表示。一次 **移动** 定义为选择 `0` 与一个相邻的数字（上下左右）进行交换.

最终当板 `board` 的结果是 `[[1,2,3],[4,5,0]]` 谜板被解开。

给出一个谜板的初始状态 `board` ，返回最少可以通过多少次移动解开谜板，如果不能解开谜板，则返回 `-1` 。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250210212549681.jpeg)

```
输入：board = [[1,2,3],[4,0,5]]
输出：1
解释：交换 0 和 5 ，1 步完成
```

**示例 2:**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250210212549701.jpeg)

```
输入：board = [[1,2,3],[5,4,0]]
输出：-1
解释：没有办法完成谜板
```

**例 3:**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250210212549706.jpeg)

```
输入：board = [[4,1,2],[5,0,3]]
输出：5
解释：
最少完成谜板的最少移动次数是 5 ，
一种移动路径:
尚未移动: [[4,1,2],[5,0,3]]
移动 1 次: [[4,1,2],[0,5,3]]
移动 2 次: [[0,1,2],[4,5,3]]
移动 3 次: [[1,0,2],[4,5,3]]
移动 4 次: [[1,2,0],[4,5,3]]
移动 5 次: [[1,2,3],[4,5,0]]
```

 

**提示：**

- `board.length == 2`
- `board[i].length == 3`
- `0 <= board[i][j] <= 5`
- `board[i][j]` 中每个值都 **不同**



==**代码**==

主要问题在于需要用其他方式来存储一个二维vector

这里使用了string来表示,另外在string的末尾额外用一个字符来记录 `0` 所在位置.也可以在queue中使用 `pair<string, int>` 来存储.

```c++
class Solution {
public:
    vector<vector<int>> dirs = {
        {1, 3},
        {0, 2, 4},
        {1, 5},
        {0, 4},
        {1, 3, 5},
        {2, 4}
    };
    int slidingPuzzle(vector<vector<int>>& board) {
        string start(7, ' ');
        for (int i = 0; i < board.size(); i++) {
            for (int j = 0; j < board[0].size(); j++) {
                start[i*3+j] = board[i][j] + '0';
                if (board[i][j] == 0) {
                    start[6] = i*3 + j + '0';
                }
            }
        }
        queue<string> q;
        unordered_set<string> visited;
        q.push(start);
        visited.insert(start);
        int step = 0;
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                string cur = q.front();
                q.pop();
                if (cur == "1234505") return step;
                int tempIndex1 = cur[6] - '0';
                for (int k = 0; k < dirs[tempIndex1].size(); k++) {
                    int tempIndex2 = dirs[tempIndex1][k];
                    if (tempIndex2 < 0 || tempIndex2 > 5) continue;
                    string temp = cur;
                    swap(temp[tempIndex1], temp[tempIndex2]);
                    temp[6] = tempIndex2 + '0';
                    if (visited.count(temp)) continue;
                    q.push(temp);
                    visited.insert(temp);
                }
            }
            step++;
        }
        return -1;
    }
};
```



### 752.[打开转盘锁](https://leetcode.cn/problems/open-the-lock/description/)

你有一个带有四个圆形拨轮的转盘锁。每个拨轮都有10个数字： `'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'` 。每个拨轮可以自由旋转：例如把 `'9'` 变为 `'0'`，`'0'` 变为 `'9'` 。每次旋转都只能旋转一个拨轮的一位数字。

锁的初始数字为 `'0000'` ，一个代表四个拨轮的数字的字符串。

列表 `deadends` 包含了一组死亡数字，一旦拨轮的数字和列表里的任何一个元素相同，这个锁将会被永久锁定，无法再被旋转。

字符串 `target` 代表可以解锁的数字，你需要给出解锁需要的最小旋转次数，如果无论如何不能解锁，返回 `-1` 。

 

**示例 1:**

```
输入：deadends = ["0201","0101","0102","1212","2002"], target = "0202"
输出：6
解释：
可能的移动序列为 "0000" -> "1000" -> "1100" -> "1200" -> "1201" -> "1202" -> "0202"。
注意 "0000" -> "0001" -> "0002" -> "0102" -> "0202" 这样的序列是不能解锁的，
因为当拨动到 "0102" 时这个锁就会被锁定。
```

**示例 2:**

```
输入: deadends = ["8888"], target = "0009"
输出：1
解释：把最后一位反向旋转一次即可 "0000" -> "0009"。
```

**示例 3:**

```
输入: deadends = ["8887","8889","8878","8898","8788","8988","7888","9888"], target = "8888"
输出：-1
解释：无法旋转到目标数字且不被锁定。
```

 

**提示：**

- `1 <= deadends.length <= 500`
- `deadends[i].length == 4`
- `target.length == 4`
- `target` **不在** `deadends` 之中
- `target` 和 `deadends[i]` 仅由若干位数字组成



==**代码**==

```c++
class Solution {
public:
    int openLock(vector<string>& deadends, string target) {
        unordered_set<string> deadSet(deadends.begin(), deadends.end());
        if (deadSet.count("0000")) return -1;
        
        queue<string> q;
        unordered_set<string> visited;
        q.push("0000");
        visited.insert("0000");
        int step = 0;
        
        while (!q.empty()) {
            int n = q.size();
            for (int i = 0; i < n; i++) {
                auto cur = q.front();
                q.pop();
                if (cur == target) return step;
                for (int i = 0; i < 4; i++) {
                    string temp = cur;
                    temp[i] = (cur[i] == '9') ? '0' : cur[i] + 1;
                    if (!visited.count(temp) && !deadSet.count(temp)) {
                        q.push(temp);
                        visited.insert(temp);
                    }
                    temp[i] = (cur[i] == '0') ? '9' : cur[i] - 1;
                    if (!visited.count(temp) && !deadSet.count(temp)) {
                        q.push(temp);
                        visited.insert(temp);
                    }
                }
            }
            step++;
        }
        return -1;
    }
};
```



### 994.[腐烂的橘子](https://leetcode.cn/problems/rotting-oranges/description/)

在给定的 `m x n` 网格 `grid` 中，每个单元格可以有以下三个值之一：

- 值 `0` 代表空单元格；
- 值 `1` 代表新鲜橘子；
- 值 `2` 代表腐烂的橘子。

每分钟，腐烂的橘子 **周围 4 个方向上相邻** 的新鲜橘子都会腐烂。

返回 *直到单元格中没有新鲜橘子为止所必须经过的最小分钟数。如果不可能，返回 `-1`* 。

 

**示例 1：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211130026136.png)**

```
输入：grid = [[2,1,1],[1,1,0],[0,1,1]]
输出：4
```

**示例 2：**

```
输入：grid = [[2,1,1],[0,1,1],[1,0,1]]
输出：-1
解释：左下角的橘子（第 2 行， 第 0 列）永远不会腐烂，因为腐烂只会发生在 4 个方向上。
```

**示例 3：**

```
输入：grid = [[0,2]]
输出：0
解释：因为 0 分钟时已经没有新鲜橘子了，所以答案就是 0 。
```

 

**提示：**

- `m == grid.length`
- `n == grid[i].length`
- `1 <= m, n <= 10`
- `grid[i][j]` 仅为 `0`、`1` 或 `2`



==**代码**==

```c++
class Solution {
public:
    int orangesRotting(vector<vector<int>>& grid) {
        int m = grid.size(), n = grid[0].size();
        queue<pair<int, int>> q;
        int num = 0;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (grid[i][j] == 1) {
                    num++;
                }
                if (grid[i][j] == 2) {
                    q.emplace(i, j);
                }
            }
        }
        if (num == 0) return 0;
        int step = 1;
        int dirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            int sz = q.size();
            for (int i = 0; i < sz; i++) {
                auto cur = q.front();
                q.pop();
                for (int j = 0; j < 4; j++) {
                    int x = cur.first + dirs[j][0];
                    int y = cur.second + dirs[j][1];
                    if (x < 0 || x >= m || y < 0 || y >= n || grid[x][y] != 1) continue;
                    q.emplace(x, y);
                    grid[x][y] = 2;
                    num--;
                    if (num == 0) return step;
                }
            }
            step++;
        }
        return -1;
    }
};
```



### 2101.[引爆最多的炸弹](https://leetcode.cn/problems/detonate-the-maximum-bombs/description/)

给你一个炸弹列表。一个炸弹的 **爆炸范围** 定义为以炸弹为圆心的一个圆。

炸弹用一个下标从 **0** 开始的二维整数数组 `bombs` 表示，其中 `bombs[i] = [xi, yi, ri]` 。`xi` 和 `yi` 表示第 `i` 个炸弹的 X 和 Y 坐标，`ri` 表示爆炸范围的 **半径** 。

你需要选择引爆 **一个** 炸弹。当这个炸弹被引爆时，**所有** 在它爆炸范围内的炸弹都会被引爆，这些炸弹会进一步将它们爆炸范围内的其他炸弹引爆。

给你数组 `bombs` ，请你返回在引爆 **一个** 炸弹的前提下，**最多** 能引爆的炸弹数目。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211215203134.png)

```
输入：bombs = [[2,1,3],[6,1,4]]
输出：2
解释：
上图展示了 2 个炸弹的位置和爆炸范围。
如果我们引爆左边的炸弹，右边的炸弹不会被影响。
但如果我们引爆右边的炸弹，两个炸弹都会爆炸。
所以最多能引爆的炸弹数目是 max(1, 2) = 2 。
```

**示例 2：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211215202665.png)

```
输入：bombs = [[1,1,5],[10,10,5]]
输出：1
解释：
引爆任意一个炸弹都不会引爆另一个炸弹。所以最多能引爆的炸弹数目为 1 。
```

**示例 3：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211215204030.png)

```
输入：bombs = [[1,2,3],[2,3,1],[3,4,2],[4,5,3],[5,6,4]]
输出：5
解释：
最佳引爆炸弹为炸弹 0 ，因为：
- 炸弹 0 引爆炸弹 1 和 2 。红色圆表示炸弹 0 的爆炸范围。
- 炸弹 2 引爆炸弹 3 。蓝色圆表示炸弹 2 的爆炸范围。
- 炸弹 3 引爆炸弹 4 。绿色圆表示炸弹 3 的爆炸范围。
所以总共有 5 个炸弹被引爆。
```

 

**提示：**

- `1 <= bombs.length <= 100`
- `bombs[i].length == 3`
- `1 <= xi, yi, ri <= 10^5`



==**代码**==

```c++
class Solution {
public:
    int maximumDetonation(vector<vector<int>>& bombs) {
        int n = bombs.size();
        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i == j) continue;
                if (pow(bombs[i][0] - bombs[j][0], 2) + pow(bombs[i][1] - bombs[j][1], 2) <= pow(bombs[i][2], 2)) {
                    graph[i].push_back(j);
                }
            }
        }
        int maxBombCount = 0;
        for (int i = 0; i < n; i++) {
            queue<int> q;
            vector<bool> visited(n);
            q.push(i);
            visited[i] = true;
            int bombCount = 0;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                bombCount++;
                for (int j = 0; j < graph[cur].size(); j++) {
                    int next = graph[cur][j];
                    if (visited[next]) continue;
                    q.push(next);
                    visited[next] = true;
                }
            }
            maxBombCount = max(maxBombCount, bombCount);
        }
        return maxBombCount;
    }
};
```



### 399.[除法求值](https://leetcode.cn/problems/evaluate-division/description/)

给你一个变量对数组 `equations` 和一个实数值数组 `values` 作为已知条件，其中 `equations[i] = [Ai, Bi]` 和 `values[i]` 共同表示等式 `Ai / Bi = values[i]` 。每个 `Ai` 或 `Bi` 是一个表示单个变量的字符串。

另有一些以数组 `queries` 表示的问题，其中 `queries[j] = [Cj, Dj]` 表示第 `j` 个问题，请你根据已知条件找出 `Cj / Dj = ?` 的结果作为答案。

返回 **所有问题的答案** 。如果存在某个无法确定的答案，则用 `-1.0` 替代这个答案。如果问题中出现了给定的已知条件中没有出现的字符串，也需要用 `-1.0` 替代这个答案。

**注意：**输入总是有效的。你可以假设除法运算中不会出现除数为 0 的情况，且不存在任何矛盾的结果。

**注意：**未在等式列表中出现的变量是未定义的，因此无法确定它们的答案。

 

**示例 1：**

```
输入：equations = [["a","b"],["b","c"]], values = [2.0,3.0], queries = [["a","c"],["b","a"],["a","e"],["a","a"],["x","x"]]
输出：[6.00000,0.50000,-1.00000,1.00000,-1.00000]
解释：
条件：a / b = 2.0, b / c = 3.0
问题：a / c = ?, b / a = ?, a / e = ?, a / a = ?, x / x = ?
结果：[6.0, 0.5, -1.0, 1.0, -1.0 ]
注意：x 是未定义的 => -1.0
```

**示例 2：**

```
输入：equations = [["a","b"],["b","c"],["bc","cd"]], values = [1.5,2.5,5.0], queries = [["a","c"],["c","b"],["bc","cd"],["cd","bc"]]
输出：[3.75000,0.40000,5.00000,0.20000]
```

**示例 3：**

```
输入：equations = [["a","b"]], values = [0.5], queries = [["a","b"],["b","a"],["a","c"],["x","y"]]
输出：[0.50000,2.00000,-1.00000,-1.00000]
```

 

**提示：**

- `1 <= equations.length <= 20`
- `equations[i].length == 2`
- `1 <= Ai.length, Bi.length <= 5`
- `values.length == equations.length`
- `0.0 < values[i] <= 20.0`
- `1 <= queries.length <= 20`
- `queries[i].length == 2`
- `1 <= Cj.length, Dj.length <= 5`
- `Ai, Bi, Cj, Dj` 由小写英文字母与数字组成



==**代码**==

```c++
class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values, vector<vector<string>>& queries) {
        int nodeCount = 0;
        unordered_map<string, int> nodeMap;
        for (auto& equation : equations) {
            if (!nodeMap.count(equation[0])) {
                nodeMap[equation[0]] = nodeCount;
                nodeCount++;
            }
            if (!nodeMap.count(equation[1])) {
                nodeMap[equation[1]] = nodeCount;
                nodeCount++;
            }
        }
        vector<vector<pair<int, double>>> edges(nodeCount);
        for (int i = 0; i < equations.size(); i++) {
            int left = nodeMap[equations[i][0]];
            int right = nodeMap[equations[i][1]];
            edges[left].emplace_back(right, values[i]);
            edges[right].emplace_back(left, 1.0 / values[i]);
        }
        vector<double> ans;
        for (auto& query : queries) {
            if (!nodeMap.count(query[0]) || !nodeMap.count(query[1])) {
                ans.emplace_back(-1.0);
                continue;
            }
            queue<pair<int, double>> q;
            vector<bool> visited(nodeCount);
            int left = nodeMap[query[0]];
            int right = nodeMap[query[1]];
            q.emplace(left, 1.0);
            visited[left] = true;
            bool found = false;
            while (!q.empty()) {
                auto [cur, result] = q.front();
                q.pop();
                if (cur == right) {
                    found = true;
                    ans.emplace_back(result);
                }
                for (auto& [next, val] : edges[cur]) {
                    if (visited[next]) continue;
                    q.emplace(next, result * val);
                    visited[next] = true;
                }
            }
            if (!found) {
                ans.emplace_back(-1.0);
            }
        }
        return ans;
    }
};
```



### 924.[尽量减少恶意软件的传播](https://leetcode.cn/problems/minimize-malware-spread/description/)

给出了一个由 `n` 个节点组成的网络，用 `n × n` 个邻接矩阵图 `graph` 表示。在节点网络中，当 `graph[i][j] = 1` 时，表示节点 `i` 能够直接连接到另一个节点 `j`。 

一些节点 `initial` 最初被恶意软件感染。只要两个节点直接连接，且其中至少一个节点受到恶意软件的感染，那么两个节点都将被恶意软件感染。这种恶意软件的传播将继续，直到没有更多的节点可以被这种方式感染。

假设 `M(initial)` 是在恶意软件停止传播之后，整个网络中感染恶意软件的最终节点数。

如果从 `initial` 中**移除某一节点**能够最小化 `M(initial)`， 返回该节点。如果有多个节点满足条件，就返回**索引最小**的节点。

请注意，如果某个节点已从受感染节点的列表 `initial` 中删除，它以后仍有可能因恶意软件传播而受到感染。

 



**示例 1：**

```
输入：graph = [[1,1,0],[1,1,0],[0,0,1]], initial = [0,1]
输出：0
```

**示例 2：**

```
输入：graph = [[1,0,0],[0,1,0],[0,0,1]], initial = [0,2]
输出：0
```

**示例 3：**

```
输入：graph = [[1,1,1],[1,1,1],[1,1,1]], initial = [1,2]
输出：1
```

 

**提示：**

- `n == graph.length`
- `n == graph[i].length`
- `2 <= n <= 300`
- `graph[i][j] == 0` 或 `1`.
- `graph[i][j] == graph[j][i]`
- `graph[i][i] == 1`
- `1 <= initial.length <= n`
- `0 <= initial[i] <= n - 1`
- `initial` 中所有整数均**不重复**



==**代码**==

```c++
class Solution {
public:
    int minMalwareSpread(vector<vector<int>>& graph, vector<int>& initial) {
        int n = graph.size();
        unordered_set<int> initialSet(initial.begin(), initial.end());
        sort(initial.begin(), initial.end());
        int targetNode = initial[0], maxReduce = 0;

        vector<bool> visited(n);
        for (int badNode : initial) {
            if (visited[badNode]) continue;
            queue<int> q;
            q.push(badNode);
            visited[badNode] = true;
            int nodeCount = 0, badNodeCount = 0;
            while (!q.empty()) {
                int cur = q.front();
                q.pop();
                nodeCount++;
                if (initialSet.count(cur)) {
                    badNodeCount++;
                }
                for (int i = 0; i < n; i++) {
                    if (visited[i]) continue;
                    if (graph[cur][i] == 0) continue;
                    q.push(i);
                    visited[i] = true;
                }
            }
            if (badNodeCount == 1) {
                if (nodeCount > maxReduce) {
                    maxReduce = nodeCount;
                    targetNode = badNode;
                }
            }
        }
        return targetNode;
    }
};
```



### 417.[太平洋大西洋水流问题](https://leetcode.cn/problems/pacific-atlantic-water-flow/description/)

有一个 `m × n` 的矩形岛屿，与 **太平洋** 和 **大西洋** 相邻。 **“太平洋”** 处于大陆的左边界和上边界，而 **“大西洋”** 处于大陆的右边界和下边界。

这个岛被分割成一个由若干方形单元格组成的网格。给定一个 `m x n` 的整数矩阵 `heights` ， `heights[r][c]` 表示坐标 `(r, c)` 上单元格 **高于海平面的高度** 。

岛上雨水较多，如果相邻单元格的高度 **小于或等于** 当前单元格的高度，雨水可以直接向北、南、东、西流向相邻单元格。水可以从海洋附近的任何单元格流入海洋。

返回网格坐标 `result` 的 **2D 列表** ，其中 `result[i] = [ri, ci]` 表示雨水从单元格 `(ri, ci)` 流动 **既可流向太平洋也可流向大西洋** 。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250211200411967.jpeg)

```
输入: heights = [[1,2,2,3,5],[3,2,3,4,4],[2,4,5,3,1],[6,7,1,4,5],[5,1,1,2,4]]
输出: [[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]]
```

**示例 2：**

```
输入: heights = [[2,1],[1,2]]
输出: [[0,0],[0,1],[1,0],[1,1]]
```

 

**提示：**

- `m == heights.length`
- `n == heights[r].length`
- `1 <= m, n <= 200`
- `0 <= heights[r][c] <= 10^5`



==**代码**==

```c++
class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        int m = heights.size(), n = heights[0].size();
        vector<vector<bool>> visitedP(m, vector<bool>(n));
        queue<pair<int, int>> qToP;
        for (int i = 0; i < m; i++) {
            visitedP[i][0] = true;
            qToP.emplace(i, 0);
        }
        for (int i = 1; i < n; i++) {
            visitedP[0][i] = true;
            qToP.emplace(0, i);
        }
        bfs(heights, qToP, visitedP);
        vector<vector<bool>> visitedA(m, vector<bool>(n));
        queue<pair<int, int>> qToA;
        for (int i = 0; i < m; i++) {
            visitedA[i][n-1] = true;
            qToA.emplace(i, n-1);
        }
        for (int i = 0; i < n - 1; i++) {
            visitedA[m-1][i] = true;
            qToA.emplace(m-1, i);
        }
        bfs(heights, qToA, visitedA);

        vector<vector<int>> ans;
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (visitedP[i][j] && visitedA[i][j]) {
                    ans.emplace_back(vector<int>{i ,j});
                }
            }
        }
        return ans;
    }
     void bfs(vector<vector<int>>& heights, queue<pair<int, int>>& q, vector<vector<bool>>& visited) {
        int m = heights.size(), n = heights[0].size();
        vector<pair<int, int>> dirs = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
        while (!q.empty()) {
            auto [x, y] = q.front();
            q.pop();
            for (auto& [dx, dy] : dirs) {
                int nx = x + dx;
                int ny = y + dy;
                if (nx < 0 || nx >= m || ny < 0 || ny >= n || visited[nx][ny] || heights[nx][ny] < heights[x][y]) continue;
                q.emplace(nx, ny);
                visited[nx][ny] = true;
            }
        }
    }
};
```



### 365.[水壶问题](https://leetcode.cn/problems/water-and-jug-problem/description/)

有两个水壶，容量分别为 `x` 和 `y` 升。水的供应是无限的。确定是否有可能使用这两个壶准确得到 `target` 升。

你可以：

- 装满任意一个水壶
- 清空任意一个水壶
- 将水从一个水壶倒入另一个水壶，直到接水壶已满，或倒水壶已空。

 

**示例 1:** 

```
输入: x = 3,y = 5,target = 4
输出: true
解释：
按照以下步骤操作，以达到总共 4 升水：
1. 装满 5 升的水壶(0, 5)。
2. 把 5 升的水壶倒进 3 升的水壶，留下 2 升(3, 2)。
3. 倒空 3 升的水壶(0, 2)。
4. 把 2 升水从 5 升的水壶转移到 3 升的水壶(2, 0)。
5. 再次加满 5 升的水壶(2, 5)。
6. 从 5 升的水壶向 3 升的水壶倒水直到 3 升的水壶倒满。5 升的水壶里留下了 4 升水(3, 4)。
7. 倒空 3 升的水壶。现在，5 升的水壶里正好有 4 升水(0, 4)。
参考：来自著名的 "Die Hard"
```

**示例 2:**

```
输入: x = 2, y = 6, target = 5
输出: false
```

**示例 3:**

```
输入: x = 1, y = 2, target = 3
输出: true
解释：同时倒满两个水壶。现在两个水壶中水的总量等于 3。
```

 

**提示:**

- `1 <= x, y, target <= 10^3`



==**代码**==

```c++
class Solution {
public:
    bool canMeasureWater(int x, int y, int target) {
        if (target > x + y) return false;
        queue<pair<int, int>> q;
        unordered_set<long long> visited;
        q.emplace(0, 0);
        visited.insert(0);
        while (!q.empty()) {
            auto [curx, cury] = q.front();
            cout << curx << " " << cury << endl;
            q.pop();
            if (curx == target || cury == target || curx + cury == target) return true;

            vector<pair<int, int>> temp;
            temp.emplace_back(x, cury);
            temp.emplace_back(curx, y);
            temp.emplace_back(0, cury);
            temp.emplace_back(curx, 0);
            temp.emplace_back(
                curx - min(curx, y - cury),
                cury + min(curx, y - cury)
            );
            temp.emplace_back(
                curx + min(cury, x - curx),
                cury - min(cury, x - curx)
            );
            for (auto& [nx, ny] : temp) {
                long long hash = nx * (y + 1) + ny;
                if (visited.count(hash)) continue;
                q.emplace(nx, ny);
                visited.insert(hash);
            }
        }
        return false;
    }
};
```

