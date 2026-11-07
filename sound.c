#include <stdio.h>
#include <string.h>
#include <math.h>

#include "sound.h"

void generate_square_wave(AudioSample* data, int sample_count, int freq, int duty_cycle, int amp) {
    // TODO refactor this later (for now it is correct)
    // It should use sampling rate as a param or something in future
    int samples_per_second = sample_count * 2;
    int dt = samples_per_second / freq;
    for (int i = 0; i < sample_count; i++) {
        if (i % dt >= duty_cycle) {
            data[i].value = amp;
        } else {
            data[i].value = 0;
        }
    }
}

void generate_sawtooth_wave(AudioSample* data, int sample_count, int frequency, int amp) {
    // TODO refactor this later (for now it is correct)
    int samples_per_second = sample_count * 2;
    int dt = samples_per_second / frequency;
    for (int i = 0; i < sample_count; i++) {
        data[i].value = (i % dt) * amp / dt;
    }
}

void generate_sine_wave(AudioSample* data, int sample_count, int freq, int amp, int sample_rate) {
    int dt = sample_rate / freq;
    for (int i = 0; i < sample_count; i++) {
        data[i].value = sin(i * 2 * M_PI / dt) * amp;
    }
}

// Assume freqs always has length of 3.
void generate_triple_sine_wave(AudioSample* data, int len, int* freqs, int amp, int sample_rate) {
    int dt1 = sample_rate / freqs[0];
    int dt2 = sample_rate / freqs[1];
    int dt3 = sample_rate / freqs[2];
    for (int i = 0; i < len; i++) {
        int val1 = sin(i * 2 * M_PI / dt1);
        int val2 = sin(i * 2 * M_PI / dt2);
        int val3 = sin(i * 2 * M_PI / dt3);
        data[i].value = (val1 + val2 + val3) * amp;
    }
}

void generate_tangent_wave(AudioSample* data, int sample_count, int frequency, int sample_rate) {
    int dt = sample_rate / frequency;
    for (int i = 0; i < sample_count; i++) {
        data[i].value = tan((i * M_PI / 2) / dt);
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
    data.sample_count = format.sample_rate;
    data.chunk_size = data.sample_count * format.block_align;
    AudioSample* audio_data = data.data;
    // Simple square wave for now
    // generate_square_wave(audio_data, data.sample_count, 260, 10, 200);
    // We can also try sawtooth for a bit
    // generate_sawtooth_wave(audio_data, data.sample_count, 260, 200);
    // And now with sine waves!
    // generate_sine_wave(audio_data, data.sample_count, 260, 200);

    // And now for something really special
    int offset = data.sample_count / 6;
    int freqs[] = {260, 330, 390};
    generate_sine_wave(audio_data, offset, 260, 200, format.sample_rate);
    generate_sine_wave(audio_data + offset, offset * 2, 330, 200, format.sample_rate);
    generate_sine_wave(audio_data + offset * 2, offset * 3, 390, 200, format.sample_rate);
    generate_triple_sine_wave(audio_data + offset * 3, offset * 5, freqs, 200, format.sample_rate);

    WaveData wav;
    strcpy(wav.descriptor, "RIFF");
    wav.file_size = 3 * 4 + format.chunk_size + data.chunk_size;
    strcpy(wav.format, "WAVE");
    wav.format_data = format;
    wav.data = data;

    return wav;
}

