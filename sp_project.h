// sp_project.cpp : Defines the entry point for the console application.
//
// HMM.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include "vector"
#include "iostream"
#include <stdlib.h> 

#include <conio.h>
#include <sstream>
#include <list>
#pragma warning(disable:4996)

using namespace std;
#define ld long double


#define T 60 			//observations per sequence / frames to consider

#define N 5				//5 states
#define M 32			//32 possible outcomes
#define p 12			//12 CC
#define F 320			//frame size
#define K 32			// k of k means
#define slide 160		//how much to slide the window

#define unisize 10*25*T	//Universe Size

double norm_data[50000] ;	//data sample for one utterance.

static int trained_words = 7 ;		//This stores index of words trained . Initially words trained in model = 8 (0-7) 
//This is incremented when Live training is done.

double Uni[10][25+1][T][p+1] = {0} ;	//store final Ci for all digits. Feed to LBG
double Uni2d[unisize][p] = {0} ;	    //flattening Uni to 2D.
double test_Ci[T][p] = {0};				//storing test ci;

double codebook[K][p] = {0} ;			//store codebook


int obs[unisize] = {0};
int O[T+1] = {0} ;	  //store the observation seq of all Name - 1 observation for 1 Ci .
int obs2d[25*10][T] ;

ld Pi[N+1];				//store pi
ld A[N+1][N+1];			//store A, state transition mtrx
ld B[N+1][M+1];			//store B, output probability mtrx

ld A_bar[N+1][N+1];			//store fixed/improved model
ld B_bar[N+1][M+1];		
ld Pi_bar[N+1];

ld Pi_avg[N+1];				//To store avg of 20 models
ld A_avg[N+1][N+1];			
ld B_avg[N+1][M+1];

//ld P ;					//store prob of a word belonging to a model
ld p_star = 0;					  //store p* 		
ld prev_p_star =0;
int q_star_t[T+1] = {0};      //store q_t* 

ld alpha[T+1][N+1] ; //forward proc
ld beta[T+1][N+1] ;  //backward proc
ld gamma[T+1][N+1] ; //gamma proc
ld delta[T+1][N+1] ; //viterbi
int psi[T+1][N+1] ;	 //viterbi
ld zeta[T+1][T+1][N+1] ; //baum welsh
int check = 0;

#include "utility.h"
#include "get_ceps.h"
#include "lbg.h"

//step 1
void get_Uni(){		//Get Ci of all digits
	char filenum[3] ;	
	int k =0 , i = 0 ,j =0 ; 
	
	for(int d = 0 ; d<= trained_words ; d++){
		for(int u = 1 ; u <= 25; u++){
			char path[50] = "" ;
			if(d <= 7)
				strcat(path , "./train/train_") ; 
			else
				strcat(path , "./live_train/train_" ); 

			sprintf(filenum ,"%d", d) ; strcat(path, filenum) ; strcat(path, "_")  ;sprintf(filenum ,"%d", u) ; strcat(path, filenum) ;
			strcat(path, ".txt") ;
			//cout<< path << endl ;
			genrate_Uni(d , u , path);
		}
	}
}

void dump_Uni(){		//dump universe to csv. Only for debugging check
	FILE* fp_dump;
	fp_dump = fopen("Universe.csv", "w+") ;
	for(int d = 0 ; d<=trained_words ; d++){
		for(int u = 1 ; u <= 25; u++){
			for(int frame = 0; frame < T ; frame++){
				for(int x=1; x <= p ; x++){
					fprintf(fp_dump,"%lf,",Uni[d][u][frame][x]) ;
				}
				fprintf(fp_dump , "\n");
			}
		}
	}
	fclose(fp_dump);
	return;
}

void Uni_2d(){						// flatten it b4 calling LBG.
	int row = 0 ;
	for(int d = 0 ; d<= trained_words ; d++){
		for(int u = 1 ; u <= 25; u++){
			for(int frame = 0; frame < T ; frame++){
				for(int x=1; x <= p ; x++){
					Uni2d[row][x-1] = Uni[d][u][frame][x];
				}
				row++;
			}
		}
	}
	return ;
}

void gen_cb(){	
	get_codebook(); //get cb from lbg 
}

