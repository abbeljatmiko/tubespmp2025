#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structure.h"
#include "data_manager.h"

int baca_dapur(char* nama_file, Dapur data[], int max) {
    FILE *fp = fopen(nama_file, "r");
    if (fp == NULL) {
        printf("Gagal buka file: %s\n", nama_file);
        return 0;
    }

    char baris[200];
    int i = 0;
    
    // Lewati baris judul (header)
    fgets(baris, 200, fp);

    // Baca baris per baris
    while (fgets(baris, 200, fp) != NULL && i < max) {
        // Parse data sesuai urutan kolom di CSV
        sscanf(baris, "%[^,],%lf,%lf,%[^,],%d,%lf", 
               data[i].nama, 
               &data[i].lat, 
               &data[i].lon, 
               data[i].jenis, 
               &data[i].kap_max, 
               &data[i].rad_max);
        
        // Reset stok untuk 5 hari ke depan
        int h;
        for(h = 0; h < 5; h++) {
            data[i].sisa[h] = data[i].kap_max;
        }
        
        i++;
    }

    fclose(fp);
    return i; // Kembalikan jumlah data terbaca
}

int baca_sekolah(char* nama_file, Sekolah data[], int max) {
    FILE *fp = fopen(nama_file, "r");
    if (fp == NULL) {
        printf("Gagal buka file: %s\n", nama_file);
        return 0;
    }

    char baris[200];
    int i = 0;
    
    fgets(baris, 200, fp); // Skip header

    while (fgets(baris, 200, fp) != NULL && i < max) {
        sscanf(baris, "%[^,],%lf,%lf,%d,%[^,],%d", 
               data[i].nama, 
               &data[i].lat, 
               &data[i].lon, 
               &data[i].butuh, 
               data[i].jenis, 
               &data[i].kap_simpan);
        
        // Reset status pengiriman
        int h;
        for(h = 0; h < 5; h++) {
            data[i].status[h] = 0;
        }
        
        i++;
    }

    fclose(fp);
    return i;
}