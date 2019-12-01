# U8G2 library (csrc) by https://github.com/olikraus/u8g2 ported to MikroC ARM compiler. 

This is an experimental port for that compiler. Some of the files have been modified to
allow the compiler to *at least* successfully compile the library. 

Here is a list of modifications:
1. The 'data' variable in this library is a 'data' keyword in MikroC. It is replaced with _data.
2. The 'rx' variable in this library is another keyword in MikroC. Again, replaced with _rx.
3. Ordering of local variable assignment has been altered to allow successful compilation. Example:

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

Issues:
1. It seems that MikroC compiler doesn't want to read octal numbers in strings
properly. Example, when the string is "\123", the compiler reads it as "1" and "23",
causing the write string functions to immediately fail.

Temporarily, a modification in the bdfconv must be done to convert the bdf into
hex format in these strings for them to work properly. (***check the Tools section!***) 

This has been fixed using the modified tools supplied.

2. Unfortunately, the compiler could not compile that very large "**u8g2_fonts.c**" and
usually end up crashing or with compile errors. You may have to make an empty 
**u8g2_fonts.c** in your project folder, copy whatever font you like there from the main 
folder of the generated font array (please check **tools_readme.md** to do this) and paste
it inside your own **u8g2_fonts.c**.

## Tools
For more info on the tools, the **tools_readme.md** is there in the **\tools** folder.
