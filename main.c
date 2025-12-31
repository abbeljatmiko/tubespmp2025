#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "data_manager.h"
#include "scheduler.h"

int main() {
    Dapur list_dapur[MAX_ITEMS];
    Sekolah list_sekolah[MAX_ITEMS];
    int n_dapur = 0;
    int n_sekolah = 0;
    int pilihan;

    do {
        printf("\n=== SISTEM MBG KABUPATEN ===\n");
        printf("1. Load Data (CSV)\n");
        printf("2. Tampilkan Data Terload\n");
        printf("3. Jalankan Penjadwalan\n");
        printf("4. Keluar\n");
        printf("Pilihan: "); scanf("%d", &pilihan);

        switch(pilihan) {
            case 1:
                n_dapur = load_data_dapur("data_supply.csv", list_dapur, MAX_ITEMS);
                n_sekolah = load_data_sekolah("data_sekolah.csv", list_sekolah, MAX_ITEMS);
                printf("\n[INFO] Data Siap: %d Dapur, %d Sekolah.\n", n_dapur, n_sekolah);
                break;
            case 2:
                printf("\n--- CEK DATA DAPUR (Untuk Debugging) ---\n");
                for(int i=0; i<n_dapur; i++) {
                    printf("%d. %s (Lat: %.4f, Lon: %.4f)\n", 
                           i+1, list_dapur[i].nama, list_dapur[i].latitude, list_dapur[i].longitude);
                }
                break;
            case 3:
                if(n_dapur > 0) jalankan_penjadwalan(list_dapur, n_dapur, list_sekolah, n_sekolah);
                else printf("Data kosong! Load dulu (Menu 1).\n");
                break;
        }
    } while (pilihan != 4);
    return 0;
}