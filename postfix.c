/* postfix.c
 *
 *  Data Structures, Homework #5
 *  Department of Computer Science at Chungbuk National University
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>


#define MAX_STACK_SIZE 10   
#define MAX_EXPRESSION_SIZE 20   

 /* stack 내에서 우선순위, lparen = 0 가장 낮음 */
typedef enum {
   lparen = 0,  /* ( 왼쪽 괄호 */
   rparen = 9,  /* ) 오른쪽 괄호*/
   times = 7,   /* * 곱셈 */
   divide = 7,  /* / 나눗셈 */
   plus = 5,    /* + 덧셈 */
   minus = 5,   /* - 뺄셈 */
   operand = 1 /* 피연산자 */
} precedence;


char infixExp[MAX_EXPRESSION_SIZE];
char postfixExp[MAX_EXPRESSION_SIZE];
char postfixStack[MAX_STACK_SIZE];
int evalStack[MAX_STACK_SIZE];

int postfixStackTop = -1;
int evalStackTop = -1;

int evalResult = 0;


void postfixpush(char x); //postfix에 x를 push하는 함수
char postfixPop(); //postfix를 pop하는 함수
void evalPush(int x); //수식의 값을 계산하는 과정에서 사용되는 스택에 정수 x를 push하는 함수
int evalPop(); //정수를 pop하는 함수
void getInfix(); //중위 표기법으로 된 수식을 읽어와 후위 표기법으로 변환하는 함수
precedence getToken(char symbol); //symbol에 대해 해당 연산자의 우선순위 반환
precedence getPriority(char x); //연산자의 우선순위를 반환하는 함수
void charCat(char* c); //문자열 c에 문자를 추가하는 함수
void toPostfix(); // 수식을 변환하는 함수
void debug(); //현재 상태를 출력하는 함수
void reset(); //초기 상태로 되돌리는 함수
void evaluation(); //수식을 계산하는 함수


int main()
{
   
   int count = 0;   //추가
   char command;

   do {
      printf("----------------------[변재윤] [2022041046]-------------------\n");
      printf("               Infix to Postfix, then Evaluation               \n");
      printf("----------------------------------------------------------------\n");
      printf(" Infix=i,   Postfix=p,  Eval=e,   Debug=d,   Reset=r,   Quit=q \n");
      printf("----------------------------------------------------------------\n");

      printf("Command = ");
      scanf(" %c", &command);

      switch (command) {
      case 'i': //command가 i 또는 I일때
      case 'I':
         getInfix();
         count++;
         break;
      case 'p': //command가 p or P일때
      case 'P':
         if (count == 0)  
         {
            printf("Infix first!\n");
            continue;
         }
         toPostfix();
         break;
      case 'e':  //command가 e or E일때
      case 'E':
         if (count == 0)   
         {
            printf("Infix first!\n");
            continue;
         }
         evaluation();
         break;
      case 'd':   //command가 d or D일때
      case 'D':
         debug();
         break;
      case 'r': //command가 r or R일때
      case 'R':
         reset();
         count = 0;
         break;
      case 'q': //command가 q or Q일때
      case 'Q':
         break;
      default:
         printf("\n       >>>>>   Concentration!!   <<<<<     \n");
         break;
      }

   } while (command != 'q' && command != 'Q');

   return 1;
}

void postfixPush(char x) //x를 postfixStack에 push한다
{
   postfixStack[++postfixStackTop] = x;
}

char postfixPop() //postfixStack에서 pop한다
{
   char x;
   if (postfixStackTop == -1)
      return '\0';
   else {
      x = postfixStack[postfixStackTop--];
   }
   return x;
}

void evalPush(int x)//x를 evalStack에 push
{
   evalStack[++evalStackTop] = x;
}

int evalPop() //evalStack에서 pop된 값을 반환
{
   if (evalStackTop == -1)
      return -1;
   else
      return evalStack[evalStackTop--];
}

/**
 * infix expression을 입력받는다.
 * infixExp에는 입력된 값을 저장한다.
 */
void getInfix() //infix를 infixExp에 저장
{
   printf("Type the expression >>> ");
   scanf("%s", infixExp);
}

precedence getToken(char symbol) //symbol에 대해 precedence반환
{
   switch (symbol) {
   case '(': 
   return lparen;
   case ')': 
   return rparen;
   case '+': 
   return plus;
   case '-': 
   return minus;
   case '/': 
   return divide;
   case '*': 
   return times;
   default: 
   return operand;
   }
}