void dump_cb(){
	FILE* fp_dump ;
	fp_dump = fopen("Codebook.csv", "w+");
	for(int k = 0 ; k <32 ; k++){
		for(int i = 0; i <p ; i++){
			fprintf(fp_dump,"%lf,",codebook[k][i]) ;
		}
		fprintf(fp_dump , "\n");
	}
	fclose(fp_dump);	
	return ;
}

void read_cb(){	//read created codebook csv
	FILE* fp ;
	fp = fopen("Codebook.csv", "r");
	char line[200];
	double temp = 0;
	int row = 0, col = 0;

	while(fgets(line , sizeof(line) , fp)){  // reading CSV row by row
		char* tok ;
		tok = strtok(line , ",");			// tokenzing by delimiter 
		
		while(tok != NULL){	
			temp = atof(tok);	
			codebook[row][col] = temp;			//Reading Universe to 2d file.
			tok = strtok(NULL, ",");
			col++;
		}
		col = 0;
		row++;
	}
	fclose(fp);
	return ;
}

void get_obseravtion(){		//finds min dist index from codebook for all Universe - Creates Observation sequence
	double tok_wt[p] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};

	for(int i = 0 ; i < unisize ; i++){			//For each of Uni.

		double minDist = DBL_MAX ; int minDistIndx = -1 ;
		for(int j = 0; j< K; j++){					//iterate each of CB.
			double temp = 0;

			for(int ci = 0; ci < p ; ci++){			//cur frame

				temp += ( tok_wt[ci] * pow((Uni2d[i][ci] - codebook[j][ci] ),2) ) ;
			}
			if(temp < minDist){
				minDist=temp;
				minDistIndx=j+1;
			}
		}
		obs[i] = minDistIndx;
		//cout<< i+1 << " " << obs[i] << endl;
	}
	return ;
}

void get_O(int Name ,int utter){		//gets Obs seq for one utterance from obs after filling obs from get_observation()
	
	int ind = 1;						//Name - > 0-9 , utter -> 1-20.
	int s = T*(25*Name + utter-1) ;			

	for(int i = s ; i < s+T ; i++){
		O[ind++] = obs[i];								//store O[1] to O[T] 
	}
	return;
}

void dump_obs(){
	FILE* fp_dump ;
	fp_dump = fopen("Obs Seq.csv", "w+");
	int idx = 0 ;

	for(int d = 0 ; d<=trained_words ; d++){				//prints 200 lines , each of T obs seq.
		for(int u = 1 ; u <= 25; u++){
			for(int frame = 0; frame < T ; frame++){
					fprintf(fp_dump,"%d,", obs[idx++]) ;
			}
			fprintf(fp_dump , "\n");
		}
	}
	fclose(fp_dump);	
	return;
}

void read_obs(){ //read obs seq to obs2d
	FILE* fp ;
	fp = fopen("Obs Seq.csv", "r");
	char line[200];
	int temp = 0;
	int row = 0,col = 0;

	while(fgets(line , sizeof(line) , fp)){  // reading CSV row by row
		char* tok ;
		tok = strtok(line , ",");			// tokenzing by delimiter 
		
		while(tok != NULL){	
			temp = atoi(tok);	
			obs2d[row][col] = temp;			//Reading Universe to 2d file.
			tok = strtok(NULL, ",");
			col++;
		}
		col = 0; row++;
	}
	return ;
	fclose(fp);
}

void get_O2(int d, int u){		//fill O from obs2d got from reading obs seq.csv
	int idx = 1;
	int row = 25*d + u-1;

	for(int i = 0 ; i < T ; i++){
		O[idx++] = obs2d[row][i];						
	}
	return;
}



//---------------------------------------------------------------------------
//MODEL BUILD
void feed_forward_model() //this is biased model which works in lazy way
{
	for(int i=1;i<=N;i++) //assign the given values
		if(i==1) //make the first state as starting state
			Pi[i]=1.0;
		else
			Pi[i]=0;
    for(int i=1;i<=N;i++) //assign the given values for transition probability distribution
        for(int j=1;j<=N;j++)
			if(i==j&&i!=N)
				A[i][j]=0.8; //probability of being in current state
			else if(i==j&&i==N)
				A[i][j]=1; //forcing to end the transition in final state
			else if(j==i+1)
				A[i][j]=0.2; //probability to transit to next immediate state
			else
				A[i][j]=0; //probability to move to non immediate states
    for(int i=1;i<=N;i++) //assign the given values for observation symbol probability distribution
        for(int j=1;j<=M;j++)
            B[i][j]=1.0/M;

	return ;
}

