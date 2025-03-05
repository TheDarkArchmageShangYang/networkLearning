# 剑指OFFER

## 状态

- 0表示轻松解决

- 1表示花费一定时间后解决
- 2表示本来有点思路,最后搜索资料或看题解解决
- 3表示没有思路

## 数据结构

### 链表

#### JZ6.[从尾到头打印链表](https://www.nowcoder.com/practice/d0267f7f55b3412ba93bd35cfa8e8035?tpId=13&tqId=23278&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入一个链表的头节点，按链表从尾到头的顺序返回每个节点的值（用数组返回）。

如输入{1,2,3}的链表如下图:

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250226202032954.png)

返回一个数组为[3,2,1]

0 <= 链表长度 <= 10000



==**代码**==

不改变链表

```c++
/**
*  struct ListNode {
*        int val;
*        struct ListNode *next;
*        ListNode(int x) :
*              val(x), next(NULL) {
*        }
*  };
*/
#include <climits>
#include <vector>
class Solution {
public:
    vector<int> printListFromTailToHead(ListNode* head) {
        vector<int> ans;
        ListNode* cur = head;
        while (cur != nullptr) {
            ans.push_back(cur->val);
            cur = cur->next;
        }
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
```



#### JZ24.[反转链表](https://www.nowcoder.com/practice/75e878df47f24fdc9dc3e400ec6058ca?tpId=13&tqId=23286&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

给定一个单链表的头结点pHead(该头节点是有值的，比如在下图，它的val是1)，长度为n，反转该链表后，返回新链表的表头。

数据范围： 0≤n≤10000≤*n*≤1000

要求：空间复杂度 O(1)*O*(1) ，时间复杂度 O(n)*O*(*n*) 。

如当输入链表{1,2,3}时，

经反转后，原链表变为{3,2,1}，所以对应的输出为{3,2,1}。

以上转换过程如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250226204401112.png)



==**代码**==

```c++
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param head ListNode类 
     * @return ListNode类
     */
    ListNode* ReverseList(ListNode* head) {
        ListNode* pre = nullptr, *cur = head;
        while (cur != nullptr) {
            ListNode* after = cur->next;
            cur->next = pre;
            pre = cur;
            cur = after;
        }
        return pre;
    }
};
```



#### JZ25.[合并两个排序的链表](https://www.nowcoder.com/practice/d8b6b4358f774294a89de2a6ac4d9337?tpId=13&tqId=23267&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入两个递增的链表，单个链表的长度为n，合并这两个链表并使新链表中的节点仍然是递增排序的。

数据范围： 0≤n≤10000≤*n*≤1000，−1000≤节点值≤1000−1000≤节点值≤1000
要求：空间复杂度 O(1)，时间复杂度 O(n)

如输入{1,3,5},{2,4,6}时，合并后的链表为{1,2,3,4,5,6}，所以对应的输出为{1,2,3,4,5,6}，转换过程如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250226204644674.png)

或输入{-1,2,4},{1,3,4}时，合并后的链表为{-1,1,2,3,4,4}，所以对应的输出为{-1,1,2,3,4,4}，转换过程如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250226204644657.png)



==**代码**==

```c++
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pHead1 ListNode类 
     * @param pHead2 ListNode类 
     * @return ListNode类
     */
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        ListNode* dummyHead = new ListNode(-1), *cur = dummyHead;
        ListNode* cur1 = pHead1, *cur2 = pHead2;
        while (pHead1 != nullptr && pHead2 != nullptr) {
            if (pHead1->val < pHead2->val) {
                cur->next = pHead1;
                pHead1 = pHead1->next;
            } else {
                cur->next = pHead2;
                pHead2 = pHead2->next;
            }
            cur = cur->next;
        }
        if (pHead1 != nullptr) {
            cur->next = pHead1;
        }
        if (pHead2 != nullptr) {
            cur->next = pHead2;
        }
        return dummyHead->next;
    }
};
```



#### JZ52.[两个链表的第一个公共结点](https://www.nowcoder.com/practice/6ab1d9a29e88450685099d45c9e31e46?tpId=13&tqId=23257&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入两个无环的单向链表，找出它们的第一个公共结点，如果没有公共节点则返回空。（注意因为传入数据是链表，所以错误测试数据的提示是用其他方式显示的，保证传入数据是正确的）

数据范围： n≤1000*n*≤1000
要求：空间复杂度 O(1)，时间复杂度 O(n)

例如，输入{1,2,3},{4,5},{6,7}时，两个无环的单向链表的结构如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250226212133125.png)

可以看到它们的第一个公共结点的结点值为6，所以返回结点值为6的结点。



==**代码**==

```c++
/*
struct ListNode {
	int val;
	struct ListNode *next;
	ListNode(int x) :
			val(x), next(NULL) {
	}
};*/
class Solution {
public:
    ListNode* FindFirstCommonNode( ListNode* pHead1, ListNode* pHead2) {
        ListNode* cur1 = pHead1, *cur2 = pHead2;
		while (cur1 != cur2) {
			cur1 = (cur1 == nullptr) ? pHead2 : cur1->next;
			cur2 = (cur2 == nullptr) ? pHead1 : cur2->next;
		}
		return cur1;
    }
};

```



#### JZ23.[链表中环的入口结点](https://www.nowcoder.com/practice/253d2c59ec3e4bc68da16833f79a38e4?tpId=13&tqId=23449&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

给一个长度为n链表，若其中包含环，请找出该链表的环的入口结点，否则，返回null。

数据范围： n≤10000*n*≤10000，1<=结点值<=100001<=结点值<=10000

要求：空间复杂度 O(1)，时间复杂度 O(n)

例如，输入{1,2},{3,4,5}时，对应的环形链表如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250227182852688.png)

可以看到环的入口结点的结点值为3，所以返回结点值为3的结点。



==**代码**==

```c++

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* EntryNodeOfLoop(ListNode* pHead) {
        ListNode* slow = pHead, *fast = pHead;
        while (fast != nullptr && fast->next != nullptr) {
            slow = slow->next;
            fast = fast->next->next;
            if (slow == fast) {
                ListNode* cur = pHead;
                while (cur != slow) {
                    cur = cur->next;
                    slow = slow->next;
                }
                return cur;
            }
        }
        return nullptr;
    }
};
```



