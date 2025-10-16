/*
  File: Area.cpp

  Author: Elif Meral

  Date: 05/03/25

  Section: 10/14

  E-mail: elifm1@umbc.edu

  Description: This file contains the Area class function definitions.
*/

#include "Area.h"

// Area (Overloaded Constructor)
// Initializes variables to create a new area
Area::Area(int id, string name, string desc, int North, int East, int South, int West) {
  m_ID = id;                  // Unique area ID
  m_name = name;              // Area name
  m_desc = desc;              // Area Description
  m_direction[n] = North;     // North Direction
  m_direction[e] = East;      // East Direction
  m_direction[s] = South;     // South Direction
  m_direction[w] = West;      // West Direction
}

// GetName()
// Returns area name as string
string Area::GetName() {
  return m_name;    
}

// GetID()
// Returns area id as int
int Area::GetID() {
  return m_ID;
}

// GetDesc()
// Returns area desc as string
string Area::GetDesc() {
  return m_desc;
}

// CheckDirection(char myDirection)
// Checks the direction and return the ID of the area in that direction
int Area::CheckDirection(char myDirection) {
  // Return area ID if a valid direction is provided
  switch (myDirection) {
  case 'n':
    return m_direction[n];  // North
  case 'e':
    return m_direction[e];  // East
  case 's':
    return m_direction[s];  // South
  case 'w':
    return m_direction[w];  // West
  case 'N':
    return m_direction[N];  // North
  case 'E':
    return m_direction[E];  // East
  case 'S':
    return m_direction[S];  // South
  case 'W':
    return m_direction[W];  // West
  default:
    return -1;              // Invalid direction
  }
}

// PrintArea()
// Prints details of area with its name, description, and exits
void Area::PrintArea() {
  cout << m_name << endl;
  cout << m_desc << endl;
  cout << "Possible Exits: ";
  
  // Checks and prints possible exits for each direction
  if (m_direction[n] != -1) cout << "N ";
  if (m_direction[e] != -1) cout << "E ";
  if (m_direction[s] != -1) cout << "S ";
  if (m_direction[w] != -1) cout << "W ";
  
  cout << endl;
}
