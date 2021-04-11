#include "tlb.h"
#include "memory.h"
#include <string.h>

#define MAXLINE 7   // 65535 + \n + \0

add getPhyAdd(add _inadd) {
    add phyadd;

    phyadd.number = tlb_search(_inadd.number);
    phyadd.offset = _inadd.offset;
    
    return phyadd;
}

int main(int argc, char* argv[]){
    if(argc==1){
        fprintf(stderr,"Please input the address file name!\n");
        return 1;
    }

    FILE* addfile;
    if((addfile = fopen(argv[1],"r"))==NULL){
        fprintf(stderr,"Can't open file %s\n",argv[1]);
        return 1;
    }

    char addline[MAXLINE];
    while(fgets(addline, MAXLINE, addfile)!=NULL){
        int rline = atoi(addline);
        add viradd = addext(rline);
        // For trial
        // fprintf(stdout,"Input: %5d\tPage number: %3d\tOffset: %3d\n", rline, addin.page_number, addin.offset);
        add phyadd = getPhyAdd(viradd);
        fprintf(stdout, "Virtual address: %d Physical address: %d Value: %d\n", 
            getAdd(viradd), getAdd(phyadd), get_value(phyadd));
    }
    fclose(addfile);

    if(argc==3 && strcmp(argv[2],"-s")==0)
        fprintf(stdout, "\nPage-fault rate:\t%.2f\nTLB hit rate:\t\t%.2f\n", get_pagefault_rate(), get_tlbhit_rate());

    return 0;
}