#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "structure.h"

// Fungsi baca file CSV
int baca_dapur(char* nama_file, Dapur data[], int max);
int baca_sekolah(char* nama_file, Sekolah data[], int max);

#endif