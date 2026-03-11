void copyArray(const vector<int>& source, vector<int>& dest, int& stepCount) {
    // i = 0 (1 次指派)
    stepCount++; 
    for (int i = 0; i < source.size(); i++) {
        // i < source.size() (1 次比較)
        stepCount++; 

        // dest[i] = source[i] 
        // 包含：2 次陣列存取 (dest, source) + 1 次指派 (=)
        stepCount += 3;
        dest[i] = source[i];

        // i++ (1 次遞增)
        stepCount++; 
    }
    // 最後一次 i < source.size() 為 false (1 次比較)
    stepCount++; 

    // 隱含的 return (1 次)
    stepCount++; 
}
