#include<iostream>
#include<bits/stdc++.h>
#include<stdio.h> 
#include<WINDOWS.H>
#include<time.h>
#include<cstdlib>
#include<fstream>
#include<iomanip>

using namespace std;

void preemptivePriorityScheduling(){												//Preemptive Priority Scheuling Function
	
	int burstTime[20], process[20], waitingTime[20], turnaroundTime[20], priority[20];
    int i, j, limit, sum = 0, position, temp, check=0;
    float averageWaitTime, averageTurnaroundTime;
    
    cout<<"Enter total number of Processes => ";
    cin>>limit;
    
    for(i = 0; i < limit; i++){
        burstTime[i] = rand() %10 + 1;
        
        priority[i] = rand() %limit + 2;
            
		check = priority[i];
		
		if(priority[i-1] == check){
			priority[i] += 1;
		}
        
		process[i] = i + 1;
    }
    for(i = 0; i < limit; i++){
        position = i;
        for(j = i + 1; j < limit; j++){
            if(priority[j] < priority[position]){
                position = j;
            }
        }
        temp = priority[i];
        priority[i] = priority[position];
        priority[position] = temp; 
        temp = burstTime[i];
        burstTime[i] = burstTime[position];
        burstTime[position] = temp;
        temp = process[i];
        process[i] = process[position];
        process[position] = temp;
    }
    
    waitingTime[0] = 0;
    
    for(i = 1; i < limit; i++){
        waitingTime[i] = 0;
        for(j = 0; j < i; j++){
            waitingTime[i] = waitingTime[i] + burstTime[j];
        }
        sum = sum + waitingTime[i];
    }
    
    averageWaitTime = sum / limit;
    sum = 0;
    
    cout<<"\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\t Priority\n";
    for(i = 0; i < limit; i++){
        turnaroundTime[i] = burstTime[i] + waitingTime[i];
        sum = sum + turnaroundTime[i];
        printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\t\t\t %d\n", process[i], burstTime[i], waitingTime[i], turnaroundTime[i],priority[i]);
    }
    averageTurnaroundTime = sum / limit;
    
    cout<<"\nAverage Waiting Time: "<<averageWaitTime;
    cout<<"\nAverage Turnaround Time: "<<averageTurnaroundTime<<"\n\n";
    cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x";
    
}

void preemptiveShortestJobScheduling(){											     //Preemptive Shortest Job Scheduling Function
	
	int arrivalTime[10], burstTime[10], temp[10], w[10], t[10];
    int i, smallest, count = 0, time, limit;
    double waitTime = 0, turnaroundTime = 0, end;
    float averageWaitingTime, averageTurnaroundTime;
    
    cout<<"\nEnter the Total Number of Processes: ";
    cin>>limit; 
    //cout<<"\nEnter Details of "<<limit<<" Processes\n";
    
    for(i = 0; i < limit; i++){
    	arrivalTime[i]= rand() %8 +0;
            
		burstTime[i]= rand() %10 +1;
			
		temp[i] = burstTime[i];
    }
    
    burstTime[9] = 9999;  
    w[0] = 0;
    t[0] = 0;
    
 	for(time = 0; count != limit; time++){
        smallest = 9;
        for(i = 0; i < limit; i++){
            if(arrivalTime[i] <= time && burstTime[i] < burstTime[smallest] && burstTime[i] > 0){
                smallest = i;
            }
        }
        burstTime[smallest]--;
        if(burstTime[smallest] == 0){
            count++;
            end = time + 1;
            waitTime = waitTime + end - arrivalTime[smallest] - temp[smallest];
            turnaroundTime = turnaroundTime + end - arrivalTime[smallest];
        }
        w[i] = end - arrivalTime[smallest]- temp[smallest];
        t[i] = (end - arrivalTime[smallest]);
    }
    
    cout<<"\t\nBurst Time\t Arrival Time\t Turnaround Time\t Waiting Time\t\n";
    for(i = 0; i < limit; i++){
        //turnaroundTime[i] = burstTime[i] + waitingTime[i];
        //sum = sum + turnaroundTime[i];
        printf("\t\n%d\t\t %d\t\t %d\t\t\t %d", temp[i], arrivalTime[i], t[i], w[i]);
    }
    
    averageWaitingTime = waitTime / limit; 
    averageTurnaroundTime = turnaroundTime / limit;
    cout<<"\nAverage Waiting Time: "<<averageWaitingTime;
    cout<<"\nAverage Turnaround Time: "<<averageTurnaroundTime<<"\n\n";
    cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x";
    
}

