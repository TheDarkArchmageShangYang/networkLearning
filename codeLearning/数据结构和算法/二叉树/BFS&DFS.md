# 基本思路

## 基本思路

二叉树的问题通常需要遍历整棵树,可以考虑常见的遍历方法:

- 动态规划
  - 将复杂问题分解为子问题
  - 主要关注子树
- 回溯算法
  - 与回溯算法基本相同,代码结构也基本相同,不需要刻意区分,以下全使用DFS
  - 主要关注树枝(根节点与左右子树的关系,而不是其中任何一个节点)
- 深度优先搜索(DFS)
  - 主要关注当前节点
- 广度优先搜索(BFS)
  - 层序遍历二叉树

面对一个问题:

1.判断使用DFS/动态规划来写递归

- 是否能够通过一次遍历二叉树来完成
- 是否能够将原问题分解为多个子问题

2.判断在==前序/中序/后序/层序==中写代码

前序只能获取当前节点的数据

中序可以获取当前节点和左子树的数据

后序可以获取当前节点和左右子树的数据

所以如果题目中需要用到子树,一般在后序修改代码,不需要子树则在前序修改代码

自顶向下DFS和自底向上DFS的区别:

- 自顶向下先处理当前节点,再递归子节点(前序位置)
- 自底向上先递归子节点,再处理当前节点(后序位置)

递归与以上的区别:

- 递归是以上算法的一种实现方式,是思想而不是算法
- 以上算法可以不使用递归,而使用迭代实现.只是很多情况下递归的代码更简洁明了

## 题单

