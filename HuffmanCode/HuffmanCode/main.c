//
//  main.c
//  HuffmanCode
//
//  Created by Sang Gyeong Jo on 2016. 11. 16..
//  Copyright © 2016년 Sang Gyeong Jo. All rights reserved.
//

#include "Huffman.h"

int main(int argc, const char * argv[]) {
    
    FILE *f_to_enc = fopen("data10.txt", "r+");
    FILE *f_o_table = fopen("data10_tbl.txt", "w+");
    FILE *f_o_enc = fopen("data10_enc.txt", "w+");
    
    FILE *f_i_table = fopen("data10_table.txt", "r+");
    FILE *f_i_dec = fopen("data10_encoded.txt", "r+");
    FILE *f_output = fopen("data10_decoded","w+");
    
    build_data(f_to_enc);
    f_to_enc = fopen("data10.txt", "r+");
    encoding(f_to_enc, f_o_enc, f_o_table);
    decoding(f_i_table, f_i_dec, f_output);
    
    return 0;
}
