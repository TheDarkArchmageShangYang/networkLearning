# LeetCode

## 数组

### 1.数组理论基础

略

### 2.二分查找

注意二分查找的不同写法

写法一:target在一个左闭右闭区间里,也就是[left, right]

- while (left <= right),因为left==right是有意义得,所以使用<=
- if (nums[mid] > target) {right = mid - 1},right要赋值为mid-1,因为nums[mid]一定不是target

写法二:target在一个左闭右开区间里,也就是[left, right)

- while (left < right),因为left==right在[left, right)里是没有意义得
- if (nums[mid] > target) {right = mid},这里reight赋值为mid,因为当前nums[mid]!=target,在左区间寻找,而寻找区间左闭右开,所以rihgt更新为mid,即下一个寻找区间不包括nums[mid]

#### 704.二分查找

**题目**

给定一个 `n` 个元素有序的（升序）整型数组 `nums` 和一个目标值 `target` ，写一个函数搜索 `nums` 中的 `target`，如果目标值存在返回下标，否则返回 `-1`。

**示例 1:**

```
输入: nums = [-1,0,3,5,9,12], target = 9
输出: 4
解释: 9 出现在 nums 中并且下标为 4
```

**示例 2:**

```
输入: nums = [-1,0,3,5,9,12], target = 2
输出: -1
解释: 2 不存在 nums 中因此返回 -1
```

 

**提示：**

1.你可以假设 `nums` 中的所有元素是不重复的。

2.`n` 将在 `[1, 10000]`之间。

3.`nums` 的每个元素都将在 `[-9999, 9999]`之间。

**代码**

```c++
class Solution {
public:
    int search(vector<int>& nums, int target) {
        int left = 0;
        int right = nums.size() - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < target) {
                left = mid + 1;
            }
            else if (nums[mid] > target) {
                right = mid - 1;
            }
            else if (nums[mid] == target) {
                return mid;
            }
        }
        return -1;
    }
};
```

**相似题目**

35.搜索插入位置

34.在排序数组中查找元素的第一个和最后一个位置

69.x的平方根

367.有效的完全平方数

### 3.移除元素

常用双指针法(快慢指针法):通过一个快指针和慢指针在一个for/while循环下完成两个for循环的工作

定义快慢指针

- 快指针：寻找新数组的元素 ，新数组就是不含有目标元素的数组
- 慢指针：指向更新 新数组下标的位置

#### 27.移除元素

**题目**

给你一个数组 `nums` 和一个值 `val`，你需要 **[原地](https://baike.baidu.com/item/原地算法)** 移除所有数值等于 `val` 的元素。元素的顺序可能发生改变。然后返回 `nums` 中与 `val` 不同的元素的数量。

假设 `nums` 中不等于 `val` 的元素数量为 `k`，要通过此题，您需要执行以下操作：

- 更改 `nums` 数组，使 `nums` 的前 `k` 个元素包含不等于 `val` 的元素。`nums` 的其余元素和 `nums` 的大小并不重要。
- 返回 `k`。

**示例 1：**

```
输入：nums = [3,2,2,3], val = 3
输出：2, nums = [2,2,_,_]
解释：你的函数函数应该返回 k = 2, 并且 nums 中的前两个元素均为 2。
你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。
```

**示例 2：**

```
输入：nums = [0,1,2,2,3,0,4,2], val = 2
输出：5, nums = [0,1,4,0,3,_,_,_]
解释：你的函数应该返回 k = 5，并且 nums 中的前五个元素为 0,0,1,3,4。
注意这五个元素可以任意顺序返回。
你在返回的 k 个元素之外留下了什么并不重要（因此它们并不计入评测）。
```

 

**提示：**

- `0 <= nums.length <= 100`
- `0 <= nums[i] <= 50`
- `0 <= val <= 100`

**代码**

```c++
class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int index = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] != val) {
                nums[index] = nums[i];
                index++;
            }
        }
        return index;
    }
};
```

**相似题目**

26.删除排序数组中的重复项

283.移动零

844.比较含退格的字符串

977.有序数组的平方

### 4.有序数组的平方

用双指针

#### 977.有序数组的平方

**题目**

给你一个按 **非递减顺序** 排序的整数数组 `nums`，返回 **每个数字的平方** 组成的新数组，要求也按 **非递减顺序** 排序。



**示例 1：**

```
输入：nums = [-4,-1,0,3,10]
输出：[0,1,9,16,100]
解释：平方后，数组变为 [16,1,0,9,100]
排序后，数组变为 [0,1,9,16,100]
```

**示例 2：**

```
输入：nums = [-7,-3,2,3,11]
输出：[4,9,9,49,121]
```

 

**提示：**

- `1 <= nums.length <= 104`
- `-104 <= nums[i] <= 104`
- `nums` 已按 **非递减顺序** 排序

**代码**

```c++
class Solution {
public:
    vector<int> sortedSquares(vector<int>& nums) {
        vector<int> ans;
        int index = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] < 0) {
                index = i + 1;
            }
        }
        int minusIndex = index - 1;
        while (index < nums.size() || minusIndex >= 0) {
            if (index < nums.size() && minusIndex >= 0) {
                if (nums[index] + nums[minusIndex] <= 0) {
                    ans.push_back(nums[index] * nums[index]);
                    index++;
                }
                else {
                    ans.push_back(nums[minusIndex] * nums[minusIndex]);
                    minusIndex--;
                }
                continue;
            }

            while (index < nums.size()) {
                ans.push_back(nums[index] * nums[index]);
                index++;
            }
            while (minusIndex >= 0) {
                ans.push_back(nums[minusIndex] * nums[minusIndex]);
                minusIndex--;
            }
        }
        return ans;
    }
};
```

### 5.长度最小的子数组

用双指针(滑动窗口)

#### 209.长度最小的子数组

**题目**

给定一个含有 `n` 个正整数的数组和一个正整数 `target` **。**

找出该数组中满足其总和大于等于 `target` 的长度最小的 **连续**

**子数组**

`[numsl, numsl+1, ..., numsr-1, numsr]` ，并返回其长度**。**如果不存在符合条件的子数组，返回 `0` 。



**示例 1：**

```
输入：target = 7, nums = [2,3,1,2,4,3]
输出：2
解释：子数组 [4,3] 是该条件下的长度最小的子数组。
```

**示例 2：**

```
输入：target = 4, nums = [1,4,4]
输出：1
```

**示例 3：**

```
输入：target = 11, nums = [1,1,1,1,1,1,1,1]
输出：0
```

 

**提示：**

- `1 <= target <= 109`
- `1 <= nums.length <= 105`
- `1 <= nums[i] <= 105`

 

**进阶：**

- 如果你已经实现 `O(n)` 时间复杂度的解法, 请尝试设计一个 `O(n log(n))` 时间复杂度的解法。

**代码**

```c++
class Solution {
public:
    int minSubArrayLen(int target, vector<int>& nums) {
        int ans = INT_MAX;
        int sum = 0;
        int left = 0;
        for (int i = 0; i < nums.size(); i++) {
            sum += nums[i];
            while (sum >= target) {
                ans = min(ans, i - left + 1);
                sum -= nums[left];
                left++;  
            }
        }
        return ans == INT_MAX ? 0 : ans;
    }
};
```



**相似题目**

904.水果成篮

76.最小覆盖子串

### 6.螺旋矩阵II

坚持循环不变量原则,找到循环过程的边界条件和固定规则

#### 59.螺旋矩阵II

**题目**

给你一个正整数 `n` ，生成一个包含 `1` 到 `n2` 所有元素，且元素按顺时针顺序螺旋排列的 `n x n` 正方形矩阵 `matrix` 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/11/13/spiraln.jpg)

