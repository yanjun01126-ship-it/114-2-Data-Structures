int findMax(const vector<int>& arr) {
    // 1. 指派 (=), 2. 陣列存取 (arr[0])
    // 共 2 個步驟
    int max = arr[0]; 

    // 迴圈部分：
    // 3. 指派 (i=1): 1 步
    // 4. 比較 (i < arr.size()): 執行 n 次
    // 5. 遞增 (i++): 執行 n-1 次
    for (int i = 1; i < arr.size(); i++) {
        
        // 6. 陣列存取 (arr[i]), 7. 比較 (> max)
        // 共 2 個步驟 (執行 n-1 次)
        if (arr[i] > max) {
            
            // 8. 陣列存取 (arr[i]), 9. 指派 (max =)
            // 共 2 個步驟 (執行次數視資料而定，最糟 n-1 次)
            max = arr[i];
        }
    }

    // 10. 回傳 (return): 1 步
    return max;
}