//calculating alpha
ld forward_proc() //alpha computation
{
    for(int i=1;i<=N;i++) //initialization
        alpha[1][i]=Pi[i]*B[i][O[1]];

    for(int t=1;t<=T-1;t++) 
    {
        for(int j=1;j<=N;j++)
        {
            ld sum=0;
            for(int i=1;i<=N;i++)
            {
                sum+=alpha[t][i]*A[i][j];
            }

            alpha[t+1][j]=sum*B[j][O[t+1]];
			//if(alpha[t+1][j] <= 0)
				//alpha[t+1][j] = (ld)(pow((ld)10,(ld)-30)) ;
        }
    }
    ld P=0;
    for(int i=1;i<=N;i++) //estimate what is the probability that the observation sequence is from the current model
	{
        P+=alpha[T][i];
		//cout << alpha[T][i] << endl;
	}
	
    return P;
}

//calculating beta
void backward_proc() //beta computation
{
    for(int i=1;i<=N;i++) //initialization
        beta[T][i]=1;

    for(int t=T-1;t>=1;t--) //induction
    {
        for(int i=1;i<=N;i++)
        {
            ld sum=0;
            for(int j=1;j<=N;j++)
            {
                sum+=A[i][j]*B[j][O[t+1]]*beta[t+1][j];
            }
            beta[t][i]=sum;
        }
    }
    return ;
}


void gamma_proc() //gamma computation
{
	int *q,argmax=1; //q--> store the state which has maximum probability of occurence at time t.
	q=new int[T+1];
	ld devider=0; //used as devider in baye's theorem for computation of gamma
	for(int t=1;t<=T;t++)
	{
		for(int i=1;i<=N;i++) //compute it once for t
		{
			devider+=alpha[t][i]*beta[t][i];
		}
		argmax=1;
		for(int i=1;i<=N;i++)
		{
			gamma[t][i]=alpha[t][i]*beta[t][i]/devider;
			if(gamma[t][argmax]<gamma[t][i])
				argmax=i;
		}
		q[t]=argmax;
		devider=0;
	}
	return ;
}

//Soln-2 -calulating delta and psi
ld viterbi(){
	memset(q_star_t, 0, sizeof q_star_t);
	int argmax=0;			 // to store the argument which gives maximum probability
	for(int i=1 ;i<=N;i++)  //step 1 - initialization
	{
		delta[1][i]=Pi[i]*B[i][O[1]];
		//cout  << delta[1][i] << endl;
		psi[1][i]=0; //indicates, no state is yet assigned
	}
		
	//step 2 - Recursion
	for(int t=2;t<=T;t++) //recursion over time sequence
	{
		for(int j=1;j<=N;j++) // to store maximum probabilities
		{
			argmax=1; //assume the first state gives maximum probability
			for(int i=1;i<=N;i++)
			{
				if(delta[t-1][i]*A[i][j] > delta[t-1][argmax]*A[argmax][j]) //checking for maximum score
					argmax=i;							//argument which gives maximum score
			}
			delta[t][j] = delta[t-1][argmax]*A[argmax][j]*B[j][O[t]];
			psi[t][j]= argmax;					  //state which gives maximum probability
			//cout  << delta[t][j] << "  ";
		}
	}

	//step 3 - Termination
	argmax=1 ;
	for(int i=1; i <= N; i++){                 //to find the argmax for last time frame
		if(delta[T][i] > delta[T][argmax])
			argmax=i;
	}
	p_star= delta[T][argmax];				//holds best possible state's value

	q_star_t[T] = argmax;					//holds best possible state at last
	//cout << ob << " ---> " << q_star_t[0][os][T] << endl;
	//step 4 - Back Tracking the path
	for(int t=T-1; t>=1 ;t--){
		q_star_t[t]= psi[t+1][q_star_t[t+1]];
		//cout << t+1 << " --> " << q_star_t[0][os][t+1] << endl;
	}
	return p_star;
}