1. DFS
   - 226.[翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/description/)
   - 257.[二叉树的所有路径](https://leetcode.cn/problems/binary-tree-paths/description/)
   - 129.[求根节点到叶节点数字之和](https://leetcode.cn/problems/sum-root-to-leaf-numbers/description/)
   - 988.[从叶结点开始的最小字符串](https://leetcode.cn/problems/smallest-string-starting-from-leaf/description/)
   - 1022.[从根到叶的二进制数之和](https://leetcode.cn/problems/sum-of-root-to-leaf-binary-numbers/description/)
   - 1457.[二叉树中的伪回文路径](https://leetcode.cn/problems/pseudo-palindromic-paths-in-a-binary-tree/description/)
   - 404.[左叶子之和](https://leetcode.cn/problems/sum-of-left-leaves/description/)
   - 1448.[统计二叉树中好节点的数目](https://leetcode.cn/problems/count-good-nodes-in-binary-tree/description/)
   - 971.[翻转二叉树以匹配先序遍历](https://leetcode.cn/problems/flip-binary-tree-to-match-preorder-traversal/description/)
   - 987.[二叉树的垂序遍历](https://leetcode.cn/problems/vertical-order-traversal-of-a-binary-tree/description/)
   - 993.[二叉树的堂兄弟节点](https://leetcode.cn/problems/cousins-in-binary-tree/description/)
   - 1315.[祖父节点值为偶数的节点和](https://leetcode.cn/problems/sum-of-nodes-with-even-valued-grandparent/description/)
   - 437.[路径总和III](https://leetcode.cn/problems/path-sum-iii/description/)
   - 1261.[在受污染的二叉树中查找元素](https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree/description/)
   - 386.[字典序排数](https://leetcode.cn/problems/lexicographical-numbers/description/)
   - 1104.[二叉树寻路](https://leetcode.cn/problems/path-in-zigzag-labelled-binary-tree/description/)
   - 1145.[二叉树着色游戏](https://leetcode.cn/problems/binary-tree-coloring-game/description/)
2. BFS
   - 513.[找树左下角的值](https://leetcode.cn/problems/find-bottom-left-tree-value/description/)
   - 199.[二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/description/)



226,257,129,988,1022,1457,404相似,均为遍历二叉树的所有路径

971需要根据先序遍历进行处理

987需要记录每个节点的深度,宽度,值

993,1315需要记录父节点/祖父节点

437:二叉树+前缀和

1261:二叉树+哈希表

386:多叉树+字典序

1104:二叉树寻路

1145:二叉树+贪心

## 深度优先搜索

### 基本模板

DFS题目可以以`二叉树的所有路径`为模板,在`ans`,`path`,`叶子节点的特殊行动`等部分进行修改

```c++
class Solution {
public:
    vector<string> ans;
    vector<string> function(TreeNode* root) {
        traverse(root, "");
        return ans;
    }
    void traverse(TreeNode* root, string path) {
        if (root == nullptr) {
            return;
        }
        path += to_string(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(path);
            return;
        }
        path += "->";
        traverse(root->left, path);
        traverse(root->right, path);
    }
};
```



### 例题

#### 226.[翻转二叉树](https://leetcode.cn/problems/invert-binary-tree/description/)

给你一棵二叉树的根节点 `root` ，翻转这棵二叉树，并返回其根节点。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241218221646831.jpeg)

```
输入：root = [4,2,7,1,3,6,9]
输出：[4,7,2,9,6,3,1]
```

**示例 2：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241218221646813.jpeg)

```
输入：root = [2,1,3]
输出：[2,3,1]
```

**示例 3：**

```
输入：root = []
输出：[]
```

 

**提示：**

- 树中节点数目范围在 `[0, 100]` 内
- `-100 <= Node.val <= 100`



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        traverse(root);
        return root;
    }
    void traverse(TreeNode* root) {
        if (root == nullptr) return;
        
        TreeNode* tmp = root->left;
        root->left = root->right;
        root->right = tmp;
        
        traverse(root->left);
        traverse(root->right);
    }
};
```



分解问题

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* invertTree(TreeNode* root) {
        if (root == nullptr) {
            return root;
        }
        TreeNode* left = invertTree(root->left);
        TreeNode* right = invertTree(root->right);

        root->left = right;
        root->right = left;
        return root;
    }
};
```



#### 257.[二叉树的所有路径](https://leetcode.cn/problems/binary-tree-paths/description/)

给你一个二叉树的根节点 `root` ，按 **任意顺序** ，返回所有从根节点到叶子节点的路径。

**叶子节点** 是指没有子节点的节点。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241222193542316.jpeg)

```
输入：root = [1,2,3,null,5]
输出：["1->2->5","1->3"]
```

**示例 2：**

```
输入：root = [1]
输出：["1"]
```

 

**提示：**

- 树中节点的数目在范围 `[1, 100]` 内
- `-100 <= Node.val <= 100`



==**代码**==

1. 首先考虑这道题用dp还是dfs,两种方法都可以.考虑到dp会使用大量`vector<string>`,所以选择用dfs

2. 然后考虑在什么位置记录当前节点,由于左右子树需要知道父亲节点的数字,所以在前序位置记录当前节点

3. 考虑dfs终止条件,除了常规的遍历空指针时,还需要在访问到叶子节点时记录整条路径

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<string> ans;
    vector<string> binaryTreePaths(TreeNode* root) {
        traverse(root, "");
        return ans;
    }
    void traverse(TreeNode* root, string path) {
        if (root == nullptr) {
            return;
        }
        path += to_string(root->val);
        if (root->left == nullptr && root->right == nullptr) {
            ans.push_back(path);
            return;
        }
        path += "->";
        traverse(root->left, path);
        traverse(root->right, path);
    }
};
```



#### 129.[求根节点到叶节点数字之和](https://leetcode.cn/problems/sum-root-to-leaf-numbers/description/)

给你一个二叉树的根节点 `root` ，树中每个节点都存放有一个 `0` 到 `9` 之间的数字。

每条从根节点到叶节点的路径都代表一个数字：

- 例如，从根节点到叶节点的路径 `1 -> 2 -> 3` 表示数字 `123` 。

计算从根节点到叶节点生成的 **所有数字之和** 。

**叶节点** 是指没有子节点的节点。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241222200133967.jpeg)

```
输入：root = [1,2,3]
输出：25
解释：
从根到叶子节点路径 1->2 代表数字 12
从根到叶子节点路径 1->3 代表数字 13
因此，数字总和 = 12 + 13 = 25
```

**示例 2：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241222200133991.jpeg)

```
输入：root = [4,9,0,5,1]
输出：1026
解释：
从根到叶子节点路径 4->9->5 代表数字 495
从根到叶子节点路径 4->9->1 代表数字 491
从根到叶子节点路径 4->0 代表数字 40
因此，数字总和 = 495 + 491 + 40 = 1026
```

 

**提示：**

- 树中节点的数目在范围 `[1, 1000]` 内
- `0 <= Node.val <= 9`
- 树的深度不超过 `10`



==**代码**==

与257基本一致

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    int sumNumbers(TreeNode* root) {
        traverse(root, 0);
        return ans;
    }
    void traverse(TreeNode* root, int sum) {
        if (root == nullptr) {
            return;
        }
        sum = sum * 10 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            ans += sum;
            return;
        } 
        traverse(root->left, sum);
        traverse(root->right, sum);
    }
};
```



#### 988.[从叶结点开始的最小字符串](https://leetcode.cn/problems/smallest-string-starting-from-leaf/description/)

给定一颗根结点为 `root` 的二叉树，树中的每一个结点都有一个 `[0, 25]` 范围内的值，分别代表字母 `'a'` 到 `'z'`。

返回 ***按字典序最小** 的字符串，该字符串从这棵树的一个叶结点开始，到根结点结束*。

> 注**：**字符串中任何较短的前缀在 **字典序上** 都是 **较小** 的：
>
> - 例如，在字典序上 `"ab"` 比 `"aba"` 要小。叶结点是指没有子结点的结点。 

节点的叶节点是没有子节点的节点。

 



**示例 1：**

**<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241223022025797.png" alt="img" style="zoom:50%;" />**

```
输入：root = [0,1,2,3,4,3,4]
输出："dba"
```

**示例 2：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241223022027542.png" alt="img" style="zoom:50%;" />

```
输入：root = [25,1,3,1,3,0,2]
输出："adz"
```

**示例 3：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241223022027695.png" alt="img" style="zoom:50%;" />

```
输入：root = [2,2,1,null,1,0,null,0]
输出："abc"
```

 

**提示：**

- 给定树的结点数在 `[1, 8500]` 范围内
- `0 <= Node.val <= 25`



==**代码**==

与257基本相同

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    string ans;
    string smallestFromLeaf(TreeNode* root) {
        traverse(root, "");
        return ans;
    }
    void traverse(TreeNode* root, string str) {
        if (root == nullptr) {
            return;
        }
        str += 'a' + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            reverse(str.begin(), str.end());
            if (ans.empty() || str.compare(ans) <= 0) {
                ans = str;
            }
            return;
        }
        traverse(root->left, str);
        traverse(root->right, str);

    }
};
```



#### 1022.[从根到叶的二进制数之和](https://leetcode.cn/problems/sum-of-root-to-leaf-binary-numbers/description/)

给出一棵二叉树，其上每个结点的值都是 `0` 或 `1` 。每一条从根到叶的路径都代表一个从最高有效位开始的二进制数。

- 例如，如果路径为 `0 -> 1 -> 1 -> 0 -> 1`，那么它表示二进制数 `01101`，也就是 `13` 。

对树上的每一片叶子，我们都要找出从根到该叶子的路径所表示的数字。

返回这些数字之和。题目数据保证答案是一个 **32 位** 整数。

 

**示例 1：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241223172237866.png" alt="img" style="zoom:50%;" />

```
输入：root = [1,0,1,0,1,0,1]
输出：22
解释：(100) + (101) + (110) + (111) = 4 + 5 + 6 + 7 = 22
```

**示例 2：**

```
输入：root = [0]
输出：0
```

 

**提示：**

- 树中的节点数在 `[1, 1000]` 范围内
- `Node.val` 仅为 `0` 或 `1` 



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    int sumRootToLeaf(TreeNode* root) {
        traverse(root, 0);
        return ans;
    }
    void traverse(TreeNode* root, int sum) {
        if (root == nullptr) {
            return;
        }
        sum = sum * 2 + root->val;
        if (root->left == nullptr && root->right == nullptr) {
            ans += sum;
        }
        traverse(root->left, sum);
        traverse(root->right, sum);
    }
};
```



#### 1457.[二叉树中的伪回文路径](https://leetcode.cn/problems/pseudo-palindromic-paths-in-a-binary-tree/description/)

给你一棵二叉树，每个节点的值为 1 到 9 。我们称二叉树中的一条路径是 「**伪回文**」的，当它满足：路径经过的所有节点值的排列中，存在一个回文序列。

请你返回从根到叶子节点的所有路径中 **伪回文** 路径的数目。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241223175541072.png)

```
输入：root = [2,3,1,3,1,null,1]
输出：2 
解释：上图为给定的二叉树。总共有 3 条从根到叶子的路径：红色路径 [2,3,3] ，绿色路径 [2,1,1] 和路径 [2,3,1] 。
     在这些路径中，只有红色和绿色的路径是伪回文路径，因为红色路径 [2,3,3] 存在回文排列 [3,2,3] ，绿色路径 [2,1,1] 存在回文排列 [1,2,1] 。
```

**示例 2：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241223175541052.png)**

```
输入：root = [2,1,1,1,3,null,null,null,null,null,1]
输出：1 
解释：上图为给定二叉树。总共有 3 条从根到叶子的路径：绿色路径 [2,1,1] ，路径 [2,1,3,1] 和路径 [2,1] 。
     这些路径中只有绿色路径是伪回文路径，因为 [2,1,1] 存在回文排列 [1,2,1] 。
```

**示例 3：**

```
输入：root = [9]
输出：1
```

 

**提示：**

- 给定二叉树的节点数目在范围 `[1, 105]` 内
- `1 <= Node.val <= 9`



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    unordered_map<int, int> hash_map;
    int pseudoPalindromicPaths (TreeNode* root) {
        traverse(root);
        return ans;
    }
    void traverse(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        hash_map[root->val]++;
        if (root->left == nullptr && root->right == nullptr) {
            int count = 0;
            for (auto& it : hash_map) {
                if (it.second % 2 == 1) count++;
            }
            if (count <= 1) ans++;
        }
        traverse(root->left);
        traverse(root->right);
        hash_map[root->val]--;
    }
};
```



#### 404.[左叶子之和](https://leetcode.cn/problems/sum-of-left-leaves/description/)

给定二叉树的根节点 `root` ，返回所有左叶子之和。

 

**示例 1：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241225141556485.jpeg" alt="img" style="zoom:67%;" />

```
输入: root = [3,9,20,null,null,15,7] 
输出: 24 
解释: 在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24
```

**示例 2:**

```
输入: root = [1]
输出: 0
```

 

**提示:**

- 节点数在 `[1, 1000]` 范围内
- `-1000 <= Node.val <= 1000`



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    int sumOfLeftLeaves(TreeNode* root) {
        traverse(root);
        return ans;
    }
    void traverse(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr) {
            ans += root->left->val;
        }
        traverse(root->left);
        traverse(root->right);
    }
};
```



#### 1448.[统计二叉树中好节点的数目](https://leetcode.cn/problems/count-good-nodes-in-binary-tree/description/)

给你一棵根为 `root` 的二叉树，请你返回二叉树中好节点的数目。

「好节点」X 定义为：从根到该节点 X 所经过的节点中，没有任何节点的值大于 X 的值。

 

**示例 1：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228020259582.png)**

```
输入：root = [3,1,4,3,null,1,5]
输出：4
解释：图中蓝色节点为好节点。
根节点 (3) 永远是个好节点。
节点 4 -> (3,4) 是路径中的最大值。
节点 5 -> (3,4,5) 是路径中的最大值。
节点 3 -> (3,1,3) 是路径中的最大值。
```

**示例 2：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228020259603.png)**

```
输入：root = [3,3,null,4,2]
输出：3
解释：节点 2 -> (3, 3, 2) 不是好节点，因为 "3" 比它大。
```

**示例 3：**

```
输入：root = [1]
输出：1
解释：根节点是好节点。
```

 

**提示：**

- 二叉树中节点数目范围是 `[1, 10^5]` 。
- 每个节点权值的范围是 `[-10^4, 10^4]` 。



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    int goodNodes(TreeNode* root) {
        traverse(root, INT_MIN);
        return ans;
    }
    void traverse(TreeNode* root, int maxNum) {
        if (root == nullptr) {
            return;
        }
        if (maxNum <= root->val) {
            ans++;
        }
        maxNum = max(maxNum, root->val);
        traverse(root->left, maxNum);
        traverse(root->right, maxNum);
    }
};
```



#### 971.[翻转二叉树以匹配先序遍历](https://leetcode.cn/problems/flip-binary-tree-to-match-preorder-traversal/description/)

给你一棵二叉树的根节点 `root` ，树中有 `n` 个节点，每个节点都有一个不同于其他节点且处于 `1` 到 `n` 之间的值。

另给你一个由 `n` 个值组成的行程序列 `voyage` ，表示 **预期** 的二叉树 [**先序遍历**](https://baike.baidu.com/item/先序遍历/6442839?fr=aladdin) 结果。

通过交换节点的左右子树，可以 **翻转** 该二叉树中的任意节点。例，翻转节点 1 的效果如下：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241226005832266.jpeg)

请翻转 **最少** 的树中节点，使二叉树的 **先序遍历** 与预期的遍历行程 `voyage` **相匹配** 。 

如果可以，则返回 **翻转的** 所有节点的值的列表。你可以按任何顺序返回答案。如果不能，则返回列表 `[-1]`。

 

**示例 1：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241226005832292.png" alt="img" style="zoom:67%;" />

```
输入：root = [1,2], voyage = [2,1]
输出：[-1]
解释：翻转节点无法令先序遍历匹配预期行程。
```

**示例 2：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241226005832062.png" alt="img" style="zoom:67%;" />

```
输入：root = [1,2,3], voyage = [1,3,2]
输出：[1]
解释：交换节点 2 和 3 来翻转节点 1 ，先序遍历可以匹配预期行程。
```

**示例 3：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241226005832062.png" alt="img" style="zoom:67%;" />

```
输入：root = [1,2,3], voyage = [1,2,3]
输出：[]
解释：先序遍历已经匹配预期行程，所以不需要翻转节点。
```

 

**提示：**

- 树中的节点数目为 `n`
- `n == voyage.length`
- `1 <= n <= 100`
- `1 <= Node.val, voyage[i] <= n`
- 树中的所有值 **互不相同**
- `voyage` 中的所有值 **互不相同**



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> ans;
    vector<int> voyage;
    int index = 0;
    int success = 1;
    vector<int> flipMatchVoyage(TreeNode* root, vector<int>& voyage) {
        this->voyage = voyage;
        traverse(root);
        return success == 1 ? ans : vector<int>{-1};
    }
    void traverse(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        if (root->val != voyage[index++]) {
            success = 0;
            return;
        }
        if (root->left != nullptr && root->left->val != voyage[index]) {
            TreeNode* tmp = root->left;
            root->left = root->right;
            root->right = tmp;
            ans.push_back(root->val);
        }
        traverse(root->left);
        traverse(root->right);
    }
};
```



#### 987.[二叉树的垂序遍历](https://leetcode.cn/problems/vertical-order-traversal-of-a-binary-tree/description/)

给你二叉树的根结点 `root` ，请你设计算法计算二叉树的 **垂序遍历** 序列。

对位于 `(row, col)` 的每个结点而言，其左右子结点分别位于 `(row + 1, col - 1)` 和 `(row + 1, col + 1)` 。树的根结点位于 `(0, 0)` 。

二叉树的 **垂序遍历** 从最左边的列开始直到最右边的列结束，按列索引每一列上的所有结点，形成一个按出现位置从上到下排序的有序列表。如果同行同列上有多个结点，则按结点的值从小到大进行排序。

返回二叉树的 **垂序遍历** 序列。

 

**示例 1：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241227002510845.jpeg" alt="img" style="zoom:80%;" />

```
输入：root = [3,9,20,null,null,15,7]
输出：[[9],[3,15],[20],[7]]
解释：
列 -1 ：只有结点 9 在此列中。
列  0 ：只有结点 3 和 15 在此列中，按从上到下顺序。
列  1 ：只有结点 20 在此列中。
列  2 ：只有结点 7 在此列中。
```

**示例 2：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241227002510861.jpeg" alt="img" style="zoom:80%;" />

```
输入：root = [1,2,3,4,5,6,7]
输出：[[4],[2],[1,5,6],[3],[7]]
解释：
列 -2 ：只有结点 4 在此列中。
列 -1 ：只有结点 2 在此列中。
列  0 ：结点 1 、5 和 6 都在此列中。
          1 在上面，所以它出现在前面。
          5 和 6 位置都是 (2, 0) ，所以按值从小到大排序，5 在 6 的前面。
列  1 ：只有结点 3 在此列中。
列  2 ：只有结点 7 在此列中。
```

**示例 3：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241227002510619.jpeg" alt="img" style="zoom:80%;" />

```
输入：root = [1,2,3,4,6,5,7]
输出：[[4],[2],[1,5,6],[3],[7]]
解释：
这个示例实际上与示例 2 完全相同，只是结点 5 和 6 在树中的位置发生了交换。
因为 5 和 6 的位置仍然相同，所以答案保持不变，仍然按值从小到大排序。
```

 

**提示：**

- 树中结点数目总数在范围 `[1, 1000]` 内
- `0 <= Node.val <= 1000`



==**代码**==

```c++
class Solution {
public:
    map<int, map<int, vector<int>>> hash_map;
    vector<vector<int>> verticalTraversal(TreeNode* root) {
        traverse(root, 0, 0);
        vector<vector<int>> ans;
        for (auto& [width, depth_map] : hash_map) {
            vector<int> column;
            for (auto& [depth, values] : depth_map) {
                sort(values.begin(), values.end());
                column.insert(column.end(), values.begin(), values.end());
            }
            ans.push_back(column);
        }
        return ans;
    }

private:
    void traverse(TreeNode* root, int width, int depth) {
        if (root == nullptr) {
            return;
        }

        hash_map[width][depth].push_back(root->val);
        traverse(root->left, width - 1, depth + 1);
        traverse(root->right, width + 1, depth + 1);
    }
};
```



#### 993.[二叉树的堂兄弟节点](https://leetcode.cn/problems/cousins-in-binary-tree/description/)

在二叉树中，根节点位于深度 `0` 处，每个深度为 `k` 的节点的子节点位于深度 `k+1` 处。

如果二叉树的两个节点深度相同，但 **父节点不同** ，则它们是一对*堂兄弟节点*。

我们给出了具有唯一值的二叉树的根节点 `root` ，以及树中两个不同节点的值 `x` 和 `y` 。

只有与值 `x` 和 `y` 对应的节点是堂兄弟节点时，才返回 `true` 。否则，返回 `false`。

 

**示例 1：
![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241227004603597.png)**

```
输入：root = [1,2,3,4], x = 4, y = 3
输出：false
```

**示例 2：
![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241227004603116.png)**

```
输入：root = [1,2,3,null,4,null,5], x = 5, y = 4
输出：true
```

**示例 3：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241227004603360.png)**

```
输入：root = [1,2,3,null,4], x = 2, y = 3
输出：false
```

 

**提示：**

- 二叉树的节点数介于 `2` 到 `100` 之间。
- 每个节点的值都是唯一的、范围为 `1` 到 `100` 的整数。



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int xdepth = 0, ydepth = 0;
    TreeNode* xparent = nullptr, * yparent = nullptr;
    bool isCousins(TreeNode* root, int x, int y) {
        traverse(root, nullptr, 0, x, y);
        if (xdepth == ydepth && xparent != yparent) {
            return true;
        }
        return false;
    }
    void traverse(TreeNode* root, TreeNode* parent, int depth, int x, int y) {
        if (root == nullptr) {
            return;
        }
        if (root->val == x) {
            xdepth = depth;
            xparent = parent;
        } else if (root->val == y) {
            ydepth = depth;
            yparent = parent;
        }
        traverse(root->left, root, depth + 1, x, y);
        traverse(root->right, root, depth + 1, x, y);
    }
};
```



#### 1315.[祖父节点值为偶数的节点和](https://leetcode.cn/problems/sum-of-nodes-with-even-valued-grandparent/description/)

给你一棵二叉树，请你返回满足以下条件的所有节点的值之和：

- 该节点的祖父节点的值为偶数。（一个节点的祖父节点是指该节点的父节点的父节点。）

如果不存在祖父节点值为偶数的节点，那么返回 `0` 。

 

**示例：**

**<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241227005733344.png" alt="img" style="zoom:80%;" />**

```
输入：root = [6,7,8,2,7,1,3,9,null,1,4,null,null,null,5]
输出：18
解释：图中红色节点的祖父节点的值为偶数，蓝色节点为这些红色节点的祖父节点。
```

 

**提示：**

- 树中节点的数目在 `1` 到 `10^4` 之间。
- 每个节点的值在 `1` 到 `100` 之间。



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    int sumEvenGrandparent(TreeNode* root) {
        traverse(root, nullptr, nullptr);
        return ans;
    }
    void traverse(TreeNode* root, TreeNode* parent, TreeNode* grandParent) {
        if (root == nullptr) {
            return;
        }
        if (grandParent != nullptr && grandParent->val % 2 == 0) {
            ans += root->val;
        }
        traverse(root->left, root, parent);
        traverse(root->right, root, parent);
    }
};
```