void roundRobinScheduling(){														//Round Robin Scheduling Function
	
	int i, limit, total = 0, x, counter = 0, timeQuantum; 
	int waitTime = 0, turnaroundTime = 0, arrivalTime[10], burstTime[10], temp[10]; 
	float averageWaitTime, averageTurnaroundTime;
	
	cout<<"\nEnter Total Number of Processes: "; 
	cin>>limit;
	
	x = limit; 
	
	for(i = 0; i < limit; i++) {
		arrivalTime[i]= rand() %8 +0;
	    
		burstTime[i]= rand() %10 +1;
		
	    temp[i] = burstTime[i];
	}
	
	cout<<"\nEnter Time Quantum: "; 
	cin>>timeQuantum;
	 
	cout<<"\nProcess ID\t\tBurst Time\t Turnaround Time\t Waiting Time\n";
	
	for(total = 0, i = 0; x != 0;) { 
	    
		if(temp[i] <= timeQuantum && temp[i] > 0) { 
	        total = total + temp[i]; 
	        temp[i] = 0; 
	        counter = 1; 
	    } 
	    else if(temp[i] > 0) { 
	        temp[i] = temp[i] - timeQuantum; 
	        total = total + timeQuantum; 
	    } 
	    
	    if(temp[i] == 0 && counter == 1) { 
			x--; 
			printf("\nProcess[%d]\t\t%d\t\t %d\t\t\t %d", i + 1, burstTime[i], total - arrivalTime[i], total - arrivalTime[i] - burstTime[i]);
			waitTime = waitTime + total - arrivalTime[i] - burstTime[i]; 
			turnaroundTime = turnaroundTime + total - arrivalTime[i]; 
			counter = 0; 
	    }
		 
	    if(i == limit - 1) {
	        i = 0; 
	    }
	    else if(arrivalTime[i + 1] <= total) {
	        i++;
	    }
	    else {
	        i = 0;
	    }
	}
	
	averageWaitTime = waitTime * 1.0 / limit;
	averageTurnaroundTime = turnaroundTime * 1.0 / limit;
	
	cout<<"\n\nAverage Waiting Time: "<<averageWaitTime; 
	cout<<"\nAvg Turnaround Time: "<<averageTurnaroundTime<<"\n\n";
	cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x"; 
	
}

void shortestRemainingTimeScheduling(){												//Shortest Remaining Time Scheduling Function

	int a[10],b[10],x[10];
	int waiting[10],turnaround[10],completion[10];
	int i,j,smallest,count=0,time,n;
	double avg=0,tt=0,end;
	
	cout<<"\nEnter the number of Processes: ";
	cin>>n;
	
	for(i = 0 ; i < n ; i++){
	
		a[i]= rand() %8 +0;
	
		b[i]= rand() %10 +1;
	}
	
	for(i = 0 ; i < n ; i++){
		x[i]=b[i];
	}
	
	b[9]=9999;
	
	for(time=0; count!=n; time++){
		smallest=9;
		for(i = 0 ; i < n ; i++){
			if(a[i]<=time && b[i]<b[smallest] && b[i]>0 )
				smallest=i;
			}
		b[smallest]--;
		
		if(b[smallest] == 0){
			count++;
			end = time+1;
			completion[smallest] = end;
			waiting[smallest] = end - a[smallest] - x[smallest];
			turnaround[smallest] = end - a[smallest];
		}
	}
	
	cout<<"pid \t burst \t arrival \twaiting \tturnaround \tcompletion";
	
	for( i = 0 ; i < n ; i++){
		printf("\n %d \t   %d \t %d\t\t%d   \t\t%d\t\t%d",i+1,x[i],a[i],waiting[i],turnaround[i],completion[i]);
		avg = avg + waiting[i];
		tt = tt + turnaround[i];
	}
	
	//printf("\n  %lf   %lf",avg,tt);
	cout<<"\n\nAverage waiting time = "<<avg/n<<"\n";
	cout<<"Average Turnaround time = "<<tt/n<<"\n\n";
	cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x";
	
}

/*void rateMonotonicScheduling(){
	
}*/ 

