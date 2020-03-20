//五子棋人机-人人对战 designed by Li Guofeng

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15

char board[SIZE][SIZE];       //该数组用于表示棋盘格局
char whiteplace[SIZE][SIZE];    //该数组用于记录白棋布局
char blackplace[SIZE][SIZE];    //该数组用于记录黑棋布局
void preboard(void);           // 该函数用于将棋盘位置分类 
void displayboard(void);      //该函数用于显示棋盘及落子情况

int rewx,rewy;             //记录白子最近一步落子的位置
int rebx,reby;              //记录黑子最近一步落子的位置

void setblack(void);        
void setwhite(void);     //这两个函数用于实现根据指定坐标落子
void chospatn(void);      //选择对战模式
void choside(void);      //用于选边（人机对战）
void order(void);         //用于决定下一步轮到哪一方（人人对战）
void aisetblack(void);    //用于AI执黑子时的落子
void aisetwhite(void);     //用于AI执白子时的落子
int trans(char c);      //用于字母和数字的转换

void pve(void);           //pve
void pvp(void);           //pvp
void whowins(void);        //进行胜负判定

int main(){
	preboard();
	displayboard();
	chospatn();
	return 0;
}

void preboard(void){
	int i,j;
	board[0][0]=1;            //┏,棋盘左上角
	board[0][SIZE-1]=2;       //┓，棋盘右上角
	board[SIZE-1][0]=3;       //┗，棋盘左下角
	board[SIZE-1][SIZE-1]=4;  //┛,棋盘右下角
	for(j=1;j<SIZE-1;j++){
		board[0][j]=5;        //┯,棋盘上沿 
		board[SIZE-1][j]=6;   //┷，棋盘下沿 
	}
	for(i=1;i<SIZE-1;i++){
		board[i][0]=7;        //┠,棋盘左沿
		board[i][SIZE-1]=8;   //┨，棋盘右沿 
	}
	for(i=1;i<SIZE-1;i++){
		for(j=1;j<SIZE-1;j++){
			board[i][j]=9;    //┼，棋盘中部 
		}
	}
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			blackplace[i][j]=0;
			whiteplace[i][j]=0;         //将未落子的位置统一标记为0
		}
	} 
}

void displayboard(void){
	int i=0,j=0;
	putchar('\n');
	for(i=0;i<SIZE;i++){
		printf("%2d",i);         //标出棋盘纵坐标
		for(j=0;j<SIZE;j++){
			switch(board[i][j]){
				case 1:printf("┏"); break;
				case 2:printf("┓"); break;
				case 3:printf("┗"); break;
				case 4:printf("┛"); break;
				case 5:printf("┯"); break;
				case 6:printf("┷"); break;
				case 7:printf("┠"); break;
				case 8:printf("┨"); break;
				case 9:printf("┼"); break;
				case 10:printf("●");break;
				//case 11:printf("▲");break;
				case 12:printf("◎");break;  
				//case 13:printf("△");break;
				default:             break;
			}
		}
		printf("\n");
	}
	printf("  A B C D E F G H I J K L M N O \n");      //标出棋盘横坐标
} 

int trans(char c){
	switch(c){
		case 'A':return 0;	
		case 'B':return 1;	
		case 'C':return 2;	
		case 'D':return 3;	
		case 'E':return 4;	
		case 'F':return 5;	
		case 'G':return 6;	
		case 'H':return 7;	
		case 'I':return 8;	
		case 'J':return 9;	
		case 'K':return 10;	
		case 'L':return 11;	
		case 'M':return 12;	
		case 'N':return 13;	
		case 'O':return 14;	
	}
}

