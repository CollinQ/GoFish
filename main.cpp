#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include "utility.h"
#include "cards.h"

using namespace std;

int main(int argv, char **argc)
{
  if (argv < 3)
  {
    cout << "Please provide 2 file names" << endl;
    return 1;
  }

  ifstream cardFile1(argc[1]);
  ifstream cardFile2(argc[2]);
  string line;

  if (cardFile1.fail() || cardFile2.fail())
  {
    cout << "Could not open file " << argc[2];
    return 1;
  }

  CardsBST BST1;
  CardsBST BST2;
  // Read each file
  while (getline(cardFile1, line) && (line.length() > 0))
  {
    string suitcp = line.substr(0, 1);
    char suit[1];
    strcpy(suit, suitcp.c_str());
    string val = line.substr(2, 2);
    Cards card;
    card.setCard(suit[0], val);
    BST1.insert(card);
  }

  cardFile1.close();

  while (getline(cardFile2, line) && (line.length() > 0))
  {
    string suitcp = line.substr(0, 1);
    char suit[1];
    strcpy(suit, suitcp.c_str());
    string val = line.substr(2, 2);
    Cards card;
    card.setCard(suit[0], val);
    BST2.insert(card);
  }
  cardFile2.close();

  Cards nullCard('z', "0");

  /*cout << "Alice's Cards: " << endl;
  BST1.printInOrder();
  cout << "Bob's Cards: " << endl;
  BST2.printInOrder();*/

  // GO FISH TIME
  Cards a = BST1.findMin();
  // goitcout << "Alice Min: " << a.getSuit() << " " << a.getVal() << endl;
  Cards b = BST2.findMax();
  // cout << "Bob Max: " << b.getSuit() << " " << b.getVal() << endl;

  Cards aMax = BST1.findMax();
  // cout << "Alice Max: " << aMax.getSuit() << " " << aMax.getVal() << endl;
  Cards bMin = BST2.findMin();
  // cout << "Bob Min: " << bMin.getSuit() << " " << bMin.getVal() << endl;

  while (!(a == nullCard) && !(b == nullCard))
  {

    // ALICE TURN

    // cout << "ALICE: " << endl;
    if (BST2.contains(a))
    {
      BST2.remove(a);
      cout << "Alice picked matching card " << a.getSuit() << " " << a.getVal() << endl;
      Cards newA = BST1.getSuccessor(a);
      BST1.remove(a);
      a = newA;
    }
    else if (!BST2.contains(a))
    {
      while (!(a == nullCard))
      {
        // cout << "Alice:" << a.getSuit() << " " << a.getVal() << endl;
        Cards newA = BST1.getSuccessor(a);
        a = newA;
        if (BST2.contains(a))
        {
          BST2.remove(a);
          cout << "Alice picked matching card " << a.getSuit() << " " << a.getVal() << endl;
          Cards newA = BST1.getSuccessor(a);
          BST1.remove(a);
          a = newA;
          break;
        }
      }
    }
    //   cout << "Bob: " << b.getSuit() << " " << b.getVal() << endl;

    // cout << "BOB: " << endl;
    if (BST1.contains(b))
    {
      BST1.remove(b);
      // cout << "Removed" << endl;
      cout << "Bob picked matching card " << b.getSuit() << " " << b.getVal() << endl;
      Cards newB = BST2.getPredecessor(b);
      BST2.remove(b);
      b = newB;
    }
    else if (!BST1.contains(b))
    {
      // cout << "Not Removed" << endl;
      while (!(b == nullCard))
      {
        Cards newB = BST2.getPredecessor(b);
        b = newB;
        // cout << "Bob: " << b.getSuit() << " " << b.getVal() << endl;
        if (BST1.contains(b))
        {
          BST1.remove(b);
          cout << "Bob picked matching card " << b.getSuit() << " " << b.getVal() << endl;
          Cards newB = BST2.getPredecessor(b);
          BST2.remove(b);
          b = newB;
          break;
        }
      }
    }
  }
  cout << endl
       << "Alice's cards: " << endl;
  BST1.printInOrder();
  cout << endl
       << "Bob's cards: " << endl;
  BST2.printInOrder();
  return 0;
}