```
输入：n = 3
输出：[[1,2,3],[8,9,4],[7,6,5]]
```

**示例 2：**

```
输入：n = 1
输出：[[1]]
```

 

**提示：**

- `1 <= n <= 20`

**代码**

```c++
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> ans(n,vector<int>(n,0));
        int num = 1;
        int left = 0, right = n - 1, top = 0, bottom = n - 1;
        while(num <= n * n) {
            for (int i = left; i <= right; i++) {
                ans[top][i] = num;
                num++;
            }
            top++;
            for (int i = top; i <= bottom; i++) {
                ans[i][right] = num;
                num++;
            }
            right--;
            for (int i = right; i >= left; i--) {
                ans[bottom][i] = num;
                num++;
            }
            bottom--;
            for (int i = bottom; i >= top; i--) {
                ans[i][left] = num;
                num++;
            }
            left++;
        }
        return ans;
    }
};
```



**相似题目**

54.螺旋矩阵

注意长方形和正方形判断条件不同!

剑指Offer 29.顺时针打印矩阵(与54相同)

## 链表

### 1.链表理论基础

链表节点定义

```c++
// 单链表

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {} 
    // ListNode(int x) {
    //     val = x;
    //     next = null;
    // }
    // 初始化可以在构造函数体内赋值,也可以使用初始化列表赋值,并且推荐使用初始化列表
    // 常量,引用等情况只能使用初始化列表赋值
};
```

### 2.移除链表元素

#### 203.移除链表元素

**题目**

给你一个链表的头节点 `head` 和一个整数 `val` ，请你删除链表中所有满足 `Node.val == val` 的节点，并返回 **新的头节点** 。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/03/06/removelinked-list.jpg)

```
输入：head = [1,2,6,3,4,5,6], val = 6
输出：[1,2,3,4,5]
```

**示例 2：**

```
输入：head = [], val = 1
输出：[]
```

**示例 3：**

```
输入：head = [7,7,7,7], val = 7
输出：[]
```

 

**提示：**

- 列表中的节点数目在范围 `[0, 104]` 内
- `1 <= Node.val <= 50`
- `0 <= val <= 50`

**代码**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeElements(ListNode* head, int val) {
        ListNode *newHead = new ListNode(0, head);
        ListNode *cur = newHead;
        while (cur->next) {
            if (cur->next->val != val) {
                cur = cur->next;
            }
            else {
                ListNode * deleteNode = cur->next;
                cur->next = cur->next->next;
                delete deleteNode;
            }
        }
        ListNode *ansHead = newHead->next;
        delete(newHead);
        return ansHead;
    }
};
```



### 3.设计链表

一般情况下创建不含数据的头节点

注意链表长度与下标判断时,有时<=,有时<

#### 707.设计链表

**题目**

你可以选择使用单链表或者双链表，设计并实现自己的链表。

单链表中的节点应该具备两个属性：`val` 和 `next` 。`val` 是当前节点的值，`next` 是指向下一个节点的指针/引用。

如果是双向链表，则还需要属性 `prev` 以指示链表中的上一个节点。假设链表中的所有节点下标从 **0** 开始。

实现 `MyLinkedList` 类：

- `MyLinkedList()` 初始化 `MyLinkedList` 对象。
- `int get(int index)` 获取链表中下标为 `index` 的节点的值。如果下标无效，则返回 `-1` 。
- `void addAtHead(int val)` 将一个值为 `val` 的节点插入到链表中第一个元素之前。在插入完成后，新节点会成为链表的第一个节点。
- `void addAtTail(int val)` 将一个值为 `val` 的节点追加到链表中作为链表的最后一个元素。
- `void addAtIndex(int index, int val)` 将一个值为 `val` 的节点插入到链表中下标为 `index` 的节点之前。如果 `index` 等于链表的长度，那么该节点会被追加到链表的末尾。如果 `index` 比长度更大，该节点将 **不会插入** 到链表中。
- `void deleteAtIndex(int index)` 如果下标有效，则删除链表中下标为 `index` 的节点。

 

**示例：**

```
输入
["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
[[], [1], [3], [1, 2], [1], [1], [1]]
输出
[null, null, null, null, 2, null, 3]

解释
MyLinkedList myLinkedList = new MyLinkedList();
myLinkedList.addAtHead(1);
myLinkedList.addAtTail(3);
myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
myLinkedList.get(1);              // 返回 2
myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
myLinkedList.get(1);              // 返回 3
```

 

**提示：**

- `0 <= index, val <= 1000`
- 请不要使用内置的 LinkedList 库。
- 调用 `get`、`addAtHead`、`addAtTail`、`addAtIndex` 和 `deleteAtIndex` 的次数不超过 `2000` 。

**代码**

```c++
class MyLinkedList {
public:
    MyLinkedList() {
        size = 0;
        head = new ListNode(0);
    }
    
    int get(int index) {
        if (index < 0 || index >= size ) {
            return -1;
        }
        ListNode *cur = head;
        for (int i = 0; i <= index; i++) {
            cur = cur->next;
        }
        return cur->val;
    }
    
    void addAtHead(int val) {
        ListNode *newNode = new ListNode(val);
        newNode->next = head->next;
        head->next = newNode;
        size++;
    }
    
    void addAtTail(int val) {
        ListNode *pre = head;
        for (int i = 0; i < size; i++) {
            pre = pre->next;
        }
        ListNode * newNode = new ListNode(val);
        newNode->next = pre->next;
        pre->next = newNode;
        size++;
    }
    
    void addAtIndex(int index, int val) {
        if (index < 0 || index > size) {
            return;
        }
        ListNode *pre = head;
        for (int i = 0; i < index; i++) {
            pre = pre->next;
        }
        ListNode * newNode = new ListNode(val);
        newNode->next = pre->next;
        pre->next = newNode;
        size++;
    }
    
    void deleteAtIndex(int index) {
        if (index < 0 || index >= size) {
            return;
        }
        ListNode *pre = head;
        for (int i = 0; i < index; i++) {
            pre = pre->next;
        }
        ListNode *p = pre->next;
        pre->next = pre->next->next;
        size--;
        delete p;
    }

private:
    int size;
    ListNode *head;
};

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
```



### 4.翻转链表

#### 206.反转链表(简单)

**题目**

给你单链表的头节点 `head` ，请你反转链表，并返回反转后的链表。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2021/02/19/rev1ex1.jpg)

```
输入：head = [1,2,3,4,5]
输出：[5,4,3,2,1]
```

**示例 2：**

![img](https://assets.leetcode.com/uploads/2021/02/19/rev1ex2.jpg)

```
输入：head = [1,2]
输出：[2,1]
```

**示例 3：**

```
输入：head = []
输出：[]
```

 

**提示：**

- 链表中节点的数目范围是 `[0, 5000]`
- `-5000 <= Node.val <= 5000`

 

**进阶：**链表可以选用迭代或递归方式完成反转。你能否用两种方法解决这道题？

**代码**

迭代:要想好迭代的顺序,本题中从后往前是无法迭代的,只能从前往后,此时涉及到两个问题:

1.某个节点后继改了之后后面的节点需要提前记录

2.头节点的位置怎么移动

递归:分开考虑单一情况和递归过程

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* reverseList(ListNode* head) {
        // 迭代
        ListNode *pre = nullptr;
        ListNode *cur = head;
        while (cur) {
            ListNode *next = cur->next;
            cur->next = pre;
            pre = cur;
            cur = next;
        }
        return pre;

        // 递归
        // if (!head || !head->next) {
        //     return head;
        // }
        // ListNode *newHead = reverseList(head->next);
        // head->next->next = head;
        // head->next = nullptr;
        // return newHead;
    }
};
```



### 5.两两交换链表中的节点

#### [24.两两交换链表中的节点(中等)](https://leetcode.cn/problems/swap-nodes-in-pairs/description/)

**题目**

给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/swap_ex1.jpg)

