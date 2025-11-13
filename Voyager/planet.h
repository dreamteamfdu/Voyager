#ifndef PLANET_H
#define PLANET_H
// Standard C++ libraries
#include <algorithm>
#include <array>
#include <iomanip>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>
#include <string>
#include <vector>

// User created libraries
#include "game.h"
#include "rock.h"
#include "plants.h"

// Biomes
enum class Biome {
    Desert,
    Ice,
    Ocean,
    Forest,
    Volcanic,
    GasGiant,
    Urban,
    Barren
};

// Planet class
class Planet {
private:
    std::string id_;
    std::string name_;
    double distanceAU_;
    Biome biome_;
    int lootLevel_;
    std::vector<Rock> rocksOnPlanet_; // Rocks available on the planet
    // Plants ToDo: declare memory for plantsOnPlanet_;
    std::vector<Plants> plantsOnPlanet_; 
    std::array<double, 3> coords_;

public:
    Planet();
    Planet(std::string id, std::string name, double distanceAU, Biome biome,
           int loot, std::array<double, 3>);

    const std::string& getId() const { return id_; }
    const std::string& getName() const { return name_; }
    double getDistanceAU() const { return distanceAU_; }
    Biome getBiome() const { return biome_; }
    std::array<double, 3> getCoordinates() const { return coords_; }


    double travelFuelCost(double fuelPerAU) const;

    std::string quickRow(double fuelPerAU) const;
    std::string describe() const;

    static std::string biomeToString(Biome b);


    void populateRocks(
        const std::vector<Rock>& allRocksInGame); // This will populate Rocks on
                                                  // the planet based on biome

    std::string
    listRocks() const; // this is the list of rocks currently on the planet

    // Plants ToDo: add method definitions to create the flora on a planet & to display the flora on a planet
    void populatePlantsOnPlanet();
    std::string listPlantsOnPlanet();
    int getNumberOfPlantsOnPlanet();   // for testing - returns the # of plants found on the planet
};

// PlanetSysterm will handle displaying and navigating planets
class PlanetSystem {
private:
    std::vector<Planet> planetList;

public:
    std::vector<Planet> getPlanetList() const;
    Planet getPlanetAtIndex(int) const;
    void generatePlanets(int number, const std::vector<Rock>& allRocks);
};

// Planet generator
class PlanetGenerator {
private:
    std::mt19937 rng;

public:
    PlanetGenerator();

    std::string generateName();

    Planet generatePlanet(int, const std::vector<std::array<double, 3>>&);
};
#endif