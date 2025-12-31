#ifndef STRUCTURE_H
#define STRUCTURE_H

// Definisi konstanta ukuran
#define MAX_CHAR 100
#define MAX_DATA 100

// Struct untuk Dapur
typedef struct {
    char nama[MAX_CHAR];
    double lat;     // Latitude
    double lon;     // Longitude
    char jenis[50];
    int kap_max;    // Kapasitas harian
    double rad_max; // Radius
    
    // Sisa stok per hari (0=Senin, 4=Jumat)
    int sisa[5]; 
} Dapur;

// Struct untuk Sekolah
typedef struct {
    char nama[MAX_CHAR];
    double lat;
    double lon;
    int butuh;      // Kebutuhan harian
    char jenis[50]; // Jenis makanan yg diminta
    int kap_simpan; 
    
    // Status kirim per hari (0=Belum, 1=Sudah)
    int status[5]; 
} Sekolah;

#endif