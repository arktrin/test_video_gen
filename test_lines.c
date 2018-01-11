#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
 
// Video resolution
#define W 512
#define H 320
 
// Allocate a buffer to store one frame
unsigned char frame[H][W][3] = {0};

#define speed 40
 
void main()
{
    int i, x, y, count;
	bool dir_flag = true; 
	uint8_t color = 2;
	uint16_t n = 400;
     
    // Open an input pipe from ffmpeg and an output pipe to a second instance of ffmpeg
    // FILE *pipein = popen("ffmpeg -i teapot.mp4 -f image2pipe -vcodec rawvideo -pix_fmt rgb24 -", "r");
    FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt bgr24 -s 512x320 -r 30 -i - -f mp4 -q:v 5 -an -vcodec mpeg4 output.mp4", "w");
	// FILE *pipeout = popen("ffmpeg -y -f rawvideo -vcodec rawvideo -pix_fmt bgr24 -s 512x320 -r 30 -i - -pix_fmt bgr24 -an -vcodec copy output.mp4", "w");    
 
    // Process video frames
    for (i=0; i<300; ++i)
    {
        // Read a frame from the input pipe into the buffer
        // count = fread(frame, 1, H*W*3, pipein);
         
        // If we didn't get a frame of video, we're probably at the end
        // if (count != H*W*3) break;
         
        // Process this frame
        for (y=0 ; y<H ; ++y)
		{ 
			for (x=0 ; x<W ; ++x)
        	{
				if (dir_flag)
				{
					if (x<n) 
            		{
						frame[y][x][2] = x % 250; // red
            			frame[y][x][1] = y % 250; // green
            			// frame[y][x][0] // blue
					}
				}
				else
				{
					if (x>n)
					{
                        frame[y][x][color] = 255; // red
                        // frame[y][x][1] // green
                    	// frame[y][x][0] // blue
                    }
				}
	
        	}
        }
		/* if (dir_flag)
		{
			n += speed;
		}
		else
		{
			n -= speed;
		}

		if (( n>500 ) && ( dir_flag )) 
		{
			dir_flag = false;
		}
		else if (( n < 40 ) && !( dir_flag ))
		{
			dir_flag = true;
			if (color > 0) {color -= 1;}
			else {color = 2;}
		}
		*/
        // Write this frame to the output pipe
        fwrite(frame, 1, H*W*3, pipeout);
		memset(frame, 0, sizeof(frame));

    }
     
    // Flush and close input and output pipes
    // fflush(pipein);
    // pclose(pipein);
    fflush(pipeout);
    pclose(pipeout);
}
