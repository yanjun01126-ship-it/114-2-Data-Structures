#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <random>
#include <ctime>
using namespace std;

struct Player {
    string name;
    int score;
};

class Card {
public:
    string suit;
    string rank;

    Card() {}
    Card(string s, string r) : suit(s), rank(r) {}

    void display() const {
        cout << rank << " of " << suit << endl;
    }
};

class Deck {
private:
    Card cards[52];

public:
    Deck() {
        string suits[] = { "Hearts", "Diamonds", "Clubs", "Spades" };
        string ranks[] = { "2", "3", "4", "5", "6", "7", "8", "9", "10",
                           "J", "Q", "K", "A" };
        int k = 0;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 13; j++) {
                cards[k++] = Card(suits[i], ranks[j]);
            }
        }
    }

    void shuffleDeck() {
        srand(time(0));
        for (int i = 51; i > 0; i--) {
            int j = rand() % (i + 1);
            swap(cards[i], cards[j]);
        }
    }

    Card getCard(int i) const {
        return cards[i];
    }
};

// ================= Queue =================
class Queue {
private:
    vector<Card> deck;
    int Front;
    int Rear;
    int capacity;

public:
    Queue(int size) : Front(0), Rear(-1), capacity(size) {}

    void enqueue(Card card) {
        if (isFull()) {
            cout << "牌堆已滿！" << endl;
            return;
        }
        deck.push_back(card);
        Rear++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "牌堆為空！" << endl;
            return;
        }
        Front++;
    }

    Card front() {
        if (isEmpty()) {
            return Card("", "");
        }
        return deck[Front];
    }

    bool isEmpty() const {
        return Front > Rear;
    }

    bool isFull() const {
        return deck.size() == capacity;
    }
};

// ================= 初始化牌堆 =================
void initializeDeck(Queue& cardDeck) {
    Deck deck;

    deck.shuffleDeck();

    for (int i = 0; i < 52; i++) {
        cardDeck.enqueue(deck.getCard(i));
    }
}

// ================= 初始化玩家 =================
void initializePlayer(Player* player, string name, Queue& cardDeck) {
    player->name = name;
    player->score = 0;

    cout << player->name << " 抽到的牌: ";

    for (int i = 0; i < 2; i++) {
        Card drawnCard = cardDeck.front();
        cardDeck.dequeue();

        cout << drawnCard.rank << " of " << drawnCard.suit << "  ";

        if (drawnCard.rank == "A") player->score += 1;
        else if (drawnCard.rank == "J" || drawnCard.rank == "Q" || drawnCard.rank == "K")
            player->score += 10;
        else
            player->score += stoi(drawnCard.rank);
    }

    cout << "\n" << player->name << " 初始分數: " << player->score << endl;
}

// ================= 玩家回合 =================
void playerTurn(Player* player, Queue& cardDeck) {
    char choice;

    while (player->score < 21 && !cardDeck.isEmpty()) {
        cout << player->name << " 分數: " << player->score
             << " (h=抽, s=停): ";
        cin >> choice;

        if (choice == 'h') {
            Card newCard = cardDeck.front();
            cardDeck.dequeue();

            if (newCard.rank == "A") player->score += 1;
            else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K")
                player->score += 10;
            else
                player->score += stoi(newCard.rank);

            cout << "抽到: " << newCard.rank << " of " << newCard.suit
                 << " → 總分: " << player->score << endl;

            if (player->score > 21) {
                cout << "爆掉！\n";
                return;
            }
        }
        else if (choice == 's') {
            break;
        }
    }
}

// ================= 莊家回合 =================
void dealerTurn(Player* dealer, Queue& cardDeck) {
    while (dealer->score < 17 && !cardDeck.isEmpty()) {
        Card newCard = cardDeck.front();
        cardDeck.dequeue();

        if (newCard.rank == "A") dealer->score += 1;
        else if (newCard.rank == "J" || newCard.rank == "Q" || newCard.rank == "K")
            dealer->score += 10;
        else
            dealer->score += stoi(newCard.rank);

        cout << "莊家抽到: " << newCard.rank << " of " << newCard.suit
             << " → 總分: " << dealer->score << endl;

        if (dealer->score > 21) {
            cout << "莊家爆了！\n";
            return;
        }
    }
}

// ================= 判斷勝負 =================
void determineWinner(Player* player, Player* dealer) {
    if (player->score > 21)
        cout << "莊家贏\n";
    else if (dealer->score > 21 || player->score > dealer->score)
        cout << "玩家贏\n";
    else if (player->score == dealer->score)
        cout << "平手\n";
    else
        cout << "莊家贏\n";
}

// ================= main =================
int main() {
    Queue cardDeck(52);

    initializeDeck(cardDeck);

    Player player, dealer;

    initializePlayer(&player, "玩家", cardDeck);
    initializePlayer(&dealer, "莊家", cardDeck);

    playerTurn(&player, cardDeck);

    if (player.score <= 21) {
        cout << "\n莊家回合...\n";
        dealerTurn(&dealer, cardDeck);
        determineWinner(&player, &dealer);
    }

    return 0;
}
