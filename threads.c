#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

// IMPORTANT: <phtread.h> is only (?) available on unix systems...
// Program for testing threads and joining them.
void* myTurn(void * arg){
	/* while(1){ */
	for(int i = 0; i < 8; i++){
		sleep(1);
		printf("My turn! %d\n", i);
	}
	return NULL;
}

// 
void yourTurn(){
	/* while(1){ */
	for(int i = 0; i < 3; i++){
		sleep(2);
		printf("Your turn! %d\n", i);
	}
}

int main(){
	pthread_t newThread;
	pthread_create(&newThread, NULL, myTurn, NULL);
	//myTurn();
	yourTurn();
	// Wait until the thread is done
	pthread_join(&newThread, NULL);
}