//soln 3 - BaumWelsh - calculating Zeta
void baum_welch_proc() //zeta computaion
{
	ld devider=0; //used as common devider just like in baye's theorem
	for(int t=1;t<=T-1;t++) //repeat this for all T-1 state transitions
	{
		devider=0;
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
				devider+=alpha[t][i]*A[i][j]*B[j][O[t+1]]*beta[t+1][j];  //Need to confirm if correct. 
		}
		for(int i=1;i<=N;i++)
		{
			for(int j=1;j<=N;j++)
				zeta[t][i][j]=(alpha[t][i]*A[i][j]*B[j][O[t+1]]*beta[t+1][j]) / devider;
		}
	}
}

void re_estimation() //re-estimate transition probabilities and observation symbol probabilities
{
	ld numerator = 0, denominator =0 ; //for re-estimation of transition probabilities
	for(int i=1;i<=N;i++) //re-estimation of Pi
		Pi_bar[i]=gamma[1][i];

	for(int i=1;i<=N;i++) //re-estimation of A
	{
		for(int j=1;j<=N;j++)
		{
			numerator=0;
			denominator=0;
			for(int t=1;t<=T-1;t++)	  
			{
				numerator+=zeta[t][i][j];
				denominator+=gamma[t][i];
			}
			A_bar[i][j]=numerator/denominator;
		}
	}
	ld maxValue=-1, sum=0;
	int  maxIndex=-1;
	for(int j=1;j<=N;j++) //re-estimation of B
	{
		maxValue=-1, maxIndex=-1, sum=0;
		for(int k=1;k<=M;k++)
		{
			numerator=0;
			denominator=0;
			for(int t=1;t<=T;t++)
			{
				if(O[t]==k)
					numerator+=gamma[t][j];

				denominator+=gamma[t][j];
			}
			if(denominator==0){
				//cout<<"ERROR : DENOM = 0 !!"<<endl; 
				B_bar[j][k] = 0;
			}
		
			else{
				B_bar[j][k]=numerator/denominator;
			}
			if(B_bar[j][k] > maxValue){
					maxValue = B_bar[j][k] ;
					maxIndex = k;
			}
			if(B_bar[j][k] < (ld)(pow((ld)10,(ld)-30))){		//< (ld)(pow((ld)10,(ld)-30)) ->replace with-> ==0
				sum += (ld)(pow((ld)10,(ld)-30)) - B_bar[j][k] ;
				B_bar[j][k] = (ld)(pow((ld)10,(ld)-30)) ;
			}
		}
		B_bar[j][maxIndex] -= sum  ;
	}
}

void replace_model() //replace old model (lambda) with new model (lambda-dash)
{
	//cout << "replacing the old model with new model" << endl;
	for(int i=1;i <= N;i++) 
        Pi[i]=Pi_bar[i];
	
    for(int i=1;i <= N;i++) 
        for(int j=1;j <= N;j++)
            A[i][j]=A_bar[i][j];

    for(int i=1;i <= N;i++) 
        for(int j=1;j <= M;j++)
            B[i][j]=B_bar[i][j];

	return;
}

//adding all converged model to avg
void add2avg(){

	for(int i=1;i<=N;i++)  //display initial state state distributions
	{
        Pi_avg[i] += Pi[i] ;
	}
    for(int i=1;i<=N;i++) //display state transition probabilities
	{
        for(int j=1;j<=N;j++)
		{
            A_avg[i][j] += A[i][j] ;	
		}
	
	}
    for(int i=1;i<=N;i++) //display observation symbol probability distribution
	{
        for(int j=1;j<=M;j++)
		{
            B_avg[i][j] += B[i][j] ;
		}
	}
	return;
}