```
输入：head = [1,2,3,4]
输出：[2,1,4,3]
```

**示例 2：**

```
输入：head = []
输出：[]
```

**示例 3：**

```
输入：head = [1]
输出：[1]
```

 

**提示：**

- 链表中节点的数目在范围 `[0, 100]` 内
- `0 <= Node.val <= 100`

**代码**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        ListNode *dummyHead = new ListNode(-1, head);
        ListNode *pre = dummyHead;
        ListNode *p = dummyHead->next;
        while (p && p->next) {
            pre->next = p->next;
            p->next = p->next->next;
            pre->next->next = p;
            pre = p;
            p = p->next;
        }
        return dummyHead->next;
    }
};
```



### 6.删除链表的倒数第N个节点

#### 19.[删除链表的倒数第N个节点](https://leetcode.cn/problems/remove-nth-node-from-end-of-list/description/)(中等)

**题目**

给你一个链表，删除链表的倒数第 `n` 个结点，并且返回链表的头结点。

 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2020/10/03/remove_ex1.jpg)

```
输入：head = [1,2,3,4,5], n = 2
输出：[1,2,3,5]
```

**示例 2：**

```
输入：head = [1], n = 1
输出：[]
```

**示例 3：**

```
输入：head = [1,2], n = 1
输出：[1]
```

 

**提示：**

- 链表中结点的数目为 `sz`
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

 

**进阶：**你能尝试使用一趟扫描实现吗？

**代码**

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode *dummyHead = new ListNode(-1, head);
        ListNode *pre = dummyHead;
        ListNode *cur = dummyHead;
        int index = 0;
        while (cur->next) {
            cur = cur->next;
            index++;
            if (index > n) {
                pre = pre->next;
            }
        }
        pre->next = pre->next->next;
        return dummyHead->next;
    }
};
```



### 7.链表相交

#### 160.[相交链表](https://leetcode.cn/problems/intersection-of-two-linked-lists/description/)(简单)

**题目**

给你两个单链表的头节点 `headA` 和 `headB` ，请你找出并返回两个单链表相交的起始节点。如果两个链表不存在相交节点，返回 `null` 。

图示两个链表在节点 `c1` 开始相交**：**

[![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/14/160_statement.png)](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/14/160_statement.png)

题目数据 **保证** 整个链式结构中不存在环。

**注意**，函数返回结果后，链表必须 **保持其原始结构** 。

**自定义评测：**

**评测系统** 的输入如下（你设计的程序 **不适用** 此输入）：

- `intersectVal` - 相交的起始节点的值。如果不存在相交节点，这一值为 `0`
- `listA` - 第一个链表
- `listB` - 第二个链表
- `skipA` - 在 `listA` 中（从头节点开始）跳到交叉节点的节点数
- `skipB` - 在 `listB` 中（从头节点开始）跳到交叉节点的节点数

评测系统将根据这些输入创建链式数据结构，并将两个头节点 `headA` 和 `headB` 传递给你的程序。如果程序能够正确返回相交节点，那么你的解决方案将被 **视作正确答案** 。

 

**示例 1：**

