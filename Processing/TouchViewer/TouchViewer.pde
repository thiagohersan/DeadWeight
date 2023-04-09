import processing.serial.*;

Serial port;

int NUM_CHANNELS = 5;

int[] val = new int[NUM_CHANNELS];
int[][] values = new int[NUM_CHANNELS][];

color[] ccolor = {
  color(255, 0, 100),
  color(255, 165, 0),
  color(255, 255, 0),
  color(55, 255, 20),
  color(130, 230, 255)
};

boolean SPLIT_CHANNELS = true;
float maxY = 0;
float offsetYFactor = 0;

void setup() {
  size(1280, 600);
  frameRate(30);
  println(Serial.list());
  port = new Serial(this, Serial.list()[2], 115200);

  for (int c = 0; c < val.length; c++) {
    values[c] = new int[width];
  }

  smooth();

  if (SPLIT_CHANNELS) {
    maxY = height / val.length;
    offsetYFactor = height / val.length;
  } else {
    maxY = height;
    offsetYFactor = 0;
  }
}

float getY(float val, float maxY) {
  return val / 1023.0f * maxY;
}

void diffChannels(int resIdx, int c0Idx, int c1Idx) {
  for (int i = width - 1; i >= 0; i--) {
    values[resIdx][i] = values[c0Idx][i] - values[c1Idx][i];
  }
}

void draw() {
  while (port.available () >= 4) {
    int h0 = port.read() & 0xFF;

    if (h0 == 0xA5) {
      int h1 = port.read() & 0xFF;
      int mask = h1 & 0xF8;

      if (mask == 0xA8) {
        int idx = (h1 & 0x07) & 0xFF;

        int v0 = ((port.read() & 0xFF) << 8) & 0xFF00;
        int v1 = ((port.read() & 0xFF) << 0) & 0x00FF;
        if (idx < val.length) {
          val[idx] = v0 | v1;
        }
      }
    }
  }

  for (int c = 0; c < val.length; c++) {
    for (int i = width - 1; i > 0; i--) {
      values[c][i] = values[c][i - 1];
    }
    values[c][0] = val[c];
  }

  //// Diff 2 channels and output on a 3rd channel
  // diffChannels(val.length - 1, 0, 1);

  background(0);

  for (int c = 0; c < val.length; c++) {
    stroke(ccolor[c % ccolor.length]);
    float offsetY = offsetYFactor * c;
    for (int x = 0; x < width - 1; x++) {
      line(
        x + 0, height - getY(values[c][x + 0], maxY) - offsetY - 1,
        x + 1, height - getY(values[c][x + 1], maxY) - offsetY - 1
        );
    }
  }
}
