#include <cstdio>
#include <cstring>

struct Student{
	char sid[11];
	int cid;
	char name[11];
	int score[4];
	bool isdel;
	int rank;
	int total;
	int passed;
};

Student student[1111];
int scnt=0;

bool tag = false;
const double eps = 1e-6;

void menu(){
	puts("Welcome to Student Performance Management System (SPMS).");
	puts("");
	puts("1 - Add");
	puts("2 - Remove");
	puts("3 - Query");
	puts("4 - Show ranking");
	puts("5 - Show Statistics");
	puts("0 - Exit");
	puts("");
}


bool _insert(Student s){
	int i;
	Student *p = student;
	
	for(i=0;i<scnt;i++,p++) if(!p->isdel){
		if(strcmp(p->sid,s.sid)==0) return false;
	}
	*p = s;
	scnt++;
	return true;
}

void insert(){
	Student a;
	char buf[111];
	
	for(;;){
		puts("Please enter the SID, CID, name and four scores. Enter 0 to finish.");
		scanf("%s",buf);
		if(strcmp(buf,"0")==0) return;
		strcpy(a.sid,buf);
		scanf("%d %s %d %d %d %d",&(a.cid),a.name,a.score,a.score+1,a.score+2,a.score+3);
		a.total = a.passed = 0;
		for(int i=0;i<4;i++){
			a.total += a.score[i];
			a.passed +=  a.score[i] >= 60;	
		}
		
		if(!_insert(a)) puts("Duplicated SID.");
		else {
			tag = true;			
		}
	}
}

int del_by_sid(char *sid){
	int i;
	Student *p = student;
	for(i=0;i<scnt;i++,p++) if(!p->isdel && strcmp(sid,p->sid)==0){
		p->isdel = true;
		return 1;
	}
	return 0;
}

int del_by_name(char *name){
	int i,cnt=0;
	Student *p = student;
	for(i=0;i<scnt;i++,p++) if(!p->isdel && strcmp(name,p->name)==0){
		p->isdel = true;
		cnt++;
	}
	return cnt;
}

void out(Student *p){
	printf("%d %s %d %s %d %d %d %d %d %.2f\n",p->rank,
											   p->sid,
											   p->cid,
											   p->name,
											   p->score[0],
											   p->score[1],
											   p->score[2],
											   p->score[3],
											   p->total,
											   p->total * 0.25 + eps);
}

void update_rank(){
	int i,j,k;
	Student *p = student,*q;
	for(i=0;i<scnt;i++,p++) if(!p->isdel){
		for(k=0,j=0,q=student;j<scnt;j++,q++) if(!q->isdel && p->total < q->total) k++;
		p->rank = k+1;
	}
	tag = false;
}

void del(){
	char buf[111];
	int n;
	int (*pf)(char *);
	for(;;){
		puts("Please enter SID or name. Enter 0 to finish.");
		scanf("%s",buf);
		if(strcmp(buf,"0")==0) return;
		if(buf[0]>='A' && buf[0] <= 'Z') pf=del_by_name;
		else pf = del_by_sid;
		n = (*pf)(buf);
		printf("%d student(s) removed.\n",n);		
		if(n) tag = true;
	}
}

void select_by_sid(char *sid){
	int i;
	Student *p = student;
	for(i=0;i<scnt;i++,p++) if(!p->isdel && strcmp(sid,p->sid)==0){
		out(p);
		return;
	}
}

void select_by_name(char *name){
	int i;
	Student *p = student;
	for(i=0;i<scnt;i++,p++) if(!p->isdel && strcmp(name,p->name)==0){
		out(p);
	}
}

void select(){
	char buf[111];
	void (*pf)(char *); 
	for(;;){
		puts("Please enter SID or name. Enter 0 to finish.");
		scanf("%s",buf);
		if(strcmp(buf,"0")==0) return;
		if(buf[0]>='A' && buf[0] <= 'Z') pf=select_by_name;
		else pf = select_by_sid;
		if(tag) update_rank();
		(*pf)(buf);
	}	
}

void stat(){
	int cid,i,j,cp[4]={0},pp[5]={0},ct[4]={0},snum=0;
	const char course[4][22]={"Chinese","Mathematics","English","Programming"};
	Student *p = student;
	
	puts("Please enter class ID, 0 for the whole statistics.");
	scanf("%d",&cid);

	for(i=0;i<scnt;i++,p++) if(!p->isdel && (!cid || cid == p->cid)){
		pp[p->passed]++;
		snum++;
		for(j=0;j<4;j++) {
			ct[j] += p->score[j];
			if(p->score[j] >= 60) cp[j]++;
		}
	}
	
	for(i=0;i<4;i++){
		puts(course[i]);
		printf("Average Score: %.2f\n",ct[i] ? ct[i] * 1.0 / snum + eps : 0.0);
		printf("Number of passed students: %d\n",cp[i]);
		printf("Number of failed students: %d\n\n",snum - cp[i]);
	}

	for(i=3;i>=1;i--) pp[i] += pp[i+1];
	puts("Overall:");
	printf("Number of students who passed all subjects: %d\n",pp[4]);
	printf("Number of students who passed 3 or more subjects: %d\n",pp[3]);
	printf("Number of students who passed 2 or more subjects: %d\n",pp[2]);
	printf("Number of students who passed 1 or more subjects: %d\n",pp[1]);
	printf("Number of students who failed all subjects: %d\n",pp[0]);

	puts("");
}

void _exit(){

}

void rank(){
	puts("Showing the ranklist hurts students' self-esteem. Don't do that.");
}

int main(){
	int op;
	void (*pf[6])()={_exit,insert,del,select,rank,stat};
	menu();
	while(scanf("%d",&op),op){		
		(*pf[op])();
		menu();
	}
	return 0;
}