void setblack(void){
	int xb,ybi;
	char yb;
	while(1){
		xb=ybi=0;
		printf("请输入黑子的坐标（格式'3 A'）:\n");    //提示落子
		scanf("%d %c",&xb,&yb);             //输入落子的位置
		ybi=trans(yb);
		if(xb>=0 && xb<SIZE && ybi>=0 && ybi<SIZE){
			if(blackplace[xb][ybi]==0){
				blackplace[xb][ybi]=1;
				whiteplace[xb][ybi]=2;
				board[xb][ybi]=10;                //0表示该点为空，1表示该点有黑棋，2表示该点有白棋，10表示在棋盘中落一黑子
				displayboard();
				rebx=xb;
				reby=ybi;
				break;
			}else{
				printf("该点已有棋子，请重试;\n");
			}
		}else{
			printf("超出棋盘范围，请重试;\n");
		}
	}
}

void setwhite(void){
	int xw,ywi;
	char yw;
	while(1){
		xw=ywi=0;
		printf("请输入白子的坐标（格式'3 A'）:\n");    //提示落子
		scanf("%d %c",&xw,&yw);             //输入落子的位置
		ywi=trans(yw);
		if(xw>=0 && xw<SIZE && ywi>=0 && ywi<SIZE){
			if(whiteplace[xw][ywi]==0){
				whiteplace[xw][ywi]=1;
				blackplace[xw][ywi]=2;
				board[xw][ywi]=12;                //0表示该点为空，1表示该点有白棋，2表示该点有黑棋，12表示在棋盘中落一白子
				displayboard();
				rewx=xw;
				rewy=ywi;
				break;
			}else{
				printf("该点已有棋子，请重试;\n");
			}
		}else{
			printf("超出棋盘范围，请重试;\n");
		}
	}
}

void chospatn(void){
	int p;
	while(1){
		p=0;
		printf("请选择对战模式:输入0进行人机对战，输入1进行人人对战\n");
		scanf("%d",&p);
		if(p==0){
			pve();   break;
		}else if(p==1){
			pvp();   break;
		}else{
			printf("输入不符合规范，请重新输入\n");
		}
	}
}

void choside(void){           //调用当且进当选择人机对战
	int c;
	while(1){
		c=0;
		printf("请选边：输入数字0选择黑棋，输入数字1选择白棋：\n");      //提示选边
		scanf("%d",&c);
		if(c==0){
			while(1){
				setblack();
				whowins();
				aisetwhite();
				whowins();
			}
		}else if(c==1){
			while(1){
				aisetblack();
				whowins();
				setwhite();
				whowins(); 
			}
		}else{
			printf("输入不符合规范，请重新输入:\n"); 
		}
	}
}

void order(void){        //人人对战的落子顺序     
	while(1){
		setblack();
		whowins();
		setwhite();
		whowins();
	}
}

