#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../../vnlib/__selftypes.h"
#include "../../lib/lz4.h"


#define ARRAY_COUNT(arr) (long)(sizeof(arr) / sizeof(arr[0]))
#define ARRAY_COUNTU(arr) (unsigned long)(sizeof(arr) / sizeof(arr[0]))

void print_usage(const char* prgName){
    printf("Usage : %s input_file output_file [-c][-s]\n", prgName);
}

void make_resource(const char* in, const char* out){
    FILE* fo = fopen(out, "wb");
    FILE* fi = fopen(in, "rb");
    char* buf;
    unsigned int size;
    unsigned int postSize;
    char* outbuf;
    unsigned int compSize;

    fseek(fi, 0, SEEK_END);
    size = ftell(fi);
    rewind(fi);

    buf = (char*)malloc(size);

    (void)!fread(buf, size, 1, fi);

    compSize = LZ4_compressBound(size);

    outbuf = (char*)malloc(compSize);

    postSize = LZ4_compress_default(buf, outbuf, size, compSize);

    fwrite(outbuf, postSize, 1, fo);
    fclose(fo);
    fclose(fi);

    free(outbuf);
    free(buf);
}

int main(int argc, char** argv){
    int i;
    const char* inputFileName = NULL;
    const char* outputFileName = NULL;
    unsigned int isScript = FALSE;
    unsigned int compress = FALSE;

    for (i = 1; i < argc; i++) {
        char* arg = argv[i];

        if (inputFileName == NULL){
            inputFileName = arg;
        }
        else if (outputFileName == NULL){
            outputFileName = arg;
        }
        else if(strcmp(arg, "-c") == 0){
            isScript = TRUE;
        }
        else if(strcmp(arg, "-s") == 0){
            compress = TRUE;
        }
        else {
            puts("too many arguments specified!");
            print_usage(argv[0]);
            return 1;
        }
    }

    if (inputFileName == NULL) {
        puts("no input file specified");
        print_usage(argv[0]);
        return 1;
    }
    if (outputFileName == NULL) {
        puts("no output file specified");
        print_usage(argv[0]);
        return 1;
    }

    if(isScript){
        char buf[100];

        snprintf(buf, ARRAY_COUNT(buf), "../mkscript/mkscript %s %s %s", inputFileName, outputFileName, compress == TRUE ? "-c" : "");

        (void)!system(buf);
    }
    else{
        make_resource(inputFileName, outputFileName);
    }

    return 0;
}