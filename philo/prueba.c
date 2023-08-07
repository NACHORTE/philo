#include "philo.h"

pthread_mutex_t mute;
int a;
void	*prueba(void *unused)
{
	pthread_mutex_lock(&mute);
	a++;
	printf("Terminado.\n");
}

void	*destruir(void *unused)
{
	while (1)
	{
		if (a > 0)
		{
			pthread_mutex_destroy(&mute);
			//printf("hola");
		}
	}
}

int main(void)
{
	
	pthread_t	hilo1, hilo2, corte;

	a = 0;
	pthread_mutex_init(&mute, NULL);
	pthread_create(&hilo1, NULL, prueba, NULL);
	pthread_create(&hilo2, NULL, prueba, NULL);
	pthread_create(&corte, NULL, destruir, NULL);
	pthread_join(hilo1, NULL);
	printf("%d \n", a);
	pthread_join(hilo2, NULL);
}