[![img](https://assets.leetcode.com/uploads/2021/03/05/160_example_1_1.png)](https://assets.leetcode.com/uploads/2018/12/13/160_example_1.png)

```
输入：intersectVal = 8, listA = [4,1,8,4,5], listB = [5,6,1,8,4,5], skipA = 2, skipB = 3
输出：Intersected at '8'
解释：相交节点的值为 8 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [4,1,8,4,5]，链表 B 为 [5,6,1,8,4,5]。
在 A 中，相交节点前有 2 个节点；在 B 中，相交节点前有 3 个节点。
— 请注意相交节点的值不为 1，因为在链表 A 和链表 B 之中值为 1 的节点 (A 中第二个节点和 B 中第三个节点) 是不同的节点。换句话说，它们在内存中指向两个不同的位置，而链表 A 和链表 B 中值为 8 的节点 (A 中第三个节点，B 中第四个节点) 在内存中指向相同的位置。
```

 

**示例 2：**

[![img](https://assets.leetcode.com/uploads/2021/03/05/160_example_2.png)](https://assets.leetcode.com/uploads/2018/12/13/160_example_2.png)

```
输入：intersectVal = 2, listA = [1,9,1,2,4], listB = [3,2,4], skipA = 3, skipB = 1
输出：Intersected at '2'
解释：相交节点的值为 2 （注意，如果两个链表相交则不能为 0）。
从各自的表头开始算起，链表 A 为 [1,9,1,2,4]，链表 B 为 [3,2,4]。
在 A 中，相交节点前有 3 个节点；在 B 中，相交节点前有 1 个节点。
```

**示例 3：**

[![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/14/160_example_3.png)](https://assets.leetcode.com/uploads/2018/12/13/160_example_3.png)

```
输入：intersectVal = 0, listA = [2,6,4], listB = [1,5], skipA = 3, skipB = 2
输出：null
解释：从各自的表头开始算起，链表 A 为 [2,6,4]，链表 B 为 [1,5]。
由于这两个链表不相交，所以 intersectVal 必须为 0，而 skipA 和 skipB 可以是任意值。
这两个链表不相交，因此返回 null 。
```

 

**提示：**

- `listA` 中节点数目为 `m`
- `listB` 中节点数目为 `n`
- `1 <= m, n <= 3 * 104`
- `1 <= Node.val <= 105`
- `0 <= skipA <= m`
- `0 <= skipB <= n`
- 如果 `listA` 和 `listB` 没有交点，`intersectVal` 为 `0`
- 如果 `listA` 和 `listB` 有交点，`intersectVal == listA[skipA] == listB[skipB]`

 

**进阶：**你能否设计一个时间复杂度 `O(m + n)` 、仅用 `O(1)` 内存的解决方案？

**代码**

先让两个链表长度一样(长的链表不断后移),然后一一比较就行

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        int lenA = 0, lenB = 0;
        int indexA = 0, indexB = 0;
        ListNode *p = headA;
        while (p) {
            lenA++;
            p = p->next;
        }
        p = headB;
        while (p) {
            lenB++;
            p = p->next;
        }

        ListNode *pA = headA;
        while (lenA - indexA > lenB) {
            pA = pA->next;
            indexA++; 
        }
        ListNode *pB = headB;
        while (lenA < lenB - indexB) {
            pB = pB->next;
            indexB++; 
        }

        while (lenA > indexA && lenB > indexB) {
            if (pA != pB) {
                pA = pA->next;
                pB = pB->next;
                indexA++; 
                indexB++; 
            }
            else {
                return pA;
            }
        }

        return NULL;
    }
};
```



### 8.环形链表II

#### 142.环形链表II(中等)

**题目**

给定一个链表的头节点  `head` ，返回链表开始入环的第一个节点。 *如果链表无环，则返回 `null`。*

如果链表中有某个节点，可以通过连续跟踪 `next` 指针再次到达，则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整数 `pos` 来表示链表尾连接到链表中的位置（**索引从 0 开始**）。如果 `pos` 是 `-1`，则在该链表中没有环。**注意：`pos` 不作为参数进行传递**，仅仅是为了标识链表的实际情况。

**不允许修改** 链表。



 

**示例 1：**

![img](https://assets.leetcode.com/uploads/2018/12/07/circularlinkedlist.png)

```
输入：head = [3,2,0,-4], pos = 1
输出：返回索引为 1 的链表节点
解释：链表中有一个环，其尾部连接到第二个节点。
```

**示例 2：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test2.png)

```
输入：head = [1,2], pos = 0
输出：返回索引为 0 的链表节点
解释：链表中有一个环，其尾部连接到第一个节点。
```

**示例 3：**

![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2018/12/07/circularlinkedlist_test3.png)

```
输入：head = [1], pos = -1
输出：返回 null
解释：链表中没有环。
```

 

**提示：**

- 链表中节点的数目范围在范围 `[0, 104]` 内
- `-105 <= Node.val <= 105`
- `pos` 的值为 `-1` 或者链表中的一个有效索引

 

**进阶：**你是否可以使用 `O(1)` 空间解决此题？

**代码**

使用哈希表来存储节点

```c++
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        unordered_set <ListNode *> visited;
        while (head != NULL) {
            if (visited.count(head)) {
                return head;
            }
            visited.insert(head);
            head = head->next;
        }
        return NULL;
    }
};
```

官方题解:

使用快慢指针来判断环的入口.fast指针移动速度是slow的两倍.如果某一次fast指针和slow指针相遇,则链表中一定存在环.

假设链表中环外长度为a,slow指针一共走了a+b,fast指针比slow多走了n圈,环长度b+c.则fast走了a+n(b+c)+b=a+(n+1)b+nc.

由于fast走了slow的两倍,所以a+(n+1)b+nc=2(a+b),所以a=c+(n-1)(b+c).

所以从链表头部到入环点的距离等于从相遇点到入环点的距离+n-1倍环长.此时额外使用一个指针ptr从链表头部开始,ptr和slow同时开始每次移动一格,最后在入环点相遇.

```c++
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {
        ListNode *slow = head, *fast = head;
        while (fast != nullptr) {
            slow = slow->next;
            if (fast->next == nullptr) {
                return nullptr;
            }
            fast = fast->next->next;
            if (fast == slow) {
                ListNode *ptr = head;
                while (ptr != slow) {
                    ptr = ptr->next;
                    slow = slow->next;
                }
                return ptr;
            }
        }
        return nullptr;
    }
};
```

## 哈希表

### 1.哈希表理论基础

一般使用set(集合)/map(映射)来实现哈希表

| 集合          | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------- | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| set           | 红黑树   | 有序     | 否               | 否           | O(log n) | O(log n) |
| multiset      | 红黑树   | 有序     | 是               | 否           | O(log n) | O(log n) |
| unordered_set | 哈希表   | 无序     | 否               | 否           | O(1)     | O(1)     |

| 映射          | 底层实现 | 是否有序 | 数值是否可以重复 | 能否更改数值 | 查询效率 | 增删效率 |
| ------------- | -------- | -------- | ---------------- | ------------ | -------- | -------- |
| map           | 红黑树   | key有序  | key不能重复      | key不能修改  | O(log n) | O(log n) |
| multimap      | 红黑树   | key有序  | key可重复        | key不能修改  | O(log n) | O(log n) |
| unordered_map | 哈希表   | key无序  | key不能重复      | key不能修改  | O(1)     | O(1)     |

由于set/multiset/map/multimap底层实现是红黑树,红黑树是一种平衡二叉搜索树,所以key有序

### 2.有效的字母异位词

#### 242.[有效的字母异位词](https://leetcode.cn/problems/valid-anagram/description/)(简单)

**题目**

给定两个字符串 `*s*` 和 `*t*` ，编写一个函数来判断 `*t*` 是否是 `*s*` 的字母异位词。

**注意：**若 `*s*` 和 `*t*` 中每个字符出现的次数都相同，则称 `*s*` 和 `*t*` 互为字母异位词。

 

**示例 1:**

```
输入: s = "anagram", t = "nagaram"
输出: true
```

**示例 2:**

```
输入: s = "rat", t = "car"
输出: false
```

 

**提示:**

- `1 <= s.length, t.length <= 5 * 104`
- `s` 和 `t` 仅包含小写字母

 

**进阶:** 如果输入字符串包含 unicode 字符怎么办？你能否调整你的解法来应对这种情况？

**代码**

```c++
class Solution {
public:
    bool isAnagram(string s, string t) {
        unordered_map <char, int> map;
        for (auto c : s) {
            map[c]++;
        }
        for (auto c : t) {
            map[c]--;
        }
        for (auto it : map) {
            if (it.second != 0) {
                return false;
            }
        }
        return true;
    }
};
```

### 3.两个数组的交集

#### 349.[两个数组的交集](https://leetcode.cn/problems/intersection-of-two-arrays/description/)(简单)

**题目**

给定两个数组 `nums1` 和 `nums2` ，返回 *它们的* 

*交集*

 。输出结果中的每个元素一定是 **唯一** 的。我们可以 **不考虑输出结果的顺序** 。



 

**示例 1：**

```
输入：nums1 = [1,2,2,1], nums2 = [2,2]
输出：[2]
```

**示例 2：**

```
输入：nums1 = [4,9,5], nums2 = [9,4,9,8,4]
输出：[9,4]
解释：[4,9] 也是可通过的
```

 

**提示：**

- `1 <= nums1.length, nums2.length <= 1000`
- `0 <= nums1[i], nums2[i] <= 1000`

**代码**

```c++
class Solution {
public:
    vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
        vector<int> ans;
        unordered_set<int> mySet(nums1.begin(), nums1.end());
        for (auto i : nums2) {
            if (mySet.count(i)) {
                ans.push_back(i);
                mySet.erase(i);
            }
        }
        return ans;
    }
};
```

### 4.快乐数

#### 202.[快乐数](https://leetcode.cn/problems/happy-number/description/)(简单)

**题目**

编写一个算法来判断一个数 `n` 是不是快乐数。

**「快乐数」** 定义为：

- 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
- 然后重复这个过程直到这个数变为 1，也可能是 **无限循环** 但始终变不到 1。
- 如果这个过程 **结果为** 1，那么这个数就是快乐数。

如果 `n` 是 *快乐数* 就返回 `true` ；不是，则返回 `false` 。

 

**示例 1：**

```
输入：n = 19
输出：true
解释：
12 + 92 = 82
82 + 22 = 68
62 + 82 = 100
12 + 02 + 02 = 1
```

**示例 2：**

```
输入：n = 2
输出：false
```

 

**提示：**

- `1 <= n <= 231 - 1`

**代码**

注意个位数经过运算也能变成1,如7->49->97->130->10->1

注意一共有3种情况:

- 最终得到1
- 最终进入循环
- 值越来越大,最后接近无穷大(证明不存在这种情况)

```c++
class Solution {
public:
    bool isHappy(int n) {
        unordered_set<int> mySet;
        while (n > 1) {
            if (mySet.count(n)) {
                return false;
            }
            mySet.insert(n);
            int sum = 0;
            while (n > 0) {
                sum += pow(n % 10, 2);
                n = n / 10;
            }
            n = sum;
        }
        return true;
    }
};
```

### 5.两数之和

#### 1.[两数之和](https://leetcode.cn/problems/two-sum/description/)(简单)

**题目**

给定一个整数数组 `nums` 和一个整数目标值 `target`，请你在该数组中找出 **和为目标值** *`target`* 的那 **两个** 整数，并返回它们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素在答案里不能重复出现。

你可以按任意顺序返回答案。

 

**示例 1：**

```
输入：nums = [2,7,11,15], target = 9
输出：[0,1]
解释：因为 nums[0] + nums[1] == 9 ，返回 [0, 1] 。
```

**示例 2：**

```
输入：nums = [3,2,4], target = 6
输出：[1,2]
```

**示例 3：**

```
输入：nums = [3,3], target = 6
输出：[0,1]
```

 

**提示：**

- `2 <= nums.length <= 104`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`
- **只会存在一个有效答案**

 

