#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<Windows.h>
#pragma warning(disable:4996)
void addRecord();
void displayRecord();
void searchRecord();
void modifyRecord();
void deleteRecord();
int menu();

typedef struct
{
	int no, pcode;
	char streetName[50], city[20], state[25], country[25];
}Address;

typedef struct
{
	int dateBirth, monthBirth, yearBirth;
}Birthday;

typedef struct
{
	char surname[20], fistName[20], lastName[20];
}Name;

typedef struct
{
	char phoneNo[15], homeNo[15];
}ContactNo;

typedef struct
{
	char name[30], mobileNo[15], relation[20];
}Emergency;

typedef struct
{
	char ID[10], gender, allergies[25], bloodType[3], mailAdress[40], job[40];
	Name name;
	Address address;
	Birthday birthday;
	ContactNo contactNo;
	Emergency emergency;
}PatientInfo;

void addRecord()
{
	char add;
	SYSTEMTIME t;
	GetLocalTime(&t);
	
	PatientInfo info;

	FILE*ptr;
	ptr = fopen("patientinfo.bin", "ab");
	if (ptr == NULL) 
	{
		printf("Unable to open the file !\n");
		exit(-1);
	}
	printf("Add Record\n");
	do {
		printf("Enter the name of patient \n");
		printf("Surname   >");
		rewind(stdin);
		scanf("%[^\n]", &info.name.surname);
		printf("Firstname >");
		rewind(stdin);
		scanf("%[^\n]", &info.name.fistName);
		printf("Lastname  >");
		rewind(stdin);
		scanf("%[^\n]", &info.name.lastName);
		printf("\nEnter the ID of patient >");
		rewind(stdin);
		scanf("%[^\n]", &info.ID);
		do {
			printf("Enter the gender (M for male F for female) >");
			rewind(stdin);
			scanf("%c", &info.gender);
			if (toupper(info.gender) != 'M' && toupper(info.gender) != 'F')
			{
				printf("Invalid gender have been entered\n");
				printf("Enter only F or M\n");
			}
		} while (toupper(info.gender) != 'M' && toupper(info.gender) != 'F');
		printf("Enter the blood type of patient >");
		rewind(stdin);
		scanf("%[^\n]", &info.bloodType);
		printf("\nEnter the address of patient\n");
		printf("House number >");
		rewind(stdin);
		scanf("%d", &info.address.no);
		printf("Street Name >");
		rewind(stdin);
		scanf("%[^\n]", &info.address.streetName);
		printf("Postcode >");
		rewind(stdin);
		scanf("%d", &info.address.pcode);
		printf("City   >");
		rewind(stdin);
		scanf("%[^\n]", &info.address.city);
		printf("State   >");
		rewind(stdin);
		scanf("%[^\n]", &info.address.state);
		printf("Country  >");
		rewind(stdin);
		scanf("%[^\n]", &info.address.country);
		printf("\nEnter the birthday of patient\n");
		do {
			printf("Date >");
			rewind(stdin);
			scanf("%d", &info.birthday.dateBirth);
			if (info.birthday.dateBirth < 1 || info.birthday.dateBirth>31)
			{
				printf("Invalid date have been entered\n");
				printf("Please Try Again\n\n");
			}
		} while (info.birthday.dateBirth < 1 || info.birthday.dateBirth>31);
		do {
			printf("Month >");
			rewind(stdin);
			scanf("%d", &info.birthday.monthBirth);
			if (info.birthday.monthBirth < 1 || info.birthday.monthBirth>12)
			{
				printf("Invalid month have been entered\n");
				printf("Please Try Again\n\n");
			}
		} while (info.birthday.monthBirth < 1 || info.birthday.monthBirth>12);
		do {
			printf("Year  >");
			rewind(stdin);
			scanf("%d", &info.birthday.yearBirth);
			if(info.birthday.yearBirth < 1900 || info.birthday.yearBirth>t.wYear)
			{
				printf("Invalid year have been entered\n");
				printf("Please Try Again\n\n");
			}
		} while (info.birthday.yearBirth < 1900 || info.birthday.yearBirth>t.wYear);
		printf("\nEnter the contact number of patient\n");
		printf("Phone number >");
		rewind(stdin);
		scanf("%[^\n]", &info.contactNo.phoneNo);
		printf("Home number  >");
		rewind(stdin);
		scanf("%[^\n]", &info.contactNo.homeNo);
		printf("Enter the email address of patient >");
		rewind(stdin);
		scanf("%[^\n]", &info.mailAdress);
		printf("Enter the job of patient >");
		rewind(stdin);
		scanf("%[^\n]", &info.job);
		printf("Allergies (if have) >");
		rewind(stdin);
		scanf("%[^\n]", &info.allergies);
		printf("\nEnter the information of people to contact for any emergency\n");
		printf("Name >");
		rewind(stdin);
		scanf("%[^\n]", &info.emergency.name);
		printf("Phone number >");
		rewind(stdin);
		scanf("%[^\n]", &info.emergency.mobileNo);
		printf("Relationship with patient >");
		rewind(stdin);
		scanf("%[^\n]", &info.emergency.relation);
		fwrite(&info, sizeof(PatientInfo), 1, ptr);
		printf("Add more record ? (Y for yes)");
		rewind(stdin);
		scanf("%c", &add);
	} while (toupper(add) == 'Y');
	printf("\n\n");
	fclose(ptr);
}

