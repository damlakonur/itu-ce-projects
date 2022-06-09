; BLG 212E HW 1 - Question 4
; Recursive Computation of the Power Function in O(log(a)) Time
; 
;
; Student Name: 	Serife Damla Konur
; Student Number: 	040160433
; Description: (Please provide a short description of your approach to solving this problem)
; 
; In this question, I wrote 3 subroutines. In algorithm 4, first the pow(x,0) is calculated recursively 
; and then value of the modulo is checked and according to result multiplications are done for return value. 
;  In algorithm 3, there was no need to store modulo values in stack because the modulo was calculated and 
; was checked consecutively in each step, but in here I store the R4(modulo) values in the stack 
; in each step when base value is reached I popped the modulo values and according to them program 
; branched for bottom up calculations.

y_size		EQU 0x4                                 ;Allocate 4 bytes of space for an 
	
			AREA	output, DATA, READWRITE			;Define area to write the output
			ALIGN 
y 			SPACE y_size 							;Define y as the output 
y_end 
			AREA recursivePowerLogN, CODE, READONLY	;Declare New Area
			ENTRY
			THUMB
			ALIGN
__main		FUNCTION								;Define main function
			EXPORT __main	
			;Your code starts here
			MOVS	R0, #x							; Move symbolic 'x' value to r1
			MOVS	R1, #a							; Move symbloic 'a' value to r2
			LDR		R6, =y							; Load start address of the allocated space 
			MOVS	R7, #0							; initial value of modulo variable
			
			PUSH	{R7}							; push r7 to stack to be used as argument 
			PUSH	{R1}							; push r1 to stack to be used as argument
			BL		pow								; branch with link to function pow, and store its return address in LR 
			STR		R3, [R6]						; finally, store the result value at address of the allocated space		
stop		B		stop							; end of the code

pow			POP		{R1}							; pop r1 which is the parameter 'a'
			POP		{R7}							; pop r7 which is modulo parameter
			MOVS	R7, #0							; for each recursive call, r7 is initialized as 0
			CMP		R1, #0							; check whether a == 0 or not
			PUSH	{R7}							; push the r7 into the stack for subroutines
			PUSH	{R1}							; push the r1 into the stack for subroutines
			BNE		temp							; if a!=0 then branch to recursion
			POP		{R1}							; if a == 0 then pop the r1
			POP		{R7}							; then pop the r7
			MOVS	R3, #1							; if a==0 then pow(x,0) = 1, move 1 to r3, r3 is used to keep result
			PUSH	{R3}							; push into the stack for bottom up calculation
			BX		LR								; then return using return address
			
													; if a != 0 then recursively calculate pow(x,a/2)			
													; in this subroutine, the two numbers is divided by repeated subtraction
													; a/b ->  R1 = a  2 = b
temp		POP		{R1}							; pop r1, r1 keeps exponent(a) value
			POP 	{R7}							; pop r7, r7 will keep modulo value
			ADDS    R7, R7, #1						; for each iteration of 'temp' increase r7 by 1
			SUBS	R1, R1, #2						; for each iteration of 'temp' decrease r1 by 2, a = a-b
			PUSH	{R7}							; push again the r7 into the stack
			PUSH    {R1}							; push again the r1 into the stack
			BPL		temp							; if a=r1 >= 0 branch to 'temp' and repeat same operations
			POP		{R1}							; when a=r1 becomes negative pop R1
			POP 	{R7}							; pop R7
			PUSH	{LR}							; push return address into the stack
			ADDS	R4, R1, #2						; R4 is the temp R4 = R1 + 2 modulo / remainder of division
			SUBS	R1, R7, #1						; R1 is the quotient / result of the division a = a/b
			PUSH	{R4}							; according to algo. 4 we have to keep modulo values for bottom up calculations
			PUSH	{R7}							; push the r7 into the stack
			PUSH	{R1}							; push the a/2 into the stack
			BL		pow								; then branch to function pow with link, in order to calculate 'temp'
													; after the calculations of temp till the base value
													; the bottom value is obtained pow(x,0)=1
													; after that
													; program returns here and starts bottom up calculations
			POP		{R3}							; pop the R3 which keeps return value	
			POP		{R4}							; pop the R4 which keeps modulo value
			CMP		R4, #0							; check the is modulo == 0 or not
			BEQ		recur1							; if modulo is equal to 0 branch to 'recur1' subroutine
			POP		{R5}							; pop the return address from the stack
			MULS	R3, R3, R3						; if mod != 0 return value is x*pow(x,a/2)*pow(x,a/2)
			MULS	R3, R0, R3						; obtain x*pow(x,a/2)*pow(x,a/2)
			PUSH	{R3}							; push return value into the stack
			BX		R5								; finally branch the address at the top of the stack

													; if modulo is zero program branches recur1 subroutine
recur1		POP		{R5}							; pop the return address from the stack
			MULS	R3, R3, R3						; if mod == 0 return value is pow(x,a/2)*pow(x,a/2)
			PUSH	{R3}							; push return value into the stack
			BX		R5								; finally branch the address at the top of the stack								
			;Your code ends here
x			EQU 2 									;Define x
a			EQU 31 									;Define a
			ENDFUNC
			END