precedence getPriority(char x) //x에 대한 precedence를 반환
{
   return getToken(x);
}

/**
 * 문자하나를 전달받아, postfixExp에 추가
 */
void charCat(char* c) //postfixExp를 문자 'c'를 추가
{
   if (postfixExp == '\0')
      strncpy(postfixExp, c, 1);
   else
      strncat(postfixExp, c, 1);
}

/**
 * infixExp의 문자를 하나씩 읽어가면서 stack을 이용하여 postfix로 변경한다.
 * 변경된 postfix는 postFixExp에 저장된다.
 */
void toPostfix() //infixExp를 postfix로 변경하여 postfixExp에 저장
{
   char* exp = infixExp;
   char x;

   /* exp를 증가시켜가면서, 문자를 읽고 postfix로 변경 */
   while (*exp != '\0')
   {
      if (getPriority(*exp) == operand) // 연산자가 아니라면
      {
         x = *exp;
         charCat(&x); // 피연산자를 postfixExp에 추가
      }

      else if (getPriority(*exp) == lparen)  // 왼쪽 괄호라면
      {
         postfixPush(*exp); // 스택에 푸시
      }

      else if (getPriority(*exp) == rparen) // 오른쪽 괄호라면
      {

         while ((x = postfixPop()) != '(') // 왼쪽 괄호를 만날 때까지
         {
            charCat(&x); // 스택에서 팝하면서 postfixExp에 추가
         }
      }

      else // 연산자라면
      {

         while (getPriority(postfixStack[postfixStackTop]) >= getPriority(*exp))
         // 현재 연산자보다 우선순위가 높은 스택의 연산자를 팝하면서
         {
            x = postfixPop();
            charCat(&x); // 스택에서 팝하면서 postfixExp에 추가
         }
         postfixPush(*exp); // 현재 연산자를 스택에 푸시
      }

      exp++; // infixExp 포인터 증가
   }


   while (postfixStackTop != -1) // 스택에 남은 연산자를 모두 팝하면서 postfixExp에 추가
   {
      x = postfixPop();
      charCat(&x);
   }
}

//infixExp,postfixExp,eavl result,postfixStack 출력하는 함수
void debug() //infixExp, postfixExp, evalResult, postfixStack 값을 출력
{
   printf("\n---DEBUG\n");
   printf("infixExp =  %s\n", infixExp);
   printf("postExp =  %s\n", postfixExp);
   printf("eval result = %d\n", evalResult);

   printf("postfixStack : ");
   for (int i = 0; i < MAX_STACK_SIZE; i++)
   {
      printf("%c  ", postfixStack[i]);
   }

   printf("\n");
}


void reset() //infixExp, postfixExp, postfixStack, evalStack 등을 초기화
{
   infixExp[0] = '\0';
   postfixExp[0] = '\0';

   for (int i = 0; i < MAX_STACK_SIZE; i++)
   {
      postfixStack[i] = '\0';
   }

   postfixStackTop = -1;
   evalStackTop = -1;
   evalResult = 0;
}


void evaluation() //postfixExp를 계산하여 결과를 evalResult에 저장
{
   int opr1, opr2, i;

   int length = strlen(postfixExp); // postfixExp의 길이
   char symbol; 
   evalStackTop = -1; // evaluation 스택의 탑을 초기화

   for (i = 0; i < length; i++) // postfixExp를 처음부터 끝까지 탐색
   {
      symbol = postfixExp[i];
      if (getToken(symbol) == operand) //현재 심볼이 피연산자인 경우
      {
         evalPush(symbol - '0'); // 해당 피연산자를 스택에 푸시
      }

      else
      {

         opr2 = evalPop(); // 스택에서 피연산자2를 팝
         opr1 = evalPop();  // 스택에서 피연산자1을 팝

         switch (symbol)
         {
         case '+': 
         evalPush(opr1 + opr2);
         break;
         case '-': 
         evalPush(opr1 - opr2); 
         break;
         case '*': 
         evalPush(opr1 * opr2); 
         break;
         case '/': 
         evalPush(opr1 / opr2); 
         break;
         default: 
         break;
         }
      }
   }


   evalResult = evalPop();
}