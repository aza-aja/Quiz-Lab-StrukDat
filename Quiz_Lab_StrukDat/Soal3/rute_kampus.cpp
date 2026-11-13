#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int numberVertex;
    vector<vector<int>> adjMatrix;

public:
    // Membuat Graph dengan jumlah vertex tertentu
    Graph(int banyakTitik) {
        numberVertex = banyakTitik;
        adjMatrix.resize(numberVertex, vector<int>(numberVertex, 0));
    }

    // Menambahkan hubungan dan bobot antarvertex
    void addEdge(int i, int j, int weight) {
        if (i >= 0 && i < numberVertex && j >= 0 && j < numberVertex) {
            adjMatrix[i][j] = weight;
            adjMatrix[j][i] = weight;
        }
    }

    // Menampilkan Adjacency Matrix
    void printAdjMatrix() {
        cout << "\nADJACENCY MATRIX\n";
        cout << "  A B C D E F\n";

        for (int i = 0; i < numberVertex; i++) {
            cout << char('A' + i) << " ";

            for (int j = 0; j < numberVertex; j++) {
                cout << adjMatrix[i][j] << " ";
            }

            cout << endl;
        }
    }

    // Menelusuri Graph menggunakan BFS
    void bfs(int startVertex) {
        vector<bool> visited(numberVertex, false);
        queue<int> q;

        visited[startVertex] = true;
        q.push(startVertex);

        cout << "\nBFS: ";

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            cout << char('A' + current) << " ";

            for (int i = 0; i < numberVertex; i++) {
                if (adjMatrix[current][i] != 0 && !visited[i]) {
                    visited[i] = true;
                    q.push(i);
                }
            }
        }

        cout << endl;
    }

    // Proses rekursif DFS
    void dfsUntil(int current, vector<bool>& visited) {
        visited[current] = true;

        cout << char('A' + current) << " ";

        for (int i = 0; i < numberVertex; i++) {
            if (adjMatrix[current][i] != 0 && !visited[i]) {
                dfsUntil(i, visited);
            }
        }
    }

    // Menjalankan DFS dari vertex awal
    void dfs(int startVertex) {
        vector<bool> visited(numberVertex, false);

        cout << "\nDFS: ";
        dfsUntil(startVertex, visited);

        cout << endl;
    }

    // Mencari rute terpendek dengan Dijkstra
    void dijkstra(int startVertex, int tujuan) {
        const int INF = 1000000000;

        vector<int> distance(numberVertex, INF);
        vector<int> parent(numberVertex, -1);
        vector<bool> visited(numberVertex, false);

        distance[startVertex] = 0;

        for (int i = 0; i < numberVertex; i++) {
            int current = -1;

            // Memilih vertex dengan jarak terkecil
            for (int j = 0; j < numberVertex; j++) {
                if (!visited[j] &&
                    (current == -1 || distance[j] < distance[current])) {
                    current = j;
                }
            }

            if (current == -1 || distance[current] == INF) {
                break;
            }

            visited[current] = true;

            // Memperbarui jarak ke vertex tetangga
            for (int j = 0; j < numberVertex; j++) {
                if (adjMatrix[current][j] != 0 &&
                    distance[current] + adjMatrix[current][j] < distance[j]) {

                    distance[j] = distance[current] + adjMatrix[current][j];
                    parent[j] = current;
                }
            }
        }

        cout << "\nJALUR TERPENDEK\n";

        if (distance[tujuan] == INF) {
            cout << "Tidak ada jalur yang tersedia.\n";
            return;
        }

        // Menyusun kembali rute terpendek
        vector<int> path;
        int current = tujuan;

        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }

        cout << "Rute: ";

        for (int i = path.size() - 1; i >= 0; i--) {
            cout << char('A' + path[i]);

            if (i > 0) {
                cout << " -> ";
            }
        }

        cout << "\nTotal jarak: " << distance[tujuan] << endl;
    }
};

int main() {
    system("cls");
    Graph graph(6);

    // Menambahkan jalur dan bobot jarak
    graph.addEdge(0, 1, 4);
    graph.addEdge(0, 2, 2);
    graph.addEdge(1, 2, 1);
    graph.addEdge(1, 3, 5);
    graph.addEdge(1, 4, 3);
    graph.addEdge(2, 3, 8);
    graph.addEdge(2, 4, 6);
    graph.addEdge(3, 4, 2);
    graph.addEdge(3, 5, 4);
    graph.addEdge(4, 5, 3);

    char awal, tujuan;

    cout << "SISTEM PENCARIAN RUTE KAMPUS\n";
    cout << "Vertex yang tersedia: A, B, C, D, E, F\n";

    cout << "Masukkan vertex awal: ";
    cin >> awal;

    cout << "Masukkan vertex tujuan: ";
    cin >> tujuan;

    // Memeriksa input vertex
    if (awal < 'A' || awal > 'F' || tujuan < 'A' || tujuan > 'F') {
        cout << "Vertex tidak valid.\n";
        return 0;
    }

    int startVertex = awal - 'A';
    int endVertex = tujuan - 'A';

    graph.printAdjMatrix();

    graph.bfs(startVertex);
    graph.dfs(startVertex);

    graph.dijkstra(startVertex, endVertex);

    return 0;
}