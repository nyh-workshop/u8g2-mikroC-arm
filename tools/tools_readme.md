# u8g2 mikroC ARM - Tools readme

Due to the compiler's differences of how it parses the octals 
in the strings, the tools to generate the fonts arrays must be
modified.

## Installation guide:

1. Download the latest copy of U8G2 and unpack it somewhere,
example: **X:\u8g2-master**. 
If you have this already, it is best you create a separate folder
especially for handling MikroC projects.

2. Copy whatever that is from the **\bdfconv** into that 
**X:\u8g2-master\tools\font\bdfconv** and overwrite those files.

Please see note for more info on that.

3. Then copy whatever that is from the **\build** into 
**X:\u8g2-master\tools\font\build** and overwrite the files.

4. Inside the **X:\u8g2-master\tools\font\build**, open the 
**build.c** and perform this modification to your needs:

Line 1187 - change the X drive to whatever location the u8g2 is:
```
char *bdf_path = "X:\\u8g2-master\\tools\\font\\bdf\\";
char *bdfconv_path = "X:\\u8g2-master\\tools\\font\\bdfconv\\bdfconv.exe";
char *otf2bdf_path = "X:\\u8g2-master\\tools\\font\\otf2bdf\\otf2bdf.exe";
FILE *u8g2_font_list_fp;
FILE *u8x8_font_list_fp;
FILE *keywords_fp;
char *u8g2_prototypes = NULL;
char *u8x8_prototypes = NULL;
char *u8g2_fonts_filename = "X:\\u8g2-master\\csrc\\u8g2_fonts.c";
char *u8x8_fonts_filename = "X:\\u8g2-master\\csrc\\u8x8_fonts.c";
```

Line 2212 - change the X drive to whatever location the u8g2 is:
```
void bdfconv(int i, int fm, char *fms, int bm, char *bms, int mm, char *mms)
{
  
  if ( fi[i].ttf_opt != NULL )
  {
    strcpy(otf_cmd, otf2bdf_path);
    strcat(otf_cmd, " ");
    strcat(otf_cmd, fi[i].ttf_opt);
    strcat(otf_cmd, " X:\\u8g2-master\\tools\\font\\ttf\\");
    strcat(otf_cmd, fi[i].filename);
    strcat(otf_cmd, " -o tmp.bdf");
    printf("%s\n", otf_cmd);
    system(otf_cmd);
  }
```
Afterwards ,compile the stuff inside (3) by running "**make**".

5. Once it's done, run **build1**. It can go for quite some time there.

6. Done. The **u8g2_fonts.c** are now hex formatted.

## Note:

If you have looked into the "bdf_font.c", there is a modification that
instead of outputting the octal formatted string, it is now changed to hex
formatted string.

Line 633:
```
for( i = 0; i < bf->target_cnt-1+extra1; i++ )
  {
    if ( bf->target_data[i] < 32 || bf->target_data[i] == '\"' || bf->target_data[i] == '\\'  || bf->target_data[i] == '?' || ( bf->target_data[i] >= '0' && bf->target_data[i] <= '9' ))
    {
      //fprintf(out_fp, "\\%o", bf->target_data[i]);
      fprintf(out_fp, "\\x%02x", bf->target_data[i]);
    }
    else if ( bf->target_data[i] < 127 )		/* issue 482, do not output ASCII char 127, instead use octal code for 127 */

```