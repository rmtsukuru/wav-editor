#include <stdio.h>
#include <string.h>

#include "types.h"
#include "sound.h"
#include "file_output.h"

void print_hex_data(FILE* file) {
    byte buffer[8];
    int len;
    while (len = fread(buffer, 1, sizeof(buffer), file)) {
        for (int i = 0; i < len; i++) {
            printf("%02X ", buffer[i]);
        }
        printf("\"");
        for (int i = 0; i < len; i++) {
            printf("%c", buffer[i]);
        }
        printf("\"");
        printf("\n");
    }
}

int display_hex_contents(char* filename) {
    FILE* file = fopen(filename, "rb");

    if (file == NULL) {
        printf("Could not load file; check that filename is valid.\n");
        return -1;
    }

    print_hex_data(file);
    fclose(file);
    return 0;
}

int save_wav_file(char* filename) {
    FILE* file = fopen(filename, "wb");

    if (file == NULL) {
        printf("Could not load file; check that filename is valid.\n");
        return -1;
    }

    WaveData wav = load_wav_data();
    int byte_count = write_wav_file(file, &wav);
    fclose(file);
    printf("Saved file %s to disk (%d bytes).\n", filename, byte_count);

    return 0;
}

int main(int argc, char** argv) {
    if (argc > 2 && strcmp(argv[2], "--hex") == 0) {
        return display_hex_contents(argv[1]);
    }
    else if (argc > 2 && strcmp(argv[2], "--write") == 0) {
        return save_wav_file(argv[1]);
    }
    else if (argc > 1) {
        printf("%s\n", argv[1]);
    }
    else {
        printf("WAV File Editor\nPlease call with a filename.\n");
    }
}

