#include <bits/stdc++.h>

using namespace std;

// Define node
struct Node {
    // Vector of node, weight (edge)
    Node(string x = "0", string y = "0") : xPos(stoi(x)), yPos(stoi(y))
    {
        coords = to_string(xPos) + " / " + to_string(yPos);
    }
    vector<pair<int, int>> adj;
    int xPos = 0;
    int yPos = 0;
    string coords = "";
    int parent = -1;
    int cost = 1e8;
    bool known = false;
};

// Array of nodes
vector<Node*> graph;
int numCities = 0;


// Prim's MST
int getNext();
void primsMST(int curr);


int main(int argc, char* argv[]) {
    // Open file
    ifstream ifs;
    ifs.open(argv[1]);

    // Read in values
    string name, xCoord, yCoord;
    size_t lNS = 11;
    int city = 0;
    map<int, string> cities;

    while (getline(ifs, name, ',')) {
        getline(ifs, xCoord, ',');
        getline(ifs, yCoord);

        if (name.size() > lNS)
        {
            lNS = name.size();
        }

        cities[city] = name;
        graph.push_back(new Node(xCoord, yCoord));
        city++;
    }
    numCities = city;
    lNS += 3;

    // Create adjacencies for every train track
    int w;
    graph.push_back(new Node());
    graph[numCities]->cost = 1e9;

    for (int i = 0; i < numCities; i++)
    {
        for (int j = i + 1; j < numCities; j++)
        {
            w = abs(graph[i]->xPos - graph[j]->xPos);
            w += abs(graph[i]->yPos - graph[j]->yPos);
            graph[i]->adj.push_back(make_pair(j, w));
            graph[j]->adj.push_back(make_pair(i, w));
        }
    }

    // Perform Prim's
    int start = getNext();
    graph[start]->cost = 0;
    primsMST(start);

    // Print out, left justified
    ofstream ofs;
    ofs.open("result.txt");

    int totalCost = 0;
    ofs << left;
    ofs << setw(lNS) << "From:";
    ofs << setw(lNS) << "To:";
    ofs << "Cost: " << endl;
    ofs << setfill('-') << setw(3 * lNS) << "" << endl;
    ofs << setfill(' ');

    for (int i = 0; i < numCities; i++)
    {
        if (graph[i]->parent == -1) continue;

        ofs << setw(lNS) << cities[graph[i]->parent];
        ofs << setw(lNS) << cities[i];
        ofs << graph[i]->cost << endl;
        totalCost += graph[i]->cost;

        ofs << setw(lNS) << graph[graph[i]->parent]->coords;
        ofs << setw(lNS) << graph[i]->coords << endl;
        ofs << endl;
    }

    ofs << setfill('-') << setw(3 * lNS) << "" << endl;
    ofs << setfill(' ');
    ofs << "Total Cost: " << totalCost << endl;

    for (Node* x : graph) delete x;

    return 0;
}

int getNext()
{
    int next = numCities;

    for (int i = 0; i < numCities; i++)
    {
        if (!graph[i]->known && (graph[i]->cost < graph[next]->cost))
        {
            next = i;
        }
    }

    return next;
}

void primsMST(int curr)
{
    if (curr == numCities) return;

    graph[curr]->known = true;

    for (pair<int, int> neighbor : graph[curr]->adj)
    {
        if (!graph[neighbor.first]->known && (neighbor.second < graph[neighbor.first]->cost))
        {
            graph[neighbor.first]->cost = neighbor.second;
            graph[neighbor.first]->parent = curr;
        }
    }

    primsMST(getNext());
}
