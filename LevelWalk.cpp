



#include "LevelWalk.h"
#include "time.h"

using namespace std;

void allocateRandomGen() {
    randGen = gsl_rng_mt19937;
    rng = gsl_rng_alloc(randGen);
    prng = gsl_rng_alloc(randGen);


}

void freeAll() {

    gsl_rng_free(rng);
    gsl_rng_free(prng);
}
/*
unsigned int *vecConvert(vector <unsigned int> tempVec) {
    unsigned int *tempArr = new unsigned int [tempVec.size()];
    int i = 0;
    for (list<unsigned int>::iterator it = tempVec.begin(); it != tempVec.end(); ++it) {
        tempArr[i] = *it;
        ++i;
    }
    return tempArr;
}*/

int main(int argc, char** argv) {
    allocateRandomGen();


    unsigned int n = atoi(argv[1]); // Number of variables

    float c = atof(argv[2]); // Density

    k = atoi(argv[3]); // value of k for the instance

    long seedForm = atol(argv[4]); //Seed for the random hash functions

    int option = atoi(argv[5]);
    
    int simNum= atoi(argv[6]);

    unsigned int m = (unsigned int) (c * n);

    gsl_rng_set(rng, seedForm);



    unsigned int num = n;
    float dens = 0.0;
    float i=1.0;
    
     if (option == 6)
         
     {
        cout <<"# n="<<n<<endl;
        while (dens < c) {

            cout<<dens<<"\t";
            RandomOrient(num, dens,simNum);

            dens += 0.001;
            //num = n * float(i);


        } 
        
     }
    
    if (option == 5)
         
     {
        cout <<"# n="<<n<<endl;
        while (dens < c) {

            cout<<dens<<"\t";
            levelOrient(num, dens,simNum);

            dens += 0.001;
            //num = n * float(i);


        } 
        
     }
    
     if (option == 4)
         
     {
         cout<<"#Size\t Max \t ErrorM\t Total\t  ErrorT "<<endl;
         int load = atoi(argv[7]);
        while (i < 50) {

            levelOrient_g(num, c, load,simNum);

            i += 1;
            num = n * float(i);


        } 
        
     }
    
    if (option == 3) {
      
        
        int simNum = atoi(argv[6]);
        for (int i = 0; i < simNum; i++) {
            gsl_rng_set(rng, seedForm);
            seedForm = seedForm + 100;
            RandomOrienthisto(n, c);

        }


    }
    if (option == 2) {
        int simNum = atoi(argv[6]);
        for (int i = 0; i < simNum; i++) {
            gsl_rng_set(rng, seedForm);
            seedForm = seedForm + 100;
            levelOrienthisto(n, c);

        }
        

    }
    if (option == 1)
        
    {  cout<<"#Size\t Max \t ErrorM\t Total\t  ErrorT "<<endl;
        while (i < 50) {
            
            levelOrient(num, c,simNum);
            gsl_rng_set(rng, seedForm);
            seedForm = seedForm + i;
            i += 0.5;
            num = n * float(i);


        }
    }else if (option == 0)
    {      
       cout<<"#Size\t Max \t ErrorM\t Total\t  ErrorT "<<endl;
        while (i < 50) {
            RandomOrient(num, c,simNum);
            gsl_rng_set(rng, seedForm);
            seedForm = seedForm + i;
            i += 0.5;
            num = n * float(i);
        }

    }
    freeAll();





    return 0;
}

