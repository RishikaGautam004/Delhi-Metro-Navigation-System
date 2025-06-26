#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <algorithm>
using namespace std;

class Graph {
public:
    struct Vertex {
            unordered_map<string, int> nbrs;
        };

        unordered_map<string, Vertex> vtces;

        void addVertex(const string& name) {
            vtces[name] = Vertex();
        }

        void addEdge(const string& v1, const string& v2, int weight) {
            if (!vtces.count(v1) || !vtces.count(v2) || vtces[v1].nbrs.count(v2)) return;
            vtces[v1].nbrs[v2] = weight;
            vtces[v2].nbrs[v1] = weight;
        }

        struct DijkstraPair {
            string vname, psf;
            int cost;
            bool operator>(const DijkstraPair& o) const {
                return cost > o.cost;
            }
        };

        pair<int, string> dijkstra(const string& src, const string& dest, bool timeMode = false) {
            unordered_map<string, int> dist;
            priority_queue<DijkstraPair, vector<DijkstraPair>, greater<>> pq;

            for (const auto& p : vtces) dist[p.first] = INT_MAX;

            dist[src] = 0;
            pq.push({src, src, 0});

            while (!pq.empty()) {
                auto cur = pq.top(); pq.pop();

                if (cur.vname == dest)
                    return {cur.cost, cur.psf};

                for (const auto& nbr : vtces[cur.vname].nbrs) {
                    int wt = timeMode ? 120 + 40 * nbr.second : nbr.second;
                    int newCost = cur.cost + wt;

                    if (newCost < dist[nbr.first]) {
                        dist[nbr.first] = newCost;
                        pq.push({nbr.first, cur.psf + " -> " + nbr.first, newCost});
                    }
                }
            }
            return {-1, ""};
        }

        void displayStations() {
            int i = 1;
            cout << "\nAvailable Metro Stations:\n";
            for (auto& p : vtces) cout << i++ << ". " << p.first << '\n';
            cout << endl;
        }

        void displayMap() {
            cout << "\nDelhi Metro Map:\n";
            for (auto& p : vtces) {
                cout << p.first << " -> ";
                for (auto& nbr : p.second.nbrs) cout << nbr.first << "(" << nbr.second << ") ";
                cout << endl;
            }
        }

        void simulateDelay(const string& station, int delayMinutes) {
            if (!vtces.count(station)) {
                cout << "\U0001F6AB Station not found!\n";
                return;
            }

            unordered_map<string, int> delayTime;
            unordered_map<string, bool> visited;
            queue<tuple<string, int, int>> q;

            int maxHops = 3;

            q.push({station, delayMinutes, 0});
            delayTime[station] = delayMinutes;
            visited[station] = true;

            cout << "\n\U0001F534 Real-Time Delay Propagation from: " << station << " (+" << delayMinutes << " mins)" << endl;

            while (!q.empty()) {
                auto [curStation, curDelay, level] = q.front(); q.pop();

                if (level >= maxHops) continue;

                for (const auto& nbr : vtces[curStation].nbrs) {
                    string neighbor = nbr.first;
                    int newDelay = curDelay + 3;

                    if (!delayTime.count(neighbor) || newDelay > delayTime[neighbor]) {
                        delayTime[neighbor] = newDelay;
                        q.push({neighbor, newDelay, level + 1});
                    }
                }
            }

            cout << "\n\U0001F4CD Affected Stations:\n";
            for (const auto& [st, d] : delayTime) {
                if (st != station)
                    cout << " → " << st << " : +" << (d - delayMinutes) << " min (Total: " << d << " mins)\n";
            }
            cout << endl;
        }
    };

    vector<string> stationList;

    void buildStationList(Graph& g) {
        stationList.clear();
        for (const auto& p : g.vtces)
            stationList.push_back(p.first);
        sort(stationList.begin(), stationList.end());
    }

    int levenshtein(const string& a, const string& b) {
        int n = (int)a.size(), m = (int)b.size();
        vector<vector<int>> dp(n + 1, vector<int>(m + 1));

        for (int i = 0; i <= n; ++i) dp[i][0] = i;
        for (int j = 0; j <= m; ++j) dp[0][j] = j;

        for (int i = 1; i <= n; ++i) {
            for (int j = 1; j <= m; ++j) {
                if (tolower(a[i - 1]) == tolower(b[j - 1]))
                    dp[i][j] = dp[i - 1][j - 1];
                else
                    dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
            }
        }
        return dp[n][m];
    }

    string autoCompleteStation(const string& input) {
        string partial = input;
        transform(partial.begin(), partial.end(), partial.begin(), ::tolower);

        vector<pair<int, string>> candidates;
        for (const auto& name : stationList) {
            string lowerName = name;
            transform(lowerName.begin(), lowerName.end(), lowerName.begin(), ::tolower);

            if (lowerName.find(partial) == 0)
                candidates.emplace_back(0, name);
            else
                candidates.emplace_back(levenshtein(partial, lowerName), name);
        }

        sort(candidates.begin(), candidates.end());

        vector<string> matches;
        for (int i = 0; i < min(5, (int)candidates.size()); ++i) {
            matches.push_back(candidates[i].second);
        }

        if (matches.empty()) {
            cout << "No station matches your input. Try again.\n";
            return "";
        } else if (matches.size() == 1) {
            cout << "Auto-completed to: " << matches[0] << endl;
            return matches[0];
        } else {
            cout << "Did you mean:\n";
            for (int i = 0; i < matches.size(); ++i)
                cout << i + 1 << ". " << matches[i] << endl;
            int choice;
            cout << "Enter choice (1-" << matches.size() << "): ";
            cin >> choice; cin.ignore();
            if (choice >= 1 && choice <= matches.size()) return matches[choice - 1];
            else {
                cout << "Invalid choice.\n";
                return "";
            }
        }
    }

