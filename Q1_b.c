#include<pthread.h>
#include<unistd.h>
#include<semaphore.h>
#include<stdio.h>
sem_t forks[5];
sem_t bowl1, bowl2;
void* func(void *num){
    int philo_num = *(int*)num;
    int a = 0, b = 0;
    printf("Philosopher %d Thinking\n", philo_num);
    while(1){
        if(sem_trywait(&bowl1)==0){
            printf("Philosopher %d choose Bowl 1\n", philo_num);
            a = 1;
            break;
        }
        if(sem_trywait(&bowl2)==0){
            printf("Philosopher %d choose Bowl 2\n", philo_num);
            b = 1;
            break;
        }
    }
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
    if(a==1){
        sem_post(&bowl1);
        printf("Philosopher %d puts down Bowl 1\n", philo_num);
    }else{
        sem_post(&bowl2);
        printf("Philosopher %d puth down Bowl 2\n", philo_num);
    }
}
int main(){
    int philo_num[] = {1, 2, 3, 4, 5};
    pthread_t id[5];
    for(int i = 0; i<5; i++){
        sem_init(&forks[i], 0, 1);
    }
    sem_init(&bowl1, 0, 1);
    sem_init(&bowl2, 0, 1);
    for(int i = 0; i<5; i++){
        pthread_create(&id[i], NULL, &func, &philo_num[i]);
    }
    for(int i = 0; i<5; i++){
        pthread_join(id[i], NULL);
    }
}
