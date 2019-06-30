#pragma once

#include "ImgPgm.h"

void  make_histogram( CImgPgm *data_a, CImgPgm *data_b );
int	find_max( long vec[], int num );

void thinning( CImgPgm *data_a, CImgPgm *data_b  );