void levelOrient(unsigned int n, float c, int simNum) {

    double avg = 0;
    unsigned int m = (unsigned int) (c * n);
    long total = 0;
       long *total_alloc=new long[simNum];
        long *max_alloc =new long[simNum];
        
       

  //  time_t start, end;
  //  time(&start);
    for (int iter = 0; iter < simNum; iter += 1) {
        

        
        // double avg = 0;

        int max_steps = 0;
        int *table = new int[n];
        fill(table, table + n, -1);

        int *lev = new int[n]; //levels
        fill(lev, lev + n, 0);

        It *item = new It[m];
        
     

        for (unsigned int num = 0; num < m; num++) {
            item[num].fillChoices(n);
        }

        total_alloc[iter]=0;
         max_alloc[iter]=0;
        for (unsigned int i = 0; i < m; ++i) {
            unsigned int curr_steps = 0;
            unsigned int curr = i;
            do {

                curr_steps++;

                unsigned int pos = 0;
                int firstmin = lev[item[curr].choices[pos]];
                int secondmin = firstmin;


                //choose the vertex with the lowest level
                for (int j = 1; j < k; j++) {

                    // cout<<"level "<<j<<" "<<lev[choices[j][curr]]<<"\n"<<lev[choices[pos][curr]];


                    if (lev[item[curr].choices[j]] < lev[item[curr].choices[pos]]) {
                        firstmin = lev[item[curr].choices[j]];
                        secondmin = lev[item[curr].choices[pos]];
                        pos = j;

                    }

                }
                
                
            if(pos==n-1)
            {
                cout<<"Allocation does not exist "<<endl;
                
                return;
            }

                int vertex = item[curr].choices[pos];


                if (table[vertex] == -1) {
                    table[vertex] = curr;
                    //Update the level
                    //
                    lev[vertex] = secondmin + 1;
                    break;
                }


                lev[vertex] = secondmin + 1;


                unsigned int new_elem = table[item[curr].choices[pos]];
                table[item[curr].choices[pos]] = curr;
                curr = new_elem;

            } while (true);
            
            

            total = total + curr_steps;
            total_alloc[iter]+=curr_steps;

            if (max_steps < curr_steps)
                max_steps = curr_steps;

            
            curr_steps = 0;
            
        }

        
        max_alloc[iter]=max_steps;
        avg += max_steps;

        //   for(unsigned int i=0; i<n; ++i) cout << table[i] << " ";
        //   cout << endl;


        for (int j = 0; j < m; j++)
            item[j].free();

        delete[] item;
        delete[] table;
        delete[] lev;
        



    }
        
        avg = avg*1.0/simNum;
        total = total*1.0/simNum;
    
    double std_total= 0; double std_max=0;
    for(int i=0;i<simNum;i++)
    {
        //cout<<"the total "<<total_alloc[i]<<"\t"<<max_alloc[i]<<endl;
        //cout<<"the difference "<< total_alloc[i]- total<<"\t"<<max_alloc[i]- avg<<endl;
        std_total+= pow((total_alloc[i]- total),2.0);
        std_max+= pow((max_alloc[i]- avg),2.0);
    }
    //time(&end);
   // std_total = std_total*1.0 /(simNum-1);
     //std_max = std_max/(simNum-1);
    std_total = sqrt(std_total*(1.0/simNum));
    std_max = sqrt(std_max*(1.0/simNum));
    
    cout <<n<<"\t"<<avg << "\t" <<std_max<<"\t"<< total << "\t"<<std_total<<endl;
    
    
    
    delete[] total_alloc;
    delete[] max_alloc;
}