#### 437.[路径总和III](https://leetcode.cn/problems/path-sum-iii/description/)

给定一个二叉树的根节点 `root` ，和一个整数 `targetSum` ，求该二叉树里节点值之和等于 `targetSum` 的 **路径** 的数目。

**路径** 不需要从根节点开始，也不需要在叶子节点结束，但是路径方向必须是向下的（只能从父节点到子节点）。

 

**示例 1：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228025247976.jpeg" alt="img" style="zoom:67%;" />

```
输入：root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
输出：3
解释：和等于 8 的路径有 3 条，如图所示。
```

**示例 2：**

```
输入：root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
输出：3
```

 

**提示:**

- 二叉树的节点个数的范围是 `[0,1000]`
- `-10^9 <= Node.val <= 10^9` 
- `-1000 <= targetSum <= 1000`



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int ans = 0;
    long long sum = 0;
    unordered_map<long long, int> sums;
    int pathSum(TreeNode* root, int targetSum) {
        sums[0] = 1;
        traverse(root, targetSum);
        return ans;
    }
    void traverse(TreeNode* root, int targetSum) {
        if (root == nullptr) {
            return;
        }
        sum += root->val;
        ans += sums[sum - targetSum];
        sums[sum]++;
        traverse(root->left, targetSum);
        traverse(root->right, targetSum);
        sums[sum]--;
        sum -= root->val;
    }
};
```

 

#### 1261.[在受污染的二叉树中查找元素](https://leetcode.cn/problems/find-elements-in-a-contaminated-binary-tree/description/)

给出一个满足下述规则的二叉树：

1. `root.val == 0`
2. 如果 `treeNode.val == x` 且 `treeNode.left != null`，那么 `treeNode.left.val == 2 * x + 1`
3. 如果 `treeNode.val == x` 且 `treeNode.right != null`，那么 `treeNode.right.val == 2 * x + 2`

现在这个二叉树受到「污染」，所有的 `treeNode.val` 都变成了 `-1`。

请你先还原二叉树，然后实现 `FindElements` 类：

- `FindElements(TreeNode* root)` 用受污染的二叉树初始化对象，你需要先把它还原。
- `bool find(int target)` 判断目标值 `target` 是否存在于还原后的二叉树中并返回结果。

 

**示例 1：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228165936084.jpeg)**

```
输入：
["FindElements","find","find"]
[[[-1,null,-1]],[1],[2]]
输出：
[null,false,true]
解释：
FindElements findElements = new FindElements([-1,null,-1]); 
findElements.find(1); // return False 
findElements.find(2); // return True 
```

**示例 2：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228165936061.jpeg)**

```
输入：
["FindElements","find","find","find"]
[[[-1,-1,-1,-1,-1]],[1],[3],[5]]
输出：
[null,true,true,false]
解释：
FindElements findElements = new FindElements([-1,-1,-1,-1,-1]);
findElements.find(1); // return True
findElements.find(3); // return True
findElements.find(5); // return False
```

**示例 3：**

**<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228165936077.jpeg" alt="img" style="zoom:80%;" />**

```
输入：
["FindElements","find","find","find","find"]
[[[-1,null,-1,-1,null,-1]],[2],[3],[4],[5]]
输出：
[null,true,false,false,true]
解释：
FindElements findElements = new FindElements([-1,null,-1,-1,null,-1]);
findElements.find(2); // return True
findElements.find(3); // return False
findElements.find(4); // return False
findElements.find(5); // return True
```

 

**提示：**

- `TreeNode.val == -1`
- 二叉树的高度不超过 `20`
- 节点的总数在 `[1, 10^4]` 之间
- 调用 `find()` 的总次数在 `[1, 10^4]` 之间
- `0 <= target <= 10^6`



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class FindElements {
public:
    unordered_set<int> valSet;
    FindElements(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        root->val = 0;
        valSet.insert(root->val);
        traverse(root);
    }

    void traverse(TreeNode* root) {
        if (root == nullptr) {
            return;
        }
        valSet.insert(root->val);
        if (root->left != nullptr) {
            root->left->val = 2 * root->val + 1;
        }
        if (root->right != nullptr) {
            root->right->val = 2 * root->val + 2;
        }
        traverse(root->left);
        traverse(root->right);
    }
    
    bool find(int target) {
        return valSet.count(target);
    }
};

/**
 * Your FindElements object will be instantiated and called as such:
 * FindElements* obj = new FindElements(root);
 * bool param_1 = obj->find(target);
 */
```



