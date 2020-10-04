#include<stdio.h>
#include<stdlib.h>
#define MS 100


int main(int argc, char *argv[])
{
  void READ_FILE(char * , int [MS][MS], int *, int *, int *);
  void DISPLAY(int [MS][MS], int );
  void kruskal(int , int , int [MS], int [MS], int [MS], int , int *, int [MS][MS]);
  void creat_dataset(int [MS][MS], int , int , int , int [MS], int [MS], int [MS], int *);
        
  int A[MS][MS], M[MS][MS], N, typ, inf, cost, ch, Qvs[MS], Qva[MS], Qw[MS], Ne;
  char str[20], *FName;
    
  inf = 1;
  Ne = 0;
// if someone fails to give filename in command line...|||    
  if(argc < 2)
  {
    printf("Enter a File Name to open: ");
// read filename in run time...|||
    scanf("%s", str); 
    printf("Entered File Name is: %s\n\n", str);
    FName = str;
  }
  else
  {
    FName = argv[1];
  }
          
// READ_FILE() function calling...|||
  READ_FILE(FName, A, &N, &typ, &inf);
  if(N == 0)
  {
    return 0;
  }

  printf("\n\nNumber of vertex in the given graph: %d", N); 

// typ = 0, indicates unweighted undirected graph          
  if(typ == 0)
  {
    printf("\n\nType of the given graph is unweighted undirected graph\n");
  }

// typ = 1, indicates weighted undirected graph
  else if(typ == 1)
  {
    printf("\n\nType of the given graph is weighted undirected graph\n");
  }
    
// typ = 2, indicates unweighted directed graph
  else if(typ == 2)
  {
    printf("\n\nType of the given graph is unweighted directed graph\n");
  }

// typ = 3, indicates weighted directed grapg
  else
  {
    printf("\n\nType of the given graph is weighted directed graph\n");
  }
        
// DISPLAY() function calling, Display the given graph...|||
  printf("The given graph is:\n");
  DISPLAY(A, N);
  
//  printf("\nEnter the source vertex: ");
//  scanf("%d", &vs);

  cost = 0;
  creat_dataset(A, N, typ, inf, Qvs, Qva, Qw, &Ne);
      
//kruskal() function calling...||
  kruskal(N, typ, Qvs, Qva, Qw, Ne, &cost, M);       

// DISPLAY() function calling, Minimum spannig tree display...|||
  printf("\nThe Minimum Spanning Tree is:\n");
  DISPLAY(M, N);
  
// for weighted graph display the cost of the traversal...|||    
  if(typ == 1 || typ == 3)
  {
    printf("\nCost of the traversal: %d\n\n", cost);
  }   
    
  printf("\nIf You Wants to Enter Another Graph, Press '1', to Exit, Press '0'\n");
  scanf("%d", &ch);
  if(ch == 1)
  {
    main(argc, argv);
  }
  else
  {
    puts("Session Expire");
  }
  return 0;
}

//Display function of a matrix...|||
void DISPLAY(int A[MS][MS], int N)
{
  int i, j;
    
  printf("   ");
  for(i=1; i<=N; i++)
  {
// display column lables
    printf("%3d", i);
  }
  printf("\n");
    
  for(i=1; i<=N; i++)
  {
//display row lable
    printf("%3d", i);
    for(j=1; j<=N; j++)
    {
// display value of a particular position
      printf("%3d", A[i][j]);
    }
    printf("\n");
  }        
  return;
}