#### JZ22.[链表中倒数最后k个结点](https://www.nowcoder.com/practice/886370fe658f41b498d40fb34ae76ff9?tpId=13&tqId=1377477&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入一个长度为 n 的链表，设链表中的元素的值为 ai ，返回该链表中倒数第k个节点。

如果该链表长度小于k，请返回一个长度为 0 的链表。

数据范围：0≤n≤1050≤*n*≤105，0≤ai≤1090≤*a**i*≤109，0≤k≤1090≤*k*≤109

要求：空间复杂度 O(n)，时间复杂度 O(n)

进阶：空间复杂度 O(1)，时间复杂度 O(n)

例如输入{1,2,3,4,5},2时，对应的链表结构如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250227182937626.png)

其中蓝色部分为该链表的最后2个结点，所以返回倒数第2个结点（也即结点值为4的结点）即可，系统会打印后面所有的节点来比较。



==**代码**==

```c++
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
#include <sys/ucontext.h>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pHead ListNode类 
     * @param k int整型 
     * @return ListNode类
     */
    ListNode* FindKthToTail(ListNode* pHead, int k) {
        ListNode* left = pHead, *right = pHead;
        while (k) {
            if (right == nullptr) {
                return nullptr;;
            }
            right = right->next;
            --k;
        }
        while (right != nullptr) {
            left = left->next;
            right = right->next;
        }
        return left;
    }
};
```



#### JZ35.[复杂链表的复制](https://www.nowcoder.com/practice/f836b2c43afc4b35ad6adc41ec941dba?tpId=13&tqId=23254&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入一个复杂链表（每个节点中有节点值，以及两个指针，一个指向下一个节点，另一个特殊指针random指向一个随机节点），请对此链表进行深拷贝，并返回拷贝后的头结点。（注意，输出结果中请不要返回参数中的节点引用，否则判题程序会直接返回空）。 下图是一个含有5个结点的复杂链表。图中实线箭头表示next指针，虚线箭头表示random指针。为简单起见，指向null的指针没有画出。

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250227183022853.png)

示例:

输入:{1,2,3,4,5,3,5,#,2,#}

输出:{1,2,3,4,5,3,5,#,2,#}

解析:我们将链表分为两段，前半部分{1,2,3,4,5}为ListNode，后半部分{3,5,#,2,#}是随机指针域表示。

以上示例前半部分可以表示链表为的ListNode:1->2->3->4->5

后半部分，3，5，#，2，#分别的表示为

1的位置指向3，2的位置指向5，3的位置指向null，4的位置指向2，5的位置指向null

如下图:

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250227183022781.png)



==**代码**==

```c++
/*
struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
            label(x), next(NULL), random(NULL) {
    }
};
*/
class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead) {
        if (pHead == nullptr) {
            return nullptr;;
        }
        RandomListNode* cur = pHead;
        while (cur != nullptr) {
            RandomListNode* newNode = new RandomListNode(cur->label);
            newNode->next = cur->next;
            cur->next = newNode;
            cur = newNode->next;
        }
        cur = pHead;
        RandomListNode* clone = cur->next;
        RandomListNode* newHead = clone;
        while (cur != nullptr) {
            if (cur->random == nullptr) {
                clone->random = nullptr;
            } else {
                clone->random = cur->random->next;
            }
            cur = cur->next->next;
            if (clone->next != nullptr) {
                clone = clone->next->next;
            }
        }
        cur = pHead;
        clone = cur->next;
        while (cur != nullptr) {
            cur->next = cur->next->next;
            if (clone->next != nullptr) {
                clone->next = clone->next->next;
            }
            cur = cur->next;
            clone = clone->next;
        }
        return newHead;
    }
};
```



#### JZ76.[删除链表中重复的结点](https://www.nowcoder.com/practice/fc533c45b73a41b0b44ccba763f866ef?tpId=13&tqId=23450&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

在一个排序的链表中，存在重复的结点，请删除该链表中重复的结点，重复的结点不保留，返回链表头指针。 例如，链表 1->2->3->3->4->4->5 处理后为 1->2->5

数据范围：链表长度满足 0≤n≤1000 0≤*n*≤1000 ，链表中的值满足 1≤val≤1000 1≤*v**a**l*≤1000 

进阶：空间复杂度 O(n) ，时间复杂度 O(n)

例如输入{1,2,3,3,4,4,5}时，对应的输出为{1,2,5}，对应的输入输出链表如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250227183143242.png)



==**代码**==

```c++

/*
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};
*/
class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead) {
        auto dummyHead = new ListNode(-1);
        dummyHead->next = pHead;
        ListNode* slow = dummyHead, *fast = pHead;
        while (fast != nullptr) {
            if (fast->next != nullptr && fast->val == fast->next->val) {
                int temp = fast->val;
                while (fast != nullptr && fast->val == temp) {
                    fast = fast->next;
                }
            } else {
                slow->next = fast;
                slow = slow->next;
                fast = fast->next;
            }
        }
        slow->next = nullptr;
        return dummyHead->next;
    }
};
```



#### JZ18.[删除链表中的节点](https://www.nowcoder.com/practice/f9f78ca89ad643c99701a7142bd59f5d?tpId=13&tqId=2273171&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

给定单向链表的头指针和一个要删除的节点的值，定义一个函数删除该节点。返回删除后的链表的头节点。

1.此题对比原题有改动

2.题目保证链表中节点的值互不相同

3.该题只会输出返回的链表和结果做对比，所以若使用 C 或 C++ 语言，你不需要 free 或 delete 被删除的节点

数据范围:

0<=链表节点值<=10000

0<=链表长度<=10000



==**代码**==

```c++
/**
 * struct ListNode {
 *	int val;
 *	struct ListNode *next;
 *	ListNode(int x) : val(x), next(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param head ListNode类 
     * @param val int整型 
     * @return ListNode类
     */
    ListNode* deleteNode(ListNode* head, int val) {
        ListNode* dummyHead = new ListNode(-1);
        dummyHead->next = head;
        ListNode* pre = dummyHead, *cur = head;
        while (cur != nullptr) {
            if (cur->val == val) {
                pre->next = cur->next;
                cur = cur->next;
            } else {
                cur = cur->next;
                pre = pre->next;
            }
        }
        return dummyHead->next;
    }
};
```



### 树

#### JZ55.[二叉树的深度](https://www.nowcoder.com/practice/435fb86331474282a3499955f0a41e8b?tpId=13&tqId=23294&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入一棵二叉树，求该树的深度。从根结点到叶结点依次经过的结点（含根、叶结点）形成树的一条路径，最长路径的长度为树的深度，根节点的深度视为 1 。

数据范围：节点的数量满足 0≤n≤1000≤*n*≤100 ，节点上的值满足 0≤val≤1000≤*v**a**l*≤100

进阶：空间复杂度 O(1)，时间复杂度 O(n)

假如输入的用例为{1,2,3,4,5,#,6,#,#,7}，那么如下图:

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250228135653376.png)



==**代码**==

```c++
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    int TreeDepth(TreeNode* pRoot) {
		if (pRoot == nullptr) {
			return 0;
		}
		return max(TreeDepth(pRoot->left), TreeDepth(pRoot->right)) + 1;
    }
};

```



#### JZ54.[二叉搜索树的第k个节点](https://www.nowcoder.com/practice/57aa0bab91884a10b5136ca2c087f8ff?tpId=13&tqId=2305268&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

给定一棵结点数为n 二叉搜索树，请找出其中的第 k 小的TreeNode结点值。

1.返回第k小的节点值即可

2.不能查找的情况，如二叉树为空，则返回-1，或者k大于n等等，也返回-1

3.保证n个节点的值不一样

数据范围： 0≤n≤10000≤*n*≤1000，0≤k≤10000≤*k*≤1000，树上每个结点的值满足0≤val≤10000≤*v**a**l*≤1000
进阶：空间复杂度 O(n)，时间复杂度 O(n)

如输入{5,3,7,2,4,6,8},3时，二叉树{5,3,7,2,4,6,8}如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250228142233086.png)

