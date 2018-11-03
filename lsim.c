#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


int num();
char *varDup();
char *SubOp();
void print();
char *combo();
void vari();
int evaluate();

char *vars={0};
char *buf={0};
int numVars= 0;
static int values[]={0x00};
char*table={0};
//int next= 0;



int main (int argc, char ** argv){

    int n,m=0,x=1,k=0,i=0,j=0;
    vars= (char *) calloc( 16,sizeof(char) );
    char *e = (char *) calloc(32,sizeof(char));
    buf = (char *) calloc(4,sizeof(int));;
    char *buffer = (char *) calloc(32,sizeof(char));
    //int* table= (int *) calloc(32,sizeof(int));


    if (argc!=2){ printf("Invoke as: %s <expression>",argv[0]);return 1;}
    if (strlen(argv[1])> 16){printf("Too many variables"); return 1;}
    //e= bufv[1];
    strcpy(e,argv[1]);
    vars = varDup(SubOp(e),vars);
    //for (i=0;i<strlen(vars);i++){
    //    vars1[i]=vars[i];
    //}
    n= num(vars);
    table= combo(n);
    //printf("%d",m);
    vari(m);
    print(n,argv[1],vars,0,values);
    while (x){
    for (i=0;i<n;i++){
       buf[i] = table[j];j++;
    }
    strcpy(buffer,argv[1]);
    values[k]= evaluate(buffer,0,vars,buf);
    //argv[1]= buffer;
    printf("\n");
    print(n,argv[1],buf,1,values);
    k++;
    if(k==(1<<(n))) x=0;

    }

    return 0;
    }
char *SubOp(char* a){
    char *str=a;
    //strcpy(str,a);
    int i;
    for (i=0;i<strlen(a);i++){
        if (str[i]=='^'|| str[i]=='v'||str[i]=='~'||str[i]=='1'|| str[i]=='0')
        str[i]=' ';

    }
    return str;
}

char *varDup(char *a,char*b){
    int i=0,j,count;
    for(i=0;i<strlen(a);i++){
        count= 0;
        if (b[0]==0x00) b[0]= a[i];
       for(j=0; j< strlen(b);j++){
        if (a[i] == b[j]) break;
        else count = 1;}
       if (count== 1) b[j] = a[i];}
 /*   for (i=0;i<n;i++){

        for (j=i+1;j<n;j++){
            if(str[i]==str[j]){
                for(x= j;x<n;x++){str[x]=str[x+1];} n--;
        }
            else j++;

    }*/

    return b;
}

int num(char *str){
    int i,j=strlen(str),n=j;
    for (i=0;i<j;i++){
    if (str[i]==' '){--n;}
    }
    return n;
}
void print(int n, char *buf,char *var,int g,int *sol){
    static int k=0; char p;
    if (sol[k] == 0) p ='0';
    else p='1';
    printf("|     ");
    for (int i=0; i<n; i++) {
    if (var[i]== ' ') {n++;continue;}
    printf("%c     |     ",var[i]);}
    if (g == 0) printf("%s \n", buf);
    else {printf("%c \n", p);k++;}
    for (int i=0; i<n; i++) {
    printf("+-----------");
    }

    return;
    /*int t=n;
    switch (t){
    case 2 : printf("|  %c   |  %c   |  %s   \n +-----+-----+-----\n", var[1],var[2],var);return;
    case 3 : printf("|  %c   |  %c   |  %c   |  %s   \n +-----+-----+-----\n", var[1],var[2],var[3],var);return;
    case 4 : printf("|  %c   |  %c   |  %c   |  %c   |  %s   \n +-----+-----+-----\n", var[1],var[2],var[3],var[4],var);return;
    }*/
}

char* combo(int n){
    int i,mask=0b0000000000000001,l,j,k=0;
        mask= mask<<n;
     char* buf= (char *) calloc(128,sizeof(int));
    //n= mask-1;

    for (i=0;i<mask;i++){
    l= i;
        for (j=1;j<=n;j++){
            if (i/(1<<(n-j))== 0)
            {buf[k]= '0';k++;}
            else
            {buf[k]= '1';k++;i=i-(1<<(n-j));}
        }
    i=l;// memory
    }
    return buf;
}
void vari(int n){
    for (int i=0;i<n;++i){
        if (i%2==0) {values[i]=0;}
        if (i%2==1) {values[i]=1;}
    }
}

int evaluate(char*expr, int next,char *vars,char *buf){
    int m= strlen(expr),shift=0;

    for (int k=0;k<m;k++){
       for (int i=0;i<strlen(vars);i++){
            if (vars[i]==' ') shift +=1;
            if (expr[k] == vars[i]) expr[k]= buf[i-shift];}
            shift=0;
    }

    char op= expr[next];
    int op1,op2= 0;
    switch (op){
    case '0': ++next;return 0;
    case '1': ++next;return 1;
    case '~': ++next;return !evaluate(expr,next,vars,buf);
    case '^': ++next;
                op1=evaluate(expr,next,vars,buf);
                op2=evaluate(expr,next+1,vars,buf);
                return op1 && op2;
    case 'v': ++next;op1=evaluate(expr,next,vars,buf); op2=evaluate(expr,next+1,vars,buf); return op1 || op2;
    case ' ': exit(1);
    //case  : exit(1);
    default:  return op;
    }



}


