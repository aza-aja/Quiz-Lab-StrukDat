#include <iostream>
#include <string>
using namespace std;

// QUEUE
// Struktur antrean mahasiswa
struct QueueNode {
    string nim;
    string nama;
    QueueNode* next;
};

QueueNode* front = nullptr;
QueueNode* rear = nullptr;

// Menambahkan mahasiswa ke antrean
void tambahAntrean() {
    QueueNode* baru = new QueueNode;

    cout << "Masukkan NIM: ";
    cin >> baru->nim;

    cout << "Masukkan nama: ";
    cin.ignore();
    getline(cin, baru->nama);

    baru->next = nullptr;

    if (front == nullptr) {
        front = rear = baru;
    } else {
        rear->next = baru;
        rear = baru;
    }

    cout << "Mahasiswa berhasil masuk antrean.\n";
}

// Memproses antrean paling depan
void prosesAntrean() {
    if (front == nullptr) {
        cout << "Antrean kosong.\n";
        return;
    }

    QueueNode* hapus = front;

    cout << "Antrean diproses:\n";
    cout << "NIM  : " << hapus->nim << endl;
    cout << "Nama : " << hapus->nama << endl;

    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete hapus;
}

// Menampilkan seluruh antrean
void tampilAntrean() {
    QueueNode* bantu = front;

    if (bantu == nullptr) {
        cout << "Antrean kosong.\n";
        return;
    }

    cout << "\nANTREAN MAHASISWA\n";

    while (bantu != nullptr) {
        cout << "NIM  : " << bantu->nim << endl;
        cout << "Nama : " << bantu->nama << endl;
        cout << endl;

        bantu = bantu->next;
    }
}

// STACK
// Struktur riwayat pengembalian
struct StackNode {
    int idBuku;
    StackNode* next;
};

StackNode* top = nullptr;

// Menambahkan ID buku ke Stack
void tambahPengembalian() {
    StackNode* baru = new StackNode;

    cout << "Masukkan ID buku yang dikembalikan: ";
    cin >> baru->idBuku;

    baru->next = top;
    top = baru;

    cout << "Pengembalian berhasil dicatat.\n";
}

// Menampilkan riwayat pengembalian
void tampilRiwayat() {
    StackNode* bantu = top;

    if (bantu == nullptr) {
        cout << "Riwayat pengembalian kosong.\n";
        return;
    }

    cout << "\nRIWAYAT PENGEMBALIAN BUKU\n";

    while (bantu != nullptr) {
        cout << "ID Buku: " << bantu->idBuku << endl;
        bantu = bantu->next;
    }
}

// BINARY SEARCH TREE
// Struktur node BST
struct TreeNode {
    int idBuku;
    TreeNode* left;
    TreeNode* right;
};

TreeNode* root = nullptr;

// Menambahkan ID buku ke BST
TreeNode* tambahBuku(TreeNode* node, int id) {
    if (node == nullptr) {
        TreeNode* baru = new TreeNode;
        baru->idBuku = id;
        baru->left = nullptr;
        baru->right = nullptr;
        return baru;
    }

    if (id < node->idBuku) {
        node->left = tambahBuku(node->left, id);
    } else if (id > node->idBuku) {
        node->right = tambahBuku(node->right, id);
    }

    return node;
}

// Mencari ID buku
TreeNode* cariBuku(TreeNode* node, int id) {
    if (node == nullptr || node->idBuku == id) {
        return node;
    }

    if (id < node->idBuku) {
        return cariBuku(node->left, id);
    }

    return cariBuku(node->right, id);
}

// Traversal PreOrder
void preorder(TreeNode* node) {
    if (node != nullptr) {
        cout << node->idBuku << " ";
        preorder(node->left);
        preorder(node->right);
    }
}

// Traversal InOrder
void inorder(TreeNode* node) {
    if (node != nullptr) {
        inorder(node->left);
        cout << node->idBuku << " ";
        inorder(node->right);
    }
}

// Traversal PostOrder
void postorder(TreeNode* node) {
    if (node != nullptr) {
        postorder(node->left);
        postorder(node->right);
        cout << node->idBuku << " ";
    }
}

// Menampilkan seluruh traversal BST
void tampilBST() {
    if (root == nullptr) {
        cout << "BST masih kosong.\n";
        return;
    }

    cout << "PreOrder  : ";
    preorder(root);

    cout << "\nInOrder   : ";
    inorder(root);

    cout << "\nPostOrder : ";
    postorder(root);

    cout << endl;
}

// MENU UTAMA
int main() {
    system("cls");
    int pilihan, id;

    do {
        cout << "\nSISTEM PERPUSTAKAAN\n";
        cout << "1. Tambah Antrean Peminjaman\n";
        cout << "2. Proses Antrean\n";
        cout << "3. Tampilkan Antrean\n";
        cout << "4. Catat Pengembalian Buku\n";
        cout << "5. Tampilkan Riwayat Pengembalian\n";
        cout << "6. Tambah ID Buku ke BST\n";
        cout << "7. Cari ID Buku\n";
        cout << "8. Tampilkan BST\n";
        cout << "9. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                system("cls");
                tambahAntrean();
                break;

            case 2:
                system("cls");
                prosesAntrean();
                break;

            case 3:
                system("cls");
                tampilAntrean();
                break;

            case 4:
                system("cls");
                tambahPengembalian();
                break;

            case 5:
                system("cls");
                tampilRiwayat();
                break;

            case 6:
                system("cls");
                cout << "Masukkan ID buku: ";
                cin >> id;

                if (cariBuku(root, id) != nullptr) {
                    cout << "ID buku sudah tersedia.\n";
                } else {
                    root = tambahBuku(root, id);
                    cout << "Buku berhasil ditambahkan.\n";
                }
                break;

            case 7:
                system("cls");
                cout << "Masukkan ID buku yang dicari: ";
                cin >> id;

                if (cariBuku(root, id) != nullptr) {
                    cout << "Buku ditemukan.\n";
                } else {
                    cout << "Buku tidak ditemukan.\n";
                }
                break;

            case 8:
                system("cls");
                tampilBST();
                break;

            case 9:
                system("cls");
                cout << "Program selesai.\n";
                break;

            default:
                system("cls");
                cout << "Pilihan tidak valid.\n";
        }

        cout << endl;

    } while (pilihan != 9);

    return 0;
}