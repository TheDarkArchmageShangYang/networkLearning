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
- 773.[滑动谜题](https://leetcode.cn/problems/sliding-puzzle/description/)
- 752.[打开转盘锁](https://leetcode.cn/problems/open-the-lock/description/)



841,1306,433最基础的BFS

773,752把问题抽象成BFS



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