该二叉树所有节点按结点值升序排列后可得[2,3,4,5,6,7,8]，所以第3个结点的结点值为4，故返回对应结点值为4的结点即可。



==**代码**==

```c++
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param proot TreeNode类 
     * @param k int整型 
     * @return int整型
     */
    TreeNode* ans = nullptr;
    int count = 0;
    int KthNode(TreeNode* proot, int k) {
        inOrder(proot, k);
        return ans != nullptr ? ans->val : -1;
    }
    void inOrder(TreeNode* root, int k) {
        if (root == nullptr || count > k) {
            return;
        }
        inOrder(root->left, k);
        count++;
        if (count == k) {
            ans = root;
        }
        inOrder(root->right, k);
    }
};
```



#### JZ7.[重建二叉树](https://www.nowcoder.com/practice/8a19cbe657394eeaac2f6ea9b0f6fcf6?tpId=13&tqId=23282&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

给定节点数为 n 的二叉树的前序遍历和中序遍历结果，请重建出该二叉树并返回它的头结点。

例如输入前序遍历序列{1,2,4,7,3,5,6,8}和中序遍历序列{4,7,2,1,5,3,8,6}，则重建出如下图所示。

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250228143549014.png)

提示:

1.vin.length == pre.length

2.pre 和 vin 均无重复元素

3.vin出现的元素均出现在 pre里

4.只需要返回根结点，系统会自动输出整颗树做答案对比

数据范围：n≤2000*n*≤2000，节点的值 −10000≤val≤10000−10000≤*v**a**l*≤10000

要求：空间复杂度 O(n)，时间复杂度 O(n)



==**代码**==

```c++
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
#include <sys/types.h>
#include <unordered_map>
#include <vector>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param preOrder int整型vector 
     * @param vinOrder int整型vector 
     * @return TreeNode类
     */
    unordered_map<int, int> nodeMap;
    TreeNode* reConstructBinaryTree(vector<int>& preOrder, vector<int>& vinOrder) {
        int n = preOrder.size();
        for (int i = 0; i < n; i++) {
            nodeMap[vinOrder[i]] = i;
        }
        return build(preOrder, 0, n-1, vinOrder, 0, n-1);
    }
    TreeNode* build(vector<int>& preOrder, int preleft, int preright, vector<int>& vinOrder, int inleft, int inright) {
        if (preleft > preright) {
            return nullptr;;
        }
        int value = preOrder[preleft];
        int index = nodeMap[value];
        int leftSize = index - inleft;
        TreeNode* root = new TreeNode(value);
        root->left = build(preOrder, preleft+1, preleft+leftSize, vinOrder, inleft, index-1);
        root->right = build(preOrder, preleft+leftSize+1, preright, vinOrder, index+1, inright);
        return root;
    }
};
```



#### JZ26.[树的子结构](https://www.nowcoder.com/practice/6e196c44c7004d15b1610b9afca8bd88?tpId=13&tqId=23293&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入两棵二叉树A，B，判断B是不是A的子结构。（我们约定空树不是任意一个树的子结构）

假如给定A为{8,8,7,9,2,#,#,#,#,4,7}，B为{8,9,2}，2个树的结构如下，可以看出B是A的子结构

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250228144850803.png)

数据范围:

0 <= A的节点个数 <= 10000

0 <= B的节点个数 <= 10000



==**代码**==

```c++
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
class Solution {
public:
    bool HasSubtree(TreeNode* pRoot1, TreeNode* pRoot2) {
		if (pRoot1 == nullptr || pRoot2 == nullptr) {
			return false;;
		}
		if (check(pRoot1, pRoot2)) {
			return true;
		}
		return HasSubtree(pRoot1->left, pRoot2) || HasSubtree(pRoot1->right, pRoot2);
    }
	bool check(TreeNode* pRoot1, TreeNode* pRoot2) {
		if (pRoot2 == nullptr) {
			return true;
		}
		if (pRoot1 == nullptr || pRoot1->val != pRoot2->val) {
			return false;;
		}
		return check(pRoot1->left, pRoot2->left) && check(pRoot1->right, pRoot2->right);
	}
};

```



#### JZ27.[二叉树的镜像](https://www.nowcoder.com/practice/a9d0ecbacef9410ca97463e4a5c83be7?tpId=13&tqId=1374963&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

操作给定的二叉树，将其变换为源二叉树的镜像。

数据范围：二叉树的节点数 0≤n≤10000≤*n*≤1000 ， 二叉树每个节点的值 0≤val≤10000≤*v**a**l*≤1000

要求： 空间复杂度 O(n)*O*(*n*) 。本题也有原地操作，即空间复杂度 O(1)*O*(1) 的解法，时间复杂度 O(n)*O*(*n*)

比如：

源二叉树

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250228150001848.png)

镜像二叉树

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250228150001831.png)



==**代码**==