**进阶：**你可以想出一个时间复杂度小于 `O(n2)` 的算法吗？

**代码**

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<int> ans(2, -1);
        unordered_map<int, int> myHashMap;
        for (int i = 0; i < nums.size(); i++) {
            auto it = myHashMap.find(target - nums[i]);
            if (it != myHashMap.end()) {
                ans[0] = i;
                ans[1] = it->second;
                return ans;
            }
            myHashMap.emplace(nums[i], i);
        }
        return ans;
    }
};
```



### 6.四数相加II

#### 454.[四数相加II](https://leetcode.cn/problems/4sum-ii/description/)(中等)

**题目**

给你四个整数数组 `nums1`、`nums2`、`nums3` 和 `nums4` ，数组长度都是 `n` ，请你计算有多少个元组 `(i, j, k, l)` 能满足：

- `0 <= i, j, k, l < n`
- `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`

 

**示例 1：**

```
输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
输出：2
解释：
两个元组如下：
1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0
```

**示例 2：**

```
输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
输出：1
```

 

 **提示：**

- `n == nums1.length`
- `n == nums2.length`
- `n == nums3.length`
- `n == nums4.length`
- `1 <= n <= 200`
- `-228 <= nums1[i], nums2[i], nums3[i], nums4[i] <= 228`

**代码**

```c++
class Solution {
public:
    int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
        unordered_map<int, int> myHashMap;
        for (auto i : nums1) {
            for (auto j : nums2) {
                myHashMap[i + j]++ ;
            }
        }