void PreemptiveCPUScheduling(){														//Preemptive CPU Scheduling Menu-Driven Function
	
	HANDLE hConsole;
 	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	{
 		int choice;
 		SetConsoleTextAttribute(hConsole, 14);
		do{
			//puts( "\nPress " );
			printf("\n\n");
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [1] Preemptive Priority Scheduling                          |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [2] Preemptive Shortest Job Scheduling                      |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [3] Round Robin Scheduling                                  |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [4] Shortest Remaining Time Scheduling                      |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [5] Rate Monotonic Scheduling 		                    |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [6] Go Back To Main Page 		                    |" );
			puts("\t|-------------------------------------------------------------------|");
			cout<<"\n\t Enter here ---> ";
			
			cin>>choice;
			
			system( "cls" );
	
			switch( choice ){
				case 1:{
					preemptivePriorityScheduling();
					//cout<<"Preemptive Priority Scheduling";
					break;
				}
				case 2:{
				 	preemptiveShortestJobScheduling();
					//cout<<"Preemptive Shortest Job Scheduling";
				    break;
				}
				case 3:{
				    roundRobinScheduling();
					//cout<<"Round Robin Scheduling";
				    break;
				}
	            case 4:{
	            	shortestRemainingTimeScheduling();
					//cout<<"Shortest Remaining Time Scheduling";
	            	break;
				}
				case 5:{
	            	cout<<"Rate Monotonic Scheduling";
	            	break;
				}
				case 6:{
					cout<<"Exit";
					break;
				}
				default:{
					cout<<"Choose from the given options!";
				}
			}
		} while( choice != 6 ); 	
	}
}

