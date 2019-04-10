__kernel void test(__global float *in, __global float *out) {
    size_t i = get_global_id(0);
    out[i] = in[i] * in[i] * in[i];
}
