U8G2 library (csrc) by https://github.com/olikraus/u8g2 ported to MikroC ARM compiler. 

This is an experimental port for that compiler. Some of the files have been modified to
allow the compiler to *at least* successfully compile the library. However, there is one
last compile error that is not currently known.

Here is a list of modifications:
1.) The 'data' variable in this library is a 'data' keyword in MikroC. It is replaced with _data.
2.) The 'rx' variable in this library is another keyword in MikroC. Again, replaced with _rx.
3.) Ordering of local variable assignment has been altered to allow successful compilation. Example:

"u8g2_font_draw_glyph" (MikroC):
```
const uint8_t *glyph_data = u8g2_font_get_glyph_data(u8g2, encoding);
u8g2_uint_t dx = 0;
u8g2->font_decode.target_x = x;
u8g2->font_decode.target_y = y;
```

"u8g2_font_draw_glyph" (Original):
```
u8g2_uint_t dx = 0;
u8g2->font_decode.target_x = x;
u8g2->font_decode.target_y = y;
const uint8_t *glyph_data = u8g2_font_get_glyph_data(u8g2, encoding);
```

Todo:
1.) Putting 'const' into all the font array, since there's no "attribute" in that compiler. (Or maybe yes?)
