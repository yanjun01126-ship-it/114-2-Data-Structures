void printPairs(const vector<int>& arr, int& stepCount) {
    int n = arr.size();

    // 外層迴圈：
    // i = 0 (1 指派)
    // i < n (比較，共執行 n + 1 次)
    // i++ (遞增，共執行 n 次)
    stepCount++; // i = 0
    for (int i = 0; i < n; i++) {
        stepCount++; // i < n (true)
        
        // 內層迴圈：
        // j = i + 1 (1 指派 + 1 算術)
        // j < n (比較，執行次數隨 i 變化)
        // j++ (遞增，執行次數隨 i 變化)
        stepCount += 2; // j = i + 1
        for (int j = i + 1; j < n; j++) {
            stepCount++; // j < n (true)

            // 核心內容：
            // arr[i], arr[j] (2 陣列存取)
            // cout (1 輸出視為 1 步驟)
            stepCount += 2; // arr[i], arr[j]
            cout << arr[i] << "," << arr[j] << endl;
            stepCount++; // cout

            stepCount++; // j++
        }
        stepCount++; // j < n (最後一次 false)

        stepCount++; // i++
    }
    stepCount++; // i < n (最後一次 false)
    
    // 隱含的 return
    stepCount++;
}
