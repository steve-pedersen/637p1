/*
** Copyright (C) 2001-2003 Erik de Castro Lopo <erikd@zip.com.au>
**  
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
** 
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
** 
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software 
** Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
*/

#include <iostream>
#include <stdio.h>
#include "sproc.h"
#include "makesine.h"

using std::cin;
using std::cout;
using std::endl;

/* Include this header file to use functions from libsndfile. */
#include    <sndfile.h>

/*    This will be the length of the buffer used to hold.frames while
**    we process them.
*/
#define FORWARD 1
#define INVERSE 0

int     
main (int argc, char *argv[])
{   /* This is a buffer of double precision floating point values
    ** which will hold our data while we process it.
    */
    static double data [BUFFER_LEN] ;
    static double outbuf [BUFFER_LEN] ;

    /* A SNDFILE is very much like a FILE in the Standard C library. The
    ** sf_open function return an SNDFILE* pointer when they sucessfully 
  ** open the specified file.
    */
    SNDFILE      *outfile ;

     /* A pointer to an SF_INFO stutct is passed to sf_open.
    ** On read, the library fills this struct with information about the file.
    ** On write, the struct must be filled in before calling sf_open.
    */ 
    SF_INFO      sfinfo ;
    int          sampleCount, currentTick=0;
    char         *outfilename;
    double frequency, phase;
    int duration;

    /* Here's where we open the input file. We pass sf_open the file name and
    ** a pointer to an SF_INFO struct.
    ** On successful open, sf_open returns a SNDFILE* pointer which is used
    ** for all subsequent operations on that file. 
    ** If an error occurs during sf_open, the function returns a NULL pointer.
  **
  ** If you are trying to open a raw headerless file you will need to set the 
  ** format and channels fields of sfinfo before calling sf_open(). For 
  ** instance to open a raw 16 bit stereo PCM file you would need the following
  ** two lines:
  **  
  **    sfinfo.format   = SF_FORMAT_RAW | SF_FORMAT_PCM_16 ;
  **    sfinfo.channels = 2 ;
    */
    sfinfo.format   = SF_FORMAT_WAV + SF_FORMAT_PCM_16 ;
    sfinfo.channels = 1 ;
    sfinfo.samplerate = SR;

    if (argc < 5) {
      printf("Usage: sprocsine [output soundfile] [frequency in Hz] [initial phase] [duration in ms]\n");
      return 1;
    }

    outfilename = argv[1];

    /* Open the output file. */
    if (! (outfile = sf_open (outfilename, SFM_WRITE, &sfinfo)))
    {   printf ("Not able to open output file %s.\n", outfilename) ;
        puts (sf_strerror (NULL)) ;
        return  1 ;
        } 
    else {
        printf("Opening output soundfile with identical header...\n\n");
    } 
    frequency = atof(argv[2]);
    phase = atof(argv[3]);
    duration = atof(argv[4]);
    cout << "Frequency = " << frequency << "Hz" << " Initial phase = " << phase;
    cout << " Duration = " << duration << " (ms)" << endl; 
    
// construct sine generator
    MakeSine sine(frequency, phase, duration);

// calculate total number of samples, add 1 for ceiling    
    sampleCount = ((int)SR * (duration / 1000)) + 1;   
    while (currentTick < sampleCount)
    {   
        int writeCount = sampleCount - currentTick > BUFFER_LEN ? BUFFER_LEN : sampleCount - currentTick;
        for (int i=0; i<writeCount; i++) {
          outbuf[i] = sine.tick();
        }
        sf_write_double (outfile, outbuf, writeCount) ;

        currentTick += writeCount;
    } ;

    /* Close output file. */
    sf_close (outfile) ;

    return 0 ;
} /* main */
