#include "../includes/ft_nmap.h"

void *test(void *arg)
{
	int a = *(int*)arg;
	printf("thread: %d\n", a);
	free(arg);
	return NULL;
}

int	thread_creator(struct nmap_luggage *l)
{
	threadrec_t thread[l->speedup];
	int	i;
	int *arg;

	i = 0;
	while (i < l->speedup)
	{
		arg = malloc(sizeof(*arg));

		*arg = i;
		pthread_create(&thread[i++].thread, NULL, test, arg);
		thread->avaiable = false;
		// usleep(10);
		// free(arg);
	}

	// pthread_create(&thread[i], NULL, test, NULL);
	i = 0;
	while (i < l->speedup)
		pthread_join(thread[i++].thread, NULL);

	return EXIT_SUCCESS;
}