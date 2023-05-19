#include <stdlib.h>

double *synthesize_sound(int phoneme_index, int duration);
void save_to_wav(double *data, int num_samples, char *filename);

int main() {
  double *data = synthesize_sound(0, 5);
  save_to_wav(data, 48000, "output.wav");
  free(data);
  return 0;
}
