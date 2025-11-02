#include <iostream>
#include <algorithm>
using namespace std;

class Connection {
public:
    int start, end, expense; // connection details
};

class HouseGroup {
public:
    int parent[50]; // supports up to 50 houses
    HouseGroup(int n) {
        for (int i = 1; i <= n; i++) parent[i] = i; // initialize
    }

    int findMainHouse(int house) { // find with path compression
        if (parent[house] == house)
            return house;
        return parent[house] = findMainHouse(parent[house]);
    }

    void joinHouses(int h1, int h2) { // union operation
        int p1 = findMainHouse(h1);
        int p2 = findMainHouse(h2);
        if (p1 != p2)
            parent[p1] = p2;
    }
};

bool sortByCost(Connection a, Connection b) {
    return a.expense < b.expense;
}

int main() {
    int houses, links;
    cout << "Pimpri Chinchwad Water Pipeline Layout System\n";
    cout << "--------------------------------------------------\n";

    cout << "Enter number of houses: ";
    cin >> houses;
    cout << "Enter number of possible connections: ";
    cin >> links;

    Connection network[100]; // store connections
    cout << "\nEnter connection details (House1 House2 Cost):\n";
    for (int i = 0; i < links; i++)
        cin >> network[i].start >> network[i].end >> network[i].expense;

    sort(network, network + links, sortByCost); // sort using algorithm header

    HouseGroup layout(houses);
    int totalCost = 0;
    Connection chosen[100];
    int chosenCount = 0;

    for (int i = 0; i < links; i++) {
        int h1 = network[i].start;
        int h2 = network[i].end;
        int c = network[i].expense;

        int p1 = layout.findMainHouse(h1);
        int p2 = layout.findMainHouse(h2);

        if (p1 != p2) { // avoid cycles
            layout.joinHouses(h1, h2);
            chosen[chosenCount++] = network[i];
            totalCost += c;
        }
    }

    cout << "\nPipelines selected for minimum cost connection:\n";
    for (int i = 0; i < chosenCount; i++)
        cout << "House " << chosen[i].start << " connected to House "
             << chosen[i].end << " (Cost: " << chosen[i].expense << ")\n";

    cout << "\nTotal minimum cost to connect all houses: " << totalCost << endl;
    cout << "All houses are now connected efficiently.\n";

    return 0;
}
