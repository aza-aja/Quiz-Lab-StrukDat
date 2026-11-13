#include <iostream>
#include <string>
using namespace std;

// Struktur Single Linked List
struct node {
    string nim;
    string nama;
    int nilai;
    node* next;
};

// Menambahkan data mahasiswa
void tambahMahasiswa(node*& head, node*& tail, int*& data, int& n, bool& sudahDiurutkan) {
    node* baru = new node();

    cout << "\nMasukkan NIM   : ";
    getline(cin, baru->nim);

    cout << "Masukkan Nama  : ";
    getline(cin, baru->nama);

    cout << "Masukkan Nilai : ";
    cin >> baru->nilai;
    cin.ignore();

    baru->next = nullptr;

    // Menambahkan node ke Linked List
    if (head == nullptr) {
        head = baru;
        tail = baru;
    } else {
        tail->next = baru;
        tail = baru;
    }

    // Menambahkan nilai ke Dynamic Array
    int* temp = new int[n + 1];

    for (int i = 0; i < n; i++) {
        temp[i] = data[i];
    }

    temp[n] = baru->nilai;

    delete[] data;
    data = temp;
    n++;

    sudahDiurutkan = false;

    cout << "\nData mahasiswa berhasil ditambahkan!\n";
}

// Menampilkan data mahasiswa
void tampilkanMahasiswa(node* head) {
    if (head == nullptr) {
        cout << "\nBelum ada data mahasiswa!\n";
        return;
    }

    node* temp = head;
    int nomor = 1;

    cout << "\nDATA MAHASISWA\n";

    while (temp != nullptr) {
        cout << "\nMahasiswa ke-" << nomor << endl;
        cout << "NIM   : " << temp->nim << endl;
        cout << "Nama  : " << temp->nama << endl;
        cout << "Nilai : " << temp->nilai << endl;

        temp = temp->next;
        nomor++;
    }
}

// Mengurutkan nilai dengan Insertion Sort
void insertionSort(int data[], int n) {
    for (int i = 1; i < n; i++) {
        int key = data[i];
        int j = i - 1;

        while (j >= 0 && data[j] > key) {
            data[j + 1] = data[j];
            j--;
        }

        data[j + 1] = key;
    }
}

// Menampilkan nilai yang sudah diurutkan
void tampilkanNilai(int data[], int n) {
    cout << "\nNILAI SETELAH DIURUTKAN\n";

    for (int i = 0; i < n; i++) {
        cout << data[i];

        if (i < n - 1) {
            cout << ", ";
        }
    }

    cout << endl;
}

// Mencari mahasiswa berdasarkan NIM Linear Search
node* linearSearch(node* head, string target) {
    node* temp = head;

    while (temp != nullptr) {
        if (temp->nim == target) {
            return temp;
        }

        temp = temp->next;
    }

    return nullptr;
}

// Mencari nilai dengan Binary Search
int binarySearch(int data[], int low, int high, int target) {
    if (low > high) {
        return -1;
    }

    int mid = low + (high - low) / 2;

    if (data[mid] == target) {
        return mid;
    } else if (target < data[mid]) {
        return binarySearch(data, low, mid - 1, target);
    } else {
        return binarySearch(data, mid + 1, high, target);
    }
}

// Menu utama program
int main() {
    system("cls");

    node* head = nullptr;
    node* tail = nullptr;

    int* data = nullptr;
    int n = 0;

    bool sudahDiurutkan = false;

    int pilihan;
    string cariNIM;
    int cariNilai;

    do {
        cout << "\nSISTEM PENGELOLAAN NILAI MAHASISWA\n";
        cout << "1. Tambah Data Mahasiswa\n";
        cout << "2. Tampilkan Data Mahasiswa\n";
        cout << "3. Urutkan Nilai                   (Insertion Sort)\n";
        cout << "4. Cari Mahasiswa Berdasarkan NIM  (Linear Search)\n";
        cout << "5. Cari Nilai                      (Binary Search)\n";
        cout << "6. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1:
                system("cls");
                tambahMahasiswa(head, tail, data, n, sudahDiurutkan);
                break;

            case 2:
                system("cls");
                tampilkanMahasiswa(head);
                break;

            case 3:
                system("cls");
                if (n == 0) {
                    cout << "\nBelum ada data nilai mahasiswa!\n";
                } else {
                    insertionSort(data, n);
                    sudahDiurutkan = true;
                    tampilkanNilai(data, n);
                }
                break;

            case 4:
                system("cls");
                if (head == nullptr) {
                    cout << "\nBelum ada data mahasiswa!\n";
                } else {
                    cout << "\nMasukkan NIM yang dicari: ";
                    getline(cin, cariNIM);

                    node* hasil = linearSearch(head, cariNIM);

                    if (hasil != nullptr) {
                        cout << "\nData mahasiswa ditemukan!\n";
                        cout << "NIM   : " << hasil->nim << endl;
                        cout << "Nama  : " << hasil->nama << endl;
                        cout << "Nilai : " << hasil->nilai << endl;
                    } else {
                        cout << "\nData mahasiswa tidak ditemukan!\n";
                    }
                }
                break;

            case 5:
                system("cls");
                if (n == 0) {
                    cout << "\nBelum ada data nilai mahasiswa!\n";
                } else if (!sudahDiurutkan) {
                    cout << "\nUrutkan nilai terlebih dahulu!\n";
                } else {
                    cout << "\nMasukkan nilai yang dicari: ";
                    cin >> cariNilai;

                    int hasil = binarySearch(data, 0, n - 1, cariNilai);

                    if (hasil != -1) {
                        cout << "\nNilai ditemukan!\n";
                        cout << "Nilai  : " << data[hasil] << endl;
                        cout << "Indeks : " << hasil << endl;
                    } else {
                        cout << "\nNilai tidak ditemukan!\n";
                    }
                }
                break;

            case 6:
                system("cls");
                cout << "\nProgram selesai.\n";
                break;

            default:
                system("cls");
                cout << "\nPilihan tidak tersedia!\n";
        }

    } while (pilihan != 6);

    // Menghapus seluruh node Linked List
    node* temp;

    while (head != nullptr) {
        temp = head;
        head = head->next;
        delete temp;
    }

    // Menghapus Dynamic Array
    delete[] data;

    return 0;
}