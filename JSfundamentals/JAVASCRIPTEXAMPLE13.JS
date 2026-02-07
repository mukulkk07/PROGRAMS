/**
 * PROJECT: NodeSynth (WAV File Generator)
 * CONCEPTS: Binary Buffers, Bitwise Operations, Digital Signal Processing, Acoustics
 */

const fs = require('fs');

// --- CONFIGURATION ---
const SAMPLE_RATE = 44100; // CD Quality (44,100 samples per second)
const VOLUME = 0.5;        // Master Volume (0.0 to 1.0)

// --- 1. The Sound Engine ---
class Oscillator {
    // Waveforms are just math functions that return -1.0 to 1.0
    static sine(t, freq) {
        return Math.sin(2 * Math.PI * freq * t);
    }

    static square(t, freq) {
        return Math.sin(2 * Math.PI * freq * t) > 0 ? 1 : -1;
    }

    static sawtooth(t, freq) {
        return 2 * (t * freq - Math.floor(t * freq + 0.5));
    }

    static noise() {
        return Math.random() * 2 - 1;
    }
}

class Synthesizer {
    constructor() {
        this.data = []; // Stores the raw audio samples
    }

    // Add a note to the track
    play(noteFreq, durationSeconds, waveType = 'square') {
        const numSamples = Math.floor(durationSeconds * SAMPLE_RATE);
        
        // Envelope (ADSR) - Makes it sound less "harsh"
        // Fade In (Attack) and Fade Out (Release)
        const attack = Math.min(numSamples * 0.1, 1000); 
        const release = Math.min(numSamples * 0.1, 1000);

        for (let i = 0; i < numSamples; i++) {
            const t = this.data.length / SAMPLE_RATE; // Current time in seconds
            let amplitude = 0;

            // Select Waveform
            if (waveType === 'sine') amplitude = Oscillator.sine(t, noteFreq);
            else if (waveType === 'square') amplitude = Oscillator.square(t, noteFreq);
            else if (waveType === 'saw') amplitude = Oscillator.sawtooth(t, noteFreq);
            else amplitude = Oscillator.noise();

            // Apply Envelope (Volume Control)
            let env = 1.0;
            if (i < attack) {
                env = i / attack; // Fade In
            } else if (i > numSamples - release) {
                env = (numSamples - i) / release; // Fade Out
            }

            // Push final sample (Volume * Envelope * Wave)
            this.data.push(amplitude * VOLUME * env);
        }
    }

    // Add silence
    rest(durationSeconds) {
        const numSamples = Math.floor(durationSeconds * SAMPLE_RATE);
        for (let i = 0; i < numSamples; i++) this.data.push(0);
    }

    // --- 2. The Encoder (Writing Raw Bytes) ---
    save(filename) {
        const numChannels = 1; // Mono
        const bitsPerSample = 16; // Standard
        const byteRate = SAMPLE_RATE * numChannels * (bitsPerSample / 8);
        const blockAlign = numChannels * (bitsPerSample / 8);
        const dataSize = this.data.length * (bitsPerSample / 8);
        const fileSize = 36 + dataSize;

        const buffer = Buffer.alloc(44 + dataSize);
        let offset = 0;

        // Helper to write strings
        const writeString = (str) => {
            for (let i = 0; i < str.length; i++) {
                buffer.writeUInt8(str.charCodeAt(i), offset++);
            }
        };

        // --- WAV HEADER SPECIFICATION ---
        writeString('RIFF');                          // ChunkID
        buffer.writeUInt32LE(fileSize, offset);       // ChunkSize
        offset += 4;
        writeString('WAVE');                          // Format
        writeString('fmt ');                          // Subchunk1ID
        buffer.writeUInt32LE(16, offset);             // Subchunk1Size (16 for PCM)
        offset += 4;
        buffer.writeUInt16LE(1, offset);              // AudioFormat (1 = PCM)
        offset += 2;
        buffer.writeUInt16LE(numChannels, offset);    // NumChannels
        offset += 2;
        buffer.writeUInt32LE(SAMPLE_RATE, offset);    // SampleRate
        offset += 4;
        buffer.writeUInt32LE(byteRate, offset);       // ByteRate
        offset += 4;
        buffer.writeUInt16LE(blockAlign, offset);     // BlockAlign
        offset += 2;
        buffer.writeUInt16LE(bitsPerSample, offset);  // BitsPerSample
        offset += 2;
        writeString('data');                          // Subchunk2ID
        buffer.writeUInt32LE(dataSize, offset);       // Subchunk2Size
        offset += 4;

        // --- WRITING THE AUDIO DATA ---
        this.data.forEach(sample => {
            // Convert -1.0 to 1.0 range -> -32768 to 32767 (16-bit integer)
            let s = Math.max(-1, Math.min(1, sample));
            s = s < 0 ? s * 32768 : s * 32767;
            buffer.writeInt16LE(Math.floor(s), offset);
            offset += 2;
        });

        fs.writeFileSync(filename, buffer);
        console.log(`\n✅ Success! File saved to: ${filename}`);
        console.log(`🎵 Size: ${(fileSize / 1024 / 1024).toFixed(2)} MB`);
    }
}

// --- 3. The Composition ---
const synth = new Synthesizer();

console.log("--- DIGITAL SYNTHESIZER ---");
console.log("Generating audio data...");

// Note Frequencies (Hz)
const NOTES = {
    E5: 659.25,
    C5: 523.25,
    G5: 783.99,
    g4: 392.00,
    C4: 261.63
};

// Mario Theme Intro
const speed = 0.15;

// "Dee-dee-DEE... dee-dee-DOO"
const tune = [
    { n: NOTES.E5, d: speed },
    { n: NOTES.E5, d: speed },
    { n: null,     d: speed }, // rest
    { n: NOTES.E5, d: speed },
    { n: null,     d: speed },
    { n: NOTES.C5, d: speed },
    { n: NOTES.E5, d: speed * 2 },
    { n: NOTES.G5, d: speed * 2 },
    { n: null,     d: speed * 2 },
    { n: NOTES.g4, d: speed * 2 }
];

// Visualization Bar
const width = 50;
let progress = 0;

tune.forEach((note, index) => {
    // Show progress bar in terminal
    process.stdout.write(`\rEncoding: [${'='.repeat(index * 5).padEnd(width)}]`);
    
    if (note.n) {
        synth.play(note.n, note.d, 'square'); // 'sine', 'square', 'saw'
    } else {
        synth.rest(note.d);
    }
});

synth.save('mario.wav');