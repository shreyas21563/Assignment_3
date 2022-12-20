#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdio.h>
sem_t forks[5];
void* func(void *num){
    int philo_num = *(int*)num;
    printf("Philosopher %d Thinking\n", philo_num);
    if(philo_num==4){
        sem_wait(&forks[(philo_num+1)%5]);
        printf("Philosopher %d picks Left Fork\n", philo_num);
        sleep(1);
        sem_wait(&forks[philo_num%5]);
        printf("Philosopher %d picks Right Fork\n", philo_num);
        sleep(1);
        printf("Philosopher %d Eating\n", philo_num);
        sem_post(&forks[(philo_num+1)%5]);
        printf("Philosopher %d puts Left Fork\n", philo_num);
        sem_post(&forks[philo_num%5]);
        printf("Philosopher %d puts Right Fork\n", philo_num);
        printf("Philosopher %d Thinking Again\n", philo_num);
    }
    else{
        sem_wait(&forks[philo_num%5]);
        printf("Philosopher %d picks Right Fork\n", philo_num);
        sleep(1);
        sem_wait(&forks[(philo_num+1)%5]);
        printf("Philosopher %d picks Left Fork\n", philo_num);
        sleep(1);
        printf("Philosopher %d Eating\n", philo_num);
        sem_post(&forks[philo_num%5]);
        printf("Philosopher %d puts Right Fork\n", philo_num);
        sem_post(&forks[(philo_num+1)%5]);
        printf("Philosopher %d puts Left Fork\n", philo_num);
        printf("Philosopher %d Thinking Again\n", philo_num);   
    }
}
int main(){
    int philo_num[] = {1, 2, 3, 4, 5};
    pthread_t id[5];
    for(int i = 0; i<5; i++){
        sem_init(&forks[i], 0, 1);
    }
    for(int i = 0; i<5; i++){
        pthread_create(&id[i], NULL, &func, &philo_num[i]);
    }
    for(int i = 0; i<5; i++){
        pthread_join(id[i], NULL);
    }
}
