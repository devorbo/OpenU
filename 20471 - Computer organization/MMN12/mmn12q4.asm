# Title:Mammn 12 Question 4        Filename: mmn12q4.asm
# Author: Devora Borowski 	Date: 9.08.2020
# Description: sum and sum squares of array as sign and unsign numbers 
#              print out difference between each pair of numbers
#              print array element as unsign numbers
# Input:       array - a array of byte in the memory
# Output:     $t0 - the sum of the array as (sign and) unsign values in array
#             $t3 - the sum squares of the array as (sign and) unsign values in array
#             also print result in screen
#                    
################# Data segment #####################
.data
array: .byte 23,-2,45,67,89,12,-100,0,120,6
msg1: .asciiz "The sum of the array(sign) is:"
msg2: .asciiz "\nThe sum of the squares(sign) is:"
msg3: .asciiz "\nThe difference of each pair of number(sign) in the array is:\n"
msg4: .asciiz "\nThe array as unsign numbers:\n"
msg5: .asciiz "\nThe sum of the array(unsign) is:"
msg6: .asciiz "\nThe sum of the squares(unsign) is:"
comma:.byte','
################# Code segment #####################
.text
.globl main
main:   # main program entry point
partA:
        li   $t0,0        # intialize the sum 
        li   $t1,0        # intialize the loop counter
        la   $t2,array    # the address of array in memory (start)
        li   $t3,0        # intialize the square sum 
sumLoop:   # loop over the elements of the array
        beq $t1,10,printSum # if the end of the loop go to printSum
        lb $t4,array($t1) # load byte from array in the current index
        add $t0,$t0,$t4 # add the element to the sum
        mul $t4,$t4,$t4 # multiply the value to get the square of the number
        add $t3,$t3,$t4 # add the square of the element to the sum
        addi $t1,$t1,1 # next index
        j sumLoop # repeat the loop        
printSum:
        # printing a comment to the user - sum array
        li $v0, 4
        la $a0, msg1
        syscall
        #print sum
        li $v0,1
        move $a0, $t0
        syscall

        # printing a comment  sum squares  array
        li $v0, 4
        la $a0, msg2
        syscall
        #print sum squares
        li $v0,1
        move $a0, $t3
        syscall
partB: # print the difference of each pair of numbers
        li $t0,0    # intialize the difference between a pair of numbers
        li $t1,0    # intialize the loop counter
        li $t3,0    # intialize the element, will be the first number in the pair
        li $t4,0    # t4 the second number of the pair
        
         # printing a comment - difference
        li $v0, 4
        la $a0, msg3
        syscall
diffLoop:   #print the difference of each pair of numbers
        # loop over the elements of the array
        beq $t1,9,partC # 9 pairs of numbers
        lb $t3,array($t1) # load byte from array in the current index
        addi $t1,$t1,1 # next index
        lb $t4,array($t1) # load byte from array on the next index
        sub $t0,$t3,$t4
        #print diff between current pair
        li $v0,1
        move $a0, $t0
        syscall
        li $t0,0    # intialize the difference
         # printing a comma between the numbers
        li $v0, 4
        la $a0, comma
        syscall
        j diffLoop # repeat the loop    

partC: # print the array values as unsign numbers
        li $t1,0    # intialize the loop counter  
        li $t3,0    # intialize the array current element
         # printing a comment - unsign numbers
        li $v0, 4
        la $a0, msg4
        syscall
unsignNum:
        beq $t1,10,partD # branch if equal
        lbu $t3,array($t1) # load byte from array in the current index
        #print number as unsign
        li $v0,1
        move $a0, $t3
        syscall
        # printing a comma between the numbers
        li $v0, 4
        la $a0, comma
        syscall
        addi $t1,$t1,1# next index
        j unsignNum # repeat the loop    
                                    
partD:
        li   $t0,0        # intialize the sum 
        li   $t1,0        # intialize the loop counter
        li   $t3,0        # intialize the square sum 
unsignSum:   # loop over the elements of the array
        beq $t1,10,printUnsignSum # if the end of the loop go to endloop
        lbu $t4,array($t1) # load byte from array as usign number, in the current index
        add $t0,$t0,$t4 # add the element to the sum
        mul $t4,$t4,$t4 # multiply the value to get the square of the number
        add $t3,$t3,$t4 # add the square of the element to the sum
        addi $t1,$t1,1 # next index
        j unsignSum # repeat the loop        
printUnsignSum:
        # printing a comment to the user - sum array
        li $v0, 4
        la $a0, msg5
        syscall
        #print sum - unsign
        li $v0,1
        move $a0, $t0
        syscall

        # printing a comment  sum squares  array
        li $v0, 4
        la $a0, msg6
        syscall
        #print sum squares - unsign
        li $v0,1
        move $a0, $t3
        syscall
                                                                                                              
exit:
        # End Program
        li $v0, 10
        syscall
    


