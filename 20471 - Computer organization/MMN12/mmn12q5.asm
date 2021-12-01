# Title:Mammn 12 Question 5        Filename: mmn12q5.asm
# Author: Devora Borowski 	Date: 11.08.2020
# Description: 
# Input:  two arrays of 10 words each, sign numbers, ascending order     
# Output:     intersect between the arrays - printed in descending order at base 10 and base 4
#                    
################# Data segment #####################
.data
array1: .word 0:10 # 10 elements that each is intialize as 0
array2: .word 0:10
msg1: .asciiz "Enter 10 numbers (sign)\n"
msg2: .asciiz "Inalid input\nEnter a number\n"
msg3: .asciiz "Insert the base to print the numbers (4/10)"
comma: .byte ','
################# Code segment #####################
.text
.globl main
main:  # main program entry point
        # fill the arrays with data from user
       la $a1,array1 # the addrss of array in the memory 
       jal get_array
       la $a1,array2 
       jal get_array
       
       la $a1,array1
       la $a2,array2
       li $a3,10
       jal find_eq
       
       # go down a line
       li $v0,11
       add $a0,$zero,'\n'
       syscall
      
       la $a1,array1
       la $a2,array2
       li $a3,4
       jal find_eq

       
exit:
       li $v0,10
       syscall
       
       ############################################################
       # procedure get_array                                      #
       # get from the user 10 sign numbers in ascending order     #
       # parameters:                                              #
       # a1 - array address                                       #
       # registers:                                               #
       # t0 - array address in memory                             #
       # t1 - array position                                      #
       # t2 - current input                                       #
       # t3 - current element                                     #
       # algoritem:                                               #
       # will read input from user, in ascending order            #
       # for invalid input will continue asking for currect input #
       # will store the data in array memory                      #
       ############################################################
get_array:       
       li $t1,0 # array position
       #print to the user
       li $v0,4
       la $a0,msg1 #enter 10 numbers   
       syscall 
       #get first element of array
       li $v0,5 # get an integer from user
       syscall
       move $t2,$v0 # save the input temporary by t2
       move $t0,$a1 # the address of the array move to t0
       sw $t2,0($t0) # store the first number in the array
loop:    
       lw $t3,($t0) # load current value into t3
       li $v0,5 # get an integer from user
       syscall
       move $t2,$v0 # save the input temporary by t2
       ble $t2,$t3,invalidInput  # invalid input - the value that was inserted is less or equal to the current index
       addi $t1,$t1,1 # counter++
       add $t0,$t0,4 # the number will be store in the next word
       sw $t2,($t0) #  store the number in the array
       bne $t1,9,loop
       jr $ra
invalidInput:
       #print to the user
       li $v0,4
       la $a0,msg2 # enter a correcr number
       syscall 
       j loop # get a new input
       ###########################################################################################
       # procedure find_eq                                                                       #
       # intersect between the arrays - printed in descending order at base as the input         #
       # parameters:                                                                             #
       # $a1 - address of first array                                                            #
       # $a2 - address of the second array                                                       #
       # $a3 - base to print out the numbers                                                     #
       # registers:                                                                              #
       # t1 - the address of current element in the first array, begin with the end of the array #
       # t2 - the address of current element in the second array                                 #
       # t3 - the value that in address t1                                                       #
       # t4 - the value that in address t4                                                       #
       # t5 - on which base to print the numbers                                                 #
       # algoritm:                                                                               #
       # will go through array from last element in will continue to the lower psition -         #
       # each time that the value in array is greater then the other array.                      #
       # when will find a number that appear in both array will print the number in the current base #
       ###########################################################################################

find_eq:       
       add $t1,$a1,36 # add 9 words mul by 4 byte each, to get to the last position in the array
       add $t2,$a2,36
       lw $t3,($t1) # t3=the value that in address t1
       lw $t4,($t2)
       move $t5,$a3 # on which base to print out the numbers
       addiu $sp,$sp,-4
       sw  $ra,0($sp)