void displayRecord()
{
	int record = 0;
	
	PatientInfo info;

	FILE*fptr;
	fptr = fopen("patientinfo.bin", "rb");
	if (fptr == NULL)
	{
		printf("Unable to open the file !\n");
		exit(-1);
	}
	printf("Display Record\n");
	printf("============================================================\n");
	while (fread(&info, sizeof(PatientInfo), 1, fptr) != 0)
	{
		printf("%d\n", record + 1);
		printf("Name                         > %s %s %s\n", info.name.surname, info.name.fistName, info.name.lastName);
		printf("ID                           > %s\n", info.ID);
		printf("Birthday                     > %02d / %02d / %4d\n", info.birthday.dateBirth, info.birthday.monthBirth, info.birthday.yearBirth);
		if (toupper(info.gender) == 'M')
			printf("Gender                       > Male\n");
		else printf("Gender                       > Female\n");
		printf("Address                      > %d , %s \n", info.address.no, info.address.streetName);
		printf("                               %d %s \n", info.address.pcode, info.address.city);
		printf("                               %s %s\n", info.address.state, info.address.country);
		printf("Blood Type                   > %s\n", info.bloodType);
		printf("Job                          > %s\n", info.job);
		printf("Allergies                    > %s\n", info.allergies);
		printf("Contact Number\n");
		printf("Phone Number                 > %s\n", info.contactNo.phoneNo);
		printf("Home Number                  > %s\n", info.contactNo.homeNo);
		printf("Email Address                > %s\n", info.mailAdress);
		printf("\nEmergency Contact\n");
		printf("Name                         > %s\n", info.emergency.name);
		printf("Relationship with patient    > %s\n", info.emergency.relation);
		printf("Contact Number               > %s\n\n\n", info.emergency.mobileNo);
		record++;
	}
	printf("============================================================\n");
	printf("<%d records in the file>\n\n", record);
	fclose(fptr);
}

void searchRecord()
{
	char search[15];
	int i = 0, count = 0, j = 0, sResult;
	
	PatientInfo info[200];

	FILE*fptr;
	fptr = fopen("patientinfo.bin", "rb");
	if (fptr == NULL)
	{
		printf("Unable to open the file !\n");
		exit(-1);
	}
	printf("Search Record\n");
	printf("Enter the patient's ID to search >");
	rewind(stdin);
	scanf("%[^\n]", &search);

	while (fread(&info[i], sizeof(PatientInfo), 1, fptr) != 0)
	{
		i++;
		count++;
	}
	for (j = 0; j < count; j++)
	{
		sResult = 0;
		if (strcmp(search, info[j].ID) == 0)
		{
			printf("Name                         > %s %s %s\n", info[j].name.surname, info[j].name.fistName, info[j].name.lastName);
			printf("Birthday                     > %02d / %02d / %4d\n", info[j].birthday.dateBirth, info[j].birthday.monthBirth, info[j].birthday.yearBirth);
			if (toupper(info[j].gender) == 'M')
				printf("Gender                       > Male\n");
			else printf("Gender                       > Female\n");
			printf("Address                      > %d , %s \n", info[j].address.no, info[j].address.streetName);
			printf("                               %d %s \n", info[j].address.pcode, info[j].address.city);
			printf("                               %s %s\n", info[j].address.state, info[j].address.country);
			printf("Blood Type                   > %s\n", info[j].bloodType);
			printf("Job                          > %s\n", info[j].job);
			printf("Allergies                    > %s\n", info[j].allergies);
			printf("Contact Number\n");
			printf("Phone Number                 > %s\n", info[j].contactNo.phoneNo);
			printf("Home Number                  > %s\n", info[j].contactNo.homeNo);
			printf("Email Address                > %s\n", info[j].mailAdress);
			printf("\nEmergency Contact\n");
			printf("Name                         > %s\n", info[j].emergency.name);
			printf("Relationship with patient    > %s\n", info[j].emergency.relation);
			printf("Contact Number               > %s\n\n", info[j].emergency.mobileNo);
			sResult = 1;
		}
	}
	if (sResult == 0)
		printf("\nNo Record Found !!!\n\n");
	fclose(fptr);
}