//taking average of all models
void do_avg(int count){
	ld sum = 0; ld diff;
	for(int i=1;i<=N;i++)  
	{
        Pi_avg[i] = int( Pi_avg[i] / count ) ;
	}
    for(int i=1;i<=N;i++) 
	{
		sum = 0;
		int  maxIndex=-1; ld maxValue=-1;

        for(int j=1;j<=N;j++)
		{
            A_avg[i][j] = A_avg[i][j]/count*1.0 ;
			sum += A_avg[i][j];	//row-wise sum.

			if(A_avg[i][j] > maxValue){
				maxValue = A_avg[i][j] ;
				maxIndex = j;
			}
		}
		if(sum != 1){	//row sum not = 1 .
			//cout << "=========== RED FLAG ROW SUM != 1 of A_avg =========";
			diff = 1 - sum;
			A_avg[i][maxIndex] = A_avg[i][maxIndex] + diff;
		}
	}


    for(int i=1;i<=N;i++) 
	{
		sum = 0;
		int  maxIndex=-1; ld maxValue=-1;

        for(int j=1;j<=M;j++)
		{
            B_avg[i][j] = B_avg[i][j]/count*1.0 ;
			sum += B_avg[i][j];	

			if(B_avg[i][j] > maxValue){
				maxValue = B_avg[i][j] ;
				maxIndex = j;
			}
		}
		if(sum != 1){
			//cout << "=========== RED FLAG ROW SUM != 1 of B_avg =========";
			diff = 1 - sum ;
			B_avg[i][maxIndex] = B_avg[i][maxIndex] + diff;
		}
	}
	return;
}

//Main process. Converging the models
void RunModel(int iters){
	int itr = 0;         // iteration no.
	p_star=0;
	prev_p_star=-1;

	while(itr<=iters){
		itr++;
		forward_proc() ;
		backward_proc() ;
		gamma_proc() ;
		viterbi() ;
		baum_welch_proc();

		re_estimation();		// get re estimated model for current iteration
		replace_model();		//store re estimated model as original model to work on them again.
		
		if(abs(p_star - prev_p_star ) < (ld)(pow((ld)10,(ld)-50)) )break;  //check
		prev_p_star = p_star ;
	}
	cout << "final Prob p_star: " <<  p_star << endl;

	cout<< "Final State sequence : " << endl;
	for(int x = 1 ; x<=T ; x++)	
		cout<< q_star_t[x] << " " ;

	cout<<"\nTotal Iterations : "<<itr<<endl << endl;
	return;
}

//---------------------------------------------
//Before each model run , set all models to 0
void reset_arrays(){
	memset(alpha, 0, sizeof(alpha));
	memset(beta, 0, sizeof(beta));
	memset(gamma, 0, sizeof(gamma));
	memset(delta, 0, sizeof(delta));
	memset(psi, 0, sizeof(psi));
	memset(zeta, 0, sizeof(zeta));
	return;
}

void reset_avgModel(){
	memset(A_avg, 0, sizeof(A_avg));
	memset(B_avg, 0, sizeof(B_avg));
	memset(Pi_avg, 0, sizeof(Pi_avg));
	return;
}

//print final averaged models
void diplay_avgmodel() //display the whole model
{
	cout << "State probabilities: " << endl;
	for(int i=1;i<=N;i++)  //display initial state state distributions
	{
        cout << Pi_avg[i] << "\t";
	}
	cout << "\ntransition probabilities: " << endl;

    for(int i=1;i<=N;i++) //display state transition probabilities
	{
        for(int j=1;j<=N;j++)
		{
            cout << A_avg[i][j] << "\t";	
		}
		cout << endl;
	
	}
	cout << "observation symbol probability: " << endl;
	
    for(int i=1;i<=N;i++) //display observation symbol probability distribution
	{
        for(int j=1;j<=M;j++)
		{
            cout << B_avg[i][j] << "\t";
		}
		cout << endl;

	}
	return;
}

//--------------------------------------------

//Storing final models to file
void print_model(ofstream& out) //display the whole model
{
	//cout<< "Printing AVG of all models to output file : "<<endl;
	out<<endl<< "================================================================" <<endl;
	out << "State probabilities: " << endl;
	for(int i=1;i<=N;i++)  //display initial state state distributions
	{
        out << Pi_avg[i] << "\t";
	}
	out << "\ntransition probabilities: " << endl;

    for(int i=1;i<=N;i++) //display state transition probabilities
	{
        for(int j=1;j<=N;j++)
		{
            out << A_avg[i][j] << "\t";	
		}
		out << endl;
	
	}
	out << "observation symbol probability: " << endl;
	
    for(int i=1;i<=N;i++) //display observation symbol probability distribution
	{
        for(int j=1;j<=M;j++)
		{
            out << B_avg[i][j] << "\t";
		}
		out << endl;
	}
	return;
}
void print_avg_a(ofstream& out){
	 for(int i=1;i<=N;i++) 
	{
        for(int j=1;j<=N;j++)
		{
            out << A_avg[i][j] << "\t";	
		}
		out << endl;
	}
}
void print_avg_b(ofstream& out){
	for(int i=1;i<=N;i++) 
	{
        for(int j=1;j<=M;j++)
		{
            out << B_avg[i][j] << "\t";
		}
		out << endl;
	}
}
void print_avg_pi(ofstream& out){
	for(int i=1;i<=N;i++)  //display initial state state distributions
	{
        out << Pi_avg[i] << "\t";
	}
}



