; BLG 212E HW 1 - Question 2
; Recursive Computation of the Power Function in O(a) Time
; 
;
; Student Name: 	Serife Damla Konur
; Student Number: 	040160433
; Description: (Please provide a short description of your approach to solving this problem)
; 
; Because base value never changes, I didn't pass the x to the subroutines and I just pass
; the exponent value using stack. I wrote 2 subroutine for function. In the 'pow' sr, program 
; checks the 'a' value and wrt to the result returns 1 or  branch to the 'recur' sr. 
; In 'recur' sr, pow(x,a-1) returns until a reaches 0. When program obtains the bottom value 1, 
; then multiplications are done in the recur sr. Finally, program return back to main and store 
; the result at address of y.


y_size		EQU 0x4                                 ;Allocate 4 bytes of space for an 
	
			AREA	output, DATA, READWRITE			;Define area to write the output
			ALIGN 
y 			SPACE y_size 							;Define y as the output 
y_end 

			AREA recursivePower, CODE, READONLY		;Declare new area for code
			ENTRY
			THUMB
			ALIGN

__main		FUNCTION								;Define main function
			EXPORT __main	

			;Your code starts here
			MOVS	R0, #x							; Move symbolic 'x' value to r1
			MOVS	R1, #a							; Move symbloic 'a' value to r2
			LDR		R6, =y							; Load start address of the allocated space 
			
			PUSH	{R1}							; push r1 to stack to be used as argument 
			BL		pow								; branch with link to function pow, and store its return address in LR 
			POP		{R3}							; pop the return value 
			STR		R3, [R6]						; finally, store the result value at address of the allocated space		
stop		B		stop							; end of the code

pow			POP		{R1}							; pop r1 which is the parameter 'a'
			CMP		R1,#0							; check whether a == 0 or not
			BNE		recur							; if a!=0 then branch to recursion
			MOVS	R3, #1							; if a==0 then pow(x,0) = 1, move 1 to r3, r3 is used to keep result
			PUSH	{R3}							; push base value to stack
			BX		LR								; then return using return address
			
			
recur		PUSH	{LR}							; push return address into the stack
			SUBS	R1, R1, #1						; decrement a by 1 -> a = a-1
			PUSH	{R1}							; store (a= a-1) value
			BL		pow								; then branch to function pow with link, and store its return address in LR
			POP		{R3}							; pop the return value
			POP		{R5}							; after a reaches 0, and finding pow(x,0) = 1 function comes here
													; the return address at top of the stack is poped
			MULS 	R3,R0,R3						; then the multiplication is done for a times -> 1 = x*1 -> x = x*x .... 
			PUSH	{R3}							; push return value into the
			BX		R5								; finally branch the last address at the stack
			;Your code ends here
x			EQU 2 									;Define x
a			EQU 31 									;Define a
			ENDFUNC
			END