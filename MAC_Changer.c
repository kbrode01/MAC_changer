/* MAC_changer.c 
Program to change MAC address written in C
Last Update: 2/22/2025
*/

#define _GNU_SOURCE //enables GNU 
#include <stdio.h> //input output
#include <unistd.h>//process control, low-level I/O
#include <string.h> //string functionality
#include <stdlib.h> //memory management, conversions, srand()
#include <assert.h> //Checking assumptions during dev
#include <errno.h> //error handling

//storage variables
typedef unsigned char int8;
typedef unsigned short int int16;
typedef unsigned int int32;
typedef unsigned long int int64;

//struct for holding mac addresses
struct s_mac{
	//occupy 48/64 assigned bits since mac addressis 48 bits
	int64 addr:48;
};
typedef struct s_mac Mac; //just renaming 

Mac generatemac(void);//generate random mac address to be changed
int main(int,char**); //typically int argc (argument count) and char *argv[] (argument vector)

Mac generatemac(){
	int64 a, b;
	Mac mac;
	
	a = (long)random();
	b = (long)random();
	mac.addr = ((a * b) % 281474976710656);//max val 48 bit mac address 
	
	return mac;
}

int main(int argc, char *argv[]){
	srand((unsigned int)getpid()); //random seeding with current process id from <unistd.h> lib typecast to make sure of type match
	char cmd[100];
    snprintf(cmd, sizeof(cmd), "sudo ip link set dev eth0 address %02X:%02X:%02X:%02X:%02X:%02X",
             (unsigned char)(mac.addr >> 40), (unsigned char)(mac.addr >> 32),
             (unsigned char)(mac.addr >> 24), (unsigned char)(mac.addr >> 16),
             (unsigned char)(mac.addr >> 8), (unsigned char)mac.addr);
    printf("Executing: %s\n", cmd);
    system(cmd); // Requires sudo privileges
	
	
	
	return 0;
}