#### 386.[字典序排数](https://leetcode.cn/problems/lexicographical-numbers/description/)

给你一个整数 `n` ，按字典序返回范围 `[1, n]` 内所有整数。

你必须设计一个时间复杂度为 `O(n)` 且使用 `O(1)` 额外空间的算法。

 

**示例 1：**

```
输入：n = 13
输出：[1,10,11,12,13,2,3,4,5,6,7,8,9]
```

**示例 2：**

```
输入：n = 2
输出：[1,2]
```

 

**提示：**

- `1 <= n <= 5 * 10^4`



==**代码**==

想象如下多叉树,每个节点有0~9共10个子节点,字典序就是该多叉树的前序遍历结果

![image-20241228172115672](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228172115759.png)

```c++
class Solution {
public:
    vector<int> ans;
    vector<int> lexicalOrder(int n) {
        for (int i = 1; i < 10; i++) {
            dfs(i, n);
        }
        return ans;
    }
    void dfs(int root, int n) {
        if (root > n) {
            return;
        }
        ans.push_back(root);
        for (int i = root * 10; i < root * 10 + 10; i++) {
            dfs(i, n);
        }
    }
};
```



#### 1104.[二叉树寻路](https://leetcode.cn/problems/path-in-zigzag-labelled-binary-tree/description/)

