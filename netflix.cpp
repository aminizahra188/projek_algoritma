#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Film {
    string judul;
    string genre;
    float rating;
    Film* next;
};

Film* awal = NULL;

void cls() {

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

}

void pause() {
    cout << "\nTekan ENTER untuk lanjut...";
    cin.ignore();
    cin.get();
}

void header() {
    cout << "====================================================\n";
    cout << "                   MOVIE LIST                       \n";
    cout << "====================================================\n";
    cout << "          Kelola Film Favoritmu Disini              \n";
    cout << "====================================================\n";
}

float inputRating() {

    float rating;

    while (true) {

        cout << "Rating Film : ";
        cin >> rating;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\n[ERROR] Rating harus angka!\n\n";
        }
        else {

            cin.ignore();

            if (rating < 0 || rating > 10) {

                cout << "\n[ERROR] Rating harus 0 - 10!\n\n";
            }
            else {

                return rating;
            }
        }
    }
}

void tambahFilm() {

    cls();
    header();

    Film* baru = new Film();

    cout << "=============== TAMBAH FILM ===============\n\n";

    cout << "Judul Film : ";
    getline(cin, baru->judul);

    while (baru->judul.empty()) {

        cout << "[ERROR] Judul tidak boleh kosong!\n";
        cout << "Judul Film : ";
        getline(cin, baru->judul);
    }

    cout << "Genre Film : ";
    getline(cin, baru->genre);

    while (baru->genre.empty()) {

        cout << "[ERROR] Genre tidak boleh kosong!\n";
        cout << "Genre Film : ";
        getline(cin, baru->genre);
    }

    baru->rating = inputRating();

    baru->next = NULL;

    if (awal == NULL) {

        awal = baru;
    }
    else {

        Film* bantu = awal;

        while (bantu->next != NULL) {

            bantu = bantu->next;
        }

        bantu->next = baru;
    }

    cout << "\n[SUCCESS] Film berhasil ditambahkan!\n";

    pause();
    cls();
}

void tampilFilm() {

    cls();
    header();

    if (awal == NULL) {

        cout << "[INFO] Data film kosong!\n";

        pause();
        cls();
        return;
    }

    Film* bantu = awal;
    int no = 1;

    cout << left;

    cout << "===================================================================\n";
    cout << setw(5)  << "No"
         << setw(30) << "Judul Film"
         << setw(20) << "Genre"
         << setw(10) << "Rating" << endl;

    cout << "===================================================================\n";

    while (bantu != NULL) {

        cout << setw(5)  << no++
             << setw(30) << bantu->judul
             << setw(20) << bantu->genre
             << setw(10) << bantu->rating
             << endl;

        bantu = bantu->next;
    }

    cout << "===================================================================\n";

    pause();
    cls();
}

void cariFilm() {

    cls();
    header();

    if (awal == NULL) {

        cout << "[INFO] Data film kosong!\n";

        pause();
        cls();
        return;
    }

    string cari;

    cout << "Masukkan judul film : ";
    getline(cin, cari);

    Film* bantu = awal;
    bool ditemukan = false;

    while (bantu != NULL) {

        if (bantu->judul == cari) {

            cout << "\n=============== FILM DITEMUKAN ===============\n";
            cout << "Judul : " << bantu->judul << endl;
            cout << "Genre : " << bantu->genre << endl;
            cout << "Rating : " << bantu->rating << endl;

            ditemukan = true;
        }

        bantu = bantu->next;
    }

    if (!ditemukan) {

        cout << "\n[INFO] Film tidak ditemukan!\n";
    }

    pause();
    cls();
}

