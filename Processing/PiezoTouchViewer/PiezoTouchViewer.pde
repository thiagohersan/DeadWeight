import processing.serial.*;

Serial port;
int[] val = new int[2];
int[][] values = new int[2][];

void setup() {
  size(1280, 600);
  println(Serial.list());
  port = new Serial(this, Serial.list()[2], 57600);

  for (int c = 0; c < 2; c++) {
    values[c] = new int[width];
  }

  smooth();
}

int getY(int val) {
  return (int)(val / 1023.0f * height) - 1;
}

void draw() {
  while (port.available () >= 4) {
    int h0 = port.read() & 0xff;

    if (h0 == 0xbe) {
      int h1 = port.read() & 0xff;

      if (h1 == 0xef || h1 == 0xad) {
        int v0 = ((port.read() & 0xff) << 8) & 0xff00;
        int v1 = ((port.read() & 0xff) << 0) & 0x00ff;
        val[(h1 == 0xef) ? 0 : 1] = v0 | v1;
      }
    }
  }

  for (int c = 0; c < 2; c++) {
    for (int i = 0; i < width - 1; i++) {
      values[c][i] = values[c][i + 1];
    }
    values[c][width - 1] = val[c];
  }


  background(0);

  stroke(255);
  for (int c = 0; c < 2; c++) {
    for (int x = 1; x < width; x++) {
      line(width - x, height - 1 - getY(values[c][x - 1]), 
        width - 1 - x, height - 1 - getY(values[c][x]));
    }
    stroke(255, 0, 255);
  }
}