在一棵无限的二叉树上，每个节点都有两个子节点，树中的节点 **逐行** 依次按 “之” 字形进行标记。

如下图所示，在奇数行（即，第一行、第三行、第五行……）中，按从左到右的顺序进行标记；

而偶数行（即，第二行、第四行、第六行……）中，按从右到左的顺序进行标记。

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241229165927721.png)

给你树上某一个节点的标号 `label`，请你返回从根节点到该标号为 `label` 节点的路径，该路径是由途经的节点标号所组成的。

 

**示例 1：**

```
输入：label = 14
输出：[1,3,4,14]
```

**示例 2：**

```
输入：label = 26
输出：[1,2,6,10,26]
```

 

**提示：**

- `1 <= label <= 10^6`



==**代码**==

如果没有"之"字形排列,只要不断`label=label/2`,最后反转数组就行了

由于改变了数字的排列顺序,所以需要找规律

以`label=13`为例,13的原父节点为6,现父节点为5

以`label=14`为例,14的原父节点为7,现父节点为4

所以规律为`label原父节点+label现父节点=label上一行的最大数+最小数=(pow(2,depth-1)-1)+pow(2,depth-2)`

![image-20241229170320313](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241229170320405.png)

```c++
class Solution {
public:
    vector<int> ans;
    vector<int> pathInZigZagTree(int label) {
        vector<int> ans;
        int depth = 1, num = 1;
        while (num * 2 <= label) {
            depth++;
            num *= 2;
        }
        while (label >= 1) {
            ans.push_back(label);
            label = pow(2, depth - 1) - 1 - (label / 2 - pow(2, depth - 2));
            depth--;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```



