#include <iostream>
#include <map>
#include "utility.h"
using namespace std;

Cards::Cards() : suit('z'), val("0") {}
Cards::~Cards() {}

Cards::Cards(char s, string v)
{
    suit = s;
    val = v;
}

void Cards::setCard(char &suit, string &val)
{
    this->suit = suit;
    this->val = val;
}
char Cards::getSuit() const
{
    return suit;
}

string Cards::getVal() const
{
    return val;
}

bool operator<(Cards const &c1, Cards const &c2)
{

    if (c1.suit == c2.suit && c1.val == c2.val)
        return false;

    int suit1;
    switch (c1.suit)
    {
    case 'c':
        suit1 = 1;
        break;

    case 'd':
        suit1 = 2;
        break;

    case 's':
        suit1 = 3;
        break;

    case 'h':
        suit1 = 4;
        break;
    }

    int suit2;
    switch (c2.suit)
    {
    case 'c':
        suit2 = 1;
        break;

    case 'd':
        suit2 = 2;
        break;

    case 's':
        suit2 = 3;
        break;

    case 'h':
        suit2 = 4;
        break;
    }

    map<string, int> cardFace;
    cardFace["a"] = 1;
    cardFace["2"] = 2;
    cardFace["3"] = 3;
    cardFace["4"] = 4;
    cardFace["5"] = 5;
    cardFace["6"] = 6;
    cardFace["7"] = 7;
    cardFace["8"] = 8;
    cardFace["9"] = 9;
    cardFace["10"] = 10;
    cardFace["j"] = 11;
    cardFace["q"] = 12;
    cardFace["k"] = 13;

    auto val1 = cardFace.find(c1.val);
    auto val2 = cardFace.find(c2.val);

    if (suit1 < suit2)
    {
        return true;
    }
    else if (suit1 > suit2)
    {
        return false;
    }
    else // COMPARING THE VALUES
    {
        if (val1->second < val2->second)
        {
            return true;
        }
        else
            return false;
    }
}

bool operator>(Cards const &c1, Cards const &c2)
{
    if (c1.suit == c2.suit && c1.val == c2.val)
        return false;
    if (c1 < c2)
        return false;
    else
        return true;
}

bool operator==(Cards const &c1, Cards const &c2)
{
    if (c1.suit == c2.suit && c1.val == c2.val)
        return true;
    else
        return false;
}

void Cards::printCard() const
{
    cout << this->suit << " " << this->val << endl;
}

/*
int main()
{
    Cards c1;
    char c = 'c';
    char h = 'h';
    string val1 = "k";
    string val2 = "9";
    c1.setCard(h, val2);
    Cards c2;
    c2.setCard(h, val1);

    Cards c3('h', "q");

    if (c3 < c2)
    {
        cout << c3.getSuit() << " " << c3.getVal() << " Is Less Than " << c2.getSuit() << " " << c2.getVal() << endl;
    }
    else
        cout << c3.getSuit() << " " << c3.getVal() << " Is Greater Than " << c2.getSuit() << " " << c2.getVal() << endl;

    return 0;
}
*/