
#include "file_output.h"

// Little-endian, because the WAV file format is silly
void write_bytes(byte* bytes, int value, int len) {
    for (int i = 0; i < len; i++) {
        int offset = i;
        int bitmask = 0xFF << (8 * offset);
        bytes[i] = (value & bitmask) >> (8 * offset);
    }
}

int write_wav_file(FILE* file, WaveData* wav) {
    // Header Chunk
    int byte_count = 0;
    byte buffer[4];
    fwrite(wav->descriptor, 4, 1, file);
    write_bytes(buffer, wav->file_size, 4);
    fwrite(buffer, 4, 1, file);
    fwrite(wav->format, 4, 1, file);
    byte_count += 12;
    // Format Chunk
    FormatChunk* format = &wav->format_data;
    fwrite(format->chunk_id, 4, 1, file);
    write_bytes(buffer, format->chunk_size, 4);
    fwrite(buffer, 4, 1, file);
    write_bytes(buffer, format->audio_format, 2);
    fwrite(buffer, 2, 1, file);
    write_bytes(buffer, format->channel_count, 2);
    fwrite(buffer, 2, 1, file);
    write_bytes(buffer, format->sample_rate, 4);
    fwrite(buffer, 4, 1, file);
    printf("Sample Rate: %d\n", format->sample_rate);
    write_bytes(buffer, format->byte_rate, 4);
    fwrite(buffer, 4, 1, file);
    write_bytes(buffer, format->block_align, 2);
    fwrite(buffer, 2, 1, file);
    write_bytes(buffer, format->bits_per_sample, 2);
    fwrite(buffer, 2, 1, file);
    byte_count += 24;
    // Data Chunk
    DataChunk* data = &wav->data;
    fwrite(data->chunk_id, 4, 1, file);
    write_bytes(buffer, data->chunk_size, 4);
    fwrite(buffer, 4, 1, file);
    printf("Data Chunk Size: %d\n", data->chunk_size);
    byte_count += 8;
    AudioSample* audio_data = data->data;
    for (int i = 0; i < data->sample_count; i++) {
        // Assume 8-bit samples for now
        byte value = (byte) audio_data[i].value;
        fwrite(&value, 1, 1, file);
        byte_count++;
    }
    return byte_count;
}