void preemptivePrioritySchedulingReal(){											//Real-Life Scenario Function of Preemptive Priority Scheduling
	
	cout<<"\t\t\t ____________________________________________________\n";
	cout<<"\t\t\t|                                                    |\n";
	cout<<"\t\t\t| PREEMPTIVE PRIORITY SCHEDULNG - REAL LIFE SCENARIO |\n";
	cout<<"\t\t\t|____________________________________________________|\n\n";
	cout<<"\t ___________________________________________________________________________________________________\n";
	cout<<"\t|                                                                                                   |\n";
	cout<<"\t| In case of a natural disaster,a medical team is setup and they decide what plan to follow incase  |\n";
	cout<<"\t| of different situation. They decide that when a patient in critical condition(high risk rate)     |\n";
	cout<<"\t| comes to the emergency room they will leave all the routine checkup and first give priority to    |\n";
	cout<<"\t| the emergency room they will leave all the routine checkup and first give priority to the         |\n";
	cout<<"\t| critical patient.Incase two patients arrive at the same time,the patient with the high risk rate  |\n";
	cout<<"\t| is given more priority than a patient with lower risk rate beacuse giving him priority will       |\n";
	cout<<"\t| eventually help in saving his life.                                                               |\n";
	cout<<"\t|___________________________________________________________________________________________________|\n\n";
      
	int burstTime[20], process[20], waitingTime[20], turnaroundTime[20], priority[20];
	int i, j, limit, sum = 0, position, temp;
	float averageWaitTime, averageTurnaroundTime;
      
    cout<<"Enter Total Number of Patients: ";
    cin>>limit;
      
    //printf("\nEnter service time of patients \n", limit);
	for(i = 0; i < limit; i++){
	    
		printf("\nPatient[%d] Details\n", i + 1);
		cout<<"----------------------\n\n";
	    cout<<"Patient service Time: ";
	    cin>>burstTime[i];
	    cout<<"Priority of patient : ";
	    cin>>priority[i];
	    process[i] = i + 1;
	}
	
	for(i = 0; i < limit; i++){
	    position = i;
	    for(j = i + 1; j < limit; j++){
	        if(priority[j] < priority[position]){
	            position = j;
	        }
	    }
	    temp = priority[i];
	    priority[i] = priority[position];
	    priority[position] = temp; 
	    temp = burstTime[i];
	    burstTime[i] = burstTime[position];
	    burstTime[position] = temp;
	    temp = process[i];
	    process[i] = process[position];
	    process[position] = temp;
	}
	
	waitingTime[0] = 0;
	
	for(i = 1; i < limit; i++){
	    waitingTime[i] = 0;
	    for(j = 0; j < i; j++){
	        waitingTime[i] = waitingTime[i] + burstTime[j];
	    }
	    sum = sum + waitingTime[i];
	}
	
	averageWaitTime = sum / limit;
	sum = 0;
	
	cout<<"\nProcess ID\t\tBurst Time\t Waiting Time\t Turnaround Time\n";
	
	for(i = 0; i < limit; i++){
	    turnaroundTime[i] = burstTime[i] + waitingTime[i];
	    sum = sum + turnaroundTime[i];
	    
	    printf("\nProcess[%d]\t\t%d\t\t %d\t\t %d\n", process[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
	}
	
	averageTurnaroundTime = sum / limit;
	cout<<"\nAverage Waiting Time: "<<averageWaitTime;
	cout<<"\nAverage Turnaround Time: "<<averageTurnaroundTime<<"\n";
	cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x";

}

void preemptiveShortestJobSchedulingReal(){											//Real-Life Scenario Function of Preemptive Shortest Job Scheduling

	cout<<"\t\t\t _________________________________________________________\n";
	cout<<"\t\t\t|                                                         |\n";
	cout<<"\t\t\t| PREEMPTIVE SHORTEST JOB SCHEDULNG - REAL LIFE SCENARIO  |\n";
	cout<<"\t\t\t|_________________________________________________________|\n\n";
	cout<<"\t ___________________________________________________________________________________________________\n";
	cout<<"\t|                                                                                                   |\n";
	cout<<"\t| In a supermarket, we have two types of queues. One of them is the normal queue, while the other   |\n";
	cout<<"\t| is an express queue. The express queue acts as the shortest job first algorithm. When customers   |\n";
	cout<<"\t| come to check out, the customer with the least amount of products is asked to come in the         |\n";
	cout<<"\t| express queue because it is the shortest job.                                                     |\n";
	cout<<"\t|___________________________________________________________________________________________________|\n\n";
	
	int arrivalTime[10], burstTime[10], temp[10];
	int i, smallest, count = 0, time, limit;
	double waitTime = 0, turnaroundTime = 0, end;
	float averageWaitingTime, averageTurnaroundTime;
	
	cout<<"\nEnter the Total Number of Customers: ";
	cin>>limit;
	
	//printf("\nEnter numbers of queues\n", limit);
	for(i = 0; i < limit; i++){
		
	    cout<<"\nEnter Arrival Time: ";
	    cin>>arrivalTime[i];
	    cout<<"Enter service time of customers : ";
	    cin>>burstTime[i]; 
	    temp[i] = burstTime[i];
	}
	
	burstTime[9] = 9999;
	
	for(time = 0; count != limit; time++){
	    smallest = 9;
	    for(i = 0; i < limit; i++){
	        if(arrivalTime[i] <= time && burstTime[i] < burstTime[smallest] && burstTime[i] > 0){
	            smallest = i;
	        }
	    }
	    burstTime[smallest]--;
	    if(burstTime[smallest] == 0){
			count++;
			end = time + 1;
			waitTime = waitTime + end - arrivalTime[smallest] - temp[smallest];
			turnaroundTime = turnaroundTime + end - arrivalTime[smallest];
	    }
	}
	
	averageWaitingTime = waitTime / limit; 
	averageTurnaroundTime = turnaroundTime / limit;
	
	cout<<"\n\nAverage Waiting Time of customers: "<<averageWaitingTime<<"\n";
	cout<<"Average service Time of customers: "<<averageTurnaroundTime<<"\n";
	cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x";
	
}

void roundRobinSchedulingReal(){													//Real-Life Scenario Function of Round Robin Scheduling
	
	cout<<"\t\t\t ____________________________________________\n";
	cout<<"\t\t\t|                                            |\n";
	cout<<"\t\t\t| ROUND ROBIN SCHEDULNG - REAL LIFE SCENARIO |\n";
	cout<<"\t\t\t|____________________________________________|\n\n";
	cout<<"\t ____________________________________________________________________________________________________\n";
	cout<<"\t|                                                                                                    |\n";
	cout<<"\t| James visits the amusement park. At the amusement park,he goes on to his favourite ride, Crazy Bus.|\n";
	cout<<"\t| After he takes the ride for the first time he enjoys it a lot and decides to get another turn      |\n";
	cout<<"\t| to get the ride again he gets in a queue in which people are waiting in turn for the ride, we      |\n";
	cout<<"\t| have used round robin algorithm to show how he can take rides in that way.                         |\n";
	cout<<"\t|____________________________________________________________________________________________________|\n\n";
	
	int i, limit, total = 0, x, counter = 0, timeQuantum; 
	int waitTime = 0, turnaroundTime = 0, arrivalTime[10], burstTime[10], temp[10]; 
	float averageWaitTime, averageTurnaroundTime;
	
	cout<<"\nEnter Total Number of children: "; 
	cin>>limit;
	
	x = limit; 	
	
	for(i = 0; i < limit; i++) {
		
	    printf("\nEnter Details of child[%d]\n", i + 1);
	    cout<<"------------------------------\n\n";
	    cout<<"Arrival Time of child: ";
	    cin>>arrivalTime[i];
	    cout<<"Time taken for the child to ride the roller coaster: ";
	    cin>>burstTime[i];
	    temp[i] = burstTime[i];
	}
	 
	cout<<"\nEnter Time alloted for each ride: ";   //time quantum
	cin>>timeQuantum;
	
	printf("\nChild number\tTime taken for ride to complete\t Ride Time\t Waiting Time for ride\n");
	
	for(total = 0, i = 0; x != 0;) { 
	    if(temp[i] <= timeQuantum && temp[i] > 0){ 
			total = total + temp[i]; 
			temp[i] = 0; 
			counter = 1; 
	    } 
	    else if(temp[i] > 0){ 
			temp[i] = temp[i] - timeQuantum; 
			total = total + timeQuantum; 
	    } 
	    
	    if(temp[i] == 0 && counter == 1){ 
			x--; 
			printf("\nchild[%d]\t\t%d\t\t\t %d\t\t %d", i + 1, burstTime[i], total - arrivalTime[i], total - arrivalTime[i] - burstTime[i]);
			waitTime = waitTime + total - arrivalTime[i] - burstTime[i]; 
			turnaroundTime = turnaroundTime + total - arrivalTime[i]; 
			counter = 0; 
	    }
		 
	    if(i == limit - 1){
	          i = 0; 
	    }
	    else if(arrivalTime[i + 1] <= total){
	        i++;
	    }
	    else {
	        i = 0;
	    }
	} 
	
	averageWaitTime = waitTime * 1.0 / limit;
	averageTurnaroundTime = turnaroundTime * 1.0 / limit;
	
	cout<<"\n\nAverage Waiting Time: "<<averageWaitTime; 
	cout<<"\nAvg ride Time: "<<averageTurnaroundTime<<"\n";
	cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x";
	 
}

void shortestRemainingTimeSchedulingReal(){											//Real-Life Scenario Function of Shortest Remaining Time Scheduling
	
	cout<<"\t\t\t ________________________________________________________\n";
	cout<<"\t\t\t|                                                        |\n";
	cout<<"\t\t\t| SHORTEST REMAINinG TIME SCHEDULNG - REAL LIFE SCENARIO |\n";
	cout<<"\t\t\t|________________________________________________________|\n\n";
	cout<<"\t ___________________________________________________________________________________________________\n";
	cout<<"\t|                                                                                                   |\n";
	cout<<"\t| University can be hectic when a student has a lot of assignments to complete. Assignments tend to |\n";
	cout<<"\t| come with deadlines and this makes it even more difficult and stressful. So, when students have   |\n";
	cout<<"\t| a host of assignments with deadlines nearby, they start doing the assignments which have the      |\n";
	cout<<"\t| closest deadline. This is an example of how the shortest remaining time algorithm is implemented  |\n";
	cout<<"\t| in real life scenario.                                                                            |\n";
	cout<<"\t|___________________________________________________________________________________________________|\n\n";
	
	int a[10],b[10],x[10];
	int waiting[10],turnaround[10],completion[10];
	int i,j,smallest,count=0,time,n;
	double avg=0,tt=0,end;
	
	cout<<"\nEnter the number of Assignments: ";
	cin>>n;
	
	for( i = 0 ; i < n ; i++){
		printf("\nEnter arrival time of assignments %d : ",i+1);
		cin>>a[i];
	}
	
	for( i = 0 ; i < n ; i++){
		printf("\nEnter deadline of assignment %d : ",i+1);
		cin>>b[i];
	}
	
	for( i = 0 ; i < n ; i++){
		x[i]=b[i];
	}
	
	b[9]=9999;
	
	for(time=0 ; count!=n ; time++){
		smallest=9;
		for( i = 0 ; i < n ; i++){
			if(a[i]<=time && b[i]<b[smallest] && b[i]>0 ){
				smallest=i;
			}
		}
		b[smallest]--;
		
		if(b[smallest] == 0){
			count++;
			end=time+1;
			completion[smallest] = end;
			waiting[smallest] = end - a[smallest] - x[smallest];
			turnaround[smallest] = end - a[smallest];
		}
	}
	
	cout<<"\npid \tDue date \t arrival of assignment  \twaiting of assignment \t \tcompletion time of assignment";
	
	for( i = 0 ; i < n ; i++){
		printf("\n %d \t   %d \t\t\t %d\t\t\t\t%d  \t\t\t\t%d",i+1,x[i],a[i],waiting[i],completion[i]);
		avg = avg + waiting[i];
		tt = tt + turnaround[i];
	}
	
	//printf("\n  %lf   %lf",avg,tt);
	cout<<"\n\nAverage waiting time = "<<avg/n<<"\n";
	cout<<"Average Turnaround time = "<<tt/n<<"\n";
	cout<<"x----------------------------x-------------------------------x------------------------------x------------------------x";
	
}

/*void rateMonotonicSchedulingReal(){

}*/
void preemptiveCPUScheduling_RealLifeScenarios(){									//Preemptive CPU Scheduling (Real-Life Scenarios) Menu Driven Function
	
	HANDLE hConsole;
 	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
 	{
 		int choice;
 		SetConsoleTextAttribute(hConsole, 14);
		do{
			//puts( "\nPress " );
			printf("\n\n");
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [1] Preemptive Priority Scheduling                          |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [2] Preemptive Shortest Job Scheduling                      |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [3] Round Robin Scheduling                                  |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [4] Shortest Remaining Time Scheduling                      |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [5] Rate Monotonic Scheduling 		                    |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [6] Go Back To Main Page 		                    |" );
			puts("\t|-------------------------------------------------------------------|");
			cout<<"\n\t Enter here ---> ";
			
			cin>>choice;
			
			system( "cls" );
	
			switch( choice ){
				case 1:{
					preemptivePrioritySchedulingReal();
					//cout<<"Preemptive Priority Scheduling";
					break;
				}
				case 2:{
				 	preemptiveShortestJobSchedulingReal();
					//cout<<"Preemptive Shortest Job Scheduling";
				    break;
				}
				case 3:{
				    roundRobinSchedulingReal();
					//cout<<"Round Robin Scheduling";
				    break;
				}
	            case 4:{
	            	shortestRemainingTimeSchedulingReal();
					//cout<<"Shortest Remaining Time Scheduling";
	            	break;
				}
				case 5:{
	            	cout<<"Rate Monotonic Scheduling";
	            	break;
				}
				case 6:{
					cout<<"Exit";
					break;
				}
				default:{
					cout<<"Choose from the given options!";
				}
			}
		} while( choice != 6 ); 	
	}      
}
int main(){																			//main Function
	
	HANDLE hConsole;
	hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	{	
		SetConsoleTextAttribute(hConsole, 11);
		
		cout<<"\n\n\tPROJECT MADE BY : \n\t--------------------------\n\t|AFFAN GHAZALI| |18K-0171|\n\t|MUBBASHIR ALI| |18K-0233|\n\t--------------------------";
		cout<<"\n\n";
		system("PAUSE");
		
		int choice;
		
		do{
			//puts( "\nPress " );
			printf("\n\n");
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [1] Preemptive CPU Scheduling				    |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [2] Preemptive CPU Scheduling (Real-Life Scenarios)         |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [3] Gantt Chart Implementation of Algorithms                |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [4] Analysis of Preemptive CPU Scheduling                   |" );
			puts("\t|-------------------------------------------------------------------|");
			puts( "\t| Press [5] Exit 		                                    |" );
			puts("\t|-------------------------------------------------------------------|");
			cout<<"\n\t Enter here ---> ";
			
			cin>>choice;
			
			system( "cls" );
	
			switch( choice ){
				case 1:{
					PreemptiveCPUScheduling();
					//cout<<"Preemptive CPU Scheduling";
					break;
				}
				case 2:{
				 	preemptiveCPUScheduling_RealLifeScenarios();
					//cout<<"Preemptive CPU Scheduling (Real-Life Scenarios)";
				    break;
				}
				case 3:{
				    cout<<"Gantt Chart Implementation of Algorithms";
				    break;
				}
	            case 4:{
	            	cout<<"Analysis of Preemptive CPU Scheduling";
	            	break;
				}
				case 5:{
					cout<<"Exit";
					break;
				}
				default:{
					cout<<"Choose from the given options!";
				}
			}
		} while( choice != 5 );
	}
	return 0;		
}