int calculateFare(int distance) {
    if (distance <= 2) return 10;
    else if (distance <= 5) return 20;
    else if (distance <= 12) return 30;
    else if (distance <= 21) return 40;
    else if (distance <= 32) return 50;
    else return 60;
}

void createMetroMap(Graph& g) {
    g.addVertex("Noida Sector 62~B");
    g.addVertex("Botanical Garden~B");
    g.addVertex("Yamuna Bank~B");
    g.addVertex("Rajiv Chowk~BY");
    g.addVertex("Vaishali~B");
    g.addVertex("Moti Nagar~B");
    g.addVertex("Janak Puri West~BO");
    g.addVertex("Dwarka Sector 21~B");
    g.addVertex("Huda City Center~Y");
    g.addVertex("Saket~Y");
    g.addVertex("Vishwavidyalaya~Y");
    g.addVertex("Chandni Chowk~Y");
    g.addVertex("New Delhi~YO");
    g.addVertex("AIIMS~Y");
    g.addVertex("Shivaji Stadium~O");
    g.addVertex("DDS Campus~O");
    g.addVertex("IGI Airport~O");
    g.addVertex("Rajouri Garden~BP");
    g.addVertex("Netaji Subhash Place~PR");
    g.addVertex("Punjabi Bagh West~P");

    g.addEdge("Noida Sector 62~B", "Botanical Garden~B", 8);
    g.addEdge("Botanical Garden~B", "Yamuna Bank~B", 10);
    g.addEdge("Yamuna Bank~B", "Vaishali~B", 8);
    g.addEdge("Yamuna Bank~B", "Rajiv Chowk~BY", 6);
    g.addEdge("Rajiv Chowk~BY", "Moti Nagar~B", 9);
    g.addEdge("Moti Nagar~B", "Janak Puri West~BO", 7);
    g.addEdge("Janak Puri West~BO", "Dwarka Sector 21~B", 6);
    g.addEdge("Huda City Center~Y", "Saket~Y", 15);
    g.addEdge("Saket~Y", "AIIMS~Y", 6);
    g.addEdge("AIIMS~Y", "Rajiv Chowk~BY", 7);
    g.addEdge("Rajiv Chowk~BY", "New Delhi~YO", 1);
    g.addEdge("New Delhi~YO", "Chandni Chowk~Y", 2);
    g.addEdge("Chandni Chowk~Y", "Vishwavidyalaya~Y", 5);
    g.addEdge("New Delhi~YO", "Shivaji Stadium~O", 2);
    g.addEdge("Shivaji Stadium~O", "DDS Campus~O", 7);
    g.addEdge("DDS Campus~O", "IGI Airport~O", 8);
    g.addEdge("Moti Nagar~B", "Rajouri Garden~BP", 2);
    g.addEdge("Punjabi Bagh West~P", "Rajouri Garden~BP", 2);
    g.addEdge("Punjabi Bagh West~P", "Netaji Subhash Place~PR", 3);
}

int main() {
    Graph g;
    createMetroMap(g);
    buildStationList(g);

    int choice;
    string src, dest, input;

    cout << "\n**** WELCOME TO THE DELHI METRO APP ****\n";
    do {
        cout << "\n1. List All Stations\n2. Show Metro Map\n3. Get Shortest Distance"
             << "\n4. Get Shortest Time\n5. Simulate Delay Propagation\n6. Exit\nEnter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                g.displayStations();
                break;

            case 2:
                g.displayMap();
                break;

            case 3:
                cout << "Enter source (partial/full): "; getline(cin, input);
                src = autoCompleteStation(input);
                if (src == "") break;
                cout << "Enter destination (partial/full): "; getline(cin, input);
                dest = autoCompleteStation(input);
                if (dest == "") break;
                {
                    auto res = g.dijkstra(src, dest, false);
                    if (res.first == -1) cout << "No path found.\n";
                    else {
                        cout << "Shortest Distance: " << res.first << " KM\n";
                        cout << "Estimated Fare: Rs " << calculateFare(res.first) << endl;
                        cout << "Path: " << res.second << endl;
                    }
                }
                break;

            case 4:
                cout << "Enter source (partial/full): "; getline(cin, input);
                src = autoCompleteStation(input);
                if (src == "") break;
                cout << "Enter destination (partial/full): "; getline(cin, input);
                dest = autoCompleteStation(input);
                if (dest == "") break;
                {
                    auto res = g.dijkstra(src, dest, true);
                    if (res.first == -1) cout << "No path found.\n";
                    else {
                        cout << "Shortest Time: " << res.first / 60 << " minutes\n";
                        cout << "Path: " << res.second << endl;
                    }
                }
                break;

            case 5:
                g.displayStations();
                cout << "Enter station with delay (partial/full): ";
                getline(cin, input);
                src = autoCompleteStation(input);
                if (src == "") break;
                int delay;
                cout << "Enter delay in minutes: ";
                cin >> delay; cin.ignore();
                g.simulateDelay(src, delay);
                break;

            case 6:
                cout << "Exiting...\n";
                break;

            default:
                cout << "Invalid option. Try again.\n";
                break;
        }
    } while (choice != 6);
    return 0;
}
