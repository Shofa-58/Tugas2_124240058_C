#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cstring>

using namespace std;

struct Pesanan
{
    char nama[50];
    char jenis_roti[30];
    int totalharga;
};

struct queue
{
    Pesanan datapesanan;
    queue *next;
};

struct stack
{
    Pesanan datalayanan;
    stack *lanjut;
};

stack *awal, *top;
queue *depan, *belakang;
int pilihmenu, jumlah_data_diinput;
char menu_kembali;

void buatstack()
{
    awal = top = NULL;
}

void buatqueue()
{
    depan = NULL;
    belakang = NULL;
}

bool stackkosong() // untuk mengecek node/data di dalam riwayat masih kosong atau tidak
{
    return (awal == NULL);
}

bool queuekosong() // untuk mengecek node/data di dalam antrian masih kosong atau tidak
{
    return (depan == NULL);
}

void Input_Data_Pesanan()
{

    Pesanan tempstruct;
    cout << "\n=====================================\n";
    cout << "         INPUT DATA PESANAN\n";
    cout << "=====================================\n";

    cout << "Nama Pembeli       : ";
    cin.getline(tempstruct.nama, 50);
    cout << "Jenis Roti         : ";
    cin.getline(tempstruct.jenis_roti, 30);
    cout << "Total Harga (Rp)   : ";
    cin >> tempstruct.totalharga;
    cin.ignore();
    queue *NB = new queue;
    NB->datapesanan = tempstruct;
    NB->next = NULL;

    if (depan == NULL)
    {
        depan = NB;
    }
    else
    {
        belakang->next = NB;
    }
    belakang = NB;

    cout << "Data Pesanan Telah di Input di Antrian" << endl;
}

void Layani_Pembeli()
{
    if (queuekosong())
    {
        cout << "pesanan masih kosong" << endl;
        return;
    }
    {
        Pesanan templayanan;
        stack *bantu = awal;
        stack *newNode = new stack;
        queue *hapus = depan;
        newNode->datalayanan = hapus->datapesanan; // memasukkan data dari queue ke stack
        newNode->lanjut = NULL;
        depan = depan->next;
        delete hapus;

        if (stackkosong())
        {
            awal = top = newNode;
        }
        else
        {
            top->lanjut = newNode;
            top = newNode;
        }
        cout << "Antrian telah dilayani dan tersimpan di riwayat" << endl;
    }
}

void Tampilan_Data_Pesanan()
{
    if (queuekosong())
    {
        cout << "pesanan masih kosong" << endl;
        return;
    }
    queue *bantu = depan;
    if (bantu == NULL)
    {
        cout << "Pesanan masih kosong!" << endl;
        return;
    }
    cout << "Daftar Pesanan dalam Antrian :" << endl;

    cout << "\n====== DAFTAR MENU ======\n";
    cout << left << "|"
         << setw(30) << "Nama" << "|"
         << setw(20) << "Kategori" << "|"
         << setw(6) << "Harga" << "|\n";

    while (bantu != NULL)
    {
        cout << left << "|"
             << setw(30) << bantu->datapesanan.nama << "|"
             << setw(20) << bantu->datapesanan.jenis_roti << "|"
             << setw(6) << bantu->datapesanan.totalharga << "|\n";
        bantu = bantu->next;
    }
    cout << endl;
}

void Hapus_Antrian_Terbaru()
{
    if (queuekosong())
    {
        cout << "pesanan masih kosong" << endl;
        return;
    }
    if (depan == belakang) // Jika hanya ada satu node/data
    {
        queue *hapus = depan;
        depan = belakang = NULL;
        delete hapus;
        cout << "Data antrian telah di hapus" << endl;
        return;
    }

    queue *hapus, *bantu = depan; // Jika ada lebih dari satu node/data
    while (bantu->next != belakang)
    {
        bantu = bantu->next;
    }
    hapus = belakang;
    belakang = bantu;
    belakang->next = NULL;
    cout << "Data antrian telah di hapus" << endl;
}

void Tampilan_Data_Riwayat()
{
    if (stackkosong())
    {
        cout << "data riwayat masih kosong" << endl;
        return;
    }

    stack *bantu = awal;

    cout << "\n====== DAFTAR MENU ======\n";
    cout << left << "|"
         << setw(30) << "Nama" << "|"
         << setw(20) << "Kategori" << "|"
         << setw(6) << "Harga" << "|\n";

    while (bantu != NULL)
    {
        cout << left << "|"
             << setw(30) << bantu->datalayanan.nama << "|"
             << setw(20) << bantu->datalayanan.jenis_roti << "|"
             << setw(6) << bantu->datalayanan.totalharga << "|\n";
        bantu = bantu->lanjut;
    }
    cout << endl;
}

int main()
{
    buatqueue();
    buatstack();

    do
    {
        cout << "\nMENU PILIHAN:\n"
             << "1. Input Data Pesanan\n"
             << "2. Layani Pesanan\n"
             << "3. Tampilkan Data Pesanan\n"
             << "4. Hapus Data Pesanan Terakhir\n"
             << "5. Tampilkan Data Pesanan yang telah dilayani\n"
             << "6. Keluar Program\n"
             << endl;
        cout << "Pilih [1-6]: " << endl;
        cin >> pilihmenu;
        cin.ignore();

        switch (pilihmenu)
        {
        case 1:
        {
            Input_Data_Pesanan();
            break;
        }
        case 2:
        {
            Layani_Pembeli();
            break;
        }
        case 3:
        {
            Tampilan_Data_Pesanan();
            break;
        }
        case 4:
        {
            Hapus_Antrian_Terbaru();
            break;
        }
        case 5:
        {
            Tampilan_Data_Riwayat();
            break;
        }

        case 6:
        {
            cout << "\nTerima kasih!" << endl;
            exit(0);
            break;
        }
        default:
            cout << "\nPilihan tidak valid" << endl;
        }

        cout << "\nKembali ke menu? (y/n): ";
        cin >> menu_kembali;
        cin.ignore();
    } while (menu_kembali == 'y' || menu_kembali == 'Y');

    return 0;
}