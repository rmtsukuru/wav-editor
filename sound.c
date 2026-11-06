#include <stdio.h>
#include <string.h>

#include "sound.h"

WaveData load_wav_data() {
    FormatChunk format;
    strcpy(format.chunk_id, "fmt ");
    format.chunk_size = 16;
    format.audio_format = 1;
    format.channel_count = 1; // Keep it simple, keep it mono for now
    format.sample_rate = 4177; // Keep it low for now
    format.bits_per_sample = 8;
    format.block_align = format.channel_count * format.bits_per_sample / 8;
    format.byte_rate = format.sample_rate * format.block_align;

    DataChunk data;
    strcpy(data.chunk_id, "data");
    data.sample_count = format.sample_rate / 2;
    data.chunk_size = data.sample_count * format.block_align;
    AudioSample* audio_data = data.data;
    // Simple square wave for now
    int frequency = 260;
    int duty_cycle = 100;
    for (int i = 0; i < data.sample_count; i++) {
        if (i % frequency >= duty_cycle) {
            audio_data[i].value = 200;
        } else {
            audio_data[i].value = 0;
        }
    }

    WaveData wav;
    strcpy(wav.descriptor, "RIFF");
    wav.file_size = 3 * 4 + format.chunk_size + data.chunk_size;
    strcpy(wav.format, "WAVE");
    wav.format_data = format;
    wav.data = data;

    return wav;
}

