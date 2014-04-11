#include "copyrt.h"
#include "sysdep.h"
#include <stdio.h>
#include "uuid.h"
#include <stdlib.h>
#include <time.h>

uuid_t NameSpace_DNS = { /* 6ba7b810-9dad-11d1-80b4-00c04fd430c8 */
0x6ba7b810, 0x9dad, 0x11d1, 0x80, 0xb4, 0x00, 0xc0, 0x4f, 0xd4, 0x30, 0xc8 };

char allowed_chars[] = { '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C',
		'D', 'E', 'F', 'G', 'H', 'J', 'K', 'L', 'M', 'N', 'P', 'Q', 'R', 'S',
		'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
char allowed_chars2[] = { '2', '3', '4', '5', '6', '7', '9', 'A', 'C', 'D', 'E',
		'F', 'G', 'H', 'J', 'K', 'L', 'P', 'Q', 'R', 'S', 'T', 'U', 'X', 'Y',
		'Z' };

/* puid -- print a UUID */
void puid(uuid_t u);

char *puid2(uuid_t u);

char *pmasterkong_code(char* page, uuid_t u);

/* Simple driver for UUID generator */
void main(int argc, char **argv) {
	uuid_t u;
	int f;
	char *page = "XU";

	int i;
	for(i = 0; i < 10; i ++) {
		uuid_create(&u);
		char *p = puid2(u); //pmasterkong_code(page, u);
		printf("MasterKong: %7d -> %s\n", i, p);
		free(p);
	}
}
;

/*void test_uuid(int argc, char **argv) {
	uuid_t u;
	int f;

	uuid_create(&u);
	char *p = puid2(u);
	printf("uuid_create()             -> %s", p);
	free(p);
	f = uuid_compare(&u, &u);
	printf("\nuuid_compare(u,u): %d\n", f);  should be 0
	f = uuid_compare(&u, &NameSpace_DNS);
	printf("uuid_compare(u, NameSpace_DNS): %d\n", f);  s.b. 1
	f = uuid_compare(&NameSpace_DNS, &u);
	printf("uuid_compare(NameSpace_DNS, u): %d\n", f);  s.b. -1

	uuid_create_from_name(&u, NameSpace_DNS, "www.widgets.com", 15);
	printf("uuid_create_from_name() -> ");
	puid(u);
}
;*/

void puid(uuid_t u) {
	int i;
	printf("%8.8x-%4.4x-%4.4x-%2.2x%2.2x-", u.time_low, u.time_mid,
			u.time_hi_and_version, u.clock_seq_hi_and_reserved,
			u.clock_seq_low);
	for (i = 0; i < 6; i++)
		printf("%2.2x", u.node[i]);
	printf("\n");
}
;

char *puid2(uuid_t u) {
	int i;
	char *result;
	result = (char *) malloc(
			strlen("6ba7b810-9dad-11d1-80b4-00c04fd430c8") * sizeof(char));
	char str[100], end[24], tmp[4];
	snprintf(str, sizeof(str), "%8.8x-%4.4x-%4.4x-%2.2x%2.2x-", u.time_low,
			u.time_mid, u.time_hi_and_version, u.clock_seq_hi_and_reserved,
			u.clock_seq_low);

	for (i = 0; i < 6; i++) {
		snprintf(tmp, 4, "%2.2x", u.node[i]);
		//printf("%s", tmp);
		strcat(end, tmp);
		strcat(str, tmp);
		//printf("%2.2x", u.node[i]);
	}
	//printf("\nend: %s\n", end);
	//printf("%s\n", str);
	for (i = 0; i < sizeof(str); i++) {
		str[i] = toupper(str[i]);
	}

	//printf("%s\n", str);
	strcpy(result, str);
	return result;
}
;

char *pmasterkong_code(char* page, uuid_t u) {
	int i;
	char *result;
	result = (char *) malloc(
			strlen("33B8109DAD1100C04X") * sizeof(char));
	char str[50], tmp[4];
	snprintf(str, sizeof(str), "%s%8.8x", page, u.time_low);

	for (i = 3; i < 6; i++) {
		snprintf(tmp, 4, "%2.2x", u.node[i]);
		//printf("%s", tmp);
		strcat(str, tmp);
		//printf("%2.2x", u.node[i]);
	}

	int allowed_chars_max_idx = sizeof(allowed_chars) - 1;
	int allowed_chars2_max_idx = sizeof(allowed_chars2) - 1;
	for (i = 0; i < sizeof(str); i++) {
		str[i] = toupper(str[i]);
		// 不允许0、1、I、O出现
		if (str[i] == '0')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'F';
		if (str[i] == '1')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'T';
		if (str[i] == 'I')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'L';
		if (str[i] == 'O')
			str[i] = allowed_chars[random_index(0, allowed_chars_max_idx)]; //'K';
		if (i > 0) {
			// 不允许N、M相邻出现或重复出现
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
			// 不允许V、W相邻出现或重复出现
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
			// 不允许8、B相邻出现或重复出现
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
