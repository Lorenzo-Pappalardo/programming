#include <iostream>
#include <vector>

using namespace std;

class Unit {
  string name;
  int valueInCents;

public:
  Unit(string name, int valueInCents) {
    this->name = name;
    this->valueInCents = valueInCents;
  }

  const string getName() const { return name; }

  const int getValueInCents() const { return valueInCents; }
};

const vector<Unit *> units = vector<Unit *>{
    new Unit("Dollar", 100), new Unit("Quarter", 25), new Unit("Dime", 10),
    new Unit("Nickel", 5), new Unit("Penny", 1)};

class Change {
  const Unit *unit;
  int pieces;

public:
  Change(const Unit *unit) {
    this->unit = unit;
    pieces = 0;
  }

  const void addPiece() { pieces++; }

  const Unit *getUnit() const { return unit; }

  const int getPieces() const { return pieces; }

  const string toString() const {
    return unit->getName() + ": " +
           to_string((unit->getValueInCents() * pieces));
  }
};

vector<Change *> getChange(int *cents) {
  vector<Change *> cuts;

  for (Unit *unit : units) {
    cuts.push_back(new Change(unit));
  }

  int i{0};
  while (i < cuts.size()) {
    const Unit *currentUnit = cuts.at(i)->getUnit();
    const int unitsCents = currentUnit->getValueInCents();

    if (*cents >= unitsCents) {
      cuts.at(i)->addPiece();
      (*cents) -= unitsCents;
    } else {
      i++;
    }
  }

  return cuts;
}

int main() {
  cout << "[Coin Change]" << endl;

  for (Unit *unit : units) {
    cout << unit->getName() << ": " << unit->getValueInCents() << " cents"
         << endl;
  }

  cout << endl << "Enter the amount of cents to convert: ";
  int cents;
  cin >> cents;

  if (cents < 0) {
    cerr << "Only positive values are accepted!" << endl;
    return -1;
  }

  cout << endl << "Computed change:" << endl;
  for (Change *cut : getChange(&cents)) {
    cout << cut->getUnit()->getName() << ": " << cut->getPieces() << endl;
  }
}