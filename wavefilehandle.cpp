#include <stdio.h>
#include <stdlib.h>

#include "AudioFile/AudioFile.h"

//=======================================================================
void save_to_wav(double *data, int num_samples, char *filename) {
  AudioFile<double> audioFile;
  audioFile.setAudioBufferSize(1, num_samples); // 1 channel, num_samples long

  for (int i = 0; i < num_samples; i++) {
    audioFile.samples[0][i] = data[i] / 32767.0; // Convert to [-1.0, 1.0] range
  }

  audioFile.setBitDepth(16);
  audioFile.setSampleRate(48000);

  bool ok = audioFile.save(filename, AudioFileFormat::Wave);
  if (!ok) {
    printf("Couldn't save %s\n", filename);
    exit(1);
  }
}
