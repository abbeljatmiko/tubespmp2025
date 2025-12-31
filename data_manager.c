#include <stdio.h>
#include <string.h>
#include "structure.h"
#include "data_manager.h"

// Fungsi membaca data Dapur
int load_data_dapur(const char* filename, Dapur list[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("[ERROR] Gagal membuka file: %s\n", filename);
        return 0;
    }

    char buffer[1024];
    int count = 0;
    
    // Lewati baris header (judul kolom)
    fgets(buffer, 1024, fp);

    // Baca baris per baris
    while (fgets(buffer, 1024, fp) && count < max) {
        // Format CSV: Nama,Lat,Long,Jenis,Kapasitas,JarakMaks
        // %[^,] artinya "baca string sampai ketemu koma"
        sscanf(buffer, "%[^,],%lf,%lf,%[^,],%d,%lf", 
               list[count].nama, 
               &list[count].latitude, 
               &list[count].longitude, 
               list[count].jenis_makanan, 
               &list[count].kapasitas_harian, 
               &list[count].jarak_maks);
        
        // Inisialisasi sisa kapasitas untuk 5 hari
        for(int i=0; i<5; i++) {
            list[count].sisa_kapasitas[i] = list[count].kapasitas_harian;
        }

        count++;
    }
    fclose(fp);
    return count;
}

// Fungsi membaca data Sekolah
int load_data_sekolah(const char* filename, Sekolah list[], int max) {
    FILE *fp = fopen(filename, "r");
    if (!fp) {
        printf("[ERROR] Gagal membuka file: %s\n", filename);
        return 0;
    }

    char buffer[1024];
    int count = 0;
    
    // Lewati baris header
    fgets(buffer, 1024, fp);

    while (fgets(buffer, 1024, fp) && count < max) {
        // Format CSV: Nama,Lat,Long,Kebutuhan,Jenis,KapasitasSimpan
        sscanf(buffer, "%[^,],%lf,%lf,%d,%[^,],%d", 
               list[count].nama, 
               &list[count].latitude, 
               &list[count].longitude, 
               &list[count].kebutuhan_harian, 
               list[count].jenis_kebutuhan, 
               &list[count].kapasitas_simpan);
        
        // Reset status pemenuhan
        for(int i=0; i<5; i++) {
            list[count].status_pemenuhan[i] = 0;
        }

        count++;
    }
    fclose(fp);
    return count;
}