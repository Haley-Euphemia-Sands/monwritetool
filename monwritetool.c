#include <stdio.h>
#include <stdlib.h>
// #include <bsd/stdlib.h>
// #include <limits.h>
#include <unistd.h>


#define MB 1024
#define GB 1048576
#define TB 1073741824




int prettify_value(long long int value_in_kb, char drive_dir[7]) {
	fprintf(stderr, "Input: value_in_kb = %lli, drive_dir[7] = %s\n", value_in_kb, drive_dir);
	char output[15];
	if (value_in_kb < MB) {
		sprintf(output, "%lli kB", value_in_kb);
		printf("Lifetime Writes on %s: %s\n", drive_dir, output);
	}
	else if (value_in_kb >= MB && value_in_kb < GB) {
		sprintf(output, "%lli MB", value_in_kb/MB);
		printf("Lifetime Writes on %s: %s\n", drive_dir, output);
	}
	else if (value_in_kb >= GB && value_in_kb < TB) {
		sprintf(output, "%lli GB", value_in_kb/GB);
		printf("Lifetime Writes on %s: %s\n", drive_dir, output);
	}
	else {
		sprintf(output, "%lli TB", value_in_kb/TB);
		printf("Lifetime Writes on %s: %s\n", drive_dir, output);
	}
	return 0;
}

