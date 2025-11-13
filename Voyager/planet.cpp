#include "planet.h"
#include "command.h"
#include "game.h"
#include "rock.h"
#include <vector>
#include <array>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

Planet::Planet() = default;

// Planet Class Implementation
Planet::Planet(string id, string name, double distanceAU, Biome biome, int loot, array<double, 3> coords)
    : id_(move(id)), name_(move(name)), distanceAU_(distanceAU), biome_(biome),
      lootLevel_(loot), coords_(coords) {}

string Planet::quickRow(double fuelPerAU) const {
    ostringstream ss;
    ss << "[" << id_ << "] " << name_ << " | " << biomeToString(biome_) << " | "
       << fixed << setprecision(2) << distanceAU_ << " AU"
       << " | Fuel Cost: " << travelFuelCost(fuelPerAU);
    return ss.str();
}

PlanetGenerator::PlanetGenerator() : rng(std::random_device{}()) {}

double Planet::travelFuelCost(double fuelPerAU) const {
    return distanceAU_ * fuelPerAU;
}

string Planet::describe() const {
    ostringstream ss;
    ss << "\n--- " << name_ << " ---\n";
    ss << "Biome: " << biomeToString(biome_) << "\n";
    ss << "Distance: " << fixed << setprecision(2) << distanceAU_ << " AU\n";
    ss << "Loot Level: " << lootLevel_ << "\n";
    ss << "Surface Conditions: "
       << (biome_ == Biome::Volcanic   ? "Molten terrain and unstable geysers."
           : biome_ == Biome::Ocean    ? "Vast seas with strong currents."
           : biome_ == Biome::Forest   ? "Dense vegetation and humid climate."
           : biome_ == Biome::Urban    ? "Ruins of an advanced civilization."
           : biome_ == Biome::Ice      ? "Frozen wastelands under dim sunlight."
           : biome_ == Biome::GasGiant ? "Massive storms and crushing pressure."
           : biome_ == Biome::Desert   ? "Endless dunes and scorching heat."
                                       : "Barren and lifeless terrain.")
       << "\n";
    return ss.str();
}

void Planet::populateRocks(const vector<Rock>& allRocksInGame) {
    // Get the planet's biome as a string
    string biomeName = Planet::biomeToString(this->biome_);

    // Clear any old rocks
    this->rocksOnPlanet_.clear();

    // Loop through the master list of all rocks
    for (const Rock& rock : allRocksInGame) {

        // If the rock's type matches the planet's biome, add it
        if (rock.getElementType() == biomeName) {
            this->rocksOnPlanet_.push_back(rock);
        }
    }
}

string Planet::biomeToString(Biome b) {
    switch (b) {
    case Biome::Desert:
        return "Desert";
    case Biome::Ice:
        return "Ice";
    case Biome::Ocean:
        return "Ocean";
    case Biome::Forest:
        return "Forest";
    case Biome::Volcanic:
        return "Volcanic";
    case Biome::GasGiant:
        return "GasGiant";
    case Biome::Urban:
        return "Urban";
    case Biome::Barren:
        return "Barren";
    }
    return "UNKNOWN";
}

// Plants ToDo: add methods to create the flora on a planet & to display the flora on a planet
        // void populatePlantsOnPlanet();
        // std::string listPlanetsOnPlanet();
void Planet::populatePlantsOnPlanet() {
    if (Planet::biome_ != Biome::Forest) {
        return;   // flora only exists on Forest planets
    }
    else {
        // push a hydrangea on this planet
        plantsOnPlanet_.push_back(Plants(Plants::HYDRANGEA, "A lovely pink hydrangea"));
    }
}

std::string Planet::listPlantsOnPlanet() {
    ostringstream ss;
    ss << "\n--- Plants on the planet ---\n";
    if (plantsOnPlanet_.empty()) {
        ss << "No Flora found.\n";
    }
    else {
        for (Plants& plant : plantsOnPlanet_) {
            ss << "  - " << plant.displayPlantDescription() << "\n";
        }
    }
    return ss.str();
}

// for testing - returns the # of plants found on the planet
int Planet::getNumberOfPlantsOnPlanet() {
    return plantsOnPlanet_.size();
}


Planet PlanetGenerator::generatePlanet(
    int index, const vector<array<double, 3>>& existingCoords) {
    uniform_real_distribution<double> distAU(0.5, 10.0);
    double distance = distAU(rng);

    uniform_int_distribution<int> distBiome(0, 7);
    Biome biome = static_cast<Biome>(distBiome(rng));

    uniform_int_distribution<int> distLoot(1, 10);
    int lootLevel = distLoot(rng);

    uniform_real_distribution<double> distCoord(-50.0, 50.0);

    // Ensure coordinate are unique
    array<double, 3> coords;
    bool unique = false;
    while (!unique) {
        coords = {distCoord(rng), distCoord(rng), distCoord(rng)};
        unique = true;

        for (const auto& c : existingCoords) {
            double dx = coords[0] - c[0];
            double dy = coords[1] - c[1];
            double dz = coords[2] - c[2];
            double dist = sqrt(dx * dx + dy * dy + dz * dz);
            if (dist < 5.0) {
                unique = false;
                break;
            }
        }

        
    }
    // Create a name and ID
    string name = generateName();
    ostringstream id;
    id << "P" << setw(3) << setfill('0') << index;

    // Plants ToDo: add call to create the flora on a planet
    Planet p(id.str(), name, distance, biome, lootLevel, coords);
    p.populatePlantsOnPlanet();

    return p;
}


string PlanetGenerator::generateName() {
    std::vector<std::string> prefixes = {"RX", "M52", "NX", "LX",
                                         "KZ", "ULS", "AD"};
    std::vector<std::string> suffixes = {"-1b",   "-3c", "-Prime", "-Alpha",
                                         "-Vega", "-9",  "-Tau"};
    std::uniform_int_distribution<int> num(10, 999);

    std::string pre = prefixes[rng() % prefixes.size()];
    std::string suf = suffixes[rng() % suffixes.size()];

    std::ostringstream name;
    name << pre << "-" << num(rng) << suf;
    return name.str();
}

string Planet::listRocks() const {
    ostringstream ss;
    ss << "\n--- Harvestable Rocks ---\n";
    if (this->rocksOnPlanet_.empty()) {
        ss << "No harvestable rocks found.\n";
    }
    else {
        for (const Rock& rock : this->rocksOnPlanet_) {
            // We can't use rock.inspect() because it prints to cout.
            // We'll build the string manually.
            ss << "  - " << rock.getName() << " (" << rock.getElementType()
               << ")\n";
        }
    }
    return ss.str();
}

vector<Planet> PlanetSystem::getPlanetList() const { return planetList; }
Planet PlanetSystem::getPlanetAtIndex(int index) const {
    return planetList[index];
}

void PlanetSystem::generatePlanets(int number,
                                   const std::vector<Rock>& allRocks) {
    PlanetGenerator generator;
    vector<array<double, 3>>
        usedCoords; // store coordinates to make sure they are unique

    for (int i = 0; i < number; ++i) {
        Planet p = generator.generatePlanet(i + 1, usedCoords);

        p.populateRocks(allRocks);

        usedCoords.push_back(p.getCoordinates());

        planetList.push_back(p);           // memory management - this 
    }
}