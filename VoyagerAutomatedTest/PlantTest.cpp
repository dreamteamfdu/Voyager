#include "pch.h"
#include "CppUnitTest.h"
#include <array>
#include <vector>
#include "../Voyager/plants.h"
#include "../Voyager/planet.h"
#include "../Voyager/rock.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

/* 
*  Plants (aka flora) functionality test cases
*  more details to come once we populate the plants.h header file
*/

namespace VoyagerAutomatedTest
{
	TEST_CLASS(PlantTest)
	{
	public:
		// first test method just demonstrates test project runs
		TEST_METHOD(Hello_PlantTest)
		{
			Logger::WriteMessage("Hello from Plant Test Project\n");
		}

		// create a few plant types & verify created correctly
		// this test case verifies the plant constructor as well as the displayPlantDescription() method
		// for now - these are the only methods in the plant class
		TEST_METHOD(Create_Plants) {
			Logger::WriteMessage("Creating a few plants & verifying created correctly and accessible\n");
			std::string pinkHydrangeaDescription = "a lovely pink hydrangea";
			Plants pink(Plants::HYDRANGEA, pinkHydrangeaDescription);
			Assert::AreEqual(pinkHydrangeaDescription, pink.displayPlantDescription());
			Logger::WriteMessage("passed pinkHydrangeaDescription test\n");

			std::string blueHydrangeaDescription = "a striking blue hydrangea";
			Plants blue(Plants::HYDRANGEA, blueHydrangeaDescription);
			Assert::AreEqual(blueHydrangeaDescription, blue.displayPlantDescription());
			Logger::WriteMessage("passed blueHydrangeaDescription test\n");
		}

		// next create some planets - but this needs us to generate the next set of code changes
		//   this test case prints out the flora messages (including no flora), using the planet method listPlantsOnPlanet
		//   it also verifies that exactly ONE plant is created on Forest planets & no plants are created on all other planets
		//   this test required a method in the planet class to return the # of flowers on the planet - net: useful for testing only
		TEST_METHOD(Create_Planets) {
			Logger::WriteMessage("Create some planets & verify the flora is created correctly\n");

			// verify that I can create 5 forest planets & will see 5 an hydrangea on each planet

			// following code is lifted from the PlanetSystem::generatePlanets method to create planets
			PlanetGenerator generator;
			std::vector<Planet> planetList;
			std::vector<std::array<double, 3>> usedCoords; // store coordinates to make sure they are unique

			for (int i = 0; i < 10; ++i) {
				Planet p = generator.generatePlanet(i + 1, usedCoords);
				usedCoords.push_back(p.getCoordinates());
				planetList.push_back(p);
				// Once the planets are created, verify that planets with a forest biome have hydrangers
				std::string s;
				s = "Planet " + p.getName();
				s += " created with biome " + p.biomeToString(p.getBiome());
				s += " with flora " + p.listPlantsOnPlanet() + "\n";
				Logger::WriteMessage(s.c_str());
				if (p.getBiome() == Biome::Forest) {
					Assert::IsTrue(p.getNumberOfPlantsOnPlanet() == 1, L"Expected one plant on the planet, but zero or large # returned");
				}
				else {
					Assert::IsTrue(p.getNumberOfPlantsOnPlanet() == 0, L"Non-forest planet, expected no plants on the planet, but non-zero plants found");
				}
			}
		}
	};
}