void levelOrient_g(unsigned int n, float c, int load, int simNum) {

    double avg = 0;
    unsigned int m = int (c * n);
    double total = 0;

   // time_t start, end;
   // time(&start);
    
    long *total_alloc=new long[simNum];
        long *max_alloc =new long[simNum];
        
        
    for (int iter = 0; iter < simNum; iter += 1) {


        // double avg = 0;
        
        
        total_alloc[iter]=0;
         max_alloc[iter]=0;
      

        int max_steps = 0;
        vector<vector<int> > table;
        
        for (unsigned int i = 0; i < n; ++i) {
            
            vector< int> tmp;
            tmp.push_back(-1);
            table.push_back(tmp);
        }


        // int *table = new int[n];
        // fill(table, table + n, -1);

        int *lev = new int[n]; //levels
        fill(lev, lev + n, 0);

        It *item = new It[m];

        for (unsigned int num = 0; num < m; num++) {
            item[num].fillChoices(n);
        }


        for (unsigned int i = 0; i < m; ++i) {
            unsigned int curr_steps = 0;
            unsigned int curr = i;
            do {

                curr_steps++;

                unsigned int pos = 0;
                int firstmin = lev[item[curr].choices[pos]];
                int secondmin = firstmin;
               // cout<<"curr="<<"\t"<<curr<<endl;

                //choose the vertex with the lowest level
                for (int j = 1; j < k; j++) {

                    // cout<<"level "<<j<<" "<<lev[choices[j][curr]]<<"\n"<<lev[choices[pos][curr]];


                    if (lev[item[curr].choices[j]] < lev[item[curr].choices[pos]]) {
                        firstmin = lev[item[curr].choices[j]];
                        secondmin = lev[item[curr].choices[pos]];
                        pos = j;

                    }

                }
                
                     
            if(pos==n-1)
            {
                cout<<"Allocation does not exist "<<endl;
                
                return;
            }

                int vertex = item[curr].choices[pos];
                int size = table[vertex].size();

                  if ( table[vertex][0] == -1)
                 {
                     table[vertex][0] =curr;
                     break;
                 }

                if (size < load ) {
                    
                   
                    table[vertex].push_back(curr);
                  
                    if (table[vertex].size() >= load ) 
                        lev[vertex] = secondmin + 1;
                    
                    break;
                }

               

                lev[vertex] = secondmin + 1;

                
                
                unsigned int loc = (unsigned int) size * gsl_rng_uniform(prng);
                unsigned int new_elem = table[vertex][loc];
                
           table[vertex][loc] =curr;
                curr = new_elem;

            } while (true);

            total = total + curr_steps;
            total_alloc[iter]+=curr_steps;

            if (max_steps < curr_steps)
                max_steps = curr_steps;


            curr_steps = 0;
        }


     
        max_alloc[iter]=max_steps;
        avg += max_steps;

        //   for(unsigned int i=0; i<n; ++i) cout << table[i] << " ";
        //   cout << endl;


        for (unsigned int j = 0; j < m; j++)
            item[j].free();

        delete[] item;
        //delete[] table;
        delete[] lev;



    }
   // time(&end);
        
        
  avg = avg*1.0/simNum;
  total = total*1.0/simNum;
    
    double std_total= 0; double std_max=0;
    for(int i=0;i<simNum;i++)
    {
        //cout<<"the total "<<total_alloc[i]<<"\t"<<max_alloc[i]<<endl;
        //cout<<"the difference "<< total_alloc[i]- total<<"\t"<<max_alloc[i]- avg<<endl;
        std_total+= pow((total_alloc[i]- total),2.0);
        std_max+= pow((max_alloc[i]- avg),2.0);
    }
    //time(&end);
   // std_total = std_total*1.0 /(simNum-1);
     //std_max = std_max/(simNum-1);
    std_total = sqrt(std_total*(1.0/simNum));
    std_max = sqrt(std_max*(1.0/simNum));
    
    cout <<n<<"\t"<<avg << "\t" <<std_max<<"\t"<< total << "\t"<<std_total<<endl;
        
}

void levelOrienthisto(unsigned int n, float c) {


    int m = int (c * n);
    double total = 0;



    int max_steps = 0;
    vector <vector <int> > vec;
    int *table = new int[n];
    fill(table, table + n, -1);

    int *lev = new int[n]; //levels
    fill(lev, lev + n, 0);

    It *item = new It[m];

    for (unsigned int num = 0; num < m; num++) {
        item[num].fillChoices(n);
    }


    for (unsigned int i = 0; i < m; ++i) {
        unsigned int curr_steps = 0;
        unsigned int curr = i;
        do {

            curr_steps++;

            unsigned int pos = 0;
            int firstmin = lev[item[curr].choices[pos]];
            int secondmin = firstmin;


            //choose the vertex with the lowest level
            for (int j = 1; j < k; j++) {

                // cout<<"level "<<j<<" "<<lev[choices[j][curr]]<<"\n"<<lev[choices[pos][curr]];


                if (lev[item[curr].choices[j]] < lev[item[curr].choices[pos]]) {
                    firstmin = lev[item[curr].choices[j]];
                    secondmin = lev[item[curr].choices[pos]];
                    pos = j;

                }

            }

            int vertex = item[curr].choices[pos];


            if (table[vertex] == -1) {
                table[vertex] = curr;
                //Update the level
                //
                lev[vertex] = secondmin + 1;
                break;
            }


            lev[vertex] = secondmin + 1;


            unsigned int new_elem = table[item[curr].choices[pos]];
            table[item[curr].choices[pos]] = curr;
            curr = new_elem;

        } while (true);

        total = total + curr_steps;

        if (max_steps < curr_steps)
            max_steps = curr_steps;


        curr_steps = 0;
    }




    //   for(unsigned int i=0; i<n; ++i) cout << table[i] << " ";
    //   cout << endl;

    for (int j = 0; j < m; j++)
        item[j].free();

    delete[] item;
    delete[] table;
    delete[] lev;


    cout << n << "\t" << max_steps << "\t" << total << endl;
}

