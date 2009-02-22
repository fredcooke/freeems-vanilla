/* FreeEMS - the open source engine management system
 *
 * Copyright 2009 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


#include <stdio.h>


/* Special byte definitions */
#define ESCAPE_BYTE	0xBB
#define START_BYTE	0xAA
#define STOP_BYTE	0xCC
#define ESCAPED_ESCAPE_BYTE		0x44
#define ESCAPED_START_BYTE		0x55
#define ESCAPED_STOP_BYTE		0x33


/* TODO split into functions? */
int main( int argc, char *argv[] ){
	if(argc == 1){
		puts("No argument supplied!! Please supply a file to parse.");
	}else if(argc == 2){
		FILE *inputFile;
		inputFile = fopen(argv[1], "rb");

		/* Could not open file */
		if(inputFile == NULL){
			printf("Error opening file %s, please check the name and try again!\n", argv[1]);
			return 1;
		}

		fseek(inputFile, 0L, SEEK_END);
		int length = ftell(inputFile);
		rewind(inputFile);
		printf("The length of file %s is %u\n\n", argv[1], length);
		printf("Attempting to parse file...\n");

		/* Statistic collection variables */
		unsigned int packets = 0;
		unsigned int charsDropped = 0;
		unsigned int badChecksums = 0;
		unsigned int startsInsidePacket = 0;
		unsigned int currentPacketLength = 0;
		unsigned int escapePairMismatches = 0;
		unsigned int escapeBytesFound = 0;

		/* Loop and state variables */
		unsigned char insidePacket = 0;
		unsigned char unescapeNext = 0;
		unsigned int processed = 0;
		unsigned char checksum = 0;
		unsigned char lastChar = 0;

		/* Iterate through the file char at a time */
		while(processed < length){
			processed++;
			unsigned char character = fgetc(inputFile);

			/* Look for a start byte to indicate a new packet */
			if(character == START_BYTE){
				/* If we are had already found a start byte */
				if(insidePacket){
					/* Increment the counter */
					startsInsidePacket++;
				}
				/* Reset to us using it unless someone else was */
				insidePacket = 1;

			}else if(insidePacket){
				if(unescapeNext){
					/* Clear escaped byte next flag */
					unescapeNext = 0;

					if(character == ESCAPED_ESCAPE_BYTE){
						/* Store and checksum escape byte */
						checksum += character;
					}else if(character == ESCAPED_START_BYTE){
						/* Store and checksum start byte */
						checksum += character;
					}else if(character == ESCAPED_STOP_BYTE){
						/* Store and checksum stop byte */
						checksum += character;
					}else{
						/* Otherwise reset and record as data is bad */
						insidePacket = 0;
						escapePairMismatches++;
					}
				}else if(character == ESCAPE_BYTE){
					/* Set flag to indicate that the next byte should be un-escaped. */
					unescapeNext = 1;
					escapeBytesFound++;
				}else if(character == STOP_BYTE){
					/* Clear the in packet flag */
					insidePacket = 0;

					/* Bring the checksum back to where it should be */
					unsigned char RXReceivedChecksum = (unsigned char)*(RXBufferCurrentPosition - 1);
					checksum -= lastChar;

					/* Check that the checksum matches */
					if(checksum == lastChar){
						/* If it's OK set process flag */
						packets++;
					}else{
						badChecksums++;
					}
				}else{
					/* If it isn't special checksum it! */
					checksum += character;
					lastChar = character;
				}
			}else{
				/* Do nothing : drop the byte */
				charsDropped++;
			}
		}

		printf("There were %u chars dropped and %u packets of which %u had bad checksums.\n", charsDropped, packets, badChecksums);
	}else{
		/* Subtract one to eliminate command name. */
		printf("Wrong number of arguments!! Was %u should be 1...\n", argc - 1);
	}
	return 0; // non-zero = error
}
