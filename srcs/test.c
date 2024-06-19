// #include "../include/philo.h"
// //두 스레드
// pthread_t pth1;
// pthread_t pth2;
// //공유자원
// int	src=10;
// //뮤텍스
// pthread_mutex_t m;

// void	*f1(void *arg){
// 	//lock을 걸고 코드영역에
// 	pthread_mutex_init(&m,NULL);
// 	pthread_mutex_lock(&m);
// 	printf("f1 start : \n");
// 	printf("org src : %d\n",src);
// 	//값을 변화시킨다
// 	src = 100;
// 	printf("chg src : %d\n",src);
// 	printf("f1 end : \n");
// 	//unlock을 하지 않는다.
// 	// pthread_mutex_unlock(&m);
// 	return 0;
// }
// void	*f2(void *arg){
// 	//f2는 f1이 lock된 상태임에도 불구하고 잘 동작한다.
// 	printf("f2 start : \n");
// 	printf("org src : %d \n",src);
// 	src = -10;
// 	printf("chg src : %d\n",src);
// 	printf("f2 end : \n");
// 	return 0;
// }
// int main(){
// 	//두 스레드를 생성 
// 	pthread_create(&pth1,NULL,f1,&src);
// 	pthread_create(&pth2,NULL,f2,&src);
// 	//만약 start routine을 f1으로 했다면 f1에서 unlock을 하지 않았다면 무한 대기가 발생한다.
// 	// pthread_create(&pth2,NULL,f1,&src);
// 	//두 스레드를 기다림
// 	pthread_join(pth1,NULL);
// 	pthread_join(pth2,NULL);
// 	//
// 	printf("lat src : %d\n",src);
// }