#### 1145.[二叉树着色游戏](https://leetcode.cn/problems/binary-tree-coloring-game/description/)

有两位极客玩家参与了一场「二叉树着色」的游戏。游戏中，给出二叉树的根节点 `root`，树上总共有 `n` 个节点，且 `n` 为奇数，其中每个节点上的值从 `1` 到 `n` 各不相同。

最开始时：

- 「一号」玩家从 `[1, n]` 中取一个值 `x`（`1 <= x <= n`）；
- 「二号」玩家也从 `[1, n]` 中取一个值 `y`（`1 <= y <= n`）且 `y != x`。

「一号」玩家给值为 `x` 的节点染上红色，而「二号」玩家给值为 `y` 的节点染上蓝色。

之后两位玩家轮流进行操作，「一号」玩家先手。每一回合，玩家选择一个被他染过色的节点，将所选节点一个 **未着色** 的邻节点（即左右子节点、或父节点）进行染色（「一号」玩家染红色，「二号」玩家染蓝色）。

如果（且仅在此种情况下）当前玩家无法找到这样的节点来染色时，其回合就会被跳过。

若两个玩家都没有可以染色的节点时，游戏结束。着色节点最多的那位玩家获得胜利 ✌️。

现在，假设你是「二号」玩家，根据所给出的输入，假如存在一个 `y` 值可以确保你赢得这场游戏，则返回 `true` ；若无法获胜，就请返回 `false` 。

