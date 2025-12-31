#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX_NAME 100
#define MAX_ITEMS 100

typedef struct {
    char nama[MAX_NAME];
    double latitude;      // Wajib double
    double longitude;     // Wajib double
    char jenis_makanan[50];
    int kapasitas_harian;
    double jarak_maks;
    
    // Helper untuk 5 hari
    int sisa_kapasitas[5]; 
} Dapur;

typedef struct {
    char nama[MAX_NAME];
    double latitude;      // Wajib double
    double longitude;     // Wajib double
    int kebutuhan_harian;
    char jenis_kebutuhan[50];
    int kapasitas_simpan;
    
    // Helper status (0: Belum, 1: Sudah)
    int status_pemenuhan[5]; 
} Sekolah;

#endif