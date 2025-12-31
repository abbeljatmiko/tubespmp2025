#ifndef STRUCTURE_H
#define STRUCTURE_H

#define MAX_NAME 100
#define MAX_ITEMS 100

// Struktur untuk Dapur Pemasok
typedef struct {
    char nama[MAX_NAME];
    double latitude;
    double longitude;
    char jenis_makanan[50];
    int kapasitas_harian;
    double jarak_maks;
    // Helper untuk tracking sisa kapasitas per hari (Senin-Jumat)
    int sisa_kapasitas[5]; 
} Dapur;

// Struktur untuk Sekolah
typedef struct {
    char nama[MAX_NAME];
    double latitude;
    double longitude;
    int kebutuhan_harian;
    char jenis_kebutuhan[50];
    int kapasitas_simpan;
    // Helper untuk status terpenuhi per hari (0: belum, 1: sudah)
    int status_pemenuhan[5]; 
} Sekolah;

// Struktur untuk Laporan Distribusi (Output)
typedef struct {
    char nama_sekolah[MAX_NAME];
    char nama_dapur[MAX_NAME];
    int jumlah_kirim;
    double jarak_tempuh;
    int hari; // 0=Senin, 1=Selasa, dst
} LogDistribusi;

#endif