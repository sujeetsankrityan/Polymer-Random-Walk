# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
#define BOX_size 10
#define MC_STEP 1000
#define MAX 100000

int crowd(int a, int b,int c);
int lattice[BOX_size][BOX_size][BOX_size];
int boundry = (BOX_size-1);
int main() {
  srand(time(NULL));
  int count_x,count_y,count_z,count=0,count1=0,count2=0,total_nbd;
  int i,j,k,j1,k1,a,b,c;
  double r,r1,r2,r3,ran;
  //int lattice[BOX_size][BOX_size][BOX_size];
  int x=0,y=0,z=0;
  int x1,y1,z1,x2,y2,z2;
  int count_step=1,count_site=1,repeat=0;
  int nbd_x1,nbd_y1,nbd_z1,nbd_x2,nbd_y2,nbd_z2,nbd=0;
  int tmp_x,tmp_y,tmp_z,site_id;
  int neighbour[6][3];
  int polymer[MAX][9];

  FILE *fp,*fp1;
  fp = fopen ("tt1","w");
  fp1 = fopen ("tt2","w");

  //Assigning initial value to lattice
  for(count_x=0;count_x<BOX_size;count_x++){
    for(count_y=0;count_y<BOX_size;count_y++){
      for(count_z=0;count_z<BOX_size;count_z++){
	lattice[count_x][count_y][count_z]=0;
      }
    }
  }
  for (k1=0;k1<MAX;k1++) {
  for (j1=0;j1<9;j1++) {polymer[k1][j1]==0;}}


  r1 = (double)rand() / (double)RAND_MAX ;
  r2 = (double)rand() / (double)RAND_MAX ;
  r3 = (double)rand() / (double)RAND_MAX ;
  x = r1*BOX_size,y = r2*BOX_size, z = r3*BOX_size; 
  //x=2;y=4;z=6;
  polymer[0][0]=1;polymer[0][1]=x;polymer[0][2]=y;polymer[0][3]=z;
  fprintf(fp,"%d %d %d \n",x,y,z);
  //printf("%d %d %d %d\n",polymer[0][0],polymer[0][1],polymer[0][2],polymer[0][3]);
  lattice[x][y][z]=1;
  x1=x,y1=y,z1=z;
  // x2=x,y2=y,z2=z;
  for (i=0;i<MC_STEP;i++) {

    //printf("%d %d %d %d\n",i,x,y,z);




    for (k=0;k<6;k++) {
      for (j=0;j<3;j++) {neighbour[k][j]==0;}}
    total_nbd=0;

    x=x+1;
    if (x>boundry) {x = x-BOX_size;}
    neighbour[0][1] = crowd(x,y,z);total_nbd+=crowd(x,y,z);neighbour[0][2] = total_nbd;
    x=x1;
    x=x-1;
    if (x<0) {x = x+BOX_size;}
    neighbour[1][1] = crowd(x,y,z);total_nbd+=crowd(x,y,z);neighbour[1][2] = total_nbd;
    x=x1;
    y=y+1;
    if (y>boundry) {y = y-BOX_size;}
    neighbour[2][1] = crowd(x,y,z);total_nbd+=crowd(x,y,z);neighbour[2][2] = total_nbd;
    y=y1;
    y=y-1;
    if (y<0) {y = y+BOX_size;}
    neighbour[3][1] = crowd(x,y,z);total_nbd+=crowd(x,y,z);neighbour[3][2] = total_nbd;
    y=y1;
    z=z+1;
    if (z>boundry) {z = z-BOX_size;}
    neighbour[4][1] = crowd(x,y,z);total_nbd+=crowd(x,y,z);neighbour[4][2] = total_nbd;
    z=z1;
    z=z-1;
    if (z<0) {z = z+BOX_size;}
    neighbour[5][1] = crowd(x,y,z);total_nbd+=crowd(x,y,z);neighbour[5][2] = total_nbd;
    z=z1;


    //for (k=0;k<6;k++){printf ("%d %f    ",neighbour[k][2],((double)neighbour[k][2]/total_nbd));}
    //printf("   %d\n",total_nbd);
    

    count_step+=1;
    r = (double)rand() / (double)RAND_MAX ;
    //printf("%f\n",r);
    if (r<=((double)neighbour[0][2]/total_nbd)) {
      if(neighbour[0][1]==0) {continue;}
      x=x+1; 
      if (x>boundry) {x = x-BOX_size;}
      if (lattice[x][y][z]==1) {x=x1;}
      if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;polymer[(count_site-1)][0]=count_site;polymer[(count_site-1)][1]=x;polymer[(count_site-1)][2]=y;polymer[(count_site-1)][3]=z;polymer[(count_site-2)][4]=1;polymer[(count_site-2)][7]=1;polymer[(count_site-2)][8]=1;fprintf(fp,"%d %d %d \n",x,y,z);}
    }
    else if (r>((double)neighbour[0][2]/total_nbd) && r<=((double)neighbour[1][2]/total_nbd)) {
      if(neighbour[1][1]==0) {continue;}
      x=x-1;
      if (x<0) {x = x+BOX_size;}
      if (lattice[x][y][z]==1) {x=x1;}
      if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;polymer[(count_site-1)][0]=count_site;polymer[(count_site-1)][1]=x;polymer[(count_site-1)][2]=y;polymer[(count_site-1)][3]=z;polymer[(count_site-2)][4]=-1;polymer[(count_site-2)][7]=-1;polymer[(count_site-2)][8]=1;fprintf(fp,"%d %d %d \n",x,y,z);}
    }
    else if (r>((double)neighbour[1][2]/total_nbd) && r<=((double)neighbour[2][2]/total_nbd)) {
      if(neighbour[2][1]==0) {continue;}
      y=y+1; 
      if (y>boundry) {y = y-BOX_size;}
      if (lattice[x][y][z]==1) {y=y1;}
      if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;polymer[(count_site-1)][0]=count_site;polymer[(count_site-1)][1]=x;polymer[(count_site-1)][2]=y;polymer[(count_site-1)][3]=z;polymer[(count_site-2)][5]=1;polymer[(count_site-2)][7]=1;polymer[(count_site-2)][8]=2;fprintf(fp,"%d %d %d \n",x,y,z);}
  }

    else if (r>((double)neighbour[2][2]/total_nbd) && r<=((double)neighbour[3][2]/total_nbd)) {
      if(neighbour[3][1]==0) {continue;}
      y=y-1;
      if (y<0) {y = y+BOX_size;}
      if (lattice[x][y][z]==1) {y=y1;}
      if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;polymer[(count_site-1)][0]=count_site;polymer[(count_site-1)][1]=x;polymer[(count_site-1)][2]=y;polymer[(count_site-1)][3]=z;polymer[(count_site-2)][5]=-1;polymer[(count_site-2)][7]=-1;polymer[(count_site-2)][8]=2;fprintf(fp,"%d %d %d \n",x,y,z);}
    }
    else if (r>((double)neighbour[3][2]/total_nbd) && r<=((double)neighbour[4][2]/total_nbd)) {
      if(neighbour[4][1]==0) {continue;}
      z=z+1; 
      if (z>boundry) {z = z-BOX_size;}
      if (lattice[x][y][z]==1) {z=z1;}
      else if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;polymer[count_site-1][0]=count_site;polymer[count_site-1][1]=x;polymer[count_site-1][2]=y;polymer[count_site-1][3]=z;polymer[(count_site-2)][6]=1;polymer[(count_site-2)][7]=1;polymer[(count_site-2)][8]=3;fprintf(fp,"%d %d %d \n",x,y,z);}
    }
    else if (r>((double)neighbour[4][2]/total_nbd)) {
      if(neighbour[5][1]==0) {continue;}
      z=z-1;
      if (z<0) {z = z+BOX_size;}
      if (lattice[x][y][z]==1) {z=z1;}
      else if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;polymer[count_site-1][0]=count_site;polymer[count_site-1][1]=x;polymer[count_site-1][2]=y;polymer[count_site-1][3]=z;polymer[(count_site-2)][6]=-1;polymer[(count_site-2)][7]=-1;polymer[(count_site-2)][8]=3;fprintf(fp,"%d %d %d \n",x,y,z);}
    }
    
    

    if (x==x1 && y==y1 && z==z1){repeat+=1;}
    if (repeat>10000) {break;}
    //if (repeat>1000 && count1==1) {break;}
    //if (repeat>500 && count1==0) {count1+=1,x=x2,y=y2,z=z2,fprintf(fp,"\n\n");}
    x1=x,y1=y,z1=z;
    //printf(" %d      %d %d %d \n",i,x,y,z);
  }





