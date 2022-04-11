#include <iostream>
#include <vector>
#include <set>

class Card
{
public:
    enum rank { ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING };
    enum suit { CLUBS, DIAMONDS, HEARTS, SPADES };

    Card(rank r = ACE, suit s = SPADES, bool ifu = true) : m_Rank(r), m_Suit(s), m_IsFaceUp(ifu) { }

    int GetValue() const;
    void Flip();

    friend std::ostream& operator<<(std::ostream& s, const Card& aCard);
private:
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

int Card::GetValue() const
{
    int value = 0;
    if (m_IsFaceUp)
    {
        value = m_Rank;
        if (value > 10)
        {
            value = 10;
        }
    }
    return value;
}

void Card::Flip()
{
    m_IsFaceUp = !m_IsFaceUp;
}

class Hand
{
public:
    Hand();
    virtual ~Hand();
    //добавляем карту в руку
    void Add(Card* pCard);

    //Очищаем руки от карт
    void Clear();

    // Получает сумму очков карт в руке, присваивая тузу
    // значение 1 или 11 в зависимости от ситуации
    int GetTotal() const;

protected:
    // Коллекция карт
    std::vector<Card*> m_Cards;
};

Hand::Hand()
{
    m_Cards.reserve(7);
}
Hand::~Hand()
{
    Clear();
}

void Hand::Add(Card* pCard)
{
    m_Cards.push_back(pCard);
}

void Hand::Clear()
{
    // Проходит по вектору, освобождая всю память в куче
    std::vector<Card*>::iterator iter = m_Cards.begin();
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        delete* iter;
        *iter = nullptr;
    }
    // Очищает вектор указателей
    m_Cards.clear();
}

int Hand::GetTotal() const
{
    // Если в руке нет карт
    if (m_Cards.empty())
    {
        return 0;
    }
    // Если первая карта имеет значение 0, то она лежит рубашкой вверх;
    // Вернуть значение 0
    if (m_Cards[0]->GetValue() == 0)
    {
        return 0;
    }
    // Находит сумму очков всех карт, каждый туз (Card::ACE == 1) дает 1 очко
    int total = 0;
    std::vector<Card*>::const_iterator iter;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        total += (*iter)->GetValue();
    }
    // Определяет. держит ли рука туз
    bool containsAce = false;
    for (iter = m_Cards.begin(); iter != m_Cards.end(); ++iter)
    {
        if ((*iter)->GetValue() == Card::ACE)
        {
            containsAce = true;
        }
    }
    // Если сумма очков всех карт в руке меньше 11
    // то туз учитывается, как 11 очков (1 + 10)
    if (containsAce && total <= 11)
    {
        total += 10;
    }

    return total;
}

int main() { 
    
    std::cout << "\t\tWelcome to Blackjack!\n\n";
    int numPlayers = 0;
    while (numPlayers < 1 || numPlayers > 7)
    {
        std::cout << "How many players? (1 - 7): ";
        std::cin >> numPlayers;
    }
    std::vector<std::string> names;
    std::string name;
    for (int i = 0; i < numPlayers; ++i)
    {
        std::cout << "Enter player name: ";
        std::cin >> name;
        names.push_back(name);
    }
    std::cout << std::endl;
   
   

}

