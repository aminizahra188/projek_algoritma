#include <iostream>
#include <fstream>
using namespace std;

struct Film {
    string judul;
    string genre;
    float rating;
    Film* next;
};

Film* head = NULL;

// ======================================
// TAMBAH FILM
// ======================================
void tambahFilm() {
    Film* baru = new Film();

    cout << "\nJudul Film : ";
    cin.ignore();
    getline(cin, baru->judul);

    cout << "Genre Film : ";
    getline(cin, baru->genre);

    cout << "Rating Film : ";
    cin >> baru->rating;

    baru->next = NULL;

    // Jika linked list kosong
    if (head == NULL) {
        head = baru;
    }
    else {
        Film* temp = head;

        while (temp->next != NULL) {
            temp = temp->next;
        }

        temp->next = baru;
    }

    cout << "\nFilm berhasil ditambahkan!\n";
}

// ======================================
// TAMPIL FILM
// ======================================
void tampilFilm() {
    if (head == NULL) {
        cout << "\nData film kosong!\n";
        return;
    }

    Film* temp = head;
    int no = 1;

    cout << "\n===== DAFTAR FILM =====\n";

    while (temp != NULL) {
        cout << no++ << ". "
             << temp->judul << " | "
             << temp->genre << " | "
             << temp->rating << endl;

        temp = temp->next;
    }
}

// ======================================
// HAPUS FILM
// ======================================
void hapusFilm() {
    if (head == NULL) {
        cout << "\nData kosong!\n";
        return;
    }

    string cari;
    cout << "\nMasukkan judul film yang ingin dihapus : ";
    cin.ignore();
    getline(cin, cari);

    Film* temp = head;
    Film* prev = NULL;

    // Jika data pertama yang dihapus
    if (temp != NULL && temp->judul == cari) {
        head = temp->next;
        delete temp;

        cout << "\nFilm berhasil dihapus!\n";
        return;
    }

    // Cari data
    while (temp != NULL && temp->judul != cari) {
        prev = temp;
        temp = temp->next;
    }

    // Jika tidak ditemukan
    if (temp == NULL) {
        cout << "\nFilm tidak ditemukan!\n";
        return;
    }

    prev->next = temp->next;
    delete temp;

    cout << "\nFilm berhasil dihapus!\n";
}

// ======================================
// SIMPAN KE FILE
// ======================================
void saveFile() {
    ofstream file("film.txt");

    Film* temp = head;

    while (temp != NULL) {
        file << temp->judul << "|"
             << temp->genre << "|"
             << temp->rating << endl;

        temp = temp->next;
    }

    file.close();

    cout << "\nData berhasil disimpan ke file!\n";
}

// ======================================
// LOAD FILE
// ======================================
void loadFile() {
    ifstream file("film.txt");

    if (!file.is_open()) {
        return;
    }

    while (true) {
        Film* baru = new Film();

        // Baca judul
        if (!getline(file, baru->judul, '|')) {
            delete baru;
            break;
        }

        // Baca genre
        getline(file, baru->genre, '|');

        // Baca rating
        file >> baru->rating;
        file.ignore();

        baru->next = NULL;

        // Masukkan ke linked list
        if (head == NULL) {
            head = baru;
        }
        else {
            Film* temp = head;

            while (temp->next != NULL) {
                temp = temp->next;
            }

            temp->next = baru;
        }
    }

    file.close();
}
