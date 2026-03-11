int countElement(const vector<int>& arr, int target, int& stepCount) {
    // int count = 0 (1 次指派)
    int count = 0;
    stepCount++;

    // i = 0 (1 次指派)
    stepCount++;
    for (int i = 0; i < arr.size(); i++) {
        // i < arr.size() (1 次比較)
        stepCount++;

        // if (arr[i] == target)
        // 包含：1 次陣列存取 (arr[i]) + 1 次比較 (==)
        stepCount += 2;
        if (arr[i] == target) {
            // count++ (1 次遞增) - 僅在條件成立時執行
            count++;
            stepCount++;
        }

        // i++ (1 次遞增)
        stepCount++;
    }
    // 最後一次 i < arr.size() 為 false (1 次比較)
    stepCount++;

    // return count (1 次回傳)
    stepCount++;
    return count;
}
