kernel void getColors(float4 bounds, float2 screenSize, global uchar4* colors) {
    size_t x = get_global_id(0);
    size_t y = get_global_id(1);

    float xpos = bounds.x + (float) x / (float) screenSize.x * (bounds.z - bounds.x);
    float ypos = bounds.y + (float) y / (float) screenSize.y * (bounds.w - bounds.y);

    ypos *= 9.0f / 16.0f;

    size_t index = x + y * (size_t) screenSize.x;

    int numIterations = 0;
    float real = xpos;
    float im = ypos;

    for(; numIterations < 400; numIterations++) {
        float nr = real * real - im * im;
        float ni = 2.0f * real * im;

        real = nr + xpos;
        im = ni + ypos;

        if(real * real + im * im >= 4) break;
    }

    float r = (float) numIterations / 200.0f;
    float g = 0.0f;
    float b = 0.0f;
    float a = 1.0f;

    colors[index] = (uchar4)((uchar) (255.0f * a), (uchar) (255.0f * b), (uchar) (255.0f * g), (uchar) (255.0f * r));
}
