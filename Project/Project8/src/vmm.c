#include "addext.h"
#include "tlb.h"
#include "memory.h"

#define MAXLINE 7   // 65535 + \n + \0

add getPhyAdd(add _inadd) {
    add phyadd;

    phyadd.number = tlb_search(_inadd.number);
    phyadd.offset = _inadd.offset;
    
    return phyadd;
}

int getValue(add _phyadd) {
    return mem[_phyadd.number][_phyadd.offset];
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
            getAdd(viradd), getAdd(phyadd), getValue(phyadd));
    }
    fclose(addfile);

    return 0;
}