```c++
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pRoot TreeNode类 
     * @return TreeNode类
     */
    TreeNode* Mirror(TreeNode* pRoot) {
        if (pRoot == nullptr) {
            return nullptr;;
        }
        TreeNode* tmp = pRoot->left;
        pRoot->left = Mirror(pRoot->right);
        pRoot->right = Mirror(tmp);
        return pRoot;
    }
};
```



#### JZ32.[从上往下打印二叉树](https://www.nowcoder.com/practice/7fe2212963db4790b57431d9ed259701?tpId=13&tqId=23280&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

不分行从上往下打印出二叉树的每个节点，同层节点从左至右打印。例如输入{8,6,10,#,#,2,1}，如以下图中的示例二叉树，则依次打印8,6,10,2,1(空节点不打印，跳过)，请你将打印的结果存放到一个数组里面，返回。

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250302172836850.png)

数据范围:

0<=节点总数<=1000

-1000<=节点值<=1000



==**代码**==

```c++
/*
struct TreeNode {
	int val;
	struct TreeNode *left;
	struct TreeNode *right;
	TreeNode(int x) :
			val(x), left(NULL), right(NULL) {
	}
};*/
#include <vector>
class Solution {
public:
    vector<int> PrintFromTopToBottom(TreeNode* root) {
		if (root == nullptr) {
			return {};
		}
		queue<TreeNode*> q;
		q.push(root);
		vector<int> ans;
		while (!q.empty()) {
			TreeNode* cur = q.front();
			q.pop();
			ans.push_back(cur->val);
			if (cur->left != nullptr) {
				q.push(cur->left);
			}
			if (cur->right != nullptr) {
				q.push(cur->right);
			}
		}
		return ans;
    }
};

```



#### JZ86.[在二叉树中找到两个节点的最近公共祖先](https://www.nowcoder.com/practice/e0cc33a83afe4530bcec46eba3325116?tpId=13&tags=&title=&difficulty=0&judgeStatus=0&rp=0&sourceUrl=%2Fexam%2Foj%2Fta%3FtpId%3D13)

给定一棵二叉树(保证非空)以及这棵树上的两个节点对应的val值 o1 和 o2，请找到 o1 和 o2 的最近公共祖先节点。

数据范围：树上节点数满足 1≤n≤105 1≤*n*≤105 , 节点值val满足区间 [0,n)

要求：时间复杂度 O(n)

注：本题保证二叉树中每个节点的val值均不相同。

