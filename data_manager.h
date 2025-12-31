#ifndef DATA_MANAGER_H
#define DATA_MANAGER_H

#include "structure.h"

int load_data_dapur(const char* filename, Dapur list[], int max);
int load_data_sekolah(const char* filename, Sekolah list[], int max);

#endif