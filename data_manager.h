#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "structure.h"

// Membaca file CSV dapur
// Mengembalikan jumlah data yang berhasil dibaca
int load_data_dapur(const char* filename, Dapur list[], int max);

// Membaca file CSV sekolah
// Mengembalikan jumlah data yang berhasil dibaca
int load_data_sekolah(const char* filename, Sekolah list[], int max);

// Tambahkan ini di bagian bawah data_manager.c
int load_data_sekolah(const char* filename, Sekolah list[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) return 0;

    char buffer[1024];
    int count = 0;
    
    fgets(buffer, 1024, fp); // Skip Header

    while (fgets(buffer, 1024, fp) && count < max) {
        // Contoh parsing sederhana (Sesuaikan urutan kolom di CSV kamu)
        // Format asumsi: Nama,Lat,Long,Kebutuhan,Jenis,KapasitasSimpan
        // sscanf(buffer, "%[^,],%lf,%lf,%d,%[^,],%d", ...); 
        
        // DUMMY PARSING (Ganti dengan sscanf yg benar)
        // list[count].nama = ...
        
        count++;
    }
    fclose(fp);
    return count;
}