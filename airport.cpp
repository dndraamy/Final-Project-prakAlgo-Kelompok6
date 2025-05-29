#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Penumpang {
    string nama;
    string nik;
    string tujuan;
    string kodeMaskapai;
    string noPenerbangan;
    string tanggal;
    Penumpang* next;
};

Penumpang* head = nullptr;

// fungsi simpan file pake ofstream (data txt)
void simpanFile() {
    ofstream file("data_penumpang.txt");
    if (!file) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    Penumpang* temp = head;
    while (temp != nullptr) {
        file << temp->nama << endl
             << temp->nik << endl
             << temp->tujuan << endl
             << temp->kodeMaskapai << endl
             << temp->noPenerbangan << endl
             << temp->tanggal << endl;
        temp = temp->next;
    }
    file.close();
}

// fungsi baca file pake ifstream (data txt)
void bacaFile() {
    ifstream file("data_penumpang.txt");
    if (!file.is_open()) {
        head = nullptr;
        return;
    }

    head = nullptr;
    Penumpang* last = nullptr;
    string nama, nik, tujuan, kode, nomor, tanggal;

    while (getline(file, nama) &&
           getline(file, nik) &&
           getline(file, tujuan) &&
           getline(file, kode) &&
           getline(file, nomor) &&
           getline(file, tanggal)) {

        Penumpang* baru = new Penumpang{nama, nik, tujuan, kode, nomor, tanggal, nullptr};

        // ini last head diganti apa ya biasanya kak taufik
        if (head == nullptr) {
            head = baru;
            last = baru;
        } else {
            last->next = baru;
            last = baru;
        }
    }

    file.close();
}

// implementasi linked list tunggal (insert at end)
void tambahData() {
    Penumpang* baru = new Penumpang;
    
    cout << "\nNama: ";
    getline(cin, baru->nama);
    cout << "NIK: ";
    getline(cin, baru->nik);
    cout << "Tujuan: ";
    getline(cin, baru->tujuan);
    cout << "Kode Maskapai: ";
    getline(cin, baru->kodeMaskapai);
    cout << "Nomor Penerbangan: ";
    getline(cin, baru->noPenerbangan);
    cout << "Tanggal (dd/mm/yyyy): ";
    getline(cin, baru->tanggal);
    
    baru->next = nullptr;

    if (head == nullptr) {
        head = baru;
    } else {
        Penumpang* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = baru;
    }

    simpanFile();
    cout << "Data berhasil ditambahkan.\n";
}

// implementasi linked list tunggal (operasi traversal/telusuri semua node dr awal-akhir)
void tampilkan() {
    bacaFile();

    if (head == nullptr) {
        cout << "Data penumpang kosong.\n";
        return;
    }

    Penumpang* temp = head;
    while (temp != nullptr) {
        cout << "\nNama: " << temp->nama
             << "\nNIK: " << temp->nik
             << "\nTujuan: " << temp->tujuan
             << "\nKode Maskapai: " << temp->kodeMaskapai
             << "\nNo Penerbangan: " << temp->noPenerbangan
             << "\nTanggal: " << temp->tanggal
             << "\n-------------------------";
        temp = temp->next;
    }
}

