int numOutputs = 14;
int screenSize = 256;
int pixPerOut = screenSize / numOutputs;

PGraphics pg;
byte[] screenValues;

void setup() {
  size(300, 720);
  frameRate(30);
  background(200);
  pg = createGraphics(width, 1024);
  screenValues = new byte[1024];

  pg.beginDraw();

  for (int i=0; i < pg.height; i++) {
    int nColor = int(noise(i/pixPerOut) * 255.0);
    nColor = ((i/70) % 2) * 255;
    int mColor = nColor < 100 ? 0 : 255;
    pg.stroke(mColor);
    screenValues[i] = byte(mColor & 0xff);
    pg.line(0, i, pg.width, i);
  }
  pg.endDraw();
}

int y0 = 0;
float v0 = 0;
float a0 = 0;
float a_inc = 5;
float a_dec = 1;
float v_dec = 0.93;

void draw() {
  if (a0 >= a_dec) { 
    a0 -= a_dec;
    v0 += a_dec;
  } else {
    a0 = 0;
  }

  v0 *= v_dec;
  y0 = int(y0 + v0) % height;

  background(200);
  image(pg, 0, 0, width, height); 

  drawFrames(y0);
}

void mouseClicked() {
  a0 += a_inc;
}

void drawFrames(int y0) {
  loadPixels();

  for (int i = 0; i < numOutputs; i++) {
    int rectTop = (i * pixPerOut + y0);

    int sum = 0;
    for (int p = 0; p < pixPerOut; p++) {
      int pixelY = (rectTop + p) % height;
      sum += pixels[pixelY * width + 2] & 0xff;
    }

    stroke(0);
    fill(sum / pixPerOut);
    int sqDim = (height / numOutputs);
    rect(width - sqDim - 1, i * sqDim, sqDim, sqDim);

    stroke(0);
    noFill();
    rect(0, rectTop % height, pixPerOut, pixPerOut);
  }
}
