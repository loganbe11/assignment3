#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "heap.h"
#include "main.h"

FILE *fpOut; //output file for report.txt

/**A hospital priority queue simulation.  Patients arrive at random intervals from 0 to 11 minutes
 *after the previous patient (first patient arrives at time 0 minutes).
 *@param filename of formatted patient data (each line has name, priority, ailment code)
 **/
int main(int argc, char *argv[])
{
  FILE *fp;  //pointer to input data file containing patient data
  Heap *heap = createHeap(100,MIN_HEAP,&free,printDataFunction,compareIntFunction);

  char patientName[100];    //the patient name read from the input file
  int  patientInitPriority; //the patient initial priority read from the input file
  char patientSymptom[3];   //the patient symptom/ailment code read from the input file

  int i = 0;

  int  arrivalTime = 0;     //the arrival time (in minutes) at the hospital from the start of the simulation

  int  gpTime = 0;     //the GP's time when she can see the next patient (in minutes) from the start of the simulation
  int  spTime = 0;     //the specialist's time when she can see the next patient (in minutes) from the start of the simulation

  char specialistField[3]= "--";  //set to "--" if no specialist is available

  PatientData *topPatient = NULL;  //a pointer to the patient data that the doctors use to scan the priority queue

  srand(time(NULL)); //setting seed

  //open the input data file
  fp = fopen(argv[1], "r");

  //open the output file report.txt for writing
  fpOut = fopen("report.txt","w");

  //Print out a header line or two in the output file
  fprintf(fpOut,"Order of Treatment: data file: %s \n",argv[1]);
  fprintf(fpOut,"--------------------------------------------\n");

  //print out some terminal information while program is running
  printf("Data File Information \n");

  //read in the input data file and store the data into a priority queue/heap (sorted by arrival time)
  while(fscanf(fp, "%s %d %s", patientName, &patientInitPriority, patientSymptom)!=EOF)
  {

    PatientData *newData = malloc(sizeof(PatientData)*1);
    strcpy(newData->patientName,patientName);
    newData->patientInitPriority = patientInitPriority;
    strcpy(newData->patientSymptom, patientSymptom);
    newData->arrivalTime = arrivalTime;

    printf("Patient Name: %s \t Patient Priority: %d \t Code: %s \t Arrival Time: %d\n",patientName,patientInitPriority,patientSymptom,arrivalTime);

    //Have the specialist examine the priority queue for his specialty and pull out the highest in the queue that matches
    i = 0;
    while(heap->nodeArray[i].data!=NULL)
    {
      topPatient=heap->nodeArray[i].data;

      //check to see if this patient can be treated by the specialist
      if(  (strcmp(topPatient->patientSymptom,specialistField) == 0))
      {
        //the specialist found a patient to treat, put it at the top of the queue and then remove it from the queue (this reheapifies)
        heap->nodeArray[99].data=heap->nodeArray[i].data;
        heap->nodeArray[i].data=heap->nodeArray[0].data;
        heap->nodeArray[0].data=heap->nodeArray[99].data;
        heap->nodeArray[99].data = NULL;

        //if the arrival time of this patient was after the specialist was ready to see them, set the specialist time to their arrival time
        if (topPatient->arrivalTime > spTime)
        {
          spTime = topPatient->arrivalTime;
        }

        printf("SP treating at time %d\t",spTime);
        fprintf(fpOut,"SP treating at time %d\t",spTime);
        printDataFunction(heap->nodeArray[0].data);
        deleteMinOrMax(heap);
        spTime = spTime + 11;  //add 11 minutes to the time the specialist is next available to see a patient
      }
      i++;
    }


    //Have the GP treat the top of the queue if he is available
    while( arrivalTime >= gpTime)
    {
      //if the queue is empty then set the GP time to the next arrival time
      if(heap->nodeArray[0].data==NULL)
      {
        gpTime = arrivalTime;
        break;
      }
      else
      {

        printf("GP treating at time %d\t",gpTime);
        fprintf(fpOut,"GP treating at time %d\t",gpTime);
        printDataFunction(heap->nodeArray[0].data);

        deleteMinOrMax(heap);
        gpTime = gpTime + 10;
      }
    }

    insertHeapNode(heap, (void*)newData);
    arrivalTime=arrivalTime +  (rand() % 11); //random arrival time between 0 and 110 min to next patient arriving
  }

  fclose(fp); //close the data file

  //no further patient arrive

  //Have the specialist examine the priority queue for his specialty and pull out the highest in the queue that matches
  i = 0;
  while(heap->nodeArray[i].data!=NULL)
  {
    topPatient=heap->nodeArray[i].data;

    //check to see if this patient can be treated by the specialist
    if(  (strcmp(topPatient->patientSymptom,specialistField) == 0))
    {
      //the specialist found a patient to treat, put it at the top of the queue and then remove it from the queue (this reheapifies)
      heap->nodeArray[99].data=heap->nodeArray[i].data;
      heap->nodeArray[i].data=heap->nodeArray[0].data;
      heap->nodeArray[0].data=heap->nodeArray[99].data;
      heap->nodeArray[99].data = NULL;

      //if the arrival time of this patient was after the specialist was ready to see them, set the specialist time to their arrival time
      if (topPatient->arrivalTime > spTime)
      {
        spTime = topPatient->arrivalTime;
      }

      printf("SP treating at time %d\t",spTime);
      fprintf(fpOut,"SP treating at time %d\t",spTime);
      printDataFunction(heap->nodeArray[0].data);
      deleteMinOrMax(heap);
      spTime = spTime + 11;  //add 11 minutes to the time the specialist is next available to see a patient
    }
    i++;
  }

  while(heap->nodeArray[0].data!=NULL)
  {
    printf("GP treating at time %d\t",gpTime);
    fprintf(fpOut,"GP treating at time %d\t",gpTime);
    printDataFunction(heap->nodeArray[0].data);
    deleteMinOrMax(heap);
    gpTime = gpTime + 10;
  }
  fclose(fpOut);


  return 0;
}

int compareIntFunction(const void *first,const void *second)
{
  const PatientData* firstPatient = first;
  const PatientData* secondPatient = second;
  float PriorityWithAgeOne = firstPatient->patientInitPriority + (firstPatient->arrivalTime - 200)*0.03;
  float PriorityWithAgeTwo = secondPatient->patientInitPriority + (secondPatient->arrivalTime - 200)*0.03;


  //printf("Comparing %d and %d\n",firstPatient->patientInitPriority,secondPatient->patientInitPriority );

  if(PriorityWithAgeOne==PriorityWithAgeTwo)
  {
    //printf("0:equal\n");
    return 0;
  }
  else if(PriorityWithAgeOne>PriorityWithAgeTwo)
  {
    //printf("1:first greater\n");
    return 1;
  }
  //printf("-1:second greater\n");
  return -1;
}

void printDataFunction(void *data)
{
  PatientData* patient = data;

  printf("Patient Name: %s \t Patient Priority: %d \t Code: %s \t Arrival Time: %d\n",patient->patientName,patient->patientInitPriority,patient->patientSymptom,patient->arrivalTime);
  fprintf(fpOut,"Patient Name: %s \t Patient Priority: %d \t Code: %s \t Arrival Time: %d\n",patient->patientName,patient->patientInitPriority,patient->patientSymptom,patient->arrivalTime);

  return;
}