// implementasi sequential search
void cariNomorPenerbangan() {
    string nomor;
    cout << "Masukkan nomor penerbangan: ";
    getline(cin, nomor);

    Penumpang* temp = head;
    bool found = false;

    while (temp != nullptr) {
        if (temp->noPenerbangan == nomor) {
            cout << "Ditemukan: " << temp->nama << " - " << temp->tujuan << " (" << temp->tanggal << ")\n";
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Data tidak ditemukan.\n";
    }
}


// implementasi sequential search
void cariKodeMaskapai() {
    string kode;
    cout << "Masukkan kode maskapai: ";
    getline(cin, kode);

    Penumpang* temp = head;
    bool found = false;

    cout << "\nHasil Pencarian:\n";
    while (temp != nullptr) {
        if (temp->kodeMaskapai == kode) {
            cout << "Nama: " << temp->nama 
                 << " | No. Penerbangan: " << temp->noPenerbangan 
                 << " | Tanggal: " << temp->tanggal << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found) {
        cout << "Tidak ditemukan data untuk kode maskapai tersebut.\n";
    }
}


// implementasi bubble sort & insertion sort
void urutkanNama() {
    if (head == nullptr || head->next == nullptr) return;

    int pilihan;
    cout << "Urutkan nama penumpang berdasarkan:\n";
    cout << "1. Huruf awal ke akhir (A-Z)\n";
    cout << "2. Huruf akhir ke awal (Z-A)\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    if (pilihan == 1) {
        // Ascending - Bubble Sort
        bool swapped;
        do {
            swapped = false;
            Penumpang* curr = head;
            while (curr->next != nullptr) {
                if (curr->nama > curr->next->nama) {
                    swap(curr->nama, curr->next->nama);
                    swap(curr->nik, curr->next->nik);
                    swap(curr->tujuan, curr->next->tujuan);
                    swap(curr->kodeMaskapai, curr->next->kodeMaskapai);
                    swap(curr->noPenerbangan, curr->next->noPenerbangan);
                    swap(curr->tanggal, curr->next->tanggal);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
        cout << "Data berhasil diurutkan secara Ascending.\n";

    } else if (pilihan == 2) {
        // Descending - Insertion Sort
        Penumpang* sorted = nullptr;
        Penumpang* current = head;

        while (current != nullptr) {
            Penumpang* next = current->next;

            if (sorted == nullptr || current->nama > sorted->nama) {
                current->next = sorted;
                sorted = current;
            } else {
                Penumpang* temp = sorted;
                while (temp->next != nullptr && temp->next->nama > current->nama) {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next;
        }

        head = sorted;
        cout << "Data berhasil diurutkan secara Descending.\n";
    } else {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    simpanFile();
}


// implementasi???
void editJadwal() {
    string nik;
    cout << "Masukkan NIK penumpang: ";
    getline(cin, nik);
    Penumpang* temp = head;
    while (temp != nullptr) {
        if (temp->nik == nik) {
            cout << "Jadwal lama: " << temp->tanggal << "\n";
            cout << "Masukkan tanggal baru: ";
            getline(cin, temp->tanggal);
            simpanFile();
            cout << "Jadwal berhasil diubah.\n";
            return;
        }
        temp = temp->next;
    }
    cout << "Data tidak ditemukan.\n";
}

// implementasi linked list ganda (hapus node spesifik)
void hapusData() {
    string nik;
    cout << "Masukkan NIK penumpang: ";
    getline(cin, nik);
    
    if (head == nullptr) {
        cout << "Data penumpang kosong.\n";
        return;
    }

    Penumpang* bantu = head;
    Penumpang* prev = nullptr;

    while (bantu != nullptr && bantu->nik != nik) {
        bantu = bantu->next;
    }

    if (bantu == nullptr) {
        cout << "Data dengan NIK " << nik << " tidak ditemukan.\n";
        return;
    }

    if (bantu == head) {
        head = bantu->next;
    } else {
        prev->next = bantu->next;
    }

    delete bantu;
    simpanFile();
    cout << "Data berhasil dihapus.\n";
}

// fungsi utama program
int main() {
    int pilihan;

    bacaFile();

    do {
        cout << "\n--- CELESTIA AIRPORT ---\n";
        cout << "1. Tambah Data Penumpang\n";
        cout << "2. Tampilkan Semua Penumpang\n";
        cout << "3. Cari Penumpang Berdasarkan Nomor Penerbangan\n";
        cout << "4. Cari Penumpang Berdasarkan Kode Maskapai\n";
        cout << "5. Urutkan Penumpang Berdasarkan Nama\n";
        cout << "6. Edit Jadwal Penumpang\n";
        cout << "7. Hapus/Cancel Data Penumpang\n";
        cout << "8. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan) {
            case 1: tambahData(); break;
            case 2: tampilkan(); break;
            case 3: cariNomorPenerbangan(); break;
            case 4: cariKodeMaskapai(); break;
            case 5: urutkanNama(); break;
            case 6: editJadwal(); break;
            case 7: hapusData(); break;
            case 8: cout << "Keluar...\n"; break;
            default: cout << "Pilihan tidak valid.\n";
        }
    } while (pilihan != 8);

    // Free allocated memory
    while (head != nullptr) {
        Penumpang* temp = head;
        head = head->next;
        delete temp;
    }

    return 0;
}