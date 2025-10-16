/*
  File: Hero.cpp

  Author: Elif Meral

  Date: 05/03/25

  Section: 10/14

  E-mail: elifm1@umbc.edu

  Description: This file contains the Hero class function definitions.
*/

#include "Hero.h"

// Hero(const string& name)
// Contains Heros name
Hero::Hero(const string& name) {
  m_name = name;
}

// ~Hero()
// Destructor
Hero::~Hero() {}

// GetName() const
// Returns Heros name
string Hero::GetName() const {
  return m_name;
}

// SetName(const string& name)
// Sets the Heros name
void Hero::SetName(const string& name) {
  m_name = name;
}

// DisplayInventory() cons
// Displays the Heros inventory
void Hero::DisplayInventory() const {
  cout << "******* INVENTORY *******" << endl;
  cout << m_inventory;
}

// CollectItem(const string& item)
// Increases amount of a collected item
void Hero::CollectItem(const string& item) {

  try {
    // Gets current amount of the item
    int count = m_inventory.At(item)->GetValue();
    // Increases item by one
    m_inventory.Update(item, count + 1);
  } catch (const out_of_range&) {
    // If item was not already in inventory there is now one of it
    m_inventory.Insert(item, 1);
  }
}

// CanCraft(const vector<string>& requirements) const
// Checks if chosen item can be crafted
bool Hero::CanCraft(const vector<string>& requirements) const {
for (size_t i = 0; i < requirements.size(); ++i) {
  string req = requirements[i];
  try {
    // Gets the amount the hero has of the required item

    Item* item = m_inventory.At(req);
    if (!item) {
      return false; // Item not found in inventory
    }
    int qty = item->GetValue();
    //  int qty = m_inventory.At(req)->GetValue();
    // If there is less than one then it can not be crafted
    if (qty < 1) {
      return false;
    }
  } catch (const out_of_range&) {
    return false;
  }
 }
// If all requirements are found the item can be crafted
 return true;
}

// Craft(const string& result, const vector<string>& requirements)
// Crafts the item
void Hero::Craft(const string& result, const vector<string>& requirements) {
  // The required item is lessened by one after crafted
  for (size_t i = 0; i < requirements.size(); i++) {
    int count = m_inventory.At(requirements[i])->GetValue();
    m_inventory.Update(requirements[i], count - 1);
  }
  
  CollectItem(result);
  cout << "Crafted: " << result << "!" << endl;
}

// Raw()
// Displays results for Raw products
void Hero::Raw() {
  Gather(RawProducts, "You mined and found nothing.", "You mined and found some ");
}

// Natural(0
// Displays results for natural products
void Hero::Natural() {
  Gather(NaturalProducts, "You searched and found nothing.", "You searched and harvested some ");
}

// Food()
// Displays results for Food Products
void Hero::Food() {
  Gather(FoodProducts, "You searched and found nothing.", "You searched and harvested some ");
}

// Hunt()
// Displays results for Hunted products
void Hero::Hunt() {
  Gather(HuntProducts, "You hunted aand found nothing.", "You went hunting and got some ");
}

//Gather(const vector<string>& products, const string& noItemMsg, const string& foundMsg)
// Gives a random message based on users choice
void Hero::Gather(const vector<string>& products, const string& noItemMsg, const string& foundMsg) {
  // gets a random index
  size_t index = rand() % (products.size() + 1);
  if (index == products.size()) {
    cout << noItemMsg << endl;
  } else {
    string item = products[index];
    cout << foundMsg << item << "!" << endl;
    CollectItem(item);
  }
}
