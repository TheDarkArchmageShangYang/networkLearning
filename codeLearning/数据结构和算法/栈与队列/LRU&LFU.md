# LRU&LFU

## LRU

LRU(Least Recently Used)是一种计算机缓存管理策略

核心数据结构是哈希链表

### 基本原理

要求如下:

- cache中的元素有时序,用以区分最近使用的元素和久未使用的元素.
  容量满了之后删除久未使用的元素
- 在cache中快速找到key对应的value
- 在访问cache中的某个key后,将该元素变为最近使用的,也就是在任意位置快速插入和删除元素

### 实现

146.[LRU缓存](https://leetcode.cn/problems/lru-cache/description/)

请你设计并实现一个满足 [LRU (最近最少使用) 缓存](https://baike.baidu.com/item/LRU) 约束的数据结构。

实现 `LRUCache` 类：

- `LRUCache(int capacity)` 以 **正整数** 作为容量 `capacity` 初始化 LRU 缓存
- `int get(int key)` 如果关键字 `key` 存在于缓存中，则返回关键字的值，否则返回 `-1` 。
- `void put(int key, int value)` 如果关键字 `key` 已经存在，则变更其数据值 `value` ；如果不存在，则向缓存中插入该组 `key-value` 。如果插入操作导致关键字数量超过 `capacity` ，则应该 **逐出** 最久未使用的关键字。

函数 `get` 和 `put` 必须以 `O(1)` 的平均时间复杂度运行。

 

**示例：**

```
输入
["LRUCache", "put", "put", "get", "put", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [4, 4], [1], [3], [4]]
输出
[null, null, null, 1, null, -1, null, -1, 3, 4]

解释
LRUCache lRUCache = new LRUCache(2);
lRUCache.put(1, 1); // 缓存是 {1=1}
lRUCache.put(2, 2); // 缓存是 {1=1, 2=2}
lRUCache.get(1);    // 返回 1
lRUCache.put(3, 3); // 该操作会使得关键字 2 作废，缓存是 {1=1, 3=3}
lRUCache.get(2);    // 返回 -1 (未找到)
lRUCache.put(4, 4); // 该操作会使得关键字 1 作废，缓存是 {4=4, 3=3}
lRUCache.get(1);    // 返回 -1 (未找到)
lRUCache.get(3);    // 返回 3
lRUCache.get(4);    // 返回 4
```

 

**提示：**

- `1 <= capacity <= 3000`
- `0 <= key <= 10000`
- `0 <= value <= 10^5`
- 最多调用 `2 * 10^5` 次 `get` 和 `put`



==**代码**==

```c++
struct DLinkedNode {
    int key, value;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};
class LRUCache {
private:
    unordered_map<int, DLinkedNode*> cache;
    DLinkedNode *head, *tail;
    int capacity, size;

public:
    LRUCache(int capacity) {
        head = new DLinkedNode();
        tail = new DLinkedNode();
        head->next = tail;
        tail->prev = head;
        this->capacity = capacity;
        size = 0;
    }

    int get(int key) {
        if (!cache.count(key)) {
            return -1;
        }
        DLinkedNode* node = cache[key];
        moveToHead(node);
        return node->value;
    }

    void put(int key, int value) {
        if (!cache.count(key)) {
            DLinkedNode* node = new DLinkedNode(key, value);
            cache[key] = node;
            addToHead(node);
            size++;
            if (size > capacity) {
                DLinkedNode* delNode = tail->prev;
                removeNode(delNode);
                cache.erase(delNode->key);
                delete delNode;
                size--;
            }
        } else {
            DLinkedNode* node = cache[key];
            node->value = value;
            moveToHead(node);
        }
    }

    void addToHead(DLinkedNode* node) {
        node->prev = head;
        node->next = head->next;
        head->next->prev = node;
        head->next = node;
    }

    void removeNode(DLinkedNode* node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    void moveToHead(DLinkedNode* node) {
        removeNode(node);
        addToHead(node);
    }
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```



## LFU

LFU(Least Frequently Used)

### 基本原理

要求如下:

- 容量满了之后删除freq最小的key,如果最小的freq对应多个key,删除最旧的一个
- 在cache中快速找到key对应的value
- 在访问cache中的某个key后,该key的freq需要+1

### 实现

460.[LFU缓存](https://leetcode.cn/problems/lfu-cache/description/)

请你为 [最不经常使用（LFU）](https://baike.baidu.com/item/缓存算法)缓存算法设计并实现数据结构。

实现 `LFUCache` 类：

- `LFUCache(int capacity)` - 用数据结构的容量 `capacity` 初始化对象
- `int get(int key)` - 如果键 `key` 存在于缓存中，则获取键的值，否则返回 `-1` 。
- `void put(int key, int value)` - 如果键 `key` 已存在，则变更其值；如果键不存在，请插入键值对。当缓存达到其容量 `capacity` 时，则应该在插入新项之前，移除最不经常使用的项。在此问题中，当存在平局（即两个或更多个键具有相同使用频率）时，应该去除 **最久未使用** 的键。

为了确定最不常使用的键，可以为缓存中的每个键维护一个 **使用计数器** 。使用计数最小的键是最久未使用的键。

当一个键首次插入到缓存中时，它的使用计数器被设置为 `1` (由于 put 操作)。对缓存中的键执行 `get` 或 `put` 操作，使用计数器的值将会递增。

函数 `get` 和 `put` 必须以 `O(1)` 的平均时间复杂度运行。

 

**示例：**

```
输入：
["LFUCache", "put", "put", "get", "put", "get", "get", "put", "get", "get", "get"]
[[2], [1, 1], [2, 2], [1], [3, 3], [2], [3], [4, 4], [1], [3], [4]]
输出：
[null, null, null, 1, null, -1, 3, null, -1, 3, 4]

解释：
// cnt(x) = 键 x 的使用计数
// cache=[] 将显示最后一次使用的顺序（最左边的元素是最近的）
LFUCache lfu = new LFUCache(2);
lfu.put(1, 1);   // cache=[1,_], cnt(1)=1
lfu.put(2, 2);   // cache=[2,1], cnt(2)=1, cnt(1)=1
lfu.get(1);      // 返回 1
                 // cache=[1,2], cnt(2)=1, cnt(1)=2
lfu.put(3, 3);   // 去除键 2 ，因为 cnt(2)=1 ，使用计数最小
                 // cache=[3,1], cnt(3)=1, cnt(1)=2
lfu.get(2);      // 返回 -1（未找到）
lfu.get(3);      // 返回 3
                 // cache=[3,1], cnt(3)=2, cnt(1)=2
lfu.put(4, 4);   // 去除键 1 ，1 和 3 的 cnt 相同，但 1 最久未使用
                 // cache=[4,3], cnt(4)=1, cnt(3)=2
lfu.get(1);      // 返回 -1（未找到）
lfu.get(3);      // 返回 3
                 // cache=[3,4], cnt(4)=1, cnt(3)=3
lfu.get(4);      // 返回 4
                 // cache=[3,4], cnt(4)=2, cnt(3)=3
```

 

**提示：**

- `1 <= capacity <= 10^4`
- `0 <= key <= 10^5`
- `0 <= value <= 10^9`
- 最多调用 `2 * 105` 次 `get` 和 `put` 方法



==**代码**==

使用双向链表来存储相同频率的元素,与LRU基本相同

keyToNode主要用于${O(1)}$查找元素

freqToNode用于存储freq对应的双向链表的头节点和尾节点

需要注意更新节点freq的时机和执行removeNode的时机应该是remove在前,再更新freq,再add

```c++
struct DLinkedNode {
    int key, value, freq;
    DLinkedNode* prev;
    DLinkedNode* next;
    DLinkedNode() : key(0), value(0), freq(0), prev(nullptr), next(nullptr) {}
    DLinkedNode(int _key, int _value, int _freq) : key(_key), value(_value), freq(_freq), prev(nullptr), next(nullptr) {}
};
class LFUCache {
private:
    unordered_map<int, DLinkedNode*> keyToNode;
    unordered_map<int, pair<DLinkedNode*, DLinkedNode*>> freqToNode;
    int capacity, size, minFreq;
    
    void addToHead(DLinkedNode* node) {
        int freq = node->freq;
        if (!freqToNode.count(freq)) {
            DLinkedNode* dummyHead = new DLinkedNode();
            DLinkedNode* dummyTail = new DLinkedNode();
            dummyHead->next = dummyTail;
            dummyTail->prev = dummyHead;
            freqToNode.emplace(freq, make_pair(dummyHead, dummyTail));
        }
        DLinkedNode* dummyHead = freqToNode[freq].first;
        node->prev = dummyHead;
        node->next = dummyHead->next;
        dummyHead->next->prev = node;
        dummyHead->next = node;
    }

    void removeNode(DLinkedNode* node) {
        int freq = node->freq;
        node->prev->next = node->next;
        node->next->prev = node->prev;
        DLinkedNode* dummyHead = freqToNode[freq].first;
        DLinkedNode* dummyTail = freqToNode[freq].second;
        if (dummyHead->next == dummyTail) {
            freqToNode.erase(freq);
            delete dummyHead;
            delete dummyTail;
        }
    }

    void updateMinFreq() {
        while (!freqToNode.count(minFreq)) {
            minFreq++;
        }
    }
public:
    LFUCache(int capacity) {
        this->capacity = capacity;
        size = 0;
        minFreq = 0;
    }
    
    int get(int key) {
        if (!keyToNode.count(key)) {
            return -1;
        }
        DLinkedNode* node = keyToNode[key];
        removeNode(node);
        node->freq++;
        addToHead(node);
        updateMinFreq();
        return node->value;
    }
    
    void put(int key, int value) {
        if (!keyToNode.count(key)) {
            if (size == capacity) {
                DLinkedNode* delNode = freqToNode[minFreq].second->prev;
                removeNode(delNode);
                keyToNode.erase(delNode->key);
                delete delNode;
                size--;
            }
            DLinkedNode* node = new DLinkedNode(key, value, 1);
            keyToNode[key] = node;
            addToHead(node);
            size++;
            minFreq = 1;
        } else {
            DLinkedNode* node = keyToNode[key];
            node->value = value;
            removeNode(node);
            node->freq++;
            addToHead(node);
            updateMinFreq();
        }
    }
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */
```