void whowins(void){
	int i,j,s;
	for(i=0;i<SIZE;i++){
		for(j=0;j<11;j++){
			if(blackplace[i][j]==1 && blackplace[i][j+1]==1 && blackplace[i][j+2]==1 && blackplace[i][j+3]==1 && blackplace[i][j+4]==1){
				printf("黑棋获胜\n");
				exit(1);
			}
			if(whiteplace[i][j]==1 && whiteplace[i][j+1]==1 && whiteplace[i][j+2]==1 && whiteplace[i][j+3]==1 && whiteplace[i][j+4]==1){
				printf("白棋获胜\n");
				exit(1);
			}
		}
	}                 //在每一行寻找连子
	for(j=0;j<SIZE;j++){
		for(i=0;i<11;i++){
			if(blackplace[i][j]==1 && blackplace[i+1][j]==1 && blackplace[i+2][j]==1 && blackplace[i+3][j]==1 && blackplace[i+4][j]==1){
				printf("黑棋获胜\n");
				exit(1);
			}
			if(whiteplace[i][j]==1 && whiteplace[i+1][j]==1 && whiteplace[i+2][j]==1 && whiteplace[i+3][j]==1 && whiteplace[i+4][j]==1){
				printf("白棋获胜\n");
				exit(1);
			}
		}
	}                 //在每一列寻找连子
	for(s=4;s<SIZE;s++){
		for(i=0,j=s;i+4<=s && j-4>=0;i++,j--){
			if(blackplace[i][j]==1 && blackplace[i+1][j-1]==1 && blackplace[i+2][j-2]==1 && blackplace[i+3][j-3]==1 && blackplace[i+4][j-4]==1){
				printf("黑棋获胜\n");
				exit(1);
			}
			if(whiteplace[i][j]==1 && whiteplace[i+1][j-1]==1 && whiteplace[i+2][j-2]==1 && whiteplace[i+3][j-3]==1 && whiteplace[i+4][j-4]==1){
				printf("白棋获胜\n");
				exit(1);
			}
		}
	}
	for(s=1;s<SIZE-4;s++){
		for(i=s,j=SIZE-1;i+4<SIZE && j-4>=s;i++,j--){
			if(blackplace[i][j]==1 && blackplace[i+1][j-1]==1 && blackplace[i+2][j-2]==1 && blackplace[i+3][j-3]==1 && blackplace[i+4][j-4]==1){
				printf("黑棋获胜\n");
				exit(1);
			}
			if(whiteplace[i][j]==1 && whiteplace[i+1][j-1]==1 && whiteplace[i+2][j-2]==1 && whiteplace[i+3][j-3]==1 && whiteplace[i+4][j-4]==1){
				printf("白棋获胜\n");
				exit(1);
			}
		}             
	}                 //在斜率为正的直线上寻找连子
	for(s=0;s<SIZE-4;s++){
		for(i=0,j=s;i+4<SIZE-s && j+4<SIZE;i++,j++){
			if(blackplace[i][j]==1 && blackplace[i+1][j+1]==1 && blackplace[i+2][j+2]==1 && blackplace[i+3][j+3]==1 && blackplace[i+4][j+4]==1){
				printf("黑棋获胜\n");
				exit(1);
			}
			if(whiteplace[i][j]==1 && whiteplace[i+1][j+1]==1 && whiteplace[i+2][j+2]==1 && whiteplace[i+3][j+3]==1 && whiteplace[i+4][j+4]==1){
				printf("白棋获胜\n");
				exit(1);
			}
		}
	}
	for(s=1;s<SIZE;s++){
		for(i=s,j=0;i+4<SIZE && j+4<SIZE-s;i++,j++){
			if(blackplace[i][j]==1 && blackplace[i+1][j+1]==1 && blackplace[i+2][j+2]==1 && blackplace[i+3][j+3]==1 && blackplace[i+4][j+4]==1){
				printf("黑棋获胜\n");
				exit(1);
			}
			if(whiteplace[i][j]==1 && whiteplace[i+1][j+1]==1 && whiteplace[i+2][j+2]==1 && whiteplace[i+3][j+3]==1 && whiteplace[i+4][j+4]==1){
				printf("白棋获胜\n");
				exit(1);
			}
		}
	}                 //在斜率为负的直线上寻找连子
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(blackplace[i][j]==0){
				goto quit;
			}
		}
	}
	printf("平局\n");
	exit(1);
	quit:s=0;
}

void pvp(void){         //加载人人对战
	order();
}

void pve(void){        //加载人机对战
	choside();
}


void aisetblack(void){            
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(blackplace[i][j]==0){
				blackplace[i][j]=1;
				whiteplace[i][j]=2;
				board[i][j]=10;
				displayboard();
				goto out;
			}
		}
	}
	out:i=j=0;
}

void aisetwhite(void){
	int i,j;
	for(i=0;i<SIZE;i++){
		for(j=0;j<SIZE;j++){
			if(whiteplace[i][j]==0){
				whiteplace[i][j]=1;
				blackplace[i][j]=2;
				board[i][j]=12;
				displayboard();
				goto out;
			}
		}
	}
	out:i=j=0;
}
