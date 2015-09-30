#define _CRT_SECURE_NO_WARNINGS
#include <fstream>
#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>

using namespace std;

#define N 100000
#define M 2
#define MM 4
#define NIL (-1L)

typedef enum {
	INSERTNOTCOMPLETE, SUCCESS, DUPLICATEKEY,
	UNDERFLO, NOTFOUND
} status;


typedef struct {
	int cnt;
	int key[MM];
	long ptr[MM + 1];
} node;

node rootnode;
long start[2], root = NIL, freelist = NIL;
FILE *fptree;

void error(char *str)
{
	printf("\nError: %s\n", str);
	exit(1);
}

void readnode(long t, node *pnode)
{
	if (t == root) {
		*pnode = rootnode;
		return;
	}
	if (fseek(fptree, t, SEEK_SET))
		error("fseek in readnode");
	if (fread(pnode, sizeof(node), 1, fptree) == 0)
		error("fread in readnode");
}

void writenode(long t, node *pnode)
{
	if (t == root)
		rootnode = *pnode;
	if (fseek(fptree, t, SEEK_SET))
		error("fseek in writenode");
	if (fwrite(pnode, sizeof(node), 1, fptree) == 0)
		error("fwrite in writenode");
}

long getnode(void)
{
	long t;
	node nod;

	if (freelist == NIL) {
		if (fseek(fptree, 0L, SEEK_END))
			error("fseek in getnode");
		t = ftell(fptree);
		writenode(t, &nod);
	} 

	else {
		t = freelist;
		readnode(t, &nod);
		freelist = nod.ptr[0];
	}
	return(t);
}

void found(long t, int i)
{
	node nod;

	printf("Found in position %d of node with contents:  ", i);
	readnode(t, &nod);
	for (i = 0; i < nod.cnt; i++)
		printf("  %d", nod.key[i]);
	puts("");

}

void notfound(int x)
{
	printf("Item %ld not found\n", x);
}

int binsearch(int x, int *a, int n)
{
	int i, left, right;

	if (x <= a[0])
		return 0;
	if (x > a[n - 1])
		return n;
	left = 0;
	right = n - 1;
	while (right - left > 1) {
		i = (right + left) / 2;
		if (x <= a[i])
			right = i;
		else
			left = i;
	}
	return(right);
}

status search(int x)
{
	int i, j, *k, n;
	node nod;
	long t = root;

	puts("Search path:");
	while (t != NIL) {
		readnode(t, &nod);
		k = nod.key;
		n = nod.cnt;
		for (j = 0; j < n; j++)
			printf("  %d", k[j]);
		puts("");
		i = binsearch(x, k, n);
		if (i < n && x == k[i]) {
			found(t, i);
			return(SUCCESS);
		}
		t = nod.ptr[i];
	}
	return(NOTFOUND);
}

status ins(int x, long t, int *y, long *u)
{
	long tnew, p_final, *p;
	int i, j, *n, k_final, *k, xnew;
	status code;
	node nod, newnod;

	if (t == NIL) {
		*u = NIL;
		*y = x;
		return(INSERTNOTCOMPLETE);
	}
	readnode(t, &nod);
	n = &nod.cnt;
	k = nod.key;
	p = nod.ptr;

	i = binsearch(x, k, *n);
	if (i < *n && x == k[i])
		return(DUPLICATEKEY);
	code = ins(x, p[i], &xnew, &tnew);
	if (code != INSERTNOTCOMPLETE)
		return code;

	if (*n < MM) {
		i = binsearch(xnew, k, *n);
		for (j = *n; j > i; j--) {
			k[j] = k[j - 1];
			p[j + 1] = p[j];
		}
		k[i] = xnew;
		p[i + 1] = tnew;
		++*n;
		writenode(t, &nod);
		return(SUCCESS);
	}
	if (i == MM) {
		k_final = xnew;
		p_final = tnew;
	}
	else {
		k_final = k[MM - 1];
		p_final = p[MM];
		for (j = MM - 1; j>i; j--) {
			k[j] = k[j - 1];
			p[j + 1] = p[j];
		}
		k[i] = xnew;
		p[i + 1] = tnew;
	}
	*y = k[M];
	*n = M;
	*u = getnode(); newnod.cnt = M;
	for (j = 0; j< M - 1; j++) {
		newnod.key[j] = k[j + M + 1];
		newnod.ptr[j] = p[j + M + 1];
	}
	newnod.ptr[M - 1] = p[MM];
	newnod.key[M - 1] = k_final;
	newnod.ptr[M] = p_final;
	writenode(t, &nod);
	writenode(*u, &newnod);
	return(INSERTNOTCOMPLETE);
}