/*********************************************************************************************************************************/
//Reptation  movement of polymer chain....
  /*********************************************************************************************************************************/
  srand(time(NULL));
  int rep_x,rep_y,rep_z,k2,count_rep=0;
  int orep_x,orep_y,orep_z,erep_x,erep_y,erep_z;
  double ran1;
  k1=0;
  printf("%d\n",count_site);
  printf("%d %d %d \n %d %d %d\n",polymer[0][1],polymer[0][2],polymer[0][3],polymer[count_site-1][1],polymer[count_site-1][2],polymer[count_site-1][3]);

  for (i=0;i<=1000;i++) {
    ran = (double)rand() / (double)RAND_MAX ;
    ran1 = (double)rand() / (double)RAND_MAX ;
    printf("\n\n");
    
    for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
    printf("%f %f\n",ran,ran1);
    
    if(ran<=0.5) {
    orep_x=polymer[0][1];orep_y=polymer[0][2];orep_z=polymer[0][3];
    erep_x=polymer[count_site-1][1];erep_y=polymer[count_site-1][2];erep_z=polymer[count_site-1][3];
      
      if(ran1<=0.166) {
	printf("-----------------HERE-----------------XX");
	rep_x=orep_x+1;rep_y=orep_y;rep_z=orep_z;
	if (rep_x>=BOX_size) {rep_x=rep_x-BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++XXX+++++++++++++\n");
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	  for (k1=count_site-1;k1>0;k1--) {polymer[k1][1]=polymer[k1-1][1];polymer[k1][2]=polymer[k1-1][2];polymer[k1][3]=polymer[k1-1][3];}
	  polymer[0][1]=rep_x;polymer[0][2]=rep_y;polymer[0][3]=rep_z;
	}}
      else if(ran1>0.166 && ran1<=0.33) {
	printf("-----------------HERE-----------------xx");
	rep_x=orep_x-1;rep_y=orep_y;rep_z=orep_z;
	if (rep_x<0) {rep_x=rep_x+BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++xxxx+++++++++++++\n");
	  for (k1=count_site-1;k1>0;k1--) {polymer[k1][1]=polymer[k1-1][1];polymer[k1][2]=polymer[k1-1][2];polymer[k1][3]=polymer[k1-1][3];}
	  polymer[0][1]=rep_x;polymer[0][2]=rep_y;polymer[0][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.33 && ran1<=0.5) {
	printf("-----------------HERE-----------------YY");
	rep_x=orep_x;rep_y=orep_y+1;rep_z=orep_z;
	//for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
	if (rep_y>=BOX_size) {rep_y=rep_y-BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++YYYY+++++++++++++\n");
	  for (k1=count_site-1;k1>0;k1--) {polymer[k1][1]=polymer[k1-1][1];polymer[k1][2]=polymer[k1-1][2];polymer[k1][3]=polymer[k1-1][3];}
	  polymer[0][1]=rep_x;polymer[0][2]=rep_y;polymer[0][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.5 && ran1<=0.66) {
	printf("-----------------HERE-----------------yy");
	rep_x=orep_x;rep_y=orep_y-1;rep_z=orep_z;
	if (rep_y<0) {rep_y=rep_y+BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++yyyy+++++++++++++\n");
	  for (k1=count_site-1;k1>0;k1--) {polymer[k1][1]=polymer[k1-1][1];polymer[k1][2]=polymer[k1-1][2];polymer[k1][3]=polymer[k1-1][3];}
	  polymer[0][1]=rep_x;polymer[0][2]=rep_y;polymer[0][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.66 && ran1<=0.83) {
	printf("-----------------HERE-----------------ZZ");
	rep_x=orep_x;rep_y=orep_y;rep_z=orep_z+1;
	//for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
	if (rep_z>=BOX_size) {rep_z=rep_z-BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++ZZZZ+++++++++++++\n");
	  for (k1=count_site-1;k1>0;k1--) {polymer[k1][1]=polymer[k1-1][1];polymer[k1][2]=polymer[k1-1][2];polymer[k1][3]=polymer[k1-1][3];}
	  polymer[0][1]=rep_x;polymer[0][2]=rep_y;polymer[0][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.83 && ran1<=1) {
	printf("-----------------HERE-----------------zz");
	rep_x=orep_x;rep_y=orep_y;rep_z=orep_z-1;
	if (rep_z<0) {rep_z=rep_z+BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++zzzz+++++++++++++\n");
	  for (k1=count_site-1;k1>0;k1--) {polymer[k1][1]=polymer[k1-1][1];polymer[k1][2]=polymer[k1-1][2];polymer[k1][3]=polymer[k1-1][3];}
	  polymer[0][1]=rep_x;polymer[0][2]=rep_y;polymer[0][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
      
    }
    
    
    if(ran>0.5) {
      orep_x=polymer[count_site-1][1];orep_y=polymer[count_site-1][2];orep_z=polymer[count_site-1][3];
      erep_x=polymer[0][1];erep_y=polymer[0][2];erep_z=polymer[0][3];

      if(ran1<=0.166) {
	printf("-----------------HERE-----------------X11");
	rep_x=orep_x+1;rep_y=orep_y;rep_z=orep_z;
	//printf("%f\n",ran);
	//for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
	if (rep_x>=BOX_size) {rep_x=rep_x-BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++XXX111+++++++++++++\n");
	  for (k1=0;k1<count_site-1;k1++) {polymer[k1][1]=polymer[k1+1][1];polymer[k1][2]=polymer[k1+1][2];polymer[k1][3]=polymer[k1+1][3];}
	  polymer[count_site-1][1]=rep_x;polymer[count_site-1][2]=rep_y;polymer[count_site-1][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.166 && ran1<=0.33) {
	printf("-----------------HERE-----------------xx11");
	rep_x=orep_x-1;rep_y=orep_y;rep_z=orep_z;
	if (rep_x<0) {rep_x=rep_x+BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++xxxx111+++++++++++++\n");
	  for (k1=0;k1<count_site-1;k1++) {polymer[k1][1]=polymer[k1+1][1];polymer[k1][2]=polymer[k1+1][2];polymer[k1][3]=polymer[k1+1][3];}
	  polymer[count_site-1][1]=rep_x;polymer[count_site-1][2]=rep_y;polymer[count_site-1][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.33 && ran1<=0.5) {
	printf("-----------------HERE-----------------YY11");
	rep_x=orep_x;rep_y=orep_y+1;rep_z=orep_z;
	//for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
	if (rep_y>=BOX_size) {rep_y=rep_y-BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++YYYY111+++++++++++++\n");
	  for (k1=0;k1<count_site-1;k1++) {polymer[k1][1]=polymer[k1+1][1];polymer[k1][2]=polymer[k1+1][2];polymer[k1][3]=polymer[k1+1][3];}
	  polymer[count_site-1][1]=rep_x;polymer[count_site-1][2]=rep_y;polymer[count_site-1][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.5 && ran1<=0.66) {
	printf("-----------------HERE-----------------yy11");
	rep_x=orep_x;rep_y=orep_y-1;rep_z=orep_z;
	if (rep_y<0) {rep_y=rep_y+BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++yyyy111+++++++++++++\n");
	  for (k1=0;k1<count_site-1;k1++) {polymer[k1][1]=polymer[k1+1][1];polymer[k1][2]=polymer[k1+1][2];polymer[k1][3]=polymer[k1+1][3];}
	  polymer[count_site-1][1]=rep_x;polymer[count_site-1][2]=rep_y;polymer[count_site-1][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.66 && ran1<=0.83) {
	printf("-----------------HERE-----------------ZZ11");
	rep_x=orep_x;rep_y=orep_y;rep_z=orep_z+1;
	//for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
	if (rep_z>=BOX_size) {rep_z=rep_z-BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++ZZZZ111+++++++++++++\n");
	  for (k1=0;k1<count_site-1;k1++) {polymer[k1][1]=polymer[k1+1][1];polymer[k1][2]=polymer[k1+1][2];polymer[k1][3]=polymer[k1+1][3];}
	  polymer[count_site-1][1]=rep_x;polymer[count_site-1][2]=rep_y;polymer[count_site-1][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      else if(ran1>0.83 && ran1<=1) {
	printf("-----------------HERE-----------------zz11");
	rep_x=orep_x;rep_y=orep_y;rep_z=orep_z-1;
	if (rep_z<0) {rep_z=rep_z+BOX_size;}
	if(lattice[rep_x][rep_y][rep_z]==0) {count_rep+=1;printf("++++++++++zzzz111+++++++++++++\n");
	  for (k1=0;k1<count_site-1;k1++) {polymer[k1][1]=polymer[k1+1][1];polymer[k1][2]=polymer[k1+1][2];polymer[k1][3]=polymer[k1+1][3];}
	  polymer[count_site-1][1]=rep_x;polymer[count_site-1][2]=rep_y;polymer[count_site-1][3]=rep_z;
	  lattice[rep_x][rep_y][rep_z]=1;lattice[erep_x][erep_y][erep_z]=0;
	}}
      for(k2=0;k2<count_site;k2++) {printf("%d %d %d\n",polymer[k2][1],polymer[k2][2],polymer[k2][3]);}
      
    }
    

      //rep_x=polymer[count_site-1][1];rep_y=polymer[count_site-1][2];rep_z=polymer[count_site-1][3];}
    
    //printf("%d %d %d\n",rep_x,rep_y,rep_z);
    

  }
  printf("\n%d\n\n",count_rep);
  //for (k1=0;k1<count_site;k1++){fprintf(fp1,"ATOM   %4u  CA AAA  %4u    %8d%8d%8d  1.00\n",k1,k1,polymer[k1][1],polymer[k1][2],polymer[k1][3]);}
  // fprintf(fp1,"ENDMDL\n");
  for (k1=0;k1<count_site;k1++) { fprintf(fp1,"%d %d %d\n",polymer[k1][1],polymer[k1][2],polymer[k1][3]);}



















 


  /*********************************************************************************************************************************/
//Function crank Shaft movement..
  /*********************************************************************************************************************************/
  /*


  int old_x1,old_y1,old_z1,old_x2,old_y2,old_z2,cs_count;   //crank shaft count
  int tmp_x1,tmp_y1,tmp_z1,tmp_x2,tmp_y2,tmp_z2;
  int df_x1,df_x2,df_x3,df_y1,df_y2,df_y3,df_z1,df_z2,df_z3;
  for (i=0;i<1000;i++) {
    ran = (double)rand() / (double)RAND_MAX ;
    site_id=ran*(count_site-1);

    if(site_id==0 || site_id==1 || site_id==(count_site-2) || site_id==(count_site-1)) {continue;}
    printf("%d\n",site_id);
    printf("\n");
    
  for (k1=(site_id-1);k1<=(site_id+2);k1++) { printf("%d %d %d\n",polymer[k1][1],polymer[k1][2],polymer[k1][3]);}

    df_x1=(polymer[site_id][1]-polymer[site_id-1][1]);df_x2=(polymer[site_id+1][1]-polymer[site_id][1]);df_x3=(polymer[site_id+2][1]-polymer[site_id+1][1]);
    df_y1=(polymer[site_id][2]-polymer[site_id-1][2]);df_y2=(polymer[site_id+1][2]-polymer[site_id][2]);df_y3=(polymer[site_id+2][2]-polymer[site_id+1][2]);
    df_z1=(polymer[site_id][3]-polymer[site_id-1][3]);df_z2=(polymer[site_id+1][3]-polymer[site_id][3]);df_z3=(polymer[site_id+2][3]-polymer[site_id+1][3]);

    if(polymer[site_id][3]==polymer[site_id-1][3] && polymer[site_id][3]==polymer[site_id+1][3] && polymer[site_id][3]==polymer[site_id+2][3]) {
      if((polymer[site_id+2][1]-polymer[site_id-1][1])==(polymer[site_id+1][1]-polymer[site_id][1]) && polymer[site_id-1][2]==polymer[site_id+2][2]) {
	old_x1=polymer[site_id][1];old_x2=polymer[site_id+1][1];
	old_y1=polymer[site_id][2];old_y2=polymer[site_id+1][2];
	old_z1=polymer[site_id][3];old_z2=polymer[site_id+1][3];

	tmp_x1=old_x1;tmp_x2=old_x2;
	tmp_z1=old_z1;tmp_z2=old_z2;
	tmp_y1=polymer[site_id][2]+2*df_y3;
	if (tmp_y1>=BOX_size) {tmp_y1=tmp_y1-BOX_size;}
	if (tmp_y1<0) {tmp_y1=tmp_y1+BOX_size;}
	tmp_y2=tmp_y1;
	
	if(lattice[tmp_x1][tmp_y1][tmp_z1]==0 && lattice[tmp_x2][tmp_y2][tmp_z2]==0) {cs_count+=1;polymer[site_id][2]=tmp_y1;polymer[site_id+1][2]=tmp_y2;lattice[tmp_x1][tmp_y1][tmp_z1]=1;lattice[tmp_x2][tmp_y2][tmp_z2]=1;lattice[old_x1][old_y1][old_z1]=0;lattice[old_x2][old_y2][old_z2]=0;printf("------------ZZZyyy----------\n");}
      }

      if((polymer[site_id+2][2]-polymer[site_id-1][2])==(polymer[site_id+1][2]-polymer[site_id][2]) && polymer[site_id-1][1]==polymer[site_id+2][1]) {
	old_x1=polymer[site_id][1];old_x2=polymer[site_id+1][1];
	old_y1=polymer[site_id][2];old_y2=polymer[site_id+1][2];
	old_z1=polymer[site_id][3];old_z2=polymer[site_id+1][3];
	
	tmp_x1=polymer[site_id][1]+2*df_x3;
	if (tmp_x1>=BOX_size) {tmp_x1=tmp_x1-BOX_size;}
	if (tmp_x1<0) {tmp_x1=tmp_x1+BOX_size;}
	tmp_x2=tmp_x1;
	tmp_y1=old_y1;tmp_y2=old_y2;
	tmp_z1=old_z1;tmp_z2=old_z2;
	
	if(lattice[tmp_x1][tmp_y1][tmp_z1]==0 && lattice[tmp_x2][tmp_y2][tmp_z2]==0) {cs_count+=1;polymer[site_id][1]=tmp_x1;polymer[site_id+1][1]=tmp_x2;lattice[tmp_x1][tmp_y1][tmp_z1]=1;lattice[tmp_x2][tmp_y2][tmp_z2]=1;lattice[old_x1][old_y1][old_z1]=0;lattice[old_x2][old_y2][old_z2]=0;printf("------------ZZZxxx----------\n");}
      }


    }    



    if(polymer[site_id][2]==polymer[site_id-1][2] && polymer[site_id][2]==polymer[site_id+1][2] && polymer[site_id][2]==polymer[site_id+2][2]) {
      if((polymer[site_id+2][1]-polymer[site_id-1][1])==(polymer[site_id+1][1]-polymer[site_id][1]) && polymer[site_id-1][3]==polymer[site_id+2][3]) {
	old_x1=polymer[site_id][1];old_x2=polymer[site_id+1][1];
	old_y1=polymer[site_id][2];old_y2=polymer[site_id+1][2];
	old_z1=polymer[site_id][3];old_z2=polymer[site_id+1][3];

	tmp_x1=old_x1;tmp_x2=old_x2;
	tmp_y1=old_y1;tmp_y2=old_y2;
	tmp_z1=polymer[site_id][3]+2*df_z3;
	if (tmp_z1>=BOX_size) {tmp_z1=tmp_z1-BOX_size;}
	if (tmp_z1<0) {tmp_z1=tmp_z1+BOX_size;}
	tmp_z2=tmp_z1;
	
	if(lattice[tmp_x1][tmp_y1][tmp_z1]==0 && lattice[tmp_x2][tmp_y2][tmp_z2]==0) {cs_count+=1;polymer[site_id][3]=tmp_z1;polymer[site_id+1][3]=tmp_z2;lattice[tmp_x1][tmp_y1][tmp_z1]=1;lattice[tmp_x2][tmp_y2][tmp_z2]=1;lattice[old_x1][old_y1][old_z1]=0;lattice[old_x2][old_y2][old_z2]=0;printf("------------YYYzzz----------\n");}
      }

      if((polymer[site_id+2][3]-polymer[site_id-1][3])==(polymer[site_id+1][3]-polymer[site_id][3]) && polymer[site_id-1][1]==polymer[site_id+2][1]) {
	old_x1=polymer[site_id][1];old_x2=polymer[site_id+1][1];
	old_y1=polymer[site_id][2];old_y2=polymer[site_id+1][2];
	old_z1=polymer[site_id][3];old_z2=polymer[site_id+1][3];
	
	tmp_x1=polymer[site_id][1]+2*df_x3;
	if (tmp_x1>=BOX_size) {tmp_x1=tmp_x1-BOX_size;}
	if (tmp_x1<0) {tmp_x1=tmp_x1+BOX_size;}
	tmp_x2=tmp_x1;
	tmp_y1=old_y1;tmp_y2=old_y2;
	tmp_z1=old_z1;tmp_z2=old_z2;
	
	if(lattice[tmp_x1][tmp_y1][tmp_z1]==0 && lattice[tmp_x2][tmp_y2][tmp_z2]==0) {cs_count+=1;polymer[site_id][1]=tmp_x1;polymer[site_id+1][1]=tmp_x2;lattice[tmp_x1][tmp_y1][tmp_z1]=1;lattice[tmp_x2][tmp_y2][tmp_z2]=1;lattice[old_x1][old_y1][old_z1]=0;lattice[old_x2][old_y2][old_z2]=0;printf("------------YYYxxx----------\n");}
      }


    }   



    if(polymer[site_id][1]==polymer[site_id-1][1] && polymer[site_id][1]==polymer[site_id+1][1] && polymer[site_id][1]==polymer[site_id+2][1]) {
      if((polymer[site_id+2][3]-polymer[site_id-1][3])==(polymer[site_id+1][3]-polymer[site_id][3]) && polymer[site_id-1][2]==polymer[site_id+2][2]) {
	old_x1=polymer[site_id][1];old_x2=polymer[site_id+1][1];
	old_y1=polymer[site_id][2];old_y2=polymer[site_id+1][2];
	old_z1=polymer[site_id][3];old_z2=polymer[site_id+1][3];

	tmp_x1=old_x1;tmp_x2=old_x2;
	tmp_z1=old_z1;tmp_z2=old_z2;
	tmp_y1=polymer[site_id][2]+2*df_y3;
	if (tmp_y1>=BOX_size) {tmp_y1=tmp_y1-BOX_size;}
	if (tmp_y1<0) {tmp_y1=tmp_y1+BOX_size;}
	tmp_y2=tmp_y1;
	
	if(lattice[tmp_x1][tmp_y1][tmp_z1]==0 && lattice[tmp_x2][tmp_y2][tmp_z2]==0) {cs_count+=1;polymer[site_id][2]=tmp_y1;polymer[site_id+1][2]=tmp_y2;lattice[tmp_x1][tmp_y1][tmp_z1]=1;lattice[tmp_x2][tmp_y2][tmp_z2]=1;lattice[old_x1][old_y1][old_z1]=0;lattice[old_x2][old_y2][old_z2]=0;printf("------------XXXyyy----------\n");}
      }

      if((polymer[site_id+2][2]-polymer[site_id-1][2])==(polymer[site_id+1][2]-polymer[site_id][2]) && polymer[site_id-1][3]==polymer[site_id+2][3]) {
	old_x1=polymer[site_id][1];old_x2=polymer[site_id+1][1];
	old_y1=polymer[site_id][2];old_y2=polymer[site_id+1][2];
	old_z1=polymer[site_id][3];old_z2=polymer[site_id+1][3];
	
	tmp_x1=old_x1;tmp_x2=old_x2;
	tmp_y1=old_y1;tmp_y2=old_y2;
	tmp_z1=polymer[site_id][3]+2*df_z3;
	if (tmp_z1>=BOX_size) {tmp_z1=tmp_z1-BOX_size;}
	if (tmp_z1<0) {tmp_z1=tmp_z1+BOX_size;}
	tmp_z2=tmp_z1;
	
	if(lattice[tmp_x1][tmp_y1][tmp_z1]==0 && lattice[tmp_x2][tmp_y2][tmp_z2]==0) {cs_count+=1;polymer[site_id][3]=tmp_z1;polymer[site_id+1][3]=tmp_z2;lattice[tmp_x1][tmp_y1][tmp_z1]=1;lattice[tmp_x2][tmp_y2][tmp_z2]=1;lattice[old_x1][old_y1][old_z1]=0;lattice[old_x2][old_y2][old_z2]=0;printf("------------XXXzzz----------\n");}
      }


    }    
 


    //for (k1=(site_id-1);k1<=(site_id+2);k1++) { printf("%d %d %d\n",polymer[k1][1],polymer[k1][2],polymer[k1][3]);}
    for (k1=0;k1<count_site;k1++){fprintf(fp1,"ATOM   %4u  CA AAA  %4u    %8d%8d%8d  1.00\n",k1,k1,polymer[k1][1],polymer[k1][2],polymer[k1][3]);}
    fprintf(fp1,"ENDMDL\n");


 }
  //for (k1=0;k1<count_site;k1++){fprintf(fp1,"ATOM   %4u  CA GLY  %4u    %8d%8d%8d  1.00\n",k1,k1,polymer[k1][1],polymer[k1][2],polymer[k1][3]);}
  //fprintf(fp1,"END\n");


  //for (k1=0;k1<count_site;k1++) { fprintf(fp1,"%d %d %d\n",polymer[k1][1],polymer[k1][2],polymer[k1][3]);}


  printf("%d",cs_count);


 
  */

  /**************************************************************************************************************************************************/

    
  /*
  //printf("%d %d\n",count_step,count_site);
  int l1,l2,l3;
  for (k1=0;k1<=(count_site);k1++) {
    l1=polymer[k1][1];l2=polymer[k1][2];l3=polymer[k1][3];
    printf("%d %d %d %d\n",l1,l2,l3,lattice[l1][l2][l3]);}
    printf("Coordinates output ends here\n");
  */

    /*
 int sign;
 int old_x,old_y,old_z;
  for (i=0;i<MC_STEP;i++) {
    ran = (double)rand() / (double)RAND_MAX ;
    site_id=ran*(count_site-1);
    //sign=(polymer[site_id][7])*(polymer[(site_id+1)][7]);
    //printf("%d %d %d %d %d\n",site_id,polymer[site_id][0],polymer[site_id][7],polymer[site_id+1][7],sign);
    if(site_id==0 || site_id==(count_site-1)) {continue;}
    printf("%d\n",site_id);
    printf("\n");
    for (k1=(site_id-1);k1<=(site_id+1);k1++) { printf("%d %d %d\n",polymer[k1][1],polymer[k1][2],polymer[k1][3]);}

    
    if(polymer[site_id][1]==polymer[site_id-1][1] && polymer[site_id][1]==polymer[site_id+1][1]) {
      old_x=polymer[site_id][1];old_y=polymer[site_id][2];old_z=polymer[site_id][3];
      tmp_x=polymer[site_id][1];
      //printf("\n%d\n\n",site_id);
      if(polymer[site_id][2]==polymer[site_id-1][2] && polymer[site_id][2]!=polymer[site_id+1][2]) {
	tmp_y=polymer[site_id+1][2];tmp_z=polymer[site_id-1][3];
	if(lattice[tmp_x][tmp_y][tmp_z]==0) {count2+=1;polymer[site_id][2]=tmp_y;polymer[site_id][3]=tmp_z;lattice[tmp_x][tmp_y][tmp_z]=1;lattice[old_x][old_y][old_z]=0; printf("+++++++++++++++++++XX111++++++++++++++++\n");}
	printf("%d  %d",lattice[tmp_x][tmp_y][tmp_z],lattice[old_x][old_y][old_z]); }
      else if(polymer[site_id][2]==polymer[site_id+1][2] && polymer[site_id][2]!=polymer[site_id-1][2]) {
	tmp_y=polymer[site_id-1][2];tmp_z=polymer[site_id+1][3];
	if(lattice[tmp_x][tmp_y][tmp_z]==0) {count2+=1;polymer[site_id][2]=tmp_y;polymer[site_id][3]=tmp_z;lattice[tmp_x][tmp_y][tmp_z]=1;lattice[old_x][old_y][old_z]=0; printf("+++++++++++++++++++XX222++++++++++++++++\n");}}
      printf("+++++++++++++++++++I am here XXXXXX    ++++++++++++++++\n");    
    }
    
      
    if(polymer[site_id][2]==polymer[site_id-1][2] && polymer[site_id][2]==polymer[site_id+1][2]) {
      old_x=polymer[site_id][1];old_y=polymer[site_id][2];old_z=polymer[site_id][3];
      tmp_y=polymer[site_id][2];
      //printf("\n%d\n\n",site_id);
      if(polymer[site_id][1]==polymer[site_id-1][1] && polymer[site_id][1]!=polymer[site_id+1][1]) {
	tmp_x=polymer[site_id+1][1];tmp_z=polymer[site_id-1][3];
	if(lattice[tmp_x][tmp_y][tmp_z]==0) {count2+=1;polymer[site_id][1]=tmp_x;polymer[site_id][3]=tmp_z;lattice[tmp_x][tmp_y][tmp_z]=1;lattice[old_x][old_y][old_z]=0;printf("+++++++++++++++++++YY111++++++++++++++++\n");}}
      else if(polymer[site_id][1]==polymer[site_id+1][1] && polymer[site_id][1]!=polymer[site_id-1][1]) {
	tmp_x=polymer[site_id-1][1];tmp_z=polymer[site_id+1][3];
	if(lattice[tmp_x][tmp_y][tmp_z]==0) {count2+=1;polymer[site_id][1]=tmp_x;polymer[site_id][3]=tmp_z;lattice[tmp_x][tmp_y][tmp_z]=1;lattice[old_x][old_y][old_z]=0;printf("+++++++++++++++++++YY222++++++++++++++++\n");}}
      //printf("+++++++++++++++++++YYYYY++++++++++++++++\n");    
    }

        
    if(polymer[site_id][3]==polymer[site_id-1][3] && polymer[site_id][3]==polymer[site_id+1][3]) { 
      old_x=polymer[site_id][1];old_y=polymer[site_id][2];old_z=polymer[site_id][3];
      tmp_z=polymer[site_id][3];
      //printf("\n%d\n\n",site_id);
      if(polymer[site_id][1]==polymer[site_id-1][1] && polymer[site_id][1]!=polymer[site_id+1][1]) {
	tmp_x=polymer[site_id+1][1];tmp_y=polymer[site_id-1][2];
	if(lattice[tmp_x][tmp_y][tmp_z]==0) {count2+=1;polymer[site_id][1]=tmp_x;polymer[site_id][2]=tmp_y;lattice[tmp_x][tmp_y][tmp_z]=1;lattice[old_x][old_y][old_z]=0;}}
      else if(polymer[site_id][1]==polymer[site_id+1][1]) {
	tmp_x=polymer[site_id-1][1];tmp_y=polymer[site_id+1][2];
	if(lattice[tmp_x][tmp_y][tmp_z]!=1) {count2+=1;polymer[site_id][1]=tmp_x;polymer[site_id][2]=tmp_y;lattice[tmp_x][tmp_y][tmp_z]=1;lattice[old_x][old_y][old_z]=0;}}
      //      printf("+++++++++++++++++++ZZZZZZ++++++++++++++++\n");    
    }
    

    // for (k1=0;k1<count_site;k1++) { printf("%d %d %d %d %d %d %d %d %d\n",polymer[k1][0],polymer[k1][1],polymer[k1][2],polymer[k1][3],polymer[k1][4],polymer[k1][5],polymer[k1][6],polymer[k1][7],polymer[k1][8]);}
    //for (k1=(site_id-1);k1<=(site_id+1);k1++) { printf("%d %d %d %d\n",polymer[k1][0],polymer[k1][1],polymer[k1][2],polymer[k1][3]);}
    for (k1=(site_id-1);k1<=(site_id+1);k1++) { printf("%d %d %d\n",polymer[k1][1],polymer[k1][2],polymer[k1][3]);}

    
  }
*/
  //printf("%d",count2);
  //for (k1=0;k1<count_site;k1++) { fprintf(fp1,"%d %d %d\n",polymer[k1][1],polymer[k1][2],polymer[k1][3]);}
  
  
}







   

/*********************************************************************/
//Function to calculate crowding

int crowd(int a, int b, int c)
{ int cont=0;
  int a1,b1,c1,a2,b2,c2,temp_a,temp_b,temp_c;

  temp_a = a;
  temp_b = b;
  temp_c = c;
  
  if (a>0 && a<boundry) {a1=(a+1);a2=(a-1);
    if (lattice[a1][b][c]==0) {cont+=1;}
    if (lattice[a2][b][c]==0) {cont+=1;}}
  else if (a==boundry) {a1=(a-boundry);a2=(a-1);
    if (lattice[a1][b][c]==0) {cont+=1;}
    if (lattice[a2][b][c]==0) {cont+=1;}}
  else if (a==0) {a1=(a+1);a2=(a+boundry);
    if (lattice[a1][b][c]==0) {cont+=1;}
    if (lattice[a2][b][c]==0) {cont+=1;}}
  a = temp_a;
  
  if (b>0 && b<boundry) {b1=(b+1);b2=(b-1);
    if (lattice[a][b1][c]==0) { cont+=1;}
    if (lattice[a][b2][c]==0) {cont+=1;}}
  else if (b==boundry) {b1=(b-boundry);b2=(b-1);
    if (lattice[a][b1][c]==0) {cont+=1;}
    if (lattice[a][b2][c]==0) {cont+=1;}}
  else if (b==0) {b1=(b+1);b2=(b+boundry);
    if (lattice[a][b1][c]==0) {cont+=1;}
    if (lattice[a][b2][c]==0) {cont+=1;}}
  b = temp_b;
  
  if (c>0 && c<boundry ){c1=(c+1);c2=(c-1);
    if (lattice[a][b][c1]==0) {cont+=1;}
    if (lattice[a][b][c2]==0) {cont+=1;}}
  else if (c==boundry) {c1=(c-boundry);c2=(c-1);
    if (lattice[a][b][c1]==0){cont+=1;}
    if (lattice[a][b][c2]==0){cont+=1;}}
  else if (c==0) {c1=(c+1);c2=(c+boundry);
    if (lattice[a][b][c1]==0) {cont+=1;}
    if (lattice[a][b][c2]==0) {cont+=1;}}
  c = temp_c;
  return cont;
}
