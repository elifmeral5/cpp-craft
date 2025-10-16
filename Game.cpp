/*
  File: Game.cpp

  Author: Elif Meral

  Date: 05/03/25

  Section: 10/14

  E-mail: elifm1@umbc.edu

  Description: This file contains the Game class function definitions.
 */

#include "Game.h"
#include "Area.h"
#include "Hero.h"
#include "Item.h"
using namespace std;

// Game(string filename) - Overloaded Constructor 
// Creates a new Game
Game::Game(string areaFile, string craftFile) {
  m_myHero = nullptr;        // Sets myHero to null
  m_areaFile = areaFile;     // Sets to areaFile
  m_craftFile = craftFile;   // Sets to craftFile
  m_curArea = START_AREA;    // Sets to START_AREA
}

// ~Game() - Destructor
// Deallocates anything dynamically allocated
Game::~Game() {
  // Delete the hero object
  delete m_myHero;

  // Loop through all area pointers and delete each one
  for (size_t i = 0; i < m_areas.size(); i++) {
    delete m_areas[i];
  }

  // Loop through all item pointers and delete each one
  for (size_t j = 0; j < m_items.size(); j++) {
    delete m_items[j];
  }
}

// LoadMap()
// Reads area data from the map file and dynamically creates Area objects. Inserts each new Area into m_myMap in the order encountered.
void Game::LoadMap() {
  // Open the file
  ifstream file(m_areaFile);

  string idString;    // Temp string for id
  string name;        // Temp string for name
  string desc;        // Temp string for description
  string n;           // Temp string for north
  string e;           // Temp string for east
  string s;           // Temp string for south
  string w;           // Temp string for west

  // Read until the end of the file
  while (getline(file, idString, DELIMITER)) {
    // Read fields separated by the delimiter
    getline(file, name, DELIMITER);
    getline(file, desc, DELIMITER);
    getline(file, n, DELIMITER);
    getline(file, e, DELIMITER);
    getline(file, s, DELIMITER);
    getline(file, w);

   // Convert some string data to integers
    int id = stoi(idString);
    int north = stoi(n);
    int east = stoi(e);
    int south = stoi(s);
    int west = stoi(w);

    // Create a new Area object with the parsed data
    Area* area = new Area(id, name, desc, north, east, south, west);
    // Add the new area to the vector of areas
    m_areas.push_back(area);
  }
  // Close file
  file.close();
}

// LoadCraft()
// Reads crafting definitions from the craft file and creates Item objects. Parses each line into an item name and its requirement list.
void Game::LoadCraft() {
  // Opens file
  ifstream file(m_craftFile);
  
  string itemName;     // Name of the item to craft
  string req1;         // first requirement of the item
  string req2;         // second requirement of the item  
  string req3;         // third requirement of the item 
  string req4;         // fourth requirement of the item 

  // Read until the end of the line
  while (getline(file, itemName, DELIMITER)) {

    // Read the four requirement fields
    getline(file, req1, DELIMITER);
    getline(file, req2, DELIMITER);
    getline(file, req3, DELIMITER);
    getline(file, req4);
    
    vector<string> requirements;

    // Only add if there is an actual requirement
    if (req1 != "None") requirements.push_back(req1);
    if (req2 != "None") requirements.push_back(req2);
    if (req3 != "None") requirements.push_back(req3);
    if (req4 != "None") requirements.push_back(req4);

    // Create a new item with its name and requirements
    Item* item = new Item(itemName, requirements);
    m_items.push_back(item);
  }
  // Close file
  file.close();
}

//HeroCreation()
// Prompts the player to enter a hero name and constructs a new Hero.
void Game::HeroCreation() {
  string name;     // Holds Hero's name 
  cout << "Hero Name: ";
  getline(cin, name);

  // Creates new Hero object
  m_myHero = new Hero(name);
}

// Look()
// Displays the current Area’s name, description, and possible exits.
void Game::Look() {
  // Empty lines to display properly
  cout << "" << endl;
  cout << "" << endl;

  // Call PrintArea function of the current area to display its details
  m_areas[m_curArea]->PrintArea();
}

