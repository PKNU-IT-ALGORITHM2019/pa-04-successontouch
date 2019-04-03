#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#pragma warning(disable:4996)
#define MINI_MAX 500
#define MAX 100000
#define SIZE 50


int n = 0;

typedef struct Web
{
	char ip[SIZE];
	char time[SIZE];
	char URL[SIZE];
	char status[SIZE];
}Web;

Web *four;

void read() {
	char buffer[MINI_MAX];
	scanf("%s", buffer);
	FILE *read_fp = fopen(buffer, "r");

	char str[MAX];
	fgets(str, MAX, read_fp);
	while (!feof(read_fp)) {
		fgets(str, MAX, read_fp);

		char *token = strtok(str, ",");
		strcpy(four[n].ip, token);
		token = strtok(NULL, ",[");
		strcpy(four[n].time, token);
		token = strtok(NULL, ",");
		strcpy(four[n].URL, token);
		token = strtok(NULL, ",");
		strcpy(four[n].status, token);
		n++;
	}
	fclose(read_fp);
}
int month_check(char month[])
{
	if (strcmp(month, "Jan") == 0) return 1;
	if (strcmp(month, "Feb") == 0) return 2;
	if (strcmp(month, "Mar") == 0) return 3;
	if (strcmp(month, "Apr") == 0) return 4;
	if (strcmp(month, "May") == 0) return 5;
	if (strcmp(month, "Jun") == 0) return 6;
	if (strcmp(month, "Jul") == 0) return 7;
	if (strcmp(month, "Aug") == 0) return 8;
	if (strcmp(month, "Sep") == 0) return 9;
	if (strcmp(month, "Oct") == 0) return 10;
	if (strcmp(month, "Nov") == 0) return 11;
	if (strcmp(month, "Dec") == 0) return 12;
	return 13;
}
int compare_time(const void *first, const void *second) {
	char a[MAX], b[MAX];
	strcpy(a, ((Web *)first)->time);
	strcpy(b, ((Web *)second)->time);

	char time1[4][MAX];
	char time2[4][MAX];

	char *token_a = strtok(a, "/ ");
	strcpy(time1[0], token_a);		//일
	token_a = strtok(NULL, "/ ");  
	strcpy(time1[1], token_a);		//월
	token_a = strtok(NULL, ": "); 
	strcpy(time1[2], token_a);		//년
	token_a = strtok(NULL, "/ "); 
	strcpy(time1[3], token_a);		//시간

	char *token_b = strtok(b, "/ ");
	strcpy(time2[0], token_b);
	token_b = strtok(NULL, "/ ");
	strcpy(time2[1], token_b);
	token_b = strtok(NULL, ": ");
	strcpy(time2[2], token_b);
	token_b = strtok(NULL, "/ ");
	strcpy(time2[3], token_b);

	int result = strcmp(time1[2], time2[2]);
	if (result != 0)
		return result;

	int day1 = month_check(time1[1]);
	int day2 = month_check(time2[1]);

	result = day1-day2;
	if (result != 0)
		return result;

	result = strcmp(time1[3], time2[3]);
	if (result != 0)
		return result;

}
int compare_ip(const void *first, const void *second) {
	int result = strcmp(((Web*)first)->ip, ((Web*)second)->ip);
	if (result != 0)
		return result;
	return compare_time(first, second);


}
void print() {
	for (int i = 0; i < n; i++) {
		printf("time:%s\n", four[i].time);
		printf("\tURL:%s\n", four[i].URL);
		printf("\tip:%s\n", four[i].ip);
		printf("\tstatus:%s\n", four[i].status);
	}

}
int main()
{
	four = (Web *)malloc(MAX * sizeof(Web));

	char buffer[MINI_MAX];
	char buffer2[MINI_MAX];
	while (1) {
		printf("$ ");
		scanf("%s", buffer);
		if (strcmp(buffer, "read") == 0)
			read();
		else if (strcmp(buffer, "sort") == 0) {
			scanf("%s", buffer2);

			if (strcmp(buffer2, "-t") == 0) {
				qsort(four, n, sizeof(Web), compare_time);
			}
			else if (strcmp(buffer2, "-ip") == 0) {
				qsort(four, n, sizeof(Web), compare_ip);
			}
			else
				continue;
		}
		else if (strcmp(buffer, "print") == 0)
			print();
	}
}