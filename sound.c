#include <stdio.h>
#include <string.h>

#include "sound.h"

void generate_square_wave(AudioSample* data, int sample_count, int freq, int duty_cycle, int amp) {
    for (int i = 0; i < sample_count; i++) {
        if (i % freq >= duty_cycle) {
            data[i].value = amp;
        } else {
            data[i].value = 0;
        }
    }
}

void generate_sawtooth_wave(AudioSample* data, int sample_count, int frequency, int amp) {
    for (int i = 0; i < sample_count; i++) {
        data[i].value = (i % frequency) * amp / frequency;
    }
}

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
    // generate_square_wave(audio_data, data.sample_count, 260, 100, 200);
    // Actually, let's try sawtooth for a bit
    generate_sawtooth_wave(audio_data, data.sample_count, 260, 200);

    WaveData wav;
    strcpy(wav.descriptor, "RIFF");
    wav.file_size = 3 * 4 + format.chunk_size + data.chunk_size;
    strcpy(wav.format, "WAVE");
    wav.format_data = format;
    wav.data = data;

    return wav;
}