void modifyRecord()
{
	int i = 0, count = 0, sResult = 0;
	char modify, sure;

	PatientInfo info[200];
	PatientInfo infoModify;
	SYSTEMTIME t;
	GetLocalTime(&t);

	FILE*fptr;
	fptr = fopen("patientinfo.bin", "rb");
	if (fptr == NULL)
	{
		printf("Unable to open the file !");
		exit(-1);
	}

	while (fread(&info[i], sizeof(PatientInfo), 1, fptr) != 0)
	{
		i++;
		count++;
	}
	printf("Modify Record\n");
	do
	{
		printf("Enter the patient's ID to modify >");
		rewind(stdin);
		scanf("%[^\n]", &infoModify.ID);
		i = 0;
		while (i < count)
		{
			if (strcmp(infoModify.ID, info[i].ID) == 0)
			{
				sResult = 1;
				printf("Enter the new name of patient \n");
				printf("Surname   >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.name.surname);
				printf("Firstname >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.name.fistName);
				printf("Lastname  >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.name.lastName);
				do {
					printf("Enter the new gender (M for male F for female) >");
					rewind(stdin);
					scanf("%c", &infoModify.gender);
					if (toupper(infoModify.gender) != 'M' && toupper(infoModify.gender) != 'F')
					{
						printf("Invalid gender have been entered\n");
						printf("Enter only F or M\n");
					}
				} while (toupper(infoModify.gender) != 'M' && toupper(infoModify.gender) != 'F');
				printf("Enter the new blood type of patient >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.bloodType);
				printf("\nEnter the new address of patient\n");
				printf("House number >");
				rewind(stdin);
				scanf("%d", &infoModify.address.no);
				printf("Street Name >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.address.streetName);
				printf("Postcode >");
				rewind(stdin);
				scanf("%d", &infoModify.address.pcode);
				printf("City   >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.address.city);
				printf("State   >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.address.state);
				printf("Country  >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.address.country);
				printf("\nEnter the new birthday of patient\n");
				do {
					printf("Date >");
					rewind(stdin);
					scanf("%d", &infoModify.birthday.dateBirth);
					if (infoModify.birthday.dateBirth < 1 || infoModify.birthday.dateBirth>31)
					{
						printf("Invalid date have been entered\n");
						printf("Please Try Again\n\n");
					}
				} while (infoModify.birthday.dateBirth < 1 || infoModify.birthday.dateBirth>31);
				do {
					printf("Month >");
					rewind(stdin);
					scanf("%d", &infoModify.birthday.monthBirth);
					if (infoModify.birthday.monthBirth < 1 || infoModify.birthday.monthBirth>12)
					{
						printf("Invalid month have been entered\n");
						printf("Please Try Again\n\n");
					}
				} while (infoModify.birthday.monthBirth < 1 || infoModify.birthday.monthBirth>12);

				do {
					printf("Year  >");
					rewind(stdin);
					scanf("%d", &infoModify.birthday.yearBirth);
					{
						printf("Invalid year have been entered\n");
						printf("Please Try Again\n\n");
					}
				} while (infoModify.birthday.yearBirth < 1900 || infoModify.birthday.yearBirth>t.wYear);
				printf("\nEnter the new contact number of patient\n");
				printf("Phone number >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.contactNo.phoneNo);
				printf("Home number  >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.contactNo.homeNo);
				printf("Enter the new email address of patient >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.mailAdress);
				printf("Enter the new job of patient >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.job);
				printf("New Allergies (if have) >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.allergies);
				printf("\nEnter the new information of people to contact for any emergency\n");
				printf("Name >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.emergency.name);
				printf("Phone number >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.emergency.mobileNo);
				printf("Relationship with patient >");
				rewind(stdin);
				scanf("%[^\n]", &infoModify.emergency.relation);
				printf("Sure to Modify ? (Y for yes)");
				rewind(stdin);
				scanf("%c", &sure);
				if (toupper(sure) == 'Y')
					info[i] = infoModify;
			}
			i++;
		}
		if (sResult == 0)
		{
			printf("\nNo Record Found !!!\n\n");
			modify = 'n';
		}
		else 
		{
			printf("Continue to modify other patient's record ? (Y for yes)");
			rewind(stdin);
			scanf("%c", &modify);
		}
	} while (toupper(modify) == 'Y');
	printf("\n\n");
	fclose(fptr);

	FILE *ptr;
	ptr = fopen("patientinfo.bin", "wb");
	if (ptr == NULL)
	{
		printf("Unable to open the file !\n");
		exit(-1);
	}

	fwrite(info, sizeof(PatientInfo), count, ptr);
	fclose(ptr);

}

void deleteRecord()
{
	int i = 0, count = 0, sResult = 0, j, nCount = 0;
	char delete, sure;

	PatientInfo info[200];
	PatientInfo infoDelete;

	FILE*fptr;
	fptr = fopen("patientinfo.bin", "rb");
	if (fptr == NULL)
	{
		printf("Unable to open the file !");
		exit(-1);
	}

	while (fread(&info[i], sizeof(PatientInfo), 1, fptr) != 0)
	{
		i++;
		count++;
	}
	do{
	printf("Enter the patient's ID to delete >");
	rewind(stdin);
	scanf("%[^\n]", &infoDelete.ID);
	i = 0;
	while (i < count)
	{
		if (strcmp(infoDelete.ID, info[i].ID) == 0)
		{
			sResult = 1;
			printf("Sure to Delete ? (Y for yes)");
			rewind(stdin);
			scanf("%c", &sure);
			if (toupper(sure) == 'Y')
			{
				for (j = i; j < count; j++)
				{
					info[j] = info[j + 1];
					nCount++;
				}
				count -= nCount;
			}
		}
		i++;
	}
	if (sResult == 0)
	{
		printf("\nNo Record Found !!!\n\n");
		delete = 'n';
	}
	else
	{
		printf("Continue to delete other patient's record ? (Y for yes)");
		rewind(stdin);
		scanf("%c", &delete);
	}
	} while (toupper(delete) == 'Y');
	printf("\n\n");
	fclose(fptr);

	FILE *ptr;
	ptr = fopen("patientinfo.bin", "wb");
	if (ptr == NULL)
	{
		printf("Unable to open the file !\n");
		exit(-1);
	}

	fwrite(info, sizeof(PatientInfo), count, ptr);
	fclose(ptr);


}
int menu()
{
	int choice;
	SYSTEMTIME t;
	GetLocalTime(&t);
	printf("%02d-%02d-%d %02d:%02d\n", t.wDay, t.wMonth, t.wYear, t.wHour, t.wMinute);
	printf("Patient Information\n");
	printf("=============================\n");
	printf("1.Add record \n");
	printf("2.Display record \n");
	printf("3.Search record \n");
	printf("4.Modify record \n");
	printf("5.Delete record \n");
	printf("6.Exit \n");
	printf("=============================\n\n");
	printf("Please enter your choice >");
	rewind(stdin);
	scanf("%d", &choice);
	return choice;
}
void main()
{
	int choice;
	do {
		choice = menu();
		switch (choice)
		{
		case 1:
			addRecord();
			break;
		case 2:
			displayRecord();
			break;
		case 3:
			searchRecord();
			break;
		case 4:
			modifyRecord();
			break;
		case 5:
			deleteRecord();
			break;
		case 6:
			exit(-1);
			break;
		default:
		{
			printf("\nInvalid selection\n");
			printf("Please try again\n\n");
		}
		}
	} while (choice !=  6);
		system("pause");
}