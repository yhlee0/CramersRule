//LeeYH

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define N 5		//행과 열의 최댓값으로 이용(5로 하겠다는 의미)

//함수 선언
double det(double(*A)[N], int n);		//행렬식을 구하는 자기호출함수
void cramer(double(*A)[N], double C[N], int n, int c);	//크래머의 규칙을 이용한 선형방정식 결과 값 계산함수

//main 함수
void main()
{
	int i = 0, j = 0;	//반복을 하기 위한 변수 선언
	int n;				//최대 차수 저장할 변수 선언
	double A[N][N] = { 0, };	//입력받을 행렬의 2차원 배열(방정식), 0으로 초기화
	double C[N] = { 0, };	//입력받을 행렬의 1차원 배열(결과값), 0으로 초기화
	printf("********************************************************\n");
	printf("***                                                  ***\n");
	printf("***  크래머의 규칙을 이용한 선형방정식 계산 프로그램 ***\n");
	printf("***                                                  ***\n");
	printf("********************************************************\n");

	//행렬의 크기 값을 입력
	printf("선형방정식의 최대 차수를 입력하세요: ");
	scanf_s("%d", &n);	//최대 차수를 n에 대입
	printf("\n");

	//선형방정식의 수식을 입력
	printf("선형방정식의 수식을 입력하세요.\n");

	for (i = 0; i < n; i++) {	//A행렬을 입력받아 저장
		for (j = 0; j < n; j++) {
			printf("%d번째 선형방정식 x%d의 값: ", i + 1, j + 1);
			scanf_s("%lf", &A[i][j]);//실수형태로 A행렬에 저장
		}
	}
	printf("\n");

	//선형방정식의 결과 값을 입력
	printf("선형방정식의 결과 값을 입력하세요. \n");

	for (i = 0; i < n; i++) {
		printf("%d 번째 선형방정식의 결과 값: ", i + 1);
		scanf_s("%lf", &C[i]);	//실수형태로 c배열에 대입
	}

	//입력한 행렬 값을 출력
	printf("\n입력한 선형방정식의 행렬 =\n\n");
	for (i = 0; i < n; i++) {	//i를 이용해 최대차수인 n과의 값을 비교해 for문 반복
		printf(" |\t");		//탭
		for (j = 0; j < n; j++)
		{
			printf(" %.f x%d\t", A[i][j], j + 1);	//A[i][j]와 j+1의 값을 순서대로 출력
		}
		printf("=\t");
		printf("%.f\t", C[i]);	//결과값도 순서대로 출력
		printf("|\n");
	}
	printf("\n");

	//입력한 행렬 A(선형방정식)의 행렬식의 값을 출력
	printf("입력한 선형방정식의 행렬식 값\n");
	printf("Det(A)=%.f \n\n", det(A, n));	//A, n을 인자로 하여det()함수 호출. 계산 후 det_a값 반환한 후 출력

	//입력한 행렬 A(선형방정식)에 대한 해답을 출력
	printf("입력한 선형방정식의 해답\n");

	for (i = 1; i < n + 1; i++) {
		cramer(A, C, n, i);
	}
	printf("\n\n");
}

//행렬식 값을 구하는 자기호출함수
double det(double(*A)[N], int n) {

	int i, j, k, y; //루프를 수행하기 위한 변수 선언
	double det_a = 0;	//결과값 저장 변수
	double temp[N][N];	//행렬식 값 임시 저장 배열

	if (n != 1) {	//선형방정식의 최대 차수가 1이 아닌 경우...(1이라면 else구문으로 다르게 처리하기 위함))
		for (i = 0; i < n; i++) {	//최대차수(n)이 될 때까지 반복
			for (j = 1; j < n; j++) {
				y = 0;	//y값 0으로 초기화

				for (k = 0; k < n; k++) {
					if (k != i) {
						temp[j - 1][y++] = *(A[0] + j * N + k);
						//소행렬식(det)을 구하기 위해 각 행렬의 원소들을 재배치
					}
				}
			}
			det_a = det_a + *(A[0] + i) * (pow(-1, i)) * det(temp, n - 1);//재귀함수 호출
			//소행렬식들의 전체합 구함
		}return det_a;		//det_a 값 리턴
	}
	else return *A[0];		//선형방정식의 최대 차수가 1인 경우
}

//크래머의 규칙을 이용한 선형방정식 결과 값 계산합수
void cramer(double(*A)[N], double C[N], int n, int c)
{
	int i = 0, j = 0;	//반복을 위한 변수

	double temp[N][N] = { 0, };	//임시배열 초기화

	//입력받은 행렬A의 값을 임시 배열에 저장
	for (i = 0; i < n; i++) {	//i< 최대차수 n까지 반복
		for (j = 0; j < n; j++)	//j< 최대차수 n까지 반복
		{
			temp[i][j] = A[i][j];	//A행렬 값을 temp행렬의 같은 위치에 저장
		}
	}

	//temp의 각 열에 C의 값을 대입 (temp는 행렬 A의 값을 넘겨받은 배열) 
	for (i = 0; i < n; i++) {
		for (j = c - 1; j < c; j++)	//c는 cramer함수 호출 시의 인자 i값임
		{
			temp[i][j] = C[i];	//temp행렬에 결과값인 c로 대체하여 저장. 크래머 공식의 대표적 과정
		}
	}

	//해답인 x의 값 계산 및 출력
	printf("x%d = %.f\t\t", c, (det(temp, n) / det(A, n)));	//(부분행렬의 행렬식/전체 행렬의 행렬식)

	//x1은 1열을, x2는 2열을, 즉 xi는 i열을 결과값으로 대체하여 행렬식을 구한다음 전체 A행렬의 행렬식 값으로 나눠주어 구함
}