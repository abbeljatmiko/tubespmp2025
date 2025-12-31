#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "data_manager.h" // Pastikan header ini ada fungsi load
#include "scheduler.h"    // Pastikan header ini ada logika jadwal

// Fungsi helper untuk membersihkan layar (opsional, agar rapi)
void clear_screen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

// Fungsi helper untuk input manual sederhana (Syarat 1.a & 1.b)
void tambah_dapur_manual(Dapur list[], int *count) {
    if (*count >= MAX_ITEMS) {
        printf("Kapasitas penyimpanan penuh!\n");
        return;
    }
    printf("\n--- Tambah Dapur Manual ---\n");
    printf("Nama Dapur: "); scanf(" %[^\n]", list[*count].nama);
    printf("Latitude: "); scanf("%lf", &list[*count].latitude);
    printf("Longitude: "); scanf("%lf", &list[*count].longitude);
    printf("Jenis Makanan: "); scanf(" %[^\n]", list[*count].jenis_makanan);
    printf("Kapasitas Harian: "); scanf("%d", &list[*count].kapasitas_harian);
    printf("Jarak Maks (km): "); scanf("%lf", &list[*count].jarak_maks);
    
    (*count)++;
    printf("Data berhasil ditambahkan!\n");
}

int main() {
    // Variabel Penyimpanan Data Utama
    Dapur daftar_dapur[MAX_ITEMS];
    Sekolah daftar_sekolah[MAX_ITEMS];
    int n_dapur = 0;
    int n_sekolah = 0;
    
    int pilihan;
    int data_terload = 0;

    do {
        // clear_screen(); // Uncomment jika ingin layar selalu bersih
        printf("\n=========================================\n");
        printf("   SISTEM RANTAI PASOK MAKAN BERGIZI (MBG)   \n");
        printf("=========================================\n");
        printf("1. Load Data dari File CSV\n");
        printf("2. Tambah Data Dapur Manual\n");
        printf("3. Tampilkan Data Saat Ini\n");
        printf("4. Jalankan Penjadwalan & Distribusi (5 Hari)\n");
        printf("5. Keluar\n");
        printf("-----------------------------------------\n");
        printf("Pilihan Anda: ");
        scanf("%d", &pilihan);

        switch (pilihan) {
            case 1:
                // Asumsi nama file sesuai soal/dummy
                // Pastikan implementasi load_data_sekolah ada di data_manager.c kamu
                n_dapur = load_data_dapur("data_supply.csv", daftar_dapur, MAX_ITEMS);
                n_sekolah = load_data_sekolah("data_sekolah.csv", daftar_sekolah, MAX_ITEMS);
                
                if (n_dapur > 0 && n_sekolah > 0) {
                    printf("\n[SUKSES] %d Dapur dan %d Sekolah berhasil dimuat.\n", n_dapur, n_sekolah);
                    data_terload = 1;
                } else {
                    printf("\n[ERROR] Gagal membaca file atau file kosong.\n");
                    printf("Pastikan 'data_supply.csv' dan 'data_sekolah.csv' ada di folder yang sama.\n");
                }
                break;

            case 2:
                tambah_dapur_manual(daftar_dapur, &n_dapur);
                data_terload = 1;
                break;

            case 3:
                printf("\n--- Data Dapur (%d) ---\n", n_dapur);
                for(int i=0; i<n_dapur; i++) {
                    printf("%d. %s (%s) - Kap: %d\n", i+1, daftar_dapur[i].nama, 
                           daftar_dapur[i].jenis_makanan, daftar_dapur[i].kapasitas_harian);
                }
                printf("\n--- Data Sekolah (%d) ---\n", n_sekolah);
                for(int i=0; i<n_sekolah; i++) {
                    printf("%d. %s (%s) - Butuh: %d\n", i+1, daftar_sekolah[i].nama, 
                           daftar_sekolah[i].jenis_kebutuhan, daftar_sekolah[i].kebutuhan_harian);
                }
                break;

            case 4:
                if (!data_terload || n_dapur == 0) {
                    printf("\n[PERINGATAN] Data belum tersedia. Silakan Load Data (Menu 1) atau Input Manual (Menu 2) dulu.\n");
                } else {
                    printf("\n--- Memulai Simulasi Penjadwalan ---\n");
                    jalankan_penjadwalan(daftar_dapur, n_dapur, daftar_sekolah, n_sekolah);
                    printf("\nSimulasi Selesai. Cek output di atas.\n");
                }
                break;

            case 5:
                printf("\nKeluar dari program. Terima kasih!\n");
                break;

            default:
                printf("\nPilihan tidak valid.\n");
        }
        
        if (pilihan != 5) {
            printf("\nTekan Enter untuk kembali ke menu...");
            getchar(); getchar(); // Trick sederhana untuk pause
        }

    } while (pilihan != 5);

    return 0;
}