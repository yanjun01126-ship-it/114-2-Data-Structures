#include <iostream>
using namespace std;

// ========================
// Tree Node Class
// 每個節點包含：資料、左子節點、右子節點
// ========================
class TreeNode {
public:
    int data;           // 儲存節點資料
    TreeNode* left;     // 指向左子節點
    TreeNode* right;    // 指向右子節點

    // 建構子：初始化節點資料與左右指標
    TreeNode(int val) : data(val), left(nullptr), right(nullptr) {}
};

// ========================
// Binary Search Tree Class
// 功能：插入、搜尋、刪除、遍歷
// ========================
class BinarySearchTree {
private:
    TreeNode* root; // 根節點

    // ========================
    // 遞迴插入節點
    // 規則：
    // 小於目前節點 -> 左子樹
    // 大於目前節點 -> 右子樹
    // ========================
    TreeNode* insert(TreeNode* node, int val) {

        // 找到空位置，建立新節點
        if (node == nullptr) {
            return new TreeNode(val);
        }

        // 插入左子樹
        if (val < node->data) {
            node->left = insert(node->left, val);
        }

        // 插入右子樹
        else if (val > node->data) {
            node->right = insert(node->right, val);
        }

        // 若值重複則不插入

        return node;
    }

    // ========================
    // 遞迴搜尋節點
    // 找到回傳 true，否則 false
    // ========================
    bool search(TreeNode* node, int target) {

        // 樹中不存在該值
        if (node == nullptr)
            return false;

        // 找到目標值
        if (node->data == target)
            return true;

        // 繼續搜尋左子樹
        else if (target < node->data)
            return search(node->left, target);

        // 繼續搜尋右子樹
        else
            return search(node->right, target);
    }

    // ========================
    // 中序遍歷（Left -> Root -> Right）
    // 輸出結果會是排序後順序
    // ========================
    void inOrderTraversal(TreeNode* node) {

        if (node == nullptr)
            return;

        // 先走訪左子樹
        inOrderTraversal(node->left);

        // 印出目前節點
        cout << node->data << " ";

        // 再走訪右子樹
        inOrderTraversal(node->right);
    }

    // ========================
    // 找到子樹中的最小值
    // 一直往左走即可
    // ========================
    TreeNode* findMin(TreeNode* node) {

        while (node->left != nullptr) {
            node = node->left;
        }

        return node;
    }

    // ========================
    // 刪除節點
    // 情況：
    // 1. 無子節點
    // 2. 一個子節點
    // 3. 兩個子節點
    // ========================
    TreeNode* deleteNode(TreeNode* node, int val) {

        // 找不到節點
        if (node == nullptr) {
            return nullptr;
        }

        // 目標值較小 -> 左子樹
        if (val < node->data) {
            node->left = deleteNode(node->left, val);
        }

        // 目標值較大 -> 右子樹
        else if (val > node->data) {
            node->right = deleteNode(node->right, val);
        }

        // 找到要刪除的節點
        else {

            // ========================
            // 情況 1：沒有左子節點
            // ========================
            if (node->left == nullptr) {

                TreeNode* temp = node->right;

                delete node;

                return temp;
            }

            // ========================
            // 情況 2：沒有右子節點
            // ========================
            else if (node->right == nullptr) {

                TreeNode* temp = node->left;

                delete node;

                return temp;
            }

            // ========================
            // 情況 3：有兩個子節點
            // 使用右子樹最小值取代
            // ========================
            TreeNode* temp = findMin(node->right);

            // 取代目前節點資料
            node->data = temp->data;

            // 刪除重複節點
            node->right = deleteNode(node->right, temp->data);
        }

        return node;
    }

public:

    // ========================
    // 建構子
    // 初始化空樹
    // ========================
    BinarySearchTree() : root(nullptr) {}

    // ========================
    // 公開插入函式
    // ========================
    void insert(int val) {
        root = insert(root, val);
    }

    // ========================
    // 公開搜尋函式
    // ========================
    bool search(int target) {
        return search(root, target);
    }

    // ========================
    // 顯示中序遍歷結果
    // ========================
    void displayInOrder() {

        cout << "Tree In-Order Traversal (Sorted Result):" << endl;

        inOrderTraversal(root);

        cout << endl;
    }

    // ========================
    // 公開刪除函式
    // ========================
    void deleteValue(int val) {
        root = deleteNode(root, val);
    }
};

// ========================
// Main Function
// ========================
int main() {

    // 建立 Binary Search Tree
    BinarySearchTree bst;

    // 預設資料
    int values[] = {7, 1, 4, 2, 8, 13, 12, 11, 15, 9, 5};

    // 計算陣列大小
    int n = sizeof(values) / sizeof(values[0]);

    // ========================
    // 將資料插入 BST
    // ========================
    for (int i = 0; i < n; ++i) {
        bst.insert(values[i]);
    }

    // ========================
    // 搜尋 / 新增功能
    // ========================
    int key;

    cout << "Enter a value to search/insert: ";
    cin >> key;

    // 若存在則不新增
    if (bst.search(key)) {
        cout << "Value " << key << " already exists." << endl;
    }

    // 若不存在則插入
    else {
        cout << "Value " << key << " inserted into tree." << endl;
        bst.insert(key);
    }

    // 顯示目前 BST
    bst.displayInOrder();

    // ========================
    // 刪除功能
    // ========================
    int deleteKey;

    cout << "Enter a value to delete: ";
    cin >> deleteKey;

    // 執行刪除
    bst.deleteValue(deleteKey);

    // 顯示刪除後結果
    cout << "Tree after deletion:" << endl;

    bst.displayInOrder();

    return 0;
}
