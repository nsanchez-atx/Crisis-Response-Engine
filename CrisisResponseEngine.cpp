/*
Nathan Sanchez

This program simulates outbreak conditions across connected regions.
Users can enter patient data, view regions, generate crises, rank patients
by risk, and transfer vaccines between connected regions.
*/

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

// Reads any integer from the user.
int readInt(string prompt)
{
    int value;

    while (true)
    {
        cout << prompt;

        if (cin >> value)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Please enter a valid number." << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Reads an integer within a given range.
int readInt(int minValue, int maxValue, string prompt)
{
    int value;

    while (true)
    {
        cout << prompt;

        if (cin >> value && value >= minValue && value <= maxValue)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }

        cout << "Please enter a number from "
             << minValue << " to " << maxValue << "." << endl;

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Reads a full line of text.
string readLine(string prompt)
{
    string value;

    cout << prompt;
    getline(cin, value);

    return value;
}

// Generates a random integer in the given range.
int randInt(int minValue, int maxValue)
{
    return minValue + rand() % (maxValue - minValue + 1);
}

struct Person
{
    string name;
    int age;
    bool immunocompromised;
    bool essentialWorker;
    int exposureLevel;
    int riskScore;
};

struct Region
{
    string name;
    int vaccineSupply;
    int outbreakLevel;
    vector<Person> residents;
};

// Places patients with higher risk scores first.
struct CompareRisk
{
    bool operator()(const Person& a, const Person& b) const
    {
        return a.riskScore < b.riskScore;
    }
};

// Calculates a patient's risk score.
int calculateRisk(const Person& person, int outbreakLevel)
{
    int score = 0;

    if (person.age >= 65)
    {
        score += 40;
    }
    else if (person.age >= 50)
    {
        score += 25;
    }

    if (person.immunocompromised)
    {
        score += 35;
    }

    if (person.essentialWorker)
    {
        score += 15;
    }

    score += person.exposureLevel * 5;
    score += outbreakLevel;

    return score;
}

// Randomly increases outbreaks and decreases vaccine supplies.
void generateCrisis(map<string, Region>& regions)
{
    for (auto& regionPair : regions)
    {
        Region& region = regionPair.second;

        region.outbreakLevel += randInt(5, 25);

        int vaccineLoss = randInt(0, 10);

        if (vaccineLoss <= region.vaccineSupply)
        {
            region.vaccineSupply -= vaccineLoss;
        }

        for (Person& person : region.residents)
        {
            person.riskScore =
                calculateRisk(person, region.outbreakLevel);
        }
    }
}

// Displays patient information.
void displayPerson(const Person& person)
{
    cout << "Name: " << person.name << endl;
    cout << "Risk Score: " << person.riskScore << endl;
    cout << "Age: " << person.age << endl;
    cout << "Exposure Level: " << person.exposureLevel << endl;

    cout << "Immunocompromised: "
         << (person.immunocompromised ? "YES" : "NO") << endl;

    cout << "Essential Worker: "
         << (person.essentialWorker ? "YES" : "NO") << endl;

    cout << endl;
}

// Displays region information.
void displayRegion(const Region& region)
{
    cout << "Region: " << region.name << endl;
    cout << "Vaccines Available: " << region.vaccineSupply << endl;
    cout << "Outbreak Level: " << region.outbreakLevel << endl;
    cout << "Population Stored: " << region.residents.size() << endl;
    cout << endl;
}

int main()
{
    srand((unsigned int)time(0));

    map<string, vector<string>> worldGraph;

    worldGraph["Austin"] = {"Dallas", "Houston"};
    worldGraph["Dallas"] = {"Houston"};
    worldGraph["Houston"] = {"Austin"};

    map<string, Region> regions;

    Region austin;
    austin.name = "Austin";
    austin.vaccineSupply = 100;
    austin.outbreakLevel = 20;

    Region dallas;
    dallas.name = "Dallas";
    dallas.vaccineSupply = 80;
    dallas.outbreakLevel = 10;

    Region houston;
    houston.name = "Houston";
    houston.vaccineSupply = 50;
    houston.outbreakLevel = 30;

    regions["Austin"] = austin;
    regions["Dallas"] = dallas;
    regions["Houston"] = houston;

    cout << "-REGION CONNECTIONS-" << endl;

    for (const auto& node : worldGraph)
    {
        cout << node.first << " connected to: ";

        for (const string& connection : node.second)
        {
            cout << connection << " ";
        }

        cout << endl;
    }

    while (true)
    {
        cout << endl;
        cout << "1. Add Patient" << endl;
        cout << "2. View Regions" << endl;
        cout << "3. Generate Crisis" << endl;
        cout << "4. Show Priority Queue" << endl;
        cout << "5. Transfer Vaccines" << endl;
        cout << "6. Exit" << endl;

        int choice = readInt("Choice: ");

        if (choice == 1)
        {
            Person newPerson;
            string regionName;

            newPerson.name = readLine("Enter patient name: ");
            newPerson.age = readInt("Enter age: ");

            int immune =
                readInt(0, 1,
                        "Immunocompromised? (1=yes 0=no): ");

            int worker =
                readInt(0, 1,
                        "Essential worker? (1=yes 0=no): ");

            newPerson.exposureLevel =
                readInt(1, 10,
                        "Exposure level (1-10): ");

            newPerson.immunocompromised = immune;
            newPerson.essentialWorker = worker;

            regionName = readLine("Enter region name: ");

            if (regions.count(regionName))
            {
                Region& region = regions[regionName];

                newPerson.riskScore =
                    calculateRisk(newPerson, region.outbreakLevel);

                region.residents.push_back(newPerson);

                cout << "\nPatient added." << endl;
            }
            else
            {
                cout << "\nRegion not found." << endl;
            }
        }
        else if (choice == 2)
        {
            cout << "\n-REGIONS-" << endl;

            for (const auto& regionPair : regions)
            {
                displayRegion(regionPair.second);
            }
        }
        else if (choice == 3)
        {
            generateCrisis(regions);

            cout << "\nCrisis generated." << endl;
        }
        else if (choice == 4)
        {
            priority_queue<Person, vector<Person>, CompareRisk> vaccineQueue;

            for (const auto& regionPair : regions)
            {
                const Region& region = regionPair.second;

                for (const Person& person : region.residents)
                {
                    vaccineQueue.push(person);
                }
            }

            cout << "\n-VACCINE PRIORITY-" << endl;

            while (!vaccineQueue.empty())
            {
                displayPerson(vaccineQueue.top());
                vaccineQueue.pop();
            }
        }
        else if (choice == 5)
        {
            cout << "\n-TRANSFER VACCINES-" << endl;

            string fromRegion = readLine("Transfer From region: ");
            string toRegion = readLine("Transfer To region: ");
            int amount = readInt("Number of vaccines: ");

            if (!regions.count(fromRegion) || !regions.count(toRegion))
            {
                cout << "\nInvalid name." << endl;
            }
            else if (amount < 0)
            {
                cout << "\nNumber of vaccines cannot be negative." << endl;
            }
            else
            {
                bool connected = false;

                for (const string& neighbor : worldGraph[fromRegion])
                {
                    if (neighbor == toRegion)
                    {
                        connected = true;
                        break;
                    }
                }

                if (!connected)
                {
                    cout << "\nRegions are not connected." << endl;
                }
                else if (regions[fromRegion].vaccineSupply < amount)
                {
                    cout << "\nNot enough vaccines available." << endl;
                }
                else
                {
                    regions[fromRegion].vaccineSupply -= amount;
                    regions[toRegion].vaccineSupply += amount;

                    cout << "\nTransfer successful." << endl;
                    cout << amount << " vaccines moved from "
                         << fromRegion << " to "
                         << toRegion << "." << endl;
                }
            }
        }
        else if (choice == 6)
        {
            break;
        }
        else
        {
            cout << "\nInvalid choice." << endl;
        }
    }

    return 0;
}
