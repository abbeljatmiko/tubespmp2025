#include <stdio.h>
#include <stdlib.h>
#include "structure.h"
#include "data_manager.h"
#include "scheduler.h"

int main() {
    Dapur list_dapur[MAX_DATA];
    Sekolah list_sekolah[MAX_DATA];
    int jml_dapur = 0;
    int jml_sekolah = 0;
    int menu;

    do {
        printf("\n=== APLIKASI RANTAI PASOK MBG ===\n");
        printf("1. Load Data CSV\n");
        printf("2. Tambah Dapur (Manual)\n");
        printf("3. Lihat Data\n");
        printf("4. Jalankan Jadwal\n");
        printf("5. Keluar\n");
        printf("Pilih > "); 
        scanf("%d", &menu);

        switch (menu) {
            case 1:
                jml_dapur = baca_dapur("data_supply.csv", list_dapur, MAX_DATA);
                jml_sekolah = baca_sekolah("data_sekolah.csv", list_sekolah, MAX_DATA);
                printf("Data terbaca: %d Dapur, %d Sekolah.\n", jml_dapur, jml_sekolah);
                break;
            
            case 2:
                if (jml_dapur < MAX_DATA) {
                    printf("Nama Dapur: "); scanf(" %[^\n]", list_dapur[jml_dapur].nama);
                    printf("Lat: "); scanf("%lf", &list_dapur[jml_dapur].lat);
                    printf("Lon: "); scanf("%lf", &list_dapur[jml_dapur].lon);
                    printf("Jenis Makanan: "); scanf(" %[^\n]", list_dapur[jml_dapur].jenis);
                    printf("Kapasitas: "); scanf("%d", &list_dapur[jml_dapur].kap_max);
                    printf("Radius Max: "); scanf("%lf", &list_dapur[jml_dapur].rad_max);
                    jml_dapur++;
                } else {
                    printf("Penyimpanan penuh.\n");
                }
                break;

            case 3:
                printf("\n--- List Dapur ---\n");
                int i;
                for(i=0; i<jml_dapur; i++) {
                    printf("%d. %s (%s)\n", i+1, list_dapur[i].nama, list_dapur[i].jenis);
                }
                break;

            case 4:
                if (jml_dapur > 0 && jml_sekolah > 0) {
                    proses_jadwal(list_dapur, jml_dapur, list_sekolah, jml_sekolah);
                } else {
                    printf("Data kosong. Silakan load data dulu.\n");
                }
                break;
                
            case 5:
                printf("Keluar program.\n");
                break;
        }
    } while (menu != 5);

    return 0;
}