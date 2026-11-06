#ifndef TYPES_H
#define TYPES_H

typedef unsigned char byte;

// This obv depends on sampling rate, but should be enough for short SFX for now
#define MAX_AUDIO_SAMPLES 100000

typedef struct {
    char chunk_id[4]; // "fmt "
    unsigned int chunk_size; // 16, for remaining bytes in chunk
    unsigned short audio_format; // 1 for PCM
    unsigned short channel_count; // 1 for mono, 2 for stereo
    unsigned int sample_rate; // in Hz, eg. 8000, 44100, 4177 (for NES), etc.
    unsigned short bits_per_sample; // 8 for 8-bit, 16 for 16-bit, etc.
    unsigned short block_align; // channel_count * bytes_per_sample
    unsigned int byte_rate; // sample_rate * block_align
} FormatChunk;

// For 8-bit samples, treat as unsigned number
// For 16-bit (and higher) samples, treat as signed number
typedef struct {
    // TODO set up union with sample type to support different types depending
    // on actual sample size
    int value;
} AudioSample;

typedef struct {
    char chunk_id[4]; // "data"
    unsigned int sample_count;
    unsigned int chunk_size; // Size of data in bytes (sample_count * block_align)
    AudioSample data[MAX_AUDIO_SAMPLES];
} DataChunk;

typedef struct {
    char descriptor[4]; // "RIFF"
    unsigned int file_size; // Excluding this field and file descriptor
                            // (so overall file size in bytes - 8)
    char format[4]; // "WAVE"
    FormatChunk format_data;
    DataChunk data;
} WaveData;

#endif

