#include <iostream>
#include<vector>
using namespace std;


/*void displayTitle() {
    cout << R"(
                   _______  ______
    /\     |\    | |  |  |  |         /\    |-----| |\        /|
   /  \    | \   |    |     |        /  \   |     | | \      / |
  /----\   |  \  |    |     |_____  /----\  |-----| |  \    /  |
 /      \  |   \ |    |     |      /      \ | \     |   \  /   |
/        \ |    \|    |     |     /        \|  \    |    \/    | By Ejaz Ahmed
)" << "\n";
    
}
void displayHelp() {
    cout << "\nAvailable Commands:\n" ;
    cout << "1. spawn X Y Species"
         << " - Create new colony at (X,Y) of specified species\n";
    cout << "2. give ID Resource Amount" 
         << " - Give resources to colony (food)\n";
    cout << "3. tick [N]" 
         << " - Advance simulation by N ticks (default 1)\n";
    cout << "4. summary ID"  
         << " - Display colony status\n";
    cout << "5. Active" 
         << " - Show all active colonies\n";
    cout << "6. species" 
         << " - List available species\n";
    cout << "7. help" 
         << " - Show this help menu\n";
    cout << "8. Exit" 
         << " - Exit simulation\n";
}
void displaySpecies() {
    cout <<  "\nAvailable Species:\n" ;
}*/
struct SpeciesInfo {
    string name;
    string description;
    int attack;
    int defense;
    int harvesting;
};
const vector<SpeciesInfo> SPECIES_LIST = {
    {"FireAnts",     "known for their painful stings", 30, 10, 5 }, {"BulletAnts",   "extremely painful sting", 35, 15, 15},
    {"leafCutters",    "ability to cut leaves", 10, 30, 10  }, {"Warriors",    "their massive colonies", 30, 15,10   },
    {"CarpenterAnts",     "build nests by excavating wood", 5, 20, 15 }, {"VelvetAnts",     "a type of wasp", 15, 15, 15 }, {"BulldogAnts",       "powerful jaws and stings", 35, 25, 5  },
    {"ArgentineAnts",       "forming supercolonies", 20, 30, 20}, {"RedHarvester Ants",        "harvesting seeds", 15, 25, 10},
    {"WeaverAnts",     "weaving leaves together", 12, 15, 12, }
};
void displaySpecies() {
    cout  << "\nAvailable Species:\n" ;

    for (const auto& species : SPECIES_LIST) {
        cout << species.name 
             << ": " << species.description <<" and " << "Attack: " << species.attack << "  Defense: " << species.defense<< "  Harvesting: " << species.harvesting << "\n";
    }
}
int main() {
   // displayTitle();
   displaySpecies();
    return 0;
}