// File read function...|||
void READ_FILE(char * FName, int A[MS][MS], int *N, int *typ, int *inf)
{
  int ch, i, j, v, u, w;
  FILE * ptr;
  char str[20];
    
// file open in read mode...||    
  ptr=fopen(FName, "r");

// if failed to open file...|||  
  if(ptr == NULL)
  {
    puts("ERROR!! FAILED TO OPEN THE FILE");

    printf("\nIf You Wants to Enter the Augmented Matrix Manually, Press '1', if You Wants to Enter Another Graph, Press '0', To Exit Press Any Number rather '1' & '0': ");
        
    scanf("%d", &ch);
        
    if(ch == 1)
    {
      puts("\n\nEnter Augmented Matrix Manually~~");

// read number of vertex from keyboard into 'N' veriable...|||            
      printf("\nEnter number of vertex: ");
      scanf("%d", N);

/*
'typ' holds a value indicating type of the given graph. 
we mapped unweighted undirected graph, weghted undirected graph, unweighted direct graph, 
weighted directed graph in to 0, 1, 2, 3 respectively
*/            
      printf("Enter Type of the Graph: ");
      scanf("%d", typ);
            
      printf("\nNOTE: For weighted graph enter 0 for no adjacency of any vertex.\n\nEnter value of the augmented matrix~~\n");
            
      for(i=1; i<=(*N); i++)
      {
        for(j=1; j<=(*N); j++)
        {
          printf("A[%d][%d]: ", i, j);
          scanf("%d", &A[i][j]);
          (*inf) += A[i][j];
        }
      }
    }
    else if(ch == 0)
    {
      printf("\nEnter a File Name to open: ");
      scanf("%s", str); 
      printf("\nEntered File Name is: %s\n\n", str);
      FName = str;
      (*inf) = 1;
            
// READ_FILE() function calling...|||
      READ_FILE(FName, A, N, typ, inf);
    }
    else
    {
// on exit return number of vertex is zero... that helps to call prims function
      (*N) = 0;
      puts("Session Exipre");
      return;
    }
  }

// if file open successfully...|||
  else
  {
    puts("FILE OPEN SUCCESSFULLY");

// read number of vertex from file into 'N' veriable...|||
    fscanf(ptr, "%d", N);
    printf("Number of vertx: %d\n", *N);
        
// intializing '0' in all the elements...|||
    for(i=1; i<=(*N); i++) 
    {
      for(j=1; j<=(*N); j++)
      {
        A[i][j]=0;
      }
    }
/*
'typ' holds a value indicating type of the given graph. 
we mapped unweighted undirected graph, weghted undirected graph, unweighted direct graph, 
weighted directed graph in to 0, 1, 2, 3 respectively
*/
        
    fscanf(ptr, "%d", typ);
    
// untill file ends loop continue
    while(!feof(ptr))
    {
// read one edge from file into 'v' variable
      fscanf(ptr, "%d", &v);

// read 2nd edge from file into 'u' variable           
      fscanf(ptr, "%d", &u);

// for weighted graph read weight from file into 'w'...||        
      if((*typ) == 1 || (*typ) == 3)
      {
        fscanf(ptr, "%d", &w);
        (*inf) += w;
      } 

// Intializing end vertices by '1' for unweighted undirected graph...|||
      if((*typ) == 0)
      {
        A[v][u]=1;
        A[u][v]=1;
      }

// Intializing end vertices by 'w'(weight of the edge) for weighted undirected graph...||| 
      else if((*typ) == 1)
      {
        A[v][u]=w;
        A[u][v]=w;
      }

// Intializing end vertices by '1' for unweighted directed graph...|||       
      else if((*typ) == 2)
      {
        A[v][u]=1;
      }

// Intializing end vertices by 'w'(weight of the edge) for weighted directed graph...|||      
      else
      {
        A[v][u]=w;
      }
    } // while(!feof(ptr))[End of the file]
    fclose(ptr); //file close
  }

// for weighted graph intializing infinity for indicating no edge between two vertex...|||
  if(*typ == 1 || *typ == 3)
  {
    for(i=1; i<=(*N); i++)
    {
      for(j=1; j<=(*N); j++)
      {
        if(i != j)
        {
          if(A[i][j] == 0)
          {
            A[i][j] = (*inf);
          } // end of if((*(A+(i*N)+j)) == 0)
        } // end of if(i != j)
      } // end of for(j=1; j<=N; j++)
    } // for(i=1; i<=N; i++)
  } // if(typ == 1 || typ == 3)
    
  return;
} // end of READ_FILE() function