**示例 1 ：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241229181050907.png" alt="img" style="zoom: 50%;" />

```
输入：root = [1,2,3,4,5,6,7,8,9,10,11], n = 11, x = 3
输出：true
解释：第二个玩家可以选择值为 2 的节点。
```

**示例 2 ：**

```
输入：root = [1,2,3], n = 3, x = 1
输出：false
```

 

**提示：**

- 树中节点数目为 `n`
- `1 <= x <= n <= 100`
- `n` 是奇数
- `1 <= Node.val <= n`
- 树中所有值 **互不相同**



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int leftChildNum = 0, rightChildNum = 0;
    bool btreeGameWinningMove(TreeNode* root, int n, int x) {
        dfs(root, x); 
        int parentNum = n - (leftChildNum + rightChildNum + 1);
        int maxNum = max({leftChildNum, rightChildNum, parentNum});
        return maxNum > n / 2;
    }
    int dfs(TreeNode* root, int x) {
        if (root == nullptr) {
            return 0;
        }
        int left = dfs(root->left, x);
        int right = dfs(root->right, x);
        if (root->val == x) {
            leftChildNum = left;
            rightChildNum = right;
        }
        return left + right + 1;
    }
};
```



## 广度优先搜索

### 基本模板

```c++
class Solution {
public:
    void levelOrdderTraverse(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        
        queue<TreeNode*> q;
        q.push(root);
        //记录当前遍历到的层数(根节点视为第1层)
        int depth = 1;
        while (!q.empty()) {
            // 需要在循环开始前记录队列长度,因为循环过程中队列长度会变化
            int n = q.size();
            for (int i = 0; i < n; i++) {
                TreeNode* cur = q.front();
                q.pop();
                // 将当前节点的左右子树加入到队列中
                if (cur->left != nullptr) {
                    q.push(cur->left);
                }
                if (cur->right != nullptr) {
                    q.push(cur->right);
                }
            }
            depth++;
        }
        return ans;
    }
};
```



### 例题

#### 513.[找树左下角的值](https://leetcode.cn/problems/find-bottom-left-tree-value/description/)

给定一个二叉树的 **根节点** `root`，请找出该二叉树的 **最底层 最左边** 节点的值。

假设二叉树中至少有一个节点。

 

**示例 1:**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228155245122.jpeg" alt="img" style="zoom:80%;" />

```
输入: root = [2,1,3]
输出: 1
```

**示例 2:**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241228155245154.jpeg" alt="img" style="zoom:67%;" />

```
输入: [1,2,3,4,null,5,6,null,null,7]
输出: 7
```

 

**提示:**

- 二叉树的节点个数的范围是 `[1,104]`
- `-2^31 <= Node.val <= 2^31 - 1` 



==**代码**==

```c+++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    int findBottomLeftValue(TreeNode* root) {
        if (root == nullptr) {
            return {};
        }
        TreeNode* ans = nullptr;
        queue<TreeNode*> q;
        q.push(root);
        int depth = 1;
        while (!q.empty()) {
            int n = q.size();
            ans = q.front();
            for (int i = 0; i < n; i++) {
                TreeNode* cur = q.front();
                q.pop();
                if (cur->left != nullptr) {
                    q.push(cur->left);
                }
                if (cur->right != nullptr) {
                    q.push(cur->right);
                }
            }
            depth++;
        }
        return ans->val;
    }
};
```



#### 199.[二叉树的右视图](https://leetcode.cn/problems/binary-tree-right-side-view/description/)

给定一个二叉树的 **根节点** `root`，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。

 

**示例 1：**

**输入：**root = [1,2,3,null,5,null,4]

**输出：**[1,3,4]

**解释：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241222202920924.png" alt="img" style="zoom:50%;" />

**示例 2：**

**输入：**root = [1,2,3,4,null,null,null,5]

**输出：**[1,3,4,5]

**解释：**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241222202920903.png" alt="img" style="zoom:50%;" />

**示例 3：**

**输入：**root = [1,null,3]

**输出：**[1,3]

**示例 4：**

**输入：**root = []

**输出：**[]

 

**提示:**

- 二叉树的节点个数的范围是 `[0,100]`
- `-100 <= Node.val <= 100` 



==**代码**==

这里可以反着遍历来提高效率

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> ans;
        if (root == nullptr) {
            return {};
        }
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            int n = q.size();
            TreeNode* last = q.front();
            for (int i = 0; i < n; i++) {
                TreeNode* cur = q.front();
                q.pop();
                if (cur->right != nullptr) {
                    q.push(cur->right);
                }
                if (cur->left != nullptr) {
                    q.push(cur->left);
                }
            }
            ans.push_back(last->val);
        }
        return ans;
    }
};
```



