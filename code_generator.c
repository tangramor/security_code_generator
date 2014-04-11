#include "sysdep.h"
#include <stdio.h>
#include "uuid.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>

char allowed_chars[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
		'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S',
		'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char allowed_chars2[] = { '2', '3', '4', '5', '6', '7', '9', 'A', 'C', 'D', 'E',
		'F', 'G', 'H', 'J', 'K', 'L', 'P', 'Q', 'R', 'S', 'T', 'U', 'X', 'Y',
		'Z' };

char *p_code(uuid_t u, int length);
char *nodup_code(int total, int length, char *p[total][length]);
void gencode(int total, int length, char *p[total][length]);

size_t printed_length ( int x )
{
    return snprintf ( NULL, 0, "%d", x );
}
;

/* Simple driver for UUID generator */
void main(int argc, char **argv) {
	uuid_t u;

	if(argc < 5 || argc > 6) {
		printf("请输入唯一码长度(大于8)、需要生成的唯一码数量、起始流水号和名称:\nPlease input code length(bigger than 8), the total number of codes, start serial number and csv file name:\ncodegen 18 1000000 1010 Name\n\n或输入唯一码长度(大于8)、需要生成的唯一码数量、起始流水号、名称和页码:\nPlease input code length(bigger than 8), the total number of codes, start serial number, csv file name and the page number:\ncodegen 18 1000000 1010 Name Page\n\n");
		exit(0);
	}

	int n = atoi(argv[1]);	//码长度
	if(n < 8) {
		printf("唯一码长度须大于8，例如:\nThe code length must be bigger than 8, for example:\ncodegen 18 1000000 1010 Name\n\n");
		exit(0);
	}

	int total = atoi(argv[2]);	//码数量
	int start = atoi(argv[3]);	//起始流水号
	int last = start + total;
	int t_len = printed_length(last);  //码数量最大位数
	
	//文件名
	char fname[sizeof(argv[4])];
	strcpy(fname, argv[4]);

	FILE *output = fopen(strcat(fname, ".csv"), "w+");
	if(output == NULL) {
		printf("无法创建文件%s", fname);
		exit(0);
	}

  //用来生成格式化串的字符串
  const char *prefix = "%";
  const char *middle = "s,%";
  const char *suffix = "d,%s\n";
  char fmt[255];
  
  /*
  char *code_t[total][n];
  gencode(total, n, code_t);
  
  int i;
	for(i = 0; i < total; i ++) {
		if(argc == 5) { // 不包含页码
		  sprintf(fmt, "%s%d%s", prefix, t_len, suffix);  // 拼接成 %Nd,%s\n , N来自t_len的值，控制序列号所占位数
		  fprintf(output, fmt, i + start, code_t[i]);
		} else if(argc == 6) {  // 第一列为页码名称
		  sprintf(fmt, "%s%s%d%s", prefix, middle, t_len, suffix);  // 拼接成 %s,%Nd,%s\n , N来自t_len的值，控制序列号所占位数
		  fprintf(output, fmt, argv[5], i + start, code_t[i]);
		}
	}
	*/


	int i;
	for(i = start; i < start + total; i ++) {
		uuid_create(&u);
		char *code = p_code(u, n);	//生成码

		if(argc == 5) { // 不包含页码
		  sprintf(fmt, "%s%d%s", prefix, t_len, suffix);  // 拼接成 %Nd,%s\n , N来自t_len的值，控制序列号所占位数
		  fprintf(output, fmt, i, code);
		} else if(argc == 6) {  // 第一列为页码名称
		  sprintf(fmt, "%s%s%d%s", prefix, middle, t_len, suffix);  // 拼接成 %s,%Nd,%s\n , N来自t_len的值，控制序列号所占位数
		  fprintf(output, fmt, argv[5], i, code);
		}
		free(code);
	}
	
	fclose(output);
}
;

void gencode(int total, int length, char *p[total][length]) {
	
	int i;
	for(i = 0; i < total; i ++) {

		char *t = nodup_code(i, length, p);

		strcpy(p[i],t);

		free(t);
	}
}
;

char *nodup_code(int total, int length, char *p[total][length]){
	uuid_t u;
	uuid_create(&u);
	char *t = p_code(u, length);	//生成码

	//查重	//check if there are duplicated codes
	int j;
	for(j = 0; j < total; j ++){
		if(total > 0 && strcmp(t, p[j]) == 0) {
			nodup_code(total, length, p);
		}
	}
	return t;
}
;

char *p_code(uuid_t u, int length) {
	int i;
	char *result;
	result = (char *) malloc(length * sizeof(char));
	char str[length], tmp[2], tmp2[9];

	snprintf(tmp2, sizeof(tmp2), "%8.8x", u.time_low);	//开头8位来自UUID
	strcpy(str, tmp2);

	int allowed_chars_max_idx = sizeof(allowed_chars) - 1;
	int allowed_chars2_max_idx = sizeof(allowed_chars2) - 1;

	//8位数以后每位均取随机值
	if(length > 8) {
		for (i = 8; i < length; i ++) {
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)];
		}
	}

	//检查是否有不符合字符相邻组合的情况
	for (i = 0; i < sizeof(str); i++) {
		str[i] = toupper(str[i]);
		// 不允许0、1、I、O出现	// don't allow 0, 1, I O appear in the code
		if (str[i] == '0')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'F';
		if (str[i] == '1')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'T';
		if (str[i] == 'I')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'L';
		if (str[i] == 'O')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'K';
		if (i > 0) {
			// 不允许N、M相邻出现或重复出现	// don't allow N and M appear side by side like NN, MM, NM, MN...
			if (str[i] == 'M' && str[i - 1] == 'M')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'P';
			if (str[i] == 'M' && str[i - 1] == 'N')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'Q';
			if (str[i] == 'N' && str[i - 1] == 'M')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'R';
			if (str[i] == 'N' && str[i - 1] == 'N')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'S';
			// 不允许V、W相邻出现或重复出现	// don't allow V and W appear side by side like WW, VV, VW, WV...
			if (str[i] == 'V' && str[i - 1] == 'V')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'X';
			if (str[i] == 'V' && str[i - 1] == 'W')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'Y';
			if (str[i] == 'W' && str[i - 1] == 'V')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'Z';
			if (str[i] == 'W' && str[i - 1] == 'W')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'A';
			// 不允许8、B相邻出现或重复出现 // don't allow 8 and B appear side by side like 8B, 88, BB, B8...
			if (str[i] == '8' && str[i - 1] == 'B')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'C';
			if (str[i] == 'B' && str[i - 1] == '8')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'D';
			if (str[i] == '8' && str[i - 1] == '8')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'E';
			if (str[i] == 'B' && str[i - 1] == 'B')
				str[i] =
						allowed_chars2[random_index(0, allowed_chars2_max_idx)]; //'F';
		}
	}
	str[length] = '\0';	//结尾

	strcpy(result, str);
	return result;
}
;

int random_index( minnum, maxnum) {
	struct timespec time1 = { 0, 0 };
	clock_gettime(CLOCK_REALTIME, &time1);
	srand(time1.tv_nsec);	//使用纳秒值作为种子，保证每次产生的随机数不一样
	//srand((unsigned) time(NULL)); //这种产生随机数方式因为计算机速度太快，导致一秒内结果都一样
	int choice = maxnum - minnum + 1;
	int a = rand() % choice + minnum;
	return a;
}
;
