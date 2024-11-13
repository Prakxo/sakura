#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum CommandValues {
    LOADSPC_VAL = 0x21,
    LOADSP_VAL = 0x22,
    AUDIO_VAL = 0x23,
    END_VAL = 0x43,
    ENDTXT_VAL = 0x72,
} CommandValues;

typedef struct command_s {
    const char* name;
    int argc;
    unsigned char* arg_sizes;
    CommandValues value;
} Command;

int last_command;
int textbox_line_count = 0;

unsigned char loadspc_sizes[] = {
    1,2,
};

unsigned char loadsp_sizes[] = {
    1,2, 1,
};
unsigned char audio_sizes[] = {
    2,
};
Command commands[] = {
    {"LOADSPC", 2, loadspc_sizes , LOADSPC_VAL},
    {"LOADSP", 3, loadsp_sizes, LOADSP_VAL},
    {"AUDIO", 1, audio_sizes, AUDIO_VAL},
    {"END", 0, NULL, END_VAL},
    {"ENDTXT", 0, NULL, ENDTXT_VAL},
};

#define COMMAND_MAX 5
#define COMMAND_MAX_LEN 30

#define CONTROL_CHAR '\x7C'
#define DELIM_CHAR '\x2C'
#define SKIP_NEWLINE_CHAR '\x28'

void __getPosByName(char* name, int* pos){
    int i;
    int found = 0;

    for(i = 0; i < COMMAND_MAX; i++){
        if(strcmp(name, commands[i].name) == 0){
            *pos = i;
            found = 1;
            break;
        }
    }

    if(!found){
        *pos = -1;
    }

}

char* __getName(char* command, int* argpos){
    int i;
    int len = strlen(command);
    int pos = 0;

    for(i = 0; i < len; i++){
        if(command[i] != ' '){
            pos++;
        }
        else{
            break;
        }
    }

    *argpos = pos +1;

    {
        char* name = calloc(0, pos);

        for(i = 0; i < pos; i++){
            name[i] = command[i];
        }
        return name;
    }
}

char* __getArgs(char* command, int startpos, int commandpos){
    int i;
    unsigned char* sizes = commands[commandpos].arg_sizes;
    char* out;
    int size_bytes = 0;
    int exit = 0;
    int h = 0;


    for(i = 0; i < commands[commandpos].argc; i++){
        size_bytes += sizes[i] * sizeof(char); 
    }

    out = calloc(0, size_bytes + commands[commandpos].argc -1);
    i = 0;

    while(exit != 1){
        char* buf = calloc(0, sizes[h]);
        char c = command[startpos];
        int j = 0;
        int convc;

        while(c != DELIM_CHAR && c != '\0'){
            buf[j++] = command[startpos++];
            c = command[startpos];
        }

        convc = atoi(buf);

        if(sizes[h] == 2){
            if(convc < 0xFF){
                out[i++] = '\0';
                out[i++] = convc;   
            }
            else{
                out[i++] = (convc & 0xFF00) >> 8;
                out[i++] = convc & 0xFF;

            }
        }
        else{
            out[i++] = convc;
        }

        out[i++] = DELIM_CHAR;

        free(buf);
        startpos++;

        if(c == '\0'){
            out[--i] = '\0';
            exit = 1;
        }

        h++;

    }

    return out;
}

char* process_command(char* command, int* postCommandLen){
    int argpos;
    char* comm = __getName(command, &argpos);
    int commpos;
    char* buf = (char*)calloc(0, 15);
    int i;
    int exit = 0;
    char* argv;
    unsigned char* sizes;
    int size_bytes = 0;

    __getPosByName(comm, &commpos);

    free(comm);

    if(commpos != -1){
        buf[0] = commands[commpos].value;
    }

    sizes = commands[commpos].arg_sizes;

    if(sizes != NULL){
        argv = __getArgs(command, argpos, commpos);

        for(i = 0; i < commands[commpos].argc; i++){
            size_bytes += sizes[i] * sizeof(char); 
        }

        i = 1;

        while(exit != 1){
            buf[i] = *argv++;

            if(i++ == size_bytes + commands[commpos].argc-1){
                exit = 1;
            }
        }
        *postCommandLen = size_bytes + 1 + commands[commpos].argc-1;

    }
    else{
        *postCommandLen = 1;
    }

    last_command = commands[commpos].value;

    return buf;
}

char* process_script(const char* in, unsigned long* outsize){
    FILE* f = fopen(in, "r");
    unsigned long size;
    char* out;
    int c;
    int i;
    
    fseek(f, 0, SEEK_END);
    size = ftell(f);
    rewind(f);

    out = (char*)malloc(size);

    c = fgetc(f);
    i = 0;

    while(c != EOF){


        if(c == CONTROL_CHAR){
            char* buf = calloc(0, COMMAND_MAX_LEN);
            int end = 0;
            int it = 0;
            char* processed;
            int commandLen;

            out[i++] = CONTROL_CHAR;

            while(end != 1){
                c = fgetc(f);
                if(c != CONTROL_CHAR){
                    buf[it++] = c;
                    #ifdef DEBUG
                    puts(buf);
                    #endif            
                }
                else{
                    end = 1;
                }
            }

            processed = process_command(buf, &commandLen);


            for(it = 0; it < commandLen; it++){
                out[i] = processed[it];
                i++;
            }


            out[i++] = CONTROL_CHAR;

            free(processed);

            free(buf);
            c = fgetc(f);

            if(last_command == END_VAL && c == '\n'){
                c = SKIP_NEWLINE_CHAR;
            }

        }
        else{   
            if(c != SKIP_NEWLINE_CHAR){
                out[i++] = c;
            }
            if(c == '\n'){
                textbox_line_count++;
            }

            if(last_command == END_VAL){
                textbox_line_count = 0;
            }
            c = fgetc(f);
        }
    }


    fclose(f);

    *outsize = i;

    return out;
}

void make_script(const char* in, const char* out){
    char* processed;
    FILE* f = fopen(out, "wb");
    unsigned long outsize;

    processed = process_script(in, &outsize);

    fwrite(processed, outsize, 1, f);
    fclose(f);

    free(processed);
}


void print_usage(const char* prgName){
    printf("Usage : %s input_file output_file\n", prgName);
}

int main (int argc, char** argv){
    int i;
    const char* inputFileName = NULL;
    const char* outputFileName = NULL;

    for (i = 1; i < argc; i++) {
        char* arg = argv[i];

        if (inputFileName == NULL){
            inputFileName = arg;
        }
        else if (outputFileName == NULL){
            outputFileName = arg;
        }
        else {
            puts("too many files specified!");
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


    make_script(inputFileName, outputFileName);

    return 0;
}
    