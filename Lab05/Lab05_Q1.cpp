#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
using namespace std;


// 表示單張撲克牌
class Card {
public:
    string colors; // 花色
    string rank;   // 點數

    // 建構子：初始化卡片
    Card(string s, string r) : colors(s), rank(r) {}

    // 顯示卡片資訊
    void display() const {
        cout << rank << " of " << colors << endl;
    }
};

// 自訂 Stack 類別
class Stack {
private:
    vector<Card> stack; // 用 vector 存卡片

public:
    // push：放入卡片（堆到最上面）
    void push(const Card& card) {
        stack.push_back(card);
    }

    // pop：移除並回傳最上面的卡片
    Card pop() {
        Card topCard = stack.back(); // 取得最上面
        stack.pop_back();            // 移除
        return topCard;              // 回傳
    }

    // 判斷 stack 是否為空
    bool isEmpty() const {
        return stack.empty();
    }
};

// 一副撲克牌
class Deck {
private:
    vector<Card> cards;   // 未洗牌
    Stack shuffledDeck;   // 洗牌後（用 stack 存）

public:
    // 建構子：建立52張牌
    Deck() {
        string colors[] = {"Hearts", "Diamonds", "Clubs", "Spades"};
        string ranks[] = {"2", "3", "4", "5", "6", "7", "8", "9",
                          "10", "J", "Q", "K", "A"};

        // 產生52張牌
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cards.push_back(Card(colors[i], ranks[j]));
            }
        }
    }


    // 洗牌 + 放入 stack
    void shuffleDeck() {
        // 建立隨機亂數產生器
        random_device rd;
        mt19937 g(rd());

        // 使用 shuffle 打亂 cards
        shuffle(cards.begin(), cards.end(), g);

        // 將洗好的牌 push 進 stack
        for (Card card : cards) {
            shuffledDeck.push(card);
        }
    }
    // 從 stack 抽出所有卡片
    
    void drawAllCards() {
        // 當 stack 不為空就一直抽
        while (!shuffledDeck.isEmpty()) {
            Card card = shuffledDeck.pop(); // 取出最上面
            card.display();                 // 顯示卡片
        }
    }
};


// 主程式

int main() {
    Deck deck;               // 建立52張牌
    deck.shuffleDeck();      // 洗牌並放入 stack

    cout << "Shuffled deck:" << endl;

    deck.drawAllCards();     // 從 stack 一張一張抽出並顯示

    return 0;
}
