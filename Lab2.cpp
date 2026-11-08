#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#define MAXSIZE 100
//顺序表结构体定义 
typedef struct {
	int data[MAXSIZE];
	int length;
}SqList;
//初始化顺序表 
void InitList(SqList* L) {
	L->length = 0;
}
//创建顺序表 
void CreateList(SqList* L, int n) {
	int i;
	printf("输入%d个元素:\n", n);
	for (i = 0;i < n;i++) {
		scanf("%d", &L->data[i]);
	}
	L->length = n;
}
//判断顺序表是否为空 
int IsEmpty(SqList* L) {
	return L->length == 0;
}
//计算顺序表长度
int Getlength(SqList* L) {
	return L->length;
}
//输出顺序表内容 
void PrintList(SqList* L) {
	int i;
	if (IsEmpty(L)) {
		printf("当前为空表\n");
		return;
	}
	printf("顺序表内容:");
	for (i = 0;i < L->length;i++) {
		printf("%d", L->data[i]);
	}
	printf("\n");
}
//获取指定位置posion的元素值 
int GetElem(SqList* L, int pos, int* e) {
	if (pos<1 || pos>L->length) {
		return 0;
	}
	*e = L->data[pos - 1];
	return 1;
}
//顺序查找：查找元素值为value的位置 
int Search_Seq(SqList* L, int val) {
	int i;
	for (i = 0;i < L->length;i++) {
		if (L->data[i] == val) {
			return i + 1;
		}
	}
	return 0;
}
//二分查找:查找元素值为value的位置 
int Search_Bin(SqList* L, int val) {
	int low = 0, high = L->length - 1, mid;
	while (low < high) {
		mid = (low + high) / 2;
		if (L->data[mid] == val) {
			return mid + 1;
		}
		else if (L->data[mid] > val) {
			high = mid - 1;
		}
		else {
			low = mid + 1;
		}
	}
	return 0;
}
//在指定位置position之前插入新元素x 
int ListInsert(SqList* L, int pos, int x) {
	int i;
	if (L->length >= MAXSIZE || pos<1 || pos>L->length + 1) {
		return 0;
	}
	for (i = L->length - 1;i >= pos - 1;i--) {
		L->data[i + 1] = L->data[i];
	}
	L->data[pos - 1] = x;
	L->length++;
	return 1;
}
//删除指定位置position的元素 
int ListDeletepos(SqList* L, int pos) {
	int i;
	if (pos<1 || pos>L->length) {
		return 0;
	}
	for (i = pos - 1;i <= L->length - 1;i++) {
		L->data[i] = L->data[i + 1];
	}
	L->length--;
	return 1;
}
//删除指定元素值value
int ListDeleteVal(SqList* L, int val) {
	int i = 0, j = 0;
	int count = 0;
	while (i < L->length) {
		if (L->data[i] == val) {
			count++;
		}
		else {
			L->data[j++] = L->data[i];
		}
		i++;
	}
	L->length -= count;
	return count;
}
int main() {
	SqList L;InitList(&L);
	int op, n, pos, e, x, val, res;
	while (1) {
		printf("\n0退出 1初始化 2创建 3判空 4长度 5打印 6取元素 7查找 8插入 9删位置 10删同值:");
		printf("请选择操作:");
		scanf("%d", &op);
		if (op == 0)break;
		switch (op) {
		case 1:
			InitList(&L);
			printf("顺序表已初始化\n");
			break;
		case 2:
			printf("请输入要创建的元素个数:");
			scanf("%d", &n);
			CreateList(&L, n);
			break;
		case 3:
			printf(IsEmpty(&L) ? "当前表为空\n" : "当前表非空\n");
			break;
		case 4:
			printf("顺序表长度=%d\n", Getlength(&L));
			break;
		case 5:
			PrintList(&L);
			break;
		case 6:
			printf("请输入要获取元素的位置:");
			scanf("%d", &pos);
			if (GetElem(&L, pos, &e)) {
				printf("位置%d的元素值为:%d\n", pos, e);
			}
			else {
				printf("获取失败，位置非法!\n");
			}
			break;
		case 7:
			printf("请输入要查找的元素值:");
			scanf("%d", &val);
			res = Search_Seq(&L, val);
			printf("顺序查找结果:");
			if (res)
				printf("找到，位置为%d\n", res);
			else
				printf("未找到(注意:二分查找要求表必须有序)\n");
			break;
		case 8:
			printf("请输入插入位置pos和元素值x:");
			scanf("%d%d", &pos, &x);
			if (ListInsert(&L, pos, x)) {
				printf("插入成功!\n");
				PrintList(&L);
			}
			else {
				printf("插入失败，位置非法或表已满!\n");
			}
			break;
		case 9:
			printf("请输入要删除的元素位置:");
			scanf("%d", &pos);
			if (ListDeletepos(&L, pos)) {
				printf("删除成功!\n");
				PrintList(&L);
			}
			else {
				printf("删除失败，位置非法!\n");
			}
			break;
		case 10:
			printf("请输入要删除的元素值:");
			scanf("%d", &val);
			res = ListDeleteVal(&L, val);
			printf("共删除了%d的元素\n", res, val);
			PrintList(&L);
			break;
		default:
			printf("无效的操作选项!\n");
			break;
		}
	}
	return 0;
}