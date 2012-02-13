/* FreeEMS - the open source engine management system
 *
 * Copyright 2009-2012 Fred Cooke
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


#define MAXIMUM_EXPECTED_PACKET_LENGTH 0x0820

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
		printf("Attempting to parse file...\n\n");

		/* Statistic collection variables */
		unsigned int packets = 0;
		unsigned int charsDropped = 0;
		unsigned int badChecksums = 0;
		unsigned int goodChecksums = 0;
		unsigned int startsInsidePacket = 0;
		unsigned int totalFalseStartLost = 0;
		unsigned int doubleStartByteOccurances = 0;
		unsigned int strayDataBytesOccurances = 0;
		unsigned int escapeBytesFound = 0;
		unsigned int escapedStopBytesFound = 0;
		unsigned int escapedStartBytesFound = 0;
		unsigned int escapedEscapeBytesFound = 0;
		unsigned int escapePairMismatches = 0;
		unsigned long sumOfGoodPacketLengths = 0;

		/* Loop and state variables */
		unsigned char insidePacket = 0;
		unsigned char unescapeNext = 0;
		unsigned int processed = 0;
		unsigned char checksum = 0;
		unsigned char lastChar = 0;
		unsigned int currentPacketLength = 0;

		// To store a packet in for purposes of further diagnostics
		unsigned char packetBuffer[MAXIMUM_EXPECTED_PACKET_LENGTH]; // more than sufficient for current FreeEMS increase for other variants.
		unsigned short packetTypeCounts[65536] = {0}; // upto 65535 of each type, then it'll overflow...

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
					if(currentPacketLength == 0){
						doubleStartByteOccurances++;
//						printf("Double start byte occurred following packet number %u\n", packets);
					}else{
						totalFalseStartLost += currentPacketLength; // remember how much we lost
						strayDataBytesOccurances++;
//						printf("Stray data or unfinished packet found following packet number %u\n", packets);
					}
				}
				/* Reset to us using it unless someone else was */
				insidePacket = 1;
				checksum = 0;
				currentPacketLength = 0;

			}else if(insidePacket){
				if(unescapeNext){
					/* Clear escaped byte next flag */
					unescapeNext = 0;

					if(character == ESCAPED_ESCAPE_BYTE){
						/* Store and checksum escape byte */
						checksum += ESCAPE_BYTE;
						lastChar = ESCAPE_BYTE;
						escapedEscapeBytesFound++;
						packetBuffer[currentPacketLength] = ESCAPE_BYTE;
						currentPacketLength++;
					}else if(character == ESCAPED_START_BYTE){
						/* Store and checksum start byte */
						checksum += START_BYTE;
						lastChar = START_BYTE;
						escapedStartBytesFound++;
						packetBuffer[currentPacketLength] = START_BYTE;
						currentPacketLength++;
					}else if(character == ESCAPED_STOP_BYTE){
						/* Store and checksum stop byte */
						checksum += STOP_BYTE;
						lastChar = STOP_BYTE;
						escapedStopBytesFound++;
						packetBuffer[currentPacketLength] = STOP_BYTE;
						currentPacketLength++;
					}else{
						/* Otherwise reset and record as data is bad */
						insidePacket = 0;
						checksum = 0;
						currentPacketLength = 0;
						escapePairMismatches++;
					}
				}else if(character == ESCAPE_BYTE){
					/* Set flag to indicate that the next byte should be un-escaped. */
					unescapeNext = 1;
					escapeBytesFound++;
				}else if(character == STOP_BYTE){
					packets++;

					/* Bring the checksum back to where it should be */
					checksum -= lastChar;

					/* Check that the checksum matches */
					if(checksum != lastChar){
						badChecksums++;
						printf("Packet number %u ending of length %u at char number %u failed checksum! Received %u Calculated %u\n", packets, currentPacketLength, processed, lastChar, checksum);
					}else{
						goodChecksums++;
						/* Add the length to the SUM */
						sumOfGoodPacketLengths += currentPacketLength;

//						printf("Packet number %u ending of length %u at char number %u checked out OK! Received %u Calculated %u\n", packets, currentPacketLength, processed, lastChar, checksum);
						{ // process packet
							// Increment count for packet type that it is
							unsigned short packetType = packetBuffer[1] * 256 + packetBuffer[2];
							packetTypeCounts[packetType]++;
						}
					}
					/* Clear the state */
					insidePacket = 0;
					currentPacketLength= 0;
					checksum = 0;
				}else{
					if (currentPacketLength < MAXIMUM_EXPECTED_PACKET_LENGTH) {
						/* If it isn't special checksum it! */
						checksum += character;
						lastChar = character;
						packetBuffer[currentPacketLength] = character;
						currentPacketLength++;
					}else{
						charsDropped++;
						/* Clear the state */
						insidePacket = 0;
						currentPacketLength= 0;
						checksum = 0;
						// TODO count overlength packets, just print for now:
						printf("Overlength packet found, resetting state!");
					}
				}
			}else{
				/* Do nothing : drop the byte */
				charsDropped++;
			}
		}

		printf("Data stream statistics :\n");

		printf("\nPackets and checksums :\n");
		printf("%u packets were found\n", packets);
		printf("%u had good checksums\n", goodChecksums);
		printf("%u had incorrect checksums\n", badChecksums);

		printf("\nGeneral issues :\n");
		printf("%u leading characters were dropped\n", charsDropped);
		printf("%u false starts occurred\n", startsInsidePacket);
		printf("%u double start bytes occurred\n", doubleStartByteOccurances);
		printf("%u stray part packets occurred\n", strayDataBytesOccurances);
		printf("%u chars lost from false starts \n", totalFalseStartLost);

		printf("\nEscaped byte profile :\n");
		printf("%u escape bytes were found\n", escapeBytesFound);
		printf("%u escaped stop bytes were found\n", escapedStopBytesFound);
		printf("%u escaped start bytes were found\n", escapedStartBytesFound);
		printf("%u escaped escape bytes were found\n", escapedEscapeBytesFound);
		printf("%u escape pairs were mismatched\n", escapePairMismatches);

		printf("\nReport counts for all non-zero packet types\n");
		unsigned long oCount = 0;
		while(oCount < 65536){
			if(packetTypeCounts[oCount] != 0){
				printf("    Packet of type %#.4x / %u was found %u times!\n", oCount, oCount, packetTypeCounts[oCount]);
			}
			oCount++;
		}

		printf("\nGood packet length stats :\n");
		printf("%u total sum of good packet bytes\n", sumOfGoodPacketLengths);
		printf("%u average good packet length (with remainder of %u)\n", (sumOfGoodPacketLengths / goodChecksums), (sumOfGoodPacketLengths % goodChecksums));

	}else{
		/* Subtract one to eliminate command name. */
		printf("Wrong number of arguments!! Was %u should be 1...\n", argc - 1);
	}
	return 0; // non-zero = error
}
