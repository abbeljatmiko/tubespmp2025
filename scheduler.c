#include <stdio.h>
#include <math.h>
#include <string.h>
#include "structure.h"
#include "scheduler.h"

// Fungsi Hitung Jarak (Euclidean dengan Faktor Konversi KM)
double hitung_jarak(double lat1, double lon1, double lat2, double lon2) {
    if (lat1 == 0 || lat2 == 0) return 0.0;

    // 1 Derajat Lat/Long ~= 111.32 KM di sekitar Ekuator
    double dLat = (lat1 - lat2) * 111.32;
    double dLon = (lon1 - lon2) * 111.32;
    
    double jarak = sqrt((dLat * dLat) + (dLon * dLon));
    return jarak;
}

void jalankan_penjadwalan(Dapur dapurs[], int n_dapur, Sekolah sekolahs[], int n_sekolah) {
    FILE *f_out = fopen("jadwal_distribusi.csv", "w");
    if (f_out) fprintf(f_out, "Hari,Sekolah,Dapur_Pemasok,Jenis,Qty,Jarak_Km,Status\n");

    int total_sukses = 0;
    int total_gagal = 0;

    printf("\n=== MULAI SIMULASI PENJADWALAN (5 HARI) ===\n");

    for (int hari = 0; hari < 5; hari++) {
        printf("\n--- HARI KE-%d ---\n", hari + 1);
        
        // Reset kapasitas harian dapur
        for(int d=0; d<n_dapur; d++) {
            dapurs[d].sisa_kapasitas[hari] = dapurs[d].kapasitas_harian;
        }

        for (int s = 0; s < n_sekolah; s++) {
            // Jika hari sebelumnya sudah terpenuhi (opsional logic), kita reset status di load_data
            // Tapi di sini asumsinya setiap hari butuh makan.
            
            double min_dist = 999999.0;
            int best_dapur = -1;

            for (int d = 0; d < n_dapur; d++) {
                // 1. Cek Jenis Makanan (String Compare)
                if (strcmp(dapurs[d].jenis_makanan, sekolahs[s].jenis_kebutuhan) != 0) continue;

                // 2. Cek Kapasitas
                if (dapurs[d].sisa_kapasitas[hari] < sekolahs[s].kebutuhan_harian) continue;

                // 3. Hitung Jarak
                double dist = hitung_jarak(dapurs[d].latitude, dapurs[d].longitude, 
                                           sekolahs[s].latitude, sekolahs[s].longitude);

                // 4. Cek Radius Maksimal
                if (dist > dapurs[d].jarak_maks) continue;

                // Greedy: Pilih yang terdekat
                if (dist < min_dist) {
                    min_dist = dist;
                    best_dapur = d;
                }
            }

            if (best_dapur != -1) {
                dapurs[best_dapur].sisa_kapasitas[hari] -= sekolahs[s].kebutuhan_harian;
                sekolahs[s].status_pemenuhan[hari] = 1;
                total_sukses++;

                printf("[SUKSES] %-15s <-- %-15s (Jarak: %.2f km)\n", 
                       sekolahs[s].nama, dapurs[best_dapur].nama, min_dist);
                
                if (f_out) fprintf(f_out, "%d,%s,%s,%s,%d,%.2f,Sukses\n", 
                        hari+1, sekolahs[s].nama, dapurs[best_dapur].nama, 
                        sekolahs[s].jenis_kebutuhan, sekolahs[s].kebutuhan_harian, min_dist);
            } else {
                total_gagal++;
                printf("[GAGAL]  %-15s : Tidak ada pemasok cocok!\n", sekolahs[s].nama);
                if (f_out) fprintf(f_out, "%d,%s,NONE,%s,%d,0,Gagal\n", 
                        hari+1, sekolahs[s].nama, sekolahs[s].jenis_kebutuhan, sekolahs[s].kebutuhan_harian);
            }
        }
    }

    if (f_out) fclose(f_out);
    
    printf("\n=== RINGKASAN ===\n");
    printf("Sukses: %d | Gagal: %d\n", total_sukses, total_gagal);
    printf("File CSV Export: jadwal_distribusi.csv\n");
}