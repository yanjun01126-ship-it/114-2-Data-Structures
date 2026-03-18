class Solution {
public:
    int findLucky(vector<int>& arr) {
        // 因為數字範圍是 1~500，用陣列
        int freq[501] = {0};
        
        // 統計每個數字出現次數
        for (int num : arr) {
            freq[num]++;
        }
        
        // 從大到小找，第一個符合的就是最大 lucky number
        for (int i = 500; i >= 1; i--) {
            if (freq[i] == i) {
                return i;
            }
        }
        
        // 沒有找到
        return -1;
    }
};
