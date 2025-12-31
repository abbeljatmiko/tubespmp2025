#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "structure.h"
#include "data_manager.h"

// --- FUNGSI DATA CADANGAN (HARDCODED) ---
// Dipanggil otomatis jika CSV gagal dibaca agar program tidak error
void load_backup_dapur(Dapur list[], int *n) {
    printf("\n[INFO] Menggunakan DATA BACKUP Dapur (Internal)...\n");
    *n = 0;
    
    // Data 1
    strcpy(list[0].nama, "Dapur_Bu_Susi"); list[0].latitude = -6.9147; list[0].longitude = 107.6098;
    strcpy(list[0].jenis_makanan, "Nasi_Ayam"); list[0].kapasitas_harian = 500; list[0].jarak_maks = 10.0;
    
    // Data 2
    strcpy(list[1].nama, "Catering_Berkah"); list[1].latitude = -6.9210; list[1].longitude = 107.6150;
    strcpy(list[1].jenis_makanan, "Nasi_Ikan"); list[1].kapasitas_harian = 300; list[1].jarak_maks = 5.5;

    // Data 3
    strcpy(list[2].nama, "Dapur_Sehat"); list[2].latitude = -6.8900; list[2].longitude = 107.6100;
    strcpy(list[2].jenis_makanan, "Nasi_Telur"); list[2].kapasitas_harian = 450; list[2].jarak_maks = 15.0;

    // Data 4
    strcpy(list[3].nama, "Boga_Rasa"); list[3].latitude = -6.9050; list[3].longitude = 107.6200;
    strcpy(list[3].jenis_makanan, "Nasi_Daging"); list[3].kapasitas_harian = 600; list[3].jarak_maks = 12.0;

    *n = 4;
    // Init sisa kapasitas
    for(int i=0; i<*n; i++) {
        for(int h=0; h<5; h++) list[i].sisa_kapasitas[h] = list[i].kapasitas_harian;
    }
}

void load_backup_sekolah(Sekolah list[], int *n) {
    printf("\n[INFO] Menggunakan DATA BACKUP Sekolah (Internal)...\n");
    *n = 0;
    
    // Sekolah 1
    strcpy(list[0].nama, "SDN_01_Bdg"); list[0].latitude = -6.9150; list[0].longitude = 107.6100;
    list[0].kebutuhan_harian = 100; strcpy(list[0].jenis_kebutuhan, "Nasi_Ayam");

    // Sekolah 2
    strcpy(list[1].nama, "SDN_Merdeka"); list[1].latitude = -6.9220; list[1].longitude = 107.6160;
    list[1].kebutuhan_harian = 150; strcpy(list[1].jenis_kebutuhan, "Nasi_Ikan");

    // Sekolah 3
    strcpy(list[2].nama, "SMP_N_3"); list[2].latitude = -6.8950; list[2].longitude = 107.6120;
    list[2].kebutuhan_harian = 200; strcpy(list[2].jenis_kebutuhan, "Nasi_Telur");

    // Sekolah 4
    strcpy(list[3].nama, "SMA_Pasundan"); list[3].latitude = -6.9100; list[3].longitude = 107.6250;
    list[3].kebutuhan_harian = 300; strcpy(list[3].jenis_kebutuhan, "Nasi_Daging");

    // Sekolah 5 (Jauh)
    strcpy(list[4].nama, "SD_Terpencil"); list[4].latitude = -6.9900; list[4].longitude = 107.5000;
    list[4].kebutuhan_harian = 50; strcpy(list[4].jenis_kebutuhan, "Nasi_Ayam");

    *n = 5;
    // Init status
    for(int i=0; i<*n; i++) {
        for(int h=0; h<5; h++) list[i].status_pemenuhan[h] = 0;
    }
}

// --- FUNGSI LOAD UTAMA ---

int load_data_dapur(const char* filename, Dapur list[], int max) {
    FILE *fp = fopen(filename, "r");
    // Jika file tidak ada, pakai backup
    if (!fp) { 
        int c; load_backup_dapur(list, &c); return c; 
    }

    char buffer[1024];
    int count = 0;
    fgets(buffer, 1024, fp); // Skip header

    while (fgets(buffer, 1024, fp) && count < max) {
        // Parse CSV
        int parsed = sscanf(buffer, "%[^,],%lf,%lf,%[^,],%d,%lf", 
               list[count].nama, &list[count].latitude, &list[count].longitude, 
               list[count].jenis_makanan, &list[count].kapasitas_harian, &list[count].jarak_maks);
        
        // Safety: Jika gagal baca koordinat (lat/long 0), anggap error dan pakai backup
        if (parsed < 3 || list[count].latitude == 0.0) {
            printf("[WARNING] Gagal baca baris CSV atau format salah. Beralih ke Backup.\n");
            fclose(fp);
            int c; load_backup_dapur(list, &c); return c;
        }

        for(int i=0; i<5; i++) list[count].sisa_kapasitas[i] = list[count].kapasitas_harian;
        count++;
    }
    fclose(fp);
    return count;
}

int load_data_sekolah(const char* filename, Sekolah list[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) { 
        int c; load_backup_sekolah(list, &c); return c; 
    }

    char buffer[1024];
    int count = 0;
    fgets(buffer, 1024, fp); 

    while (fgets(buffer, 1024, fp) && count < max) {
        int parsed = sscanf(buffer, "%[^,],%lf,%lf,%d,%[^,],%d", 
               list[count].nama, &list[count].latitude, &list[count].longitude, 
               &list[count].kebutuhan_harian, list[count].jenis_kebutuhan, &list[count].kapasitas_simpan);
        
        if (parsed < 3 || list[count].latitude == 0.0) {
            printf("[WARNING] Gagal baca baris CSV atau format salah. Beralih ke Backup.\n");
            fclose(fp);
            int c; load_backup_sekolah(list, &c); return c;
        }

        for(int i=0; i<5; i++) list[count].status_pemenuhan[i] = 0;
        count++;
    }
    fclose(fp);
    return count;
}