        int ans = 0;
        for (auto i : nums3) {
            for (auto j : nums4) {
                if (myHashMap.find(- i - j) != myHashMap.end()) {
                    ans += myHashMap[- i - j];
                }
            }
        }
        return ans;
    }
};
```



### 7.赎金信

#### 383.[赎金信](https://leetcode.cn/problems/ransom-note/description/)(简单)

**题目**

给你两个字符串：`ransomNote` 和 `magazine` ，判断 `ransomNote` 能不能由 `magazine` 里面的字符构成。

如果可以，返回 `true` ；否则返回 `false` 。

`magazine` 中的每个字符只能在 `ransomNote` 中使用一次。

 

**示例 1：**

```
输入：ransomNote = "a", magazine = "b"
输出：false
```

**示例 2：**

```
输入：ransomNote = "aa", magazine = "ab"
输出：false
```

**示例 3：**

```
输入：ransomNote = "aa", magazine = "aab"
输出：true
```

 

**提示：**

- `1 <= ransomNote.length, magazine.length <= 105`
- `ransomNote` 和 `magazine` 由小写英文字母组成

**代码**

```c++
class Solution {
public:
    bool canConstruct(string ransomNote, string magazine) {
        unordered_map<char, int> myHashMap;
        for (auto c : magazine) {
            myHashMap[c]++;
        }
        
        for (auto c : ransomNote) {
            if (myHashMap[c] == 0) {
                return false;
            }
            myHashMap[c]--;
        }
        return true;
    }
};
```



### 8.三数之和

#### 15.[三数之和](https://leetcode.cn/problems/3sum/description/)(中等)

**题目**

给你一个整数数组 `nums` ，判断是否存在三元组 `[nums[i], nums[j], nums[k]]` 满足 `i != j`、`i != k` 且 `j != k` ，同时还满足 `nums[i] + nums[j] + nums[k] == 0` 。请

你返回所有和为 `0` 且不重复的三元组。

**注意：**答案中不可以包含重复的三元组。

 

 

**示例 1：**

```
输入：nums = [-1,0,1,2,-1,-4]
输出：[[-1,-1,2],[-1,0,1]]
解释：
nums[0] + nums[1] + nums[2] = (-1) + 0 + 1 = 0 。
nums[1] + nums[2] + nums[4] = 0 + 1 + (-1) = 0 。
nums[0] + nums[3] + nums[4] = (-1) + 2 + (-1) = 0 。
不同的三元组是 [-1,0,1] 和 [-1,-1,2] 。
注意，输出的顺序和三元组的顺序并不重要。
```

**示例 2：**

```
输入：nums = [0,1,1]
输出：[]
解释：唯一可能的三元组和不为 0 。
```

**示例 3：**

```
输入：nums = [0,0,0]
输出：[[0,0,0]]
解释：唯一可能的三元组和为 0 。
```

 

**提示：**

- `3 <= nums.length <= 3000`
- `-105 <= nums[i] <= 105`

**代码**

求出三数之和为0的三元组不难,难点在于保证不重复

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 2; i++) {
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            int j = i + 1, k = nums.size() - 1;
            while (j < k) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    j++;
                    continue;
                }
                if (k < nums.size() - 1 && nums[k] == nums[k + 1]) {
                    k--;
                    continue;
                }
                if (nums[j] + nums[k] > -nums[i]) {
                    k--;
                }
                else if (nums[j] + nums[k] < -nums[i]) {
                    j++;
                }
                else {
                    ans.push_back({nums[i], nums[j], nums[k]});
                    j++;
                    k--;
                }
            }
        }
        return ans;
    }
};
```



### 9.四数之和

#### 18.[四数之和](https://leetcode.cn/problems/4sum/description/)(中等)

**题目**

给你一个由 `n` 个整数组成的数组 `nums` ，和一个目标值 `target` 。请你找出并返回满足下述全部条件且**不重复**的四元组 `[nums[a], nums[b], nums[c], nums[d]]` （若两个四元组元素一一对应，则认为两个四元组重复）：

- `0 <= a, b, c, d < n`
- `a`、`b`、`c` 和 `d` **互不相同**
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

你可以按 **任意顺序** 返回答案 。

 

**示例 1：**

```
输入：nums = [1,0,-1,0,-2,2], target = 0
输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]
```

**示例 2：**

```
输入：nums = [2,2,2,2,2], target = 8
输出：[[2,2,2,2]]
```

 

**提示：**

- `1 <= nums.length <= 200`
- `-109 <= nums[i] <= 109`
- `-109 <= target <= 109`

**代码**

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        if (nums.size() < 4) {
            return {};
        }
        vector<vector<int>> ans;
        sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size() - 3; i++) {
            cout << i << endl;
            if (i > 0 && nums[i] == nums[i - 1]) {
                continue;
            }
            for (int j = i + 1; j < nums.size() - 2; j++) {
                if (j > i + 1 && nums[j] == nums[j - 1]) {
                    continue;
                }
                int left = j + 1, right = nums.size() - 1;
                while (left < right) {
                    long sum = (long)nums[i] + nums[j] + nums[left] + nums[right];
                    if (sum == target) {
                        ans.push_back({nums[i], nums[j], nums[left], nums[right]});
                        while (left < right && nums[left] == nums[left + 1]) {
                            left++;
                        }
                        left++;
                        while (left <right && nums[right] == nums[right - 1]) {
                            right--;
                        }
                        right--;
                    }
                    else if (sum < target) {
                        left++;
                    }
                    else {
                        right--;
                    }
                }
            }
        }
        return ans;
    }
};
```

## 字符串

### 1.反转字符串

#### 344.[反转字符串](https://leetcode.cn/problems/reverse-string/description/)(简单)

**题目**

编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 `s` 的形式给出。

不要给另外的数组分配额外的空间，你必须**[原地](https://baike.baidu.com/item/原地算法)修改输入数组**、使用 O(1) 的额外空间解决这一问题。

 

**示例 1：**

```
输入：s = ["h","e","l","l","o"]
输出：["o","l","l","e","h"]
```

**示例 2：**

```
输入：s = ["H","a","n","n","a","h"]
输出：["h","a","n","n","a","H"]
```

 

**提示：**

- `1 <= s.length <= 105`
- `s[i]` 都是 [ASCII](https://baike.baidu.com/item/ASCII) 码表中的可打印字符

**代码**

```c++
class Solution {
public:
    void reverseString(vector<char>& s) {
        for (int i = 0; i < s.size() / 2; i++) {
            swap(s[i], s[s.size() - 1 - i]);
        }
    }
};
```



### 2.反转字符串II

#### 541.[反转字符串II](https://leetcode.cn/problems/reverse-string-ii/description/)(简单)

**题目**

给定一个字符串 `s` 和一个整数 `k`，从字符串开头算起，每计数至 `2k` 个字符，就反转这 `2k` 字符中的前 `k` 个字符。

- 如果剩余字符少于 `k` 个，则将剩余字符全部反转。
- 如果剩余字符小于 `2k` 但大于或等于 `k` 个，则反转前 `k` 个字符，其余字符保持原样。

 

**示例 1：**

```
输入：s = "abcdefg", k = 2
输出："bacdfeg"
```

**示例 2：**

```
输入：s = "abcd", k = 2
输出："bacd"
```

 

**提示：**

- `1 <= s.length <= 104`
- `s` 仅由小写英文组成
- `1 <= k <= 104`

**代码**

```c++
class Solution {
public:
    string reverseStr(string s, int k) {
        int n = s.size();
        for (int i = 0; i < n; i += 2 * k) {
            int l = min(n, i + k);
            for (int left = i, right = l - 1; left < right; left++, right--) {
                swap(s[left], s[right]);
            }
        }
        return s;
    }
};
```



### 3.替换数字

#### [替换数字](https://kamacoder.com/problempage.php?pid=1064)(卡码网)

**题目**

###### 题目描述

给定一个字符串 s，它包含小写字母和数字字符，请编写一个函数，将字符串中的字母字符保持不变，而将每个数字字符替换为number。 例如，对于输入字符串 "a1b2c3"，函数应该将其转换为 "anumberbnumbercnumber"。

###### 输入描述

输入一个字符串 s,s 仅包含小写字母和数字字符。

###### 输出描述

打印一个新的字符串，其中每个数字字符都被替换为了number

###### 输入示例

```
a1b2c3
```

###### 输出示例

```
anumberbnumbercnumber
```

###### 提示信息

数据范围：
1 <= s.length < 10000。

**代码**

```c++
#include <iostream>
#include <string>