status insert(int x)
{
	long tnew, u;
	int xnew;
	status code = ins(x, root, &xnew, &tnew);

	if (code == DUPLICATEKEY)
		printf("Duplicate uid %d ignored \n", x);
	else
		if (code == INSERTNOTCOMPLETE) {
			u = getnode();
			rootnode.cnt = 1;
			rootnode.key[0] = xnew;
			rootnode.ptr[0] = root;
			rootnode.ptr[1] = tnew;
			root = u;
			writenode(u, &rootnode);
			code = SUCCESS;
		}
	return(code);  
}

void freenode(long t)
{
	node nod;

	readnode(t, &nod);
	nod.ptr[0] = freelist;
	freelist = t;
	writenode(t, &nod);
}

void rdstart(void)
{

	if (fseek(fptree, 0L, SEEK_SET))
		error("fseek in rdstart");
	if (fread(start, sizeof(long), 2, fptree) == 0)
		error("fread in rdstart");
	readnode(start[0], &rootnode);
	root = start[0];
	freelist = start[1];
}

void wrstart(void)
{

	start[0] = root;
	start[1] = freelist;
	if (fseek(fptree, 0L, SEEK_SET))
		error("fseek in wrstart");
	if (fwrite(start, sizeof(long), 2, fptree) == 0)
		error("fwrite in wrstart");
	if (root != NIL)
		writenode(root, &rootnode);
}

status del(int x, long t)
{
	int i, j, *k, *n, *item, *nleft, *nright, *lkey, *rkey, borrowleft = 0, nq,
		*addr;
	status code;
	long *p, left, right, *lptr, *rptr, q, q1;
	node nod, nod1, nod2, nodL, nodR;

	if (t == NIL)
		return(NOTFOUND);
	readnode(t, &nod);
	n = &nod.cnt;
	k = nod.key;
	p = nod.ptr;
	i = binsearch(x, k, *n);
	/* *t is a leaf */
	if (p[0] == NIL) {
		if (i == *n || x < k[i])
			return NOTFOUND;
		for (j = i + 1; j < *n; j++) {
			k[j - 1] = k[j];
			p[j] = p[j + 1];
		}
		--*n;
		writenode(t, &nod);
		return(*n >= (t == root ? 1 : M) ? SUCCESS : UNDERFLO);
	}
	item = k + i;
	left = p[i];
	readnode(left, &nod1);
	nleft = &nod1.cnt;

	if (i < *n && x == *item) {
		q = p[i];
		readnode(q, &nod1);
		nq = nod1.cnt;
		while (q1 = nod1.ptr[nq], q1 != NIL) {
			q = q1;
			readnode(q, &nod1);
			nq = nod1.cnt;
		}

		addr = nod1.key + nq - 1;
		*item = *addr;
		*addr = x;
		writenode(t, &nod);
		writenode(q, &nod1);
	}


	code = del(x, left);
	if (code != UNDERFLO)
		return code;
	if (i < *n)
		readnode(p[i + 1], &nodR);
	if (i == *n || nodR.cnt == M) {
		if (i > 0) {
			readnode(p[i - 1], &nodL);
			if (i == *n || nodL.cnt > M)
				borrowleft = 1;
		}
	}
	if (borrowleft) {
		item = k + i - 1;
		left = p[i - 1];
		right = p[i];
		nod1 = nodL;
		readnode(right, &nod2);
		nleft = &nod1.cnt;
	}
	else {
		right = p[i + 1]; 
		readnode(left, &nod1);
		nod2 = nodR;
	}
	nright = &nod2.cnt;
	lkey = nod1.key;
	rkey = nod2.key;
	lptr = nod1.ptr;
	rptr = nod2.ptr;
	if (borrowleft) {
		rptr[*nright + 1] = rptr[*nright];
		for (j = *nright; j>0; j--) {
			rkey[j] = rkey[j - 1];
			rptr[j] = rptr[j - 1];
		}
		++*nright;
		rkey[0] = *item;
		rptr[0] = lptr[*nleft];
		*item = lkey[*nleft - 1];
		if (--*nleft >= M) {
			writenode(t, &nod);
			writenode(left, &nod1);
			writenode(right, &nod2);
			return SUCCESS;
		}
	}
	else
		if (*nright > M) {
			lkey[M - 1] = *item;
			lptr[M] = rptr[0];
			*item = rkey[0];
			++*nleft;
			--*nright;
			for (j = 0; j < *nright; j++) {
				rptr[j] = rptr[j + 1];
				rkey[j] = rkey[j + 1];
			}
			rptr[*nright] = rptr[*nright + 1];
			writenode(t, &nod);
			writenode(left, &nod1);
			writenode(right, &nod2);
			return(SUCCESS);
		}
	lkey[M - 1] = *item;
	lptr[M] = rptr[0];
	for (j = 0; j<M; j++) {
		lkey[M + j] = rkey[j];
		lptr[M + j + 1] = rptr[j + 1];
	}
	*nleft = MM;
	freenode(right);
	for (j = i + 1; j < *n; j++) {
		k[j - 1] = k[j];
		p[j] = p[j + 1];
	}
	--*n;
	writenode(t, &nod);
	writenode(left, &nod1);
	return(*n >= (t == root ? 1 : M) ? SUCCESS : UNDERFLO);
}

