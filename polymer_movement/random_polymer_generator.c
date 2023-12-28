# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
#define BOX_size 10
#define MC_STEP 100000

double crowd(int x,int y,int z);

int main() {

  int count_x,count_y,count_z,count;
  int i;
  double r,r1,r2,r3;
  int lattice[BOX_size][BOX_size][BOX_size];
  int x=0,y=0,z=0;
  int x1,y1,z1,x2,y2,z2;
  int count_step=1,count_site=1,repeat=0;
  int temp_x,temp_y,temp_z;

  FILE *fp;
  fp = fopen("xx2","w");

  //Assigning initial value to lattice
  for(count_x=0;count_x<BOX_size-1;count_x++){
    for(count_y=0;count_y<BOX_size-1;count_y++){
      for(count_z=0;count_z<BOX_size-1;count_z++){
	lattice[count_x][count_y][count_z]=0;
      }
    }
  }

  r = (double)rand() / (double)RAND_MAX ;
  // r = (double)rand();
  r1 = (double)rand() / (double)RAND_MAX ;
  r2 = (double)rand() / (double)RAND_MAX ;
  r3 = (double)rand() / (double)RAND_MAX ;
  // printf("%f %f %f %f\n",r,r1,r2,r3);
  x = r1*BOX_size,y = r2*BOX_size, z = r3*BOX_size; 
  printf("%d %d %d \n\n\n",x,y,z);
  lattice[x][y][z]=1;
  //printf("%d\n",lattice[x][y][z+1]);
  x1=x,y1=y,z1=z;
  
  
  for (i=0;i<MC_STEP;i++){
    
    x2=crowd(x,y,z);
    printf("%d",x2);
    

    
    count_step+=1;
    r = (double)rand() / (double)RAND_MAX ;
    // printf("%f \n",r);
    if (r <=0.33) {x=x+1; 
      if (x>(BOX_size-1)) {x = x-BOX_size;}
      if (lattice[x][y][z]==1) {x=x1;}
      if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;//printf("%d %d %d \n",x,y,z);
      }
    }
    else if (r>0.33 && r<=0.66) {y=y+1;
      if (y>(BOX_size-1)) {y = y-BOX_size; }
      if (lattice[x][y][z]==1) {y=y1;}
      if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;//printf("%d %d %d \n",x,y,z);
      }
    }
    else if (r>0.66 && r<=1.0) {z=z+1;
      if (z>(BOX_size-1)) {z = z-BOX_size; }
      if (lattice[x][y][z]==1) {z=z1;}
      if (lattice[x][y][z]==0) {lattice[x][y][z]=1;count_site+=1;repeat=0;//printf("%d %d %d \n",x,y,z);
      }
      //printf("%d %d %d \n",x,y,z);
    }
    if (x==x1 && y==y1 && z==z1){repeat+=1;}
    if (repeat>100) {break;}
    x1=x,y1=y,z1=z;
    //lattice[x][y][z]=1;
    //printf("%d %d %d \n",x,y,z);
    //fprintf(fp,"%i %i %i\n",x,    y,    z);
  }
  printf("%d %d %d\n",count_step,count_site,repeat);
  
}

/*********************************************************************/
//Function to calculate crowding

double crowd(int a,int b,int c)
{ int cont=0,lattice[BOX_size][BOX_size][BOX_size],a1,b1,c1,a2,b2,c2,Box_size;
  if (a+1<BOX_size) {a1=a+1;if (lattice[a1][b][c]==1){cont+=1;}}
  if (a+1>=BOX_size) {a1=a+1-Box_size;if (lattice[a1][b][c]==1){cont+=1;}}
  if (b+1<BOX_size) {b1=b+1;if (lattice[a][b1][c]==1){cont+=1;}}
  if (b+1>=BOX_size) {b1=b+1-Box_size;if (lattice[a][b1][c]==1){cont+=1;}}
  if (c+1<BOX_size) {c1=c+1;if (lattice[a][b][c1]==1){cont+=1;}}
  if (c+1>=BOX_size) {c1=c+1-Box_size;if (lattice[a][b][c1]==1){cont+=1;}}
  if (a-1>=0) {a2=a-1;if (lattice[a2][b][c]==1){cont+=1;}}
  if (a-1<0) {a2=a-1+Box_size;if (lattice[a2][b][c]==1){cont+=1;}}
  if (b-1>=0) {b2=b-1;if (lattice[a][b2][c]==1){cont+=1;}}
  if (b-1<0) {b2=b-1+Box_size;if (lattice[a][b2][c]==1){cont+=1;}}
  if (c-1>=0) {c2=c-1;if (lattice[a][b][c2]==1){cont+=1;}}
  if (c-1<0) {c2=c-1+Box_size;if (lattice[a][b][c2]==1){cont+=1;}}


  //if (lattice[a1][b][c]==1){cont+=1;}
//if (lattice[a][b1][c]==1){cont+=1;}
//if (lattice[a][b][c1]==1){cont+=1;}
  //if (lattice[a2][b][c]==1){cont+=1;}
  //if (lattice[a][b2][c]==1){cont+=1;}
  //if (lattice[a][b][c2]==1){cont+=1;}

//if (lattice[x][(y+1)%BOX_size][z]==1){cont+=1;}
  //if (lattice[x][y][(z+1)%BOX_size]==1){cont+=1;}
  //if (lattice[(x-1)%BOX_size][y][z]==1){cont+=1;}
  //if (lattice[x][(y-1)%BOX_size][z]==1){cont+=1;}
  //if (lattice[x][y][(z-1)%BOX_size]==1){cont+=1;}
  return cont;
}