//------------------------------------------------------------------------------------

//Live Testing functions
void live_testCi(const char* path){		//Get Ci of test txt
	genrate_Uni(-2 , -1 , path);	
}

void offline_testCi(const char* path){
	genrate_Uni(-2 , 0 , path);
}

//Generate obs seq of test file
void get_test_O(){
	double tok_wt[p] = {1.0, 3.0, 7.0, 13.0, 19.0, 22.0, 25.0, 33.0, 42.0, 50.0, 56.0, 61.0};

	for(int i = 0 ; i < T ; i++){			//For each of frame of test.

		double minDist = DBL_MAX ; int minDistIndx = -1 ;

		for(int j = 0; j< K; j++){				//iterate each of CB.
			double temp = 0;

			for(int ci = 0; ci < p ; ci++){			//cur frame
				temp += ( tok_wt[ci] * pow((test_Ci[i][ci] - codebook[j][ci] ),2) ) ;
			}
			//cout<< j+1 << " " << temp << endl;

			if(temp < minDist){
				minDist= temp;
				minDistIndx= j+1;
			}
		}
		O[i+1] = minDistIndx;
		//cout<< i+1 << " " << O[i] << endl;
	}
	return ;

}

//------------------Pipelines------------

void pipeline2obs2(){ 
	get_Uni();	
	dump_Uni();
	Uni_2d();	
	gen_cb(); dump_cb() ; read_cb();	//create own codebook for base training
	get_obseravtion();	
	dump_obs() ;	
}

void pipeline2obs3(){ //for live training, no need to update codebook
	get_Uni();	
	Uni_2d();	
	read_cb();	
	get_obseravtion();	
	dump_obs() ;	
}



//-------------------------------------------------------------

