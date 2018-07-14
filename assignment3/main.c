#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"
#include "main.h"


/**A hospital priority queue simulation.  Patients arrive at random intervals from 0 to 14 minutes
 *after the previous patient (first patient arrives at time 0 minutes).
 *@param filename of formatted patient data (each line has name, priority, ailment code)
 **/
int main(int argc, char *argv[])
{
  FILE *fp;  //pointer to input data file containing patient data

  Heap *heap = createHeap(100,MIN_HEAP,&free,NULL,compareIntFunction);

  char patientName[100];    //the patient name read from the input file
  int  patientInitPriority; //the patient initial priority read from the input file
  char patientSymptom[3];   //the patient symptom/ailment code read from the input file
  int  arrivalTime = 0;     //the arrival time (in minutes) at the hospital from the start of the simulation

  srand(time(NULL)); //setting seed

  //open the input data file
  fp = fopen(argv[1], "r");


  printf("Data File Information \n");

  //read in the input data file and store the data into a priority queue/heap (sorted by arrival time)
  while(fscanf(fp, "%s %d %s", patientName, &patientInitPriority, patientSymptom)!=EOF)
  {

    PatientData *newData = malloc(sizeof(PatientData)*1);

    strcpy(newData->patientName,patientName);
    newData->patientInitPriority = patientInitPriority;
    strcpy(newData->patientSymptom, patientSymptom);
    newData->arrivalTime = arrivalTime;

    insertHeapNode(heap, (void*)newData);
    printf("Patient: %s \t Priority: %d \t Code: %s \t Arrival Time: %d\n",patientName,patientInitPriority,patientSymptom,arrivalTime);

    arrivalTime=arrivalTime +  (rand() % 15); //random arrival time between 0 and 14 min to next patient arriving

  }

  fclose(fp); //close the data file


  return 0;
}

int compareIntFunction(const void *first,const void *second)
{
  const PatientData* firstPatient = first;
  const PatientData* secondPatient = second;

  //printf("Comparing %d and %d\n",firstPatient->patientInitPriority,secondPatient->patientInitPriority );

  if(firstPatient->patientInitPriority==secondPatient->patientInitPriority)
  {
    //printf("0:equal\n");
    return 0;
  }
  else if(firstPatient->patientInitPriority>secondPatient->patientInitPriority)
  {
    //printf("1:first greater\n");
    return 1;
  }
  //printf("-1:second greater\n");
  return -1;
}
