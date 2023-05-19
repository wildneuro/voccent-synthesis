#include <fftw3.h>
#include <math.h>
#include <stdlib.h>
#include <vector>

const int NUM_SAMPLES = (48000); // Sampling rate.

struct PhonemeProfile {
  double frequency1;
  double frequency2;
  double frequency3;
};

PhonemeProfile phonemes[] = {
    {730.0, 1090.0, 2440.0}, // F1, F2, F3 for /a/
                             // Add more phonemes here
};

double *synthesize_sound(int phoneme_index, int duration) {
  PhonemeProfile profile = phonemes[phoneme_index];

  double amplitude = 32000;
  int sample_rate = 48000;
  int num_samples = duration * sample_rate;

  fftw_complex *signal =
      (fftw_complex *)fftw_malloc(sizeof(fftw_complex) * num_samples);

  for (int i = 0; i < num_samples; i++) {
    double t = (double)i / NUM_SAMPLES;

    double sum_signal = 0.0;
    for (int harmonic = 1; harmonic <= 10; ++harmonic) {
      sum_signal +=
          (1.0 / harmonic) *
          (amplitude * sin(2.0 * M_PI * harmonic * profile.frequency1 * t / 2) +
           amplitude * sin(2.0 * M_PI * harmonic * profile.frequency2 * t / 4) +
           amplitude *
               sin(2.0 * M_PI * harmonic * profile.frequency3 * t / 12));
    }

    /* signal[i][0] = amplitude * sin(440.0 * t * 2.0 * M_PI); */
    signal[i][0] = sum_signal;
    signal[i][1] = 0.0;
  }

  /* for (int i = 0; i < num_samples; i++) { */
  /*   double t = (double)i / NUM_SAMPLES; */
  /*   signal[i][0] = amplitude * sin(440.0 * t * 2.0 * M_PI); */
  /*   signal[i][1] = 0.0; // imaginary part of signal[i] is 0 */
  /* } */

  double *data = new double[num_samples];
  for (int i = 0; i < num_samples; i++) {
    data[i] = signal[i][0];
  }

  fftw_free(signal);

  return data;
}