如当输入{3,5,1,6,2,0,8,#,#,7,4},5,1时，二叉树{3,5,1,6,2,0,8,#,#,7,4}如下图所示：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250223231611474.png)

所以节点值为5和节点值为1的节点的最近公共祖先节点的节点值为3，所以对应的输出为3。

节点本身可以视为自己的祖先



==**代码**==

```c++
/**
 * struct TreeNode {
 *	int val;
 *	struct TreeNode *left;
 *	struct TreeNode *right;
 *	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 * };
 */
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param root TreeNode类 
     * @param o1 int整型 
     * @param o2 int整型 
     * @return int整型
     */
    int lowestCommonAncestor(TreeNode* root, int o1, int o2) {
        return find(root, o1, o2)->val;
    }
    TreeNode* find(TreeNode* root, int o1, int o2) {
        if (root == nullptr || root->val == o1 || root->val == o2) {
            return root;
        }
        TreeNode* left = find(root->left, o1, o2);
        TreeNode* right = find(root->right, o1, o2);

        if (left == nullptr) {
            return right;
        } else if (right == nullptr) {
            return left;
        }

        return root;
    }
};
```



### 队列&栈

#### JZ9.[用两个栈实现队列](https://www.nowcoder.com/practice/54275ddae22f475981afa2244dd448c6?tpId=13&tqId=23281&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

用两个栈来实现一个队列，使用n个元素来完成 n 次在队列尾部插入整数(push)和n次在队列头部删除整数(pop)的功能。 队列中的元素为int类型。保证操作合法，即保证pop操作时队列内已有元素。

数据范围： n≤1000*n*≤1000

要求：存储n个元素的空间复杂度为 O(n)，插入与删除的时间复杂度都是 O(1)



==**代码**==

```c++
class Solution
{
public:
    void push(int node) {
        stack1.push(node);
    }

    int pop() {
        if (stack2.empty()) {
            while (!stack1.empty()) {
                stack2.push(stack1.top());
                stack1.pop();
            }
        }
        int temp = stack2.top();
        stack2.pop();
        return temp;
    }

private:
    stack<int> stack1;
    stack<int> stack2;
};
```



#### JZ30.[包含min函数的栈](https://www.nowcoder.com/practice/4c776177d2c04c2494f2555c9fcc1e49?tpId=13&tqId=23268&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

定义栈的数据结构，请在该类型中实现一个能够得到栈中所含最小元素的 min 函数，输入操作时保证 pop、top 和 min 函数操作时，栈中一定有元素。

此栈包含的方法有：

push(value):将value压入栈中

pop():弹出栈顶元素

top():获取栈顶元素

min():获取栈中最小元素

数据范围：操作数量满足 0≤n≤300 0≤*n*≤300 ，输入的元素满足 ∣val∣≤10000 ∣*v**a**l*∣≤10000 
进阶：栈的各个操作的时间复杂度是 O(1) *O*(1) ，空间复杂度是 O(n) *O*(*n*) 

示例:

输入:  ["PSH-1","PSH2","MIN","TOP","POP","PSH1","TOP","MIN"]

输出:  -1,2,1,-1

解析:

"PSH-1"表示将-1压入栈中，栈中元素为-1

"PSH2"表示将2压入栈中，栈中元素为2，-1

“MIN”表示获取此时栈中最小元素==>返回-1

"TOP"表示获取栈顶元素==>返回2

"POP"表示弹出栈顶元素，弹出2，栈中元素为-1

"PSH1"表示将1压入栈中，栈中元素为1，-1

"TOP"表示获取栈顶元素==>返回1

“MIN”表示获取此时栈中最小元素==>返回-1



==**代码**==

```c++
#include <stack>
class Solution {
public:
    stack<int> stk;
    stack<int> minstk;
    void push(int value) {
        stk.push(value);
        if (minstk.empty() || minstk.top() >= value) {
            minstk.push(value);
        }
    }
    void pop() {
        if (stk.top() == minstk.top()) {
            minstk.pop();
        }
        stk.pop();
    }
    int top() {
        return stk.top();
    }
    int min() {
        return minstk.top();
    }
};
```



#### JZ31.[栈的压入、弹出序列](https://www.nowcoder.com/practice/d77d11405cc7470d82554cb392585106?tpId=13&tqId=23290&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入两个整数序列，第一个序列表示栈的压入顺序，请判断第二个序列是否可能为该栈的弹出顺序。假设压入栈的所有数字均不相等。例如序列1,2,3,4,5是某栈的压入顺序，序列4,5,3,2,1是该压栈序列对应的一个弹出序列，但4,3,5,1,2就不可能是该压栈序列的弹出序列。

\1. 0<=pushV.length == popV.length <=1000

\2. -1000<=pushV[i]<=1000

\3. pushV 的所有数字均不相同



==**代码**==

```c++
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param pushV int整型vector 
     * @param popV int整型vector 
     * @return bool布尔型
     */
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        int n = pushV.size();
        stack<int> stk;
        int pushIndex = 0;
        for (int i = 0; i < n; i++) {
            while (pushIndex < n && (stk.empty() || stk.top() != popV[i])) {
                stk.push(pushV[pushIndex]);
                pushIndex++;
            }
            if (stk.top() == popV[i]) {
                stk.pop();
            } else {
                return false;
            }
        }
        return true;
    }
};
```



#### JZ73.[翻转单词序列](https://www.nowcoder.com/practice/3194a4f4cf814f63919d0790578d51f3?tpId=13&tqId=23287&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

牛客最近来了一个新员工Fish，每天早晨总是会拿着一本英文杂志，写些句子在本子上。同事Cat对Fish写的内容颇感兴趣，有一天他向Fish借来翻看，但却读不懂它的意思。例如，“nowcoder. a am I”。后来才意识到，这家伙原来把句子单词的顺序翻转了，正确的句子应该是“I am a nowcoder.”。Cat对一一的翻转这些单词顺序可不在行，你能帮助他么？

数据范围：1≤n≤100 1≤*n*≤100 
进阶：空间复杂度 O(n)，时间复杂度 O(n)，保证没有只包含空格的字符串



==**代码**==

```c++
class Solution {
public:
    string ReverseSentence(string str) {
        int n = str.length();
        reverse(str.begin(), str.end());
        for (int i = 0; i < n; i++) {
            int j = i;
            while (j < n && str[j] != ' ') {
                j++;
            }
            reverse(str.begin() + i, str.begin() + j);
            i = j;
        }
        return str;
    }
};
```



#### JZ59.[滑动窗口的最大值](https://www.nowcoder.com/practice/1624bc35a45c42c0bc17d17fa0cba788?tpId=13&tqId=23458&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

给定一个长度为 n 的数组 num 和滑动窗口的大小 size ，找出所有滑动窗口里数值的最大值。

例如，如果输入数组{2,3,4,2,6,2,5,1}及滑动窗口的大小3，那么一共存在6个滑动窗口，他们的最大值分别为{4,4,6,6,6,5}； 针对数组{2,3,4,2,6,2,5,1}的滑动窗口有以下6个： {[2,3,4],2,6,2,5,1}， {2,[3,4,2],6,2,5,1}， {2,3,[4,2,6],2,5,1}， {2,3,4,[2,6,2],5,1}， {2,3,4,2,[6,2,5],1}， {2,3,4,2,6,[2,5,1]}。

窗口大于数组长度或窗口长度为0的时候，返回空。

数据范围： 1≤n≤10000，0≤size≤10000，数组中每个元素的值满足 ∣val∣≤10000

要求：空间复杂度 O(n)，时间复杂度 O(n)



==**代码**==

```c++
#include <climits>
#include <vector>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param num int整型vector 
     * @param size int整型 
     * @return int整型vector
     */
    vector<int> maxInWindows(vector<int>& num, int size) {
        int n = num.size();
        if (size == 0 || n < size) return {};
        int left = 0, right = 0;
        deque<int> dq;
        vector<int> ans;
        while (right < n) {
            while (!dq.empty() && num[dq.back()] <= num[right]) {
                dq.pop_back();
            }
            dq.push_back(right);
            right++;
            if (right < size) continue;
            while (dq.front() < left) {
                dq.pop_front();
            }
            ans.push_back(num[dq.front()]);
            left++;
        }
        return ans;
    }
};
```



## 算法

### 搜索算法

#### JZ53.[数字在升序数组中出现的次数](https://www.nowcoder.com/practice/70610bf967994b22bb1c26f9ae901fa2?tpId=13&tqId=23274&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

给定一个长度为 n 的非降序数组和一个非负数整数 k ，要求统计 k 在数组中出现的次数

数据范围：0≤n≤1000,0≤k≤1000≤*n*≤1000,0≤*k*≤100，数组中每个元素的值满足 0≤val≤1000≤*v**a**l*≤100
要求：空间复杂度 O(1)，时间复杂度 O(logn)



==**代码**==

```c++
#include <vector>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums int整型vector 
     * @param k int整型 
     * @return int整型
     */
    int GetNumberOfK(vector<int>& nums, int k) {
        return getUpperBound(nums, k) - getLowerBound(nums, k) + 1;
    }
    int getUpperBound(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] <= k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return right;
    }
    int getLowerBound(vector<int>& nums, int k) {
        int n = nums.size();
        int left = 0, right = n - 1;
        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < k) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
        return left;
    }
};
```



#### JZ11.[旋转数组的最小数字](https://www.nowcoder.com/practice/9f3231a991af4f55b95579b44b7a01ba?tpId=13&tqId=23269&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

有一个长度为 n 的非降序数组，比如[1,2,3,4,5]，将它进行旋转，即把一个数组最开始的若干个元素搬到数组的末尾，变成一个旋转数组，比如变成了[3,4,5,1,2]，或者[4,5,1,2,3]这样的。请问，给定这样一个旋转数组，求数组中的最小值。

数据范围：1≤n≤100001≤*n*≤10000，数组中任意元素的值: 0≤val≤100000≤*v**a**l*≤10000

要求：空间复杂度：O(1)，时间复杂度：O(logn)



==**代码**==

```c++
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param nums int整型vector 
     * @return int整型
     */
    int minNumberInRotateArray(vector<int>& nums) {
        int n = nums.size();
        int left = 0, right = n - 1;

        while (left < right) {
            int mid = left + (right - left) / 2;
            if (nums[mid] < nums[right]) {
                right = mid;
            } else if (nums[mid] > nums[right]) {
                left = mid + 1;
            } else {
                right --;
            }
        }
        return nums[left];
    }
};
```



#### JZ38.[字符串的排列](https://www.nowcoder.com/practice/fe6b651b66ae47d7acce78ffdd9a96c7?tpId=13&tqId=23291&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

输入一个长度为 n 字符串，打印出该字符串中字符的所有排列，你可以以任意顺序返回这个字符串数组。

例如输入字符串ABC,则输出由字符A,B,C所能排列出来的所有字符串ABC,ACB,BAC,BCA,CBA和CAB。

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250225224044720.png)