// kruskal() function...|||
void kruskal(int N, int typ, int Qvs[MS], int Qva[MS], int Qw[MS], int Ne, int *cost, int M[MS][MS])
{  
  int St[N], i, j, NoE, x, y, w, f, temp;

// intializing '0' in all the elements of the spannig tree, M and status array, St. 
  for(i = 1; i<= N; i++)
  {
    St[i] = 0;
    for(j = 1; j<= N; j++)
    {
      M[i][j] = 0;
    }
  }
// temp holds the last element of those array contain the data set of sorted edges...|||    
  temp = Ne-1;

//NoE is number of edge in the minimum spannig tree. that should be (N-1)...|||
  NoE = 1;
  while(NoE < N)
  {
// read the data from the data set...|||
    x = Qvs[temp]; // x holds one vertex of the end verices
    y = Qva[temp]; // y holds one vertex of the end verices
    
    w = Qw[temp]; // w holds the weight of the edge
// delete the data from the data set...|||
   temp -= 1;

/* for undirected graph 'f' indicates any edge make a circuit or not.
f will be '1' if any edge make circuit either it will remain '0'. 
intially 'f' is 0
*/
    f = 0;

// for undirect graph             
    if(typ == 0 || typ == 1)
    {
// if there was any vertex that has been traversed before that vertex will check.
      for(i = 1; i <= N; i++)
      {
        if(i != x)
        {
          if(i != y)
          {
            if(St[i] == 1)
            {
              // if any ith vertex is connected with x & y both then f become 1. 
              if(M[x][i] != 0)
              {
                if(M[y][i] != 0)
                {
                  f = 1;
                  // means the edge connected by x & y will make a circuit
                } // end of if(M[y][i] != 0)
              } // end of if(M[x][i] != 0)
            } // end of if(St[i] == 1)
          } // end of if(i != y)
        } // end of if(i != x)
      } // end of for(i = 1; i <= N; i++)
 
      if(f == 0) // if the edge doesn't make a circuit
      {
        //for unweighted undirected graph insert the edge
        if(typ == 0) 
        { 
          // intial '1' to indicate there is an edge..           
          M[x][y] = 1; 
          M[y][x] = 1;
        }
        //for weighted undirected graph insert the edge
        else
        {
          // intial weight, 'w' to indicate there is an edge..     
          M[x][y] = w;
          M[y][x] = w;
        }
        // make the status '1' of the traversed vertex   
        St[x] = 1;
        St[y] = 1;
        // update cost of the traversal
        (*cost) += w;
        // update number of vertex in the minimum spanning tree
        NoE += 1;
      } // end of if(f == 0)
                            
    } // end of if(typ == 0 || typ == 1)
        
    // for directed graph 
    else
    {
      // if the destiny vertex not traversed yet. connect the edge..
      if(St[y] == 0)
      {
        // for unweighted directed graph
        if(typ == 2)
        {
          // intialize by '1' to indicate the end vertices are connected
          M[x][y] = 1;
        }
        // for weighted directed graph
        else
        {
          // intialize by weigjt '1' to indicate the end vertices are connected
          M[x][y] = w;
        }
        // update status of the traversed vertex
        St[y] = 1;
        // updare cost for the traversal
        (*cost) += w;
        // update number of edge of the spannig tree
        NoE += 1;  
      } //end of if(St[y] == 0)
            
    } // end of else block
  } // end of while(NoE < N)

// for weighted graph initalize infinity to indicate no edge between any end vertices
  if(typ == 1 || typ == 3)
  {
    for(i = 1; i <= N; i++)
    {
      for(j = 1; j <= N; j++)
      {
        if(i != j)
        {
          if(M[i][j] == 0)
          {
            M[i][j] = (*cost) + 1;
          }
        }
      }
    }
  }
  return;
}

// creat the data set from the given file. all the edges are sorted Descending manner w.r.t their weight.

