#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<time.h>

void bProcessCreated();
void bDisplay();
void ExecuteRRAlgorithm();
void Restore();
void ExecutePriorityAlgorithm();


struct PCB{
	int m_iProcessID;     //���̺�
	char m_strProcessName[10];   //������
	int m_iCPUTime;
	int m_iRemainingTime;
	int m_iState;
	int m_iPriority;
	struct PCB *next;
}PCB;

struct PCB *pReadyQueue=NULL;          //ȫ�ֱ���
int iProcessID=0;


int main(){
	int i;
	bProcessCreated();
	bDisplay();
	printf("��ѡ����ȷ�ʽ��1 ʱ��Ƭ   2 ���ȼ�\n");
	scanf("%d",&i);
	switch(i){
		case 1:
		  ExecuteRRAlgorithm();
          Restore();
		  break;
		case 2:
          ExecutePriorityAlgorithm();
		  break;
	}
}



void bProcessCreated(){
    srand(time(NULL));
	char strProcessName[10];
	int iCPUTime;
	struct PCB *pTemp;
	int iPriority;
	struct PCB *pCurrentProcess;
	int iProcessNumber;

	printf("������Ҫ�����Ľ��̸���:");
	scanf("%d",&iProcessNumber);
	for(int i=0;i<iProcessNumber;i++){
		pTemp=new struct PCB;

		pTemp->m_iProcessID=iProcessID;    //�½��̵Ľ��̺�
		iProcessID++;
		printf("�������������");
		scanf("%s",&strProcessName);
		printf("���������ռ��cpu��ʱ�䣺");
		scanf("%d",&iCPUTime);
		iPriority=rand()%10;
		printf("������ɵ����ȼ�Ϊ:%d\n",iPriority);
		printf("\n");
		pTemp->m_iCPUTime=iCPUTime;
		pTemp->m_iPriority=iPriority;
		pTemp->m_iState=0;
		pTemp->m_iRemainingTime=iCPUTime;
		strcpy(pTemp->m_strProcessName,strProcessName);

		if(iProcessID==1){
			pReadyQueue=pTemp;
			pCurrentProcess=pTemp;
			pCurrentProcess->next=NULL;
		}
		else{
			pCurrentProcess->next=pTemp;
			pCurrentProcess=pTemp;
			pCurrentProcess->next=NULL;
		}

	}
}




void bDisplay(){
	struct PCB *pTemp=pReadyQueue;
	if(pTemp==NULL)
		printf("no process exits\n");
	else{
		printf("����ID\t\t��������\t\t��Ҫcpuʱ��\t\t���ȼ�\n");
		while(pTemp!=NULL){
			printf("%d\t\t   %s\t\t\t%d\t\t\t%d\n",pTemp->m_iProcessID,pTemp->m_strProcessName,pTemp->m_iCPUTime,pTemp->m_iPriority);
			pTemp=pTemp->next;
		}
	}
}


void ExecuteRRAlgorithm(){
	int iQuantum;
	bool bAllRunned=false;
	struct PCB *pTemp=pReadyQueue;
	if(pTemp==NULL){
		printf("no process exits\n");
	}
	iQuantum=rand()%6;
	printf("�������ʱ��ƬΪ����λs����%d\n",iQuantum);
	printf("ʱ��Ƭ��ת�����㷨RR�����Ƚ������:\n");
	printf("����ID\t��������   ����ʱ��\n");
	while(!bAllRunned){
		bAllRunned=true;
		pTemp=pReadyQueue;
		while(pTemp!=NULL){
			if(pTemp->m_iRemainingTime>=iQuantum){
				pTemp->m_iRemainingTime=pTemp->m_iRemainingTime-iQuantum;
				printf("%d\t %s\t %d\n",pTemp->m_iProcessID,pTemp->m_strProcessName,iQuantum);
				pTemp=pTemp->next;
				bAllRunned=false;
			}
			else if(0<pTemp->m_iRemainingTime&&pTemp->m_iRemainingTime<iQuantum){
				printf("%d\t %s\t %d\n",pTemp->m_iProcessID,pTemp->m_strProcessName,pTemp->m_iRemainingTime);
				pTemp->m_iRemainingTime=0;
				pTemp=pTemp->next;
				bAllRunned=false;
			}
            else{
                pTemp=pTemp->next;
            }
		}
	}
	printf("�������!\n");
}


void Restore()
{
	struct PCB*pTemp=NULL;
	pTemp=pReadyQueue;
	while(pTemp!=NULL)
	{
		pTemp->m_iRemainingTime=pTemp->m_iCPUTime;
		pTemp=pTemp->next;
	}
}
void ExecutePriorityAlgorithm(){
	struct PCB*pTemp=NULL;
	struct PCB*pFirst=NULL;
	struct PCB*pSecond=NULL;
	struct PCB temp;
	pTemp=pReadyQueue;
	pFirst=pTemp;
	pSecond=pFirst->next;
	while(pFirst!=NULL)
	{
		while(pSecond!=NULL)
		{
			if(pFirst->m_iPriority<pSecond->m_iPriority)
			{
				temp.m_iCPUTime=pSecond->m_iCPUTime;
				temp.m_iPriority=pSecond->m_iPriority;
				temp.m_iProcessID=pSecond->m_iProcessID;
				temp.m_iRemainingTime=pSecond->m_iRemainingTime;
				temp.m_iState=pSecond->m_iState;
				strcpy(temp.m_strProcessName,pSecond->m_strProcessName);
				pSecond->m_iCPUTime=pFirst->m_iCPUTime;
				pSecond->m_iPriority=pFirst->m_iPriority;
				pSecond->m_iProcessID=pFirst->m_iProcessID;
				pSecond->m_iRemainingTime=pFirst->m_iRemainingTime;
				pSecond->m_iState=pFirst->m_iState;
				strcpy(pSecond->m_strProcessName,pFirst->m_strProcessName);
				pFirst->m_iCPUTime=temp.m_iCPUTime;
				pFirst->m_iPriority=temp.m_iPriority;
				pFirst->m_iProcessID=temp.m_iProcessID;
				pFirst->m_iRemainingTime=temp.m_iRemainingTime;
				pFirst->m_iState=temp.m_iState;
				strcpy(pFirst->m_strProcessName,temp.m_strProcessName);
			}
			pSecond=pSecond->next;
		}
		pFirst=pFirst->next;
		if(pFirst!=NULL)
			pSecond=pFirst->next;
		else
			pSecond=NULL;
	}
	printf("���ȼ��㷨(Priority),���Ƚ������:\n");
	printf("����ID\t��������   ����ʱ��\n");
	while(pTemp!=NULL){
		printf("%d\t %s\t %d\n",pTemp->m_iProcessID,pTemp->m_strProcessName,pTemp->m_iRemainingTime);
		pTemp=pTemp->next;
	}
}




