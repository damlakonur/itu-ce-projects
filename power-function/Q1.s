; BLG 212E HW 1 - Question 1
; Iterative Computation of the Power Function
; 
;
; Student Name: 	Serife Damla Konur
; Student Number: 	040160433
; Description: (Please provide a short description of your approach to solving this problem)


y_size		EQU 0x4									; Allocate 4 bytes of space for an integer output 
	
			AREA	output, DATA, READWRITE			; Define area to write the output
			ALIGN 								
y 			SPACE y_size 							; Define y as the output
y_end 

			AREA iterativePower,CODE, READONLY		; Declare new area for code
			ENTRY
			THUMB
			ALIGN

__main		FUNCTION								; Define main function
			EXPORT __main							; Make __main as global to access from startup file
				
			;Your code starts here
			MOVS 	R0,#1							; i=1 as index value
			MOVS	R1,#x							; Move symbolic 'x' value to r1
			MOVS	R2,#a							; Move symbloic 'a' value to r2
			MOVS	R3,#1							; y = 1 as initial value of output value
			LDR		R4,=y							; Load start address of the allocated space for output
			B		pow
			
pow			MULS 	R3,R1,R3						; Multiplication for power y = y*x
			STR		R3,[R4]							; store the y*x value at address of the output
			ADDS	R0,R0,#1						; update counter i+=1
			CMP		R2,R0							; check if i<=a
			BLT		stop							; if a<i then stop
			B		pow								; otherwise branch to pow again
			
stop		B	  	stop							; Branch stop
			;Your code ends here

x			EQU 2 									; Define x
a			EQU 30 									; Define a
			ENDFUNC
			END	