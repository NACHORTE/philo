#include "philo.h"

pthread_mutex_t mute;
int a;
void	*prueba(void *unused)
{
	//pthread_mutex_lock(&mute);
	a++;
	printf("Terminado.\n");
	//pthread_mutex_unlock(&mute);
}

int main(void)
{
	
	pthread_t	hilo1, hilo2;

	a = 0;
	pthread_mutex_init(&mute, NULL);
	pthread_create(&hilo1, NULL, prueba, NULL);
	pthread_create(&hilo2, NULL, prueba, NULL);
	pthread_join(hilo1, NULL);
	pthread_join(hilo2, NULL);
	printf("%d \n", a);
}