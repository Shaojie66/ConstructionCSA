#include <stdlib.h>
#include <stdio.h>
//#define NUM 10*1024
#define ERROR -1
char* buff;
char* start_point;
int size;
char* get_gi(char* p, int n) { 
	static char* m, * t;
	m = (char*)malloc(n);
	t = (char*)malloc(n);
	if (m == NULL || n == NULL)
		return NULL;
	t = m;
	while (n--) {
		*m++ = *p++;
	}
	*(m) = '\0';
	return t;
}
char* get_seq(char* p, int n) {
	static char* m, * t;
	m = (char*)malloc(n - 1);
	t = (char*)malloc(n - 1);
	if (m == NULL || n == NULL)
		return NULL;
	t = m;
	p = p + n;
	while ((n < size) && (*p)) {
		*m++ = *p++;
		n++;
	}
	*(m - 1) = '\0';
	return t;
}
int main(int argc, char* argv[])
{
	FILE* file;
	size = 0;
	file = fopen(argv[1], "rt");
	/*argv[1]Ϊ�����д���ĵ�ַ��"rt"��ʾ��ֻ���ķ�ʽ��һ���ı��ļ�*/
	if (file == NULL)
	{
		printf("ERROR:cannot retrieve this file.\n");
		return ERROR;
	}
	fseek(file, 0L, SEEK_END);
	size = ftell(file);
	/*ͨ����λ���ļ�ĩβ�������ļ���Сsize������Ҳ��ͨ������ע�͵���forѭ����ȡ�ļ���Сsize*/
	rewind(file);
	//char a;
	//a='0';
	//int ii;
	//ii=0;
	/*for(;a!=EOF;){
	a = getc(file);

	printf("a is %c%d\n",a,ii);
	ii++;
	}*/
	//rewind(file);
	//printf("ii number is %d\n",ii);
	printf("The file size is %d\n", size);
	buff = (char*)malloc(size - 1);
	start_point = (char*)malloc(size - 1);
	if (buff == NULL || start_point == NULL)
		return ERROR;
	fread(buff, size - 1, 1, file);
	/*��fileָ����ı��ļ����ݶ���buff��������*/
	start_point = buff;
	/*start_point���ڴ洢buffָ����׵�ַ������free��*/
	printf("%s\n", buff);
	/*��ӡ���ı��ļ����ݣ��˴����ڵ��ԣ�printf�Ǹ��ܺõĵ��Է������˴��ɼ���ı��Ƿ�������Լ��Ƿ���ȷ��*/
	static int i;
	//unsigned short *aa;
	//printf("%c\n",*buff);
	static int pos;
	static int seq_pos;
	for (; *buff; buff++) {
		//printf("%p\n",buff);
		i++;
		if ((*buff == '|') && (*(buff + 1) == ' ')) {
			pos = i;
			//buff--;
			printf("The value of pos is %d\n", pos);
		}
		if ((*buff == 'A' || *buff == 'T' || *buff == 'C' || *buff == 'G') && (*(buff + 1) == 'A' || *(buff + 1) == 'T' || *(buff + 1) == 'C' || *(buff + 1) == 'G')\
			&& (*(buff + 2) == 'A' || *(buff + 2) == 'T' || *(buff + 2) == 'C' || *(buff + 2) == 'G')) {
			seq_pos = i - 1;
			printf("The value of seq_pos is %d\n", seq_pos);
			break;
		}
	}
	/*forѭ���м�¼�˱�ʶ���Ľ���λ�úͺ������е���ʼλ�ã�����ı�ʶ����ָ�ĵ�һ���ո�ǰ����ַ�*/
	//printf("%d\n",i);
	char* mm = get_gi(start_point, pos);
	/*mmָ���ʶ�����׵�ַ����������get_gi��ʵ����ָ�����ʵ�ֵ��ַ����Ŀ�����ĩ����Ҫ���Ͻ�����'\0'*/
	char* seq = get_seq(start_point, seq_pos);
	/*seqָ��������е��׵�ַ����������get_seqҲ��ָ�����ʵ�ֵ��ַ����Ŀ���*/
	printf("DESCRIPTOR=\n%s\n", mm);
	printf("SEQ=\n%s\n", seq);
	buff = start_point;

	free(buff);
	//free(mm);
	//free(seq);
	fclose(file);
	//getchar();
	return 0;
}