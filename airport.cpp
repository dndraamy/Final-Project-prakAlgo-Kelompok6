#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

struct Penumpang
{
    string nama;
    string nik;
    string tujuan;
    string noPenerbangan;
    string waktu;
    Penumpang *next;
};

string tanggalSkrg;

Penumpang *head = nullptr;

// Simpan ke file txt dengan fprintf
void simpanFile()
{
    FILE *file = fopen("data_penumpang.txt", "w");
    if (!file)
    {
        cout << "Gagal membuka file untuk menyimpan!\n";
        return;
    }

    Penumpang *temp = head;
    while (temp)
    {
        fprintf(file, "%s\n%s\n%s\n%s\n%s\n",
                temp->nama.c_str(),
                temp->nik.c_str(),
                temp->tujuan.c_str(),
                temp->noPenerbangan.c_str(),
                temp->waktu.c_str());
        temp = temp->next;
    }

    fclose(file);
}

// Fungsi bantu untuk mengganti '\n' dari fgets
void hapusNewline(char *str)
{
    int i = 0;
    while (str[i])
    {
        if (str[i] == '\n')
        {
            str[i] = '\0';
            break;
        }
        i++;
    }
}

// Baca dari file txt dengan fgets
void bacaFile()
{
    FILE *file = fopen("data_penumpang.txt", "r");
    if (!file)
    {
        cout << "File belum ada atau tidak dapat dibuka.\n";
        return;
    }

    while (head)
    {
        Penumpang *hapus = head;
        head = head->next;
        delete hapus;
    }

    char nama[100], nik[20], tujuan[100], nomor[20], waktu[20];

    Penumpang *tail = nullptr;
    while (fgets(nama, sizeof(nama), file) &&
           fgets(nik, sizeof(nik), file) &&
           fgets(tujuan, sizeof(tujuan), file) &&
           fgets(nomor, sizeof(nomor), file) &&
           fgets(waktu, sizeof(waktu), file))
    {
        hapusNewline(nama);
        hapusNewline(nik);
        hapusNewline(tujuan);
        hapusNewline(nomor);
        hapusNewline(waktu);

        Penumpang *baru = new Penumpang;
        baru->nama = nama;
        baru->nik = nik;
        baru->tujuan = tujuan;
        baru->noPenerbangan = nomor;
        baru->waktu = waktu;
        baru->next = nullptr;

        if (!head)
        {
            head = tail = baru;
        }
        else
        {
            tail->next = baru;
            tail = baru;
        }
    }

    fclose(file);
}

// implementasi linked list tunggal (insert atn end)
void tambahData()
{
    system("cls");
    Penumpang *baru = new Penumpang;

    bacaFile();

    cout << "=== CALESTIA AIRPORT ===" << endl;
    cout << "Tambahkan Data Penumpang untuk tanggal " << tanggalSkrg << ":" << endl;

    cout << "\nNama: ";
    getline(cin, baru->nama);

    cout << "NIK: ";
    getline(cin, baru->nik);

    cout << "Tujuan: ";
    getline(cin, baru->tujuan);
    cout << "Nomor Penerbangan: ";
    getline(cin, baru->noPenerbangan);

    bool dataSudahAda;
    do
    {
        dataSudahAda = false;
        cout << "Waktu (hh/mm): ";
        getline(cin, baru->waktu);

        Penumpang *temp = head;
        while (temp != nullptr)
        {
            if (temp->nik == baru->nik && temp->waktu == baru->waktu)
            {
                cout << "\nError: Data dengan NIK " << baru->nik
                     << " dan waktu " << baru->waktu << " sudah ada!\n";
                cout << "Silakan masukkan waktu yang berbeda.\n\n";
                dataSudahAda = true;
                break;
            }
            temp = temp->next;
        }
    } while (dataSudahAda);

    baru->next = nullptr;

    if (head == nullptr)
    {
        head = baru;
    }
    else
    {
        Penumpang *temp = head;
        while (temp->next != nullptr)
        {
            temp = temp->next;
        }
        temp->next = baru;
    }

    simpanFile();
    cout << "\nData penumpang berhasil ditambahkan!";
    cin.get();
}