// StartGame()
// Initial start of the whole game with the files loading and creating Hero and playing
void Game::StartGame() {
  // Loads files
  LoadMap();
  LoadCraft();
  cout << "Welcome to UMBC Runescape" << endl;
  // Creates Hero
  HeroCreation();

  // Writes area descrription
  Look();

  // Starts play
  Action();
}

// Action()
// Presents the player with the main menu
void Game::Action() { 
  int choice = 0;     // User choice

  // Continues until valid choice
  while (choice != 6) {

    //Displays options
    cout << "What would you like to do?" << endl;
    cout << "1. Look" << endl;
    cout << "2. Move" << endl;
    cout << "3. Use Area" << endl;
    cout << "4. Craft Item" << endl;
    cout << "5. Inventory" << endl;
    cout <<"6. Quit" << endl;
    cin >> choice;
    cin.ignore();

    // Action according to userr choice
    if (choice == 1) {
      Look();
    } else if (choice == 2) {
      Move();
    } else if (choice == 3) {
      UseArea();
    } else if (choice == 4) {
      CraftItem();
    } else if (choice == 5) {
      m_myHero->DisplayInventory();

      // If user chooses to quit
    } else if (choice == 6) {
      cout << "Thanks for playing!" << endl;
    }
  }
}

// Move()
// Prompts the player for a direction
void Game::Move() {
  string dir;     // chosen direction
  bool check = false;    // checks for valid choice

  // Keeps asking until valid input
  while (!check) {
    cout << "Which direction? (N E S W) " << endl;
    getline(cin,dir);

    char direction = dir[0]; // turns direction into character
    int newIndex = m_areas[m_curArea]->CheckDirection(direction); // Checks for direction availability
    
    // Moves User to area if possible
    if (newIndex != -1) {
      m_curArea = newIndex;
      Look();
      check = true;
    } 
  }
}

// CraftItem()
// Displays Users items to craft
void Game::CraftItem() {
  bool check = false;
  size_t selection;   // User selection 
  // Display all craftable items with numbers
  cout << "Which item would you like to craft?" << endl;
  for (size_t i = 0; i < m_items.size(); ++i) {
    cout << i + 1 << ". " << m_items[i]->GetName() << endl;
  }

  //Prompts user until valid input
  while (!check) {
   cin >> selection;

   // Validate input: check if the selection is within the valid range
    if (selection < 1 || selection > m_items.size()) {
      check = false;
    } else {
      check  = true; 
    }
  }
  
  // Get the selected item
  Item* selectedItem = m_items[selection - 1];
  
  // Check if the Hero can craft the item 
  if (m_myHero->CanCraft(selectedItem->GetReq())) {
    // If the hero can craft it, do the crafting and update inventory
    m_myHero->Craft(selectedItem->GetName(), selectedItem->GetReq());
  } else {
    // If the hero cannot craft it, show an error message
    cout << "Cannot craft " << selectedItem->GetName() << ". Missing requirements." << endl;
  }
}

// UseArea() 
// Gives user the option on what they want to look for in the area
void Game::UseArea() {
  bool check = false;   // Valid input check
  int type;             // Users chosen type

  // Continues to ask user unttil valid choice
  while(!check){
    //Displays choices
    cout << "What would you like to look for?" << endl;
    cout << "1. Raw Materials (Mining)" << endl;
    cout << "2. Natural Resources (Woodcutting/Foraging)" << endl;
    cout << "3. Food (Fishing/Farming)" << endl;
    cout << "4. Hunt" << endl;
    cin >> type;
    cin.ignore();

    // Action based on users choice 
    if (type == 1) {
      m_myHero->Raw();
      check = true;
    } else if (type == 2) {
      m_myHero->Natural();
      check = true;
    } else if (type == 3) {
      m_myHero->Food();
      check = true;
    } else if (type == 4) {
       m_myHero->Hunt();
       check = true;
    }
  }
}
