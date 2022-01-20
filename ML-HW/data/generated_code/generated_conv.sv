//conv0 kernel0 coeff
wire signed[15:0] conv0_kernel0_c[4:0];
assign conv0_kernel0_c[0] = 16'hFDE2;
assign conv0_kernel0_c[1] = 16'hFCE1;
assign conv0_kernel0_c[2] = 16'hF087;
assign conv0_kernel0_c[3] = 16'hF10E;
assign conv0_kernel0_c[4] = 16'hF55A;


//conv0 kernel1 coeff
wire signed[15:0] conv0_kernel1_c[4:0];
assign conv0_kernel1_c[0] = 16'hFF82;
assign conv0_kernel1_c[1] = 16'hFE45;
assign conv0_kernel1_c[2] = 16'h04AA;
assign conv0_kernel1_c[3] = 16'hFEE1;
assign conv0_kernel1_c[4] = 16'h01FC;


//conv0 kernel2 coeff
wire signed[15:0] conv0_kernel2_c[4:0];
assign conv0_kernel2_c[0] = 16'hF660;
assign conv0_kernel2_c[1] = 16'hF488;
assign conv0_kernel2_c[2] = 16'hEECE;
assign conv0_kernel2_c[3] = 16'hF2D6;
assign conv0_kernel2_c[4] = 16'hF818;


//conv0 kernel3 coeff
wire signed[15:0] conv0_kernel3_c[4:0];
assign conv0_kernel3_c[0] = 16'h022A;
assign conv0_kernel3_c[1] = 16'h0305;
assign conv0_kernel3_c[2] = 16'h0333;
assign conv0_kernel3_c[3] = 16'hF94F;
assign conv0_kernel3_c[4] = 16'hFAB0;


//conv0 kernel4 coeff
wire signed[15:0] conv0_kernel4_c[4:0];
assign conv0_kernel4_c[0] = 16'h110F;
assign conv0_kernel4_c[1] = 16'h193E;
assign conv0_kernel4_c[2] = 16'h1100;
assign conv0_kernel4_c[3] = 16'h1466;
assign conv0_kernel4_c[4] = 16'h0A20;


//conv1 kernel0_0 coeff
wire signed[15:0] conv1_kernel0_0_c[4:0];
assign conv1_kernel0_0_c[0] = 16'h03B1;
assign conv1_kernel0_0_c[1] = 16'h1198;
assign conv1_kernel0_0_c[2] = 16'h0C69;
assign conv1_kernel0_0_c[3] = 16'h0615;
assign conv1_kernel0_0_c[4] = 16'hFC23;


//conv1 kernel0_1 coeff
wire signed[15:0] conv1_kernel0_1_c[4:0];
assign conv1_kernel0_1_c[0] = 16'hFDD7;
assign conv1_kernel0_1_c[1] = 16'h0186;
assign conv1_kernel0_1_c[2] = 16'hFD16;
assign conv1_kernel0_1_c[3] = 16'hFE35;
assign conv1_kernel0_1_c[4] = 16'hFDC1;


//conv1 kernel0_2 coeff
wire signed[15:0] conv1_kernel0_2_c[4:0];
assign conv1_kernel0_2_c[0] = 16'hFDD7;
assign conv1_kernel0_2_c[1] = 16'h0F23;
assign conv1_kernel0_2_c[2] = 16'h16AE;
assign conv1_kernel0_2_c[3] = 16'h0C46;
assign conv1_kernel0_2_c[4] = 16'hFED2;


//conv1 kernel0_3 coeff
wire signed[15:0] conv1_kernel0_3_c[4:0];
assign conv1_kernel0_3_c[0] = 16'h03A7;
assign conv1_kernel0_3_c[1] = 16'h0139;
assign conv1_kernel0_3_c[2] = 16'h02C7;
assign conv1_kernel0_3_c[3] = 16'hFD5F;
assign conv1_kernel0_3_c[4] = 16'hFD19;


//conv1 kernel0_4 coeff
wire signed[15:0] conv1_kernel0_4_c[4:0];
assign conv1_kernel0_4_c[0] = 16'h0B41;
assign conv1_kernel0_4_c[1] = 16'hF478;
assign conv1_kernel0_4_c[2] = 16'hFC46;
assign conv1_kernel0_4_c[3] = 16'hFD87;
assign conv1_kernel0_4_c[4] = 16'hFEB5;


//conv1 kernel1_0 coeff
wire signed[15:0] conv1_kernel1_0_c[4:0];
assign conv1_kernel1_0_c[0] = 16'h061E;
assign conv1_kernel1_0_c[1] = 16'h07F6;
assign conv1_kernel1_0_c[2] = 16'h04D2;
assign conv1_kernel1_0_c[3] = 16'hFA82;
assign conv1_kernel1_0_c[4] = 16'hFE3A;


//conv1 kernel1_1 coeff
wire signed[15:0] conv1_kernel1_1_c[4:0];
assign conv1_kernel1_1_c[0] = 16'hFE5D;
assign conv1_kernel1_1_c[1] = 16'h0336;
assign conv1_kernel1_1_c[2] = 16'h01A5;
assign conv1_kernel1_1_c[3] = 16'h015D;
assign conv1_kernel1_1_c[4] = 16'h0200;


//conv1 kernel1_2 coeff
wire signed[15:0] conv1_kernel1_2_c[4:0];
assign conv1_kernel1_2_c[0] = 16'h0706;
assign conv1_kernel1_2_c[1] = 16'h04C6;
assign conv1_kernel1_2_c[2] = 16'h05B0;
assign conv1_kernel1_2_c[3] = 16'hFAE6;
assign conv1_kernel1_2_c[4] = 16'h0005;


//conv1 kernel1_3 coeff
wire signed[15:0] conv1_kernel1_3_c[4:0];
assign conv1_kernel1_3_c[0] = 16'hFF7E;
assign conv1_kernel1_3_c[1] = 16'h030B;
assign conv1_kernel1_3_c[2] = 16'h0087;
assign conv1_kernel1_3_c[3] = 16'h028F;
assign conv1_kernel1_3_c[4] = 16'h02E1;


//conv1 kernel1_4 coeff
wire signed[15:0] conv1_kernel1_4_c[4:0];
assign conv1_kernel1_4_c[0] = 16'hD665;
assign conv1_kernel1_4_c[1] = 16'h0C76;
assign conv1_kernel1_4_c[2] = 16'h149B;
assign conv1_kernel1_4_c[3] = 16'h1370;
assign conv1_kernel1_4_c[4] = 16'h0A85;