void RandomOrient(unsigned int n, float c, int simNum) {


    double avg = 0;
    double total = 0;
    unsigned int m = int (c * n);
   // time_t start, end;
   // time(&start);
    
     long *total_alloc=new long[simNum];
        long *max_alloc =new long[simNum];
        
       
    for (int iter = 0; iter < simNum; iter += 1) {
 total_alloc[iter]=0;
            max_alloc[iter]=0;

        // double avg = 0;

        int max_steps = 0;
        int *table = new int[n];
        fill(table, table + n, -1);

        int *lev = new int[n]; //levels
        fill(lev, lev + n, 0);

        It *item = new It[m];

        for (unsigned int num = 0; num < m; num++) {
            item[num].fillChoices(n);
        }


        for (unsigned int i = 0; i < m; ++i) {
            unsigned int curr_steps = 0;
            unsigned int curr = i;
            do {

                curr_steps++;


                unsigned int pos = (unsigned int) k * gsl_rng_uniform(prng);

                if (table[item[curr].choices[pos]] == -1) {
                    table[item[curr].choices[pos]] = curr;
                    break;
                }

                unsigned int new_elem = table[item[curr].choices[pos]];
                table[item[curr].choices[pos]] = curr;
                curr = new_elem;


            } while (true);

            total += curr_steps;
            total_alloc[iter]+=curr_steps;

            if (max_steps < curr_steps)
                max_steps = curr_steps;


            curr_steps = 0;
          
        }


        avg += max_steps;
        max_alloc[iter]=max_steps;

        //   for(unsigned int i=0; i<n; ++i) cout << table[i] << " ";
        //   cout << endl;

        for (unsigned int j = 0; j < m; j++)
            item[j].free();

        delete[] item;
        delete[] table;
        delete[] lev;



    }
   avg = avg*1.0/simNum;
        total = total*1.0/simNum;
    
    double std_total= 0; double std_max=0;
    for(int i=0;i<simNum;i++)
    {
        //cout<<"the total "<<total_alloc[i]<<"\t"<<max_alloc[i]<<endl;
        //cout<<"the difference "<< total_alloc[i]- total<<"\t"<<max_alloc[i]- avg<<endl;
        std_total+= pow((total_alloc[i]- total),2.0);
        std_max+= pow((max_alloc[i]- avg),2.0);
    }
    //time(&end);
   // std_total = std_total*1.0 /(simNum-1);
     //std_max = std_max/(simNum-1);
    std_total = sqrt(std_total*(1.0/simNum));
    std_max = sqrt(std_max*(1.0/simNum));
    
    cout <<n<<"\t"<<avg << "\t" <<std_max<<"\t"<< total << "\t"<<std_total<<endl;
    
    
    
    delete[] total_alloc;
        delete[] max_alloc;
}

void RandomOrienthisto(unsigned int n, float c) {



    double total = 0;
   unsigned int m = (unsigned int) (c * n);



    int max_steps = 0;
    int *table = new int[n];
    fill(table, table + n, -1);

    int *lev = new int[n]; //levels
    fill(lev, lev + n, 0);

    It *item = new It[m];

    for (unsigned int num = 0; num < m; num++) {
        item[num].fillChoices(n);
    }


    for (unsigned int i = 0; i < m; ++i) {
        unsigned int curr_steps = 0;
        unsigned int curr = i;
        do {

            curr_steps++;


            unsigned int pos = (unsigned int) k * gsl_rng_uniform(prng);

            if (table[item[curr].choices[pos]] == -1) {
                table[item[curr].choices[pos]] = curr;
                break;
            }

            unsigned int new_elem = table[item[curr].choices[pos]];
            table[item[curr].choices[pos]] = curr;
            curr = new_elem;


        } while (true);

        total += curr_steps;

        if (max_steps < curr_steps)
            max_steps = curr_steps;


        curr_steps = 0;
    }



    //   for(unsigned int i=0; i<n; ++i) cout << table[i] << " ";
    //   cout << endl;

    for (int j = 0; j < m; j++)
        item[j].free();

    delete[] item;
    delete[] table;
    delete[] lev;




    cout << n << "\t" << max_steps << "\t" << total << endl;

}

void It::fillChoices(unsigned int n) {
    for (int j = 0; j < k; j++) {
        unsigned int tempVar = (unsigned int) n * gsl_rng_uniform(rng);
        int pos = j - 1;
        while (pos >= 0) {
            while (tempVar == choices[pos])
                tempVar = (unsigned int) n * gsl_rng_uniform(rng);

            pos--;
        }

        choices.push_back(tempVar);
    }

}
