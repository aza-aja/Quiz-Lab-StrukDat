#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int TABLE_SIZE = 20;

class HashTable {
private:
    vector<pair<long long, string>> table;
    vector<int> status;

    int hash1(long long key) {
        return key % TABLE_SIZE;
    }

    int hash2(long long key) {
        return 19 - (key % 19);
    }

public:
    HashTable() {
        table.resize(TABLE_SIZE);
        status.resize(TABLE_SIZE, 0);
    }

    void insert(long long key, string value) {
        int index = hash1(key);
        int step = hash2(key);
        int deletedIndex = -1;

        for (int i = 0; i < TABLE_SIZE; i++) {
            if (status[index] == 1 && table[index].first == key) {
                table[index].second = value;
                cout << "Data berhasil diperbarui.\n";
                return;
            }

            if (status[index] == 2 && deletedIndex == -1) {
                deletedIndex = index;
            }

            if (status[index] == 0) {
                if (deletedIndex != -1) {
                    index = deletedIndex;
                }

                table[index] = make_pair(key, value);
                status[index] = 1;

                cout << "Data berhasil ditambahkan.\n";
                return;
            }

            index = (index + step) % TABLE_SIZE;
        }

        if (deletedIndex != -1) {
            table[deletedIndex] = make_pair(key, value);
            status[deletedIndex] = 1;
            cout << "Data berhasil ditambahkan.\n";
        } else {
            cout << "Hash Table penuh.\n";
        }
    }

    void search(long long key) {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            if (status[index] == 0) {
                break;
            }

            if (status[index] == 1 && table[index].first == key) {
                cout << "Data ditemukan.\n";
                cout << "NIM  : " << table[index].first << endl;
                cout << "Nama : " << table[index].second << endl;
                return;
            }

            index = (index + step) % TABLE_SIZE;
        }

        cout << "Data tidak ditemukan.\n";
    }

    void remove(long long key) {
        int index = hash1(key);
        int step = hash2(key);

        for (int i = 0; i < TABLE_SIZE; i++) {
            if (status[index] == 0) {
                break;
            }

            if (status[index] == 1 && table[index].first == key) {
                status[index] = 2;
                cout << "Data berhasil dihapus.\n";
                return;
            }

            index = (index + step) % TABLE_SIZE;
        }

        cout << "Data tidak ditemukan.\n";
    }

    void display() {
        cout << "\nISI HASH TABLE\n";

        for (int i = 0; i < TABLE_SIZE; i++) {
            cout << i << " : ";

            if (status[i] == 1) {
                cout << table[i].first << " - " << table[i].second;
            } else if (status[i] == 2) {
                cout << "DELETED";
            } else {
                cout << "EMPTY";
            }

            cout << endl;
        }
    }
};

int main() {
    HashTable ht;
    int pilihan;
    long long nim;
    string nama;

    // Data awal 15 mahasiswa untuk pengujian
    ht.insert(228000000000, "Andi");
    ht.insert(228000000038, "Budi");
    ht.insert(228000000076, "Citra");
    ht.insert(228000000114, "Dewi");
    ht.insert(228000000152, "Eko");
    ht.insert(228000000190, "Fajar");
    ht.insert(228000000228, "Gita");
    ht.insert(228000000266, "Hani");
    ht.insert(228000000304, "Indra");
    ht.insert(228000000342, "Joko");
    ht.insert(228000000380, "Kiki");
    ht.insert(228000000418, "Lina");
    ht.insert(228000000456, "Maya");
    ht.insert(228000000494, "Nanda");
    ht.insert(228000000532, "Oki");

    do {
        cout << "\nSISTEM PENGELOLAAN DATA MAHASISWA\n";
        cout << "1. Insert Data\n";
        cout << "2. Search Data\n";
        cout << "3. Remove Data\n";
        cout << "4. Display Hash Table\n";
        cout << "5. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                cout << "Masukkan NIM: ";
                cin >> nim;

                cout << "Masukkan nama: ";
                cin.ignore();
                getline(cin, nama);

                ht.insert(nim, nama);
                break;

            case 2:
                cout << "Masukkan NIM yang dicari: ";
                cin >> nim;

                ht.search(nim);
                break;

            case 3:
                cout << "Masukkan NIM yang dihapus: ";
                cin >> nim;

                ht.remove(nim);
                break;

            case 4:
                ht.display();
                break;

            case 5:
                cout << "Program selesai.\n";
                break;

            default:
                cout << "Pilihan tidak valid.\n";
        }

        cout << endl;

    } while (pilihan != 5);

    return 0;
}