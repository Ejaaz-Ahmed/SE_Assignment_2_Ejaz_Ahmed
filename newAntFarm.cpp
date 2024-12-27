#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <random>
#include <string>
#include <algorithm>
#include <sstream>
#include <iomanip>
using namespace std;
void displayTitle() {
    cout << R"(
                   _______  ______          _______
    /\     |\    | |  |  |  |         /\    |     | |\        /|
   /  \    | \   |    |     |        /  \   |     | | \      / |
  /----\   |  \  |    |     |_____  /----\  |-----| |  \    /  |
 /      \  |   \ |    |     |      /      \ | \     |   \  /   |
/        \ |    \|    |     |     /        \|  \    |    \/    | By Ejaz Ahmed
)" << "\n";   
}
class AntFarm;          //forward declaring
class Resources;
struct AntSpecies {     //structure for attributes
    string name;
    string description;
    int baseAttack;
    int baseDefense;
    int resourceEfficiency;        //for displaying the efficiency
    string specialAbility;
};
// Ant Species Database
class AntSpeciesDatabase {
private:
  static std::map<string, AntSpecies> species; //using build-in "map"
public:
    static void initialize() {
        species = {             //map
            {"FireAnt", {
                "FireAnt",
                "Aggressive species with powerful bite",
                8, 5, 3,
                "Enhanced damage in combat"
            }},{"HarvesterAnt", {
                "HarvesterAnt",
                "Specialized in gathering resources",
                4, 4, 9,
                "Double resource collection"
            }},{"CarpenterAnt", {
                "CarpenterAnt",
                "Expert builders and wood specialists",
                5, 7, 6,
                "Can build extra rooms"
            }},{"WeaveAnt", {
                "WeaveAnt",
                "Known for creating intricate nests",
                4, 8, 5,
                "Enhanced defense structures"
            }},{"ArmyAnt", {
                "ArmyAnt",
                "Highly aggressive raiders",
                9, 4, 4,
                "Group attack bonus"
            }},{"LeafcutterAnt", {
                "LeafcutterAnt",
                "Fungus farmers with complex societies",
                5, 5, 8,
                "Can grow food resources"
            }},{"BulldogAnt", {
                "BulldogAnt",
                "Large and aggressive hunters",
                9, 6, 4,
                "High individual combat power"
            }},{"TrapjawAnt", {
                "TrapjawAnt",
                "Lightning-fast hunters",
                7, 5, 6,
                "First strike in combat"
            }},{"HoneyPotAnt", {
                "HoneyPotAnt",
                "Living food storage vessels",
                3, 7, 8,
                "Enhanced food storage"
            }}, {"Slavemaker", {
                "Slavemaker",
                "Raiders that capture other ants",
                8, 5, 5,
                "Can convert enemy ants"
            }},{"DriverAnt", {
                "DriverAnt",
                "Highly organized swarm raiders",
                8, 6, 5,
                "Swarm attack bonus"
            }},{"GiantAnt", {
                "GiantAnt",
                "Largest and most durable species",
                7, 9, 4,
                "Enhanced health pool"
            }}
        };
    }
    static const AntSpecies& getSpecies(const string& name) {
        auto it = species.find(name);
        if (it == species.end()) {
            throw std::runtime_error("Invalid ant species: " + name);
        }
        return it->second;
    }
    static void listSpecies() {
        cout << "\nAvailable Ant Species:\n";
        cout << setw(15) << "Name" << "  "<< setw(8) << "Attack" << "  "
        << setw(8) << "Defense" << "  "<< setw(11) << "Efficiency" << "  "
         << "Special Ability\n";
        for (const auto& [name, spec] : species) {
            cout << setw(15) << spec.name << "  "<< setw(8) << spec.baseAttack << " | "
                     << setw(8) << spec.baseDefense << "  "<< setw(11) << spec.resourceEfficiency << "  "<< spec.specialAbility << "\n";
        }
    }
};
map<string, AntSpecies> AntSpeciesDatabase::species;
// Singleton: Meadow Class
class Meadow {
private:
    static Meadow* instance;
    vector<std::shared_ptr<AntFarm>> antFarms;
    Meadow() {}
public:
    static Meadow* getInstance() {
        if (!instance) {
            instance = new Meadow();
        }
        return instance;
    }
    void spawnAntFarm(const std::string& species, int x, int y);
    void giveResources(int id, const std::string& resource, int amount);
    void performTicks(int ticks);
    void summary(int id);
    size_t getAntFarmCount() const { return antFarms.size(); }
    std::shared_ptr<AntFarm> getAntFarm(int id) const {
        return (id >= 0 && id < antFarms.size()) ? antFarms[id] : nullptr;
    }
};
Meadow* Meadow::instance = nullptr;
// Resource Management
class Resources {
private:
    std::map<std::string, int> resources;
public:
    void add(const std::string& resource, int amount) {
        resources[resource] += amount;
    }
    int get(const std::string& resource) const {
        auto it = resources.find(resource);
        return (it != resources.end()) ? it->second : 0;
    }
    void display() const {
        for (const auto& [resource, amount] : resources) {
            std::cout << "  " << resource << ": " << amount << "\n";
        }
    }
};
// Decorator: Ant Attributes
class Ant {
protected:
    std::string type;
    int strength;
    int efficiency;
public:
    Ant(const std::string& type, int strength, int efficiency) 
        : type(type), strength(strength), efficiency(efficiency) {}  
    virtual void displayAttributes() = 0;
    virtual int getStrength() const { return strength; }
    virtual int getEfficiency() const { return efficiency; }
    virtual std::string getType() const { return type; }
    virtual ~Ant() {}
};
class BaseAnt : public Ant {
public:
    BaseAnt() : Ant("Worker", 1, 1) {}
    