数据范围：n<10*n*<10
要求：空间复杂度 O(n!)，时间复杂度 O(n!)



==**代码**==

```c++
#include <vector>
class Solution {
  public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param str string字符串
     * @return string字符串vector
     */
    vector<string> Permutation(string str) {
        int n = str.length();
        sort(str.begin(), str.end());
        vector<string> ans;
        vector<bool> visited(n);
        string path;
        auto backtrack = [&](auto&& backtrack) {
            if (path.length() == n) {
                ans.push_back(path);
                return;
            }
            for (int i = 0; i < n; i++) {
                if (visited[i]) continue;
                if (i > 0 && str[i] == str[i - 1] && !visited[i - 1]) continue;
                path.push_back(str[i]);
                visited[i] = true;
                backtrack(backtrack);
                visited[i] = false;
                path.pop_back();
            }
        };

        backtrack(backtrack);
        return ans;
    }
};
```



#### JZ44.[数字序列中某一位的数字](https://www.nowcoder.com/practice/29311ff7404d44e0b07077f4201418f5?tpId=13&tqId=2285751&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

数字以 0123456789101112131415... 的格式作为一个字符序列，在这个序列中第 2 位（**从下标 0 开始计算**）是 2 ，第 10 位是 1 ，第 13 位是 1 ，以此类题，请你输出第 n 位对应的数字。

数据范围： 0≤n≤109



==**代码**==

```c++
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param n int整型 
     * @return int整型
     */
    int findNthDigit(int n) {
        int digit = 1;
        long long start = 1, len = 9;
        while (n > len) {
            n -= len;
            start *= 10;
            digit++;
            len = 9 * start * digit;
        }
        int num = start + (n - 1) / digit;
        int index = (n - 1) % digit;
        return to_string(num)[index] - '0';
    }
};
```



### 动态规划

#### JZ85.[连续子数组的最大和(二)](https://www.nowcoder.com/practice/11662ff51a714bbd8de809a89c481e21?tpId=13&tqId=2282583&sourceUrl=%2Fexam%2Foj%2Fta%3FtpId%3D13)

输入一个长度为n的整型数组array，数组中的一个或连续多个整数组成一个子数组，找到一个具有最大和的连续子数组。

1.子数组是连续的，比如[1,3,5,7,9]的子数组有[1,3]，[3,5,7]等等，但是[1,3,7]不是子数组

2.如果存在多个最大和的连续子数组，那么返回其中长度最长的，该题数据保证这个最长的只存在一个

3.该题定义的子数组的最小长度为1，不存在为空的子数组，即不存在[]是某个数组的子数组

4.返回的数组不计入空间复杂度计算

数据范围:

1<=n<=1051<=*n*<=105

−100<=a[i]<=100−100<=*a*[*i*]<=100

要求:时间复杂度O(n)，空间复杂度O(n)

进阶:时间复杂度O(n)，空间复杂度O(1)



==**代码**==

定义 `dp[i]` 为以 `arrar[i]` 为最后一个数字的子数组的最大和

- 如果 `dp[i] <= 0`,`dp[i+1] = array[i+1]`
- 如果 `dp[i] > 0`,`dp[i+1] = dp[i+1] + array[i+1]`

在所有 `dp[i]` 中取最大值

```c++
#include <vector>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param array int整型vector 
     * @return int整型vector
     */
    vector<int> FindGreatestSumOfSubArray(vector<int>& array) {
        int n = array.size();
        int dp = array[0];
        int left = 0, right = 0;
        int ans = dp, ansleft = 0, ansright = 0;
        for (int i = 1; i < n; i++) {
            right++;
            if (dp < 0) {
                dp = array[i];
                left = right;
            } else {
                dp += array[i];
            }
            if (dp > ans || (dp == ans && (right - left) > (ansright - ansleft))) {
                ans = dp;
                ansleft = left;
                ansright = right;
            }
        }
        vector<int> ansNum;
        for (int i = ansleft; i <= ansright; i++) {
            ansNum.push_back(array[i]);
        }
        return ansNum;
    }
};
```



#### JZ69.[跳台阶](https://www.nowcoder.com/practice/8c82a5b80378478f9484d87d1c5f12a4?tpId=13&tqId=23261&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D265)

一只青蛙一次可以跳上1级台阶，也可以跳上2级。求该青蛙跳上一个 n 级的台阶总共有多少种跳法（先后次序不同算不同的结果）。

数据范围：1≤n≤401≤*n*≤40

要求：时间复杂度：O(n)，空间复杂度： O(1)



==**代码**==

定义 `dp[i]` 为跳上 `i` 级台阶的跳法数量

- 如果跳上第 `i` 级台阶时跳了一级,`dp[i] = dp[i-1]`
- 如果跳上第 `i` 级台阶时跳了两级,`dp[i] = dp[i-2]`
- 因此 `dp[i] = dp[i-1] + dp[i-2]`

base case: `dp[0] = 1`

```c++
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param number int整型 
     * @return int整型
     */
    int jumpFloor(int number) {
        int x1 = 0, x2 = 0, x3 = 1;
        for (int i = 1; i <= number; i++) {
            x1 = x2;
            x2 = x3;
            x3 = x1 + x2;
        }
        return x3;
    }
};
```



#### JZ10.[斐波那契数列](https://www.nowcoder.com/practice/c6c7742f5ba7442aada113136ddea0c3?tpId=13&tqId=23255&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

大家都知道斐波那契数列，现在要求输入一个正整数 n ，请你输出斐波那契数列的第 n 项。