## 动态规划

### 例题

#### 623.[在二叉树中增加一行](https://leetcode.cn/problems/add-one-row-to-tree/description/)

给定一个二叉树的根 `root` 和两个整数 `val` 和 `depth` ，在给定的深度 `depth` 处添加一个值为 `val` 的节点行。

注意，根节点 `root` 位于深度 `1` 。

加法规则如下:

- 给定整数 `depth`，对于深度为 `depth - 1` 的每个非空树节点 `cur` ，创建两个值为 `val` 的树节点作为 `cur` 的左子树根和右子树根。
- `cur` 原来的左子树应该是新的左子树根的左子树。
- `cur` 原来的右子树应该是新的右子树根的右子树。
- 如果 `depth == 1 `意味着 `depth - 1` 根本没有深度，那么创建一个树节点，值 `val `作为整个原始树的新根，而原始树就是新根的左子树。

 

**示例 1:**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241225224038994.jpeg" alt="img" style="zoom: 67%;" />

```
输入: root = [4,2,6,3,1,5], val = 1, depth = 2
输出: [4,1,1,2,null,null,6,3,1,5]
```

**示例 2:**

<img src="https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241225224038998.jpeg" alt="img" style="zoom:67%;" />

```
输入: root = [4,2,null,3,1], val = 1, depth = 3
输出:  [4,2,null,1,1,3,null,null,1]
```

 

**提示:**

- 节点数在 `[1, 10^4]` 范围内
- 树的深度在 `[1, 10^4]`范围内
- `-100 <= Node.val <= 100`
- `-10^5 <= val <= 10^5`
- `1 <= depth <= the depth of tree + 1`



==**代码**==

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:

    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if (root == nullptr) {
            return nullptr;
        }
        if (depth == 1) {
            TreeNode* newHead = new TreeNode(val, root, nullptr);
            return newHead;
        } else if (depth == 2) {
            root->left = new TreeNode(val, root->left, nullptr);
            root->right = new TreeNode(val, nullptr, root->right);
            return root;
        }
        root->left = addOneRow(root->left, val, depth - 1);
        root->right = addOneRow(root->right, val, depth - 1);
        return root;
    }
};
```



## 其他

### 例题

#### 652.[寻找重复的子树](https://leetcode.cn/problems/find-duplicate-subtrees/description/)

给你一棵二叉树的根节点 `root` ，返回所有 **重复的子树** 。

对于同一类的重复子树，你只需要返回其中任意 **一棵** 的根结点即可。

如果两棵树具有 **相同的结构** 和 **相同的结点值** ，则认为二者是 **重复** 的。

 

**示例 1：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241221000515900.jpeg)

```
输入：root = [1,2,3,4,null,2,4,null,null,4]
输出：[[2,4],[4]]
```

**示例 2：**

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241221000515659.jpeg)

```
输入：root = [2,1,1]
输出：[[1]]
```

**示例 3：**

**![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20241221000515885.jpeg)**

```
输入：root = [2,2,2,3,null,3,null]
输出：[[2,3],[3]]
```

 

**提示：**

- 树中的结点数在 `[1, 5000]` 范围内。
- `-200 <= Node.val <= 200`



==**代码**==

- 是否可以通过一次遍历二叉树来完成?
  - 可以!

- 首先考虑对于某一个节点,需要知道什么信息
  - 1.以我为根节点的子树的序列
  - 2.以其他节点为根节点的子树的序列
- 第1点可以在后序位置知道左右子树情况,可以通过拼接字符串的方式把二叉树序列化
- 第2点可以通过哈希表来知道
  - 注意某种情况有3个以上重复子树时只需要加入一次,所以需要判断`hash_map[str] == 1`

```c++
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    unordered_map<string, int> hash_map;
    vector<TreeNode*> ans;
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        traverse(root);
        return ans;
    }
    string traverse(TreeNode* root) {
        if (root == nullptr) {
            return "#";
        }
        string left = traverse(root->left);
        string right = traverse(root->right);
        string str = left + "," + right + "," + to_string(root->val);
        if (hash_map[str] == 1) {
            ans.push_back(root);
        }
        hash_map[str]++;
        return str;
    }
};
```

