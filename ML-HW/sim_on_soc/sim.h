#ifndef __SIM_H__
#define __SIM_H__

#include "fixed32.h"
#include "fir_coeff.h"
#include "weights.h"

void fir(fixed32 x[360], fixed32 y[261]) {
    for (int i = 100-1; i < 360; ++i) {
        fixed32 yi = 0;
        for (int k = 0; k < 100; ++k) {
            if (0 <= i-k && i-k < 360) {
                fixed32 xh = fixed32_mul(x[i-k], fir_coeff[k]);
                yi = fixed32_add(yi, xh);
            }
        }
        y[i-99] = yi;
    }
}

void conv0(fixed32 x[261], fixed32 y[5][129]) {
    for (int f = 0; f < 5; ++f) {
        for (int s = 4; s < 261; s += 2) {
            fixed32 tmp = 0;
            for (int ch = 0; ch < 1; ++ch) {
                for (int i = 0; i < 5; ++i) {
                    fixed32 m = fixed32_mul(x[s-4+i], conv0_weights[f][ch][i]);
                    tmp = fixed32_add(tmp, m);
                }
            }
            y[f][(s-4)>>1] = tmp;
        }
    }
}

void relu0(fixed32 x[5][129], fixed32 y[5][129]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 129; ++j) {
            y[i][j] = fixed32_sign(x[i][j]) ? 0 : x[i][j];
        }
    }
}

void maxpool0(fixed32 x[5][129], fixed32 y[5][64]) {
    for (int i = 0; i < 5; ++i) {
        for (int j = 0; j < 128; j += 2) {
            // if x[i][j] >= x[i][j+1]
            if (fixed32_ge(x[i][j], x[i][j+1])) {
                y[i][j>>1] = x[i][j];
            }
            else {
                y[i][j>>1] = x[i][j+1];
            }
        }
    }
}

void conv1(fixed32 x[5][64], fixed32 y[2][30]) {
    for (int f = 0; f < 2; ++f) {
        for (int s = 4; s < 64; s += 2) {
            fixed32 tmp = 0;
            for (int ch = 0; ch < 5; ++ch) {
                for (int i = 0; i < 5; ++i) {
                    fixed32 m = fixed32_mul(x[ch][s-4+i], conv1_weights[f][ch][i]);
                    tmp = fixed32_add(tmp, m);
                }
            }
            y[f][(s-4)>>1] = tmp;
        }
    }
}

void relu1(fixed32 x[2][30], fixed32 y[2][30]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 30; ++j) {
            y[i][j] = fixed32_sign(x[i][j]) ? 0 : x[i][j];
        }
    }
}

void maxpool1(fixed32 x[2][30], fixed32 y[2][15]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 30; j += 2) {
            // if x[i][j] >= x[i][j+1]
            if (fixed32_ge(x[i][j], x[i][j+1])) {
                y[i][j>>1] = x[i][j];
            }
            else {
                y[i][j>>1] = x[i][j+1];
            }
        }
    }
}

void flatten(fixed32 x[2][15], fixed32 y[30]) {
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 15; ++j) {
            y[i*15+j] = x[i][j];
        }
    }
}

void fc0(fixed32 x[30], fixed32 y[9]) {
    for (int r = 0; r < 9; ++r) {
        fixed32 tmp = 0;
        for (int c = 0; c < 30; ++c) {
            fixed32 m = fixed32_mul(x[c], fc0_weights[r][c]);
            tmp = fixed32_add(tmp, m);
        }
        y[r] = tmp;
    }
}

void fc1(fixed32 x[9], fixed32 y[5]) {
    for (int r = 0; r < 5; ++r) {
        fixed32 tmp = 0;
        for (int c = 0; c < 9; ++c) {
            fixed32 m = fixed32_mul(x[c], fc1_weights[r][c]);
            tmp = fixed32_add(tmp, m);
        }
        y[r] = tmp;
    }
}

int cmp(fixed32 x[5]) {
    int max_idx = 0;
    fixed32 max_val = x[0];
    for (int i = 1; i < 5; ++i) {
        if (fixed32_gt(x[i], max_val)) {
            max_idx = i;
            max_val = x[i];
        }
    }
    return max_idx;
}

int inference(fixed32 in[360])
{
    fixed32 fir_out[261];
    fir(in, fir_out);

    fixed32 conv0_out[5][129];
    conv0(fir_out, conv0_out);

    fixed32 relu0_out[5][129];
    relu0(conv0_out, relu0_out);

    fixed32 maxpool0_out[5][64];
    maxpool0(relu0_out, maxpool0_out);

    fixed32 conv1_out[2][30];
    conv1(maxpool0_out, conv1_out);

    fixed32 relu1_out[2][30];
    relu1(conv1_out, relu1_out);

    fixed32 maxpool1_out[2][15];
    maxpool1(relu1_out, maxpool1_out);

    fixed32 flatten_out[30];
    flatten(maxpool1_out, flatten_out);
    
    fixed32 fc0_out[9];
    fc0(flatten_out, fc0_out);

    fixed32 fc1_out[5];
    fc1(fc0_out, fc1_out);

    int cls = cmp(fc1_out);
    return cls;
}

#endif