    void displayAttributes() override {
        std::cout << "Type: " << type << ", Strength: " << strength << ", Efficiency: " << efficiency;
    }
};
class StrongAnt : public Ant {
    std::shared_ptr<Ant> ant;
public:
    StrongAnt(std::shared_ptr<Ant> ant) : Ant(ant->getType(), ant->getStrength() * 2, ant->getEfficiency()), ant(ant) {}
    void displayAttributes() override {
        ant->displayAttributes();
        std::cout << " (Enhanced Strength)";
    }
};
class EfficientAnt : public Ant {
    std::shared_ptr<Ant> ant;
public:
    EfficientAnt(std::shared_ptr<Ant> ant) : Ant(ant->getType(), ant->getStrength(), ant->getEfficiency() * 2), ant(ant) {}
    void displayAttributes() override {
        ant->displayAttributes();
        std::cout << " (Enhanced Efficiency)";
    }
};
// Factory: Create Ants
class AntFactory {
public:
    enum AntType { Worker, Warrior, Scout };    //Related items in one plase
    static std::shared_ptr<Ant> createAnt(AntType type) {       //shared_ptr (smart pointers)
        switch (type) {
            case Worker:
                return std::make_shared<BaseAnt>();
            case Warrior:
                return std::make_shared<StrongAnt>(std::make_shared<BaseAnt>());
            case Scout:
                return std::make_shared<EfficientAnt>(std::make_shared<BaseAnt>());
            default:
                return nullptr;
        }
    }
};
// Builder: AntFarm
class AntFarm {
private:
    std::string species;
    int x, y;
    std::vector<std::string> rooms;
    std::vector<std::shared_ptr<Ant>> ants;
    Resources resources;
    int health;
public:
    AntFarm(const std::string& species, int x, int y) 
        : species(species), x(x), y(y), health(100) {}
    void addRoom(const std::string& room) {
        rooms.push_back(room);
    }
    void addAnt(std::shared_ptr<Ant> ant) {
        ants.push_back(ant);
    }
    void addResources(const std::string& resource, int amount) {
        resources.add(resource, amount);
    }
    void battle(std::shared_ptr<AntFarm> otherFarm) {
        int totalStrength = 0;
        for (const auto& ant : ants) {
            totalStrength += ant->getStrength();
        }   
        int otherStrength = 0;
        for (const auto& ant : otherFarm->ants) {
            otherStrength += ant->getStrength();
        }
        if (totalStrength > otherStrength) {
            otherFarm->health -= 20;
            std::cout << species << " won the battle against " << otherFarm->species << "!\n";
        } else if (totalStrength < otherStrength) {
            health -= 20;
            std::cout << otherFarm->species << " won the battle against " << species << "!\n";
        } else {
            std::cout << "The battle between " << species << " and " << otherFarm->species << " ended in a draw!\n";
        }
    }
    void rest() {
        health = std::min(100, health + 10);
        for (const auto& ant : ants) {
            if (ant->getType() == "Worker") {
                resources.add("food", ant->getEfficiency());
            }
        }
    }
    void summary() {
        std::cout << "\nColony Summary:\n";
        std::cout << "Species: " << species << "\n";
        std::cout << "Location: (" << x << ", " << y << ")\n";
        std::cout << "Health: " << health << "\n";
        std::cout << "Rooms: " << rooms.size() << "\n";
        std::cout << "Ants: " << ants.size() << "\n";   
        std::cout << "Resources:\n";
        resources.display();
        std::cout << "Ant Details:\n";
        for (const auto& ant : ants) {
            std::cout << "  ";
            ant->displayAttributes();
            std::cout << "\n";
        }
    }
    bool isDead() const { return health <= 0; }
    std::string getSpecies() const { return species; }
};
// Implementation of Meadow methods
void Meadow::spawnAntFarm(const std::string& species, int x, int y) {
    auto antFarm = std::make_shared<AntFarm>(species, x, y);
    // Add some initial ants
    antFarm->addAnt(AntFactory::createAnt(AntFactory::Worker));
    antFarm->addAnt(AntFactory::createAnt(AntFactory::Warrior));
    antFarm->addAnt(AntFactory::createAnt(AntFactory::Scout));
    // Add some initial rooms
    antFarm->addRoom("Nursery");
    antFarm->addRoom("Storage");
    int newId = antFarms.size();  // Get the ID before adding
    antFarms.push_back(antFarm);
    std::cout << "AntFarm of species " << species << " spawned at (" << x << ", " << y << ") with ID: " << newId << "\n";
}
void Meadow::giveResources(int id, const std::string& resource, int amount) {
    if (id >= 0 && id < antFarms.size()) {
        antFarms[id]->addResources(resource, amount);
        std::cout << "Gave " << amount << " " << resource << " to colony " << id << ".\n";
    } else {
        std::cout << "Invalid colony ID." << std::endl;
    }
}
void Meadow::performTicks(int ticks) {
    std::random_device rd;
    std::mt19937 gen(rd());         //random number generation
    std::uniform_int_distribution<> dis(0, antFarms.size() - 1);
    for (int t = 0; t < ticks; ++t) {
        std::cout << "\nTick " << (t + 1) << ":\n";
        // Random encounters and battles
        if (antFarms.size() > 1) {
            int farm1 = dis(gen);
            int farm2 = dis(gen);
            if (farm1 != farm2) {
                antFarms[farm1]->battle(antFarms[farm2]);
            }
        }
        // Rest and resource gathering
        for (auto& farm : antFarms) {
            farm->rest();
        }
        // Remove dead colonies
        antFarms.erase(
            std::remove_if(antFarms.begin(), antFarms.end(),
                [](const auto& farm) { return farm->isDead(); }),
            antFarms.end());
    }
}
void Meadow::summary(int id) {
    if (id >= 0 && id < antFarms.size()) {
        antFarms[id]->summary();
    } else {
        std::cout << "Invalid colony ID." << std::endl;
    }
}
// Helper function to display commands
void displayHelp() {
    std::cout << "\nAvailable commands:\n"
              << "  species                         =>  List all available ant species\n"  // Added this line
              << "  spawn <x> <y> <species>         =>  Create a new ant colony\n"
              << "  give <id> <resource> <amount>   =>  Give resources to a colony\n"
              << "  tick [number]                   =>  Simulate specified number of ticks (default: 1)\n"
              << "  summary <id>                    =>  Display colony summary\n"
              << "  Colonies data                   =>  List all colonies\n"
              << "  help                            =>  Display this help message\n"
              << "  exit                            =>  Exit the simulation\n";
}
int main() {
    displayTitle();
    AntSpeciesDatabase::initialize();  // Initialize the species database
    Meadow* meadow = Meadow::getInstance();
    cout << "Welcome to AntFarm Simulation!\n";
    displayHelp();
    string command;
    while (true) {
        cout << "\nEnter command: ";
        getline(cin, command);
        istringstream iss(command);
        string cmd;
        iss >> cmd;
        try {
            if (cmd == "exit") {
                break;
            } else if (cmd == "help") {
                displayHelp();
            } else if (cmd == "species") {  // Add this new command
                AntSpeciesDatabase::listSpecies();
            } else if (cmd == "spawn") {
                int x, y;
                string species;
                if (iss >> x >> y >> species) {
                    meadow->spawnAntFarm(species, x, y);
                } else {
                    cout << "Usage: spawn <x> <y> <species>\n";
                }
            } else if (cmd == "give") {
                int id, amount;
                string resource;
                if (iss >> id >> resource >> amount) {
                    meadow->giveResources(id, resource, amount);
                } else {
                    cout << "Usage: give <id> <resource> <amount>\n";
                }
            } else if (cmd == "tick") {
                int ticks = 1;
                iss >> ticks;
                meadow->performTicks(ticks);
            } else if (cmd == "summary") {
                int id;
                if (iss >> id) {
                    meadow->summary(id);
                } else {
                    cout << "Usage: summary <id>\n";
                }
            } else if (cmd == "list") {
                cout << "\nActive Colonies:\n";
                for (size_t i = 0; i < meadow->getAntFarmCount(); ++i) {
                    auto farm = meadow->getAntFarm(i);
                    cout << "ID " << i << ": " << farm->getSpecies() << "\n";
                }
            } else {
                cout << "Invalid command. Type 'help' for available commands.\n";
            }
        } catch (const std::exception& e) {
            cout << "Error: " << e.what() << "\n";
        }
    }
    return 0;
}