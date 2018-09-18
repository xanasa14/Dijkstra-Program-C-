//Xavier Navarro 
//CS610 Data Structures and Alg 
//April 23rd 2018
//Instructors Dr. Ali Mili and Lu Zhenliang
//Greedy Method - Dijkstra Algorithm 

#include <iostream>
#include <unordered_map>
#include <vector>
#include <limits>
#include <algorithm>
#include <cstring>
#include <list>
using namespace std;

#define MAX_LINE_LENGTH 2000

class Graph
{
    unordered_map<char, const unordered_map<char, int>> vertices;
    
public:
    void add_vertex(char names, const unordered_map<char, int>& PATHS)
    {
        vertices.insert(unordered_map<char, const unordered_map<char, int>>::value_type(names, PATHS));
    }
    
    vector<char> shortest_path(char Beginning, char END)
    {
        unordered_map<char, int> Cost;
        unordered_map<char, char> precedent;
        vector<char> nodes;
        vector<char> path; 
        
        auto comparator = [&] (char left, char right) { return Cost[left] > Cost[right]; };
        int count = 0;
        for (auto& vertex : vertices)
        {
            if (vertex.first == Beginning)
            {
                Cost[vertex.first] = 0;
            }
            else
            {
                Cost[vertex.first] = numeric_limits<int>::max();
            }
            
            nodes.push_back(vertex.first);
            push_heap(begin(nodes), end(nodes), comparator);
        }
        
        while (!nodes.empty())
        {
            pop_heap(begin(nodes), end(nodes), comparator);
            char smallest = nodes.back();
            nodes.pop_back();
            
            if (smallest == END)
            {
                while (precedent.find(smallest) != end(precedent))
                {
                    path.push_back(smallest);
                    smallest = precedent[smallest];
                }
                
                break;
            }
            
            if (Cost[smallest] == numeric_limits<int>::max())
            {
                break;
            }
            
            for (auto& neighbor : vertices[smallest])
            {
                int alt = Cost[smallest] + neighbor.second;
                
                if (alt < Cost[neighbor.first])
                {
                    Cost[neighbor.first] = alt;
                    precedent[neighbor.first] = smallest;
                    make_heap(begin(nodes), end(nodes), comparator);
                    count += alt;
                }
            }
        }
        
        cout << "Distance: " << Cost[END] << endl;
        return path;
    }
};

int main()
{
    int seq = 0;
    list <int> lista;
    char init_node;
    char dest_node;
    char tmp[MAX_LINE_LENGTH];
    
    Graph g;
    
    while (true) {
        cin >> tmp;
        
        if (strcmp(tmp, "END") == 0) {
            break;
        }
        
        char *firstPart = strtok(tmp, ":");
        
        if (strcmp(firstPart, "From") == 0) {
            char *secondPart = strtok(NULL, ":");
            init_node = secondPart[0];
        } else if (strcmp(firstPart, "To") == 0) {
            char *secondPart = strtok(NULL, ":");
            dest_node = secondPart[0];
        } else {
            char *Cost = strtok(NULL, ":");
            list <char*> Towards;
            
            char *destinationNodeInfo = strtok(Cost, ",");
            while (destinationNodeInfo != NULL) {
                Towards.push_back(destinationNodeInfo);
                destinationNodeInfo = strtok(NULL, ",");
            }
            
            unordered_map<char, int> PATHS;
            for (char *destinationNode : Towards) {
                char node = strtok(destinationNode, "=")[0];
                int distance = stoi(strtok(NULL, "="));

                PATHS[node] = distance;
            }
            
            g.add_vertex(firstPart[0], PATHS);
        }
    }
    cout << "From what node do you want to start? " << endl;
    cin >> init_node;
    cout << "Towards what node it is the destination? " << endl;
    cin >> dest_node;
    cout << "Starting point: " << init_node << endl;
    cout << "Ending point: " << dest_node << endl;
    
    for (char vertex : g.shortest_path(init_node, dest_node))
    {
        cout << "shortest_path includes : " << seq << " Node : " << vertex << endl;
        seq++;
    }
    cout << "shortest_path includes : " << seq << " Node : " << init_node <<endl;    
    return 0;
}