// implementasi linked list tunggal (operasi traversal/telusuri semua node dr awal-akhir)
void tampilkan()
{
    system("cls");
    bacaFile();

    cout << "=== CALESTIA AIRPORT ===" << endl;
    cout << "Menampilkan Data Penumpang pada tanggal " << tanggalSkrg << endl;

    if (head == nullptr)
    {
        cout << "Data penumpang kosong.\n";
    }
    else
    {
        cout << left << setw(20) << "Nama"
             << setw(20) << "NIK"
             << setw(15) << "Tujuan"
             << setw(20) << "No. Penerbangan"
             << setw(15) << "waktu" << endl;
        cout << string(105, '-') << endl;

        Penumpang *temp = head;
        while (temp != nullptr)
        {
            cout << left << setw(20) << temp->nama
                 << setw(20) << temp->nik
                 << setw(15) << temp->tujuan
                 << setw(20) << temp->noPenerbangan
                 << setw(15) << temp->waktu << endl;
            temp = temp->next;
        }
    }

    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.get();
}

// implementasi sequential search
void cariNomorPenerbangan()
{
    system("cls");

    string nomor;
    cout << "=== CALESTIA AIRPORT ===" << endl;
    cout << "\nMasukkan nomor penerbangan: ";
    getline(cin, nomor);
    cout << endl;

    Penumpang *temp = head;
    bool found = false;

    cout << "Data penumpang dengan nomor penerbangan " << nomor << " :" << endl;
    cout << string(65, '-') << endl;
    cout << left << setw(20) << "Nama"
         << setw(15) << "Tujuan"
         << setw(15) << "Tanggal"
         << setw(15) << "Waktu"
         << endl;

    cout << string(65, '-') << endl;

    while (temp != nullptr)
    {
        if (temp->noPenerbangan == nomor)
        {

            cout << left << setw(20) << temp->nama
                 << setw(15) << temp->tujuan
                 << setw(15) << tanggalSkrg
                 << setw(15) << temp->waktu
                 << endl;
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Tidak ditemukan!\n";
    }
    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.get();
}

// implementasi sequential search
void cariNIK()
{
    system("cls");
    string nik;
    cout << "=== CALESTIA AIRPORT ===" << endl;
    cout << "\nMasukkan NIK penumpang: ";
    getline(cin, nik);

    Penumpang *temp = head;
    bool found = false;

    cout << "\nHasil Pencarian :" << endl;
    while (temp != nullptr)
    {
        if (temp->nik == nik)
        {
            cout << "\nNama: " << temp->nama << "\n";
            cout << "Nomor penerbangan: " << temp->noPenerbangan << "\n";
            cout << "Tujuan: " << temp->tujuan << "\n";
            cout << "Tanggal: " << tanggalSkrg << "\n";
            cout << "Waktu: " << temp->waktu << "\n";
            found = true;
        }
        temp = temp->next;
    }

    if (!found)
    {
        cout << "Tidak ditemukan data penumpang dengan NIK " << nik << "!" << endl;
    }

    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.get();
}

void urutkanNama()
{
    system("cls");

    if (head == nullptr || head->next == nullptr)
        return;

    int pilihan;
    cout << "Urutkan nama penumpang berdasarkan:\n";
    cout << "1. Huruf awal ke akhir (A-Z)\n";
    cout << "2. Huruf akhir ke awal (Z-A)\n";
    cout << "Pilihan: ";
    cin >> pilihan;
    cin.ignore();

    bool swapped;
    Penumpang *curr;

    if (pilihan == 1)
    {
        // Ascending - Bubble Sort
        do
        {
            swapped = false;
            curr = head;
            while (curr->next != nullptr)
            {
                if (curr->nama > curr->next->nama)
                {
                    swap(curr->nama, curr->next->nama);
                    swap(curr->nik, curr->next->nik);
                    swap(curr->tujuan, curr->next->tujuan);
                    swap(curr->noPenerbangan, curr->next->noPenerbangan);
                    swap(curr->waktu, curr->next->waktu);
                    swapped = true;
                }
                curr = curr->next;
            }
        } while (swapped);
        cout << "Data berhasil diurutkan secara Ascending (A-Z).\n";
    }
    else if (pilihan == 2)
    {
        // Descending - Insertion Sort
        Penumpang *sorted = nullptr;
        Penumpang *current = head;

        while (current != nullptr)
        {
            Penumpang *next = current->next;

            if (sorted == nullptr || current->nama > sorted->nama)
            {
                current->next = sorted;
                sorted = current;
            }
            else
            {
                Penumpang *temp = sorted;
                while (temp->next != nullptr && temp->next->nama > current->nama)
                {
                    temp = temp->next;
                }
                current->next = temp->next;
                temp->next = current;
            }

            current = next;
        }

        head = sorted;
        cout << "Data berhasil diurutkan secara Descending.\n";
    }
    else
    {
        cout << "Pilihan tidak valid.\n";
        return;
    }

    simpanFile();
    cout << "\nTekan Enter untuk melihat hasil data tersortir...";
    cin.get();
    tampilkan();
}

// implementasi linked list tunggal (hapus node spesifik berdasarkan NIK)
void hapusData()
{
    system("cls");
    string nik, waktu;

    cout << "=== CALESTIA AIRPORT ===\n";
    cout << "Hapus Data Penumpang\n\n";

    bacaFile();

    if (head == nullptr)
    {
        cout << "Data penumpang kosong.\n";
        cin.get();
        cin.ignore();
        return;
    }

    cout << "Masukkan NIK penumpang: ";
    getline(cin, nik);
    cout << "Masukkan waktu penerbangan (hh/mm): ";
    getline(cin, waktu);

    Penumpang *prev = nullptr;
    Penumpang *current = head;
    bool found = false;

    while (current != nullptr)
    {
        if (current->nik == nik && current->waktu == waktu)
        {
            found = true;
            cout << "\nData yang akan dihapus:\n";
            cout << "Nama: " << current->nama << "\n";
            cout << "NIK: " << current->nik << "\n";
            cout << "Tujuan: " << current->tujuan << "\n";
            cout << "No. Penerbangan: " << current->noPenerbangan << "\n";
            cout << "Tanggal: " << tanggalSkrg << "\n";
            cout << "Waktu: " << current->waktu << "\n\n";

            char konfirmasi;
            cout << "Apakah Anda yakin ingin menghapus data ini? (y/n): ";
            cin >> konfirmasi;
            cin.ignore();

            if (konfirmasi == 'y' || konfirmasi == 'Y')
            {
                if (prev == nullptr)
                {
                    head = current->next;
                }
                else
                {
                    prev->next = current->next;
                }

                delete current;
                simpanFile();
                cout << "\nData berhasil dihapus!\n";
            }
            else
            {
                cout << "\nPenghapusan dibatalkan.\n";
            }
            break;
        }
        prev = current;
        current = current->next;
    }

    if (!found)
    {
        cout << "\nData dengan NIK " << nik << " dan waktu " << waktu << " tidak ditemukan.\n";
    }

    cout << "\nTekan Enter untuk kembali ke menu utama...";
    cin.get();
}

int main()
{
    system("cls");
    int pilihan;

    bacaFile();
    cout << "\n=== CELESTIA AIRPORT ===\n";
    cout << "Tanggal hari ini : ";
    getline(cin, tanggalSkrg);
    do
    {
        cout << "\nMenu Utama :\n";
        cout << "1. Tambah Data Penumpang\n";
        cout << "2. Tampilkan Semua Penumpang\n";
        cout << "3. Daftar Penumpang Berdasarkan Nomor Penerbangan\n";
        cout << "4. Cari Penumpang Berdasarkan NIK\n";
        cout << "5. Urutkan Penumpang Berdasarkan Nama\n";
        cout << "6. Hapus/Cancel Penumpang\n";
        cout << "7. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;
        cin.ignore();

        switch (pilihan)
        {
        case 1:
            tambahData();
            break;
        case 2:
            tampilkan();
            break;
        case 3:
            cariNomorPenerbangan();
            break;
        case 4:
            cariNIK();
            break;
        case 5:
            urutkanNama();
            break;
        case 6:
            hapusData();
            break;
        case 7:
            cout << "Terimakasih sudah menggunakan program.\n";
            cin.get();
            break;
        default:
            cout << "Pilihan tidak valid.";
        }
    } while (pilihan != 7);

    return 0;
}
