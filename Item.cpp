/*
  File: Item.cpp

  Author: Elif Meral

  Date: 05/03/25

  Section: 10/14

  E-mail: elifm1@umbc.edu

  Description: This file contains the Item class function definitions.

*/
#include "Item.h"

// Item(const string& name, const vector<string>& requirements
// Constructor to initialize an item with a name and requirements
Item::Item(const string& name, const vector<string>& requirements) {
    m_name = name;           // Set the name of the item
    m_req = requirements;    // Copy the requirements vector
}

// GetName()
// Gets the name of the item
string Item::GetName() const {
    return m_name;
}

// GetReq()
// Gets the list of crafting requirements
const vector<string>& Item::GetReq() const {
    return m_req;
}