int testing(int choice)
{
	int total_names = 10;
	const char *temp[10] = {"Pranjal","Aaru","Ishita","Mukund","Virat","Sarthak","Madhuri","Priyansh","Rohan","Kirti" } ;
	vector<std::string> names;

	for(int i =0 ; i<10 ;i++)
		names.push_back(temp[i]);

	
	//-------------------Base Training--------------------
	if(choice == 1){

		cout<< "Getting Observation sequence from samples..........\n";
		pipeline2obs2();
		read_obs() ;

		char filenum[3] ;
		ofstream a_avg ; ofstream b_avg ; ofstream pi_avg ; //FILE* out;
		ofstream out;
	
		int iters = 200;	int utters = 25;

		char output[30] = "output.txt" ;
		out.open(output);

		for(int d = 0 ; d <=trained_words ; d++){
			char a[30] = "./models/a_avg_";			//storing avg models of names with their index number
			char b[30] = "./models/b_avg_";   
			char pi[30] = "./models/pi_avg_";   
			sprintf(filenum ,"%d", d) ;

			strcat(a, filenum) ; strcat(b, filenum) ;strcat(pi, filenum) ;	
			strcat(a, ".txt") ; strcat(b, ".txt") ;strcat(pi, ".txt") ;
			a_avg.open(a); b_avg.open(b); pi_avg.open(pi);

			reset_avgModel(); //resets avgmodel arrays to 0;
			cout<< "Training Model for Name: " << names[d] << endl;

			for(int u = 1 ; u <= utters ; u++){
				reset_arrays();			//resets all arrays to 0;
				feed_forward_model();

				get_O2(d,u);	       //fills O with current obs seq.				
				printO();

				cout<< "utterance : " << u << "......" << "  " ;
				RunModel(iters);
				add2avg();	            //sum all models into avg model arrays
			}
			do_avg(utters);		         //get avg of 20 models - now we have A_avg,B_avg,Pi_avg as best model

			cout<<endl;
			out<< endl<< "Avg Model for Name: " << names[d] <<endl ;
			print_model(out);	
			print_avg_a(a_avg);  print_avg_b(b_avg);  print_avg_pi(pi_avg);	//print in respective model files
			a_avg.close() ; b_avg.close() ; pi_avg.close();

		}
		out.close();

	}
	//-----------------OFFLINE TESTING-------------------------
	else if(choice == 2){

		read_cb() ;		//read codebook
		int utter ;  ld fp; //forward proc value store
		char filenum[3] ;
		ld C =0 , c = 0; 
		double acc , final_acc ;

		for(int name = 0 ; name <= trained_words ; name++){

			for(utter = 1; utter <= 5; utter++){
				//open file
				char path[80] = "./tests/test_";	

				sprintf(filenum ,"%d", name);    strcat(path, filenum) ;	
				strcat(path, "_") ;
				sprintf(filenum ,"%d", utter);		strcat(path, filenum) ;
				strcat(path, ".txt") ;

				offline_testCi(path);	
				get_test_O() ;	

				cout<< "testing Name :" << names[name] << " , utterance : "<< utter << endl;
				ld best_p = 0 ; int d = 0;

				for(int m= 0 ; m <= trained_words ; m++){ //checking
					get_avg_model(m); 

					cout<<endl<< "Prob of test word being Name "<< names[m] << " = ";

					fp = forward_proc();
					cout << fp << endl;
					if(fp > best_p ){
						best_p = fp;
						d =  m;
					}	
				}
				cout << "Predicted Name : " << names[d] << endl <<endl ;
				if(d == name){
					c++ ; C++;
				}
			}
			acc = c/5.0;
			cout << "Accuracy for Name " << names[name] << " = " << acc*100 << "%\n";
			c = 0;
			
		}
		final_acc = C/((trained_words+1)*5.0) ;
		cout << "\nOverall Accuracy of Model : " << final_acc*100 << "%\n" ;

	}

	//------------------Live testing-------------------

	else if(choice == 3){
		
		char path[30] = "livetest.txt";	 //generate test
		char cmd[100] = "Recording_Module.exe 3 i.wav ";

		strcat(cmd, path) ;
		system(cmd);

		live_testCi(path);	//get Ci of test.
		read_cb() ;		//read codebook

		get_test_O() ;		//fills O with test observation.
		printO() ;

		ld fp; ld best_p = 0 ; int name = 0;

		for(int m= 0 ; m <= trained_words ; m++){		//Name
			get_avg_model(m);
	
			fp = forward_proc();

			if(fp > best_p ){
				best_p = fp;
				name =  m;
			}
		}

		return name;
	}
	//-------------------live training---------------
	
	else if(choice ==4){
		trained_words++ ;	//This is index of new name to train

		pipeline2obs3();	
		read_obs() ;		//now obs seq.csv has obs sequence for all words including new word.


		char filenum[3] ;
		ofstream a_avg ; ofstream b_avg ; ofstream pi_avg ; //FILE* out;
		ofstream out;
	
		int iters = 200;	int utters = 25;

		char a[30] = "./models/a_avg_" ;			//storing avg models of names with their index number
		char b[30] = "./models/b_avg_" ;   
		char pi[30] = "./models/pi_avg_" ;   
		sprintf(filenum ,"%d", trained_words) ;

		strcat(a, filenum) ; strcat(b, filenum) ; strcat(pi , filenum) ;	
		strcat(a, ".txt") ; strcat(b, ".txt") ; strcat(pi , ".txt") ;
		a_avg.open(a); b_avg.open(b); pi_avg.open(pi);

		reset_avgModel(); //resets avgmodel arrays to 0;
		
		for(int u = 1 ; u <= utters ; u++){
			reset_arrays();			//resets all arrays to 0;
			feed_forward_model();

			get_O2(trained_words,u);	       //fills O with current obs seq.				
			printO();

		
			RunModel(iters);
			add2avg();	            //sum all models into avg model arrays
		}
		do_avg(utters);		         //get avg of 20 models - now we have A_avg,B_avg,Pi_avg as best model

		cout<<endl;
		
		print_avg_a(a_avg);  print_avg_b(b_avg);  print_avg_pi(pi_avg);	//store in respective model files
		a_avg.close() ; b_avg.close() ; pi_avg.close();

	}


	//------------------------------
	else{
		cout << "Wrong choice !! Exiting !!!";
		return 0;
	}

	//-----------------------------------------------------
	return 0;
}


