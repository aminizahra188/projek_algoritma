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

void cariFilm(){
    if(awal == NULL){
        cout << "\nData film kosong!\n";
        return;
    }

    string cari;

    cout << "\nMasukkan judul film : ";
    cin.ignore();
    getline(cin, cari);

    Film* bantu = awal;
    bool ditemukan = false;

    while(bantu != NULL){
        if(bantu->judul == cari){
            cout << "\nFilm ditemukan!\n";
            cout << "Judul : " << bantu->judul << endl;
            cout << "Genre : " << bantu->genre << endl;
            cout << "Rating : " << bantu->rating << endl;
            ditemukan = true;
        }
        bantu = bantu->next;
    }

    if(!ditemukan){
        cout << "\nFilm tidak ditemukan!\n";
    }

}

void sortRate(){
    if(awal == NULL){
        return;
    }

    bool tukar;
    do{
        tukar = false;
        Film* bantu = awal;

        while(bantu->next != NULL){
            if(bantu->rating < bantu->next->rating){
                swap(bantu->judul, bantu->next->judul);
                swap(bantu->genre, bantu->next->genre);
                swap(bantu->rating, bantu->next->rating);
                tukar = true;
            }

            bantu = bantu->next;
        }

    }while(tukar);
    cout << "\nData berhasil diurutkan berdasarkan rating!\n";

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

int main(){

loadFile();
int pilih;

do {
    cout << "\n===== MOVIE LIST =====\n";
    cout << "1. Tambah Film\n";
    cout << "2. Tampilkan Film\n";
    cout << "3. Cari Film\n";
    cout << "4. Sorting Rating\n";
    cout << "5. Hapus Film\n";
    cout << "6. Simpan File\n";
    cout << "0. Keluar\n";
    cout << "Pilih menu : ";
    cin >> pilih;

    switch(pilih){
        case 1:
        tambahFilm();
        break;

        case 2:
        tampilFilm();
        break;

        case 3:
        cariFilm();
        break;

        case 4:
        sortRate();
        break;

        case 5:
        hapusFilm();
        break;

        case 6:
        saveFile();
        break;

        case 0:
        saveFile();
        cout << "\nProgram selesai\n";
        break;

        default:
        cout << "\nMenu tidak tersedia!\n";

    }

   }while (pilih != 0);

   return 0;

}