first:# if the current element in the first array is greater then the second array, then go to the element before
       bgt $t3,$t4,moveFirst 
second:
       bgt $t4,$t3,moveSecond  
equal:
       # when the currnt vaules of both array are equal, print them out
       beq $t5,10,print10
       move $a3,$t3 # the number to print (in base 4)
       # save in stock
       addiu $sp,$sp,-20
       sw  $t1,16($sp)
       sw  $t2,12($sp)
       sw  $t3,8($sp)
       sw  $t4,4($sp)
       sw  $t5,0($sp)
       jal base4 # go to the procedure
       lw $t5,0($sp)
       lw $t4,4($sp)
       lw $t3,8($sp)
       lw $t2,12($sp)
       lw $t1,16($sp)
       addiu $sp,$sp,20
next:       
       li $v0,11
       lb $a0,comma
       syscall
       j moveFirst # move the first array position one to the left 
end: 
      lw $ra,0($sp)
      addiu $sp,$sp,4
      
      jr $ra
                       
moveFirst:
       addi $t1,$t1,-4 # the address of the word before the current
       bge $t1,$a1,load1 #if past the first element exit the program
       j end
load1:
       lw $t3,($t1)
       j first    
moveSecond:       
       addi $t2,$t2,-4
       bge $t2,$a2,load2  #branch to first -go through first and second, check in which array the current value is greater
       j end
load2:
       lw $t4,($t2) 
       j first
print10:
       li $v0,1
       move $a0,$t3
       syscall 
       j next
               
       ###################################################################
       # procedure base4                                                 #
       # print out a given number in base 4 16 digit (included a sign)   #
       # parameters:                                                     #
       # $a3 - number to print in base 4                                 #
       # registers:                                                      #
       # t0 - the integer that was passed                                #
       # t1 - counter of digit in bade 4 - 16 digit                      #
       # t2 - status of t1, print division or module                     #
       # t3 - the current digit                                          #
       # t4 - module of current digit by 4                               #
       # t5 - division of current digit by 4                             #
       # t6 - t6=4 , represent  base 4                                   #
       # algoritm:                                                       #
       # each digit in hexadecimal is two digit in base 4                #
       # divide a digit in 4 will give the more important digit          #
       # and module will give the less important digit                   #
       ###################################################################

base4:        
        move $t0,$a3
        li $t1,-1 # go through 8 hex digit, each digit loop twice (=16),-1 represent the minus sign
        li $t2,0 # statues of hex digit (0-divide,1-module), prints divide by 4, then module by 4
        # t1 - counter of digit in bade 4 - 16 digit
        # t1 is odd and t2=1 - then divide
        # t1 is even and t2=0 - then module
        li $t6,4 # base 4
loopBase4:
        srl $t3,$t0,28 # 4 bit * 7 to the right - to get the highest digit as one digit
        beq $t1,-1,sign # to print a minus sign if the number is negative
base:        
        bne $t2,$zero,odd
        # convert the digit from hex to two digit in base 4 
        div $t3,$t6
        mflo $t4 # divide
        mfhi $t5 # module
        j checkDigit
odd:
        # shift the entire number to the left, finished with the current digit
        sll $t0,$t0,4          
checkDigit:
        bne $t2,$zero,module
        # first digit in base 4
        addi $t2,$t2,1 # change status
        move $a0,$t4
        j print
continue:        
        addi $t1,$t1,1
        bne $t1,16,loopBase4
        jr $ra
        
print:  # print the value that is in a0
        li $v0,1
        syscall 
        j continue       
module: # second digit in base 4
        addi $t2,$t2,-1
        move $a0,$t5
        j print                                                        
sign:
        addi $t1,$t1,1
        ble $t3,7,base
        # if the number is negative print a minus sign, then treat it as the absolute value 
        li $v0,11
        add $a0,$zero,'-'
        syscall 
        abs $t0,$t0 #set the number to the absolute number
        srl $t3,$t0,28 # the highest digit is a different value
        j base                                                                                                                                   
