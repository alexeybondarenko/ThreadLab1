//
//  main.cpp
//  Thread1
//
//  Created by Alexey Bondarenko on 2/18/15.
//  Copyright (c) 2015 Alexey Bondarenko. All rights reserved.
//

#include <iostream>

#include <cstdlib>
#include <pthread.h>
#include <thread>

#define NUMBER 100
#define THREAD_COUNT 20

using namespace std;

static float minValue = NULL;
static float maxValue = NULL;
static unsigned long int counter = 0;

void compare (float value) {
    if (value < minValue) {
        minValue = value;
    } else if (value > maxValue) {
        maxValue = value;
    }
}

struct thread_num {
    long int start;
    long int end;
    float * array;
};

void compareLoop (thread_num td) {
    for (long int i = td.start; i < td.end; i++)
        compare(*(td.array+i));
}

void minMax (long int numbers_count, int thread_cout)
{
    float *arr;
    long int i;
    arr = (float *) malloc (numbers_count * sizeof(float));
    for (i=0; i< numbers_count; i++) {
        arr[i] = i;
    }
    
    unsigned long int range = numbers_count / thread_cout;
    thread_num td;
    td.array = arr;
    
    clock_t start, stop;
    start = clock();
    
    thread *threads = new thread[thread_cout];
    for (i = 0; i < thread_cout; i++) {
        td.start = i * range;
        td.end = td.start + range;
        threads[i] = thread(compareLoop, td);
    }

    for (i = 0; i < thread_cout; i++) {
        threads[i].join();
    }
    stop = clock ();
    
    cout << minValue << ":"<<maxValue << "  "<< (stop - start) / CLOCKS_PER_SEC <<"ss"<<endl;
    
    delete [] threads;
}

void compareLoop2 (long int count) {
    for (unsigned long int i = 0; i < count; i++) {
        counter ++;
        compare(rand());
    }
}


int main () {
   
    long int numb = 1e+8,
        thread_count = 2,
        range = numb / thread_count;
    
    cout << "range " << range << endl;
    clock_t start, stop;
    start = clock();

    thread t1 (compareLoop2, range);
    thread t2 (compareLoop2, range);
    t1.join();
    t2.join();
//    thread *threads = new thread[thread_count];
//    for (i = 0; i < thread_count; i++) {
//        threads[i] = thread(compareLoop2, range);
//    }
//    
//    for (i = 0; i < thread_count; i++) {
//        threads[i].join();
//    }
    stop = clock ();
    cout << counter << " -> "<< minValue << ":"<<maxValue << "  "<< (stop - start) / (CLOCKS_PER_SEC / 1000)  <<"ms"<<endl;
    
//    delete [] threads;
    return 0;
}