斐波那契数列是一个满足 fib(x)={1x=1,2fib(x−1)+fib(x−2)x>2*f**i**b*(*x*)={1*f**i**b*(*x*−1)+*f**i**b*(*x*−2)*x*=1,2*x*>2 的数列

数据范围：1≤n≤401≤*n*≤40

要求：空间复杂度 O(1)，时间复杂度 O(n)，本题也有时间复杂度 O(logn) 的解法



==**代码**==

```c++
class Solution {
  public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param n int整型
     * @return int整型
     */
    int Fibonacci(int n) {
        int x1 = 0, x2 = 0, x3 = 1;
        for (int i = 2; i <= n; i++) {
            x1 = x2;
            x2 = x3;
            x3 = x1 + x2;
        }
        return x3;
    }
};
```



#### JZ71.[跳台阶扩展问题](https://www.nowcoder.com/practice/22243d016f6b47f2a6928b4313c85387?tpId=13&tqId=23262&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

一只青蛙一次可以跳上1级台阶，也可以跳上2级……它也可以跳上n级。求该青蛙跳上一个n级的台阶(n为正整数)总共有多少种跳法。

数据范围：1≤n≤201≤*n*≤20
进阶：空间复杂度 O(1)， 时间复杂度 O(1)



==**代码**==

定义 `dp[i]` 为跳上 `i` 级台阶的跳法数量

- 如果跳上第 `i` 级台阶时跳了一级,`dp[i] = dp[i-1]`
- 如果跳上第 `i` 级台阶时跳了两级,`dp[i] = dp[i-2]`
- ....
- 因此 `dp[i] = dp[i-1] + dp[i-2] + ... + dp[i-3]`

base case: `dp[0] = 1`

```c++
class Solution {
  public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param number int整型
     * @return int整型
     */
    int jumpFloorII(int number) {
        int ans = 1, x = 2;
        --number;
        while (number > 0) {
            if (number % 2 == 1) {
                ans *= x;
            }
            x *= x;
            number /= 2;
        }
        return ans;
    }
};
```



#### JZ70.[矩形覆盖](https://www.nowcoder.com/practice/72a5a919508a4251859fb2cfb987a0e6?tpId=13&tqId=23283&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

我们可以用 2*1 的小矩形横着或者竖着去覆盖更大的矩形。请问用 n 个 2*1 的小矩形无重叠地覆盖一个 2*n 的大矩形，从同一个方向看总共有多少种不同的方法？

数据范围：0≤n≤38 0≤*n*≤38 
进阶：空间复杂度 O(1)，时间复杂度 O(n)

注意：约定 n == 0 时，输出 0

比如n=3时，2*3的矩形块有3种不同的覆盖方法(从同一个方向看)：

![img](https://fzchen-picgo.oss-cn-shanghai.aliyuncs.com/Github/learning/20250224132733365.png)



==**代码**==

定义 `dp[i]` 为用 `i` 个2\*1的小矩形覆盖一个2*i的大矩形的方法数量

- 最右边的小矩形竖着放: `dp[i] = dp[i-1]`
- 最右边的小矩形横着放: `dp[i] = dp[i-2]`
- `dp[i] = dp[i-1] + dp[i-2]`
- base case: `dp[0] = 1`,`dp[1] = 1`

```c++
class Solution {
public:
    int rectCover(int number) {
        if (number == 0) return 0;
        int x1 = 0, x2 = 0, x3 = 1;
        for (int i = 1; i <= number; i++) {
            x1 = x2;
            x2 = x3;
            x3 = x1 + x2;
        }
        return x3;
    }
};
```



#### JZ47.[礼物的最大价值](https://www.nowcoder.com/practice/2237b401eb9347d282310fc1c3adb134?tpId=13&tqId=2276652&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

在一个m×n*m*×*n*的棋盘的每一格都放有一个礼物，每个礼物都有一定的价值（价值大于 0）。你可以从棋盘的左上角开始拿格子里的礼物，并每次向右或者向下移动一格、直到到达棋盘的右下角。给定一个棋盘及其上面的礼物的价值，请计算你最多能拿到多少价值的礼物？

如输入这样的一个二维数组，
[
[1,3,1],
[1,5,1],
[4,2,1]
]

那么路径 1→3→5→2→1 可以拿到最多价值的礼物，价值为12



==**代码**==

定义 `dp[i][j]` 为从[0,0]走到[i,j]的礼物最大值

- `dp[i][j] = max(dp[i-1][j],dp[i][j-1]) + nums[i][j]`
- base case: `dp[0][0] = nums[0][0]`

```c++
#include <vector>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param grid int整型vector<vector<>> 
     * @return int整型
     */
    int maxValue(vector<vector<int> >& grid) {
        int m = grid.size(), n = grid[0].size();
        vector<int> dp(n + 1);
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                dp[j+1] = max(dp[j+1], dp[j]) + grid[i][j];
            }
        }
        return dp[n];
    }
};
```



#### JZ48.[最长不含重复字符的子字符串](https://www.nowcoder.com/practice/48d2ff79b8564c40a50fa79f9d5fa9c7?tpId=13&tqId=2276769&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

请从字符串中找出一个最长的不包含重复字符的子字符串，计算该最长子字符串的长度。

数据范围:

 s.length≤40000



==**代码**==

定义 `dp[i]` 为以 `str[i]` 为结尾的子字符串的最大长度

- 如果 `str[i]` 不在哈希表中,`dp[i] = dp[i-1] + 1`
- 如果 `str[i]` 在哈希表中
  - 如果上一次与 `str[i]` 相同的字符不在 `dp[i-1]` 的子字符串中,`dp[i] = dp[i-1] + 1`
  - 如果上一次与 `str[i]` 相同的字符在 `dp[i-1]` 的子字符串中,`dp[i] = i - map[str[i]]`
- base case: `dp[-1] = 0`

```c++
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param s string字符串 
     * @return int整型
     */
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> letterMap;
        int dp = 0, ans = 0;
        for (int i = 0; i < s.length(); i++) {
            if (!letterMap.count(s[i])) {
                ++dp;
            } else {
                dp = min(dp + 1, i - letterMap[s[i]]);
            }
            letterMap[s[i]] = i;
            ans = max(ans, dp);
        }
        return ans;
    }
};
```



#### JZ46.[把数字翻译成字符串](https://www.nowcoder.com/practice/046a55e6cd274cffb88fc32dba695668?tpId=13&tqId=1024831&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

有一种将字母编码成数字的方式：'a'->1, 'b->2', ... , 'z->26'。

现在给一串数字，返回有多少种可能的译码结果

数据范围：字符串长度满足 0<n≤900<*n*≤90

进阶：空间复杂度 O(n)，时间复杂度 O(n)



==**代码**==

定义 `dp[i]` 表示前 `i` 个数的译码方法的数量

- 如果可以和前面的1或2组合译码,`dp[i] = dp[i-2]`
- 如果只能直接编译,`dp[i] = dp[i-1]`
- 如果0的前面不是1或2,`dp[i] = 0`
- base case: `dp[0] = 1`

```c++
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 解码
     * @param nums string字符串 数字串
     * @return int整型
     */
    int solve(string nums) {
        if (nums == "0") {
            return 0;
        }
        int x1 = 0, x2 = 1, x3 = 1;
        for (int i = 1; i < nums.length(); i++) {
            x1 = x2;
            x2 = x3;
            if (nums[i] == '0' && nums[i-1] != '1' && nums[i-1] != '2') {
                return 0;
            } else if ((nums[i-1] == '1' && nums[i] != '0') || (nums[i-1] == '2' && nums[i] > '0' && nums[i] < '7')) {
                x3 = x1 + x2;
            } else {
                x3 = x2;
            }
        }
        return x3;
    }
};
```



### 回溯

#### JZ12.[矩阵中的路径](https://www.nowcoder.com/practice/2a49359695a544b8939c77358d29b7e6?tpId=13&tqId=1517966&sourceUrl=%2Fexam%2Foj%2Fta%3Fpage%3D1%26tpId%3D13%26type%3D13)

请设计一个函数，用来判断在一个n乘m的矩阵中是否存在一条包含某长度为len的字符串所有字符的路径。路径可以从矩阵中的任意一个格子开始，每一步可以在矩阵中向左，向右，向上，向下移动一个格子。如果一条路径经过了矩阵中的某一个格子，则该路径不能再进入该格子。 例如 [abcesfcsadee] 矩阵中包含一条字符串"bcced"的路径，但是矩阵中不包含"abcb"路径，因为字符串的第一个字符b占据了矩阵中的第一行第二个格子之后，路径不能再次进入该格子。

数据范围：0≤n,m≤20,1≤len≤25



==**代码**==

```c++
#include <string>
#include <vector>
class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     * 
     * @param matrix char字符型vector<vector<>> 
     * @param word string字符串 
     * @return bool布尔型
     */
    vector<pair<int, int>> dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
    vector<vector<bool>> visited;
    bool hasPath(vector<vector<char> >& matrix, string word) {
        if (matrix.size() == 0) return false;
        int m = matrix.size(), n = matrix[0].size();
        visited.resize(m, vector<bool>(n));
        for (int i = 0; i < m; i++) {
            for (int j = 0; j < n; j++) {
                if (matrix[i][j] == word[0] && backtrack(matrix, word, i, j, 0)) {
                    return true;
                }
            }
        }
        return false;
    }
    bool backtrack(vector<vector<char>>& matrix, string word, int x, int y, int start) {
        int m = matrix.size(), n = matrix[0].size();
        if (start == word.length() - 1) {
            return true;
        }
        visited[x][y] = true;
        for (auto [dx, dy] : dirs) {
            int nx = x + dx;
            int ny = y + dy;
            if (nx < 0 || nx >= m || ny < 0 || ny >= n) continue;
            if (visited[nx][ny] || matrix[nx][ny] != word[start + 1]) continue;
            if (backtrack(matrix, word, nx, ny, start + 1)) {
                return true;
            }
        }
        visited[x][y] = false;
        return false;
    }
};
```



### 排序

### 位运算

### 模拟

### 其他算法



### LCR121.[寻找目标值-二维数组](https://leetcode.cn/problems/er-wei-shu-zu-zhong-de-cha-zhao-lcof/description/?envType=problem-list-v2&envId=8LSpuXqD&)(0)

`m`*`n` 的二维数组 `plants` 记录了园林景观的植物排布情况，具有以下特性：

- 每行中，每棵植物的右侧相邻植物不矮于该植物；
- 每列中，每棵植物的下侧相邻植物不矮于该植物。

 

请判断 `plants` 中是否存在目标高度值 `target`。

 

**示例 1：**

```
输入：plants = [[2,3,6,8],[4,5,8,9],[5,9,10,12]], target = 8

输出：true
```

 

**示例 2：**

```
输入：plants = [[1,3,5],[2,5,7]], target = 4

输出：false
```

 

**提示：**

- `0 <= n <= 1000`
- `0 <= m <= 1000`



==**代码**==

```c++
class Solution {
public:
    bool findTargetIn2DPlants(vector<vector<int>>& plants, int target) {
        if (plants.size() == 0) return false;
        int m = plants.size(), n = plants[0].size();
        int row = 0, column = n - 1;
        while (row < m && column >= 0) {
            if (plants[row][column] == target) {
                return true;
            } else if (plants[row][column] < target) {
                ++row;
            } else {
                --column;
            }
        }
        return false;
    }
};
```



### LCR120.[寻找文件副本](https://leetcode.cn/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/description/?envType=problem-list-v2&envId=8LSpuXqD&)(0/2)

设备中存有 `n` 个文件，文件 `id` 记于数组 `documents`。若文件 `id` 相同，则定义为该文件存在副本。请返回任一存在副本的文件 `id`。

 

**示例 1：**

```
输入：documents = [2, 5, 3, 0, 5, 0]
输出：0 或 5
```

 

**提示：**

- `0 ≤ documents[i] ≤ n-1`
- `2 <= n <= 100000`



==**代码**==

哈希表: 时间复杂度:${O(N)}$,空间复杂度:${O(N)}$

```c++
class Solution {
public:
    int findRepeatDocument(vector<int>& documents) {
        unordered_set<int> document_set;
        for (int document: documents) {
            if (!document_set.count(document)) {
                document_set.insert(document);
            } else {
                return document;
            }
        }
        return -1;
    }
};
```

原地交换: 时间复杂度:${O(N)}$,空间复杂度:${O(1)}$

```c++
class Solution {
public:
    int findRepeatDocument(vector<int>& documents) {
        int i = 0;
        while (i < documents.size()) {
            if (documents[i] == i) {
                i++;
                continue;
            }
            if (documents[documents[i]] == documents[i]) {
                return documents[i];
            }
            swap(documents[i], documents[documents[i]]);
        }
        return -1;
    }
};
```

