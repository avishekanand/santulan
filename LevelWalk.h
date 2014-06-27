/* 
 * File:   LevelWalk.h
 * Author: mbk-11-22
 *
 * Created on December 28, 2012, 1:22 PM
 */

#ifndef LEVELWALK_H
#define	LEVELWALK_H



#include<iostream>
#include<cstdlib>
#include<ctime>
#include<algorithm>
#include<fstream>
#include<string>
#include<vector>
#include<math.h>

#include <gsl/gsl_rng.h>
    using namespace std;
    
 int k;
 
 
const gsl_rng_type * randGen;
gsl_rng *rng, *prng;

void RandomOrient(unsigned int n, float c, int simNum);
void levelOrient(unsigned int n, float c, int simNum);
void levelOrient_g(unsigned int n, float c, int load, int simNum);
void levelOrienthisto(unsigned int n, float c) ;
void RandomOrienthisto(unsigned int n, float c);
    
typedef struct 
{

    vector <unsigned int> choices;
    
    void fillChoices(unsigned int n);

    void free()
    {
        
    }
    
}It;




#endif	/* LEVELWALK_H */

