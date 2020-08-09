struct colors {
  int a = 255;
  int r = 0;
  int g = 0;
  int b = 0;
  color_t final = color_from_argb(a, r, g, b);
  colors(int q, int c, int d, int l) : a(q), r(c), g(d), b(l) { }
  colors(int c, int d, int l) : r(c), g(d), b(l) { }
  colors() { }
};

colors fadeColors(colors c1, colors c2, float mix)
{
  //mix:  color 1 0.0 <--> 1.0 color 2
  colors result;
  result.r = c1.r*(1-mix) + c2.r*(mix);
  result.g = c1.g*(1-mix) + c2.g*(mix);
  result.b = c1.b*(1-mix) + c2.b*(mix);
  return result;
}