void creat_dataset(int A[MS][MS], int N, int typ, int inf, int Qvs[MS], int Qva[MS], int Qw[MS], int *Ne)
{
  void Mod_Bubble_sort(int [MS], int [MS], int [MS], int );
       
  int i, j;

// for undirected graph read all the edges and store into array 
  if(typ == 0 || typ == 1)
  {
    i = 1;
    while(i <= N) // for all vertex
    {
      j = i+1;
      while(j <= N) // other remaining vertex for ith vertex
      {
        if(i != j) // if ith & jth are not same
        {
          if(typ == 0) // for unweighted undirected graph
          {
            if(A[i][j] != 0) // if ith & jth vertex are conncected
            {
              // store the end vertices
              Qvs[(*Ne)] = i; // Qvs array holds ith vertex
              Qva[(*Ne)] = j; // Qva array holds the adjacence vertex of ith vertex
                            
              (*Ne) += 1; // number of edges in the arrays
            } // end of if(A[i][j] != 0)
          } // end of if(typ == 0)
                    
          // for weighted undirected graph
          else
          {
            // if ith and jth are not connected
            if(A[i][j] != inf)
            {
              // store the end vertices
              Qvs[(*Ne)] = i; // Qvs array holds ith vertex
              Qva[(*Ne)] = j; // Qva array holds the adjacence vertex of ith vertex
              Qw[(*Ne)] = A[i][j]; //Qw array holds the weight of the edge
              (*Ne) += 1; // update number of elements of the arrays
            } // end of if(A[i][j] != inf)
          } // end of else block
        } // end of if(i != j)
        j += 1;
      } // end of while(j <= N)
      i+= 1;
    } // end of while(i <= N)
  }  // end of if(typ == 0 || typ == 1)

// for directed graph    
  else
  {
  	i = 1;
  	while(i <= N) // for all ith vertex
  	{
  	  j = 1;
  	  while(j <= N) // for all jth vertex
  	  {
  	  	 if(i != j) // if ith & jth vertex are not same
  	   	{
  	   	  if(typ == 2) // for unweighted directed graph
  	   	  {
  	    	  	if(A[i][j] != 0) // if ith & jth vertex is adjacence
  	    	  	{
             // store the end vertices
  	    	     Qvs[(*Ne)] = i; // Qvs array holds the ith vertex
             Qva[(*Ne)] = j; // Qva array holds the adajacency vertex
             (*Ne) += 1; // number of edge in the array update
  	  	     } // end of if(A[i][j] != 0)
  	   	  } // end of if(typ == 2)
         
         // for weighted directed graph
  	   	  else
  	   	  {
           // if ith & jth vertex are connected
  	   	    if(A[i][j] != inf)
  	    	  	{
             // store the edge
  	   	      Qvs[(*Ne)] = i; // Qvs holds the ith vertex
             Qva[(*Ne)] = j; // Qva holds the adjacency vertex
             Qw[(*Ne)] = A[i][j]; // Qw holds the weight of the edge
             (*Ne) += 1; // update number of edge in the arrays
  	    	  	} // end of if(A[i][j] != inf)
  	   	  } // end of else block
   	  	} // end of if(i != j)
       j += 1;
   	  } // end of while(j <= N)
      i += 1;
    } // end of while(i <= n)
  } // end of else block

// for weighted graph sort the weight(Qw array) descending manner
  if(typ == 1 || typ == 3)
  {
    // sorting the data set using modified bubble sort
    Mod_Bubble_sort(Qvs, Qva, Qw, *Ne);
  } 
  return;
}

// modified bubble sort 
void Mod_Bubble_sort(int Qvs[MS], int Qva[MS], int Qw[MS], int Ne )
{
  int i, j, f, temp;
       
  i = 0;
  while(i < Ne-1)
  {
    f = 0; // f indicates array is sorted
    j = 0;
    while(j < Ne - 1 - i)
    {
      // if the j+1 the elements greater than jth elements interchange the value
      if(Qw[j] < Qw[j+1]) 
      {
        temp = Qw[j+1];
        Qw[j+1] = Qw[j];
        Qw[j] = temp;

// interchange the value of Qvs if there was any changes in Qw array
                        
        temp = Qvs[j+1];
        Qvs[j+1] = Qvs[j];
        Qvs[j] = temp;

// interchange the value of Qva if there was any changes in Qw array
                                
        temp = Qva[j+1];
        Qva[j+1] = Qva[j];
        Qva[j] = temp; 
        
        f = 1; // array is not sorted yet
      }            
      j += 1;
    }
    if(f == 0) // if array is sorted then terminate from the loop
    {
      break;
    }
    i += 1;
  }

  return;
}
