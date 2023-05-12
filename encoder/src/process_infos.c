#include "../include/encoder.h"

/*
 * Prints information about the process received from the Decoder.
 * the information is:
 * uncompressed text, bytes before compression, bytes after compression, decompression time.
 */
void print_process_infos(char *process_infos)
{
	printf("----------- Process infos -----------\n");

	// Decode text.
	printf("Decoded Text:\n%s\n", strchr(strchr(process_infos, ' ') + 1, ' ') + 1);
	printf("-------------------------------------\n");

	// Bits
	printf("Bits BEFORE compression: %li\n", (strlen(strchr(strchr(process_infos, ' ') + 1, ' ') + 1)) * 8);
	printf("Bits AFTER compression:  ");
	int i = 0;
	for (i; process_infos[i] != ' '; i++)
		printf("%c", process_infos[i]);
	printf("\n");
	printf("-------------------------------------\n");

	// Ececution time.
	i++;
	printf("Decode Execution time: ");
	for (i; process_infos[i] != ' '; i++)
		printf("%c", process_infos[i]);
	printf("\n");

	printf("-------------------------------------\n");
}