void sortRate() {

    cls();
    header();

    if (awal == NULL) {

        cout << "[INFO] Data film kosong!\n";

        pause();
        cls();
        return;
    }

    bool tukar;

    do {

        tukar = false;

        Film* bantu = awal;

        while (bantu->next != NULL) {

            if (bantu->rating < bantu->next->rating) {

                swap(bantu->judul, bantu->next->judul);
                swap(bantu->genre, bantu->next->genre);
                swap(bantu->rating, bantu->next->rating);

                tukar = true;
            }

            bantu = bantu->next;
        }

    } while (tukar);

    cout << "[SUCCESS] Data berhasil diurutkan berdasarkan rating!\n\n";

    Film* tampil = awal;
    int no = 1;

    cout << "====================================================\n";
    cout << setw(5)  << "No"
         << setw(15) << "Judul Film"
         << setw(15) << "Genre"
         << setw(15) << "Rating" << endl;
    cout << "====================================================\n";

    while (tampil != NULL) {

        cout << setw(5)  << no++
             << setw(15) << tampil->judul
             << setw(15) << tampil->genre
             << setw(15) << tampil->rating
             << endl;

        tampil = tampil->next;
    }

    cout << "====================================================\n";

    pause();
    cls();
}

void hapusFilm() {

    cls();
    header();

    if (awal == NULL) {

        cout << "[INFO] Data kosong!\n";

        pause();
        cls();
        return;
    }

    string cari;

    cout << "Masukkan judul film yang ingin dihapus : ";
    getline(cin, cari);

    Film* bantu = awal;
    Film* prev = NULL;

    if (bantu != NULL && bantu->judul == cari) {

        awal = bantu->next;

        delete bantu;

        cout << "\n[SUCCESS] Film berhasil dihapus!\n";

        pause();
        cls();
        return;
    }

    while (bantu != NULL && bantu->judul != cari) {

        prev = bantu;
        bantu = bantu->next;
    }

    if (bantu == NULL) {

        cout << "\n[INFO] Film tidak ditemukan!\n";

        pause();
        cls();
        return;
    }

    prev->next = bantu->next;

    delete bantu;

    cout << "\n[SUCCESS] Film berhasil dihapus!\n";

    pause();
    cls();
}

void saveFile() {

    ofstream file("film.txt");

    if (!file.is_open()) {

        cout << "\n[ERROR] File gagal dibuka!\n";
        return;
    }

    Film* bantu = awal;

    while (bantu != NULL) {

        file << bantu->judul << "|"
             << bantu->genre << "|"
             << bantu->rating << endl;

        bantu = bantu->next;
    }

    file.close();
}

void loadFile() {

    ifstream file("film.txt");

    if (!file.is_open()) {

        return;
    }

    while (true) {

        Film* baru = new Film();

        if (!getline(file, baru->judul, '|')) {

            delete baru;
            break;
        }

        getline(file, baru->genre, '|');

        file >> baru->rating;
        file.ignore();

        baru->next = NULL;

        if (awal == NULL) {

            awal = baru;
        }
        else {

            Film* bantu = awal;

            while (bantu->next != NULL) {

                bantu = bantu->next;
            }

            bantu->next = baru;
        }
    }

    file.close();
}

int main() {

    loadFile();

    int pilih;

    do {

        cls();
        header();

        cout << "1. Tambah Film\n";
        cout << "2. Tampilkan Film\n";
        cout << "3. Cari Film\n";
        cout << "4. Sorting Rating\n";
        cout << "5. Hapus Film\n";
        cout << "6. Simpan File\n";
        cout << "0. Keluar\n";

        cout << "\nPilih menu : ";
        cin >> pilih;

        if (cin.fail()) {

            cin.clear();
            cin.ignore(1000, '\n');

            cout << "\n[ERROR] Input menu harus angka!\n";

            pause();
            continue;
        }

        cin.ignore();

        switch (pilih) {

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

        cout << "\n[SUCCESS] Data berhasil disimpan!\n";

        pause();
        break;

        case 0:

        saveFile();

        cls();

        cout << "=========================================\n";
        cout << "        PROGRAM TELAH SELESAI            \n";
        cout << "=========================================\n";

        break;

        default:

        cout << "\n[WARNING] Menu tidak tersedia!\n";

        pause();
        }

    } while (pilih != 0);

    return 0;
}