void main() {

	/*-----------------------------------------------------------------------------------*/
	/*-----------------Var Declarations -------------------------------------------------*/
	/*-----------------------------------------------------------------------------------*/
	// const char *errb, *errc, *errd;
	long long int lli_sdb_lifetime_lifetime_writes, lli_sdc_lifetime_lifetime_writes, lli_sdd_lifetime_lifetime_writes;
	// int error=0;
	int errorfd = 1;
	int sdb_size, sdc_size, sdd_size;
	
	
	/*-----------------------------------------------------------------------------------*/
	/*-----------------file descriptor declaration and opening file streams.-------------*/
	/*-----------------------------------------------------------------------------------*/
	
	FILE *fd_sdb_lifetime_writes, *fd_sdc_lifetime_writes, *fd_sdd_lifetime_writes;
	fd_sdb_lifetime_writes = fopen("/sys/fs/ext4/sdb1/lifetime_write_kbytes", "r");
	fd_sdc_lifetime_writes = fopen("/sys/fs/ext4/sdc1/lifetime_write_kbytes", "r");
	fd_sdd_lifetime_writes = fopen("/sys/fs/ext4/sdd1/lifetime_write_kbytes", "r");
	
	fprintf(stderr, "lli_sdb_lifetime_lifetime_writes = %lli, lli_sdc_lifetime_lifetime_writes = %lli, lli_sdd_lifetime_lifetime_writes = %lli\n", lli_sdb_lifetime_lifetime_writes, lli_sdc_lifetime_lifetime_writes, lli_sdd_lifetime_lifetime_writes);
	fprintf(stderr, "sdb_size = %i, sdc_size = %i, sdd_size = %i\n", sdb_size, sdc_size, sdd_size);
	fprintf(stderr, "File Descriptor Pointers: sdb = %i, sdc = %i, sdd = %i\n", fd_sdb_lifetime_writes, fd_sdc_lifetime_writes, fd_sdd_lifetime_writes);
	
	if (fd_sdb_lifetime_writes == NULL){
		fprintf(stderr, "/sys/fs/ext4/sdb1/lifetime_write_kbytes Failed to Open!\n");
		errorfd = 0;
		
	}
	if (fd_sdc_lifetime_writes == NULL){
		fprintf(stderr, "/sys/fs/ext4/sdc1/lifetime_write_kbytes Failed to Open!\n");
		errorfd = 0;
	}
	if (fd_sdd_lifetime_writes == NULL){
		fprintf(stderr, "/sys/fs/ext4/sdd1/lifetime_write_kbytes Failed to Open!\n");
		errorfd = 0;	
	}
	
	
	while (errorfd != 0) {
		fprintf(stderr, "Entered the While Loop\n");
		/*-----------------------------------------------------------------------------------*/			
		/*-----------------Seeking and Reading from File Streams-----------------------------*/
		/*-----------------------------------------------------------------------------------*/

			
		// lifetime writes var file size determination for /dev/sdb1
			
		fseek(fd_sdb_lifetime_writes, 0, SEEK_END);
		sdb_size = ftell(fd_sdb_lifetime_writes);
		fseek(fd_sdb_lifetime_writes, 0, SEEK_SET);
			
		fprintf(stderr, "Point A Reached\n");
		
		// lifetime writes var file size determination for /dev/sdc1
			
		fseek(fd_sdc_lifetime_writes, 0, SEEK_END);
		sdc_size = ftell(fd_sdc_lifetime_writes);
		fseek(fd_sdc_lifetime_writes, 0, SEEK_SET);
			
		fprintf(stderr, "Point B Reached\n");
			
		// lifetime writes var file size determination for /dev/sdd1
			
		fseek(fd_sdd_lifetime_writes, 0, SEEK_END);
		sdd_size = ftell(fd_sdd_lifetime_writes);
		fseek(fd_sdd_lifetime_writes, 0, SEEK_SET);
			
		fprintf(stderr, "Point C Reached\n");
			
		// Allocate chunk of memory for each file
			
		char *sdb_lifetime_writes_content = calloc(sdb_size+1, sizeof(char));
		char *sdc_lifetime_writes_content = calloc(sdc_size+1, sizeof(char));
		char *sdd_lifetime_writes_content = calloc(sdd_size+1, sizeof(char));
			
		fprintf(stderr, "calloc function called\n");
			
		// Reading from virtual file containing the lifetime writes to the devices
			
		fread(sdb_lifetime_writes_content, sizeof(char), sdb_size, fd_sdb_lifetime_writes);
		fread(sdc_lifetime_writes_content, sizeof(char), sdc_size, fd_sdc_lifetime_writes);
		fread(sdd_lifetime_writes_content, sizeof(char), sdd_size, fd_sdd_lifetime_writes);
			
		fprintf(stderr, "3 Files Read\n");
			
			
		// Convert to Int
			
			
		lli_sdb_lifetime_lifetime_writes = strtoll(sdb_lifetime_writes_content, NULL, 10);
		lli_sdc_lifetime_lifetime_writes = strtoll(sdc_lifetime_writes_content, NULL, 10);
		lli_sdd_lifetime_lifetime_writes = strtoll(sdd_lifetime_writes_content, NULL, 10);
		/* if (errb || errc || errd != NULL){
			fprintf(stderr ,"Errors errb:%s errc:%s errd:%s	 Encountered.\n Skipping this instance of loop\n", errb, errc, errd);
			error = 1;
		}*/
			
		fprintf(stderr, "str to lli done: lli_sdb_lifetime_lifetime_writes = %lli, lli_sdc_lifetime_lifetime_writes = %lli, lli_sdd_lifetime_lifetime_writes = %lli\n", lli_sdb_lifetime_lifetime_writes, lli_sdc_lifetime_lifetime_writes, lli_sdd_lifetime_lifetime_writes);
			
		/*-----------------------------------------------------------------------------------*/
		/*---------------- Printing the data to screen --------------------------------------*/
		/*-----------------------------------------------------------------------------------*/
		// if (error !=1) {
		printf("Monitor Lifetime Writes Tool\n--------------------------\n");
		prettify_value(lli_sdb_lifetime_lifetime_writes, "/dev/sdb");
		prettify_value(lli_sdc_lifetime_lifetime_writes, "/dev/sdc");
		prettify_value(lli_sdd_lifetime_lifetime_writes, "/dev/sdd");
		printf("\n\n\n");
		fprintf(stderr, "prettify_value function has been called 3 times\n");
		// }
			
		// Freeing up memory allocation
		free(sdb_lifetime_writes_content);
		free(sdc_lifetime_writes_content);
		free(sdd_lifetime_writes_content);
		
		fprintf(stderr, "free memory allocation\n");
			
		// resetting error flag
		// error = 0; 
			
		sleep(5); //wait 5 seconds before looping
			
		fprintf(stderr, "5 Seconds of Sleep over\n");
	}
	
}	
