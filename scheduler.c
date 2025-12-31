#include <stdio.h>
#include <math.h>
#include <string.h>
#include "structure.h"
#include "scheduler.h"

// Rumus Haversine sederhana untuk jarak (bisa diganti Euclidean untuk simpel)
double hitung_jarak(double lat1, double lon1, double lat2, double lon2) {
    // Implementasi rumus jarak di sini
    // return sqrt(pow(lat2-lat1, 2) + pow(lon2-lon1, 2)); // Versi simpel
    return 0.0; // Placeholder
}

void jalankan_penjadwalan(Dapur dapurs[], int n_dapur, Sekolah sekolahs[], int n_sekolah) {
    // Loop untuk 5 hari kerja
    for (int hari = 0; hari < 5; hari++) {
        printf("--- Menjadwalkan Hari ke-%d ---\n", hari + 1);
        
        // Reset kapasitas dapur untuk hari baru
        for(int d=0; d<n_dapur; d++) {
            dapurs[d].sisa_kapasitas[hari] = dapurs[d].kapasitas_harian;
        }

        // Loop setiap sekolah
        for (int s = 0; s < n_sekolah; s++) {
            if (sekolahs[s].status_pemenuhan[hari] == 1) continue;

            int kebutuhan = sekolahs[s].kebutuhan_harian;
            int best_dapur_idx = -1;
            double min_dist = 999999.0;

            // Cari dapur terbaik (Terdekat & Kapasitas Cukup & Jenis Cocok)
            for (int d = 0; d < n_dapur; d++) {
                // Cek jenis makanan
                if (strcmp(dapurs[d].jenis_makanan, sekolahs[s].jenis_kebutuhan) != 0) continue;
                
                // Cek kapasitas
                if (dapurs[d].sisa_kapasitas[hari] < kebutuhan) continue;

                double dist = hitung_jarak(dapurs[d].latitude, dapurs[d].longitude, 
                                           sekolahs[s].latitude, sekolahs[s].longitude);

                // Cek jarak maksimum dapur
                if (dist > dapurs[d].jarak_maks) continue;

                // Greedy: Ambil yang terdekat
                if (dist < min_dist) {
                    min_dist = dist;
                    best_dapur_idx = d;
                }
            }

            // Jika ketemu dapur yang pas
            if (best_dapur_idx != -1) {
                dapurs[best_dapur_idx].sisa_kapasitas[hari] -= kebutuhan;
                sekolahs[s].status_pemenuhan[hari] = 1;
                printf("[SUKSES] Hari %d: %s dilayani oleh %s (Jarak: %.2f)\n", 
                       hari+1, sekolahs[s].nama, dapurs[best_dapur_idx].nama, min_dist);
                
                // TODO: Simpan ke struct LogDistribusi untuk di-export ke CSV nanti
            } else {
                printf("[GAGAL] Hari %d: %s tidak mendapatkan pasokan!\n", hari+1, sekolahs[s].nama);
                // TODO: Catat konflik ini
            }
        }
    }
}