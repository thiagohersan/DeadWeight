import processing.serial.*;

Serial port;
int[] val = new int[5];
int[][] values = new int[5][];
color[] ccolor = {
  color(255, 0, 100),
  color(255, 165, 0),
  color(255, 255, 0),
  color(55, 255, 20),
  color(130, 230, 255)
};

void setup() {
  size(1280, 600);
  frameRate(30);
  println(Serial.list());
  port = new Serial(this, Serial.list()[2], 115200);

  for (int c = 0; c < val.length; c++) {
    values[c] = new int[width];
  }

  smooth();
}

int getY(int val) {
  return (int)(val / 1023.0f * height) - 1;
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
        val[idx] = v0 | v1;
      }
    }
  }

  for (int c = 0; c < val.length; c++) {
    for (int i = 0; i < width - 1; i++) {
      values[c][i] = values[c][i + 1];
    }
    values[c][width - 1] = val[c];
  }


  background(0);

  for (int c = 0; c < val.length; c++) {
    stroke(ccolor[c]);
    for (int x = 1; x < width; x++) {
      line(width - x, height - 1 - getY(values[c][x - 1]), 
        width - 1 - x, height - 1 - getY(values[c][x]));
    }
  }
}