status delnode(int x)
{
	long newroot;

	status code = del(x, root);
	if (code == UNDERFLO) {
		newroot = rootnode.ptr[0];
		freenode(root);
		if (newroot != NIL)
			readnode(newroot, &rootnode);
		root = newroot;
		code = SUCCESS;
	}
	return(code); 
}

void printtree(long t)
{
	static int position = 0;
	int i, *k, n;
	node nod;

	if (t != NIL) {
		position += 6;
		readnode(t, &nod);
		k = nod.key;
		n = nod.cnt;
		printf("%*s", position, "");
		for (i = 0; i<n; i++)
			printf(" %d", k[i]);
		puts("");
		for (i = 0; i <= n; i++)
			printtree(nod.ptr[i]);
		position -= 6;
	}
}

void nuumbers()
{
	int arreglo[N];

	for (int i = 0; i < N; i++)
	{
		int r;
		bool encontrado = true;
		while (encontrado)
		{
			encontrado = false;
			r = rand() % 1000000;
			for (int x = 0; x < N; x++)
			{
				if (r == arreglo[x] && r > 0)
				{
					encontrado = true;
					break;
				}
			}
		}
		arreglo[i] = r;
	}
	ofstream out("btree.txt");
	if (!out)
		cout << "No hay archivo" << endl;
	else
		cout << "SEE" << endl;

	for (int j = 0; j < N; j++)
		out << arreglo[j] << " ";
}

int main()
{
	clock_t t;
	nuumbers();
	int x, code = 0;
	char ch, treefilnam[51], inpfilnam[51];
	FILE *fpinp;

	printf("Nombre del archivo bin");
	scanf("%50s", treefilnam);
	fptree = fopen(treefilnam, "r+b");
	if (fptree == NULL) {
		fptree = fopen(treefilnam, "w+b");
		wrstart();
	}
	else {
		rdstart();
		printtree(root);
	}
	
	if (code)
		printtree(root);
	printf("Hay archivo de texto? (1(YES)): ");
	scanf(" %c", &ch);
	while (getchar() != '\n');
	if (toupper(ch) == '1') {
		printf("Nombre del txt: ");
		scanf("%50s", inpfilnam);
		if ((fpinp = fopen(inpfilnam, "r")) == NULL)
			error("nosta");
		while (fscanf(fpinp, "%d", &x) == 1)
			insert(x);
		fclose(fpinp);
		//printtree(root);
	}

	/*for (; ; ) {
		printf("Pon un numero seguido de I, D, o S (for Insert, Delete and Search), o Q para salir: ");
		code = scanf("%d", &x);
		scanf(" %c", &ch);
		ch = toupper(ch);
		if (code)

			switch (ch) {

			case 'I': if (insert(x) == SUCCESS)
				printtree(root);
				break;

			case 'D': if (delnode(x) == SUCCESS)
				printtree(root);
					  else
						  puts("Not found");
				break;

			case 'S': if (search(x) == NOTFOUND)
				puts("Not found");
				break;
			}
		else
			if (ch == 'Q')
				break;
	}*/
	t = clock();

	wrstart();
	fclose(fptree);
	t = clock() - t;

	printf("Tarde %f segundo(s), para acabar el árbol AVL", (float)t / CLOCKS_PER_SEC);
	return(0);
}