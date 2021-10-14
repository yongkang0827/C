#include<stdio.h>
#include<stdlib.h>
#pragma warning(disable:4996)
#define SST 0.1;
#define STD 0.2;
int menu(void);
void logo(void);

int menu(void)
{
	printf("COMBO A= RM 7.00\n=> Fried Chicken + French Fries + Salad + Drinks\n");
	printf("COMBO B= RM 9.00\n=> Burger + French Fries + Salad + Drinks\n");
	printf("COMBO C= RM 12.00\n=> 2 Fried Chickens + Chicken Rice + Potato + Drinks\n");
	printf("COMBO D= RM 17.00\n=> Fried chicken + Burger + Potato + Drinks \n\n");
}	
void logo(void)
{
	printf("                                                          =======\n");
	printf("                                                          |K   K|\n");
	printf("                                                          |K K  |\n");
	printf("                                                          |KK   |\n");
	printf("                                                          |K K  |\n");
	printf("                                                          |K   K|\n");
	printf("                                                          =======\n");
	printf("                                                          K'DONALD\n");
}

int main()
{
	int qty, customer = 0, a = 0, b = 0, c = 0, d = 0;
	char combo, extraCombo, next, dining, student;
	double price, total = 0, totalPrice = 0, change, payment, comboPrice, salesAllDay = 0, sstCollect = 0, totalSST = 0, salesA, salesB, salesC, salesD, stdDiscount;
	do
	{
		customer += 1;
		printf("\nCustomer no %d\n", customer);
		logo();
		menu();
		do
		{
			printf("Enter the combo selected              >");
			rewind(stdin);
			scanf("%c", &combo);
			printf("Enter the quantity of combo selected  >");
			rewind(stdin);
			scanf("%d", &qty);
			printf("You have selected %d of COMBO %c.\n", qty, combo);
			switch (combo)
			{
			case'A':
			case'a':
				comboPrice = 7;
				a += qty;
				break;
			case'B':
			case'b':
				comboPrice = 9;
				b += qty;
				break;
			case'C':
			case'c':
				comboPrice = 12;
				c += qty;
				break;
			case'D':
			case'd':
				comboPrice = 17;
				d += qty;
				break;
			default:
				printf("ERROR!\n");
				comboPrice = 0;
			}
			price = comboPrice * qty;
			printf("Combo %c : %d @ RM%.2f                  =RM %.2f \n", combo, qty, comboPrice, price);
			total += price;
			printf("Any more combo to order (Y for yes )?");
			rewind(stdin);
			scanf("%c", &extraCombo);
		} while (extraCombo != 'N');
		printf("\nTake away or dining here\n(T for take away and D for dining here)");
		rewind(stdin);
		scanf("%c", &dining);
		printf("student?(with showing student card)\n(Y for Yes)\n");
		rewind(stdin);
		scanf("%c", &student);
		if (student == 'Y')
		{
			printf("Student Discount 20%% \n\n");
		}
		printf("==========================================\n");
		printf("Total combo price     >RM %.2f\n", total);
		if (student == 'Y')
		{
			stdDiscount = total * STD;
			total -= stdDiscount;
			printf("Student discount      >RM %.2f\n", stdDiscount);
		}
		sstCollect = total * SST;
		totalSST += sstCollect;
		totalPrice = total + total * SST;
		printf("SST charges           >Rm %.2f\n", sstCollect);
		printf("The total price       >RM %.2f\n", totalPrice);
		printf("MOney paid            >RM ");
		scanf("%lf", &payment);
		change = payment - totalPrice;
		printf("Change                >RM %.2f\n", change);
		printf("Thank you for coming K'DONALD .\n We are welcome you for your next time dining.\nHave a good day !\n\n");
		total = 0;
		salesAllDay += totalPrice;
		printf("Next customer?(Y for yes)");
		rewind(stdin);
		scanf("%c", &next);
	} while (next != 'N');
	salesA = a * 7;
	salesB = b * 9;
	salesC = c * 12;
	salesD = d * 17;
	printf("\n\n\nDaily Sales Report\n");
	printf("==============================================\n");
	printf("Total customer dining today   >%d\n", customer);
	printf("Quantity of Combo A sales     >%d\n", a);
	printf("Total Sales of Combo A        >RM %.2f\n", salesA);
	printf("Quantity of Combo B sales     >%d\n", b);
	printf("Total Sales of Combo B        >RM %.2f\n", salesB);
	printf("Quantity of Combo C sales     >%d\n", c);
	printf("Total Sales of Combo C        >RM %.2f\n", salesC);
	printf("Quantity of Combo D sales     >%d\n", d);
	printf("Total Sales of Combo D        >RM %.2f\n", salesD);
	printf("Total Quantity Sold           >%d\n", a + b + c + d);
	printf("Total amount of Combo Sales   >RM %.2f\n", salesA + salesB + salesC + salesD);
	printf("Total SST collected           >RM %.2f\n", totalSST);
	printf("Total sales in this day       >RM %.2f\n", salesAllDay);
	printf("It time to break.\nHave a nice day .\nThank you K'DONALD for having you.\n");
	system("pause");
}