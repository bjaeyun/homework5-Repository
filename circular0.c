/**
 * circularQ.c
 *
 * School of Computer Science,
 * Chungbuk National University
 */

#include <stdio.h>
#include <stdlib.h>

#define MAX_QUEUE_SIZE 4 //MAX_QUEUE의 최대 크기를 4로 정의

typedef char element; //char로 데이터 타입을 정의
typedef struct
{
    element queue[MAX_QUEUE_SIZE]; //큐의 배열
    int front, rear; //front, rear를 int형 선언
} QueueType;

QueueType *createQueue(); // Circular Queue를 동적 할당하여 생성하는 함수
int freeQueue(QueueType *cQ); // Circular Queue를 해제하는 함수 
int isEmpty(QueueType *cQ);// Circular Queue가 비어있는지 검사하는 함수
int isFull(QueueType *cQ); // Circular Queue가 가득찼는지 검사하는 함수
void enQueue(QueueType *cQ, element item); // Circular Queue에 요소를 삽입하는 함수
void deQueue(QueueType *cQ, element *item); // Circular Queue에서 요소를 삭제하는 함수
void printQ(QueueType *cQ); // Circular Queue를 출력하는 함수
void debugQ(QueueType *cQ); //Circular Queue의 내용과 front, rear값을 출력하는 디버그 함수
element getElement(); // 표준 입력으로부터 요소를 입력받는 함수

int main(void)
{
    QueueType *cQ = createQueue(); //큐 생성
    element data; //입력받은 element저장하는 변수

    char command; //사용자 입력 명령 저장하는 변수

    do
    {
        printf("\n------------[2022041046] [변재윤]---------------------\n");
        printf("                     Circular Q                   \n");
        printf("------------------------------------------------------\n");
        printf(" Insert=i,  Delete=d,   PrintQ=p,   Debug=b,   Quit=q \n");
        printf("------------------------------------------------------\n");

        printf("Command = ");
        scanf(" %c", &command); //사용자로부터 command를 입력받음

        switch (command)
        {
        case 'i': //command가 i 또는 I일때
        case 'I':
            data = getElement(); //사용자로부터 element입력받음
            enQueue(cQ, data); //큐에 element 차가
            break;
        case 'd': //command가 d 또는 D일때
        case 'D':
            deQueue(cQ, &data); // 큐에서 element 삭제하고 그 값을 data에 저장
            break;
        case 'p': //command가 p or P일때
        case 'P':
            printQ(cQ); // 큐의 모든 데이터 출력
            break;
        case 'b':  //command가 b or B일때
        case 'B':
            debugQ(cQ);  // 디버그용 정보 출력
            break;
        case 'q':  //command가 q or Q일때
        case 'Q':
            break;
        default: //command를 잘못 입력했을때
            printf("\n       >>>>>   Concentration!!   <<<<<     \n");
            break;
        }

    } while (command != 'q' && command != 'Q'); 
  freeQueue(cQ);
    return 1; //1 반환
}

QueueType *createQueue() {//새로운 큐 생성 함수
    QueueType *cQ; 
    cQ = (QueueType *)malloc(sizeof(QueueType)); //Queue Type 크기만큼 동적 메모리 할당
    cQ->front = 0; //front값 초기화
    cQ->rear = 0; //rear값 초기화
    return cQ; //cQ 반환
}

int freeQueue(QueueType *cQ)// Circular Queue를 해제하는 함수
{
    if (cQ == NULL) //cQ가 NULL이라면
        return 1; //1을 반환
    free(cQ); //cQ가 비어있지 않을 때 동적 메모리 해제
    return 1; //1 반환
}

element getElement() //요소를 입력 받는 함수
{
    element item; //입력 받을 요소
    printf("Input element = ");
    scanf(" %c", &item);
    return item; //item 반환
}

int isEmpty(QueueType *cQ) //큐가 비어있는지 확인하는 함수
{
    if (cQ->front == cQ->rear) //만약 큐가 비어있을 때
    {
        printf("Circular Queue is empty!"); //출력
        return 1; //1 반환
    }
    else //아니라면
        return 0; //0 반환
}

int isFull(QueueType *cQ) //큐가 가득 찼는지 확인하는 함수
{
    if (((cQ->rear + 1) % MAX_QUEUE_SIZE) == cQ->front) //큐가 가득 찼을 때
    {
        printf(" Circular Queue is full!"); //출력
        return 1; //1 반환(가득 참)
    }
    else
        return 0; //0 반환(가득 차지 않음)
}

void enQueue(QueueType *cQ, element item) //큐에 요소를 추가하는 함수
{
    if (isFull(cQ)) ///큐가 가득 찼다면
        return; //종료
    else //아니면
    {
        cQ->rear = (cQ->rear + 1) % MAX_QUEUE_SIZE; //rear 값을 1증가시키고
        cQ->queue[cQ->rear] = item; //새로운 요소를 rear위치에 추가
    }
}

void deQueue(QueueType *cQ, element *item) //큐에서 요소를 제거하는 함수
{
    if (isEmpty(cQ)) //큐가 비어있다면
        return;//종료
    else //아니면
    {
        cQ->front = (cQ->front + 1) % MAX_QUEUE_SIZE; //rear값을 중가시키며 새로운 위치 지정
        *item = cQ->queue[cQ->front]; //지정된 위치에 새로운 요소 추가
        return;
    }
}

void printQ(QueueType *cQ) //큐의 내용을 출력하는 함수
{
    int i, first, last;

    first = (cQ->front + 1) % MAX_QUEUE_SIZE; //요소가 시작하는 위치
    last = (cQ->rear + 1) % MAX_QUEUE_SIZE; //요소가 끝나는 위치

    printf("Circular Queue : [");

    i = first;// i에 first값 
    while (i != last) //first부터 last까지 큐 출력
    {
        printf("%3c", cQ->queue[i]);
        i = (i + 1) % MAX_QUEUE_SIZE;
    }
    printf(" ]\n");
}

void debugQ(QueueType *cQ) //큐의 내부 상태를 출력하는 디버그 함수
{

    printf("\n---DEBUG\n");
    for (int i = 0; i < MAX_QUEUE_SIZE; i++)
    {
        if (i == cQ->front) //i가 큐의 front와 같다면
        {
            printf("  [%d] = front\n", i); //front의 위치 출력
            continue; //다음 인덱스 탐색
        }
        printf("  [%d] = %c\n", i, cQ->queue[i]); //
    }
    // printQ(cQ);
    printf("front = %d, rear = %d\n", cQ->front, cQ->rear); //front, rear 값 출력
}
