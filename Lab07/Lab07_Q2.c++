#include <iostream>
#include <cctype>
#include <cstring>
using namespace std;

/* Stack 使用 linked list 實作：
   - push：放入元素到頂端
   - pop：移除頂端元素
   - peek：查看頂端
   - isEmpty：判斷是否為空 */
struct Node {
    char data;
    Node* next;
};

class Stack {
private:
    Node* top;

public:
    Stack() { top = nullptr; }

    void push(char ch) {
        Node* newNode = new Node;
        newNode->data = ch;
        newNode->next = top;
        top = newNode;
    }

    char pop() {
        if (isEmpty()) return '\0';
        char ch = top->data;
        Node* temp = top;
        top = top->next;
        delete temp;
        return ch;
    }

    char peek() {
        return (top ? top->data : '\0');
    }

    bool isEmpty() {
        return top == nullptr;
    }
};

/* 定義運算子優先順序：
   * / > + - */
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

/* 中序 (Infix) → 後序 (Postfix)
   1. 遇到數字/字母 → 直接輸出
   2. 遇到 '(' → push
   3. 遇到 ')' → pop 直到 '('
   4. 遇到運算子 → 比較優先權，小的先進，大的先出
   5. 最後清空 stack */
void InfixToPostfix(const char* infix, char* postfix) {
    Stack s;
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char ch = infix[i];

        if (isalnum(ch)) {
            postfix[j++] = ch;
        }
        else if (ch == '(') {
            s.push(ch);
        }
        else if (ch == ')') {
            while (!s.isEmpty() && s.peek() != '(') {
                postfix[j++] = s.pop();
            }
            s.pop();
        }
        else {
            while (!s.isEmpty() && precedence(s.peek()) >= precedence(ch)) {
                postfix[j++] = s.pop();
            }
            s.push(ch);
        }
    }

    while (!s.isEmpty()) {
        postfix[j++] = s.pop();
    }

    postfix[j] = '\0';
}

/* 主程式：
   - 輸入中序表達式
   - 呼叫轉換函式
   - 輸出後序結果 */
int main() {
    char infix[100], postfix[100];

    cout << "Enter an Infix expression: ";
    cin >> infix;

    InfixToPostfix(infix, postfix);

    cout << "Postfix expression: " << postfix << endl;

    return 0;
}