using namespace std;

int main(void){
    string ans;
    string str = "number";
    cin >> ans;
    
    int num=0;
    for (auto letter : ans) {
        if (letter >= '0' && letter <= '9') {
            num++;
        }
    }
    
    int slow = ans.size() - 1;
    ans.resize(ans.size() + 5 * num);
    int fast = ans.size() - 1;
    
    for (int i = slow; i >= 0; i--) {
        if (ans[i] >= '0'&& ans[i] <= '9') {
            for (int j = 5; j >= 0; j--){
                ans[fast] = str[j];
                fast--;
            }
        }else{
            ans[fast] = ans[i];
            fast--;
        }
    }
    
    cout << ans << endl;
    return 0;
}
```



### 4.翻转字符串里的单词

#### 151.[反转字符串中的单词](https://leetcode.cn/problems/reverse-words-in-a-string/description/)(中等)

**题目**

给你一个字符串 `s` ，请你反转字符串中 **单词** 的顺序。

**单词** 是由非空格字符组成的字符串。`s` 中使用至少一个空格将字符串中的 **单词** 分隔开。

返回 **单词** 顺序颠倒且 **单词** 之间用单个空格连接的结果字符串。

**注意：**输入字符串 `s`中可能会存在前导空格、尾随空格或者单词间的多个空格。返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。

 

**示例 1：**

```
输入：s = "the sky is blue"
输出："blue is sky the"
```

**示例 2：**

```
输入：s = "  hello world  "
输出："world hello"
解释：反转后的字符串中不能存在前导空格和尾随空格。
```

**示例 3：**

```
输入：s = "a good   example"
输出："example good a"
解释：如果两个单词间有多余的空格，反转后的字符串需要将单词间的空格减少到仅有一个。
```

 

**提示：**

- `1 <= s.length <= 104`
- `s` 包含英文大小写字母、数字和空格 `' '`
- `s` 中 **至少存在一个** 单词



 

**进阶：**如果字符串在你使用的编程语言中是一种可变数据类型，请尝试使用 `O(1)` 额外空间复杂度的 **原地** 解法。

**代码**

### 5.右旋转字符串

### 6.实现strStr()

### 7.重复的子字符串

## 栈与队列

### 1.栈与队列理论基础

栈是以底层容器完成其工作,对外提供统一的接口,底层容器是可插拔的(可以控制用哪种容器来实现栈的功能,vector,deque,list等都可以,默认使用deque)

### 2.用栈实现队列

#### 232.[用栈实现队列](https://leetcode.cn/problems/implement-queue-using-stacks/description/)(简单)

**题目**

请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（`push`、`pop`、`peek`、`empty`）：

实现 `MyQueue` 类：

- `void push(int x)` 将元素 x 推到队列的末尾
- `int pop()` 从队列的开头移除并返回元素
- `int peek()` 返回队列开头的元素
- `boolean empty()` 如果队列为空，返回 `true` ；否则，返回 `false`

**说明：**

- 你 **只能** 使用标准的栈操作 —— 也就是只有 `push to top`, `peek/pop from top`, `size`, 和 `is empty` 操作是合法的。
- 你所使用的语言也许不支持栈。你可以使用 list 或者 deque（双端队列）来模拟一个栈，只要是标准的栈操作即可。

 

**示例 1：**

```
输入：
["MyQueue", "push", "push", "peek", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 1, 1, false]

解释：
MyQueue myQueue = new MyQueue();
myQueue.push(1); // queue is: [1]
myQueue.push(2); // queue is: [1, 2] (leftmost is front of the queue)
myQueue.peek(); // return 1
myQueue.pop(); // return 1, queue is [2]
myQueue.empty(); // return false
```



 

**提示：**

- `1 <= x <= 9`
- 最多调用 `100` 次 `push`、`pop`、`peek` 和 `empty`
- 假设所有操作都是有效的 （例如，一个空的队列不会调用 `pop` 或者 `peek` 操作）

 

**进阶：**

- 你能否实现每个操作均摊时间复杂度为 `O(1)` 的队列？换句话说，执行 `n` 个操作的总时间复杂度为 `O(n)` ，即使其中一个操作可能花费较长时间。

**代码**

用栈模拟队列,一个栈是肯定不行的,需要用两个栈,一个栈输入,一个栈输出.

在push的时候,把数据push入输入栈就行.

在pop的时候,如果输出栈为空,就把输入栈的数据导入到输出栈中;如果输出栈不为空,直接从输出栈pop.

```c++
class MyQueue {
public:
    stack<int> inStack, outStack;
    MyQueue() {

    }
    
    void push(int x) {
        inStack.push(x);
    }
    
    int pop() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        int result = outStack.top();
        outStack.pop();
        return result;
    }
    
    int peek() {
        if (outStack.empty()) {
            while (!inStack.empty()) {
                outStack.push(inStack.top());
                inStack.pop();
            }
        }
        return outStack.top();
    }
    
    bool empty() {
        return inStack.empty() && outStack.empty();
    }
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */
```

### 3.用队列实现栈

#### 225.[用队列实现栈](https://leetcode.cn/problems/implement-stack-using-queues/description/)(简单)

**题目**

请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（`push`、`top`、`pop` 和 `empty`）。

实现 `MyStack` 类：

- `void push(int x)` 将元素 x 压入栈顶。
- `int pop()` 移除并返回栈顶元素。
- `int top()` 返回栈顶元素。
- `boolean empty()` 如果栈是空的，返回 `true` ；否则，返回 `false` 。

 

**注意：**

- 你只能使用队列的标准操作 —— 也就是 `push to back`、`peek/pop from front`、`size` 和 `is empty` 这些操作。
- 你所使用的语言也许不支持队列。 你可以使用 list （列表）或者 deque（双端队列）来模拟一个队列 , 只要是标准的队列操作即可。

 

**示例：**

```
输入：
["MyStack", "push", "push", "top", "pop", "empty"]
[[], [1], [2], [], [], []]
输出：
[null, null, null, 2, 2, false]

