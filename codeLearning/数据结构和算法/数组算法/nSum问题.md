# nSum问题

## 1.两数之和

1.[两数之和](https://leetcode.cn/problems/two-sum/description/)

时间复杂度O(N•log(N)),空间复杂度O(N))

先排序,然后二分查找

注意在此题中排序的时间复杂度为O(N•log(N)),使用哈希表可以降到O(N),且空间复杂度均为O(N)

![image-20241128143854127](assets/nSum%E9%97%AE%E9%A2%98/image-20241128143854127.png)

```c++
class Solution {
public:
    vector<int> twoSum(vector<int>& nums, int target) {
        vector<pair<int, int>> numPairs;
        for (int i = 0; i < nums.size(); ++i) {
            numPairs.emplace_back(nums[i], i);
        }
        sort(numPairs.begin(), numPairs.end());

        int left = 0;
        int right = numPairs.size() - 1;
        
        while (left < right) {
            int sum = numPairs[left].first + numPairs[right].first;
            if (sum == target) {
                return vector<int>{numPairs[left].second, numPairs[right].second};
            } else if (sum < target) {
                left++;
            } else if (sum > target) {
                right--;
            }
        }

        return vector<int>{-1, -1};
    }
};
```

如果nums中可能有多对元素之和等于target,要求返回所有合为target的元素对,且不能出现重复

注意数组中可能有重复元素,例如 nums = [1,1,1,2,2,3,3], target = 4,此时[1,3]可能会重复

```c++
class Solution {
public:
    vector<vector<int>> twoSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());
        
        int left = 0;
        int right = nums.size() - 1;
        vector<vector<int>> ans;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                ans.push_back({nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) {
                    left++;
                }
                while (left < target && nums[right] == nums[right - 1]) {
                    right--;
                }
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else if (sum > target) {
                right--;
            }
        }
        return ans;
    }
};
```

## 2.三数之和

15.[三数之和](https://leetcode.cn/problems/3sum/description/)

时间复杂度O(N^2^),空间复杂度O(N)

为了将两数之和的函数抽出来,导致空间复杂度O(N).如果放在for循环下,空间复杂度O(log(N))(即sort的空间复杂度)

![image-20241128152157816](assets/nSum%E9%97%AE%E9%A2%98/image-20241128152157816.png)

```c++
class Solution {
public:
    vector<vector<int>> threeSum(vector<int>& nums) {
        sort(nums.begin(), nums.end());

        vector<vector<int>> ans;
        for (int i = 0; i < nums.size() - 2; i++) {
            vector<vector<int>> tmps = twoSum(nums, i + 1, -nums[i]);

            for (vector<int> tmp : tmps) {
                cout << tmp[0]  << " " << tmp[1] << endl;
                tmp.push_back(nums[i]);
                ans.push_back(tmp);
            }
            while (i < nums.size() - 1 && nums[i] == nums[i + 1]) i++;
        }

        return ans;
    }

    vector<vector<int>> twoSum(vector<int>& nums, int start, int target) {
        // sort(nums.begin(), nums.end());
        
        int left = start;
        int right = nums.size() - 1;
        vector<vector<int>> ans;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                ans.push_back({nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) {
                    left++;
                }
                while (left < right && nums[right] == nums[right - 1]) {
                    right--;
                }
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else if (sum > target) {
                right--;
            }
        }
        return ans;
    }
};
```

## 3.四数之和

18.[四数之和](https://leetcode.cn/problems/4sum/description/)

时间复杂度O(N^3^),空间复杂度O(N^2^)

为了将三数之和,两数之和的函数抽出来,导致空间复杂度O(N^2^).如果放在for循环下,空间复杂度O(log(N))(即sort的空间复杂度)

注意target和nums[i]的取值是[-10^9, 10^9],int会溢出

![image-20241128152737428](assets/nSum%E9%97%AE%E9%A2%98/image-20241128152737428.png)

```c++
class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
        sort(nums.begin(), nums.end());

        int n = nums.size();
        vector<vector<int>> ans;
        for (int i = 0; i < n - 3; i++) {
            vector<vector<int>> tmps = threeSum(nums, i + 1, target - nums[i]);

            for (vector<int> tmp : tmps) {
                // cout << tmp[0]  << " " << tmp[1] << endl;
                tmp.push_back(nums[i]);
                ans.push_back(tmp);
            }
            while (i < nums.size() - 1 && nums[i] == nums[i + 1]) i++;
        }

        return ans;
    }

    vector<vector<int>> threeSum(vector<int>& nums, int start, long target) {
        // sort(nums.begin(), nums.end());

        int n = nums.size();
        vector<vector<int>> ans;
        for (int i = start; i < n - 2; i++) {
            vector<vector<int>> tmps = twoSum(nums, i + 1, target - nums[i]);

            for (vector<int> tmp : tmps) {
                // cout << tmp[0]  << " " << tmp[1] << endl;
                tmp.push_back(nums[i]);
                ans.push_back(tmp);
            }
            while (i < nums.size() - 1 && nums[i] == nums[i + 1]) i++;
        }

        return ans;
    }

    vector<vector<int>> twoSum(vector<int>& nums, int start, long target) {
        // sort(nums.begin(), nums.end());
        
        int left = start;
        int right = nums.size() - 1;
        vector<vector<int>> ans;
        while (left < right) {
            int sum = nums[left] + nums[right];
            if (sum == target) {
                ans.push_back({nums[left], nums[right]});
                while (left < right && nums[left] == nums[left + 1]) {
                    left++;
                }
                while (left < target && nums[right] == nums[right - 1]) {
                    right--;
                }
                left++;
                right--;
            } else if (sum < target) {
                left++;
            } else if (sum > target) {
                right--;
            }
        }
        return ans;
    }
};
```

## 4.n数之和

时间复杂度O(N^(n-1)^),N为数组长度,n为组成target的数字的数量