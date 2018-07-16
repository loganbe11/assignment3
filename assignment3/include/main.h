#ifndef MAIN_H_INCLUDED
#define MAIN_H_INCLUDED

int compareIntFunction(const void *first,const void *second);

void printDataFunction( void *data);
typedef struct PatientData
{
  char patientName[100];
  int patientInitPriority;
  char patientSymptom[3];
  int arrivalTime;
} PatientData;
#endif // MAIN_H_INCLUDED