解释：
MyStack myStack = new MyStack();
myStack.push(1);
myStack.push(2);
myStack.top(); // 返回 2
myStack.pop(); // 返回 2
myStack.empty(); // 返回 False
```

 

**提示：**

- `1 <= x <= 9`
- 最多调用`100` 次 `push`、`pop`、`top` 和 `empty`
- 每次调用 `pop` 和 `top` 都保证栈不为空

 

**进阶：**你能否仅用一个队列来实现栈。

**代码**



### 4.有效的括号

### 5.删除字符串中的所有相邻重复项

### 6.逆波兰表达式求值

### 7.滑动窗口最大值

### 8.前k个高频元素

## 博弈

#### 292.Nim游戏(简单)

**题目**

你和你的朋友，两个人一起玩 Nim 游戏：

- 桌子上有一堆石头。
- 你们轮流进行自己的回合， **你作为先手** 。
- 每一回合，轮到的人拿掉 1 - 3 块石头。
- 拿掉最后一块石头的人就是获胜者。

假设你们每一步都是最优解。请编写一个函数，来判断你是否可以在给定石头数量为 `n` 的情况下赢得游戏。如果可以赢，返回 `true`；否则，返回 `false` 。

**提示：**

- 1 <= n <= pow(2,31) - 1

**代码**

如果n是4的倍数，则必输，无论你取多少(x)，对手取4-x。

如果n不是4的倍数，则必胜，只要第一步取n%4，后续对手取x，自己取4-x。

```c++
class Solution {
public:
    bool canWinNim(int n) {
        return n % 4 != 0;
    }
};
```

#### 375.猜数字大小(中等)

**题目**

我们正在玩一个猜数游戏，游戏规则如下：

1. 我从 `1` 到 `n` 之间选择一个数字。
2. 你来猜我选了哪个数字。
3. 如果你猜到正确的数字，就会 **赢得游戏** 。
4. 如果你猜错了，那么我会告诉你，我选的数字比你的 **更大或者更小** ，并且你需要继续猜数。
5. 每当你猜了数字 `x` 并且猜错了的时候，你需要支付金额为 `x` 的现金。如果你花光了钱，就会 **输掉游戏** 。

给你一个特定的数字 `n` ，返回能够 **确保你获胜** 的最小现金数，**不管我选择那个数字** 。

**提示：**

- `1 <= n <= 200`

**代码**

动态规划

推导过程

```
dp[i][i] = 0
dp[1][2] = 1
dp[1][3] = 2

dp[1][n] = min(i + max(dp[1][i-1] + dp[i+1][n])) (1 < i < n)
dp[1][n] = i + dp[i+1][n] (i = 1)
dp[1][n] = i + dp[1][i-1] (i = n)
dp[1][4] = min(1+dp[2][4], 2+max(dp[1][1], dp[3][4]), 3+max(dp[1][2], dp[4][4]), 4+dp[1][3])
```

```c++
class Solution {
public:
    int getMoneyAmount(int n) {
        vector<vector<int>> dp(n+1,vector<int>(n+1,0));
        for (int j = 2; j <= n; j++) {
            for (int i = j - 1; i > 0; i--) {
                int ans = INT_MAX;
                for (int k = i + 1; k < j; k++) {
                    ans = min(ans, k + max(dp[i][k-1], dp[k+1][j]));
                }
                ans = min(ans, i + dp[i+1][j]);
                ans = min(ans, j + dp[i][j-1]);
                dp[i][j] = ans;
            }
        }
        return dp[1][n];
    }
};
```

#### 464.我能赢吗(中等)

**题目**

在 "100 game" 这个游戏中，两名玩家轮流选择从 `1` 到 `10` 的任意整数，累计整数和，先使得累计整数和 **达到或超过** 100 的玩家，即为胜者。

如果我们将游戏规则改为 “玩家 **不能** 重复使用整数” 呢？

例如，两个玩家可以轮流从公共整数池中抽取从 1 到 15 的整数（不放回），直到累计整数和 >= 100。

给定两个整数 `maxChoosableInteger` （整数池中可选择的最大数）和 `desiredTotal`（累计和），若先出手的玩家能稳赢则返回 `true` ，否则返回 `false` 。假设两位玩家游戏时都表现 **最佳** 。

**提示:**

- `1 <= maxChoosableInteger <= 20`
- `0 <= desiredTotal <= 300`

**代码**

#### 1025.除数博弈(简单)

**题目**

爱丽丝和鲍勃一起玩游戏，他们轮流行动。爱丽丝先手开局。

最初，黑板上有一个数字 `n` 。在每个玩家的回合，玩家需要执行以下操作：

- 选出任一 `x`，满足 `0 < x < n` 且 `n % x == 0` 。
- 用 `n - x` 替换黑板上的数字 `n` 。

如果玩家无法执行这些操作，就会输掉游戏。

*只有在爱丽丝在游戏中取得胜利时才返回 `true` 。假设两个玩家都以最佳状态参与游戏。*

**提示：**

- `1 <= n <= 1000`

**代码**

n = 2, true可选项：1

n = 3, false可选项：1

n = 4, true(选1，给对面3)可选项：1 2

n = 5, false可选项：1

n = 6, true(选1/3，给对面false的数值)可选项：1 2 3

n = 7, false可选项：1

n = 8, true(选1)可选项：1 2 4

n = 9, false可选项：1 3

n = 10, true(选1/5)可选项：1 2 5

n = 11, false可选项：1

n = 12, true(选1/3)可选项：1 2 3 4 6

猜测：偶数赢，奇数输？

n <= 12时成立

假设n <= k时成立，则n=k+1时

当k是偶数时，k+1是奇数，其因数x一定也是奇数，则k+1-x<=k，轮到对方时一定是偶数，所以自己必输

当k是奇数时，k+1是偶数，其因数x可以是奇数也可以是偶数，选择奇数的x(如必然存在的1)，则k+1-x<=k，轮到对方是一定是奇数，所以自己必赢

```c++
class Solution {
public:
    bool divisorGame(int n) {
        return n % 2 == 0;
    }
};
```

