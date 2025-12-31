#include <stdio.h>
#include <math.h>
#include <string.h>
#include "structure.h"
#include "scheduler.h"

// Fungsi hitung jarak sederhana (dalam KM)
double get_jarak(double lat1, double lon1, double lat2, double lon2) {
    // Konversi kasar: 1 derajat = 111.32 km
    double dy = (lat1 - lat2) * 111.32;
    double dx = (lon1 - lon2) * 111.32;
    return sqrt((dx * dx) + (dy * dy));
}

void proses_jadwal(Dapur d_list[], int nd, Sekolah s_list[], int ns) {
    // Buka file output
    FILE *fout = fopen("jadwal_distribusi.csv", "w");
    fprintf(fout, "Hari,Sekolah,Pemasok,Jarak,Status\n");

    int hari, s, d;
    int sukses = 0, gagal = 0;

    printf("\n--- Memulai Penjadwalan ---\n");

    // Loop Senin (0) sampai Jumat (4)
    for (hari = 0; hari < 5; hari++) {
        printf("Hari ke-%d:\n", hari + 1);

        // Reset kapasitas harian dapur
        for (d = 0; d < nd; d++) {
            d_list[d].sisa[hari] = d_list[d].kap_max;
        }

        // Cek setiap sekolah
        for (s = 0; s < ns; s++) {
            int target_dapur = -1;
            double jarak_min = 99999.0; // Set angka besar

            // Cari dapur yang cocok
            for (d = 0; d < nd; d++) {
                // 1. Cek jenis makanan
                if (strcmp(d_list[d].jenis, s_list[s].jenis) != 0) continue;

                // 2. Cek stok dapur
                if (d_list[d].sisa[hari] < s_list[s].butuh) continue;

                // 3. Hitung jarak
                double jarak = get_jarak(d_list[d].lat, d_list[d].lon, 
                                         s_list[s].lat, s_list[s].lon);

                // 4. Cek radius maksimal dapur
                if (jarak > d_list[d].rad_max) continue;

                // Ambil yang paling dekat
                if (jarak < jarak_min) {
                    jarak_min = jarak;
                    target_dapur = d;
                }
            }

            // Simpan hasil
            if (target_dapur != -1) {
                // Kurangi stok dapur
                d_list[target_dapur].sisa[hari] -= s_list[s].butuh;
                s_list[s].status[hari] = 1;
                sukses++;

                printf("  [OK] %s <- %s (%.2f km)\n", 
                       s_list[s].nama, d_list[target_dapur].nama, jarak_min);
                
                fprintf(fout, "%d,%s,%s,%.2f,Sukses\n", 
                        hari+1, s_list[s].nama, d_list[target_dapur].nama, jarak_min);
            } else {
                gagal++;
                printf("  [FAIL] %s tidak dapat pasokan.\n", s_list[s].nama);
                fprintf(fout, "%d,%s,NONE,0,Gagal\n", 
                        hari+1, s_list[s].nama);
            }
        }
    }

    fclose(fout);
    printf("\nSelesai. Total Sukses: %d, Gagal: %d\n", sukses, gagal);
    printf("Hasil disimpan di 'jadwal_distribusi.csv'\n");
}