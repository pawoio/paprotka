#include <allegro.h>
#include <stdio.h>
#include <stdbool.h>


void fern(unsigned char * line[], int width, int height,int iter, int p1, int p12, int p123);

int main()

{
	int iterations=5000, p1=85, p2=7, p3=7, p4=1;

	int p12 = p1 + p2;
	int p123 = p1 + p2 + p3;
	
	allegro_init();
	install_keyboard();
	set_color_depth( 24 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 1000, 1000, 0, 0 );

	BITMAP * fernImg = create_bitmap(1000, 1000);

	if( !fernImg)
	{
		set_gfx_mode( GFX_TEXT, 0, 0, 0, 0 );
		allegro_message( "Image error" );
		allegro_exit();
		return 1;
	}
	
	clear_to_color (fernImg, makecol(0,0,0));
	fern(fernImg->line,fernImg->w,fernImg->h,iterations, p1, p12, p123);
	blit(fernImg, screen, 0, 0, 0, 0, fernImg->w, fernImg->h);
	textprintf_ex(screen, font, 40, 15, makecol(255, 255, 255), -1, "Iterations: %d", iterations);
	textprintf_ex(screen, font, 40, 30, makecol(255, 255, 255), -1, "P(1): %d", p1);
	textprintf_ex(screen, font, 40, 45, makecol(255, 255, 255), -1, "P(2): %d", p2);
	textprintf_ex(screen, font, 40, 60, makecol(255, 255, 255), -1, "P(3): %d", p3);
	textprintf_ex(screen, font, 40, 75, makecol(255, 255, 255), -1, "P(4): %d", p4);

	while( !key[ KEY_ESC ] )
	{

		 if(key[KEY_UP])
			{


				if(iterations < 1000)
					iterations*=2;
				else if(iterations <1600)
					iterations+=150;
				else if (iterations < 32000)
					iterations+=1000;
				else iterations+=10000;

				clear_to_color (fernImg,makecol(0,0,0));
				fern(fernImg->line,fernImg->w,fernImg->h,iterations, p1, p12, p123);
				blit(fernImg, screen, 0, 0, 0, 0, fernImg->w, fernImg->h);
				textprintf_ex(screen, font, 40, 15, makecol(255, 255, 255), -1, "Iterations: %d", iterations);
				textprintf_ex(screen, font, 40, 30, makecol(255, 255, 255), -1, "P(1): %d", p1);
				textprintf_ex(screen, font, 40, 45, makecol(255, 255, 255), -1, "P(2): %d", p2);
				textprintf_ex(screen, font, 40, 60, makecol(255, 255, 255), -1, "P(3): %d", p3);
				textprintf_ex(screen, font, 40, 75, makecol(255, 255, 255), -1, "P(4): %d", p4);

			} else if(key[KEY_DOWN])
		 {
			 if(iterations < 1000)
				 iterations/=2;
			 else if(iterations <1600)
				 iterations-=150;
			 else if (iterations < 32000)
				 iterations-=1000;
			 else iterations-=10000;
			 if(iterations==0)
				 iterations=1;

			 clear_to_color (fernImg,makecol(0,0,0));
			 fern(fernImg->line,fernImg->w,fernImg->h,iterations, p1, p12, p123);
			 blit(fernImg, screen, 0, 0, 0, 0, fernImg->w, fernImg->h);
			 textprintf_ex(screen, font, 40, 15, makecol(255, 255, 255), -1, "Iterations: %d", iterations);
			 textprintf_ex(screen, font, 40, 30, makecol(255, 255, 255), -1, "P(1): %d", p1);
			 textprintf_ex(screen, font, 40, 45, makecol(255, 255, 255), -1, "P(2): %d", p2);
			 textprintf_ex(screen, font, 40, 60, makecol(255, 255, 255), -1, "P(3): %d", p3);
			 textprintf_ex(screen, font, 40, 75, makecol(255, 255, 255), -1, "P(4): %d", p4);

		 }

		else if(key[KEY_P]) {

			 while (!key[KEY_ENTER]) {

				 if (key[KEY_DOWN]) {
					 p1 == 0 ? p1 = 0 : (++p4, p1 -= 1);


				 } else if (key[KEY_UP]) {
					 ++p1;
					 p4 == 0 ? (p3 == 0 ? (p2 == 0 ? --p1 : p2--) : --p3) : --p4;
				 }


				 clear_to_color(fernImg, makecol(0, 0, 0));
				 fern(fernImg->line, fernImg->w, fernImg->h, iterations, p1, p12, p123);
				 blit(fernImg, screen, 0, 0, 0, 0, fernImg->w, fernImg->h);
				 textprintf_ex(screen, font, 40, 15, makecol(255, 255, 255), -1, "Iterations: %d", iterations);
				 textprintf_ex(screen, font, 40, 30, makecol(255, 0, 0), -1, "P(1): %d", p1);
				 textprintf_ex(screen, font, 40, 45, makecol(255, 255, 255), -1, "P(2): %d", p2);
				 textprintf_ex(screen, font, 40, 60, makecol(255, 255, 255), -1, "P(3): %d", p3);
				 textprintf_ex(screen, font, 40, 75, makecol(255, 255, 255), -1, "P(4): %d", p4);


				 readkey();
			 }


			 readkey();

			 while (!key[KEY_ENTER]) {

				 if (key[KEY_DOWN]) {
					 p2 == 0 ? p2 = 0 : (++p4, p2 -= 1);


				 } else if (key[KEY_UP]) {
					 ++p2;
					 p4 == 0 ? (p3 == 0 ? --p2 : --p3) : --p4;
				 }


				 clear_to_color(fernImg, makecol(0, 0, 0));
				 fern(fernImg->line, fernImg->w, fernImg->h, iterations, p1, p12, p123);
				 blit(fernImg, screen, 0, 0, 0, 0, fernImg->w, fernImg->h);
				 textprintf_ex(screen, font, 40, 15, makecol(255, 255, 255), -1, "Iterations: %d", iterations);
				 textprintf_ex(screen, font, 40, 30, makecol(255, 255, 255), -1, "P(1): %d", p1);
				 textprintf_ex(screen, font, 40, 45, makecol(255, 0, 0), -1, "P(2): %d", p2);
				 textprintf_ex(screen, font, 40, 60, makecol(255, 255, 255), -1, "P(3): %d", p3);
				 textprintf_ex(screen, font, 40, 75, makecol(255, 255, 255), -1, "P(4): %d", p4);


				 readkey();
			 }


			 readkey();

			 while (!key[KEY_ENTER]) {

				 if (key[KEY_DOWN]) {
					 p3 == 0 ? p3 = 0 : (++p4, p3 -= 1);


				 } else if (key[KEY_UP]) {
					 ++p3;
					 p4 == 0 ? --p3 : --p4;
				 }


				 clear_to_color(fernImg, makecol(0, 0, 0));
				 fern(fernImg->line, fernImg->w, fernImg->h, iterations, p1, p12, p123);
				 blit(fernImg, screen, 0, 0, 0, 0, fernImg->w, fernImg->h);
				 textprintf_ex(screen, font, 40, 15, makecol(255, 255, 255), -1, "Iterations: %d", iterations);
				 textprintf_ex(screen, font, 40, 30, makecol(255, 255, 255), -1, "P(1): %d", p1);
				 textprintf_ex(screen, font, 40, 45, makecol(255, 255, 255), -1, "P(2): %d", p2);
				 textprintf_ex(screen, font, 40, 60, makecol(255, 0, 0), -1, "P(3): %d", p3);
				 textprintf_ex(screen, font, 40, 75, makecol(255, 255, 255), -1, "P(4): %d", p4);


				 readkey();
			 }


			 readkey();
		 }


	}
	destroy_bitmap(fernImg);
	allegro_exit();
	return 0;
}
