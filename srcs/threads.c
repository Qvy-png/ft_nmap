#include "../includes/ft_nmap.h"

void *test(void *arg)
{
	int a = *(int*)arg;
	printf("thread: %d\n", a);
	free(arg);
	return NULL;
}

typedef struct {
    struct nmap_luggage *l;
    int start_port;
    int end_port;
    int thread_id;
} thread_data_t;

void *port_scan_thread(void *arg) {
    thread_data_t *data = (thread_data_t *)arg;
    struct nmap_luggage *l = data->l;
    (void)l;
    int thread_id = data->thread_id;
    int start_port = data->start_port;
    int end_port = data->end_port;

    printf("Thread %d: Scanning ports %d to %d\n", thread_id, start_port, end_port);

    for (int i = start_port; i < end_port; i++) {
    //     int port = l->ports_num[i];
    //     int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    //     if (sockfd < 0) {
    //         perror("socket");
    //         continue;
    //     }

    //     struct sockaddr_in serv_addr;
    //     memset(&serv_addr, 0, sizeof(serv_addr));
    //     serv_addr.sin_family = AF_INET;
    //     serv_addr.sin_port = htons(port);
    //     serv_addr.sin_addr.s_addr = inet_addr(l->IP);

    //     // Set timeout for the connection attempt
    //     struct timeval timeout;
    //     timeout.tv_sec = 1;  // 1 second timeout
    //     timeout.tv_usec = 0;
    //     setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &timeout, sizeof(timeout));
    //     setsockopt(sockfd, SOL_SOCKET, SO_SNDTIMEO, &timeout, sizeof(timeout));

    //     if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) == 0) {
    //         printf("Thread %d: Port %d is open\n", thread_id, port);
    //     } else {
    //         printf("Thread %d: Port %d is closed\n", thread_id, port);
    //     }

    //     close(sockfd);
        printf("Thread %d, testing port : %d\n", thread_id, i);
    }

    free(data);
    return NULL;
}


// TODO malloc fail handling
void multithread_scan(struct nmap_luggage *l) {
    if (l->ports_count <= 0) {
        printf("No ports to scan\n");
        return;
    }

    if (l->speedup <= 0) {
        printf("Invalid thread count\n");
        return;
    }

    // Calculate ports per thread
    int ports_per_thread = l->ports_count / l->speedup;
    int remainder = l->ports_count % l->speedup;

    pthread_t *threads = malloc(l->speedup * sizeof(pthread_t));
    if (!threads) {
        perror("malloc for threads");
        return;
    }

    int start_port = 1;
    for (int i = 0; i < l->speedup; i++) {
        int end_port;

        // Distribute remainder ports to first few threads
        if (remainder > 0) {
            end_port = start_port + ports_per_thread + 1;
            remainder--;
        } else {
            end_port = start_port + ports_per_thread;
        }

        // Create thread data
        thread_data_t *data = malloc(sizeof(thread_data_t));
        if (!data) {
            perror("malloc for thread data");
            continue;
        }

        data->l = l;
        data->start_port = start_port;
        data->end_port = end_port;
        data->thread_id = i;

        // Create thread
        if (pthread_create(&threads[i], NULL, port_scan_thread, data) != 0) {
            perror("pthread_create");
            free(data);
            continue;
        }

        start_port = end_port;
    }

    // Wait for all threads to complete
    for (int i = 0; i < l->speedup; i++) {
        pthread_join(threads[i], NULL);
    }

    free(threads);
}


int	thread_creator(struct nmap_luggage *l)
{
    multithread_scan(l);
	// threadrec_t thread[l->speedup];
	// int	i;
	// int *arg;

	// i = 0;
	// while (i < l->speedup)
	// {
	// 	arg = malloc(sizeof(*arg));

	// 	*arg = i;
	// 	pthread_create(&thread[i++].thread, NULL, test, arg);
	// 	thread->avaiable = false;
	// 	// usleep(10);
	// 	// free(arg);
	// }

	// // pthread_create(&thread[i], NULL, test, NULL);
	// i = 0;
	// while (i < l->speedup)
	// 	pthread_join(thread[i++].thread, NULL);

	return EXIT_SUCCESS;
}

// TODO
// number of scans * number of ports = number of threads in ideal world
// if too much threads for the amount of jobs, speedup = nb_of_scan * nb_of_ports
// (nb_of_scans * nb_of_ports)/nb_of_threads = nb_of_jobs_per_threads (Jpt)
// if the number has decimales, give more work to the last thread

// somehow wait for the entire results to be done, to display result properly