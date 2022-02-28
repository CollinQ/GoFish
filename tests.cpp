#include <iostream>
#include "cards.h"
#include "utility.h"
using namespace std;

int main()
{

    /*  alice cards
    c j
    s 10

        bob cards
    c 9
    d 2
    */

    CardsBST Alice, Bob;
    Cards cJ('c', "j");
    Cards s10('s', "10");
    Cards c6('c', "6");
    Cards c9('c', "9");
    Cards c5('c', "5");
    Cards d2('d', "2");
    Cards hK('h', "k");

    Cards nullCard('z', "0");

    Alice.insert(cJ);
    Alice.insert(s10);
    Alice.insert(c6);
    Alice.insert(hK);
    Alice.insert(c9);
    Alice.insert(d2);
    Bob.insert(d2);
    Bob.insert(c9);
    Bob.insert(hK);
    Bob.insert(c6);

    cout << "Testing In Order" << endl;
    cout << "Alice's Hand: " << endl;
    Alice.printInOrder();
    cout << "Bob's Hand: " << endl;
    Bob.printInOrder();

    cout << "Successors / Predecessors Test" << endl;
    Cards p = Alice.getPredecessor(cJ);
    cout << "Predecessor: " << p.getSuit() << " " << p.getVal() << endl;
    cout << "Predecessor: " << Bob.getPredecessor(d2).getSuit() << " " << Bob.getPredecessor(d2).getVal() << endl;
    cout << "Successor: " << Alice.getSuccessor(cJ).getSuit() << " " << Alice.getSuccessor(cJ).getVal() << endl;
    cout << "Successor: " << Bob.getSuccessor(d2).getSuit() << " " << Bob.getSuccessor(d2).getVal() << endl;

    cout << "Max / Min Test" << endl;
    cout << "Alice's Max: " << Alice.findMax().getSuit() << " " << Alice.findMax().getVal() << endl;
    cout << "Alice's Min: " << Alice.findMin().getSuit() << " " << Alice.findMin().getVal() << endl;
    cout << "Bob's Max: " << Bob.findMax().getSuit() << " " << Bob.findMax().getVal() << endl;
    cout << "Bob's Min: " << Bob.findMin().getSuit() << " " << Bob.findMin().getVal() << endl;

    Cards aMin = Alice.findMin();
    Cards bMax = Bob.findMax();

    bool alBob = true;
    // while true, alice picks. while false, bob picks.

    while (!(aMin == nullCard) & !(bMax == nullCard))
    {
        cout << "Alice's cards: \n";
        Alice.printPreOrder();

        while (alBob && !(aMin == nullCard))
        {
            if (Bob.contains(aMin))
            {
                cout << "Alice picked a matching card ";
                aMin.printCard();
                Bob.remove(aMin);
                Cards a = Alice.getSuccessor(aMin);
                Alice.remove(aMin);
                cout << "Alice's cards: \n";
                Alice.printPreOrder();
                aMin = a;
                alBob = false;
            }
            else
            {
                Cards a = Alice.getSuccessor(aMin);
                aMin = a;
            }
        }

        while (!alBob && !(bMax == nullCard))
        {
            if (Alice.contains(bMax))
            {
                cout << "Bob picked a matching card ";
                bMax.printCard();
                Alice.remove(bMax);
                Cards b = Bob.getPredecessor(bMax);
                Bob.remove(bMax);
                bMax = b;
                alBob = true;
            }
            else
            {
                Cards b = Bob.getPredecessor(bMax);
                bMax = b;
            }
        }
    }

    cout << "Alice's cards: \n";
    Alice.printInOrder();
    cout << "Bob's cards: \n";
    Bob.printInOrder();

    return 0;
}
