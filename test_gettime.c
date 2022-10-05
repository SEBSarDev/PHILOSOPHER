# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

time_t	dif_actu_last(struct timeval *last, struct timeval *actu)
{
	time_t dif_sec;
	suseconds_t add_micro;
	time_t res;
	
	res = 0;
	if (actu->tv_sec > last->tv_sec)
	{
		dif_sec = (actu->tv_sec - last->tv_sec) - 1; 
		dif_sec = dif_sec * 1000;
		add_micro = actu->tv_usec + (1000000 - last->tv_usec);
		add_micro = add_micro / 1000;
		res = dif_sec + add_micro;
	}
	else
	{
		add_micro = actu->tv_usec -  last->tv_usec;
		add_micro = add_micro / 1000;
		res = add_micro;
	}
	return (res);
}

int main()
{
	struct timeval last;
	struct timeval actu;
	time_t res;

	gettimeofday(&last, NULL);
	usleep(8000);
	gettimeofday(&actu, NULL);
	res = dif_actu_last(&last, &actu);
	printf("1 sec = %ld\nmicrosec = %ld\n", last.tv_sec, last.tv_usec);
	printf("2 sec = %ld\nmicrosec = %ld\n", actu.tv_sec, actu.tv_usec);
	printf("res = %ld\n", res);
}
